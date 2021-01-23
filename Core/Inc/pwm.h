/**
  ******************************************************************************
  * @file    PWM.H
  * @author  PineconePi (BTA-16 And xdd_core)
  * @version V1.0.0
  * @date    20-February-2019
  * @brief  This document is used for PWM configuration
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

#ifndef _PWM_H_
#define _PWM_H_

#include	"system.h"

/*PWM channel|PWMͨ��*/
#define PWM_Channel1 0x00
#define PWM_Channel2 0x08
#define PWM_Channel3 0x10

/*PWM module|PWMģ��*/
#define PWM_0 0
#define PWM_1 1
#define PWM_2 2
#define PWM_3 3
#define PWM_4 4
#define PWM_5 5
#define PWM_6 6
#define PWM_7 7

//========================================================================
// Structures:PWM_InitTypeDef|�ṹ��:  PWM_InitTypeDef
// Description:PWM configuration structure.|����: PWM ���ýṹ�塣
// Parameters: PWM_Channel (PWM channel number parameter range: 1~3)
// 			   PWM_Value (PWM value) parameter range: 0-1000 [formula: duty cycle (high level time)/period (frequency)= PWM_Value/1000])
// 			   For example, the duty cycle of steering gear control is 2.5 ms and 20 ms, then 2.5/20 = 125/1000 (PWM_Value value should be 125)
// 			   PWM_Frequency (PWM frequency range: 46-5882)
// ����: PWM_Channel	(PWMͨ����	 ������Χ��1~3)
// 			 PWM_Value		(PWMֵ			 ������Χ��0~1000 [���㹫ʽ��ռ�ձȣ��ߵ�ƽʱ�䣩/���ڣ�Ƶ�ʣ�= PWM_Value/1000])
//       ����������ռ�ձ�Ϊ2.5ms ����Ϊ20ms����2.5/20=125/1000(PWM_ValueֵӦΪ 125)
// 		   PWM_Frequency(PWMƵ��		 ������Χ��46~5882)
// Return:none|����: none.
// Version:VER1.0.0|�汾: VER1.0.0
// Date:2018-12-20||����: 2018-12-20
// Note: Control the steering gear to 0 degrees by following steps
// PWM_InitTypeDef PWM_Init;
// PWM_Init.PWM_Channelx=PWM_Channel1;
// PWM_Init.PWM_Value=25;
// PWM_Init.PWM_Frequency=50;
// PWM_Output (PWM_0, &amp; PWM_Init);
// ��ע: ͨ�����²�����ƶ��ƫת��0��
//			 PWM_InitTypeDef PWM_Init;
//			 PWM_Init.PWM_Channelx=PWM_Channel1;
//			 PWM_Init.PWM_Value=25;
//			 PWM_Init.PWM_Frequency=50;
//			 PWM_Output(PWM_0,&PWM_Init);
//========================================================================
typedef struct{ 
	unsigned char	PWM_Channelx;
	float PWM_Value;
	float	PWM_Frequency;
} PWM_InitTypeDef;

/*PWM output function|PWM�������*/
void PWM_Output(unsigned char PWM_Number,PWM_InitTypeDef *PWMx);

#endif