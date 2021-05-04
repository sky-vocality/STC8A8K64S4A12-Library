#include "uart.h"
#include "gpio.h"
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
	GPIO_InitTypeDef GPIO_InitTypeDef012;
	int a = 0;
	LCD_Init();
	LCD_P6x8Str(13, 3,(unsigned char*)"Init!");
	Delay_Ms(1000);
	LCD_CLS();
	ENC_EXT_init();
	jy901_timer_init();
	wheel_pid_timer_init();
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
		GPIO_InitTypeDef012.Mode = GPIO_PullUp;//上拉准双向口
		GPIO_InitTypeDef012.Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;//同时配置IO引脚 Px.0与Px.1
		GPIO_Inilize(GPIO_P5 ,&GPIO_InitTypeDef012);//IO引脚 P0.0
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
		}
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
		int a;
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
		//PWM_Output(PWM_1,&server_pwm);
	}
}
