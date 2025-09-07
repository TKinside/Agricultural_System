//
// Created by tKinsde on 2025/9/7.
//

#include "logger.h"


extern osMessageQueueId_t Queue_toLoggerHandle;//消息队列句柄
extern osMutexId_t MUTEX_UARTHandle;//串口互斥锁句柄

void log_printf(const char *format, ...)
{
    // 在栈上创建一个足够大的临时缓冲区
    char temp_buffer[256];

    va_list args;
    va_start(args, format);
    // 使用 vsnprintf 安全地格式化字符串
    int len = vsnprintf(temp_buffer, sizeof(temp_buffer), format, args);
    va_end(args);

    if (len > 0)
    {
        // 从FreeRTOS堆中动态申请一块大小正好的内存
        char* dynamic_buffer = pvPortMalloc(len + 1);

        if (dynamic_buffer != NULL)
        {
            // 申请成功，将格式化好的字符串复制到新内存中
            strcpy(dynamic_buffer, temp_buffer);

            // 将这块内存的“地址”发送到日志队列
            if (osMessageQueuePut(Queue_toLoggerHandle, &dynamic_buffer, 0, 0) != osOK)
            {
                // 如果队列满了，发送失败，必须释放内存，防止泄漏
                vPortFree(dynamic_buffer);
            }
        }
        // 如果 pvPortMalloc 失败，这条日志就会被无声地丢弃
    }
}