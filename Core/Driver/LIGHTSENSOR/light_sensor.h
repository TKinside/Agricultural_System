//
// Created by tKinsde on 2025/9/9.
//

#ifndef AGRICULTURAL_SYSTEM_LIGHT_SENSOR_H
#define AGRICULTURAL_SYSTEM_LIGHT_SENSOR_H

#include "main.h"

#define LIGHT_SENSOR_DATA_BUFFER_SIZE 16

void TK_vLightSensor_Init(void);
float TK_fLightSensor_GetLightIntensity(void);
void TK_vLightSensor_Conversion(void);











#endif //AGRICULTURAL_SYSTEM_LIGHT_SENSOR_H



