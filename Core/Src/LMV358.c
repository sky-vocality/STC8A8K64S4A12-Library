/**
  ******************************************************************************
  * @file    LMV358.c
  * @author  NULL
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
  ********************************************************************************/
	
#include "LMV358.h"

/*unsigned int ad_data_max[6] = {240,240,240,240,240,240};
unsigned int ad_data_min[6] = { 75,75,75,75,75,75};*/  //六路采集
unsigned int ad_data_max[2] = {240,240};  //两路采集
unsigned int ad_data_min[2] = { 75,75}; 
unsigned int left = 0, right = 0;
/*
int left1 = 0, right1 = 0;
int left2 = 0, right2 = 0;
*/

//========================================================================
// Function:LMV358_Init
// Description:start the LMV358|描述: 初始化LMV358模块，并开启P1.x的adc采集
// Parameter:NONE
//       
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-04-12|日期: 2021-04-12
// Author: NULL|作者: NULL
// Note:|备注:
//	
//	
//	
//========================================================================

void LMV358_Init()
{
	ADC_InitTypeDef ADC_Init;
	ADC_Init.ADC_Px=ADC_P10;                          //更改此处替换adc采集的IO口
	ADC_Init.ADC_Speed=ADC_540T;
	ADC_Init.ADC_Power=ENABLE;
	ADC_Init.ADC_AdjResult=ADC_RES_H2L8;
	ADC_Init.ADC_Polity=PolityHigh;
	ADC_Init.ADC_Interrupt=ENABLE;
	ADC_Inilize(&ADC_Init);
}

//========================================================================
// Function:LMV358_GetAvergeData()
// Description:Do data processing of ADC acquisition|描述:中值平均滤波，取值次数为times(12)次
// Parameter:unsigned char k  |参数: P1.x的通道号k
//       
//       
// Return:unsigned int|返回: 返回处理后的电感信号(单通道)
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-04-12|日期: 2021-04-12
// Author: NULL|作者: NULL
// Note:|备注:
//	
//	
//========================================================================

unsigned int LMV358_GetAvergeData(unsigned char k)
{
	unsigned char cnt=0;
	unsigned char i,j;
	unsigned int temp=0;
	unsigned int data_temp[times]={0};
	//unsigned int t=0;
	for (cnt=0;cnt<times;cnt++)
    {
		
		if((data_temp[cnt] = Get_ADC10bitResult(k))==1024)
		{
			if(cnt==0)
			{
				data_temp[cnt]=0;
			}
			else
			{
				data_temp[cnt]=data_temp[cnt-1];
			}
		}
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
	
return data_temp[times/2];
}

//========================================================================
// Function:LMV358_InductorNormal()
// Description:Do InductorNormal work|描述: 对六路采集回的电感做归一化处理（1000以内）
// Parameter:NONE     
// Return:None|返回: 无返回值
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-04-12|日期: 2021-04-12
// Author: NULL|作者: NULL
// Note:|备注:
//	
//========================================================================

void LMV358_InductorNormal()
{
	//unsigned int num[6]={0};
	unsigned int num[2]={0};
	
	/*num[0]=LMV358_GetAvergeData(0);
	num[1]=LMV358_GetAvergeData(1);*/
	num[0]=LMV358_GetAvergeData(1);
	num[1]=LMV358_GetAvergeData(4);
	/*num[4]=LMV358_GetAvergeData(4);
	num[5]=LMV358_GetAvergeData(5);*/
	
	/*if (num[0] < ad_data_min[0])            ad_data_min[0] = num[0];     
	else if (num[0] > ad_data_max[0])       ad_data_max[0] = num[0];     
	if (num[1] < ad_data_min[1])            ad_data_min[1] = num[1];
	else if (num[1] > ad_data_max[1])       ad_data_max[1] = num[1]; */
	if (num[0] < ad_data_min[0])            ad_data_min[0] = num[0];
	else if (num[0] > ad_data_max[0])       ad_data_max[0] = num[0];
	if (num[1] < ad_data_min[1])            ad_data_min[1] = num[1];
	else if (num[1] > ad_data_max[1])       ad_data_max[1] = num[1];	
	/*if (num[4] < ad_data_min[4])            ad_data_min[4] = num[4];
	else if (num[4] > ad_data_max[4])       ad_data_max[4] = num[4];
	if (num[5] < ad_data_min[5])            ad_data_min[5] = num[5];
	else if (num[5] > ad_data_max[5])       ad_data_max[5] = num[5];*/
	
	/*left = (num[0] - ad_data_min[0]) * 100 / (ad_data_max[0] - ad_data_min[0]);     
	right = (num[5] - ad_data_min[5]) * 100 / (ad_data_max[5] - ad_data_min[5]);
	left1 = (num[1] - ad_data_min[1]) * 100 / (ad_data_max[1] - ad_data_min[1]);     
	right1 = (num[4] - ad_data_min[4]) * 100 / (ad_data_max[4] - ad_data_min[4]);*/
	left = (num[0] - ad_data_min[0]) * 100 / (ad_data_max[0] - ad_data_min[0]);     
	right = (num[1] - ad_data_min[1]) * 100 / (ad_data_max[1] - ad_data_min[1]);
	
}

//========================================================================
// Function:LMV358_Output()
// Description:Output the final process|描述: 差比和算法输出误差
// Parameter:NONE     
// Return:error|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-05-13|日期: 2021-05-13
// Author: NULL|作者: NULL
// Note:|备注:
//	
//========================================================================

float LMV358_Output()
{
	float error;
	//LMV358_InductorNormal();
	//error = ((right-left)<<7)/(right+left)*1.;
	error = (int)LMV358_GetAvergeData(1) - (int)LMV358_GetAvergeData(4);
	return error;
}

void LMV358_timer_init()
{
	TIM_InitTypeDef TIM_InitTypeDef;
	LMV358_Init();
	TIM_InitTypeDef.TIM_Mode = TIM_16BitAutoReload;
	TIM_InitTypeDef.TIM_Polity = PolityLow;
	TIM_InitTypeDef.TIM_Interrupt = ENABLE;
	TIM_InitTypeDef.TIM_ClkSource = TIM_CLOCK_1T;
	TIM_InitTypeDef.TIM_ClkOut = ENABLE;
	TIM_InitTypeDef.TIM_Value = 41536;
	TIM_InitTypeDef.TIM_Run = ENABLE;
	Timer_Inilize(Timer2, &TIM_InitTypeDef);
}
