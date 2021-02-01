/**
 ******************************************************************************
 * @file    jy901.h
 * @author  sky-vocality
 * @version V1.0.0
 * @date    25-February-2021
 * @brief  This file is used for update jy901 data
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
#ifndef	__JY901_H
#define	__JY901_H

#include "system.h"
#include "iic.h"

#define IICAddr   0x50
#define ROLL      0x3d
#define PITCH     0x3e
#define YAW       0x3f

typedef struct
{ 
	double Roll;
    double Pitch;
    double Yaw;
} JY901_InitDefine; 

extern JY901_InitDefine jy901;

void jy901_update();

#endif
