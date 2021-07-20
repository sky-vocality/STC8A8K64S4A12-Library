/**
 ******************************************************************************
 * @file    mpu6050.c
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

#include "mpu6050.h"

MPU6050_InitDefine mpu6050 = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float q0 = 1, q1 = 0, q2 = 0, q3 = 0;  //四元数
float exInt = 0, eyInt = 0, ezInt = 0; //叉积计算误差的累计积分
unsigned int a_LSB = 16384;			   //a原始值系数
float g_LSB = 32.8;					   //g原始值系数

//========================================================================
// Function:void MPU_Init()|函数:  void MPU_Init()
// Description:Initialize MPU6050|描述:初始化MPU6050
// Parameter:|参数:
//
//
// Return:|返回:
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-07-20|日期: 2021-07-20
// Author: sky-vocality|作者: sky-vocality
// Note:|备注:
//
//
//
//
//
//========================================================================
void MPU_Init()
{
	IIC_host_Slave_machine(host_machine); //初始化IIC总线

	MPU_Write_Byte(MPU_PWR_MGMT1_REG, 0X80); //复位MPU6050
	Delay_Ms(100);
	MPU_Write_Byte(MPU_PWR_MGMT1_REG, 0X00); //唤醒MPU6050
	MPU_Set_Gyro_Fsr(2);					 //陀螺仪传感器,±1000dps
	MPU_Set_Accel_Fsr(0);					 //加速度传感器 ±2g
	MPU_Set_Rate(50);						 //设置采样率50HZ
	MPU_Write_Byte(MPU_INT_EN_REG, 0X00);	 //关闭所有中断
	MPU_Write_Byte(MPU_USER_CTRL_REG, 0X00); //I2C主模式关闭
	MPU_Write_Byte(MPU_FIFO_EN_REG, 0X00);	 //关闭FIFO
	MPU_Write_Byte(MPU_INTBP_CFG_REG, 0X80); //INT引脚低电平有效

	MPU_Write_Byte(MPU_PWR_MGMT1_REG, 0X01); //设置CLKSEL,PLL X 轴为参考
	MPU_Write_Byte(MPU_PWR_MGMT2_REG, 0X00); //加速度陀螺仪都工作
	MPU_Set_Rate(50);						 //设置采样率为50HZ
}

//========================================================================
// Function:void MPU_Write_Byte()|函数:  void MPU_Write_Byte()
// Description:Send data to MPU6050 with IIC|描述:  用IIC给MPU6050发送数据
// Parameter:reg:address,	dat:data|参数:reg:寄存器地址,	dat:数据
//
//
// Return:|返回:
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-07-20|日期: 2021-07-20
// Author: sky-vocality|作者: sky-vocality
// Note:|备注:
//
//
//
//
//
//========================================================================
void MPU_Write_Byte(unsigned char reg, unsigned char dat)
{
	P_SW2 = 0x90;
	Start();
	SendData(MPU6050_ADDR << 1);
	SendData(reg);
	SendData(dat);
	Stop();
	P_SW2 = 0x00;
}

//========================================================================
// Function:void MPU_Read_Byte()|函数:  void MPU_Read_Byte()
// Description:Read data to MPU6050 with IIC|描述:  用IIC给MPU6050发送数据
// Parameter:dat:data|参数:dat:数据
//
//
// Return:The 16-bit data obtained by the fusion
// of the high and low eight bits|返回:高八位和低八位融合后得到的16位的数据
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-07-20|日期: 2021-07-20
// Author: sky-vocality|作者: sky-vocality
// Note:|备注:
//
//
//
//
//
//========================================================================
int MPU_Read_Byte(unsigned char reg)
{
	unsigned char p0 = 0;
	int temp = 0;
	unsigned char p1 = 0;
	P_SW2 = 0x90;
	Start();
	SendData(MPU6050_ADDR << 1);
	SendData(reg);
	Start();
	SendData(MPU6050_ADDR << 1 | 1);
	p0 = RecvData(); //Read data 1|读取数据1
	SendACK();
	p1 = RecvData(); //读取数据2|读取数据2
	SendNAK();
	Stop(); //Send stop command|发送停止命令
	temp = ((unsigned int)p0 << 8) | p1;
	P_SW2 = 0x00;
	return temp;
}

//========================================================================
// Function:void MPU_Set_Gyro_Fsr()|函数:  void MPU_Set_Gyro_Fsr()
// Description:Configure the gyroscope range|描述:配置陀螺仪量程
// Parameter:fsr:configure number|参数:fsr:配置数
//
//
// Return:|返回:
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-07-20|日期: 2021-07-20
// Author: sky-vocality|作者: sky-vocality
// Note:|备注:
// fsr:0,±250dps;131LSB/o/s
// 1,±500dps;65.5LSB/o/s
// 2,±1000dps;32.8LSB/o/s
// 3,±2000dps;16.4LSB/o/s
//
//
//
//
//========================================================================
void MPU_Set_Gyro_Fsr(unsigned char fsr)
{
	if (fsr == 0)
		g_LSB = 131;
	else if (fsr == 1)
		g_LSB = 65.5;
	else if (fsr == 2)
		g_LSB = 32.8;
	else
		g_LSB = 16.4;
	MPU_Write_Byte(MPU_GYRO_CFG_REG, fsr << 3);
}

//========================================================================
// Function:void MPU_Set_Accel_Fsr()|函数:  void MPU_Set_Accel_Fsr()
// Description:Configure the accelerometer range|描述:配置加速度计量程
// Parameter:fsr:configure number|参数:fsr:配置数
//
//
// Return:|返回:
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-07-20|日期: 2021-07-20
// Author: sky-vocality|作者: sky-vocality
// Note:|备注:
// fsr:0,±2g;16384LSB/g
// 1,±4g;8192LSB/g
// 2,±8g;4096LSB/g
// 3,±16g;2048LSB/g
//
//
//
//
//========================================================================
void MPU_Set_Accel_Fsr(unsigned char fsr)
{
	if (fsr == 0)
		a_LSB = 16384;
	else if (fsr == 1)
		a_LSB = 8192;
	else if (fsr == 2)
		a_LSB = 4096;
	else
		a_LSB = 2048;
	MPU_Write_Byte(MPU_ACCEL_CFG_REG, fsr << 3);
}

//========================================================================
// Function:void MPU_Set_LPF()|函数:  void MPU_Set_LPF()
// Description:Set up the digital low pass filter of MPU6050|描述:设置MPU6050的数字低通滤波器
// Parameter:lpf:Digital low pass filtering frequency (Hz)|参数:lpf:数字低通滤波频率(Hz)
//
//
// Return:|返回:
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-07-20|日期: 2021-07-20
// Author: sky-vocality|作者: sky-vocality
// Note:|备注:
//
//
//
//
//========================================================================
void MPU_Set_LPF(unsigned int lpf)
{
	unsigned char dat = 0;
	if (lpf >= 188)
		dat = 1;
	else if (lpf >= 98)
		dat = 2;
	else if (lpf >= 42)
		dat = 2;
	else if (lpf >= 42)
		dat = 3;
	else if (lpf >= 20)
		dat = 4;
	else if (lpf >= 10)
		dat = 5;
	else
		dat = 6;
	MPU_Write_Byte(MPU_CFG_REG, dat); //设置数字低通滤波器
}

//========================================================================
// Function:void MPU_Set_Rate()|函数:void MPU_Set_Rate()
// Description:Set the sample rate of MPU6050|描述:设置MPU6050的采样率
// Parameter:rate:(Hz)|参数:rate:(Hz)
//
//
// Return:|返回:
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-07-20|日期: 2021-07-20
// Author: sky-vocality|作者: sky-vocality
// Note:|备注:
//
//
//
//
//========================================================================
void MPU_Set_Rate(unsigned int rate)
{
	unsigned char dat;
	if (rate > 1000)
		rate = 1000;
	if (rate < 4)
		rate = 4;
	dat = 1000 / rate - 1;
	MPU_Write_Byte(MPU_SAMPLE_RATE_REG, dat); //设置数字低通滤波器
	MPU_Set_LPF(rate / 2);					  //自动设置LPF为采样率的一半
}

static float invSqrt(float x) //快速计算 1/Sqrt(x)
{
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long *)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float *)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}

//========================================================================
// Function:void MPU_Set_Rate()|函数:void MPU_Set_Rate()
// Description:MPU6050 data update and attitude solution|描述:MPU6050数据更新与姿态解算
// Parameter:|参数:
//
//
// Return:|返回:
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-07-20|日期: 2021-07-20
// Author: sky-vocality|作者: sky-vocality
// Note:|备注:
//
//
//
//
//========================================================================
void MPU_Update()
{
	float Kp = 1.50f;
	float Ki = 0.005f;
	float vx, vy, vz; //实际重力加速度
	float ex, ey, ez; //叉积计算的误差
	float norm;

	float q0q0 = q0 * q0;
	float q0q1 = q0 * q1;
	float q0q2 = q0 * q2;
	float q0q3 = q0 * q3;
	float q1q1 = q1 * q1;
	float q1q2 = q1 * q2;
	float q1q3 = q1 * q3;
	float q2q2 = q2 * q2;
	float q2q3 = q2 * q3;
	float q3q3 = q3 * q3;

	mpu6050.Gx = ((double)MPU_Read_Byte(MPU_GYRO_XOUTH_REG) / g_LSB) * G;
	mpu6050.Gy = ((double)MPU_Read_Byte(MPU_GYRO_YOUTH_REG) / g_LSB) * G;
	mpu6050.Gz = ((double)MPU_Read_Byte(MPU_GYRO_ZOUTH_REG) / g_LSB) * G;

	mpu6050.Ax = ((double)MPU_Read_Byte(MPU_ACCEL_XOUTH_REG) / a_LSB) / 57.2957795;
	mpu6050.Ay = ((double)MPU_Read_Byte(MPU_ACCEL_YOUTH_REG) / a_LSB) / 57.2957795;
	mpu6050.Az = ((double)MPU_Read_Byte(MPU_ACCEL_ZOUTH_REG) / a_LSB) / 57.2957795;

	if (mpu6050.Ax * mpu6050.Ay * mpu6050.Az == 0)
		return;

	//加速度计测量的重力方向(机体坐标系)
	norm = invSqrt(mpu6050.Ax * mpu6050.Ax + mpu6050.Ay * mpu6050.Ay + mpu6050.Az * mpu6050.Az);
	mpu6050.Ax = mpu6050.Ax * norm;
	mpu6050.Ay = mpu6050.Ay * norm;
	mpu6050.Az = mpu6050.Az * norm;

	//四元数推出的实际重力方向(机体坐标系)
	vx = 2 * (q1q3 - q0q2);
	vy = 2 * (q0q1 + q2q3);
	vz = q0q0 - q1q1 - q2q2 + q3q3;

	//叉积误差
	ex = (mpu6050.Ay * vz - mpu6050.Az * vy);
	ey = (mpu6050.Az * vx - mpu6050.Ax * vz);
	ez = (mpu6050.Ax * vy - mpu6050.Ay * vx);

	//叉积误差积分为角速度
	exInt = exInt + ex * Ki;
	eyInt = eyInt + ey * Ki;
	ezInt = ezInt + ez * Ki;

	//角速度补偿
	mpu6050.Gx = mpu6050.Gx + Kp * ex + exInt;
	mpu6050.Gy = mpu6050.Gy + Kp * ey + eyInt;
	mpu6050.Gz = mpu6050.Gz + Kp * ez + ezInt;

	//更新四元数
	q0 = q0 + (-q1 * mpu6050.Gx - q2 * mpu6050.Gy - q3 * mpu6050.Gz) * halfT;
	q1 = q1 + (q0 * mpu6050.Gx + q2 * mpu6050.Gz - q3 * mpu6050.Gy) * halfT;
	q2 = q2 + (q0 * mpu6050.Gy - q1 * mpu6050.Gz + q3 * mpu6050.Gx) * halfT;
	q3 = q3 + (q0 * mpu6050.Gz + q1 * mpu6050.Gy - q2 * mpu6050.Gx) * halfT;

	//单位化四元数
	norm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 = q0 * norm;
	q1 = q1 * norm;
	q2 = q2 * norm;
	q3 = q3 * norm;

	//四元数反解欧拉角
	mpu6050.Yaw = atan2(2.f * (q1q2 + q0q3), q0q0 + q1q1 - q2q2 - q3q3) * 57.3f;
	mpu6050.Pitch = -asin(2.f * (q1q3 - q0q2)) * 57.3f;
	mpu6050.Roll = atan2(2.f * q2q3 + 2.f * q0q1, q0q0 - q1q1 - q2q2 + q3q3) * 57.3f;
}
