//
// Created by tKinsde on 2025/5/18.
//负责一系列对LED灯的操作，基于STM32F103C8T6（开发板）

#ifndef AGRICULTURAL_SYSTEM_LED_H
#define AGRICULTURAL_SYSTEM_LED_H

#include "main.h"
#include "stdbool.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
enum LED_COLOR
{
    ALL=0,
    LED_RED,
    LED_GREEN,
    LED_BLUE,
    LED_RED_AND_GREEN,
    LED_RED_AND_BLUE,
    LED_GREEN_AND_BLUE,
    STOP_BLINK
};


void TK_vLED_Init(void);
void TK_vLED_On(enum LED_COLOR LED_SWITCH);
void TK_vLED_Off(enum LED_COLOR LED_SWITCH);
void TK_vLED_Toggle(enum LED_COLOR LED_SWITCH);
void TK_vLED_Blink(enum LED_COLOR LED_SWITCH,uint32_t usTime);
void TK_vLED_Delay(enum LED_COLOR LED_SWITCH,uint32_t usTime);







#endif //AGRICULTURAL_SYSTEM_LED_H
