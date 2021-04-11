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
 * LCD_P6x8Str(20,0,(unsigned char*)"Hello world");
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

#define LCD_SCL	P32
#define LCD_SDA	P33
#define LCD_RST	P34

#define HIGH 1
#define LOW  0
#define IICADRR 0x78
#define X_WIDTH 132
#define Y_WIDTH 64

void LCD_Init();
void LCD_Fill(unsigned char bmp_data); //Screen filling|屏幕填充
void LCD_CLS(void); //Screen clear|清屏
void LCD_PutPixel(unsigned char x,unsigned char y); //draw a point|画一个点
void LCD_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[]); //display a string|显示字符串
void LCD_PrintU16(unsigned char x,unsigned char y,unsigned int num); //display a uint|显示uint
void LCD_Print16(unsigned char x,unsigned char y,int num); //display a int|显示int
void LCD_PrintFloat(unsigned char x,unsigned char y,float num); //display a float|显示浮点数

#endif
