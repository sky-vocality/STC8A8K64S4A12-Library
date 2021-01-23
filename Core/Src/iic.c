/**
  ******************************************************************************
  * @file    iic.c
  * @author  PineconePi
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This file is used to Configure hardware IIC 
  * @License:GNU General Public License v3.0         
  ******************************************************************************
  * @attention
  *To operate IIC-related registers in host mode, P_SW2 = 0x80 is required. 
  *After  settings are completed, you must P_SW2 = 0x00
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
	/********************* The sample program is at the end of the iic.c file|ʾ��������iic.c�ļ�ĩβ************************/
	
#include "iic.h"
#include "intrins.h"
/********************* IIC port|IIC�˿���************************/
sbit    SDA         =   P1^4;
sbit    SCL         =   P1^5;
/********************* IIC slave mode related variables|IIC�ӻ�ģʽ��ر���************************/
bit isda;                                       //Equipment Address Mark|�豸��ַ��־
bit isma;                                       //Storage address flag|�洢��ַ��־
unsigned char addr;
unsigned char pdata buffer[256];
//========================================================================
// Function:void IIC_host_Slave_machine(unsigned char host_Slave_machine)|����: void IIC_host_Slave_machine(unsigned char host_Slave_machine)
// Description:Set IIC mode.|����: ����IICģʽ��
// Parameter:Host_Slave_machine: Host mode or slave mode|����: host_Slave_machine������ģʽ��ӻ�ģʽ
//       
//       
// Return:|����: 
// Version:VER1.0.0|�汾: VER1.0.0
// Date:2018-12-20|����: 2018-12-20
// ����: PineconePi
// ��ע:
//	
//	
//	
//	
//	
//========================================================================
void IIC_host_Slave_machine(unsigned char host_Slave_machine)
{
	if(host_Slave_machine==host_machine)
	{
		I2CCFG = 0xe0;                              //Enabling I2C host mode|ʹ��I2C����ģʽ
    I2CMSST = 0x00;
	}
	else if(host_Slave_machine==Slave_machine)
	{
		 P_SW2 = 0x80; 				//Operating hardware IIC register must set P_SW2 to 1|����Ӳ��IIC�Ĵ���������P_SW2Ϊ1
		I2CCFG = 0x81;                              //Enabling I2C slave mode|ʹ��I2C�ӻ�ģʽ
    I2CSLADR = IIC_Slave_machine_address;       //Set the slave device address to 5A|���ôӻ��豸��ַΪ5A
    I2CSLST = 0x00;
    I2CSLCR = 0x00;                             //Prohibit slave mode interruption|��ֹ�ӻ�ģʽ�ж�
	}
}
//========================================================================
// Function:void handle_Slave_machine()|����: void handle_Slave_machine()
// Description:IIC slave mode processing function.|����: IIC�ӻ�ģʽ��������
// Parameter:|����:
//       
//       
// Return:|����: 
// Version:VER1.0.0|�汾: VER1.0.0
// Date:2018-12-20|����: 2018-12-20
// Author: Pinecone Pi|����: PineconePi
// Note:|��ע:
//	
//	
//	
//	
//	
//========================================================================
void handle_Slave_machine()
{
	  isda = 1;                                   //Initialization of user variables|�û�������ʼ��
    isma = 1;
    addr = 0;
    I2CTXD = buffer[addr];
	     if (I2CSLST & 0x40)
        {
            I2CSLST &= ~0x40;                   //Handling START events|����START�¼�
        }
        else if (I2CSLST & 0x20)
        {
            I2CSLST &= ~0x20;                   //Handling RECV events|����RECV�¼�
            if (isda)
            {
                isda = 0;                       //Handling RECV events (RECV DEVICE ADDR)|����RECV�¼���RECV DEVICE ADDR��
            }
            else if (isma)
            {
                isma = 0;                       //Handling RECV events (RECV MEMORY ADDR)|����RECV�¼���RECV MEMORY ADDR��
                addr = I2CRXD;
                I2CTXD = buffer[addr];
            }
            else
            {
                buffer[addr++] = I2CRXD;        //Handling RECV events (RECV DATA)|����RECV�¼���RECV DATA��
            }
        }
        else if (I2CSLST & 0x10)
        {
            I2CSLST &= ~0x10;                   //Handling SEND events|����SEND�¼�
            if (I2CSLST & 0x02)
            {
                I2CTXD = 0xff;
            }
            else
            {
                I2CTXD = buffer[++addr];
            }
        }
        else if (I2CSLST & 0x08)
        {
            I2CSLST &= ~0x08;                   //Handling STOP events|����STOP�¼�
            isda = 1;
            isma = 1;
        }
	
}
//========================================================================
// Function:IIC Host Mode Related Processing Function|����:  IIC����ģʽ��ش�����
// Description:IIC host mode correlation processing function.|����:  IIC����ģʽ��ش�������
// Parameter:|����:
//       
//       
// Return:|����: 
// Version:VER1.0.0|�汾: VER1.0.0
// Date:2018-12-20|����: 2018-12-20
// Author: Pinecone Pi|����: PineconePi
// Note:|��ע:
//	
//	
//	
//	
//	
//========================================================================
void Wait()
{
    while (!(I2CMSST & 0x40));
    I2CMSST &= ~0x40;
}

void Start()
{
    I2CMSCR = 0x01;                             //Send START command|����START����
    Wait();
}

void SendData(char dat)
{
    I2CTXD = dat;                               //Write data to data buffer|д���ݵ����ݻ�����
    I2CMSCR = 0x02;                             //Send SEND command|����SEND����
    Wait();
}

void RecvACK()
{
    I2CMSCR = 0x03;                             //���Ͷ�ACK����
    Wait();
}

char RecvData()
{
    I2CMSCR = 0x04;                             //Send read ACK command|����RECV����
    Wait();
    return I2CRXD;
}

void SendACK()
{
    I2CMSST = 0x00;                             //Setting ACK Signal|����ACK�ź�
    I2CMSCR = 0x05;                             //Send ACK commands|����ACK����
    Wait();
}

void SendNAK()
{
    I2CMSST = 0x01;                             //Setting NAK Signal|����NAK�ź�
    I2CMSCR = 0x05;                             //Send ACK commands|����ACK����
    Wait();
}

void Stop()
{
    I2CMSCR = 0x06;                             //Send STOP command|����STOP����
    Wait();
}

void wait_device()
{
    int i;

    for (i=0; i<3000; i++)
    {
        _nop_();
        _nop_();
        _nop_();
        _nop_();
    }
}
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