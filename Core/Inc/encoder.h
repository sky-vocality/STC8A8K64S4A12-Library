/**
 ******************************************************************************
 * @file    encoder.h
 * @author  sky-vocality
 * @version V1.0.0
 * @date    25-January-2021
 * @brief  This file is used for processing encoder data
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
#ifndef	__ENCODER_H
#define	__ENCODER_H

#include	"system.h"
#include  "exit.h"

#ifndef	EXT_INT0
#define	EXT_INT0			0	//External interrupt 0|外部中断0
#define	EXT_INT1			2	//External interrupt 1|外部中断1
#define	EXT_INT2			10	//External interrupt 2|外部中断2
#define	EXT_INT3			11	//External interrupt 3|外部中断3
#define	EXT_INT4			16	//External interrupt 4|外部中断4
#endif

#define	ENC_MODE_RiseFall	0		//Rising edge interruption|上升沿中断
#define	ENC_MODE_Fall		1			//Falling edge interruption|下降沿中断

#define ENABLE  	1			//Interrupt enable|中断允许
#define DISABLE  	0			//Interrupt disable|中断关闭

#define PolityHigh  1	  //High priority|高优先级
#define PolityLow  	0		//Low priority (default)|低优先级（默认）
//========================================================================
// Structure:ENC_InitTypeDef|结构体: ENC_InitTypeDef
// Description:ENC configuration structure|描述: ENC配置结构体。
// Parameters:ENC_Mode（NC_MODE_RiseFall：Rising edge interruption ，NC_MODE_Fall: Falling edge interruption)
//            ENC_Polity(PolityHigh:High priority , PolityLow:Low priority (default))
//            ENC_Interrupt(ENABLE:， DISABLE：）
// 参数: ENC_Mode（EXT_MODE_RiseFall：上升沿中断 ，EXT_MODE_Fall: 下降沿中断)
//       ENC_Polity(PolityHigh:高优先级 , PolityLow:低优先级（默认）)
//       ENC_Interrupt(ENABLE:允许 ， DISABLE：不使能）
// 返回: none.
// 版本: VER1.0.0
// 日期: 2018-12-20
// 备注: 通过以下步骤使能INT0
//	ENC_InitTypeDef ENC_InitTypeDef;
//	ENC_InitTypeDef.ENC_Mode = ENC_MODE_RiseFall;//上升沿中断
//	ENC_InitTypeDef.ENC_Polity = PolityHigh;//高优先级
//	ENC_InitTypeDef.ENC_Interrupt = ENABLE;//使能
//	NC_Inilize(EXT_INT0,&ENC_InitTypeDef);//完成配置
//========================================================================
typedef struct
{
	unsigned char	ENC_Mode;			//Interrupt mode|中断模式,  	ENC_MODE_RiseFall, ENC_MODE_Fall
	unsigned char	ENC_Polity;		//Priority Setting|优先级设置	PolityHigh,PolityLow
	unsigned char	ENC_Interrupt;		//Interrupt enable|中断允许		ENABLE,DISABLE
} ENC_InitTypeDef;

//Modify the interrupt program in the corresponding interrupt function in exit.c|在相应的exit.c中的中断函数中修改中断程序
unsigned char	ENC_Inilize(unsigned char EXT, ENC_InitTypeDef *INTx);

#endif
