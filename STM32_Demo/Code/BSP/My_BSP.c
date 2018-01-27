//-----------------------------------------------------------------------------
// MY_BSP.c
//
//  Created on	: 2016-7-14
//      Author	: DGVY
//		version	: V1.0
//		brief	:
//-----------------------------------------------------------------------------
// Attention:
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "My_BSP.h"
#include "Printf_Uart.h"
#include "delay.h"
#include "sys.h"
#include "BSP\LED\LED.h"
#include "BSP\MCU\Timer\Timer.h"
#include "BSP\Time\Time.h"
#include "BSP\MCU\SysTick\SysTick.h"
#include "BSP\Motor_Drive\Moto_Drive.h"
#include "BSP\OLED\OLED.h"
#include "BSP\MCU\IIC_Soft\IIC_Soft.h"
#include "BSP\MPU6050\MPU6050.h"
#include "BSP\Encoder\Encoder.h"
#include "BSP\BEEP\BEEP.h"
#include "BSP\KEY\KEY.h"

//-----------------------------------------------------------------------------
// Private Define
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Private Function Prototypes
//-----------------------------------------------------------------------------

//===============================================================================


//-----------------------------------------------------------------------------
// Extern Function
// 外部函数
//-----------------------------------------------------------------------------

/*****************************************************************************\
* Function Name   : Init
* Input           : uint32_t uart_bound     [初始化UART波特率]
*                   uint8_t  delay_sysclk   [系统时钟频率]
* Output          : None
* Return          : None
* Description     : 板级初始化，初始化硬件
*                   默认uart波特率为115200
*                   默认系统时钟为168MHz
\*****************************************************************************/
void BSP_Init(uint32_t uart_bound,uint8_t delay_sysclk)
{
    /* 设置系统中断优先级分组2 */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* 初始化Uart1 用于printf函数 */
    uart_printf_init(uart_bound);

    /* 清空系统时间 */
    System_Tiem_Clear();

    /* 初始化滴答定时器 */
    SysTick_Init();

    /* LED初始化 */
    LED_Init();
    LED_ALL_ON();

    /* 蜂鸣器初始化 */
    BEEP_Init();
    BEEP_ON();

    /* IIC初始化 */
    I2c_Soft_Init();
    delay_ms(100);

    /* 加速度计、陀螺仪初始化，配置20hz低通 */
    MPU6050_Init(20);   			

    /* OLED初始化 */
    OLED_Init();

    /* 编码器初始化 */
    Encoder_Init_TIM5();
    Encoder_Init_TIM2();

    /* 按键初始化 */
    KEY_Init();

    delay_ms(1000);
    BEEP_OFF();
    LED_ALL_OFF();
}


/******************* (C) COPYRIGHT 2016 DGVY **********END OF FILE***********/
