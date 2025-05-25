//
// Created by tKinsde on 2025/5/22.
//

#ifndef AGRICULTURAL_SYSTEM_AHT20_H
#define AGRICULTURAL_SYSTEM_AHT20_H

#include "main.h"
#include "i2c.h"
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "message.h"
#include "stdbool.h"
// AHT20 IIC器件地址
#define AHT20_ADDRESS 0x70
// 温湿度数据暂存变量
extern float Temperature;
extern float Humidity;

void TK_vAHT20_Send(uint8_t *data, uint8_t len);
void TK_vAHT20_Receive(uint8_t *data, uint8_t len);
void TK_vAHT20_Init(void);
bool TK_bAHT20_Measure(void);
float TK_fAHT20_GetTemperature(void);
float TK_fAHT20_GetHumidity(void);


#endif //AGRICULTURAL_SYSTEM_AHT20_H
