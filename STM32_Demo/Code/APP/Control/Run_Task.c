//-----------------------------------------------------------------------------
// Run_Task.c
//
//  Created on	: 2017-1-8
//      Author	: DGVY
//		version	: V1.0
//		brief	:
//-----------------------------------------------------------------------------
// Attention:
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "includes.h"
#include "sys_include.h"
#include "PID_Control.h"
#include "PID_forward.h"
#include "PID_Parameter.h"
#include "Route_Control.h"
#include <stdio.h>
#include "Robot.h"
#include "Task_Setting.h"
#include "Basal_Move.h"
#include "uart4.h"
#include "Laser_Ranging.h"

//-----------------------------------------------------------------------------
// Private Typedef
//-----------------------------------------------------------------------------

extern forward_ctl_t RouteToSet;

//-----------------------------------------------------------------------------
// Private Macro
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Private Variables
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Private Function Prototypes
//-----------------------------------------------------------------------------

//===============================================================================

//-----------------------------------------------------------------------------
// Extern Function
// 外部函数
//-----------------------------------------------------------------------------

#include "GYRO_Lib.h"
// 锁定点任务
extern int32_t lock_type;
extern Flag Protect_Angle;
extern Flag Protect_X;
extern Flag Protect_Y;
extern int32_t Junction_x[][9];
extern int32_t Junction_y[][9];
void Locak_Point_Task(void *p_arg)
{
	OS_ERR err;
	err = err;
	p_arg = p_arg;

	/*角度保护*/
	int i = 0;
	PID_Set_Angle_Value(0);
	while (1)
	{
		PID_Angle_Loop_Test();
		SetMotorSpeed();
		if (my_abs(nloc.Angle) <= 1.5f)
		{
			i++;
		}
		else
		{
#if defined(DEBUG_PRINTF)
			printf("angle: %f\r\n", nloc.Angle);
			i = 0;
#endif
		}
		if (i >= 90)    //激光测距仪读值需要时间
		{
			Protect_Angle = MY_FALSE;
			break;
		}

		delay_ms(10);
	}

	/*Y保护*/
	if (Protect_Y == MY_TRUE)
	{
		/*设置锁定装盘区*/
		PID_Set_Angle_Value(0);
		PID_Set_LineX_Value(Junction_x[G_Robot_Master.Ground_Set - 1][8]);
		PID_Set_LineY_Value(Junction_y[G_Robot_Master.Ground_Set - 1][8]);

		while (1)
		{
			PID_Angle_Loop_Test();
			PID_LineX_Loop_Test();
			PID_LineY_Loop_Test();
			SetMotorSpeed();
			delay_ms(10);

			if (my_abs(nloc.Coords.y - Junction_y[G_Robot_Master.Ground_Set - 1][8]) < 5)
			{
				Protect_Y = MY_FALSE;
				break;
			}
		}
	}

	/*X保护*/
	if (Protect_X == MY_TRUE)
	{
		PID_Set_Angle_Value(0);
		PID_Set_LineX_Value(0);
		PID_Set_LineY_Value(nloc.Coords.y);

		while (1)
		{
			PID_Angle_Loop_Test();
			PID_LineX_Loop_Test();
			PID_LineY_Loop_Test();
			SetMotorSpeed();
			delay_ms(10);

			if (my_abs(nloc.Coords.x) < 5)
			{
				Protect_X = MY_FALSE;
				break;
			}
		}
	}

	/*用激光更新码盘当前坐标*/
	nloc.Coords.x = (int32_t)(Laser_Ranging_Get_Distance() - Laser_Ranging_Fisrst_Distance);
	printf("Laser:  %d\r\n", nloc.Coords.x);
	GYRO_Set_Position_X(nloc.Coords.x);

#if defined(DEBUG_PRINTF)
	printf("===================================\r\n");
	printf("nloc: %d\r\n", nloc.Coords.x);
#endif

	switch (lock_type)
	{
	case 1:         //锁定在当前点
#if defined(DEBUG_PRINTF)
		printf("& Lock_Nloc\r\n");
#endif
		PID_Set_Angle_Value(0);             //设定锁定角度
		PID_Set_LineX_Value(nloc.Coords.x);    //设定锁定坐标x
		PID_Set_LineY_Value(nloc.Coords.y);    //设定锁定坐标y
		break;
	case 2:         //锁定在交叉点
#if defined(DEBUG_PRINTF)
		printf("& Lock_Junction\r\n");
#endif
		PID_Set_Angle_Value(0);                     //设定锁定角度
		PID_Set_LineX_Value(jun_pos.Coords.x);    //设定锁定坐标x
		PID_Set_LineY_Value(jun_pos.Coords.y);    //设定锁定坐标y
		break;
	default:
#if defined(DEBUG_PRINTF)
		printf("& Lock_Junction\r\n");
#endif
		PID_Set_Angle_Value(0);                     //设定锁定角度
		PID_Set_LineX_Value(nloc.Coords.x);    //设定锁定坐标x
		PID_Set_LineY_Value(nloc.Coords.y);    //设定锁定坐标y
	}
	while (1)
	{
		PID_Angle_Loop_Test();
		PID_LineX_Loop_Test();
		PID_LineY_Loop_Test();
		SetMotorSpeed();

		delay_ms(10);
	}
}

/*直线调节任务*/
int32_t G_Line_Adj_Direction;
extern int32_t velocity;
void Line_Adjust_Task(void *p_arg)
{
	OS_ERR err;
	err = err;
	p_arg = p_arg;

	int32_t vect_x, vect_y;
	int32_t tempx = nloc.Coords.x, tempy = nloc.Coords.y;
	switch (G_Line_Adj_Direction)
	{
	case 0:             //y+
        vect_x =  0; 
        vect_y =  1;
        PID_Set_LineX_Value(tempx);    //设定锁定坐标x
        break;        
	case 1:             //y-
        vect_x =  0; 
        vect_y = -1;
        PID_Set_LineX_Value(tempx);    //设定锁定坐标x
        break;        
	case 2:             //x+
        vect_x =  1; 
        vect_y =  0;
        PID_Set_LineY_Value(tempy);    //设定锁定坐标y
        break;        
	case 3:             //x-
        vect_x = -1; 
        vect_y =  0;
        PID_Set_LineY_Value(tempy);    //设定锁定坐标y
        break;        
	default:    
        vect_x = vect_y =  0; 
        break;
	}

    PID_Set_Angle_Value(0);             //设定锁定角度

    while (1)
    {
        linear_speed(vect_x, vect_y, nloc.Angle, velocity);
        PID_Angle_Loop_Test();
        switch (G_Line_Adj_Direction)
        {
        case 0:
        case 1:
            PID_LineX_Loop_Test();
            break;
        case 2:
        case 3:
            PID_LineY_Loop_Test();
            break;
        default:
            break;
        }
		SetMotorSpeed();
		delay_ms(10);
	}
}

/*前往交叉点任务*/
extern int32_t Junction_x[][9];    //交叉点坐标
extern int32_t Junction_y[][9];    //交叉点坐标
int32_t Junction_Key;    //前往交叉点按键
extern int32_t location_offset_x;
extern int32_t location_offset_y;
void Runto_Junction_Task(void* p_arg)
{
	OS_ERR err;
	err = err;
	p_arg = p_arg;

	while (G_Robot_Master.State == Pause)
	{
		delay_ms(50);
	}

	if ((G_Robot_Master.Ground_Set == Ground_Blue) || (G_Robot_Master.Ground_Set == Ground_Red))
	{
		jun_pos.Coords.x = Junction_x[(G_Robot_Master.Ground_Set - 1)][(Junction_Key - 1)];
		jun_pos.Coords.y = Junction_y[(G_Robot_Master.Ground_Set - 1)][(Junction_Key - 1)];

        // 加偏移量
        if ((Junction_Key != 1) && (Junction_Key != 5) && (Junction_Key != 9))
        {
            jun_pos.Coords.x += location_offset_x;
            jun_pos.Coords.y += location_offset_y;

            // 防止位置设置超量程
            //y
            if (my_abs(jun_pos.Coords.y) < 1540)
            {
                if (G_Robot_Master.Ground_Set == Ground_Red)
                {
                    jun_pos.Coords.y = 1540;
                }
                else
                {
                    jun_pos.Coords.y = -1540;
                }
            }
            else if (my_abs(jun_pos.Coords.y) > 13600)
            {
                if (G_Robot_Master.Ground_Set == Ground_Red)
                {
                    jun_pos.Coords.y = 13600;
                }
                else
                {
                    jun_pos.Coords.y = -13600;
                }
            }
            //x
            if (jun_pos.Coords.x > 260)
            {
                jun_pos.Coords.x = 260;
            }
            else if (jun_pos.Coords.x < -250)
            {
                jun_pos.Coords.x = -250;
            }
        }
        else if (Junction_Key == 5)
        {
            jun_pos.Coords.y += location_offset_y;
        }


	}
	else //(G_Robot_Master.Ground_Set == No_Set)
	{
		jun_pos.Coords.x = nloc.Coords.x;
		jun_pos.Coords.y = nloc.Coords.y;
	}
	PID_Set_Angle_Value(0);    //设定目标角度
	PID_Set_LineX_Value(0);    //设定目标坐标x
	setup_Yline(jun_pos.Coords.y);   //设定目标坐标y

	while (1)
	{
		PID_Angle_Loop_Test();    //PID角度环控制
		PID_LineX_Loop_Test();    //PID直线X控制
		control_Yline();          //前馈式Y直线控制
		SetMotorSpeed();

		OS_ERR  p_err;
		if (GetCurTimeMS(&p_err) >= RouteToSet.end_time)
		{
			Robot_Stop();
		}

		delay_ms(10);             //调节时间
	}

}
/*****************************************************************************/

// 更新位置信息任务
void Robot_Location_Update_Task(void *p_arg)
{
	OS_ERR err;
	err = err;
	p_arg = p_arg;

	//static int i = 0;
#if defined(DEBUG_PRINTF)
	printf("\r\n@ Robot_Location_Update_Task\r\n");
#endif
    while (1)
    {
        Robot_Location_Update();
        Robot_Speed_Upadte();

		//i++;
		//if (i >= 30)
		//{
		//	//OSSchedLock(&err);
		//	Robot_Send_Location_to_Remote();
		//	//OSSchedUnlock(&err);
		//	i = 0;
		//}
		delay_ms(5);   //每5ms更新一次
	}
}



/******************* (C) COPYRIGHT 2016 DGVY ***********END OF FILE***********/
