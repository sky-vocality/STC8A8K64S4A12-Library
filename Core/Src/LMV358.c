/**
  ******************************************************************************
  * @file    LMV358.c
  * @author  NULL(基于PineconePi(基于宏晶科技STC15库函数进行修改)库函数进行修改)
  * @version V1.0.0
  * @date    12-April-2021
  * @brief  This file is used for config LMV358
  * @License:GNU General Public License v3.0         
  ******************************************************************************
  * @attention
  *
  *  
  * 
  * 
  ******************************************************************************
**/
#include "LMV358.h"
ad_data_max[6] = {500,500,500,500,500,500};
ad_data_min[6] = { 0,0,0,0,0,0};   	
left = 0, right = 0;
left1 = 0, right1 = 0;
left2 = 0, right2 = 0;
//========================================================================
// Function:void LMV358_start
// Description:start the LMV358|描述: ??LMV358??
// Parameter:NONE
//       
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-04-12|日期: 2021-4-12
// Author: NULL|作者: NULL
// Note:|备注:
//	
//	
//	
//	
//	
//========================================================================
void LMV358_start()
{
	ADC_InitTypeDef ADC_Init;
	ADC_Init.ADC_Px=ADC_P10;
	ADC_Init.ADC_Speed=ADC_180T;
	ADC_Init.ADC_Power=ENABLE;
	ADC_Init.ADC_AdjResult=ADC_RES_H2L8;
	ADC_Init.ADC_Polity=PolityHigh;
	ADC_Init.ADC_Interrupt=ENABLE;
	ADC_Inilize(&ADC_Init);
}
//========================================================================
// Function:void LMV358_start
// Description:Do data processing of ADC acquisition|描述: ????????
// Parameter:unsigned char k  |??:adc???  P1.x
//       
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-04-12|日期: 2021-4-12
// Author: NULL|作者: NULL
// Note:|备注:
//	
//	
//	
//	
//	
//========================================================================
unsigned int get_adc_averge(unsigned char k)
{
	unsigned char cnt=0;
	unsigned int sum=0;
	unsigned char i,j;
	unsigned int temp=0;
	unsigned int data_temp[times]={0};
	
	unsigned char tem[5]={0};
	
	for (cnt=0;cnt<times;cnt++)
  {
    data_temp[cnt] = Get_ADC10bitResult(k);
		Delay_Us(100);
	}
	
  for (j=0;j<times-1;j++)
  {
		for (i=0;i<times-j-1;i++)
    {
       if (data_temp[i]>data_temp[i+1] )
       {
          temp = data_temp[i];
          data_temp[i] = data_temp[i+1];
          data_temp[i+1] = temp;
       }
     }
   }
	
	 for(cnt=1;cnt<times-1;cnt++)
     sum += data_temp[cnt];

 return (sum/(times-2));
}
//========================================================================
// Function:void InductorNormal()
// Description:InductorNormal()|描述: ???
// Parameter:NONE
//       
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-04-12|日期: 2021-4-12
// Author: NULL|作者: NULL
// Note:|备注:
//	
//========================================================================
void InductorNormal()
{
	unsigned char num[6]={0};
	
	num[0]=get_adc_averge(0);
	num[1]=get_adc_averge(1);
	num[2]=get_adc_averge(2);
	num[3]=get_adc_averge(3);
	num[4]=get_adc_averge(4);
	num[5]=get_adc_averge(5);
	
	if (num[0] < ad_data_min[0])            ad_data_min[0] = num[0];     // ?????
	else if (num[0] > ad_data_max[0])       ad_data_max[0] = num[0];     // ?????
	if (num[1] < ad_data_min[1])            ad_data_min[1] = num[1];
	else if (num[1] > ad_data_max[1])       ad_data_max[1] = num[1]; 
	if (num[2] < ad_data_min[2])            ad_data_min[2] = num[2];
	else if (num[2] > ad_data_max[2])       ad_data_max[2] = num[2];
	if (num[3] < ad_data_min[3])            ad_data_min[3] = num[3];
	else if (num[3] > ad_data_max[3])       ad_data_max[3] = num[3];	
	if (num[4] < ad_data_min[4])            ad_data_min[4] = num[4];
	else if (num[4] > ad_data_max[4])       ad_data_max[4] = num[4];
	if (num[5] < ad_data_min[5])            ad_data_min[5] = num[5];
	else if (num[5] > ad_data_max[5])       ad_data_max[5] = num[5];
	
	left = (num[0] - ad_data_min[0]) * 100 / (ad_data_max[0] - ad_data_min[0]);     // ????????0--1000??
	right = (num[5] - ad_data_min[5]) * 100 / (ad_data_max[5] - ad_data_min[5]);
	left1 = (num[1] - ad_data_min[1]) * 100 / (ad_data_max[1] - ad_data_min[1]);     // ????????0--1000??
	right1 = (num[4] - ad_data_min[4]) * 100 / (ad_data_max[4] - ad_data_min[4]);
	left2 = (num[2] - ad_data_min[2]) * 100 / (ad_data_max[2] - ad_data_min[2]);     // ????????0--1000??
	right2 = (num[3] - ad_data_min[3]) * 100 / (ad_data_max[3] - ad_data_min[3]);
	
}

