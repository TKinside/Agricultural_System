#ifndef __OLED_H__
#define __OLED_H__

#include "font.h"
#include "main.h"
#include "string.h"
#include "i2c.h"
#include <math.h>
#include <stdlib.h>
#include "stdio.h"
#include "../../MiddleFile/message.h"
#include <cmsis_os2.h>
#include "LED/led.h"


typedef enum {
  OLED_COLOR_NORMAL = 0, // 正常模式 黑底白字
  OLED_COLOR_REVERSED    // 反色模式 白底黑字
} OLED_ColorMode;

typedef enum {
    PAGE_HOME=0,
    PAGE_SENSOR,      // 显示温湿度和光照强度
    PAGE_MACHINE,      // 显示电机状态
    PAGE_INFORMATION, //显示关于信息
    PAGE_COUNT
} PageState;
typedef enum {
    BRIGHTNESS_STANDBY=0, // 待机亮度
    BRIGHTNESS_ACTIVE   // 运行亮度
}MachineState_t;
//I2C1总线互斥锁
extern osMutexId_t MUTEX_I2C1Handle;
//I2C1发送完成信号量
extern  osSemaphoreId_t SEM_I2C1_TX_CPLTHandle;
//I2C1接收完成信号量
extern  osSemaphoreId_t SEM_I2C1_RX_CPLTHandle;


void OLED_Init(void);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);

void OLED_NewFrame(void);
void OLED_ShowFrame(void);
void OLED_SetPixel(uint8_t x, uint8_t y, OLED_ColorMode color);

void OLED_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, OLED_ColorMode color);
void OLED_DrawRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h, OLED_ColorMode color);
void OLED_DrawFilledRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h, OLED_ColorMode color);
void OLED_DrawTriangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3, OLED_ColorMode color);
void OLED_DrawFilledTriangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3, OLED_ColorMode color);
void OLED_DrawCircle(uint8_t x, uint8_t y, uint8_t r, OLED_ColorMode color);
void OLED_DrawFilledCircle(uint8_t x, uint8_t y, uint8_t r, OLED_ColorMode color);
void OLED_DrawEllipse(uint8_t x, uint8_t y, uint8_t a, uint8_t b, OLED_ColorMode color);
void OLED_DrawImage(uint8_t x, uint8_t y, const Image *img, OLED_ColorMode color);

void OLED_PrintASCIIChar(uint8_t x, uint8_t y, char ch, const ASCIIFont *font, OLED_ColorMode color);
void OLED_PrintASCIIString(uint8_t x, uint8_t y, char *str, const ASCIIFont *font, OLED_ColorMode color);
void OLED_PrintString(uint8_t x, uint8_t y, char *str, const Font *font, OLED_ColorMode color);

//以上是商家提供驱动以及基本函数封装，下为自定义
void OLED_SetContrast(uint8_t contrast);

void TK_vOLED_DisplayCurrentPage(void);
void TK_vOLED_PageUp(void);
void TK_vOLED_PageDown(void);
void TK_vOLED_UpdateSensorData(SensorMessage_t sensorData_Get);
void TK_vOLED_Clear(void);
void TK_vOLED_DisplayMachineState(MachineState_t machineState);
PageState TK_xOLED_GetCurrentPage();
void TK_vOLED_RefreshArea(uint8_t x, uint8_t y, uint8_t width, uint8_t height);

#endif // __OLED_H__