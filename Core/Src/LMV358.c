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
unsigned int ad_data_min[6] = { 75,75,75,75,75,75};*/  //��·�ɼ�
unsigned int ad_data_max[2] = {240,240};  //��·�ɼ�
unsigned int ad_data_min[2] = { 75,75}; 
unsigned int left = 0, right = 0;
/*
int left1 = 0, right1 = 0;
int left2 = 0, right2 = 0;
*/

//========================================================================
// Function:LMV358_Init
// Description:start the LMV358|����: ��ʼ��LMV358ģ�飬������P1.x��adc�ɼ�
// Parameter:NONE
//       
//       
// Return:|����: 
// Version:VER1.0.0|�汾: VER1.0.0
// Date:2021-04-12|����: 2021-04-12
// Author: NULL|����: NULL
// Note:|��ע:
//	
//	
//	
//========================================================================

void LMV358_Init()
{
	ADC_InitTypeDef ADC_Init;
	ADC_Init.ADC_Px=ADC_P10;                          //���Ĵ˴��滻adc�ɼ���IO��
	ADC_Init.ADC_Speed=ADC_540T;
	ADC_Init.ADC_Power=ENABLE;
	ADC_Init.ADC_AdjResult=ADC_RES_H2L8;
	ADC_Init.ADC_Polity=PolityHigh;
	ADC_Init.ADC_Interrupt=ENABLE;
	ADC_Inilize(&ADC_Init);
}

//========================================================================
// Function:LMV358_GetAvergeData()
// Description:Do data processing of ADC acquisition|����:��ֵƽ���˲���ȡֵ����Ϊtimes(12)��
// Parameter:unsigned char k  |����: P1.x��ͨ����k
//       
//       
// Return:unsigned int|����: ���ش����ĵ���ź�(��ͨ��)
// Version:VER1.0.0|�汾: VER1.0.0
// Date:2021-04-12|����: 2021-04-12
// Author: NULL|����: NULL
// Note:|��ע:
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
// Description:Do InductorNormal work|����: ����·�ɼ��صĵ������һ������1000���ڣ�
// Parameter:NONE     
// Return:None|����: �޷���ֵ
// Version:VER1.0.0|�汾: VER1.0.0
// Date:2021-04-12|����: 2021-04-12
// Author: NULL|����: NULL
// Note:|��ע:
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
// Description:Output the final process|����: ��Ⱥ��㷨������
// Parameter:NONE     
// Return:error|����: 
// Version:VER1.0.0|�汾: VER1.0.0
// Date:2021-05-13|����: 2021-05-13
// Author: NULL|����: NULL
// Note:|��ע:
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
