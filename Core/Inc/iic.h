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


#define host_machine 0  //Host mode|����ģʽ
#define Slave_machine 1 //Slave mode|�ӻ�ģʽ

#define IIC_Slave_machine_address 0x5a //Slave device address 5A|�ӻ��豸��ַΪ5A

void IIC_host_Slave_machine(unsigned char host_Slave_machine);//Set IIC mode (host mode, slave mode)|����IICģʽ������ģʽ���ӻ�ģʽ��
void handle_Slave_machine();//Slave mode processing function|�ӻ�ģʽ������
/********************* IIC����ģʽ��ش�����************************/
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
// Function:IIC Host Mode Related Processing Function Example|����:  IIC����ģʽ��ش�����ʾ��
// Description: IIC host mode correlation processing function example.|����:  IIC����ģʽ��ش�����ʾ����
// Parameter:|����:     
// Return:|����: 
// Version:VER1.0.0|�汾: VER1.0.0
// Date:2018-12-20|����: 2018-12-20
// Author: Pinecone Pi|����: PineconePi
// Example:|ʾ����
//    P_SW2 = 0x80;																	
//    IIC_host_Slave_machine��host_machine);       //Setting up host mode|����Ϊ����ģʽ
//    Start();                                    //Send Start Command|������ʼ����
//    SendData(0xa0);                             //Send Device Address + Write Command|�����豸��ַ+д����
//    RecvACK();
//    SendData(0x00);                             //Send high bytes of storage address|���ʹ洢��ַ���ֽ�
//    RecvACK();
//    SendData(0x00);                             //Send Storage Address Low Byte|���ʹ洢��ַ���ֽ�
//    RecvACK();
//    SendData(0x12);                             //Write test data 1|д��������1
//    RecvACK();
//    SendData(0x78);                             //Write test data 2|д��������2
//    RecvACK();
//    Stop();                                     //Send stop command|����ֹͣ����
//    Delay();                                    //Waiting for the device to write data|�ȴ��豸д����
//    Start();                                    //Send Start Command|������ʼ����
//    SendData(0xa0);                             //Send Device Address + Write Command|�����豸��ַ+д����
//    RecvACK();
//    SendData(0x00);                             //Send high bytes of storage address|���ʹ洢��ַ���ֽ�
//    RecvACK();
//    SendData(0x00);                             //Send Storage Address Low Byte|���ʹ洢��ַ���ֽ�
//    RecvACK();
//    Start();                                    //Send Start Command|������ʼ����
//    SendData(0xa1);                             //Send device address + read command|�����豸��ַ+������
//    RecvACK();
//    P0 = RecvData();                            //Read data 1|��ȡ����1
//    SendACK();
//    P2 = RecvData();                            //��ȡ����2|��ȡ����2
//    SendNAK();
//    Stop();                                     //Send stop command|����ֹͣ����
//    P_SW2 = 0x00;
//========================================================================