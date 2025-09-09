//
// Created by tKinsde on 2025/9/9.
//

#include "light_sensor.h"
#include "message.h"
#include "adc.h"
#include "cmsis_os2.h"

//光照原始值数组
static volatile uint16_t LightSensor_Data_Raw[LIGHT_SENSOR_DATA_BUFFER_SIZE];
//光照平均原始值
static volatile uint16_t LightSensor_Data_Raw_Average = 0;
//光照百分比
static volatile float LightSensor_Data_Percent_Global = 0.0f;
//转换完成信号量
extern osSemaphoreId_t SEM_ADC1_CONV_CPLTHandle;
void TK_vLightSensor_Init(void){
    //启动ADC校准
    HAL_ADCEx_Calibration_Start(&hadc1);
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)LightSensor_Data_Raw, LIGHT_SENSOR_DATA_BUFFER_SIZE);
}
float TK_fLightSensor_GetLightIntensity(void)
{
    return LightSensor_Data_Percent_Global;
}

void TK_vLightSensor_Conversion(void)
{
    uint32_t sum=0;
    for (int i = 0; i < LIGHT_SENSOR_DATA_BUFFER_SIZE; i++) {
        sum+=LightSensor_Data_Raw[i];
    }
    LightSensor_Data_Raw_Average= sum/LIGHT_SENSOR_DATA_BUFFER_SIZE;
    LightSensor_Data_Percent_Global =(1.0f - ((float)LightSensor_Data_Raw_Average / 4095.0f)) * 100.0f;
    osSemaphoreRelease(SEM_ADC1_CONV_CPLTHandle);
}