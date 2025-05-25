//
// Created by tKinsde on 2025/5/25.
//

#ifndef AGRICULTURAL_SYSTEM_TK_EXIT_H
#define AGRICULTURAL_SYSTEM_TK_EXIT_H

#include "main.h"
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "event.h"

extern osThreadId_t Task_OLEDHandle;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);


#endif //AGRICULTURAL_SYSTEM_TK_EXIT_H
