#include "gd32f4xx.h"
#include "systick.h"

#define  DWT_CYCCNT             *(volatile unsigned int *)0xE0001004
#define  DWT_CR                 *(volatile unsigned int *)0xE0001000
#define  DEM_CR                 *(volatile unsigned int *)0xE000EDFC
#define  DEM_CR_TRCENA          (1 << 24)
#define  DWT_CR_CYCCNTENA       (1 <<  0)

volatile uint32_t SysTickMs;

static void delay_timer_init(void)
{
    DEM_CR |= (uint32_t)DEM_CR_TRCENA;
    DWT_CYCCNT = 0;
    DWT_CR |= (uint32_t)DWT_CR_CYCCNTENA;
}

void systick_init(void)
{
    /* setup systick timer for 1000Hz interrupts */
    if (SysTick_Config(SystemCoreClock / 1000U)) {
        /* capture error */
        while (1);
    }
    NVIC_SetPriority(SysTick_IRQn, 0x00U);
    nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);
    delay_timer_init();
}


void delay_increment(void)
{
    SysTickMs++;
}

uint32_t TaskDelay_GetTick(void)
{
    return SysTickMs;
}
