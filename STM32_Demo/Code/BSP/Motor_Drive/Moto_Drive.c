#include "stm32f4xx.h"
#include "Moto_Drive.h"
#include "BSP\MCU\Timer\Timer.h"

void MOTO1_Init(void)
{
    TIM5_PWM_Init(100 - 1, 84 - 1);
    TIM4_Encoder_Init();
}

void MOTO1_Set(uint32_t pwm)
{
    Set_PWM_TIM5_CH1(pwm);
}

void MOTO2_Set(uint32_t pwm)
{
    Set_PWM_TIM5_CH2(pwm);
}

int32_t MOTO1_Get_Encoder(void)
{
    return Get_TIM4_Encoder();
}
