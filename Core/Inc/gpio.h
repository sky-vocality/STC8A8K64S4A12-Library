/**
  ******************************************************************************
  * @file    gpio.h
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
#ifndef	__GPIO_H_
#define	__GPIO_H_

#include	"system.h"

#define	GPIO_PullUp		0	//Up-pull quasi-bidirectional port (default)|����׼˫���(Ĭ��)
#define	GPIO_HighZ		1	//Floating input|��������
#define	GPIO_OUT_OD		2	//Open drain output|��©���
#define	GPIO_OUT_PP		3	//push-pull|�������

#define	GPIO_Pin_0		0x01	//IO pin Px.0|IO���� Px.0
#define	GPIO_Pin_1		0x02	//IO pin Px.1|IO���� Px.1
#define	GPIO_Pin_2		0x04	//IO pin Px.2|IO���� Px.2
#define	GPIO_Pin_3		0x08	//IO pin Px.3|IO���� Px.3
#define	GPIO_Pin_4		0x10	//IO pin Px.4|IO���� Px.4
#define	GPIO_Pin_5		0x20	//IO pin Px.5|IO���� Px.5
#define	GPIO_Pin_6		0x40	//IO pin Px.6|IO���� Px.6
#define	GPIO_Pin_7		0x80	//IO pin Px.7|IO���� Px.7
#define	GPIO_Pin_All	0xFF	//IO All pin |IO��������
	
#define	GPIO_P0			0		
#define	GPIO_P1			1
#define	GPIO_P2			2
#define	GPIO_P3			3
#define	GPIO_P4			4
#define	GPIO_P5			5

//========================================================================
// Structures: GPIO_InitTypeDef|�ṹ��: GPIO_InitTypeDef
// Description: GPIO configuration structure.|����: GPIO���ýṹ�塣
// Parameters: Mode, IO mode (GPIO_PullUp: pull-up quasi-bidirectional port, GPIO_HighZ: floating input, GPIO_OUT_OD: leak-out output, GPIO_OUT_PP: push-pull output)
//			 Pin, port, (GPIO_Pin_0: IO pin Px.0, PIO_Pin_1: IO pin Px.1, PIO_Pin_2: IO pin Px.2, PIO_Pin_3: IO pin Px.3,
// 			 PIO_Pin_4: IO pin Px.4, PIO_Pin_5: IO pin Px.5, PIO_Pin_6: IO pin Px.6, PIO_Pin_7: IO pin Px.7,
//			 PIO_Pin_All:IO All Pins 
// ����: Mode,IOģʽ��GPIO_PullUp������׼˫��� , GPIO_HighZ���������� , GPIO_OUT_OD����©��� , GPIO_OUT_PP���������
//			 Pin,�˿�,(GPIO_Pin_0 ��IO���� Px.0 ��PIO_Pin_1 ��IO���� Px.1 ��PIO_Pin_2 ��IO���� Px.2 ��PIO_Pin_3 ��IO���� Px.3 ��
// 			 PIO_Pin_4 ��IO���� Px.4 ��PIO_Pin_5 ��IO���� Px.5 ��PIO_Pin_6 ��IO���� Px.6 ��PIO_Pin_7 ��IO���� Px.7 ��
//			 PIO_Pin_All ��IO�������� 
// Return: none|����: none.
// Version: VER1.0.0|�汾: VER1.0.0
// Date: 2018-12-20|����: 2018-12-20
// Note: Set P ^ 0 to two-way port by following steps
// GPIO_InitTypeDef GPIO_InitTypeDef;
// GPIO_InitTypeDef.Mode = GPIO_PullUp; //Up-pull quasi-bidirectional ports
// GPIO_InitTypeDef.Pin = GPIO_Pin_0 | GPIO_Pin_1; // Configure both IO pins Px.0 and Px.1
// GPIO_Inilize (GPIO_P, &amp; GPIO_InitTypeDef); //IO pin P 0.0
// ��ע: ͨ�����²��轫P0^0����Ϊ����׼˫���
//     GPIO_InitTypeDef GPIO_InitTypeDef;
//		 GPIO_InitTypeDef.Mode = GPIO_PullUp;//����׼˫���
//     GPIO_InitTypeDef.Pin = GPIO_Pin_0|GPIO_Pin_1;//ͬʱ����IO���� Px.0��Px.1
//		 GPIO_Inilize(GPIO_P0 ,&GPIO_InitTypeDef);//IO���� P0.0
//========================================================================
typedef struct
{
	unsigned char	Mode;		//IO Mode|IOģʽ
	unsigned char	Pin;		//Port|�˿�	
} GPIO_InitTypeDef;

unsigned char	GPIO_Inilize(unsigned char GPIO, GPIO_InitTypeDef *GPIOx);

#endif