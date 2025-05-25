//
// Created by tKinsde on 2025/5/24.
//

#ifndef AGRICULTURAL_SYSTEM_EVENT_H
#define AGRICULTURAL_SYSTEM_EVENT_H

#include "cmsis_os2.h"

//线程间通信使用
#define EVENT_PAGE_UP   (1U << 0)  // 0x00000001 unsigned int
#define EVENT_PAGE_DOWN (1U << 1)  // 0x00000002 unsigned int


#endif //AGRICULTURAL_SYSTEM_EVENT_H
