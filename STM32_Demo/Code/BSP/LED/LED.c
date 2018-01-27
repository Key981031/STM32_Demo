#include "stm32f4xx.h"
#include "sys.h"
#include "LED.h"

#define LED1_ON  PDout(8) = 0;
#define LED1_OFF PDout(8) = 1;

#define LED2_ON  PBout(15) = 0;
#define LED2_OFF PBout(15) = 1;

#define LED3_ON  PBout(14) = 0;
#define LED3_OFF PBout(14) = 1;

#define LED4_ON  PDout(9) = 0;
#define LED4_OFF PDout(9) = 1;

#define LED5_ON  PDout(10) = 0;
#define LED5_OFF PDout(10) = 1;

#define LED6_ON  PDout(11) = 0;
#define LED6_OFF PDout(11) = 1;

/**********************************************
* 初始化LED
**********************************************/
void LED_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    GPIO_Init(GPIOD, &GPIO_InitStructure);  //初始化GPIO

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**********************************************
* 开灯
**********************************************/
void LED_ON(enum LED_Num led)
{
    switch (led)
    {
    case LED_1:LED1_ON; break;
    case LED_2:LED2_ON; break;
    case LED_3:LED3_ON; break;
    case LED_4:LED4_ON; break;
    case LED_5:LED5_ON; break;
    case LED_6:LED6_ON; break;
    default:
        break;
    }
}

/**********************************************
* 关灯
**********************************************/
void LED_OFF(enum LED_Num led)
{
    switch (led)
    {
    case LED_1:LED1_OFF; break;
    case LED_2:LED2_OFF; break;
    case LED_3:LED3_OFF; break;
    case LED_4:LED4_OFF; break;
    case LED_5:LED5_OFF; break;
    case LED_6:LED6_OFF; break;
    default:
        break;
    }
}

/**********************************************
* 开启全部LED
**********************************************/
void LED_ALL_ON(void)
{
    LED1_ON;
    LED2_ON;
    LED3_ON;
    LED4_ON;
    LED5_ON;
    LED6_ON;
}

/**********************************************
* 关闭全部LED
**********************************************/
void LED_ALL_OFF(void)
{
    LED1_OFF;
    LED2_OFF;
    LED3_OFF;
    LED4_OFF;
    LED5_OFF;
    LED6_OFF;
}
