/**
  ******************************************************************************
  * @file    LMV358.h
  * @author  NULL(基于PineconePi(基于宏晶科技STC15库函数进行修改))
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
  * 
  * 
  *
  * 
  ******************************************************************************
	**/
	
#ifndef	__LMV358_H
#define	__LMV358_H

#define times 12
#include "adc.h"
#include "delay.h"
#include "uart.h"

unsigned int get_adc_averge(unsigned char);
void LMV358_start();
void get_adc();




#endif