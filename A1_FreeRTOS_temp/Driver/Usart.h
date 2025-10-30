#ifndef __USART_H
#define __USART_H

#include "gd32f4xx.h"
#include <stdint.h>
#include <stdio.h>


// 函数声明
void Usart_Init(void);

void Drv_usart0_SendByte(uint8_t ch);

void Drv_usart0_SendString(const char *str);

#endif
