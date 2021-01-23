/**
  ******************************************************************************
  * @file    uart.c
  * @author  PineconePi(基于宏晶科技STC15库函数进行修改)
  * @version V1.0.0
  * @date    20-December-2018
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
#include "uart.h"
#include "delay.h"
#include "gpio.h"

COMx_Define	COM1,COM2;
unsigned char	xdata TX1_Buffer[COM_TX1_Lenth];	//Send buffer
unsigned char 	xdata RX1_Buffer[COM_RX1_Lenth];	//Receive buffer
unsigned char	xdata TX2_Buffer[COM_TX2_Lenth];	//Send buffer
unsigned char 	xdata RX2_Buffer[COM_RX2_Lenth];	//Receive buffer

//========================================================================
// Function:void CLR_RTI2()
// Description:Label Clearance
// Parameter:
//       
//       
// Return: 
// Version:VER1.0.0
// Date:2018-12-20
// Author: Pinecone Pi
//	
//	
//	
//	
//	
//========================================================================
void CLR_RTI2()
{
	if (S2CON & 0x02)
    {
        S2CON &= ~0x02;                         //Clear interruption sign
    }
    if (S2CON & 0x01)
    {
        S2CON &= ~0x01;                         //Clear interruption sign
    }
}


/********************* Interrupt function in UART2|UART2中断************************/
void UART2_int (void) interrupt 8
{
	if(S2RI)
	{
		CLR_RTI2();
		if(COM2.B_RX_OK == 0)
		{
			if(COM2.RX_Cnt >= COM_RX2_Lenth)	COM2.RX_Cnt = 0;
			RX2_Buffer[COM2.RX_Cnt++] = S2BUF;
			COM2.RX_TimeOut = TimeOutSet2;
		}
	}

	if(S2TI)
	{
		CLR_RTI2();
		if(COM2.TX_read != COM2.TX_write)
		{
			S2BUF = TX2_Buffer[COM2.TX_read];
			if(++COM2.TX_read >= COM_TX2_Lenth)		COM2.TX_read = 0;
		}
		else	COM2.B_TX_busy = 0;
	}

}

//========================================================================
// Function:unsigned char USART_Configuration(unsigned char UARTx, COMx_InitDefine *COMx)|函数: unsigned char USART_Configuration(unsigned char UARTx, COMx_InitDefine *COMx)
// Description:Serial port initialization program.|描述: 串口初始化程序.
// Parameter:Refer to the structure definition in uart. C.|参数:  请参考uart.c里面的结构体定义
//       
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2018-12-20|日期: 2018-12-20
// Author: Pinecone Pi|作者: PineconePi
// Note:|备注:
//	
//	
//	
//	
//	
//========================================================================
unsigned char USART_Configuration(unsigned char UARTx, COMx_InitDefine *COMx)
{
	unsigned char	i;
	unsigned long	j;
	
	if(UARTx == USART1)
	{
		COM1.id = 1;
		COM1.TX_read    = 0;
		COM1.TX_write   = 0;
		COM1.B_TX_busy  = 0;
		COM1.RX_Cnt     = 0;
		COM1.RX_TimeOut = 0;
		COM1.B_RX_OK    = 0;
		for(i=0; i<COM_TX1_Lenth; i++)	TX1_Buffer[i] = 0;
		for(i=0; i<COM_RX1_Lenth; i++)	RX1_Buffer[i] = 0;

		if(COMx->UART_Mode > UART_9bit_BRTx)	return 2;	//Mode error|模式错误
		if(COMx->UART_Polity == PolityHigh)		PS = 1;	//High priority interrupt|高优先级中断
		else									PS = 0;	//Low priority interrupt|低优先级中断
		SCON = (SCON & 0x3f) | COMx->UART_Mode;
		if((COMx->UART_Mode == UART_9bit_BRTx) ||(COMx->UART_Mode == UART_8bit_BRTx))	//Variable baud rate|可变波特率
		{
			j = (MAIN_Fosc / 4) / COMx->UART_BaudRate;	//Calculate by 1T|按1T计算
			if(j >= 65536UL)	return 2;	//Error|错误
			j = 65536UL - j;
			if(COMx->UART_BRT_Use == BRT_Timer1)
			{
				TR1 = 0;
				AUXR &= ~0x01;		//S1 BRT Use Timer1;
				TMOD &= ~(1<<6);	//Timer1 set As Timer
				TMOD &= ~0x30;		//Timer1_16bitAutoReload;
				AUXR |=  (1<<6);	//Timer1 set as 1T mode
				TH1 = (unsigned char)(j>>8);
				TL1 = (unsigned char)j;
				ET1 = 0;	//No interruption|禁止中断
				TMOD &= ~0x40;	//timing|定时
				INTCLKO &= ~0x02;	//No Clock Output|不输出时钟
				TR1  = 1;
			}
			else if(COMx->UART_BRT_Use == BRT_Timer2)
			{
				AUXR &= ~(1<<4);	//Timer stop
				AUXR |= 0x01;		//S1 BRT Use Timer2;
				AUXR &= ~(1<<3);	//Timer2 set As Timer
				AUXR |=  (1<<2);	//Timer2 set as 1T mode
				TH2 = (unsigned char)(j>>8);
				TL2 = (unsigned char)j;
				IE2  &= ~(1<<2);	//No interruption|禁止中断
				AUXR &= ~(1<<3);	//timing|定时
				AUXR |=  (1<<4);	//Timer run enable
			}
			else return 2;	//Error|错误
		}
		else if(COMx->UART_Mode == UART_ShiftRight)
		{
			if(COMx->BaudRateDouble == ENABLE)	AUXR |=  (1<<5);	//Fixed baud rate SysClk/2|固定波特率SysClk/2
			else								AUXR &= ~(1<<5);	//Fixed baud rate SysClk/12|固定波特率SysClk/12
		}
		else if(COMx->UART_Mode == UART_9bit)	//Fixed baud rate SysClk*2^SMOD/64 |固定波特率SysClk*2^SMOD/64
		{
			if(COMx->BaudRateDouble == ENABLE)	PCON |=  (1<<7);	//Fixed baud rate SysClk/32|固定波特率SysClk/32
			else								PCON &= ~(1<<7);	//Fixed baud rate SysClk/64|固定波特率SysClk/64
		}
		if(COMx->UART_Interrupt == ENABLE)	ES = 1;	//Allowed interruption|允许中断
		else								ES = 0;	//No interruption|禁止中断
		if(COMx->UART_RxEnable == ENABLE)	REN = 1;	//Allow reception|允许接收
		else								REN = 0;	//No acceptance|禁止接收
		
		if(COMx->UART_P_SW == UART1_SW_P30_P31)
		{
			GPIO_InitTypeDef GPIO_InitTypeDef;
			GPIO_InitTypeDef.Mode = GPIO_OUT_PP;
			GPIO_InitTypeDef.Pin = GPIO_Pin_1;//配置IO引脚 Px.1
			GPIO_Inilize(GPIO_P3 ,&GPIO_InitTypeDef);//IO引脚 P3.1
		}
		else if(COMx->UART_P_SW == UART1_SW_P16_P17)
		{
			GPIO_InitTypeDef GPIO_InitTypeDef;
			GPIO_InitTypeDef.Mode = GPIO_OUT_PP;
			GPIO_InitTypeDef.Pin = GPIO_Pin_7;//配置IO引脚 Px.7
			GPIO_Inilize(GPIO_P1 ,&GPIO_InitTypeDef);//IO引脚 P1.7
		}
		else
		{
			GPIO_InitTypeDef GPIO_InitTypeDef;
			GPIO_InitTypeDef.Mode = GPIO_OUT_PP;
			GPIO_InitTypeDef.Pin = GPIO_Pin_7;//配置IO引脚 Px.7
			GPIO_Inilize(GPIO_P3 ,&GPIO_InitTypeDef);//IO引脚 P3.7
		}
		P_SW1 = (P_SW1 & 0x3f) | (COMx->UART_P_SW & 0xc0);	//Switch IO|切换IO
		return	0;
	}

	if(UARTx == USART2)
	{
		COM2.id = 2;
		COM2.TX_read    = 0;
		COM2.TX_write   = 0;
		COM2.B_TX_busy  = 0;
		COM2.RX_Cnt     = 0;
		COM2.RX_TimeOut = 0;
		COM2.B_RX_OK    = 0;
		for(i=0; i<COM_TX2_Lenth; i++)	TX2_Buffer[i] = 0;
		for(i=0; i<COM_RX2_Lenth; i++)	RX2_Buffer[i] = 0;

		if((COMx->UART_Mode == UART_9bit_BRTx) ||(COMx->UART_Mode == UART_8bit_BRTx))	//Variable baud rate|可变波特率
		{
			if(COMx->UART_Polity == PolityHigh)		IP2 |=  1;	//High priority interrupt|高优先级中断
			else									IP2 &= ~1;	//Low priority interrupt|低优先级中断
			if(COMx->UART_Mode == UART_9bit_BRTx)	S2CON |=  (1<<7);	//9bit
			else									S2CON &= ~(1<<7);	//8bit
			j = (MAIN_Fosc / 4) / COMx->UART_BaudRate;	//Calculate by 1T|按1T计算
			if(j >= 65536UL)	return 2;	//error|错误
			j = 65536UL - j;
			AUXR &= ~(1<<4);	//Timer stop
			AUXR &= ~(1<<3);	//Timer2 set As Timer
			AUXR |=  (1<<2);	//Timer2 set as 1T mode
			TH2 = (unsigned char)(j>>8);
			TL2 = (unsigned char)j;
			IE2  &= ~(1<<2);	//No interruption|禁止中断
			AUXR |=  (1<<4);	//Timer run enable
		}
		else	return 2;	//Mode error|模式错误
		if(COMx->UART_Interrupt == ENABLE)	IE2   |=  1;		//Allowed interruption|允许中断
		else								IE2   &= ~1;		//No interruption|禁止中断
		if(COMx->UART_RxEnable == ENABLE)	S2CON |=  (1<<4);	//Allow reception|允许接收
		else								S2CON &= ~(1<<4);	//No acceptance|禁止接收
		if(COMx->UART_P_SW == UART2_SW_P10_P11)
		{
			GPIO_InitTypeDef GPIO_InitTypeDef;
			GPIO_InitTypeDef.Mode = GPIO_OUT_PP;
			GPIO_InitTypeDef.Pin = GPIO_Pin_1;//配置IO引脚 Px.1
			GPIO_Inilize(GPIO_P1 ,&GPIO_InitTypeDef);//IO引脚 P1.1
		}
		else
		{
			GPIO_InitTypeDef GPIO_InitTypeDef;
			GPIO_InitTypeDef.Mode = GPIO_OUT_PP;
			GPIO_InitTypeDef.Pin = GPIO_Pin_7;//配置IO引脚 Px.7
			GPIO_Inilize(GPIO_P4 ,&GPIO_InitTypeDef);//IO引脚 P4.7
		}
		P_SW2 = (P_SW2 & ~1) | (COMx->UART_P_SW & 0x01);	//Switch IO|切换IO
	}
	return	0;
}


//========================================================================
// Function:void TX1_write2buff(unsigned char dat)|函数: void TX1_write2buff(unsigned char dat)
// Description:Serial Port 1 Send|描述: 串口1发送.
// Parameter: dat: Data to be sent|参数: dat:要发送的数据
//       
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2018-12-20|日期: 2018-12-20
// Author: Pinecone Pi|作者: PineconePi
// Note:|备注: 
//	
//	
//	
//	
//	
//========================================================================

void TX1_write2buff(unsigned char dat)	//写入发送缓冲，指针+1
{
	while(1)
	{
		if(COM1.B_TX_busy == 0)		//空闲
		{  
			COM1.B_TX_busy = 1;		//标志忙
			SBUF = dat;
			while(!TI); 					//等待发送完成
			TI=0; 							//清零发送标志位
			COM1.B_TX_busy = 0;
			break;
		}
		else
		{
			Delay_Us(5);
		}
	}
	
}
//========================================================================
// Function:void TX1_write2buff(unsigned char dat)|函数: void TX1_write2buff(unsigned char dat)
// Description:Serial port 2 send.|描述: 串口2发送.
// Parameter: dat: Data to be sent|参数: dat:要发送的数据
//       
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2018-12-20|日期: 2018-12-20
// Author: Pinecone Pi|作者: PineconePi
// Note:|备注: 
//	
//	
//	
//	
//	
//========================================================================

void TX2_write2buff(unsigned char dat)	//Write send buffer, pointer + 1
{
	TX2_Buffer[COM2.TX_write] = dat;	//Loading and Sending Buffer
	if(++COM2.TX_write >= COM_TX2_Lenth)	COM2.TX_write = 0;

	if(COM2.B_TX_busy == 0)		//free
	{  
		COM2.B_TX_busy = 1;		//Sign busy
		CLR_RTI2();				//Trigger Send Interrupt
	}
}

//========================================================================
// Function:void PrintString1(unsigned char *puts)|函数: void PrintString1(unsigned char *puts)
// Description:TX1 send string|TX1发送字符串
// Parameter: puts: Strin to be sent|参数: puts:要发送的字符串
//       
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-01-23|日期: 2021-01-23
// Author: sky_vocality|作者: sky_vocality
// Note:|备注: 
//	
//	
//	
//	
//	
//========================================================================
void PrintString1(unsigned char *puts)
{
    for (; *puts != 0;	puts++)  TX1_write2buff(*puts); 	//End with stop 0|遇到停止符0结束
}

//========================================================================
// Function:void PrintString2(unsigned char *puts)|函数: void PrintString2(unsigned char *puts)
// Description:TX2 send string|TX2发送字符串
// Parameter: puts: Strin to be sent|参数: puts:要发送的字符串
//       
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-01-23|日期: 2021-01-23
// Author: sky_vocality|作者: sky_vocality
// Note:|备注: 
//	
//	
//	
//	
//	
//========================================================================
void PrintString2(unsigned char *puts)
{
    for (; *puts != 0;	puts++)  TX2_write2buff(*puts); 	//End with stop 0|遇到停止符0结束
}

//========================================================================
// Function:unsigned char ReceiveByte(void)|函数: unsigned char ReceiveByte(void)
// Description:Read receive byte|读取接收到的数据
// Parameter:
//       
//       
// Return:|返回: rbyte: receive byte|接收到的数据
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-01-23|日期: 2021-01-23
// Author:  sky_vocality|作者: sky_vocality
// Note:|备注: 
//	
//	
//	
//	
//	
//========================================================================
unsigned char ReceiveByte(void)
{
    unsigned char rbyte;
    while(!RI);
    RI=0;
    rbyte=SBUF;
    return rbyte;
}

unsigned char *pchar;

void SerialPortInte(void) interrupt 4 
{ 
    RI=0;
    *pchar=SBUF;
}

//========================================================================
// Function:void intToString(int N,char arr[])|函数: void intToString(int N,char arr[])
// Description:int To String|int类型转string
// Parameter: N: The int need change|参数: N: 需要转换的int类型
//            arr: The string's save arr|arr: 字符串存储的地址
//       
//       
// Return:|返回:
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-01-23|日期: 2021-01-23
// Author:  sky_vocality|作者: sky_vocality
// Note:|备注: 
//	
//	
//	
//	
//	
//========================================================================
void intToString(int N,char arr[]){
    int i,j,flag;
    char stack[10]; 
    i=0;
    if (N<0){
        flag=0;
        N=-N;
    }else{
        flag=1;
    }
    while (N/10!=0){
        stack[i]=(char)(48+N%10);
        N=N/10;
        i++;
    }
    stack[i]=(char)(48+N);
    if (flag==0){
        arr[0]='-';
        for (j=i;j>-1;j--){
            arr[i-j+1]=stack[j];
        }
        arr[i+2]='\0';
    }else{
        for (j=i;j>-1;j--){
            arr[i-j]=stack[j];
        }
        arr[i+1]='\0';
    }
}
