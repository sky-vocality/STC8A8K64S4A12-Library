/**
 ******************************************************************************
 * @file    oled.h
 * @author  sky-vocality
 * @version V1.0.0
 * @date    9-April-2021
 * @brief  This file is a oled driver
 * @License:GNU General Public License v3.0         
 ******************************************************************************
 * @attention
 * 
 * LCD_Init();               //LCD init|LCD初始化
 * time_delay_ms(500);
 * LCD_CLS();                //LCD Clear|LCD清屏
 * LCD_P8x16Str(20,0,(uint8_t*)"Hello world");
 * 
 * 
 * 
 ******************************************************************************
**/

#ifndef	__OLED_H
#define	__OLED_H

#include "system.h"
#include "iic.h"
#include "delay.h"
#include "gpio.h"


void LCD_Init();
void LCD_Fill(unsigned char bmp_data); //Screen filling|屏幕填充
void LCD_CLS(void); //Screen clear|清屏
void LCD_PutPixel(unsigned char x,unsigned char y); //draw a point|画一个点
void LCD_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[]); //display a string|显示字符串
void LCD_PrintU16(unsigned char x,unsigned char y,unsigned int num); //display a uint|显示uint
void LCD_PrintFloat(unsigned char x,unsigned char y,float num); //display a float|显示浮点数

#endif
