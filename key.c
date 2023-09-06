#include "stm32f4xx.h"
#include "sys.h"


void key_init(void)
{
	GPIO_InitTypeDef 		GPIO_InitStructure;
	
	//�򿪶˿�A��Ӳ��ʱ�ӣ����ǶԶ˿�A����
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);	

	//�򿪶˿�E��Ӳ��ʱ�ӣ����ǶԶ˿�E����
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	
	//����GPIOA�ĵ�0������
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	//��ʼ��
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//����GPIOE�ĵ�2 3 4������
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;

	//��ʼ��
	GPIO_Init(GPIOE,&GPIO_InitStructure);	
}

uint32_t key_sta_get(void)
{
	uint32_t key_sta=0;
	
	if(PAin(0) == 0)
		key_sta|=1<<0;
	
	if(PEin(2) == 0)
		key_sta|=1<<1;
	
	if(PEin(3) == 0)
		key_sta|=1<<2;
	
	if(PEin(4) == 0)
		key_sta|=1<<3;
	
	return key_sta;
}

