/**
 ******************************************************************************
 * @file    oled.c
 * @author  sky-vocality
 * @version V1.0.0
 * @date    9-April-2021
 * @brief  This file is a oled driver
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

#include "oled.h"

//ascii字符集
const unsigned char F6x8[][6] =
{
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // sp
    { 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00 },   // !
    { 0x00, 0x00, 0x07, 0x00, 0x07, 0x00 },   // "
    { 0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14 },   // #
    { 0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12 },   // $
    { 0x00, 0x62, 0x64, 0x08, 0x13, 0x23 },   // %
    { 0x00, 0x36, 0x49, 0x55, 0x22, 0x50 },   // &
    { 0x00, 0x00, 0x05, 0x03, 0x00, 0x00 },   // '
    { 0x00, 0x00, 0x1c, 0x22, 0x41, 0x00 },   // (
    { 0x00, 0x00, 0x41, 0x22, 0x1c, 0x00 },   // )
    { 0x00, 0x14, 0x08, 0x3E, 0x08, 0x14 },   // *
    { 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08 },   // +
    { 0x00, 0x00, 0x00, 0xA0, 0x60, 0x00 },   // ,
    { 0x00, 0x08, 0x08, 0x08, 0x08, 0x08 },   // -
    { 0x00, 0x00, 0x60, 0x60, 0x00, 0x00 },   // .
    { 0x00, 0x20, 0x10, 0x08, 0x04, 0x02 },   // /
    { 0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E },   // 0
    { 0x00, 0x00, 0x42, 0x7F, 0x40, 0x00 },   // 1
    { 0x00, 0x42, 0x61, 0x51, 0x49, 0x46 },   // 2
    { 0x00, 0x21, 0x41, 0x45, 0x4B, 0x31 },   // 3
    { 0x00, 0x18, 0x14, 0x12, 0x7F, 0x10 },   // 4
    { 0x00, 0x27, 0x45, 0x45, 0x45, 0x39 },   // 5
    { 0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30 },   // 6
    { 0x00, 0x01, 0x71, 0x09, 0x05, 0x03 },   // 7
    { 0x00, 0x36, 0x49, 0x49, 0x49, 0x36 },   // 8
    { 0x00, 0x06, 0x49, 0x49, 0x29, 0x1E },   // 9
    { 0x00, 0x00, 0x36, 0x36, 0x00, 0x00 },   // :
    { 0x00, 0x00, 0x56, 0x36, 0x00, 0x00 },   // ;
    { 0x00, 0x08, 0x14, 0x22, 0x41, 0x00 },   // <
    { 0x00, 0x14, 0x14, 0x14, 0x14, 0x14 },   // =
    { 0x00, 0x00, 0x41, 0x22, 0x14, 0x08 },   // >
    { 0x00, 0x02, 0x01, 0x51, 0x09, 0x06 },   // ?
    { 0x00, 0x32, 0x49, 0x59, 0x51, 0x3E },   // @
    { 0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C },   // A
    { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x36 },   // B
    { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x22 },   // C
    { 0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C },   // D
    { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x41 },   // E
    { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x01 },   // F
    { 0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A },   // G
    { 0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F },   // H
    { 0x00, 0x00, 0x41, 0x7F, 0x41, 0x00 },   // I
    { 0x00, 0x20, 0x40, 0x41, 0x3F, 0x01 },   // J
    { 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41 },   // K
    { 0x00, 0x7F, 0x40, 0x40, 0x40, 0x40 },   // L
    { 0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F },   // M
    { 0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F },   // N
    { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E },   // O
    { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x06 },   // P
    { 0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E },   // Q
    { 0x00, 0x7F, 0x09, 0x19, 0x29, 0x46 },   // R
    { 0x00, 0x46, 0x49, 0x49, 0x49, 0x31 },   // S
    { 0x00, 0x01, 0x01, 0x7F, 0x01, 0x01 },   // T
    { 0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F },   // U
    { 0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F },   // V
    { 0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F },   // W
    { 0x00, 0x63, 0x14, 0x08, 0x14, 0x63 },   // X
    { 0x00, 0x07, 0x08, 0x70, 0x08, 0x07 },   // Y
    { 0x00, 0x61, 0x51, 0x49, 0x45, 0x43 },   // Z
    { 0x00, 0x00, 0x7F, 0x41, 0x41, 0x00 },   // [
    { 0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55 },   // 55
    { 0x00, 0x00, 0x41, 0x41, 0x7F, 0x00 },   // ]
    { 0x00, 0x04, 0x02, 0x01, 0x02, 0x04 },   // ^
    { 0x00, 0x40, 0x40, 0x40, 0x40, 0x40 },   // _
    { 0x00, 0x00, 0x01, 0x02, 0x04, 0x00 },   // '
    { 0x00, 0x20, 0x54, 0x54, 0x54, 0x78 },   // a
    { 0x00, 0x7F, 0x48, 0x44, 0x44, 0x38 },   // b
    { 0x00, 0x38, 0x44, 0x44, 0x44, 0x20 },   // c
    { 0x00, 0x38, 0x44, 0x44, 0x48, 0x7F },   // d
    { 0x00, 0x38, 0x54, 0x54, 0x54, 0x18 },   // e
    { 0x00, 0x08, 0x7E, 0x09, 0x01, 0x02 },   // f
    { 0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C },   // g
    { 0x00, 0x7F, 0x08, 0x04, 0x04, 0x78 },   // h
    { 0x00, 0x00, 0x44, 0x7D, 0x40, 0x00 },   // i
    { 0x00, 0x40, 0x80, 0x84, 0x7D, 0x00 },   // j
    { 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00 },   // k
    { 0x00, 0x00, 0x41, 0x7F, 0x40, 0x00 },   // l
    { 0x00, 0x7C, 0x04, 0x18, 0x04, 0x78 },   // m
    { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x78 },   // n
    { 0x00, 0x38, 0x44, 0x44, 0x44, 0x38 },   // o
    { 0x00, 0xFC, 0x24, 0x24, 0x24, 0x18 },   // p
    { 0x00, 0x18, 0x24, 0x24, 0x18, 0xFC },   // q
    { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x08 },   // r
    { 0x00, 0x48, 0x54, 0x54, 0x54, 0x20 },   // s
    { 0x00, 0x04, 0x3F, 0x44, 0x40, 0x20 },   // t
    { 0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C },   // u
    { 0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C },   // v
    { 0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C },   // w
    { 0x00, 0x44, 0x28, 0x10, 0x28, 0x44 },   // x
    { 0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C },   // y
    { 0x00, 0x44, 0x64, 0x54, 0x4C, 0x44 },   // z
    { 0x14, 0x14, 0x14, 0x14, 0x14, 0x14 }    // horiz lines
};

void Delay_1ms(unsigned int Del_1ms)
{ 
    Delay_Us(Del_1ms);
}

void IIC_Start()
{
    LCD_SCL = HIGH;
    Delay_1ms(2);
    LCD_SDA = HIGH;
    Delay_1ms(2);
    LCD_SDA = LOW;
    Delay_1ms(2);
    LCD_SCL = LOW;
    Delay_1ms(2);
}

void IIC_Stop()
{
    LCD_SCL = LOW;
    Delay_1ms(2);
    LCD_SDA = LOW;
    Delay_1ms(2);
    LCD_SCL = HIGH;
    Delay_1ms(2);
    LCD_SDA = HIGH;
    Delay_1ms(2);
}

void Write_IIC_Byte(unsigned char IIC_Byte)
{
    unsigned char i;
    for(i=0;i<8;i++)		
    {
        if(IIC_Byte & 0x80)
        {  		  
        LCD_SDA=HIGH;
        }
        else 
        {      
        LCD_SDA=LOW;
        }
        Delay_1ms(1);
        LCD_SCL=HIGH;
        Delay_1ms(1);
        LCD_SCL=LOW;
        Delay_1ms(1);
        IIC_Byte<<=1;		//loop
    }
    LCD_SDA=1;
    Delay_1ms(1);
    LCD_SCL=1;
    Delay_1ms(1);
    LCD_SCL=0;
    Delay_1ms(1);
}

void LCD_WrDat(unsigned char dat)
{
    IIC_Start();
    Write_IIC_Byte(IICADRR);			
    Write_IIC_Byte(0x40);			//write data
    Write_IIC_Byte(dat);
    IIC_Stop();
}

void LCD_WrCmd(unsigned char cmd)
{
    IIC_Start();
    Write_IIC_Byte(IICADRR);              //Slave Address,SA0=0
    Write_IIC_Byte(0x00);			//write command
    Write_IIC_Byte(cmd); 
    IIC_Stop();
}

//========================================================================
// Function:void LCD_Set_Pos(unsigned char x, unsigned char y)|函数:  void LCD_Set_Pos(unsigned char x, unsigned char y)
// Description:Set the coordinates of the pixels|描述:设置像素点的坐标
// Parameter: x,y:The coordinate value (x, y) of the point， the range of x is 0-127, and the range of y is 0-64|参数:点的坐标值(x,y),x的范围0～127，y的范围0～64
// 
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-04-09|日期: 2021-04-09
// Author: sky-vocality|作者: sky-vocality
// Note:|备注:
//	
//	
//	
//	
//	
//========================================================================
void LCD_Set_Pos(unsigned char x, unsigned char y)
{
    LCD_WrCmd(0xb0+y);
    LCD_WrCmd(((x&0xf0)>>4)|0x10);
    LCD_WrCmd((x&0x0f)); 
} 

//========================================================================
// Function:void LCD_Fill(unsigned char bmp_data)|函数:void LCD_Fill(unsigned char bmp_data)
// Description:Initial screen clearing|描述:初始清屏
// Parameter: bmp_data:Populated data|参数:填充的数据
// 
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-04-09|日期: 2021-04-09
// Author: sky-vocality|作者: sky-vocality
// Note:|备注:
//	
//	
//	
//	
//	
//========================================================================
void LCD_Fill(unsigned char bmp_data)
{
    unsigned char y,x;

    for(y=0;y<8;y++)
    {
        LCD_WrCmd(0xb0+y);
        LCD_WrCmd(0x01);
        LCD_WrCmd(0x10);
        for(x=0;x<X_WIDTH;x++)
            LCD_WrDat(bmp_data);
    }
}

//========================================================================
// Function:void LCD_CLS(void)|函数:void LCD_CLS(void)
// Description:Screen clearing|描述:清屏
// Parameter:|参数:
// 
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-04-09|日期: 2021-04-09
// Author: sky-vocality|作者: sky-vocality
// Note:|备注:
//	
//	
//	
//	
//	
//========================================================================
void LCD_CLS(void)
{
    unsigned char y,x;	
    for(y=0;y<8;y++)
    {
        LCD_WrCmd(0xb0+y);
        LCD_WrCmd(0x01);
        LCD_WrCmd(0x10); 
        for(x=0;x<X_WIDTH;x++)
        LCD_WrDat(0);
    }
}

void LCD_Init(void)        
{ 
    //-----端口初始化----//
    GPIO_InitTypeDef GPIO_InitTypeDef;
    GPIO_InitTypeDef.Mode = GPIO_PullUp;//上拉准双向口
    GPIO_InitTypeDef.Pin = GPIO_Pin_3;
    GPIO_Inilize(GPIO_P2 ,&GPIO_InitTypeDef);
    GPIO_Inilize(GPIO_P3 ,&GPIO_InitTypeDef);
    GPIO_Inilize(GPIO_P4 ,&GPIO_InitTypeDef);

    LCD_SCL=1;              
    LCD_RST=0;
    Delay_Ms(500);
    LCD_RST=1;

    LCD_WrCmd(0xae);//--turn off oled panel
    LCD_WrCmd(0x00);//---set low column address
    LCD_WrCmd(0x10);//---set high column address
    LCD_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    LCD_WrCmd(0x81);//--set contrast control register
    LCD_WrCmd(0xcf); // Set SEG Output Current Brightness
    LCD_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
    LCD_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
    LCD_WrCmd(0xa6);//--set normal display
    LCD_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
    LCD_WrCmd(0x3f);//--1/64 duty
    LCD_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    LCD_WrCmd(0x00);//-not offset
    LCD_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
    LCD_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
    LCD_WrCmd(0xd9);//--set pre-charge period
    LCD_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    LCD_WrCmd(0xda);//--set com pins hardware configuration
    LCD_WrCmd(0x12);
    LCD_WrCmd(0xdb);//--set vcomh
    LCD_WrCmd(0x40);//Set VCOM Deselect Level
    LCD_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
    LCD_WrCmd(0x02);//
    LCD_WrCmd(0x8d);//--set Charge Pump enable/disable
    LCD_WrCmd(0x14);//--set(0x10) disable
    LCD_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
    LCD_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
    LCD_WrCmd(0xaf);//--turn on oled panel
    LCD_Fill(0x00);  //初始清屏
    LCD_Set_Pos(0,0);    
}

//========================================================================
// Function:void LCD_PutPixel(unsigned char x,unsigned char y)|函数:void LCD_PutPixel(unsigned char x,unsigned char y)
// Description:Draw a point|画一个点
// Parameter: x,y:The coordinate value of the point (x, y), the range of X is 0-127, and the range of Y is 0-64|参数:点的坐标值(x,y),x的范围0～127，y的范围0～64
// 
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-04-09|日期: 2021-04-09
// Author: sky-vocality|作者: sky-vocality
// Note:|备注:
//	
//	
//	
//	
//	
//========================================================================
void LCD_PutPixel(unsigned char x,unsigned char y)
{
    unsigned char data1;

    LCD_Set_Pos(x,(unsigned char)(y>>3)); 
    data1 =(unsigned char)(0x01<<(y%8));
    LCD_WrCmd((unsigned char)(0xb0+(y>>3)));
    LCD_WrCmd((unsigned char)(((x&0xf0)>>4)|0x10));
    LCD_WrCmd((unsigned char)((x&0x0f)|0x00));
    LCD_WrDat(data1);
}

//========================================================================
// Function:void LCD_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[])|函数:void LCD_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[])
// Description:Writes a set of ascii strings|写入一组标准ASCII字符串
// Parameter: x,y:Display location, y is the page range 0-7|参数:显示的位置（x,y），y为页范围0～7
//            *p:String to display|要显示的字符串
//
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-04-09|日期: 2021-04-09
// Author: sky-vocality|作者: sky-vocality
// Note:|备注:
//	
//	
//	
//	
//	
//======================================================================== 
void LCD_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[])
{
    unsigned char c=0,i=0,j=0;      
    while (ch[j]!='\0')
    {    
        c =ch[j]-32;
        if(x>126){x=0;y++;}
        LCD_Set_Pos(x,y);    
        for(i=0;i<6;i++)     
            LCD_WrDat(F6x8[c][i]);  
        x+=6;
        j++;
    }
}

//========================================================================
// Function:void LCD_PrintU16(unsigned char x,unsigned char y,unsigned int num)|函数:void LCD_PrintU16(unsigned char x,unsigned char y,unsigned int num)
// Description:display uint|显示无符号整型
// Parameter: x,y:Display location, y is the page range 0-7|参数:显示的位置（x,y），y为页范围0～7
//            num:uint to display|要显示的无符号整型
//
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-04-09|日期: 2021-04-09
// Author: sky-vocality|作者: sky-vocality
// Note:|备注:
//	
//	
//	
//	
//	
//========================================================================
void LCD_PrintU16(unsigned char x,unsigned char y,unsigned int num)
{
    unsigned char tmp[6],i;
    tmp[5]=0;
    tmp[4]=(unsigned char)(num%10+0x30);
    tmp[3]=(unsigned char)(num/10%10+0x30);
    tmp[2]=(unsigned char)(num/100%10+0x30);
    tmp[1]=(unsigned char)(num/1000%10+0x30);
    tmp[0]=(unsigned char)(num/10000%10+0x30);

    for(i=0;i<4;i++)
    {
        if(tmp[i]=='0')
            tmp[i]=' ';
        else
            break;
    }

    LCD_P6x8Str(x,y,tmp);

}

//========================================================================
// Function:void LCD_Print16(unsigned char x,unsigned char y,int num)|函数:void LCD_Print16(unsigned char x,unsigned char y,int num)
// Description:display uint|显示整型
// Parameter: x,y:Display location, y is the page range 0-7|参数:显示的位置（x,y），y为页范围0～7
//            num:uint to display|要显示的整型
//
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-04-11|日期: 2021-04-11
// Author: sky-vocality|作者: sky-vocality
// Note:|备注:
//	
//	
//	
//	
//	
//========================================================================
void LCD_Print16(unsigned char x,unsigned char y,int num)
{
	int i,j,flag;
    unsigned char stack[10];
	unsigned char tmp[10];
    i=0;
    if (num<0){
        flag=0;
        num=-num;
    }else{
        flag=1;
    }
    while (num/10!=0){
        stack[i]=(char)(48+num%10);
        num=num/10;
        i++;
    }
    stack[i]=(char)(48+num);
    if (flag==0){
        tmp[0]='-';
        for (j=i;j>-1;j--){
            tmp[i-j+1]=stack[j];
        }
        tmp[i+2]='\0';
    }else{
        for (j=i;j>-1;j--){
            tmp[i-j]=stack[j];
        }
        tmp[i+1]='\0';
    }

    LCD_P6x8Str(x,y,tmp);

}

//========================================================================
// Function:void LCD_PrintFloat(unsigned char x,unsigned char y,float num)|函数:void LCD_PrintFloat(unsigned char x,unsigned char y,float num)
// Description:display uint|显示浮点数
// Parameter: x,y:Display location, y is the page range 0-7|参数:显示的位置（x,y），y为页范围0～7
//            num:uint to display|要显示的浮点数
//
//       
// Return:|返回: 
// Version:VER1.0.1|版本: VER1.0.1
// Date:2021-04-11|日期: 2021-04-11
// Author: sky-vocality|作者: sky-vocality
// Note:|备注:
//	
//	
//	
//	
//	
//========================================================================
void LCD_PrintFloat(unsigned char x,unsigned char y,float num)
{
	int temp,i,j;
	int n = 10;
	char tmp[10];
    if(num>=0)//判断是否大于0
        tmp[0] = '+';
    else
    {
        tmp[0] = '-';
        num = -num;
    }
    temp = (int)num;//取整数部分
    for(i=0;temp!=0;i++)//计算整数部分的位数
        temp /=10;
    temp =(int)num;
    for(j=i;j>0;j--)//将整数部分转换成字符串型
    {
        tmp[j] = temp%10+'0';
        temp /=10;
    }
    tmp[i+1] = '.';
    num -=(int)num;
    for(i=i+2;i<n-1;i++)//将小数部分转换成字符串型
    {
        num*=10;
        tmp[i]=(int)num+'0';
        num-=(int)num;
    }
    tmp[n-1] = '\0';
	
    LCD_P6x8Str(x,y,tmp);
}
