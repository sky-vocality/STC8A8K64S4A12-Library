#include "uart.h"
#include "gpio.h"
#include "pwm.h"
#include "delay.h"
#include "pid.h"
#include "encoder.h"
#include "oled.h"
#include "LMV358.h"

//double Roll = 0;
//int temp = 0;
//char kkk[5] = 0;

int main()
{
	//GPIO_InitTypeDef GPIO_InitTypeDef012;
	int a = 0;
	LCD_Init();
	LCD_P6x8Str(13, 3,(unsigned char*)"Init!");
	Delay_Ms(1000);
	ENC_EXT_init();
	jy901_timer_init();
	wheel_pid_timer_init();
	LMV358_timer_init();
	LCD_CLS();
	while(1)
	{
		//jy901_update();
		
		LCD_P6x8Str(0, 1,(unsigned char*)"wkp:");
		LCD_PrintFloat(25,1,wheel_pid.Kp);
		LCD_P6x8Str(0, 2,(unsigned char*)"wki:");
		LCD_PrintFloat(25,2,wheel_pid.Ki);
		LCD_P6x8Str(0, 3,(unsigned char*)"wkd:");
		LCD_PrintFloat(25,3,wheel_pid.Kd);
		LCD_P6x8Str(0, 7,(unsigned char*)"val:");
		LCD_Print16(25,7,wheel_pwm.PWM_Value);
		/*
		GPIO_InitTypeDef012.Mode = GPIO_PullUp;//����׼˫���
		GPIO_InitTypeDef012.Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;//ͬʱ����IO���� Px.0��Px.1
		GPIO_Inilize(GPIO_P5 ,&GPIO_InitTypeDef012);//IO���� P0.0
		if( P50 == 0)
		{
			wheel_pid.Kp = wheel_pid.Kp + 0.01;
		}
		if( P51 == 0)
		{
			wheel_pid.Ki = wheel_pid.Ki + 0.01;
		}
		if( P52 == 0)
		{
			wheel_pid.Kd = wheel_pid.Kd + 0.01;
		}*/
		//LCD_Print16(13,3,encoder_num);
		//LCD_PrintFloat(13,3,1.1);
		//wheel_pwm.PWM_Value = 250;//wheel_pid.pid_out;
		//PWM_PCA_Output(PWM_0,&wheel_pwm);
		//wheel_pwm.PWM_Value = 210;//wheel_pid.pid_out;
		//PWM_PCA_Output(PWM_0,&wheel_pwm);
		//Delay_Ms(100);
		//server_pwm.PWM_Value = 147.5;//server_pid.pid_out + 147.5;
		//PWM_Output(PWM_1,&server_pwm);
		//LCD_PrintFloat(3,0,jy901.Pitch);
		//LCD_PrintFloat(4,0,jy901.Yaw);
		//Delay_Ms(100);
		LCD_CLS();
		//LCD_P6x8Str(13,3,(unsigned char*)"Hello world");
		//LCD_Fill(0x00);
		//Delay_Ms(500);
		//LCD_CLS();
		/*
		//jy901_update();
		PID_Control(increment, encoder_num, 210, &wheel_pid);
		wheel_pwm.PWM_Value = wheel_pid.pid_out;
		PWM_Output(PWM_0,&wheel_pwm);
		intToString(encoder_num,kkk);
		encoder_num = 0;
		PrintString1(kkk);
		PrintString1(",\r\n");
		//kkkkk = ReceiveByte1();
		//PrintString1(RX2_Buffer);
		//PrintString1(&kkkkk);
		//int a;
		for(a = 0;a<1000;a++)
		{
			server_pwm.PWM_Value = 78;//server_pid.pid_out + 147.5;
			PWM_CLK_Output(PWM_1,&server_pwm);
			LCD_PrintU16(13,3,a);
			LCD_CLS();
			Delay_Ms(20);
		}*/
		//server_pwm.PWM_Value = 147.5;//server_pid.pid_out + 147.5;
		//PWM_Output(PWM_1,&server_pwm);
		//jy901_update();
		//Delay_Ms(500);
		//server_pwm.PWM_Value = 147.5;//server_pid.pid_out + 147.5;
		//PWM_Output(PWM_1,&server_pwm);}*/
	/*
	unsigned int error;
	unsigned char m[10]={0};
	unsigned int n=0;

	COMx_InitDefine COM_1;
	COM_1.UART_Mode=UART_8bit_BRTx;			//Pattern|模式,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COM_1.UART_BRT_Use=BRT_Timer1;		//Using baud rate|使用波特率,   BRT_Timer1,BRT_Timer2
	COM_1.UART_BaudRate=19200;		//baud rate|波特率,       ENABLE,DISABLE
	COM_1.Morecommunicate=ENABLE;	//Multiprocessor Communication Allowance|多机通讯允许, ENABLE,DISABLE
	COM_1.UART_RxEnable=ENABLE;		//Allow reception|允许接收,   ENABLE,DISABLE
	COM_1.BaudRateDouble=ENABLE;		//Baud rate doubled|波特率加倍, ENABLE,DISABLE
	COM_1.UART_Interrupt=ENABLE;		//Interrupt control|中断控制,   ENABLE,DISABLE
	COM_1.UART_Polity=PolityHigh;		//priority|优先级,     PolityLow,PolityHigh
	COM_1.UART_P_SW=UART1_SW_P30_P31;			//Switch port|切换端口,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17(必须使用内部时钟)
	USART_Configuration(USART1,&COM_1);

	LMV358_Init();
	while(1)
	{
	LMV358_InductorNormal();
	/*
	n=LMV358_GetAvergeData(2);
	intToString(n,m);
	PrintString1(m);PrintString1("\r\n");
	n=LMV358_GetAvergeData(3);
	intToString(n,m);
	*//*
	error = LMV358_Output();
	intToString(error,m);
	PrintString1(m);PrintString1("\r\n");	
	Delay_Ms(500);
	}*/
	}
}
