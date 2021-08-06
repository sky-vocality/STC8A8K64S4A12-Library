/**
  ******************************************************************************
  * @file    exti.c
  * @author  sky-vocality(基于PineconePi(基于宏晶科技STC15库函数进行修改)库函数进行修改)
  * @version V1.0.0
  * @date    20-January-2021
  * @brief  This file is used for external interrupt configuration
  * @License:GNU General Public License v3.0         
  ******************************************************************************
  * @attention
  * 内含PAC中断
  * Embedded PAC interrupt.
  *  
  * 
  * 
  * 
  * 
  *
  * 
  ******************************************************************************
**/

#include "exit.h"

int encoder_num = 0;
int encoder_num_l = 0;

/********************* INT0 interrupt function|INT0中断函数 *************************/
void Ext_INT0 (void) interrupt EXT_INT0		//The sign has been cleared when entering or interrupting|进中断时已经清除标志
{
	//Add user logic here|此处添加用户逻辑
}

/********************* INT1 interrupt function|INT1中断函数 *************************/
void Ext_INT1 (void) interrupt EXT_INT1		//The sign has been cleared when entering or interrupting|进中断时已经清除标志
{
	//Add user logic here|此处添加用户逻辑
}

/********************* INT2 interrupt function|INT2中断函数 *************************/
void Ext_INT2 (void) interrupt EXT_INT2	//
{
	//Add user logic here|此处添加用户逻辑
}

/********************* INT3 interrupt function|INT3中断函数 *************************/
void Ext_INT3 (void) interrupt EXT_INT3
{
	//Add user logic here|此处添加用户逻辑
}

/********************* INT4 interrupt function|INT4中断函数 *************************/
void Ext_INT4 (void) interrupt EXT_INT4
{
	//Add user logic here|此处添加用户逻辑
}

/********************* PCA Interrupt Handling Function|PCA??????************************/
void	PCA_Ext (void) interrupt PCA_INT0
{
	if(CCF0)		//PCA module 0 interrupt|PCA??0??
	{
		CCF0 = 0;		//Clear PCA module 0 interrupt flag|?PCA??0????
	}

	if(CCF1)	//PCA Module 1 Interruption|PCA??1??
	{
		CCF1 = 0;		//Clear the interrupt flag in PCA module 1|?PCA??1????
	}

	if(CCF2)	//PCA Module 2 Interruption|PCA??2??
	{
		CCF2 = 0;		//Clear the interrupt flag in PCA module 2|?PCA??2????
	}

		if(CCF3)	//PCA Module 3 Interruption|PCA??3??
	{
		CCF3 = 0;		//Clear the interrupt flag in PCA module 3|?PCA??3????
	}
}

//========================================================================
// Function:unsigned char Ext_Inilize(unsigned char EXT, EXTI_InitTypeDef *INTx)|函数: unsigned char Ext_Inilize(unsigned char EXT, EXTI_InitTypeDef *INTx)
// Description:External interrupt initializer|描述: 外部中断初始化程序.
// Parameter:EXT,Interrupt sequence number（EXT_INT0：External interrupt 0 , EXT_INT1：External interrupt 1 , EXT_INT2：External interrupt 2 , 
//                                          EXT_INT3：External interrupt 3 ， EXT_INT4：External interrupt 4)
// 参数: EXT,中断序号（EXT_INT0：外部中断0 , EXT_INT1：外部中断1 , EXT_INT2：外部中断2 , 
//       EXT_INT3：外部中断3 ， EXT_INT4：外部中断4)
//       INTx: 结构参数,请参考Exti.h里的定义.
// Return:Successful return 0, empty return 1, error return 2.|返回: 成功返回0, 空操作返回1,错误返回2.
// Version:VER1.0.0|版本: VER1.0.0
// Date:2018-12-20|日期: 2018-12-20
// Note: Enable INT0 by following steps
//	EXTI_InitTypeDef EXTI_InitTypeDef;
//	EXTI_InitTypeDef.EXTI_Mode = EXT_MODE_RiseFall;//Rising edge interruption
//	EXTI_InitTypeDef.EXTI_Polity = PolityHigh;//High priority|高优先级
//	EXTI_InitTypeDef.EXTI_Interrupt = ENABLE;//Enable|使能
//	Ext_Inilize(EXT_INT0,&EXTI_InitTypeDef);//Complete configuration|完成配置
// 备注: 通过以下步骤使能INT0
//	EXTI_InitTypeDef EXTI_InitTypeDef;
//	EXTI_InitTypeDef.EXTI_Mode = EXT_MODE_RiseFall;//上升沿中断
//	EXTI_InitTypeDef.EXTI_Polity = PolityHigh;//高优先级
//	EXTI_InitTypeDef.EXTI_Interrupt = ENABLE;//使能
//	Ext_Inilize(EXT_INT0,&EXTI_InitTypeDef);//完成配置
//========================================================================
unsigned char Ext_Inilize(unsigned char EXT, EXTI_InitTypeDef *INTx)
{
	if(EXT >  EXT_INT4)	return 1;	//Empty operation|空操作
	
	EA = 1;
	
	if(EXT == EXT_INT0)	//External interrupt 0|外中断0
	{
		if(INTx->EXTI_Interrupt == ENABLE)		EX0 = 1;	//Allowed interruption|允许中断
		else									EX0 = 0;	//No interruption|禁止中断
		if(INTx->EXTI_Polity == PolityHigh)		PX0 = 1;	//High priority interrupt|高优先级中断
		else									PX0 = 0;	//Low priority interrupt|低优先级中断
		if(INTx->EXTI_Mode == EXT_MODE_Fall)	IT0 = 1;	//Falling edge interruption|下降沿中断
		else									IT0 = 0;	//Rise, fall and interrupt|上升,下降沿中断
		return	0;		//Success|成功
	}

	if(EXT == EXT_INT1)	//External interrupt 1|外中断1
	{
		if(INTx->EXTI_Interrupt == ENABLE)		EX1 = 1;	//Allowed interruption|允许中断
		else									EX1 = 0;	//No interruption|禁止中断
		if(INTx->EXTI_Polity == PolityHigh)		PX1 = 1;	//High priority interrupt|高优先级中断
		else									PX1 = 0;	//Low priority interrupt|低优先级中断
		if(INTx->EXTI_Mode == EXT_MODE_Fall)	IT1 = 1;	//Falling edge interruption|下降沿中断
		else									IT1 = 0;	//Rise, fall and interrupt|上升,下降沿中断
		return	0;		//Success|成功
	}

	if(EXT == EXT_INT2)		//Outer interrupt 2, fixed to lower priority interrupt|外中断2, 固定为下降沿低优先级中断
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INTCLKO |=  (1 << 4);	//Allowed interruption|允许中断	
		else								INTCLKO &= ~(1 << 4);	//No interruption|禁止中断
		return	0;		//Success|成功
	}

	if(EXT == EXT_INT3)		//Outer interrupt 3, fixed to lower priority interrupt|外中断3, 固定为下降沿低优先级中断
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INTCLKO |=  (1 << 5);	//Allowed interruption|允许中断	
		else								INTCLKO &= ~(1 << 5);	//No interruption|禁止中断
		return	0;		//Success|成功
	}

	if(EXT == EXT_INT4)		//External interrupt 4, fixed to lower priority interrupt|外中断4, 固定为下降沿低优先级中断
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INTCLKO |=  (1 << 6);	//Allowed interruption|允许中断	
		else								INTCLKO &= ~(1 << 6);	//No interruption|禁止中断
		return	0;		//Success|成功
	}

	if(EXT == PCA_INT0)		//External interrupt 4, fixed to lower priority interrupt|外中断4, 固定为下降沿低优先级中断
	{
		CCON = 0x00;
		CMOD = 0x0d;
		CL = 0x00;
		CH = 0x00;
		if (INTx->EXTI_Mode == EXT_MODE_Fall)  CCAPM0 = 0x11;
		else CCAPM0 = 0x21;
		CCAP0L = 0;
		CCAP0H = 0;
		CR = 1;
		return	0;		//Success|成功
	}

	if(EXT == PCA_INT1)
	{
		CCON = 0x00;
		CMOD = 0x0d;
		CL = 0x00;
		CH = 0x00;
		if (INTx->EXTI_Mode == EXT_MODE_Fall)  CCAPM1 = 0x11;
		else CCAPM1 = 0x21;
		CCAP1L = 0;
		CCAP1H = 0;
		CR = 1;
		return	0;		//Success|成功
	}

	if(EXT == PCA_INT2)
	{
		CCON = 0x00;
		CMOD = 0x0d;
		CL = 0x00;
		CH = 0x00;
		if (INTx->EXTI_Mode == EXT_MODE_Fall)  CCAPM2 = 0x11;
		else CCAPM2 = 0x21;
		CCAP2L = 0;
		CCAP2H = 0;
		CR = 1;
		return	0;		//Success|成功
	}

	if(EXT == PCA_INT3)
	{
		CCON = 0x00;
		CMOD = 0x0d;
		CL = 0x00;
		CH = 0x00;
		if (INTx->EXTI_Mode == EXT_MODE_Fall)  CCAPM3 = 0x11;
		else CCAPM0 = 0x21;
		CCAP3L = 0;
		CCAP3H = 0;
		CR = 1;
		return	0;		//Success|成功
	}
	return 2;	//fail|失败
}