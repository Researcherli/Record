#include "gd32f4xx_it.h"
#include "systick.h"
#include "FreeRTOS.h"

extern void xPortSysTickHandler( void );


void NMI_Handler(void)
{
    while(1) {
    }
}

void HardFault_Handler(void)
{
    while(1) {
    }
}

void MemManage_Handler(void)
{
    while(1) {
    }
}

void BusFault_Handler(void)
{
    while(1) {
    }
}

void UsageFault_Handler(void)
{
    while(1) {
    }
}

//void SVC_Handler(void)
//{
//    while(1) {
//    }
//}

void DebugMon_Handler(void)
{
    while(1) {
    }
}

//void PendSV_Handler(void)
//{
//    while(1) {
//    }
//}

void SysTick_Handler(void)
{
	#if (INCLUDE_xTaskGetSchedulerState  == 1 )
		if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
		{
	#endif   
			xPortSysTickHandler();
	#if (INCLUDE_xTaskGetSchedulerState  == 1 )
		}
	#endif  
}
