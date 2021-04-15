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

#ifndef	__PID_H
#define	__PID_H

#include "system.h"
#include "timer.h"

#define position    0
#define increment   1
#define angle   2

typedef struct PID_PARAMETER
{
	float Kp;
	float Ki;
	float Kd;
	float error_now;
	float error_last;
	float error_inter;
    float out_limit_max;
	float out_limit_low;
	float pid_out;
}PID;

extern PID wheel_pid;
extern PID server_pid;

void PID_Control(unsigned char pid_type, float current_position,float expected_position,PID* motor_type);

void wheel_pid_timer_init();

#endif