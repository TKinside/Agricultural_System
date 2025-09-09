/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LED/led.h"
#include "AHT20/aht20.h"
#include "OLED/oled.h"
#include "../MiddleFile/event.h"
#include "usart.h"
#include "LIGHTSENSOR/light_sensor.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for Task_LED */
osThreadId_t Task_LEDHandle;
const osThreadAttr_t Task_LED_attributes = {
  .name = "Task_LED",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal7,
};
/* Definitions for Task_AHT20 */
osThreadId_t Task_AHT20Handle;
const osThreadAttr_t Task_AHT20_attributes = {
  .name = "Task_AHT20",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Task_OLED */
osThreadId_t Task_OLEDHandle;
const osThreadAttr_t Task_OLED_attributes = {
  .name = "Task_OLED",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Task_KEY */
osThreadId_t Task_KEYHandle;
const osThreadAttr_t Task_KEY_attributes = {
  .name = "Task_KEY",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for Task_LOGGER */
osThreadId_t Task_LOGGERHandle;
uint32_t Task_LOGGERBuffer[ 128 ];
osStaticThreadDef_t Task_LOGGERControlBlock;
const osThreadAttr_t Task_LOGGER_attributes = {
  .name = "Task_LOGGER",
  .cb_mem = &Task_LOGGERControlBlock,
  .cb_size = sizeof(Task_LOGGERControlBlock),
  .stack_mem = &Task_LOGGERBuffer[0],
  .stack_size = sizeof(Task_LOGGERBuffer),
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for Task_LIGHTSENSO */
osThreadId_t Task_LIGHTSENSOHandle;
const osThreadAttr_t Task_LIGHTSENSO_attributes = {
  .name = "Task_LIGHTSENSO",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Queue_toOLED */
osMessageQueueId_t Queue_toOLEDHandle;
uint8_t Queue_toOLEDBuffer[ 5 * 20 ];
osStaticMessageQDef_t Queue_toOLEDControlBlock;
const osMessageQueueAttr_t Queue_toOLED_attributes = {
  .name = "Queue_toOLED",
  .cb_mem = &Queue_toOLEDControlBlock,
  .cb_size = sizeof(Queue_toOLEDControlBlock),
  .mq_mem = &Queue_toOLEDBuffer,
  .mq_size = sizeof(Queue_toOLEDBuffer)
};
/* Definitions for Queue_toLogger */
osMessageQueueId_t Queue_toLoggerHandle;
uint8_t Queue_toLoggerBuffer[ 16 * 4 ];
osStaticMessageQDef_t Queue_toLoggerControlBlock;
const osMessageQueueAttr_t Queue_toLogger_attributes = {
  .name = "Queue_toLogger",
  .cb_mem = &Queue_toLoggerControlBlock,
  .cb_size = sizeof(Queue_toLoggerControlBlock),
  .mq_mem = &Queue_toLoggerBuffer,
  .mq_size = sizeof(Queue_toLoggerBuffer)
};
/* Definitions for MUTEX_I2C1 */
osMutexId_t MUTEX_I2C1Handle;
const osMutexAttr_t MUTEX_I2C1_attributes = {
  .name = "MUTEX_I2C1"
};
/* Definitions for MUTEX_UART */
osMutexId_t MUTEX_UARTHandle;
const osMutexAttr_t MUTEX_UART_attributes = {
  .name = "MUTEX_UART"
};
/* Definitions for SEM_I2C1_TX_CPLT */
osSemaphoreId_t SEM_I2C1_TX_CPLTHandle;
const osSemaphoreAttr_t SEM_I2C1_TX_CPLT_attributes = {
  .name = "SEM_I2C1_TX_CPLT"
};
/* Definitions for SEM_I2C1_RX_CPLT */
osSemaphoreId_t SEM_I2C1_RX_CPLTHandle;
const osSemaphoreAttr_t SEM_I2C1_RX_CPLT_attributes = {
  .name = "SEM_I2C1_RX_CPLT"
};
/* Definitions for SEM_ADC1_READ_CPLT */
osSemaphoreId_t SEM_ADC1_READ_CPLTHandle;
const osSemaphoreAttr_t SEM_ADC1_READ_CPLT_attributes = {
  .name = "SEM_ADC1_READ_CPLT"
};
/* Definitions for SEM_ADC1_CONV_CPLT */
osSemaphoreId_t SEM_ADC1_CONV_CPLTHandle;
const osSemaphoreAttr_t SEM_ADC1_CONV_CPLT_attributes = {
  .name = "SEM_ADC1_CONV_CPLT"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void AppTask_LED(void *argument);
void AppTask_AHT20(void *argument);
void AppTask_OLED(void *argument);
void AppTask_KEY(void *argument);
void AppTask_LOGGER(void *argument);
void AppTask_LIGHTSENSOR(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationIdleHook(void);

/* USER CODE BEGIN 2 */
void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of MUTEX_I2C1 */
  MUTEX_I2C1Handle = osMutexNew(&MUTEX_I2C1_attributes);

  /* creation of MUTEX_UART */
  MUTEX_UARTHandle = osMutexNew(&MUTEX_UART_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of SEM_I2C1_TX_CPLT */
  SEM_I2C1_TX_CPLTHandle = osSemaphoreNew(1, 1, &SEM_I2C1_TX_CPLT_attributes);

  /* creation of SEM_I2C1_RX_CPLT */
  SEM_I2C1_RX_CPLTHandle = osSemaphoreNew(1, 1, &SEM_I2C1_RX_CPLT_attributes);

  /* creation of SEM_ADC1_READ_CPLT */
  SEM_ADC1_READ_CPLTHandle = osSemaphoreNew(1, 0, &SEM_ADC1_READ_CPLT_attributes);

  /* creation of SEM_ADC1_CONV_CPLT */
  SEM_ADC1_CONV_CPLTHandle = osSemaphoreNew(1, 0, &SEM_ADC1_CONV_CPLT_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */

  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of Queue_toOLED */
  Queue_toOLEDHandle = osMessageQueueNew (5, 20, &Queue_toOLED_attributes);

  /* creation of Queue_toLogger */
  Queue_toLoggerHandle = osMessageQueueNew (16, 4, &Queue_toLogger_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Task_LED */
  Task_LEDHandle = osThreadNew(AppTask_LED, NULL, &Task_LED_attributes);

  /* creation of Task_AHT20 */
  Task_AHT20Handle = osThreadNew(AppTask_AHT20, NULL, &Task_AHT20_attributes);

  /* creation of Task_OLED */
  Task_OLEDHandle = osThreadNew(AppTask_OLED, NULL, &Task_OLED_attributes);

  /* creation of Task_KEY */
  Task_KEYHandle = osThreadNew(AppTask_KEY, NULL, &Task_KEY_attributes);

  /* creation of Task_LOGGER */
  Task_LOGGERHandle = osThreadNew(AppTask_LOGGER, NULL, &Task_LOGGER_attributes);

  /* creation of Task_LIGHTSENSO */
  Task_LIGHTSENSOHandle = osThreadNew(AppTask_LIGHTSENSOR, NULL, &Task_LIGHTSENSO_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_AppTask_LED */
/**
  * @brief  Function implementing the Task_LED thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_AppTask_LED */
void AppTask_LED(void *argument)
{
  /* USER CODE BEGIN AppTask_LED */
  /* Infinite loop */
    //TK_vLED_Init();
  for(;;)
  {
      //TK_vLED_Blink(ALL,100);
  }
  /* USER CODE END AppTask_LED */
}

/* USER CODE BEGIN Header_AppTask_AHT20 */
/**
* @brief Function implementing the Task_AHT20 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AppTask_AHT20 */
void AppTask_AHT20(void *argument)
{
  /* USER CODE BEGIN AppTask_AHT20 */
  /* Infinite loop */
  TK_vAHT20_Init();
  SensorMessage_t AHT20Data_Send;
  for(;;)
  {
      if (TK_bAHT20_Measure()==true)
      {
          AHT20Data_Send.type=AHT20;
          AHT20Data_Send.DATA.AHT20.temperature=TK_fAHT20_GetTemperature();
          AHT20Data_Send.DATA.AHT20.humidity=TK_fAHT20_GetHumidity();
          //给一秒钟来进行消息的入队
          osMessageQueuePut(Queue_toOLEDHandle,&AHT20Data_Send,0, pdMS_TO_TICKS(1000));

      }
      else
      {
          //保留错误处理
      }
      osDelay(pdMS_TO_TICKS(1000));//一秒钟测量一次
 }
  /* USER CODE END AppTask_AHT20 */
}

/* USER CODE BEGIN Header_AppTask_OLED */
/**
* @brief Function implementing the Task_OLED thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AppTask_OLED */
void AppTask_OLED(void *argument)
{
  /* USER CODE BEGIN AppTask_OLED */
  /* Infinite loop */
  OLED_Init();
  TK_vOLED_Clear();
  PageState currentPage = TK_xOLED_GetCurrentPage();//当前页面
  SensorMessage_t sensorData_Get;//接收传感器信息
  for(;;)
  {
      if (currentPage == PAGE_SENSOR)
      {
          if (osMessageQueueGet(Queue_toOLEDHandle,&sensorData_Get,NULL,osWaitForever)==osOK)
          {
              TK_vOLED_UpdateSensorData(sensorData_Get);
          }
      }
      else
      {
          //其他页面
      }

  }


  /* USER CODE END AppTask_OLED */
}

/* USER CODE BEGIN Header_AppTask_KEY */
/**
* @brief Function implementing the Task_KEY thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AppTask_KEY */
void AppTask_KEY(void *argument)
{
  /* USER CODE BEGIN AppTask_KEY */
  /* Infinite loop */
  //延时一会让别的模块上电初始化
    osDelay(pdMS_TO_TICKS(1500));
    static uint32_t pageFlags = 0;//当前页面
    for(;;)
    {
        //响应按键翻页
        pageFlags = osThreadFlagsWait(EVENT_PAGE_UP | EVENT_PAGE_DOWN, osFlagsWaitAny, osWaitForever);
        if (pageFlags == EVENT_PAGE_UP)
        {
            TK_vOLED_PageUp();

        }
        else if  (pageFlags == EVENT_PAGE_DOWN)
        {
            TK_vOLED_PageDown();
        }
    }
  /* USER CODE END AppTask_KEY */
}

/* USER CODE BEGIN Header_AppTask_LOGGER */
/**
* @brief Function implementing the Task_LOGGER thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AppTask_LOGGER */
void AppTask_LOGGER(void *argument)
{
  /* USER CODE BEGIN AppTask_LOGGER */
  char* readyLog_ptr;
  /* Infinite loop */
  for(;;)
  {
      if (osMessageQueueGet(Queue_toLoggerHandle,&readyLog_ptr,NULL,osWaitForever)==osOK)
      {
          if (readyLog_ptr!= NULL)
          {
              if (osMutexAcquire(MUTEX_UARTHandle,osWaitForever)==osOK)
              {
                  //暂时采用阻塞模式
                  HAL_UART_Transmit(&huart2,(uint8_t*)readyLog_ptr,strlen(readyLog_ptr), pdMS_TO_TICKS(50));
                  osMutexRelease(MUTEX_UARTHandle);
              }
              vPortFree(readyLog_ptr);
          }

      }
  }
  /* USER CODE END AppTask_LOGGER */
}

/* USER CODE BEGIN Header_AppTask_LIGHTSENSOR */
/**
* @brief Function implementing the Task_LIGHTSENSO thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AppTask_LIGHTSENSOR */
void AppTask_LIGHTSENSOR(void *argument)
{
  /* USER CODE BEGIN AppTask_LIGHTSENSOR */
  /* Infinite loop */
  TK_vLED_Init();
  SensorMessage_t LightSensorData_Send;
  for(;;)
  {
      if(osSemaphoreAcquire(SEM_ADC1_CONV_CPLTHandle,osWaitForever)==osOK)
      {
        TK_vLightSensor_Conversion();
      }
      if (osSemaphoreAcquire(SEM_ADC1_CONV_CPLTHandle, pdMS_TO_TICKS(1000))==osOK)
      {
          LightSensorData_Send.type=LIGHT_SENSOR;
          LightSensorData_Send.DATA.light_intensity=TK_fLightSensor_GetLightIntensity();
          osMessageQueuePut(Queue_toOLEDHandle,&LightSensorData_Send,0, pdMS_TO_TICKS(1000));
      }
      osDelay(pdMS_TO_TICKS(1000));//一秒钟测量一次y()
  }
  /* USER CODE END AppTask_LIGHTSENSOR */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

