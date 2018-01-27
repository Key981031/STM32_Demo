#ifndef _MPU6050_H
#define _MPU6050_H

#include "stm32f4xx.h"
#include "APP\Sensor_Param\Sensor_Param.h"


#define GYRO_DEATH_ZOOM 20   //  20 / 65536

#define OFFSET_AV_NUM 50
#define FILTER_NUM 10

#define TO_ANGLE 				0.06103f 		//0.061036 //   4000/65536  +-2000   ???
#define ACC_ADJ_EN 									//�Ƿ�����У׼���ٶȼ�,(����������)


enum
{
    A_X = 0,
    A_Y,
    A_Z,
    G_Y,
    G_X,
    G_Z,
    TEM,
    ITEMS,
};


typedef struct
{
    char Acc_CALIBRATE;
    char Gyro_CALIBRATE;
    xyz_s16_t Acc_I16;
    xyz_s16_t Gyro_I16;

    xyz_f_t Acc;
    xyz_f_t Gyro;

    //	XYZ_STRUCT Acc_deg;
    xyz_f_t Gyro_deg;

    xyz_f_t Acc_Offset;
    xyz_f_t Gyro_Offset;
    xyz_f_t Gyro_Auto_Offset;
    float Temprea_Offset;
    float Gyro_Temprea_Adjust;
    float ACC_Temprea_Adjust;

    s16 Tempreature;
    float TEM_LPF;
    float Ftempreature;
}MPU6050_STRUCT;

extern MPU6050_STRUCT mpu6050;
extern float mpu6050_tmp[ITEMS];



void MPU6050_Init(u16);
void MPU6050_Read(void);

void MPU6050_Data_Prepare(float T);


/**********************************************
* �����ǽ���
**********************************************/
void MPU6050_GYRO_Calibrate(void);

/**********************************************
* ���ٶȼƽ���
**********************************************/
void MPU6050_ACC_Calibrate(void);

#endif
