#include "stm32f4xx.h"
#include "flash.h"
#include <stdio.h>

/**
 * @bieaf ��������
 *	
 * @param sector_num    ������
 * @return 1
 */
int32_t sector_erase(uint32_t sector_num)
{
	int32_t rt=-1;
	
	/* ����FLASH*/
	FLASH_Unlock();
	
	if(FLASH_COMPLETE==FLASH_EraseSector(sector_num,VoltageRange_3))
		rt=0;
	/* ����FLASH*/
	FLASH_Lock();
	
	return rt;
}


/**
 * @bieaf д���ɸ�����
 *
 * @param addr       д��ĵ�ַ
 * @param buf       д�����ݵ���ʼ��ַ
 * @param word_size  ����
 * @return 
 */
void flash_program(uint32_t addr, uint32_t * buf, uint32_t word_size)
{	
	uint32_t i;
	
	/* ����FLASH*/
	FLASH_Unlock();
	
	for(i = 0; i < word_size; i++)	
	{
		/* ��FLASH��д*/
		FLASH_ProgramWord( addr + 4 * i, buf[i]);	
	}

	/* ����FLASH*/
	FLASH_Lock();
}



/**
 * @bieaf �����ɸ�����
 *
 * @param addr      �����ݵĵ�ַ
 * @param buf       �������ݵ�����ָ��
 * @param word_size ����
 * @return 
 */
void flash_read(uint32_t addr, uint32_t * buf, uint32_t word_size)
{
	uint32_t i=0;
	
	for(i =0; i < word_size; i++)
		buf[i] = *(__IO uint32_t*)(addr + 4 * i);
}


/* ��ȡ����ģʽ */
uint32_t read_start_mode(void)
{
	uint32_t mode = 0;
	
	flash_read((APPLICATION_2_ADDR + APPLICATION_2_SIZE - 4), &mode, 1);
	
	return mode;
}



/**
 * @bieaf ���г���ĸ���
 * @detail 1.����Ŀ�ĵ�ַ
 *         2.Դ��ַ�Ĵ��뿽����Ŀ�ĵ�ַ
 *         3.����Դ��ַ
 *
 * @param  ���˵�Դ��ַ
 * @param  ���˵�Ŀ�ĵ�ַ
 * @return ���˵ĳ����С
 */
void move_code(uint32_t dest_addr, uint32_t src_addr,uint32_t word_size)
{
	uint32_t temp[256];
	uint32_t i;
	
	/*1.����Ŀ�ĵ�ַ*/
	printf("> start erase application 1 sector......\r\n");
	
	//����
	sector_erase(APPLICATION_1_SECTOR);
	
	printf("> erase application 1 success......\r\n");
	
	/*2.��ʼ����*/	

	printf("> start copy......\r\n");
	
	for(i = 0; i <word_size/1024; i++)
	{
		flash_read((src_addr + i*1024), temp, 256);
		flash_program((dest_addr + i*1024), temp, 256);
	}
	
	printf("> copy finish......\r\n");
	
	/*3.����Դ��ַ*/
	
	printf("> start erase application 2 sector......\r\n");
	
	//����
	sector_erase(APPLICATION_2_SECTOR);
	
	printf("> erase application 2 success......\r\n");
	
}

/* ���û������ջ��ֵ */
__asm void MSR_MSP (uint32_t ulAddr) 
{
    MSR MSP, r0 			                   //set Main Stack value
    BX r14
}





void iap_execute_app (uint32_t app_addr)
{
	jump_func jump_to_app; 
	
	//printf("* ( __IO uint32_t * ) app_addr  =%08X ,app_addr=%08X\r\n",* ( __IO uint32_t * ) app_addr,app_addr );
    
	//if ( ( ( * ( __IO uint32_t * ) app_addr ) & 0x2FFE0000 ) == 0x200006B0 )	//���ջ����ַ�Ƿ�Ϸ�.
	//{ 
		//printf("stack is legal\r\n");
		
		jump_to_app = (jump_func) * ( __IO uint32_t *)(app_addr + 4);			//�û��������ڶ�����Ϊ����ʼ��ַ(��λ��ַ)		
		
		MSR_MSP( * ( __IO uint32_t * ) app_addr );								//��ʼ��APP��ջָ��(�û��������ĵ�һ�������ڴ��ջ����ַ)
		
		jump_to_app();															//��ת��APP.
	//}
	
	//printf("stack is illegal\r\n");
}
