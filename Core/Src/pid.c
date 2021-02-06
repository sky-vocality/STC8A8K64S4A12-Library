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

#define Inter_Max   2000

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
    	motor_type->pid_out = motor_type->Kp * motor_type->error_now + motor_type->Ki * motor_type->error_inter +	motor_type->Kd * (motor_type->error_now-motor_type->error_last);
    	// limit out of pid
        if(motor_type->pid_out > motor_type->out_limit)
            motor_type->pid_out = motor_type->out_limit;
        else if (motor_type->pid_out < -motor_type->out_limit)
            motor_type->pid_out = -motor_type->out_limit;
	}
    else if(pid_type == increment)
	{
		motor_type->error_last=motor_type->error_now;
		motor_type->error_now = expected_position - current_position;
		motor_type->pid_out += motor_type->Kp * (motor_type->error_now - motor_type->error_last) + motor_type->Ki * motor_type->error_now;
		if(motor_type->pid_out > motor_type->out_limit)
            motor_type->pid_out = motor_type->out_limit;
        else if (motor_type->pid_out < -motor_type->out_limit)
            motor_type->pid_out = -motor_type->out_limit;
	}
}
