//
// Created by tKinsde on 2025/5/25.
//

#include "it_callback.h"
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_12)
    {
        osThreadFlagsSet(Task_OLEDHandle,EVENT_PAGE_UP);
    }

    if(GPIO_Pin == GPIO_PIN_13)
    {
        osThreadFlagsSet(Task_OLEDHandle,EVENT_PAGE_DOWN);
    }
}

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    if (hi2c->Instance == I2C1)
    {
        //TK_vLED_Blink(LED_GREEN, 100);
        osSemaphoreRelease(SEM_I2C1_TX_CPLTHandle);
        //TK_vLED_Off(LED_GREEN);
    }
}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    if (hi2c->Instance == I2C1)
    {
        osSemaphoreRelease(SEM_I2C1_RX_CPLTHandle);
    }
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c) {
    if (hi2c->Instance == I2C1) {
        // 发生错误时，将两个信号量都释放，防止任何等待的任务死锁
        osSemaphoreRelease(SEM_I2C1_TX_CPLTHandle);
        osSemaphoreRelease(SEM_I2C1_RX_CPLTHandle);
    }
}