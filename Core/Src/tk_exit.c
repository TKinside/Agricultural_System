//
// Created by tKinsde on 2025/5/25.
//

#include "tk_exit.h"
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

