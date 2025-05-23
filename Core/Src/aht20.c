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




// 温湿度数据暂存变量
float Temperature=0.0f;
float Humidity=0.0f;

// ========================== 底层通信函数 ==========================

// 函数AHT20_Send用于向AHT20传感器发送数据
void TK_vAHT20_Send(uint8_t *data, uint8_t len) {
    // 使用HAL库的I2C主发送函数，向AHT20传感器发送数据
    HAL_I2C_Master_Transmit_DMA(&hi2c1, AHT20_ADDRESS, data, len);
}

// 函数AHT20_Receive用于从AHT20传感器接收数据
void TK_vAHT20_Receive(uint8_t *data, uint8_t len) {
    // 使用HAL库的I2C主接收函数从AHT20传感器接收数据
    HAL_I2C_Master_Receive_DMA(&hi2c1, AHT20_ADDRESS, data, len);
}

void TK_vAHT20_Init(void) {

    // 定义一个uint8_t类型的变量readBuffer
    uint8_t readBuffer;
    // 延时40ms,初始化必须硬性延迟
    HAL_Delay(40);
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

void TK_vAHT20_Measure(void) {
    // 定义发送缓冲区，包含三个字节的数据
    uint8_t sendBuffer[3] = {0xAC, 0x33, 0x00};
    // 定义接收缓冲区，包含六个字节的数据
    uint8_t readBuffer[6];
    // 发送数据
    TK_vAHT20_Send(sendBuffer, 3);
    // 延时75ms
    osDelay(pdMS_TO_TICKS(50));
    // 接收数据
    TK_vAHT20_Receive(readBuffer, 6);

    // 判断数据是否有效
    if ((readBuffer[0] & 0x80) == 0x00) {
        // 定义湿度变量和温度变量
        float humi, temp;
        // 判断编译器是否支持__CMSIS_GCC_H宏定义
#ifdef __CMSIS_GCC_H //只快一点点，但是看起来可能更直观一些：__REV()是硬实现的大小端序转换，在cmsis_gcc.h中定义
        // 使用__REV()函数进行大小端序转换，计算湿度
        humi = (__REV(*(uint32_t*)readBuffer) & 0x00fffff0) >> 4;
        // 使用__REV()函数进行大小端序转换，计算温度
        temp = __REV(*(uint32_t*)(readBuffer+2)) & 0x000fffff;
#else
        // 手动进行大小端序转换，计算湿度
        humi = ((uint32_t)readBuffer[3] >> 4) + ((uint32_t)readBuffer[2] << 4) + ((uint32_t)readBuffer[1] << 12);
        // 手动进行大小端序转换，计算温度
    temp = (((uint32_t)readBuffer[3] & 0x0F) << 16) + (((uint32_t)readBuffer[4]) << 8) + (uint32_t)readBuffer[5];
#endif
        // 计算湿度
        Humidity = humi * 100 / (1 << 20);
        // 计算温度
        Temperature = temp * 200 / (1 << 20) - 50;
    }
}

float TK_fAHT20_Temperature(void) {
    return Temperature;
}

float TK_fAHT20_Humidity(void) {
    return Humidity;
}

