/**
  ******************************************************************************
  * @file    adc.h
  * @author  sky-vocality(����PineconePi(���ں꾧�Ƽ�STC15�⺯�������޸�))
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
	
#ifndef	__ADC_H
#define	__ADC_H

#include	"system.h"

#define	ADC_P10		0x01	//IO Pin Px.0|IO���� Px.0
#define	ADC_P11		0x02	//IO Pin Px.1|IO���� Px.1
#define	ADC_P12		0x04	//IO Pin Px.2|IO���� Px.2
#define	ADC_P13		0x08	//IO Pin Px.3|IO���� Px.3
#define	ADC_P14		0x10	//IO Pin Px.4|IO���� Px.4
#define	ADC_P15		0x20	//IO Pin Px.5|IO���� Px.5
#define	ADC_P16		0x40	//IO Pin Px.6|IO���� Px.6
#define	ADC_P17		0x80	//IO Pin Px.7|IO���� Px.7
#define	ADC_P1_All	0xFF	//IO All Pin |IO��������

#define ADC_90T		(3<<5)
#define ADC_180T	(2<<5)
#define ADC_360T	(1<<5)
#define ADC_540T	0

#define ADC_CH0		0
#define ADC_CH1		1
#define ADC_CH2		2
#define ADC_CH3		3
#define ADC_CH4		4
#define ADC_CH5		5
#define ADC_CH6		6
#define ADC_CH7		7

#define ADC_RES_H2L8	1
#define ADC_RES_H8L2	0

#define ENABLE  	1			//Enable|����
#define DISABLE  	0			//Disable|�ر�

#define PolityHigh  1	  //PolityHigh|�����ȼ�
#define PolityLow  	0		//PolityLow|�����ȼ���Ĭ�ϣ�

typedef struct
{
	unsigned char	ADC_Px;			//Setting up IO for ADC|����Ҫ��ADC��IO,	ADC_P10 ~ ADC_P17,ADC_P1_All
	unsigned char	ADC_Speed;		//ADC speed|ADC�ٶ�			ADC_90T,ADC_180T,ADC_360T,ADC_540T
	unsigned char	ADC_Power;		//ADC Power Allowance/Shutdown|ADC��������/�ر�	ENABLE,DISABLE
	unsigned char	ADC_AdjResult;	//ADC Result Adjustment|ADC�������,	ADC_RES_H2L8,ADC_RES_H8L2
	unsigned char	ADC_Polity;		//Priority Setting|���ȼ�����	PolityHigh,PolityLow
	unsigned char	ADC_Interrupt;	//Interrupt enable|�ж�����		ENABLE,DISABLE
} ADC_InitTypeDef;

void ADC_Inilize(ADC_InitTypeDef *ADCx);
void ADC_PowerControl(unsigned char Pwr);
unsigned int Get_ADC10bitResult(unsigned char Channel);	//channel = 0~7

#endif
