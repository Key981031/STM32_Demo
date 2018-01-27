#include "stm32f4xx.h"
#include "sys.h"

/**********************************************
* 初始化蜂鸣器
**********************************************/
void BEEP_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOF时钟

    //GPIOF9,F10初始化设置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//LED0和LED1对应IO口
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIO

}

/**********************************************
* 蜂鸣器开
**********************************************/
void BEEP_ON(void)
{
    PEout(2) = 1;
}

/**********************************************
* 蜂鸣器关
**********************************************/
void BEEP_OFF(void)
{
    PEout(2) = 0;
}
