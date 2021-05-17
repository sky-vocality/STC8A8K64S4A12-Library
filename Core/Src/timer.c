/**
  ******************************************************************************
  * @file    timer.c
  * @author  sky-vocality(����PineconePi(���ں꾧�Ƽ�STC15�⺯�������޸�)�⺯�������޸�)
  * @version V1.0.0
  * @date    11-January-2021
  * @brief  This document is used for timer configuration 
  * @License:GNU General Public License v3.0         
  ******************************************************************************
  * @attention
  *
  *Timer Interrupt Processing Function in timer.c
  *  
  * 
  * 
  * 
  * 
  *
  * 
  ******************************************************************************
**/

#include	"timer.h"
#include "oled.h"

int timer0_num = 0;
int timer1_num = 0;
int timer2_num = 0;
float angle_aim = -1.0;
float follow_aim = 50;

/********************* Timer0 interrupt function|Timer0�жϺ���************************/
void timer0_int (void) interrupt 1
{
	timer0_num++;
	if(timer0_num == 10)
	{
		PID_Control(increment, encoder_num, 160, &wheel_pid);
		wheel_pwm.PWM_Value = wheel_pid.pid_out;
		PWM_PCA_Output(PWM_0,&wheel_pwm);
		//LCD_P6x8Str(0, 0,(unsigned char*)"num:");
		//LCD_Print16(25,0,encoder_num);
		//LCD_P6x8Str(0, 7,(unsigned char*)"val:");
		//LCD_Print16(25,7,wheel_pwm.PWM_Value);
		timer0_num = 0;
		encoder_num = 0;
	}
}

/********************* Timer1 interrupt function|Timer1�жϺ���************************/
void timer1_int (void) interrupt 3
{
	timer1_num++;
	if(timer1_num == 10)
	{
		jy901_update();
		PID_Control(angle, -jy901.Roll, angle_aim, &server_pid);
		server_pwm.PWM_Value = server_pid.pid_out + 78;
		PWM_CLK_Output(PWM_1,&server_pwm);
		timer1_num = 0;
	}
}

/********************* Timer2 interrupt function|Timer2�жϺ���************************/
void timer2_int (void) interrupt 12
{
	timer2_num++;
	if(timer2_num == 40)
	{
		PID_Control(position, LMV358_Output(), follow_aim, &follow_pid);
		angle_aim = follow_pid.pid_out;
		timer2_num = 0;
	}
}


//========================================================================
// Function:unsigned char	Timer_Inilize(unsigned char TIM, TIM_InitTypeDef *TIMx)|����: unsigned char	Timer_Inilize(unsigned char TIM, TIM_InitTypeDef *TIMx)
// Description: Timer initialization program.|����: ��ʱ����ʼ������.
// Parameter: Refer to the structure definition in timer. C|����:  ��ο�timer.c����Ľṹ�嶨��
//       
//       
// Return:|����: 
// Version:VER1.0.0|�汾: VER1.0.0
// Date:2021-01-29|����: 2018-01-29
// Author: sky-vokality|����: sky-vokality
// Note:|��ע:
//	
//	
//	
//	
//	
//========================================================================
unsigned char	Timer_Inilize(unsigned char TIM, TIM_InitTypeDef *TIMx)
{
	if(TIM > Timer2)	return 1;	//Empty operation|�ղ���

	EA = 1;
	
	if(TIM == Timer0)
	{
		TR0 = 0;		//Stop count|ֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE)		ET0 = 1;	//Allowed interruption|�����ж�
		else									ET0 = 0;	//No interruption|��ֹ�ж�
		if(TIMx->TIM_Polity == PolityHigh)		PT0 = 1;	//High priority interrupt|�����ȼ��ж�
		else									PT0 = 0;	//Low priority interrupt|�����ȼ��ж�
		if(TIMx->TIM_Mode >  TIM_16BitAutoReloadNoMask)	return 2;	//Error|����
		TMOD = (TMOD & ~0x03) | TIMx->TIM_Mode;	//Operating mode: 0:16 bit auto-reloading, 1:16 bit timing/counting, 2:8 bit auto-reloading, 3:16 bit auto-reloading, unshieldable interruption|����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ, 3: 16λ�Զ���װ, ���������ж�
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~0x80;	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x80;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x04;	//External Counting or Frequency Division|����������Ƶ
		else										TMOD &= ~0x04;	//timing|��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	INTCLKO |=  0x01;	//Output clock|���ʱ��
		else							INTCLKO &= ~0x01;	//No Clock Output|�����ʱ��
		
		TH0 = (unsigned char)(TIMx->TIM_Value >> 8);
		TL0 = (unsigned char)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR0 = 1;	//Start running|��ʼ����
		return	0;		//�ɹ�
	}

	if(TIM == Timer1)
	{
		TR1 = 0;		//Stop countֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE)		ET1 = 1;	//Allowed interruption|�����ж�
		else									ET1 = 0;	//No interruption|��ֹ�ж�
		if(TIMx->TIM_Polity == PolityHigh)		PT1 = 1;	//High priority interrupt|�����ȼ��ж�
		else									PT1 = 0;	//Low priority interrupt|�����ȼ��ж�
		if(TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return 2;	//error|����
		TMOD = (TMOD & ~0x30) | TIMx->TIM_Mode;	//Work mode, 0:16 bit auto-reloading, 1:16 bit timing/counting, 2:8 bit auto-reloading|����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~0x40;	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x40;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x40;	//External Counting or Frequency Division|����������Ƶ
		else										TMOD &= ~0x40;	//timing|��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	INTCLKO |=  0x02;	//Output clock|���ʱ��
		else							INTCLKO &= ~0x02;	//No Clock Output|�����ʱ��
		
		TH1 = (unsigned char)(TIMx->TIM_Value >> 8);
		TL1 = (unsigned char)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR1 = 1;	//Start running|��ʼ����
		return	0;		//success|�ɹ�
	}

	if(TIM == Timer2)		//Timer2,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		AUXR &= ~(1<<4);	//Stop countֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE)			IE2  |=  (1<<2);	//Allowed interruption|�����ж�
		else										IE2  &= ~(1<<2);	//No interruption|��ֹ�ж�
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~(1<<2);	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  (1<<2);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	AUXR |=  (1<<3);	//External Counting or Frequency Division|����������Ƶ
		else										AUXR &= ~(1<<3);	//timing|��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	INTCLKO |=  0x04;	//Output clock|���ʱ��
		else							INTCLKO &= ~0x04;	//No Clock Output|�����ʱ��

		TH2 = (unsigned char)(TIMx->TIM_Value >> 8);
		TL2 = (unsigned char)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	AUXR |=  (1<<4);	//Start running|��ʼ����
		return	0;		//success|�ɹ�
	}
	return 2;	//Error|����
}
