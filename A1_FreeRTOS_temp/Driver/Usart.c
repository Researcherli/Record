#include "gd32f4xx.h"
#include <stdio.h>
#include <string.h>

// 宏定义USART0参数
#define DEBUG_USART_PERIPH      USART0
#define DEBUG_USART_BAUDRATE    115200U
#define DEBUG_USART_TX_PORT     GPIOA
#define DEBUG_USART_TX_PIN      GPIO_PIN_9
#define DEBUG_USART_RX_PORT     GPIOA
#define DEBUG_USART_RX_PIN      GPIO_PIN_10

// 私有函数声明
static void usart_gpio_init(void);
static void usart_config(void);

// 初始化USART
void Usart_Init(void)
{
    usart_gpio_init();
    usart_config();
}

// GPIO初始化
static void usart_gpio_init(void)
{
    // 使能时钟
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_USART0);

    // 配置USART0 TX (PA9) 和 RX (PA10) 的复用功能
    gpio_af_set(GPIOA, GPIO_AF_7, DEBUG_USART_TX_PIN | DEBUG_USART_RX_PIN);

    // TX引脚配置：复用推挽输出，50MHz
    gpio_mode_set(DEBUG_USART_TX_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, DEBUG_USART_TX_PIN);
    gpio_output_options_set(DEBUG_USART_TX_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, DEBUG_USART_TX_PIN);

    // RX引脚配置：复用输入，上拉
    gpio_mode_set(DEBUG_USART_RX_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, DEBUG_USART_RX_PIN);
}

// USART配置
static void usart_config()
{
    usart_deinit(DEBUG_USART_PERIPH);
    usart_baudrate_set(DEBUG_USART_PERIPH, DEBUG_USART_BAUDRATE);
    usart_receive_config(DEBUG_USART_PERIPH, USART_RECEIVE_ENABLE);
    usart_transmit_config(DEBUG_USART_PERIPH, USART_TRANSMIT_ENABLE);
    usart_enable(DEBUG_USART_PERIPH);
}

// 发送单个字节
void Drv_usart0_SendByte(uint8_t ch)
{
    usart_data_transmit(DEBUG_USART_PERIPH, ch);
    // 确保发送数据寄存器空闲
    while (!usart_flag_get(DEBUG_USART_PERIPH, USART_FLAG_TBE));
}

// 重定向fputc
int fputc(int ch, FILE* f)
{
    // 兼容回车换行
    if (ch == '\n') {
        Drv_usart0_SendByte('\r');
    }
    Drv_usart0_SendByte((uint8_t)ch);
    return ch;
}

