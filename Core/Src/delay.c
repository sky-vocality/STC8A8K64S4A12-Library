/**
  ******************************************************************************
  * @file    Delay.c
  * @author  sky-vocality(����PineconePi(���ں꾧�Ƽ�STC15�⺯�������޸�)�⺯�������޸�)
  * @version V1.0.0
  * @date    20-January-2021
  * @brief  This file is used to complete software Delay
  * @License:GNU General Public License v3.0         
  ******************************************************************************
  * @attention
  *The frequency of crystal oscillator is 24 Mhz
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
#include "delay.h"
#include "Intrins.h"
//========================================================================
// Function:void Delay_Ms(unsigned int ms)|����: void Delay_Ms(unsigned int ms)
// Description:Delay Function|����: ��ʱ������
// Parameter:Ms, the number of MS to be delayed, where only 1-10000 (10s) MS is supported|����: Ms,Ҫ��ʱ��ms��, ����ֻ֧��1~10000 (10s) ms
// Return:none|����: none.
// Version VER1.0.0|�汾: VER1.0.0
// Date:2018-12-20|����: 2018-12-20
// Note:delay_ms(1000);//Delay 1s|��ע: delay_ms(1000);//�ӳ�1s
//========================================================================
void Delay_Ms(unsigned int Ms){
  unsigned int k;
	unsigned char i, j;
	for(k=0;k<Ms;k++)
	{
	_nop_();
	i = 32;
	j = 40;
		do
		{
		  while (--j);
		} while (--i);
	}}
//========================================================================
// Function:Delay_Us(unsigned int Us)|����: Delay_Us(unsigned int Us)
// Description:Delay Function|����: ��ʱ������
// Parameter:Us, the number of us delays, where only 1-10000 (10ms) us is supported|����: Us,Ҫ��ʱ��us��, ����ֻ֧��1~10000 (10ms) us
// Return:none|����: none.
// Version:VER1.0.0|�汾: VER1.0.0
// Date:2018-12-20|����: 2018-12-20
// Note:delay_us(1000);//delay 1ms|��ע: delay_us(1000);//�ӳ�1ms
//========================================================================
void Delay_Us(unsigned int Us){
  unsigned int k;
	unsigned char i;
	for(k=0;k<Us;k++)
	{
	i = 6;
	while (--i);
	}
}
