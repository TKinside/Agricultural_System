//
// Created by tKinsde on 2025/5/18.
//

#include "led.h"

// 函数TK_bLED_Init用于初始化LED灯
void TK_vLED_Init(void)
{
    // 所有灯亮灭各0.5s代表初始化成功
    TK_vLED_Off(ALL);
    HAL_Delay(500);
    TK_vLED_On(ALL);
    HAL_Delay(500);
}
// 函数TK_vLED_On用于开启LED灯
void TK_vLED_On(enum LEDColor_t LED_SWITCH)
{
    // 根据LED_SWITCH的值，控制LED灯的亮灭
    switch (LED_SWITCH)
    {
        case ALL:
            // 打开所有LED灯
            HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
            break;
        case LED_RED:
            // 打开红灯
            HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
            break;
        case LED_GREEN:
            // 打开绿灯
            HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
            break;
        case LED_BLUE:
            // 打开蓝灯
            HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
            break;
        case LED_RED_AND_GREEN:
            // 打开红灯和绿灯
            HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
            break;
        case LED_RED_AND_BLUE:
            // 打开红灯和蓝灯
            HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
            break;
        case LED_GREEN_AND_BLUE:
            // 打开绿灯和蓝灯
            HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
            break;
        default:
            // 默认情况，不执行任何操作
            break;
    }
}
// 函数TK_vLED_Off用于关闭LED灯
void TK_vLED_Off(enum LEDColor_t LED_SWITCH)
{
    // 根据LED_SWITCH的值，关闭对应的LED灯
    switch (LED_SWITCH)
    {
        // 关闭所有LED灯
        case ALL:
            HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
            break;
        // 关闭红色LED灯
        case LED_RED:
            HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
            break;
        // 关闭绿色LED灯
        case LED_GREEN:
            HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
            break;
        // 关闭蓝色LED灯
        case LED_BLUE:
            HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
            break;
        // 关闭红色和绿色LED灯
        case LED_RED_AND_GREEN:
            HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
            break;
        // 关闭红色和蓝色LED灯
        case LED_RED_AND_BLUE:
            HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
            break;
        // 关闭绿色和蓝色LED灯
        case LED_GREEN_AND_BLUE:
            HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
            break;
        // 默认情况
        default:
            break;
    }
}
// 函数TK_vLED_Toggle用于切换LED灯的状态
void TK_vLED_Toggle(enum LEDColor_t LED_SWITCH)
{
    // 根据LED_SWITCH的值，切换对应的LED灯的状态
    switch (LED_SWITCH)
    {
        // 切换所有LED灯的状态
        case ALL:
            HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
            HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
            HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
            break;
        // 切换红色LED灯的状态
        case LED_RED:
            HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
            break;
        // 切换绿色LED灯的状态
        case LED_GREEN:
            HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
            break;
        // 切换蓝色LED灯的状态
        case LED_BLUE:
            HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
            break;
        // 切换红色和绿色LED灯的状态
        case LED_RED_AND_GREEN:
            HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
            HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
            break;
        // 切换红色和蓝色LED灯的状态
        case LED_RED_AND_BLUE:
            HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
            HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
            break;
        // 切换绿色和蓝色LED灯的状态
        case LED_GREEN_AND_BLUE:
            HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
            HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
            break;
        // 默认情况，不进行任何操作
        default:
            break;
    }
}
// 函数TK_vLED_Blink用于控制LED灯的闪烁
// 参数LED_SWITCH表示要控制的LED灯的颜色
// 参数usTime表示LED灯的闪烁时间
void TK_vLED_Blink(enum LEDColor_t LED_SWITCH,uint32_t usTime)
{
    // 调用TK_vLED_Toggle函数，控制LED灯的开关
    TK_vLED_Toggle(LED_SWITCH);
    // 调用osDelay函数，延时usTime毫秒
    osDelay(pdMS_TO_TICKS(usTime));
}
// 函数TK_vLED_Delay用于控制LED灯的亮灭，参数LED_SWITCH表示要控制的LED灯的颜色，usTime表示延迟的时间
void TK_vLED_Delay(enum LEDColor_t LED_SWITCH,uint32_t usTime)
{
    // 打开LED灯
    TK_vLED_On(LED_SWITCH);
    // 延迟usTime毫秒
    osDelay(pdMS_TO_TICKS(usTime));
    // 关闭LED灯
    TK_vLED_Off(LED_SWITCH);
}

