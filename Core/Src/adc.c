/**
  ******************************************************************************
  * @file    adc.h
  * @author  sky-vocality(基于PineconePi(基于宏晶科技STC15库函数进行修改))
  * @version V1.0.0
  * @date    13-March-2021
  * @brief  This file is used to configure ADC
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

#include "adc.h"
#include "intrins.h"

/********************* ADC Interrput Function************************/
void ADC_int (void) interrupt 5
{
	ADC_CONTR &= ~ADC_FLAG;
}

//========================================================================
// Function:void	ADC_Inilize(ADC_InitTypeDef *ADCx)|函数: void	ADC_Inilize(ADC_InitTypeDef *ADCx)
// Description:ADC initializer|描述: ADC初始化程序.
// Parameter:Refer to the structure definition in adc.h.|参数: 请参考adc.h里面的结构体定义
//       
//       
// Return: |返回: 
// Version: |版本: VER1.0.0
// Date:2021-03-13|日期: 2021-03-13
// Author:sky-vocality |作者: sky-vocality
// Note: |备注:
//	
//	
//	
//	
//	
//========================================================================
void ADC_Inilize(ADC_InitTypeDef *ADCx)
{
	EA = 1;
	
	P1M0 = 0x00;
	P1M1 |= ADCx->ADC_Px;
	ADC_CONTR = (ADC_CONTR & ~ADC_90T) | ADCx->ADC_Speed;
	if(ADCx->ADC_Power == ENABLE)	ADC_CONTR |= 0x80;
	else							ADC_CONTR &= 0x7F;
	if(ADCx->ADC_AdjResult == ADC_RES_H2L8)	ADCCFG |=  (1<<5);	//The high 2 bits of 10-bit AD results are placed in the low 2 bits of ADC_RES and the low 8 bits in ADC_RESL.|10位AD结果的高2位放ADC_RES的低2位，低8位在ADC_RESL。
	else									ADCCFG &= ~(1<<5);	//ADC_RES is the highest 8 bits of 10-bit AD results and the lowest 2 bits are the lowest 2 bits of ADC_RESL results.|10位AD结果的高8位放ADC_RES，低2位在ADC_RESL的低2位。
	if(ADCx->ADC_Interrupt == ENABLE)	EADC = 1;			//Interrupt enable|中断允许		ENABLE,DISABLE
	else								EADC = 0;
	if(ADCx->ADC_Polity == PolityHigh)	PADC = 1;		//Priority Setting|优先级设置	PolityHigh,PolityLow
	else								PADC = 0;
}


//========================================================================
// Function:void ADC_PowerControl(unsigned char pwr)|函数: void	ADC_PowerControl(unsigned char pwr)
// Description:ADC power control program.|描述: ADC电源控制程序.
// Parameter:Pwr: power control,ENABLE OR DISABLE.|参数: Pwr: 电源控制,ENABLE或DISABLE.
//       
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-03-13|日期: 2021-03-13
// Author: sky-vocality|作者: sky-vocality
// Note:|备注:
//	
//	
//	
//	
//	
//========================================================================
void ADC_PowerControl(unsigned char Pwr)
{
	if(Pwr == ENABLE)	ADC_CONTR |= 0x80;
	else				ADC_CONTR &= 0x7f;
}

//========================================================================
// Function:unsigned int Get_ADC10bitResult(unsigned char channel)|函数: unsigned int	Get_ADC10bitResult(unsigned char channel)
// Description:Query the ADC results once.|描述: 查询一次ADC结果.
// Parameter: Select the ADC to convert. |参数: Channel: 选择要转换的ADC.
//       
//       
// Return:ADC results.|返回: ADC结果.
// Version:VER1.0.0|:版本: VER1.0.0
// Date:2021-03-13|日期: 2021-03-13
// Author:sky-vocality|作者: sky-vocality
// Note:|备注:
//	
//	
//	
//	
//	
//========================================================================
unsigned int Get_ADC10bitResult(unsigned char Channel)	//Channel = 0~7
{
	unsigned int	adc;
	unsigned char	i;

	if(Channel > ADC_CH7)	return	1024;	//错误,返回1024,调用的程序判断	
	ADC_RES = 0;
	ADC_RESL = 0;

	ADC_CONTR = (ADC_CONTR & 0xe0) | ADC_START | Channel; 
	_nop_();	
    _nop_();	//对ADC_CONTR操作后要2T之后才能访问

	for(i=0; i<250; i++)		//超时
	{
		if(!(ADC_CONTR & ADC_FLAG))
		{
			ADC_CONTR &= ~ADC_FLAG;
			if(ADCCFG &  (1<<5))		//12位AD结果的高4位放ADC_RES的高4位，低8位在ADC_RESL。
			{
				adc = (unsigned int)(ADC_RES & 0x0f);
				adc = (adc << 8) | ADC_RESL;
			}
			else		//12位AD结果的高8位放ADC_RES，低4位在ADC_RESL的低4位。
			{
				adc = (int)ADC_RES << 8;
				adc |= (int)ADC_RESL;
				adc = adc>>4;
			}
			return	adc;
		}
	}
	return	1024;	//错误,返回1024,调用的程序判断
}

