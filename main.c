#include "uart.h"
#include "pwm.h"
#include "delay.h"
#include "iic.h"


//double Roll = 0;
int temp = 0;
char kkk[3] = 0;

int main()
{
	char p0 = 0;
	char p1 = 0;
	double Roll = 0;
	int ahh = 0;
	PWM_InitTypeDef PWM_Init;
	COMx_InitDefine COMx_InitDefine1;
	COMx_InitDefine COMx_InitDefine2;
	COMx_InitDefine1.UART_Mode = UART_8bit_BRTx;			//Pattern|模式,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitDefine1.UART_BRT_Use = BRT_Timer1;		//Using baud rate|使用波特率,   BRT_Timer1,BRT_Timer2
	COMx_InitDefine1.UART_BaudRate = 19200;		//baud rate|波特率,       ENABLE,DISABLE
	COMx_InitDefine1.Morecommunicate = ENABLE;	//Multiprocessor Communication Allowance|多机通讯允许, ENABLE,DISABLE
	COMx_InitDefine1.UART_RxEnable = ENABLE;		//Allow reception|允许接收,   ENABLE,DISABLE
	COMx_InitDefine1.BaudRateDouble = DISABLE;		//Baud rate doubled|波特率加倍, ENABLE,DISABLE
	COMx_InitDefine1.UART_Interrupt = ENABLE;		//Interrupt control|中断控制,   ENABLE,DISABLE
	COMx_InitDefine1.UART_Polity = PolityHigh;		//priority|优先级,     PolityLow,PolityHigh
	COMx_InitDefine1.UART_P_SW = UART1_SW_P30_P31;			//Switch port|切换端口,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17(必须使用内部时钟)
	PWM_Init.PWM_Channelx=PWM_Channel1;
	PWM_Init.PWM_Value=145;
	PWM_Init.PWM_Frequency=100;
	PWM_Output(PWM_0,&PWM_Init);
	COMx_InitDefine2.UART_Mode = UART_8bit_BRTx;			//Pattern|模式,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitDefine2.UART_BRT_Use = BRT_Timer2;		//Using baud rate|使用波特率,   BRT_Timer1,BRT_Timer2
	COMx_InitDefine2.UART_BaudRate = 19200;		//baud rate|波特率,       ENABLE,DISABLE
	COMx_InitDefine2.Morecommunicate = ENABLE;	//Multiprocessor Communication Allowance|多机通讯允许, ENABLE,DISABLE
	COMx_InitDefine2.UART_RxEnable = ENABLE;		//Allow reception|允许接收,   ENABLE,DISABLE
	COMx_InitDefine2.BaudRateDouble = DISABLE;		//Baud rate doubled|波特率加倍, ENABLE,DISABLE
	COMx_InitDefine2.UART_Interrupt = ENABLE;		//Interrupt control|中断控制,   ENABLE,DISABLE
	COMx_InitDefine2.UART_Polity = PolityHigh;		//priority|优先级,     PolityLow,PolityHigh
	COMx_InitDefine2.UART_P_SW = UART2_SW_P10_P11;			//Switch port|切换端口,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17(必须使用内部时钟)
	USART_Configuration(USART2, &COMx_InitDefine2);
	USART_Configuration(USART1, &COMx_InitDefine1);											
  IIC_host_Slave_machine(host_machine);       //Setting up host mode|设置为主机模式
	while(1)
	{
		Start();                                    //Send Start Command|发送起始命令
    SendData(0x50<<1);                             //Send device address + read command|发送设备地址+读命令
		SendData(0x3e);
		Start();
		SendData((0x50<<1)|1);
    p0 = RecvData();                            //Read data 1|读取数据1
    SendACK();
    p1 = RecvData();                            //读取数据2|读取数据2
    SendNAK();
    Stop();                                     //Send stop command|发送停止命令
		//PrintString1(&p1);
		//PrintString1(&p0);
		temp = (p1<<8)|p0;
		Roll=(double)temp/32768*180;
		ahh = Roll;
		if(ahh == 0)
		{
			intToString(temp,kkk);
			PrintString1(kkk);
			continue;
		}
		intToString(ahh,kkk);
		PrintString1(kkk);
		PrintString1("\r\n");
		Delay_Ms(30);
		//kkkkk = ReceiveByte1();
		//PrintString1(RX2_Buffer);
		//PrintString1(&kkkkk);
		/*
		int a;
		for(a = 0;a<1000;a++)
		{
			PWM_Init.PWM_Value=a;
			PWM_Output(PWM_0,&PWM_Init);
			intToString(a,acac);
			PrintString1(acac);
			PrintString1("\r\n");
			Delay_Ms(50);
		}
		*/
	}
}