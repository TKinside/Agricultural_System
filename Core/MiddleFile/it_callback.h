//
// Created by tKinsde on 2025/5/25.
//

#ifndef AGRICULTURAL_SYSTEM_IT_CALLBACK_H
#define AGRICULTURAL_SYSTEM_IT_CALLBACK_H

#include "main.h"
#include "cmsis_os2.h"
#include "event.h"

extern osThreadId_t Task_OLEDHandle;
extern  osSemaphoreId_t SEM_I2C1_TX_CPLTHandle;
extern  osSemaphoreId_t SEM_I2C1_RX_CPLTHandle;
extern  osSemaphoreId_t SEM_ADC1_READ_CPLTHandle;


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);









#endif //AGRICULTURAL_SYSTEM_IT_CALLBACK_H
