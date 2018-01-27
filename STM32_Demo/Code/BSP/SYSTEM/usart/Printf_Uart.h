#ifndef __USART_H
#define __USART_H

#ifdef __cplusplus  
extern "C" {
#endif  

#include <stdio.h>
#include "stm32f4xx_conf.h"
#include "sys.h" 
#include "My_Flag.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.csom
//修改日期:2011/6/14
//版本：V1.4
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
//********************************************************************************
//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
//********************************************************************************
//V1.4修改说明
//1,修改串口初始化IO的bug
//2,修改了USART_RX_STA,使得串口最大接收字节数为2的14次方
//3,增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//4,修改了EN_USART1_RX的使能方式
//********************************************************************************
//v1.4修改说明
//可通过宏定义选择printf的端口，目前支持UART1与UART2
//不知道为何，UART2不能用，希望有人可以解决
//////////////////////////////////////////////////////////////////////////////////

#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USARTx_RX 			1		//使能（1）/禁止（0）串口1接收

//通过宏定义选择printf函数的通信端口
#define USE_UART1_PRINTF
//#define USE_UART2_PRINTF

#if defined (USE_UART1_PRINTF)
#define PRINTF_BUS USART1
#elif defined (USE_UART2_PRINTF)
#define PRINTF_BUS USART2
#error "UART2 can not used! I can't fix this BUG! "
#else
#error "Please choose PRINTF_BUS!"
#endif

	  	
extern vu8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
//extern vu16 USART_RX_STA;         		//接收状态标记

extern Flag Flag_UART_RX;   //接收完成标志位

void uart_printf_init(u32 bound);
void u1_putchar(u8 ch);
void u1_putbuff(u8 *buff, u32 len);

#ifdef __cplusplus  
}
#endif  

#endif


