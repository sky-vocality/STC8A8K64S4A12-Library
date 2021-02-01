/**
 ******************************************************************************
 * @file    jy901.c
 * @author  sky-vocality
 * @version V1.0.0
 * @date    25-February-2021
 * @brief  This file is used for update jy901 data
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

#include "jy901.h"

JY901_InitDefine jy901;

//========================================================================
// Function:void jy901_update()|函数:  void jy901_update()
// Description:Update jy901 data with IIC|描述:  使用IIC更新jy901的数据
// Parameter:|参数:
//       
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2021-02-01|日期: 2021-02-01
// Author: sky-vocality|作者: sky-vocality
// Note:|备注:
//	
//	
//	
//	
//	
//========================================================================
void jy901_update()
{
    unsigned char p0 = 0;
    int temp = 0;
    unsigned char p1 = 0;
    Start();                                    //Send Start Command|发送起始命令
    SendData(IICAddr<<1);                          //Send device address + read command|发送设备地址+读命令
    SendData(ROLL);
    Start();
    SendData((IICAddr<<1)|1);
    p0 = RecvData();                            //Read data 1|读取数据1
    SendACK();
    p1 = RecvData();                            //读取数据2|读取数据2
    SendNAK();
    Stop();                                     //Send stop command|发送停止命令
    temp = (p1<<8)|p0;
    jy901.Roll = (double)temp/32768*180;

    Start();                                    //Send Start Command|发送起始命令
    SendData(IICAddr<<1);                          //Send device address + read command|发送设备地址+读命令
    SendData(PITCH);
    Start();
    SendData((IICAddr<<1)|1);
    p0 = RecvData();                            //Read data 1|读取数据1
    SendACK();
    p1 = RecvData();                            //读取数据2|读取数据2
    SendNAK();
    Stop();                                     //Send stop command|发送停止命令
    temp = (p1<<8)|p0;
    jy901.Pitch = (double)temp/32768*180;

    Start();                                    //Send Start Command|发送起始命令
    SendData(IICAddr<<1);                          //Send device address + read command|发送设备地址+读命令
    SendData(YAW);
    Start();
    SendData((IICAddr<<1)|1);
    p0 = RecvData();                            //Read data 1|读取数据1
    SendACK();
    p1 = RecvData();                            //读取数据2|读取数据2
    SendNAK();
    Stop();                                     //Send stop command|发送停止命令
    temp = (p1<<8)|p0;
    jy901.Yaw = (double)temp/32768*180;
}
