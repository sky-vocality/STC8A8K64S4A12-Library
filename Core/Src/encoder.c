/**
 ******************************************************************************
 * @file    encoder.c
 * @author  sky-vocality
 * @version V1.0.0
 * @date    25-January-2021
 * @brief  This file is used for processing encoder data
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

#include "encoder.h"

unsigned char	ENC_Inilize(unsigned char EXT, ENC_InitTypeDef *INTx)
{
  EXTI_InitTypeDef EXTI_InitTypeDef;
	EXTI_InitTypeDef.EXTI_Mode = INTx->ENC_Mode;//上升沿中断
	EXTI_InitTypeDef.EXTI_Polity = INTx->ENC_Polity;//高优先级
	EXTI_InitTypeDef.EXTI_Interrupt = INTx->ENC_Interrupt;//使能
	return Ext_Inilize(EXT,&EXTI_InitTypeDef);//完成配置
}
