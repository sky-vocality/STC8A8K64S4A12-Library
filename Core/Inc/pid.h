/**
 ******************************************************************************
 * @file    pid.h
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

#ifndef	__PID_H
#define	__PID_H

#include "system.h"

typedef struct PID_PARAMETER
{
	float Kp;
	float Ki;
	float Kd;
	float error_now;
	float error_last;
	float error_inter;
    float out_limit;
	float pid_out;
}PID;

void PID_Control(float current_position,float expected_position,PID* motor_type);


#endif