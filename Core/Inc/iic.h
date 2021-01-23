/**
  ******************************************************************************
  * @file    iic.h
  * @author  PineconePi
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This file is used to Configure hardware IIC 
  * @License:GNU General Public License v3.0         
  ******************************************************************************
  * @attention
  *To operate IIC-related registers in host mode, P_SW2 = 0x80 is required. 
  *After  settings are completed, you must P_SW2 = 0x00
  *The sample program is at the end of the file iic.c
  *  
  * 
  * 
  * 
  * 
  *
  * 
  ******************************************************************************
	**/
#ifndef _IIC_H_
#define _IIC_H_

#include "system.h"


#define host_machine 0  //Host mode|主机模式
#define Slave_machine 1 //Slave mode|从机模式

#define IIC_Slave_machine_address 0x5a //Slave device address 5A|从机设备地址为5A

void IIC_host_Slave_machine(unsigned char host_Slave_machine);//Set IIC mode (host mode, slave mode)|设置IIC模式（主机模式，从机模式）
void handle_Slave_machine();//Slave mode processing function|从机模式处理函数
/********************* IIC主机模式相关处理函数************************/
void Wait();
void Start();
void SendData(char dat);
void RecvACK();
char RecvData();
void SendACK();
void SendNAK();
void Stop();
void wait_device();
#endif

//========================================================================
// Function:IIC Host Mode Related Processing Function Example|函数:  IIC主机模式相关处理函数示例
// Description: IIC host mode correlation processing function example.|描述:  IIC主机模式相关处理函数示例。
// Parameter:|参数:     
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2018-12-20|日期: 2018-12-20
// Author: Pinecone Pi|作者: PineconePi
// Example:|示例：
//    P_SW2 = 0x80;																	
//    IIC_host_Slave_machine（host_machine);       //Setting up host mode|设置为主机模式
//    Start();                                    //Send Start Command|发送起始命令
//    SendData(0xa0);                             //Send Device Address + Write Command|发送设备地址+写命令
//    RecvACK();
//    SendData(0x00);                             //Send high bytes of storage address|发送存储地址高字节
//    RecvACK();
//    SendData(0x00);                             //Send Storage Address Low Byte|发送存储地址低字节
//    RecvACK();
//    SendData(0x12);                             //Write test data 1|写测试数据1
//    RecvACK();
//    SendData(0x78);                             //Write test data 2|写测试数据2
//    RecvACK();
//    Stop();                                     //Send stop command|发送停止命令
//    Delay();                                    //Waiting for the device to write data|等待设备写数据
//    Start();                                    //Send Start Command|发送起始命令
//    SendData(0xa0);                             //Send Device Address + Write Command|发送设备地址+写命令
//    RecvACK();
//    SendData(0x00);                             //Send high bytes of storage address|发送存储地址高字节
//    RecvACK();
//    SendData(0x00);                             //Send Storage Address Low Byte|发送存储地址低字节
//    RecvACK();
//    Start();                                    //Send Start Command|发送起始命令
//    SendData(0xa1);                             //Send device address + read command|发送设备地址+读命令
//    RecvACK();
//    P0 = RecvData();                            //Read data 1|读取数据1
//    SendACK();
//    P2 = RecvData();                            //读取数据2|读取数据2
//    SendNAK();
//    Stop();                                     //Send stop command|发送停止命令
//    P_SW2 = 0x00;
//========================================================================