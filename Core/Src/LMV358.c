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

unsigned int ad_data_max[6] = {240,240,240,240,240,240};
unsigned int ad_data_min[6] = { 75,75,75,75,75,75};   	
int left = 0, right = 0;
int left1 = 0, right1 = 0;
int left2 = 0, right2 = 0;

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
	ADC_Init.ADC_Speed=ADC_180T;
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
	unsigned int num[6]={0};
	
	num[0]=LMV358_GetAvergeData(0);
	num[1]=LMV358_GetAvergeData(1);
	num[2]=LMV358_GetAvergeData(2);
	num[3]=LMV358_GetAvergeData(3);
	num[4]=LMV358_GetAvergeData(4);
	num[5]=LMV358_GetAvergeData(5);
	
	if (num[0] < ad_data_min[0])            ad_data_min[0] = num[0];     
	else if (num[0] > ad_data_max[0])       ad_data_max[0] = num[0];     
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
	
	left = (num[0] - ad_data_min[0]) * 100 / (ad_data_max[0] - ad_data_min[0]);     
	right = (num[5] - ad_data_min[5]) * 100 / (ad_data_max[5] - ad_data_min[5]);
	left1 = (num[1] - ad_data_min[1]) * 100 / (ad_data_max[1] - ad_data_min[1]);     
	right1 = (num[4] - ad_data_min[4]) * 100 / (ad_data_max[4] - ad_data_min[4]);
	left2 = (num[2] - ad_data_min[2]) * 100 / (ad_data_max[2] - ad_data_min[2]);     
	right2 = (num[3] - ad_data_min[3]) * 100 / (ad_data_max[3] - ad_data_min[3]);
	
}

