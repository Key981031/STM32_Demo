//-----------------------------------------------------------------------------
// My_Flag.h
//
//  Created on	: 2016-10-7
//      Author	: DGVY
//		version	: V2.0
//		brief	: 状态标志位
//-----------------------------------------------------------------------------
// Attention:
//      所有的状态标识变量都用此文件定义

//-----------------------------------------------------------------------------
// Define to prevent recursive inclusion
//-----------------------------------------------------------------------------
#ifndef __MY_FLAG_H
#define __MY_FLAG_H
	

//-----------------------------------------------------------------------------
// 二元状态标志
//-----------------------------------------------------------------------------
typedef enum
{
    MY_TRUE = 1,
    MY_FALSE = 0
}eBoolTypedef;

#define Flag eBoolTypedef

// 重定义
#define Ready       MY_TRUE   
#define Not_Ready   MY_FALSE

#define eConnectStatues eBoolTypedef
#define No_Connect  MY_FALSE
#define Connected   MY_TRUE

#define Laser_ON MY_TRUE
#define Laser_OFF MY_FALSE

//#define DEBUG_PRINTF         //串口打印

//-----------------------------------------------------------------------------
// 多元状态标志
//-----------------------------------------------------------------------------
typedef enum
{
    State_1,
    State_2,
    State_3
    //可自行添加
}MultiState;

// 重定义



//-----------------------------------------------------------------------------
// Extern
//-----------------------------------------------------------------------------


#endif /* __MY_FLAG_H */
/******************* (C) COPYRIGHT 2016 DGVY **********END OF FILE***********/