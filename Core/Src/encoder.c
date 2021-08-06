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
 * 本程序使用了位置差分法使用了一个外部中断与定时器中断，用户可在函数中自行进行修改
 * This program uses the position difference method to use an external interrupt
 * and timer interrupt, the user can be modified in the function.
 * 因器件原因本编码器无ab项，使用者可自行修改
 * This encoder has no ab item due to device reason, which can be modified by user
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

void ENC_EXT_init()
{
	ENC_InitTypeDef ENC_InitTypeDef;
	ENC_InitTypeDef.ENC_Mode = ENC_MODE_RiseFall;
	ENC_InitTypeDef.ENC_Polity = PolityHigh;
	ENC_InitTypeDef.ENC_Interrupt = ENABLE;
	ENC_Inilize(PCA_INT1,&ENC_InitTypeDef);
}
