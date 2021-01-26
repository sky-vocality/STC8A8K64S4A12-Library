/**
 ******************************************************************************
 * @file    pid.c
 * @author  sky-vocality
 * @version V1.0.0
 * @date    26-January-2021
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

#define Inter_Max   2000

void PID_Control(float current_position, float expected_position,PID* motor_type)
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
    motor_type->pid_out = motor_type->Kp * motor_type->error_now + motor_type->Ki * motor_type->error_inter +	motor_type->Kd * (motor_type->error_now-motor_type->error_last);
    // limit out of pid
    if(motor_type->pid_out > motor_type->out_limit)
        motor_type->pid_out = motor_type->out_limit;
    else if (motor_type->pid_out < -motor_type->out_limit)
        motor_type->pid_out = -motor_type->out_limit;
}
