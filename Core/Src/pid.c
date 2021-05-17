/**
 ******************************************************************************
 * @file    pid.h
 * @author  sky-vocality
 * @version V1.0.1
 * @date    6-February-2021
 * @brief  This file is a PID regulator
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

#include "pid.h"

#define Inter_Max   5

PID wheel_pid = {0.15, 0.45, 0.28, 0, 0, 0, 980, 0, 0};
PID server_pid = {0.38886, 0.15, 0.04459, 0, 0, 0, 52.0, -52.0, 0};
PID follow_pid = {0.01, 0.0, 0.015, 0, 0, 0, 6, 6, 0};

void PID_Control(unsigned char pid_type, float current_position,float expected_position,PID* motor_type)
{
	if(pid_type == position)
	{
		//  float error_position;
		motor_type->error_last=motor_type->error_now;
		motor_type->error_now = expected_position - current_position;
		motor_type->error_inter += motor_type->error_now;
		// limit intergration of pid
		if(motor_type->error_inter>Inter_Max)
			motor_type->error_inter = Inter_Max;
		if(motor_type->error_inter<-Inter_Max)
			motor_type->error_inter = -Inter_Max;
    	motor_type->pid_out = motor_type->Kp * motor_type->error_now + motor_type->Ki * motor_type->error_inter + motor_type->Kd * (motor_type->error_now-motor_type->error_last);
    	// limit out of pid
        if(motor_type->pid_out > motor_type->out_limit_max)
            motor_type->pid_out = motor_type->out_limit_max;
        else if (motor_type->pid_out < motor_type->out_limit_low)
            motor_type->pid_out = motor_type->out_limit_low;
	}
    else if(pid_type == increment)
	{
		motor_type->error_last=motor_type->error_now;
		motor_type->error_now = expected_position - current_position;
		motor_type->pid_out += motor_type->Kp * (motor_type->error_now - motor_type->error_last) + motor_type->Ki * motor_type->error_now;
		// limit out of pid
		if(motor_type->pid_out > motor_type->out_limit_max)
            motor_type->pid_out = motor_type->out_limit_max;
        else if (motor_type->pid_out < motor_type->out_limit_low)
            motor_type->pid_out = motor_type->out_limit_low;
	}
	else if(pid_type == angle)
	{
		//  float error_position;
		motor_type->error_last=motor_type->error_now;
		motor_type->error_now = expected_position + current_position;
		motor_type->error_inter += current_position;
		// limit intergration of pid
		if(motor_type->error_inter>Inter_Max)
			motor_type->error_inter = Inter_Max;
		if(motor_type->error_inter<-Inter_Max)
			motor_type->error_inter = -Inter_Max;
    	motor_type->pid_out = motor_type->Kp * motor_type->error_now + motor_type->Ki * motor_type->error_inter + motor_type->Kd * -jy901.Gx;
    	// limit out of pid
        if(motor_type->pid_out > motor_type->out_limit_max)
            motor_type->pid_out = motor_type->out_limit_max;
        else if (motor_type->pid_out < motor_type->out_limit_low)
            motor_type->pid_out = motor_type->out_limit_low;
	}
}

void wheel_pid_timer_init()
{
	TIM_InitTypeDef TIM_InitTypeDef;
	TIM_InitTypeDef.TIM_Mode = TIM_16BitAutoReload;		//Working mode|����ģʽ,  	TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitTypeDef.TIM_Polity = PolityHigh;		//Priority Setting|���ȼ�����	PolityHigh,PolityLow
	TIM_InitTypeDef.TIM_Interrupt = ENABLE;	//Interrupt enable|�ж�����		ENABLE,DISABLE
	TIM_InitTypeDef.TIM_ClkSource = TIM_CLOCK_1T;	//Clock source|ʱ��Դ		TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitTypeDef.TIM_ClkOut = ENABLE;		//Programmable clock output|�ɱ��ʱ�����,	ENABLE,DISABLE
	TIM_InitTypeDef.TIM_Value = 41536;		//Initial load|װ�س�ֵ
	TIM_InitTypeDef.TIM_Run = ENABLE;		//�Ƿ�����|�Ƿ�����		ENABLE,DISABLE
	Timer_Inilize(Timer0, &TIM_InitTypeDef);
}
