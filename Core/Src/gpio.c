/**
  ******************************************************************************
  * @file    gpio.c
  * @author  sky-vocality(����PineconePi(���ں꾧�Ƽ�STC15�⺯�������޸�)�⺯�������޸�)
  * @version V1.0.0
  * @date    20-January-2021
  * @brief  This document is used for GPIO configuration
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
	
#include	"gpio.h"


//========================================================================
// Function:unsigned char	GPIO_Inilize(unsigned char GPIO, GPIO_InitTypeDef *GPIOx)|����: unsigned char	GPIO_Inilize(unsigned char GPIO, GPIO_InitTypeDef *GPIOx)
// Description:Initialize the IO port.|����: ��ʼ��IO��.
// Parameter: GPIO��GPIO_P0:P0 pins (8)��GPIO_P1:P1 pins (8)��GPIO_P2:P2 pins (8)��GPIO_P3:P3 pins (8)��
//             GPIO_P4:P4 pins (8)��GPIO_P5:P5 pins (8)��
//			   GPIOx: For structural parameters, please refer to the structure description in gpio.h..
// ����: GPIO��GPIO_P0:P0���ţ�8������GPIO_P1:P1���ţ�8������GPIO_P2:P2���ţ�8������GPIO_P3:P3���ţ�8������
//             GPIO_P4:P4���ţ�8������GPIO_P5:P5���ţ�8������
//       GPIOx: �ṹ����,��ο�gpio.h��Ľṹ��˵��.
// Return:Successful return 0, empty return 1, error return 2.|����: �ɹ�����0, �ղ�������1,���󷵻�2.
// Version:VER1.0.0|�汾: VER1.0.0
// Date:2018-12-20|����: 2018-12-20
// Note: Set P ^ 0 and P ^ 1 as up-pull quasi-bidirectional ports by following steps
//       GPIO_InitTypeDef GPIO_InitTypeDef;
//		 GPIO_InitTypeDef.Mode = GPIO_PullUp;//Up-drawing alignment bi-directional port
//       GPIO_InitTypeDef.Pin = GPIO_Pin_0|GPIO_Pin_1;//Configuration of IO pins Px.0 and Px.1 at the same time.1
//		 GPIO_Inilize(GPIO_P0 ,&GPIO_InitTypeDef);//IO pin P 0.0
// ��ע: ͨ�����²��轫P0^0��P0^1����Ϊ����׼˫���
//       GPIO_InitTypeDef GPIO_InitTypeDef;
//		 GPIO_InitTypeDef.Mode = GPIO_PullUp;//����׼˫���
//       GPIO_InitTypeDef.Pin = GPIO_Pin_0|GPIO_Pin_1;//ͬʱ����IO���� Px.0��Px.1
//		 GPIO_Inilize(GPIO_P0 ,&GPIO_InitTypeDef);//IO���� P0.0
//========================================================================
unsigned char	GPIO_Inilize(unsigned char GPIO, GPIO_InitTypeDef *GPIOx)
{
	if(GPIO > GPIO_P5)				return 1;	//Empty operation
	if(GPIOx->Mode > GPIO_OUT_PP)	return 2;	//error
	if(GPIO == GPIO_P0)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P0M1 &= ~GPIOx->Pin,	P0M0 &= ~GPIOx->Pin;	 //Up-drawing alignment bi-directional port|����׼˫���
		if(GPIOx->Mode == GPIO_HighZ)		P0M1 |=  GPIOx->Pin,	P0M0 &= ~GPIOx->Pin;	 //Floating input|��������
		if(GPIOx->Mode == GPIO_OUT_OD)		P0M1 |=  GPIOx->Pin,	P0M0 |=  GPIOx->Pin;	 //Open drain output|��©���
		if(GPIOx->Mode == GPIO_OUT_PP)		P0M1 &= ~GPIOx->Pin,	P0M0 |=  GPIOx->Pin;	 //push-pull|�������
	}
	if(GPIO == GPIO_P1)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P1M1 &= ~GPIOx->Pin,	P1M0 &= ~GPIOx->Pin;	 //Up-drawing alignment bi-directional port|����׼˫���
		if(GPIOx->Mode == GPIO_HighZ)		P1M1 |=  GPIOx->Pin,	P1M0 &= ~GPIOx->Pin;	 //Floating input|��������
		if(GPIOx->Mode == GPIO_OUT_OD)		P1M1 |=  GPIOx->Pin,	P1M0 |=  GPIOx->Pin;	 //Open drain output|��©���
		if(GPIOx->Mode == GPIO_OUT_PP)		P1M1 &= ~GPIOx->Pin,	P1M0 |=  GPIOx->Pin;	 //push-pull|�������
	}
	if(GPIO == GPIO_P2)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P2M1 &= ~GPIOx->Pin,	P2M0 &= ~GPIOx->Pin;	 //Up-drawing alignment bi-directional port|����׼˫���
		if(GPIOx->Mode == GPIO_HighZ)		P2M1 |=  GPIOx->Pin,	P2M0 &= ~GPIOx->Pin;	 //Floating input|��������
		if(GPIOx->Mode == GPIO_OUT_OD)		P2M1 |=  GPIOx->Pin,	P2M0 |=  GPIOx->Pin;	 //Open drain output|��©���
		if(GPIOx->Mode == GPIO_OUT_PP)		P2M1 &= ~GPIOx->Pin,	P2M0 |=  GPIOx->Pin;	 //push-pull|�������
	}
	if(GPIO == GPIO_P3)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P3M1 &= ~GPIOx->Pin,	P3M0 &= ~GPIOx->Pin;	 //Up-drawing alignment bi-directional port|����׼˫���
		if(GPIOx->Mode == GPIO_HighZ)		P3M1 |=  GPIOx->Pin,	P3M0 &= ~GPIOx->Pin;	 //Floating input|��������
		if(GPIOx->Mode == GPIO_OUT_OD)		P3M1 |=  GPIOx->Pin,	P3M0 |=  GPIOx->Pin;	 //Open drain output|��©���
		if(GPIOx->Mode == GPIO_OUT_PP)		P3M1 &= ~GPIOx->Pin,	P3M0 |=  GPIOx->Pin;	 //push-pull|�������
	}
	if(GPIO == GPIO_P4)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P4M1 &= ~GPIOx->Pin,	P4M0 &= ~GPIOx->Pin;	 //Up-drawing alignment bi-directional port|����׼˫���
		if(GPIOx->Mode == GPIO_HighZ)		P4M1 |=  GPIOx->Pin,	P4M0 &= ~GPIOx->Pin;	 //Floating input|��������
		if(GPIOx->Mode == GPIO_OUT_OD)		P4M1 |=  GPIOx->Pin,	P4M0 |=  GPIOx->Pin;	 //Open drain output|��©���
		if(GPIOx->Mode == GPIO_OUT_PP)		P4M1 &= ~GPIOx->Pin,	P4M0 |=  GPIOx->Pin;	 //push-pull|�������
	}
	if(GPIO == GPIO_P5)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P5M1 &= ~GPIOx->Pin,	P5M0 &= ~GPIOx->Pin;	 //Up-drawing alignment bi-directional port|����׼˫���
		if(GPIOx->Mode == GPIO_HighZ)		P5M1 |=  GPIOx->Pin,	P5M0 &= ~GPIOx->Pin;	 //Floating input|��������
		if(GPIOx->Mode == GPIO_OUT_OD)		P5M1 |=  GPIOx->Pin,	P5M0 |=  GPIOx->Pin;	 //Open drain output|��©���
		if(GPIOx->Mode == GPIO_OUT_PP)		P5M1 &= ~GPIOx->Pin,	P5M0 |=  GPIOx->Pin;	 //push-pull|�������
	}
	return 0;	//Success|�ɹ�
}
