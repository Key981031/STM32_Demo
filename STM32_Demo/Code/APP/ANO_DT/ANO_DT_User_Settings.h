/*
 * ANO_DT_User_Settings.h
 *
 *  Created on: 2016骞�11鏈�25鏃�
 *      Author: DGVY
 */

#ifndef __ANO_DT_USER_SETTINGS_H_
#define __ANO_DT_USER_SETTINGS_H_


/************************************************************************/
// 模块内部头文件，外部不要引用
/************************************************************************/

#include "BSP\MPU6050\MPU6050.h"

/**************用于修改地面站的各种设定，由用户指定********************/

// -----用到的UART口-----
// USART1 -- 1
// USART2 -- 2
// USART3 -- 3
// USART4 -- 4
#define ANO_DT_UART_PORT_SELECT 1

// -----指定各按钮事件-----
//加速度计校准按钮
#define ANO_DT_ACCELEROMETER_ADJUSTING()	MPU6050_GYRO_Calibrate();

//陀螺仪校准按钮
#define ANO_DT_GYRO_CALIBRATED()			MPU6050_ACC_Calibrate();

//6面校准
#define ANO_DT_3D_CALIBRATED()              {MPU6050_ACC_Calibrate(),MPU6050_GYRO_Calibrate();}

//罗盘校准按钮
#define ANO_DT_COMPASS_CALIBRATED()			printf("compass_adj\r\n");

//气压计校准按钮
#define ANO_DT_BAROMETER_CALIBRATED()		printf("barometer_adj\r\n");


// -----全部数据写入单片机成功指示-----
#define ANO_DT_DATA_RECEIVE_WRITE_SUCCEED() \
        printf("\r\nPID_Data_Upate is successful!!\r\n");


// 参数放大比例，单片机内的参数将乘以此数，再存入FLASH或发送到上位机
#define ANO_DT_PARAMETER_SCALING   1

// 单片机内部参数类型
#define ANO_DT_PARAMETER_TYPE (double)

// 单片机内部数据存储地址，默认为FLASH的第八扇区
#define ANO_DT_PID_DATA_SAVE_FLASH_ADDRESS ADDR_FLASH_SECTOR_10


// -----要调节的数据，以下数据与匿名地面站"飞控参数"一栏一一对应----
//#define USE_PID_01
//#define USE_PID_02
//#define USE_PID_03
//#define USE_PID_04
//#define USE_PID_05
//#define USE_PID_06
//#define USE_PID_07
//#define USE_PID_08
//#define USE_PID_09
//#define USE_PID_10
//#define USE_PID_11
//#define USE_PID_12
//#define USE_PID_13
//#define USE_PID_14
//#define USE_PID_15
//#define USE_PID_16
//#define USE_PID_17
//#define USE_PID_18


#if defined(USE_PID_01)
#define PID_01_P    G_PID_Parameter.PID_Angle.Parameter.P
#define PID_01_I    G_PID_Parameter.PID_Angle.Parameter.I
#define PID_01_D    G_PID_Parameter.PID_Angle.Parameter.D
#endif

#if defined(USE_PID_02)
#define PID_02_P    G_PID_Parameter.PID_Angle.Parameter.Out_Max
#define PID_02_I    G_PID_Parameter.PID_Angle.Parameter.Out_Min
#define PID_02_D    G_PID_Parameter.PID_Angle.Parameter.Iteg_Max
#endif

#if defined(USE_PID_03)
#define PID_03_P    G_PID_Parameter.PID_LineX.Parameter.P
#define PID_03_I    G_PID_Parameter.PID_LineX.Parameter.I
#define PID_03_D    G_PID_Parameter.PID_LineX.Parameter.D
#endif

#if defined(USE_PID_04)
#define PID_04_P    G_PID_Parameter.PID_LineX.Parameter.Out_Max
#define PID_04_I    G_PID_Parameter.PID_LineX.Parameter.Out_Min
#define PID_04_D    G_PID_Parameter.PID_LineX.Parameter.Iteg_Max
#endif

#if defined(USE_PID_05)
#define PID_05_P    G_PID_Parameter.PID_LineY.Parameter.P
#define PID_05_I    G_PID_Parameter.PID_LineY.Parameter.I
#define PID_05_D    G_PID_Parameter.PID_LineY.Parameter.D
#endif

#if defined(USE_PID_06)
#define PID_06_P    G_PID_Parameter.PID_LineY.Parameter.Out_Max
#define PID_06_I    G_PID_Parameter.PID_LineY.Parameter.Out_Min
#define PID_06_D    G_PID_Parameter.PID_LineY.Parameter.Iteg_Max
#endif

#if defined(USE_PID_07)
#define PID_07_P    forwardParam[0]
#define PID_07_I    forwardParam[1]
#define PID_07_D    forwardParam[2]
#endif

#if defined(USE_PID_08)
#define PID_08_P    forwardParam[3]
#define PID_08_I    forwardParam[4]
#define PID_08_D    forwardParam[5]
#endif

#if defined(USE_PID_09)
#define PID_09_P    g_Speed[0]
#define PID_09_I    g_Speed[2]
#define PID_09_D    g_Speed[3]
#endif

#if defined(USE_PID_10)
#define PID_10_P    g_Speed[3]
#define PID_10_I    0
#define PID_10_D    0
#endif

#if defined(USE_PID_11)
#define PID_11_P    0
#define PID_11_I    0
#define PID_11_D    0
#endif

#if defined(USE_PID_12)
#define PID_12_P    0
#define PID_12_I    0
#define PID_12_D    0
#endif

#if defined(USE_PID_13)
#define PID_13_P    0
#define PID_13_I    0
#define PID_13_D    0
#endif

#if defined(USE_PID_14)
#define PID_14_P    0
#define PID_14_I    0
#define PID_14_D    0
#endif

#if defined(USE_PID_15)
#define PID_15_P    0
#define PID_15_I    0
#define PID_15_D    0
#endif

#if defined(USE_PID_16)
#define PID_16_P    0
#define PID_16_I    0
#define PID_16_D    0
#endif

#if defined(USE_PID_17)
#define PID_17_P    0
#define PID_17_I    0
#define PID_17_D    0
#endif

#if defined(USE_PID_18)
#define PID_18_P    0
#define PID_18_I    0
#define PID_18_D    0
#endif

#endif /* ANO_DT_ANO_DT_USER_SETTINGS_H_ */
