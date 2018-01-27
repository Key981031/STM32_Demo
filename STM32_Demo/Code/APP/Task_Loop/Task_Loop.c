#include "stm32f4xx.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "Task_Loop.h"
#include "APP\ANO_DT\ANO_DT.h"
#include "BSP\Time\Time.h"
#include "BSP\Motor_Drive\Moto_Drive.h"
#include "APP\Display\Display.h"
#include "BSP\MPU6050\MPU6050.h"
#include "APP\IMU\IMU.h"
#include "BSP\AK8975\AK8975.h"
#include "BSP\Encoder\Encoder.h"
#include "BSP\KEY\KEY.h"

/* 任务循环计时结构体 */
typedef struct {
    uint8_t check_flag;
    uint8_t err_flag;
    uint8_t cnt_1ms;
    uint8_t cnt_2ms;
    uint8_t cnt_5ms;
    uint8_t cnt_10ms;
    uint8_t cnt_20ms;
    uint8_t cnt_50ms;
}Loop_Time_TypeDef;

static Loop_Time_TypeDef Loop_Time;    //任务循环计时

__INLINE static void Task_1ms(void);
__INLINE static void Task_2ms(void);
__INLINE static void Task_5ms(void);
__INLINE static void Task_10ms(void);
__INLINE static void Task_20ms(void);
__INLINE static void Task_50ms(void);


/**********************************************
* 清空循环计数标志
**********************************************/
void Loop_Time_Clear(void)
{
    memset(&Loop_Time, 0, sizeof(Loop_Time_TypeDef));
}

/**********************************************
* 任务循环
* 由主函数初始化完成后调用
**********************************************/
void Task_Loop(void)
{
    if (Loop_Time.check_flag >= 1)
    {
        Task_1ms();                     //周期1ms的任务
        if (Loop_Time.cnt_2ms >= 2)
        {
            Loop_Time.cnt_2ms = 0;
            Task_2ms();	                //周期2ms的任务
        }
        if (Loop_Time.cnt_5ms >= 5)
        {
            Loop_Time.cnt_5ms = 0;
            Task_5ms();                 //周期5ms的任务
        }
        if (Loop_Time.cnt_10ms >= 10)
        {
            Loop_Time.cnt_10ms = 0;
            Task_10ms();                //周期10ms的任务
        }
        if (Loop_Time.cnt_20ms >= 20)
        {
            Loop_Time.cnt_20ms = 0;
            Task_20ms();                //周期20ms的任务
        }
        if (Loop_Time.cnt_50ms >= 50)
        {
            Loop_Time.cnt_50ms = 0;
            Task_50ms();                //周期50ms的任务
        }

        Loop_Time.check_flag = 0;       //循环运行完毕标志
    }
}

float test[5];

/**********************************************
* 1ms任务
**********************************************/
__INLINE static void Task_1ms(void)
{

}

/**********************************************
* 2ms任务
**********************************************/
__INLINE static void Task_2ms(void)
{
    float inner_loop_time;

    inner_loop_time = Get_Cycle_T(0);               //获取内环准确的执行周期

    test[0] = GetSysTime_us() / 1000000.0f;

    MPU6050_Read();                                 //读取mpu6轴传感器

    MPU6050_Data_Prepare(inner_loop_time);          //mpu6轴传感器数据处理

    test[1] = GetSysTime_us() / 1000000.0f;
}

/**********************************************
* 5ms任务
**********************************************/
__INLINE static void Task_5ms(void)
{
    float outer_loop_time;

    outer_loop_time = Get_Cycle_T(2);			//获取外环准确的执行周期

    //test[2] = (float)GetSysTime_us() / 1000000.0f;
    int32_t t1 = 0;
    int32_t t2 = 0;
    t1 = GetSysTime_us();

    /*IMU更新姿态。输入：半个执行周期，三轴陀螺仪数据（转换到度每秒），三轴加速度计数据（4096--1G）；输出：ROLPITYAW姿态角*/
    IMUupdate(
        0.5f *outer_loop_time, 
        mpu6050.Gyro_deg.x, 
        mpu6050.Gyro_deg.y, 
        mpu6050.Gyro_deg.z, 
        mpu6050.Acc.x, 
        mpu6050.Acc.y,
        mpu6050.Acc.z, 
        &Roll, &Pitch, &Yaw);

    //test[3] = (float)GetSysTime_us() / 1000000.0f;
    t2 = GetSysTime_us();

    printf("%d\r\n", (t2 - t1));
}

/**********************************************
* 10ms任务
**********************************************/
__INLINE static void Task_10ms(void)
{
    ANO_AK8975_Read();      // 读取磁力计
}

/**********************************************
* 20ms任务
**********************************************/
__INLINE static void Task_20ms(void)
{
    int32_t Encoder_2 = 0;
    int32_t Encoder_5 = 0;
    Encoder_2 = Read_Encoder(2);
    Encoder_5 = Read_Encoder(5);
    //ANO_DT_Send_Senser(Encoder_2, Encoder_5, 0, 0, 0, 0, 0, 0, 0, 0);

    /* 发送传感器参数到上位机 */
    //ANO_DT_Send_Senser(
    //    mpu6050.Acc.x, mpu6050.Acc.y, mpu6050.Acc.z,
    //    mpu6050.Gyro_deg.x, mpu6050.Gyro_deg.y, mpu6050.Gyro_deg.z,
    //    ak8975.Mag_Val.x, ak8975.Mag_Val.y, ak8975.Mag_Val.z, 0);

    //ANO_DT_Send_Status(Roll, Pitch, Yaw, 0, 0, 1);

    /* 执行上位机指令 */
    ANO_DT_Do();
}

/**********************************************
* 50ms任务
**********************************************/
__INLINE static void Task_50ms(void)
{   
    switch (KEY_Scan())
    {
    case 1:  break;
    case 2:  break;
    case 3:  break;
    case 4:  break;
    case 5:  break;
    case 6:  break;
    default:      break;
    }
    //Display_Time();
}

/**********************************************
* 任务循环计时
* 由1ms定时中断调用
**********************************************/
void Loop_Time_Check(void)
{
    Loop_Time.cnt_2ms++;
    Loop_Time.cnt_5ms++;
    Loop_Time.cnt_10ms++;
    Loop_Time.cnt_20ms++;
    Loop_Time.cnt_50ms++;

    if (Loop_Time.check_flag >= 2)
    {
        Loop_Time.err_flag++;     //每累加一次，证明代码在预定周期2ms内没有跑完。
    }
    else
    {
        Loop_Time.check_flag += 1;	//该标志位在循环的最后被清零
    }
}
