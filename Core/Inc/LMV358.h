/**
  ******************************************************************************
  * @file    LMV358.h
  * @author  NULL
  * @version V1.0.0
  * @date    12-April-2021
  * @brief  This file is used to configure LMV358
  * @License:GNU General Public License v3.0         
  ******************************************************************************
  * @attention
  *
  *
  *  
  *
  * 
  ********************************************************************************/
	
#ifndef	__LMV358_H
#define	__LMV358_H

#define times 12

#include "adc.h"
#include "delay.h"
#include "uart.h"

unsigned int LMV358_GetAvergeData(unsigned char);
void LMV358_Init();
void LMV358_InductorNormal();
unsigned int LMV358_Output();

//extern unsigned int ad_data_max[6];  
//extern unsigned int ad_data_min[6];   	
extern unsigned int ad_data_max[2];  
extern unsigned int ad_data_min[2];
extern unsigned int left,right;
//extern int left1,right1;
//extern int left2,right2;


#endif