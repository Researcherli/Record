#include "gd32f4xx.h"
#include "FreeRTOS.h"
#include "systick.h"
#include "task.h"
#include "Usart.h"

void System_Init(void);
void RTOS_Init(void);

//【Debug任务】
//任务优先级
#define Debug_TASK_PRIO		(tskIDLE_PRIORITY + 2)
//任务堆栈大小	
#define Debug_STK_SIZE 		1024  
//任务句柄
TaskHandle_t Debug_Task_Handler;
//任务函数
void Debug_Task(void *pvParameters);

int main()
{
	System_Init();
	RTOS_Init();
}

void System_Init()
{
	Usart_Init();
}

/**********************************************************************************************************
* 函 数 名: RTOS_Init
* 功能说明: RTOS初始化，用于创建任务
* 形 参：无
* 返 回 值: 无
**********************************************************************************************************/
void RTOS_Init(void)
{
	taskENTER_CRITICAL();           //进入临界区
	//创建Debug任务
	xTaskCreate((TaskFunction_t )Debug_Task,     	
							(const char*    )"Debug_task",   	
							(uint16_t       )Debug_STK_SIZE, 
							(void*          )NULL,				
							(UBaseType_t    )Debug_TASK_PRIO,	
							(TaskHandle_t*  )&Debug_Task_Handler); 
							
	taskEXIT_CRITICAL();            //退出临界区	
	vTaskStartScheduler();          //开启任务调度
}

/**********************************************************************************************************
* 函 数 名: Debug_Task
* 功能说明: Debug任务
* 形  	参: 无
* 返 回 值: 无
**********************************************************************************************************/
void Debug_Task(void *pvParameters)
{
    while(1)
    {
      printf("Hello FreeRTOS\r\n");
      vTaskDelay(pdMS_TO_TICKS(500));
    }
} 


