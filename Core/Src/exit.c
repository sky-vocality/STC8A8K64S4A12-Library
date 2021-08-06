/**
  ******************************************************************************
  * @file    exti.c
  * @author  sky-vocality(����PineconePi(���ں꾧�Ƽ�STC15�⺯�������޸�)�⺯�������޸�)
  * @version V1.0.0
  * @date    20-January-2021
  * @brief  This file is used for external interrupt configuration
  * @License:GNU General Public License v3.0         
  ******************************************************************************
  * @attention
  * �ں�PAC�ж�
  * Embedded PAC interrupt.
  *  
  * 
  * 
  * 
  * 
  *
  * 
  ******************************************************************************
**/

#include "exit.h"

int encoder_num = 0;
int encoder_num_l = 0;

/********************* INT0 interrupt function|INT0�жϺ��� *************************/
void Ext_INT0 (void) interrupt EXT_INT0		//The sign has been cleared when entering or interrupting|���ж�ʱ�Ѿ������־
{
	//Add user logic here|�˴�����û��߼�
}

/********************* INT1 interrupt function|INT1�жϺ��� *************************/
void Ext_INT1 (void) interrupt EXT_INT1		//The sign has been cleared when entering or interrupting|���ж�ʱ�Ѿ������־
{
	//Add user logic here|�˴�����û��߼�
}

/********************* INT2 interrupt function|INT2�жϺ��� *************************/
void Ext_INT2 (void) interrupt EXT_INT2	//
{
	//Add user logic here|�˴�����û��߼�
}

/********************* INT3 interrupt function|INT3�жϺ��� *************************/
void Ext_INT3 (void) interrupt EXT_INT3
{
	//Add user logic here|�˴�����û��߼�
}

/********************* INT4 interrupt function|INT4�жϺ��� *************************/
void Ext_INT4 (void) interrupt EXT_INT4
{
	//Add user logic here|�˴�����û��߼�
}

/********************* PCA Interrupt Handling Function|PCA??????************************/
void	PCA_Ext (void) interrupt PCA_INT0
{
	if(CCF0)		//PCA module 0 interrupt|PCA??0??
	{
		CCF0 = 0;		//Clear PCA module 0 interrupt flag|?PCA??0????
	}

	if(CCF1)	//PCA Module 1 Interruption|PCA??1??
	{
		CCF1 = 0;		//Clear the interrupt flag in PCA module 1|?PCA??1????
	}

	if(CCF2)	//PCA Module 2 Interruption|PCA??2??
	{
		CCF2 = 0;		//Clear the interrupt flag in PCA module 2|?PCA??2????
	}

		if(CCF3)	//PCA Module 3 Interruption|PCA??3??
	{
		CCF3 = 0;		//Clear the interrupt flag in PCA module 3|?PCA??3????
	}
}

//========================================================================
// Function:unsigned char Ext_Inilize(unsigned char EXT, EXTI_InitTypeDef *INTx)|����: unsigned char Ext_Inilize(unsigned char EXT, EXTI_InitTypeDef *INTx)
// Description:External interrupt initializer|����: �ⲿ�жϳ�ʼ������.
// Parameter:EXT,Interrupt sequence number��EXT_INT0��External interrupt 0 , EXT_INT1��External interrupt 1 , EXT_INT2��External interrupt 2 , 
//                                          EXT_INT3��External interrupt 3 �� EXT_INT4��External interrupt 4)
// ����: EXT,�ж���ţ�EXT_INT0���ⲿ�ж�0 , EXT_INT1���ⲿ�ж�1 , EXT_INT2���ⲿ�ж�2 , 
//       EXT_INT3���ⲿ�ж�3 �� EXT_INT4���ⲿ�ж�4)
//       INTx: �ṹ����,��ο�Exti.h��Ķ���.
// Return:Successful return 0, empty return 1, error return 2.|����: �ɹ�����0, �ղ�������1,���󷵻�2.
// Version:VER1.0.0|�汾: VER1.0.0
// Date:2018-12-20|����: 2018-12-20
// Note: Enable INT0 by following steps
//	EXTI_InitTypeDef EXTI_InitTypeDef;
//	EXTI_InitTypeDef.EXTI_Mode = EXT_MODE_RiseFall;//Rising edge interruption
//	EXTI_InitTypeDef.EXTI_Polity = PolityHigh;//High priority|�����ȼ�
//	EXTI_InitTypeDef.EXTI_Interrupt = ENABLE;//Enable|ʹ��
//	Ext_Inilize(EXT_INT0,&EXTI_InitTypeDef);//Complete configuration|�������
// ��ע: ͨ�����²���ʹ��INT0
//	EXTI_InitTypeDef EXTI_InitTypeDef;
//	EXTI_InitTypeDef.EXTI_Mode = EXT_MODE_RiseFall;//�������ж�
//	EXTI_InitTypeDef.EXTI_Polity = PolityHigh;//�����ȼ�
//	EXTI_InitTypeDef.EXTI_Interrupt = ENABLE;//ʹ��
//	Ext_Inilize(EXT_INT0,&EXTI_InitTypeDef);//�������
//========================================================================
unsigned char Ext_Inilize(unsigned char EXT, EXTI_InitTypeDef *INTx)
{
	if(EXT >  EXT_INT4)	return 1;	//Empty operation|�ղ���
	
	EA = 1;
	
	if(EXT == EXT_INT0)	//External interrupt 0|���ж�0
	{
		if(INTx->EXTI_Interrupt == ENABLE)		EX0 = 1;	//Allowed interruption|�����ж�
		else									EX0 = 0;	//No interruption|��ֹ�ж�
		if(INTx->EXTI_Polity == PolityHigh)		PX0 = 1;	//High priority interrupt|�����ȼ��ж�
		else									PX0 = 0;	//Low priority interrupt|�����ȼ��ж�
		if(INTx->EXTI_Mode == EXT_MODE_Fall)	IT0 = 1;	//Falling edge interruption|�½����ж�
		else									IT0 = 0;	//Rise, fall and interrupt|����,�½����ж�
		return	0;		//Success|�ɹ�
	}

	if(EXT == EXT_INT1)	//External interrupt 1|���ж�1
	{
		if(INTx->EXTI_Interrupt == ENABLE)		EX1 = 1;	//Allowed interruption|�����ж�
		else									EX1 = 0;	//No interruption|��ֹ�ж�
		if(INTx->EXTI_Polity == PolityHigh)		PX1 = 1;	//High priority interrupt|�����ȼ��ж�
		else									PX1 = 0;	//Low priority interrupt|�����ȼ��ж�
		if(INTx->EXTI_Mode == EXT_MODE_Fall)	IT1 = 1;	//Falling edge interruption|�½����ж�
		else									IT1 = 0;	//Rise, fall and interrupt|����,�½����ж�
		return	0;		//Success|�ɹ�
	}

	if(EXT == EXT_INT2)		//Outer interrupt 2, fixed to lower priority interrupt|���ж�2, �̶�Ϊ�½��ص����ȼ��ж�
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INTCLKO |=  (1 << 4);	//Allowed interruption|�����ж�	
		else								INTCLKO &= ~(1 << 4);	//No interruption|��ֹ�ж�
		return	0;		//Success|�ɹ�
	}

	if(EXT == EXT_INT3)		//Outer interrupt 3, fixed to lower priority interrupt|���ж�3, �̶�Ϊ�½��ص����ȼ��ж�
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INTCLKO |=  (1 << 5);	//Allowed interruption|�����ж�	
		else								INTCLKO &= ~(1 << 5);	//No interruption|��ֹ�ж�
		return	0;		//Success|�ɹ�
	}

	if(EXT == EXT_INT4)		//External interrupt 4, fixed to lower priority interrupt|���ж�4, �̶�Ϊ�½��ص����ȼ��ж�
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INTCLKO |=  (1 << 6);	//Allowed interruption|�����ж�	
		else								INTCLKO &= ~(1 << 6);	//No interruption|��ֹ�ж�
		return	0;		//Success|�ɹ�
	}

	if(EXT == PCA_INT0)		//External interrupt 4, fixed to lower priority interrupt|���ж�4, �̶�Ϊ�½��ص����ȼ��ж�
	{
		CCON = 0x00;
		CMOD = 0x0d;
		CL = 0x00;
		CH = 0x00;
		if (INTx->EXTI_Mode == EXT_MODE_Fall)  CCAPM0 = 0x11;
		else CCAPM0 = 0x21;
		CCAP0L = 0;
		CCAP0H = 0;
		CR = 1;
		return	0;		//Success|�ɹ�
	}

	if(EXT == PCA_INT1)
	{
		CCON = 0x00;
		CMOD = 0x0d;
		CL = 0x00;
		CH = 0x00;
		if (INTx->EXTI_Mode == EXT_MODE_Fall)  CCAPM1 = 0x11;
		else CCAPM1 = 0x21;
		CCAP1L = 0;
		CCAP1H = 0;
		CR = 1;
		return	0;		//Success|�ɹ�
	}

	if(EXT == PCA_INT2)
	{
		CCON = 0x00;
		CMOD = 0x0d;
		CL = 0x00;
		CH = 0x00;
		if (INTx->EXTI_Mode == EXT_MODE_Fall)  CCAPM2 = 0x11;
		else CCAPM2 = 0x21;
		CCAP2L = 0;
		CCAP2H = 0;
		CR = 1;
		return	0;		//Success|�ɹ�
	}

	if(EXT == PCA_INT3)
	{
		CCON = 0x00;
		CMOD = 0x0d;
		CL = 0x00;
		CH = 0x00;
		if (INTx->EXTI_Mode == EXT_MODE_Fall)  CCAPM3 = 0x11;
		else CCAPM0 = 0x21;
		CCAP3L = 0;
		CCAP3H = 0;
		CR = 1;
		return	0;		//Success|�ɹ�
	}
	return 2;	//fail|ʧ��
}