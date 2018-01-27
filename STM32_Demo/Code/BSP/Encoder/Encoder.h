#ifndef __ENCODER_H
#define __ENCODER_H

#include <stdint.h>

#define ENCODER_BASE_COUNT 0x7FFFFFFF

#define ENCODER_TIM_PERIOD (u16)(0x7FFFFFFF)
void Encoder_Init_TIM5(void);
void Encoder_Init_TIM2(void);
int32_t Read_Encoder(uint8_t TIMX);

#endif
