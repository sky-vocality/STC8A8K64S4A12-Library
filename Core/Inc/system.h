/**
  ******************************************************************************
  * @file    system.h
  * @author  sky-vocality
  * @version V1.0.0
  * @date    20-December-2020
  * @brief  This article will be used for the unified invocation of functions and system configuration. 
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
#ifndef		__SYSTEM_H_
#define		__SYSTEM_H_


/*********************************************************/

  #define MAIN_Fosc		24000000UL	//Define master clock 24Mhz
//#define MAIN_Fosc		22118400UL	//Define the master clock
//#define MAIN_Fosc		12000000UL	//Define the master clock
//#define MAIN_Fosc		11059200UL	//Define the master clock
//#define MAIN_Fosc		 5529600UL	//Define the master clock


/*********************************************************/

#include	"PineconePiNano.h"//Library function calls are written down in turn|库函数调用依次往下写


/**************************************************************************/

#define Main_Fosc_KHZ	(MAIN_Fosc / 1000)

/***********************************************************/

#endif