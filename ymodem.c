#include "stm32f4xx.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "beep.h"
#include "flash.h"
#include "key.h"
#include "ymodem.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
 * @bieaf CRC-16 У��  ������ݴ���������Ƿ���ִ���ĳЩλ����ĳ��λ������ĳ������λ���󣩡�
 *
 * @param addr У�����ݿ�ʼ��ַ
 * @param num   ���ݳ���
 * @param crc   ��ʼ��CRCֵ
 * @return crc  ����CRC��ֵ
 */
#define POLY 			0x1021   //�����˶���ʽ��ֵ����CRC-16-CCITT��ʹ�õĶ���ʽ��
uint16_t crc16(uint8_t *addr,int32_t num, uint16_t crc)
{
	int32_t i; 
	//��һ��ʹ��ѭ��������У������ݣ���������Ϊ���ݵĳ���num
	for(;num > 0;num--)
	{
		//�ڶ�����ÿ�ε����У�ͨ��*addr++ȡ�����ݵ�һ���ֽڣ�����ָ��addr������ָ����һ���ֽڡ�
		
		crc = crc ^ (*addr++ << 8); //��ȡaddrָ����ֽ�ֵ������ָ����һ���ֽ�\
		����8λ,Ȼ����CRCֵ��������������������Ŀ����ȷ��ÿ���ֽڶ��ܶ�CRCֵ��ÿ���ֽڶ����д���CRC�㷨ͨ����λ����λ�Ʋ���������У��ֵ��\
		ͬʱҲ��Ҫ����ÿ���ֽڵ�λ�ϣ�����Ӧ�ض���Щλ������������
		
		//���������CRCֵ���λ�Ƿ�Ϊ1
		for(i = 0;i < 8; i++)
		{
			if(crc & 0x8000)//����ǣ���CRCֵ����1λ�������ʽ������������
				crc = (crc << 1) ^ POLY;
			else //������λΪ0����ֻ��CRCֵ����1λ��
				crc <<= 1;
		}
		//��֤CRCֵ����Ϊ16λ��ͨ����λ�������CRCֵ�ض�Ϊ16λ��
		crc &= 0xFFFF;
	}
	return(crc);
}

/* ���������Ĳ��� */
static enum UPDATE_STATE update_state = TO_START; //������¼�����ĵ�ǰ����

void ymodem_set_state(enum UPDATE_STATE state) 
{
	update_state = state;
}


/* ��ѯ�����Ĳ��� */
uint8_t ymodem_get_state(void)
{
	return update_state;
}

/* ymodem����ָ�� */
void ymodem_send_cmd(uint8_t command)
{
	USART_SendData(USART1,command); //ͨ������1��������
	//�ȴ����ݷ��ͳɹ�
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	USART_ClearFlag(USART1,USART_FLAG_TXE);
	
	delay_ms(10);
}

/* ���������� */
void update_set_down(void)
{
	//����һ�����ڱ��������ɵ��ض�ֵ��
	uint32_t update_flag = 0xAAAAAAAA;				// ��Ӧbootloader���������� 
	
	flash_program((APPLICATION_2_ADDR + APPLICATION_2_SIZE - 4), &update_flag,1 );//��ȥ4��Ϊ�˽�update_flag�洢������ĩβ��λ�á�
	
}

/**
 * @bieaf ymodem����
 *
 * @param none
 * @return none
 */
void ymodem_download(void)
{
	uint16_t crc = 0;
	
}
