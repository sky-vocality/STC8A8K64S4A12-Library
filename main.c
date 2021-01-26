#include "uart.h"
#include "pwm.h"
#include "delay.h"
#include "uart.h"

char acac[8] = 0;

int main()
{
	PWM_InitTypeDef PWM_Init;
	COMx_InitDefine COMx_InitDefine; 
	COMx_InitDefine.UART_Mode = UART_8bit_BRTx;			//Pattern|ģʽ,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitDefine.UART_BRT_Use = BRT_Timer1;		//Using baud rate|ʹ�ò�����,   BRT_Timer1,BRT_Timer2
	COMx_InitDefine.UART_BaudRate = 19200;		//baud rate|������,       ENABLE,DISABLE
	COMx_InitDefine.Morecommunicate = ENABLE;	//Multiprocessor Communication Allowance|���ͨѶ����, ENABLE,DISABLE
	COMx_InitDefine.UART_RxEnable = DISABLE;		//Allow reception|�������,   ENABLE,DISABLE
	COMx_InitDefine.BaudRateDouble = DISABLE;		//Baud rate doubled|�����ʼӱ�, ENABLE,DISABLE
	COMx_InitDefine.UART_Interrupt = ENABLE;		//Interrupt control|�жϿ���,   ENABLE,DISABLE
	COMx_InitDefine.UART_Polity = PolityHigh;		//priority|���ȼ�,     PolityLow,PolityHigh
	COMx_InitDefine.UART_P_SW = UART1_SW_P30_P31;			//Switch port|�л��˿�,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17(����ʹ���ڲ�ʱ��)
	PWM_Init.PWM_Channelx=PWM_Channel1;
	PWM_Init.PWM_Value=25;
	PWM_Init.PWM_Frequency=100;
	PWM_Output(PWM_0,&PWM_Init);
	USART_Configuration(USART1, &COMx_InitDefine);
	while(1)
	{
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
	}
}