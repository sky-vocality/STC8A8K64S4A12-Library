#include "uart.h"
#include "pwm.h"
#include "delay.h"
#include "pid.h"
#include "encoder.h"
#include "adc.h"
#include "oled.h"

//double Roll = 0;
//int temp = 0;
char kkk[5] = 0;

int main()
{
	//double Roll = 0;
	//int ahh = 0;
	/*
	COMx_InitDefine COMx_InitDefine1;
	ENC_EXT_init();
	COMx_InitDefine1.UART_Mode = UART_8bit_BRTx;			//Pattern|??,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitDefine1.UART_BRT_Use = BRT_Timer1;		//Using baud rate|?????,   BRT_Timer1,BRT_Timer2
	COMx_InitDefine1.UART_BaudRate = 19200;		//baud rate|???,       ENABLE,DISABLE
	COMx_InitDefine1.Morecommunicate = ENABLE;	//Multiprocessor Communication Allowance|??????, ENABLE,DISABLE
	COMx_InitDefine1.UART_RxEnable = ENABLE;		//Allow reception|????,   ENABLE,DISABLE
	COMx_InitDefine1.BaudRateDouble = DISABLE;		//Baud rate doubled|?????, ENABLE,DISABLE
	COMx_InitDefine1.UART_Interrupt = ENABLE;		//Interrupt control|????,   ENABLE,DISABLE
	COMx_InitDefine1.UART_Polity = PolityHigh;		//priority|???,     PolityLow,PolityHigh
	COMx_InitDefine1.UART_P_SW = UART1_SW_P30_P31;			//Switch port|????,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17(????????)
	USART_Configuration(USART1, &COMx_InitDefine1);
	*/
	LCD_Init();
	//LCD init|LCD???
	//IIC_host_Slave_machine(host_machine);
	LCD_P6x8Str(13, 3,(unsigned char*)"Init!");
	Delay_Ms(500);
	LCD_CLS();
	//LCD_PrintU16(13,3,13100);
	//LCD_PrintFloat(13,3,5.21);
	//ENC_EXT_init();
	jy901_timer_init();
	wheel_pid_timer_init();
	//jy901_update();
	while(1)
	{
		//jy901_update();
		//LCD_PrintFloat(13,3,server_pid.pid_out);
		LCD_PrintFloat(13,3,wheel_pid.pid_out);
		//wheel_pwm.PWM_Value = 0;//wheel_pid.pid_out;
		//PWM_Output(PWM_0,&wheel_pwm);
		Delay_Ms(100);
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
		int a;
		for(a = 0;a<1000;a++)
		{
			server_pwm.PWM_Value = 147.5;//server_pid.pid_out + 147.5;
			PWM_Output(PWM_1,&server_pwm);
			LCD_PrintU16(13,3,a);
			LCD_CLS();
			Delay_Ms(50);
		}*/
		//server_pwm.PWM_Value = 147.5;//server_pid.pid_out + 147.5;
		//PWM_Output(PWM_1,&server_pwm);
		//jy901_update();
		//Delay_Ms(500);
		//server_pwm.PWM_Value = 147.5;//server_pid.pid_out + 147.5;
		//PWM_Output(PWM_1,&server_pwm);
	}
}
