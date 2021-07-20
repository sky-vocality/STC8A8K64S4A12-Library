/**
 ******************************************************************************
 * @file    mpu6050.h
 * @author  sky-vocality
 * @version V1.0.0
 * @date    18-July-2021
 * @brief  This file is used for drive mpu6050
 * @License:GNU General Public License v3.0         
 ******************************************************************************
 * @attention
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 ******************************************************************************
**/
#ifndef	__MPU6050_H
#define	__MPU6050_H
#include "iic.h"
#include "timer.h"
#include "math.h"

#define MPU6050_ADDR                    0x68  	//IIC写入时的地址字节数据，+1为读取
#define MPU6050_ADDR2                   0x69  	//取决于AD0的状态

#define MPU6050_ID	                    0x98	//IIC地址寄存器(默认数值0x98，只读)

#define MPU_SELF_TEST_X_GYRO            0x00
#define MPU_SELF_TEST_Y_GYRO            0x01 
#define MPU_SELF_TEST_Z_GYRO            0x02

#define MPU_SELF_TESTX_REG	        	0X0D	//ACCEL自检寄存器X
#define MPU_SELF_TESTY_REG		        0X0E	//ACCEL自检寄存器Y
#define MPU_SELF_TESTZ_REG		        0X0F	//ACCEL自检寄存器Z

#define MPU_SELF_TESTA_REG		        0X10	//自检寄存器A

#define MPU_XG_OFFS_USRH                0x13	
#define MPU_XG_OFFS_USRL                0x14
#define MPU_YG_OFFS_USRH                0x15
#define MPU_YG_OFFS_USRL                0x16
#define MPU_ZG_OFFS_USRH                0x17
#define MPU_ZG_OFFS_USRL                0x18

#define MPU_SAMPLE_RATE_REG	        	0X19	//采样频率分频器
#define MPU_CFG_REG			    		0X1A	//配置寄存器
#define MPU_GYRO_CFG_REG				0X1B	//陀螺仪配置寄存器
#define MPU_ACCEL_CFG_REG				0X1C	//加速度计配置寄存器
#define MPU_ACCEL_CONFIG_2              0x1D
#define MPU_LOW_POWER_MODE				0x1E
#define MPU_MOTION_DET_REG				0X1F	//运动检测阀值设置寄存器
#define MPU_FIFO_EN_REG					0X23	//FIFO使能寄存器

#define MPU_I2CMST_STA_REG				0X36	//IIC主机状态寄存器
#define MPU_INTBP_CFG_REG				0X37	//中断/旁路设置寄存器
#define MPU_INT_EN_REG					0X38	//中断使能寄存器
#define MPU_INT_STA_REG					0X3A	//中断状态寄存器

#define MPU_ACCEL_XOUTH_REG				0X3B	//加速度值,X轴高8位寄存器
#define MPU_ACCEL_XOUTL_REG				0X3C	//加速度值,X轴低8位寄存器
#define MPU_ACCEL_YOUTH_REG				0X3D	//加速度值,Y轴高8位寄存器
#define MPU_ACCEL_YOUTL_REG				0X3E	//加速度值,Y轴低8位寄存器
#define MPU_ACCEL_ZOUTH_REG				0X3F	//加速度值,Z轴高8位寄存器
#define MPU_ACCEL_ZOUTL_REG				0X40	//加速度值,Z轴低8位寄存器

#define MPU_TEMP_OUTH_REG				0X41	//温度值高八位寄存器
#define MPU_TEMP_OUTL_REG				0X42	//温度值低8位寄存器

#define MPU_GYRO_XOUTH_REG				0X43	//陀螺仪值,X轴高8位寄存器
#define MPU_GYRO_XOUTL_REG				0X44	//陀螺仪值,X轴低8位寄存器
#define MPU_GYRO_YOUTH_REG				0X45	//陀螺仪值,Y轴高8位寄存器
#define MPU_GYRO_YOUTL_REG				0X46	//陀螺仪值,Y轴低8位寄存器
#define MPU_GYRO_ZOUTH_REG				0X47	//陀螺仪值,Z轴高8位寄存器
#define MPU_GYRO_ZOUTL_REG				0X48	//陀螺仪值,Z轴低8位寄存器

#define MPU_I2CSLV0_DO_REG				0X63	//IIC从机0数据寄存器
#define MPU_I2CSLV1_DO_REG				0X64	//IIC从机1数据寄存器
#define MPU_I2CSLV2_DO_REG				0X65	//IIC从机2数据寄存器
#define MPU_I2CSLV3_DO_REG				0X66	//IIC从机3数据寄存器

#define MPU_I2CMST_DELAY_REG	        0X67	//IIC主机延时管理寄存器
#define MPU_SIGPATH_RST_REG				0X68	//信号通道复位寄存器
#define MPU_MDETECT_CTRL_REG	        0X69	//运动检测控制寄存器
#define MPU_USER_CTRL_REG				0X6A	//用户控制寄存器
#define MPU_PWR_MGMT1_REG				0X6B	//电源管理寄存器1
#define MPU_PWR_MGMT2_REG				0X6C	//电源管理寄存器2 
#define MPU_FIFO_CNTH_REG				0X72	//FIFO计数寄存器高八位
#define MPU_FIFO_CNTL_REG				0X73	//FIFO计数寄存器低八位
#define MPU_FIFO_RW_REG					0X74	//FIFO读写寄存器

#define WHO_AM_I		        		0X75	//器件ID寄存器

#define G  			9.7914		//重庆的重力加速度
#define halfT 		0.01f		//计算周期的一半，单位s

typedef struct
{ 
	double Roll;
    double Pitch;
    double Yaw;
	double Gx;
	double Gy;
	double Gz;
    double Ax;
	double Ay;
	double Az;
} MPU6050_InitDefine; 

extern MPU6050_InitDefine mpu6050;

void MPU_Init();
void MPU_Update();

void MPU_Write_Byte(unsigned char reg, unsigned char dat);
int MPU_Read_Byte(unsigned char reg);
void MPU_Set_Gyro_Fsr(unsigned char fsr);
void MPU_Set_Accel_Fsr(unsigned char fsr);
void MPU_Set_LPF(unsigned int lpf);
void MPU_Set_Rate(unsigned int rate);
static float invSqrt(float x)

#endif
