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
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
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
/* Definitions for TK_LEDInitTimeoutTimer */
osTimerId_t TK_LEDInitTimeoutTimerHandle;
const osTimerAttr_t TK_LEDInitTimeoutTimer_attributes = {
  .name = "TK_LEDInitTimeoutTimer"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void AppTask_LED(void *argument);
void AppTask_AHT20(void *argument);
void TK_LEDInitCallback(void *argument);

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

  /* Create the timer(s) */
  /* creation of TK_LEDInitTimeoutTimer */
  TK_LEDInitTimeoutTimerHandle = osTimerNew(TK_LEDInitCallback, osTimerPeriodic, NULL, &TK_LEDInitTimeoutTimer_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */

  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Task_LED */
  Task_LEDHandle = osThreadNew(AppTask_LED, NULL, &Task_LED_attributes);

  /* creation of Task_AHT20 */
  Task_AHT20Handle = osThreadNew(AppTask_AHT20, NULL, &Task_AHT20_attributes);

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

  for(;;)
  {
    TK_vAHT20_Measure();
  }
  /* USER CODE END AppTask_AHT20 */
}

/* TK_LEDInitCallback function */
void TK_LEDInitCallback(void *argument)
{
  /* USER CODE BEGIN TK_LEDInitCallback */

  /* USER CODE END TK_LEDInitCallback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

