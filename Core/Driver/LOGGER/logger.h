//
// Created by tKinsde on 2025/9/7.
//

#ifndef AGRICULTURAL_SYSTEM_LOGGER_H
#define AGRICULTURAL_SYSTEM_LOGGER_H

#include "main.h"
#include "cmsis_os2.h"      //需要 osMessageQueueId_t
#include "FreeRTOS.h"      // 需要 pvPortMalloc/vPortFree
#include "usart.h"         // 需要 UART 句柄和 HAL_UART_Transmit
#include <stdio.h>         // 需要 vsnprintf
#include <string.h>        // 需要 strlen
#include <stdarg.h>        // 需要 va_list, va_start, va_end





void log_printf(const char *format, ...);



#endif //AGRICULTURAL_SYSTEM_LOGGER_H
