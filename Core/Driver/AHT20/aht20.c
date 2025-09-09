//
// Created by tKinsde on 2025/5/22.
//

/*模块配套规格说明书内容：
1.上电后要等待40ms，读取温湿度值之前， 首
先要看状态字的校准使能位Bit[3]是否为 1(通
过发送0x71可以获取一个字节的状态字)，如果
不为1，要发送0xBE命令(初始化)，此命令参数
有两个字节， 第一个字节为0x08，第二个字节
为0x00。
2.直接发送 0xAC命令(触发测量)，此命令参数
有两个字节，第一个字节为 0x33，第二个字节
为0x00。
3.等待75ms待测量完成，忙状态Bit[7]为0，然
后可以读取六个字节(发0X71即可以读取)。
4.计算温湿度值。
*/
#include "aht20.h"
#include "i2c.h"
#include "cmsis_os2.h"

// 温湿度数据暂存变量
static AHT20_Data_t AHT20_Data_Global={0.0f,0.0f};
//I2C1总线互斥锁
extern osMutexId_t MUTEX_I2C1Handle;
//I2C1发送完成信号量
extern  osSemaphoreId_t SEM_I2C1_TX_CPLTHandle;
//I2C1接收完成信号量
extern  osSemaphoreId_t SEM_I2C1_RX_CPLTHandle;



// ========================== 底层通信函数 ==========================

// 函数AHT20_Send用于向AHT20传感器发送数据
void TK_vAHT20_Send(uint8_t *data, uint8_t len) {
    // 使用HAL库的I2C主发送函数，向AHT20传感器发送数据
    // 1. 获取总线使用权
    if (osMutexAcquire(MUTEX_I2C1Handle, osWaitForever) == osOK)
    {
        // 2. 启动DMA传输
        HAL_StatusTypeDef status = HAL_I2C_Master_Transmit_DMA(&hi2c1, AHT20_ADDRESS, data, len);

        if (status == HAL_OK)
        {

            // 3. 等待DMA硬件完成数据搬运
            osSemaphoreAcquire(SEM_I2C1_TX_CPLTHandle, osWaitForever);

            // 4. 等待I2C硬件协议完成，总线真正空闲
            //    这是预防问题的核心！
            uint32_t tickstart = osKernelGetTickCount();
            while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
            {

                // 如果等待超时（例如超过25ms），说明总线被硬件卡死
                if ((osKernelGetTickCount() - tickstart) > 25)
                {
                    // 执行HAL库级别的安全恢复流程
                    HAL_I2C_DeInit(&hi2c1);
                    HAL_I2C_Init(&hi2c1);
                    break; // 跳出循环
                }
            }
        }
        else // DMA启动失败 (status is HAL_BUSY or HAL_ERROR)
        {
            //TK_vLED_Delay(LED_RED,10);
            // 立即执行HAL库级别的安全恢复流程
            HAL_I2C_DeInit(&hi2c1);
            HAL_I2C_Init(&hi2c1);
        }

        // 5. 归还总线使用权
        osMutexRelease(MUTEX_I2C1Handle);

        // 注意：这里不再需要任何 osDelay()！
    }
}

// 函数AHT20_Receive用于从AHT20传感器接收数据
void TK_vAHT20_Receive(uint8_t *data, uint8_t len) {
    // 使用HAL库的I2C主接收函数从AHT20传感器接收数据

    // 1. 获取总线使用权
    if (osMutexAcquire(MUTEX_I2C1Handle, osWaitForever) == osOK)
    {
        // 2. 启动DMA传输
        HAL_StatusTypeDef status = HAL_I2C_Master_Receive_DMA(&hi2c1, AHT20_ADDRESS, data, len);

        if (status == HAL_OK)
        {

            // 3. 等待DMA硬件完成数据搬运
            osSemaphoreAcquire(SEM_I2C1_RX_CPLTHandle, osWaitForever);

            // 4. 等待I2C硬件协议完成，总线真正空闲
            //    这是预防问题的核心！
            uint32_t tickstart = osKernelGetTickCount();
            while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
            {

                // 如果等待超时（例如超过25ms），说明总线被硬件卡死
                if ((osKernelGetTickCount() - tickstart) > 25)
                {
                    // 执行HAL库级别的安全恢复流程
                    HAL_I2C_DeInit(&hi2c1);
                    HAL_I2C_Init(&hi2c1);
                    break; // 跳出循环
                }
            }
        }
        else // DMA启动失败 (status is HAL_BUSY or HAL_ERROR)
        {
            //TK_vLED_Delay(LED_RED,10);
            // 立即执行HAL库级别的安全恢复流程
            HAL_I2C_DeInit(&hi2c1);
            HAL_I2C_Init(&hi2c1);
        }

        // 5. 归还总线使用权
        osMutexRelease(MUTEX_I2C1Handle);

        // 注意：这里不再需要任何 osDelay()！
    }
}

void TK_vAHT20_Init(void) {

    // 定义一个uint8_t类型的变量readBuffer
    uint8_t readBuffer;
    // 延时40ms,初始化必须硬性延迟
    osDelay(50);
    // 从AHT20接收一个字节的数据
    TK_vAHT20_Receive(&readBuffer, 1);
    // 如果接收到的数据与0x08进行按位与运算的结果为0
    if ((readBuffer & 0x08) == 0x00) {
        // 定义一个uint8_t类型的数组sendBuffer，长度为3
        uint8_t sendBuffer[3] = {0xBE, 0x08, 0x00};
        // 向AHT20发送3个字节的数据
        TK_vAHT20_Send(sendBuffer, 3);
    }
}

bool TK_bAHT20_Measure(void) {
    // 定义发送缓冲区，包含触发测量的命令
    uint8_t sendBuffer[3] = {0xAC, 0x33, 0x00};
    // 定义接收缓冲区，用于存放AHT20返回的6个字节数据
    uint8_t readBuffer[6];

    // 发送触发测量命令
    TK_vAHT20_Send(sendBuffer, 3);
    // 等待75ms让传感器完成测量。
    // 在RTOS环境中，osDelay是更好的选择
    osDelay(75);
    // 接收传感器数据
    TK_vAHT20_Receive(readBuffer, 6);

    // --- 开始修改的部分 ---

    // 步骤1: 检查状态字节，确保数据是有效的
    // AHT20手册规定，忙标志位(Bit[7])为0时，数据才有效。
    if ((readBuffer[0] & 0x80) == 0) {
        //ox80:10000000  (Bit[7])为0:0xxxxxxxx
        // 定义32位无符号整型变量，用于存放拼接后的原始数据
        uint32_t humi_raw = 0;
        uint32_t temp_raw = 0;

        // 步骤2: 精确地按照数据手册进行位操作，拼接原始数据

        // **拼接20位的湿度原始数据**
        // Byte 1 是最高8位 -> 对应湿度数据的 bits [19:12]
        humi_raw |= ((uint32_t)readBuffer[1]) << 12;
        // Byte 2 是中间8位 -> 对应湿度数据的 bits [11:4]
        humi_raw |= ((uint32_t)readBuffer[2]) << 4;
        // Byte 3 的高4位是最低4位 -> 对应湿度数据的 bits [3:0]
        humi_raw |= (((uint32_t)readBuffer[3]) & 0xF0) >> 4;

        // **拼接20位的温度原始数据**
        // Byte 3 的低4位是最高4位 -> 对应温度数据的 bits [19:16]
        temp_raw |= ((uint32_t)readBuffer[3] & 0x0F) << 16;
        // Byte 4 是中间8位 -> 对应温度数据的 bits [15:8]
        temp_raw |= (uint32_t)readBuffer[4] << 8;
        // Byte 5 是最低8位 -> 对应温度数据的 bits [7:0]
        temp_raw |= (uint32_t)readBuffer[5];

        // 步骤3: 使用官方给定的公式进行计算
        // 为了确保浮点数运算的精度，所有常量都使用浮点数形式 (例如 100.0f)

        // 计算最终湿度值
        AHT20_Data_Global.Humidity = ((float)humi_raw / 1048576.0f) * 100.0f; // 1048576.0f 就是 2^20，最终得到的结果是一个百分比

        // 计算最终温度值
        AHT20_Data_Global.Temperature = ((float)temp_raw / 1048576.0f) * 200.0f - 50.0f;

        // 数据解析和计算成功
        return true;
    }

    // 如果忙标志位不为0，或者其他任何原因导致数据无效，则直接返回false
    return false;
}

float TK_fAHT20_GetTemperature(void) {
    return AHT20_Data_Global.Temperature;
}

float TK_fAHT20_GetHumidity(void) {
    return AHT20_Data_Global.Humidity;
}

