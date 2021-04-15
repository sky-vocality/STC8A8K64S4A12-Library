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
#include "pwm.h"

PWM_InitTypeDef wheel_pwm = {PWM_Channel1, 0, 12500};
PWM_InitTypeDef server_pwm = {PWM_Channel1, 147.5, 100};

//========================================================================
// Function:void PWM_CLK_Output(unsigned char PWM_Number,PWM_InitTypeDef *PWMx)|����: void PWM_CLK_Output(unsigned char PWM_Number,PWM_InitTypeDef *PWMx)
// Description:PWM module output function|����: PWMģ���������
// Parameters: PWM_Number (PWM module number parameter range: 0-7)
//             * PWMx: See PWM.h for details
// ����: PWM_Number		(PWMģ���� ������Χ��0~7)
//  	 *PWMx�������PWM.h
//       
//       
// Return:|����: 
// Version:VER1.0.0|�汾: VER1.0.0
// Date:2021-04-16|����: 2021-04-16
// Author: sky-vocality|����: sky-vocality
// Note:|��ע:
//	
//	
//	
//	
//	
//========================================================================
void PWM_CLK_Output(unsigned char PWM_Number,PWM_InitTypeDef *PWMx)
{ 
	float PWM_Buf = 0,PWM_Pre = 0,PWM_Value;
	PWM_Buf = ( 1500000 / PWMx->PWM_Frequency );
	PWM_Value = 1000 - PWMx->PWM_Value;
	PWM_Pre = (PWM_Value/1000);
	P_SW2 = 0x80;																//Allow access to extended RAM (STC added)|���������չRAM��STC������
	PWMCKS = 0x0f;															   //System Clock 16 Dividing Frequency|ϵͳʱ��16��Ƶ
	PWMC = PWM_Buf;	
	switch(PWM_Number)
	{
		case 0 : PWM0T1 = 0x0000;PWM0T2 = PWM_Buf*PWM_Pre;PWM0CR= 0x80|PWMx->PWM_Channelx;break;
		case 1 : PWM1T1 = 0x0000;PWM1T2 = PWM_Buf*PWM_Pre;PWM1CR= 0x80|PWMx->PWM_Channelx;break;
		case 2 : PWM2T1 = 0x0000;PWM2T2 = PWM_Buf*PWM_Pre;PWM2CR= 0x80|PWMx->PWM_Channelx;break;
		case 3 : PWM3T1 = 0x0000;PWM3T2 = PWM_Buf*PWM_Pre;PWM3CR= 0x80|PWMx->PWM_Channelx;break;
		case 4 : PWM4T1 = 0x0000;PWM4T2 = PWM_Buf*PWM_Pre;PWM4CR= 0x80|PWMx->PWM_Channelx;break;
		case 5 : PWM5T1 = 0x0000;PWM5T2 = PWM_Buf*PWM_Pre;PWM5CR= 0x80|PWMx->PWM_Channelx;break;
		case 6 : PWM6T1 = 0x0000;PWM6T2 = PWM_Buf*PWM_Pre;PWM6CR= 0x80|PWMx->PWM_Channelx;break;
		case 7 : PWM7T1 = 0x0000;PWM7T2 = PWM_Buf*PWM_Pre;PWM7CR= 0x80|PWMx->PWM_Channelx;break;
		default:break;
	}
	P_SW2 = 0x00;																//Disallow Access to Extended RAM (STC Added)|��ֹ������չRAM��STC������
	PWMCR = 0x80;                               //Start PWM module|����PWMģ��
}

//========================================================================
// Function:void PWM_PCA_Output(unsigned char PWM_Number,PWM_InitTypeDef *PWMx)|����: void PWM_PCA_Output(unsigned char PWM_Number,PWM_InitTypeDef *PWMx)
// Description:PWM_PCA module output function|����: PWM_PCAģ���������
// Parameters: PWM_Number (PWM module number parameter range: 0-3)
//             * PWMx: See PWM.h for details
// ����: PWM_Number		(PWMģ���� ������Χ��0~3)
//  	 *PWMx�������PWM.h
//       
//       
// Return:|����: 
// Version:VER1.0.0|�汾: VER1.0.0
// Date:2021-04-16|����: 2021-04-16
// Author: sky-vocality|����: sky-vocality
// Note:|��ע:
//	
//	
//	
//	
//	
//========================================================================
void PWM_PCA_Output(unsigned char PWM_Number,PWM_InitTypeDef *PWMx)
{ 
	unsigned int PWM_Buf = 0, PWM_out = 0;
	float PWM_Pre = 0,PWM_Value;
	PWM_Buf = 255 - (unsigned int)(24000000 / (PWMx->PWM_Frequency *256));
	PWM_Value = 1000 - PWMx->PWM_Value;
	PWM_Pre = (PWM_Value/1000);
	PWM_out = (int)(255 * PWM_Pre);
	CCON = 0x00;
	CMOD = 0x0d;
	CL = 0;
	CH = 0;
	switch(PWMx->PWM_Channelx)
	{
		case 0x00 : P_SW1 = 0x00;break;
		case 0x08 : P_SW1 = 0x10;break;
		case 0x10 : P_SW1 = 0x20;break;
		default:break;
	}
	switch(PWM_Number)
	{
		case 0 : CCAPM0 = 0x42;PCA_PWM0 = 0x00;CCAP0L = (unsigned char)PWM_out;CCAP0H = (unsigned char)PWM_out;break;
		case 1 : CCAPM1 = 0x42;PCA_PWM1 = 0x00;CCAP1L = (unsigned char)PWM_out;CCAP1H = (unsigned char)PWM_out;break;
		case 2 : CCAPM2 = 0x42;PCA_PWM2 = 0x00;CCAP2L = (unsigned char)PWM_out;CCAP2H = (unsigned char)PWM_out;break;
		case 3 : CCAPM3 = 0x42;PCA_PWM3 = 0x00;CCAP3L = (unsigned char)PWM_out;CCAP3H = (unsigned char)PWM_out;break;
		default:break;
	}
	CR = 1;
}

