/**
  ******************************************************************************
  * @file    adc.h
  * @author  PineconePi(���ں꾧�Ƽ�STC15�⺯�������޸�)
  * @version V1.0.0
  * @date    20-December-2018
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
// Function:void	ADC_Inilize(ADC_InitTypeDef *ADCx)|����: void	ADC_Inilize(ADC_InitTypeDef *ADCx)
// Description:ADC initializer|����: ADC��ʼ������.
// Parameter:Refer to the structure definition in adc.h.|����: ��ο�adc.h����Ľṹ�嶨��
//       
//       
// Return: |����: 
// Version: |�汾: VER1.0.0
// Date:2018-12-20|����: 2018-12-20
// Author:PineconePi |����: PineconePi
// Note: |��ע:
//	
//	
//	
//	
//	
//========================================================================
void DC_Inilize(ADC_InitTypeDef *ADCx)
{
	EA = 1;
	
	P1M0 = 0x00;
	P1M1 |= ADCx->ADC_Px;
	ADC_CONTR = (ADC_CONTR & ~ADC_90T) | ADCx->ADC_Speed;
	if(ADCx->ADC_Power == ENABLE)	ADC_CONTR |= 0x80;
	else							ADC_CONTR &= 0x7F;
	if(ADCx->ADC_AdjResult == ADC_RES_H2L8)	ADCCFG |=  (1<<5);	//The high 2 bits of 10-bit AD results are placed in the low 2 bits of ADC_RES and the low 8 bits in ADC_RESL.|10λAD����ĸ�2λ��ADC_RES�ĵ�2λ����8λ��ADC_RESL��
	else									ADCCFG &= ~(1<<5);	//ADC_RES is the highest 8 bits of 10-bit AD results and the lowest 2 bits are the lowest 2 bits of ADC_RESL results.|10λAD����ĸ�8λ��ADC_RES����2λ��ADC_RESL�ĵ�2λ��
	if(ADCx->ADC_Interrupt == ENABLE)	EADC = 1;			//Interrupt enable|�ж�����		ENABLE,DISABLE
	else								EADC = 0;
	if(ADCx->ADC_Polity == PolityHigh)	PADC = 1;		//Priority Setting|���ȼ�����	PolityHigh,PolityLow
	else								PADC = 0;
}


//========================================================================
// Function:void ADC_PowerControl(unsigned char pwr)|����: void	ADC_PowerControl(unsigned char pwr)
// Description:ADC power control program.|����: ADC��Դ���Ƴ���.
// Parameter:Pwr: power control,ENABLE OR DISABLE.|����: Pwr: ��Դ����,ENABLE��DISABLE.
//       
//       
// Return:|����: 
// Version:VER1.0.0|�汾: VER1.0.0
// Date:2018-12-20|����: 2018-12-20
// Author: PineconePi|����: PineconePi
// Note:|��ע:
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
// Function:unsigned int Get_ADC10bitResult(unsigned char channel)|����: unsigned int	Get_ADC10bitResult(unsigned char channel)
// Description:Query the ADC results once.|����: ��ѯһ��ADC���.
// Parameter: Select the ADC to convert. |����: Channel: ѡ��Ҫת����ADC.
//       
//       
// Return:ADC results.|����: ADC���.
// Version:VER1.0.0|:�汾: VER1.0.0
// Date:2018-12-20|����: 2018-12-20
// Author:PineconePi|����: PineconePi
// Note:|��ע:
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

	if(Channel > ADC_CH7)	return	1024;	//����,����1024,���õĳ����ж�	
	ADC_RES = 0;
	ADC_RESL = 0;

	ADC_CONTR = (ADC_CONTR & 0xe0) | ADC_START | Channel; 
	_nop_();	
    _nop_();	//��ADC_CONTR������Ҫ2T֮����ܷ���

	for(i=0; i<250; i++)		//��ʱ
	{
		if(ADC_CONTR & ADC_FLAG)
		{
			ADC_CONTR &= ~ADC_FLAG;
			if(ADCCFG &  (1<<5))		//10λAD����ĸ�2λ��ADC_RES�ĵ�2λ����8λ��ADC_RESL��
			{
				adc = (unsigned int)(ADC_RES & 3);
				adc = (adc << 8) | ADC_RESL;
			}
			else		//10λAD����ĸ�8λ��ADC_RES����2λ��ADC_RESL�ĵ�2λ��
			{
				adc = (unsigned int)ADC_RES;
				adc = (adc << 2) | (ADC_RESL & 3);
			}
			return	adc;
		}
	}
	return	1024;	//����,����1024,���õĳ����ж�
}

