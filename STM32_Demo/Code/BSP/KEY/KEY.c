#include "stm32f4xx.h"
#include "sys.h"
#include "KEY.h"
#include "delay.h"

#define KEY1 PEin(3)
#define KEY2 PEin(4)
#define KEY3 PCin(13)
#define KEY4 PCin(6)
#define KEY5 PBin(12)
#define KEY6 PBin(13)

/**********************************************
* 初始化按键输入
**********************************************/
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_13;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，WKUP按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>WK_UP!!
uint8_t KEY_Scan(void)
{
    //static uint8_t key_count = 0;
    static u8 key_up = 1;   //按键松开标志
    if (key_up && (KEY1 == 0 || KEY2 == 0 || KEY3 == 0 || KEY4 == 0 || KEY5 == 0 || KEY6 == 0)) //有按键按下
    {
        key_up = 0;
        if (KEY1 == 0) return 1;
        else if (KEY2 == 0) return 2;
        else if (KEY3 == 0) return 3;
        else if (KEY4 == 0) return 4;
        else if (KEY5 == 0) return 5;
        else if (KEY6 == 0) return 6;
    }
    else if (KEY1 == 1 && KEY2 == 1 && KEY3 == 1 && KEY4 == 1 && KEY5 == 1 && KEY6 == 1)
    {
        key_up = 1;
    }

    return 0; //无按键按下
}
