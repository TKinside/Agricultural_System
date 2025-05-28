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
#include "led.h"
#include "aht20.h"
#include "oled.h"
#include "event.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
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
  .priority = (osPriority_t) osPriorityNormal,
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
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Queue_toOLED */
osMessageQueueId_t Queue_toOLEDHandle;
uint8_t Queue_toOLEDBuffer[ 5 * 16 ];
osStaticMessageQDef_t Queue_toOLEDControlBlock;
const osMessageQueueAttr_t Queue_toOLED_attributes = {
  .name = "Queue_toOLED",
  .cb_mem = &Queue_toOLEDControlBlock,
  .cb_size = sizeof(Queue_toOLEDControlBlock),
  .mq_mem = &Queue_toOLEDBuffer,
  .mq_size = sizeof(Queue_toOLEDBuffer)
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void AppTask_LED(void *argument);
void AppTask_AHT20(void *argument);
void AppTask_OLED(void *argument);

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

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */

  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of Queue_toOLED */
  Queue_toOLEDHandle = osMessageQueueNew (5, 16, &Queue_toOLED_attributes);

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

  for(;;)
  {
    osDelay(1);
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
  SensorMessage_t AHT20_msg;
  for(;;)
  {
      if (TK_bAHT20_Measure()==true)
      {
          AHT20_msg.type=AHT20;
          AHT20_msg.DATA.AHT20.temperature=TK_fAHT20_GetTemperature();
          AHT20_msg.DATA.AHT20.humidity=TK_fAHT20_GetHumidity();
          osMessageQueuePut(Queue_toOLEDHandle,&AHT20_msg,0,0);
      }
      else
      {
          //保留错误处理
      }
      osDelay(pdMS_TO_TICKS(1000));
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
  SensorMessage_t Sensor_Getted;
  for(;;)
  {
      uint32_t flags = osThreadFlagsWait(EVENT_PAGE_UP | EVENT_PAGE_DOWN, osFlagsWaitAny, 0);
      if (flags & EVENT_PAGE_UP)
      {
         TK_vOLED_PageUp();

      }
      else if  (flags & EVENT_PAGE_DOWN)
      {
          TK_vOLED_PageDown();

      }
      if (CurrentPage==PAGE_SENSOR)
      {
          if (osMessageQueueGet(Queue_toOLEDHandle,&Sensor_Getted,0,0)==osOK) {

              TK_vOLED_UpdateSensorData(Sensor_Getted);

          }


      }

  }


  /* USER CODE END AppTask_OLED */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

