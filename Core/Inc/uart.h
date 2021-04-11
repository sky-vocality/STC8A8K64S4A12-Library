/**
  ******************************************************************************
  * @file    uart.h
  * @author  sky-vocality(����PineconePi(���ں꾧�Ƽ�STC15�⺯�������޸�)�⺯�������޸�)
  * @version V1.0.1
  * @date    28-January-2020
  * @brief  This file is used to configure the serial port 
  * @License:GNU General Public License v3.0         
  ******************************************************************************
  * @attention
  *
  *Serial Interrupt Processing Function in uart.c 
  *  
  * 
  * 
  * 
  * 
  *
  * 
  ******************************************************************************
**/
#ifndef __UART_H
#define __UART_H	 

#include	"system.h"

#define	COM_TX1_Lenth	11
#define	COM_RX1_Lenth	11
#define	COM_TX2_Lenth	11
#define	COM_RX2_Lenth	11

#define	USART1	1
#define	USART2	2

#define	UART_ShiftRight	0		//Synchronized shift output|ͬ����λ���
#define	UART_8bit_BRTx	(1<<6)	//8-bit data, variable baud rate|8λ����,�ɱ䲨����
#define	UART_9bit		(2<<6)	//9-bit data, fixed baud rate|9λ����,�̶�������
#define	UART_9bit_BRTx	(3<<6)	//9-bit data, variable baud rate|9λ����,�ɱ䲨����

#define	UART1_SW_P30_P31	0
#define	UART1_SW_P36_P37	(1<<6)
#define	UART1_SW_P16_P17	(2<<6)	//Internal clock must be used|����ʹ���ڲ�ʱ��
#define	UART2_SW_P10_P11	0
#define	UART2_SW_P46_P47	1


#define	TimeOutSet1		5
#define	TimeOutSet2		5

#define	BRT_Timer1	1
#define	BRT_Timer2	2

#define ENABLE  	1			//����
#define DISABLE  	0			//�ر�

#define PolityHigh  1	  //High priority|�����ȼ�
#define PolityLow  	0		//Low priority (default)|�����ȼ���Ĭ�ϣ�

typedef struct
{ 
	unsigned char	id;				//Serial port number|���ں�

	unsigned char	TX_read;		//Send Read Pointer|���Ͷ�ָ��
	unsigned char	TX_write;		//Send Write Pointer|����дָ��
	unsigned char	B_TX_busy;		//Busy signæ��־

	unsigned char 	RX_Cnt;			//Received byte count|�����ֽڼ���
	unsigned char	RX_TimeOut;		//Receiving timeout|���ճ�ʱ
	unsigned char	B_RX_OK;		//Receiving Block Completion|���տ����
} COMx_Define; 

typedef struct
{ 
	unsigned char	UART_Mode;			//Pattern|ģʽ,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	unsigned char	UART_BRT_Use;		//Using baud rate|ʹ�ò�����,   BRT_Timer1,BRT_Timer2
	unsigned long	UART_BaudRate;		//baud rate|������,       ENABLE,DISABLE
	unsigned char	Morecommunicate;	//Multiprocessor Communication Allowance|���ͨѶ����, ENABLE,DISABLE
	unsigned char	UART_RxEnable;		//Allow reception|�������,   ENABLE,DISABLE
	unsigned char	BaudRateDouble;		//Baud rate doubled|�����ʼӱ�, ENABLE,DISABLE
	unsigned char	UART_Interrupt;		//Interrupt control|�жϿ���,   ENABLE,DISABLE
	unsigned char	UART_Polity;		//priority|���ȼ�,     PolityLow,PolityHigh
	unsigned char	UART_P_SW;			//Switch port|�л��˿�,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17(����ʹ���ڲ�ʱ��)
} COMx_InitDefine; 

extern	COMx_Define	COM1,COM2;
extern	unsigned char	xdata TX1_Buffer[COM_TX1_Lenth];	//Send buffer|���ͻ���
extern	unsigned char 	xdata RX1_Buffer[COM_RX1_Lenth];	//Receive buffer|���ջ���
extern	unsigned char	xdata TX2_Buffer[COM_TX2_Lenth];	//Send buffer|���ͻ���
extern	unsigned char 	xdata RX2_Buffer[COM_RX2_Lenth];	//Receive buffer|���ջ���

unsigned char	USART_Configuration(unsigned char UARTx, COMx_InitDefine *COMx);
void TX1_write2buff(unsigned char dat);	//Write send buffer, pointer + 1|д�뷢�ͻ��壬ָ��+1
void TX2_write2buff(unsigned char dat);	//Write send buffer, pointer + 1|д�뷢�ͻ��壬ָ��+1
void PrintString1(unsigned char *puts); //TX1 send string|TX1�����ַ���
void PrintString2(unsigned char *puts); //TX2 send string|TX2�����ַ���

unsigned char ReceiveByte1(void);
unsigned char ReceiveByte2(void);

void intToString(int N,char arr[]);
void floatToString(float N,char arr[], int n);

#endif

