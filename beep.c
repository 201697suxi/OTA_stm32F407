#include "stm32f4xx.h"
#include "sys.h"


void beep_init(void)
{
	GPIO_InitTypeDef 		GPIO_InitStructure;
	
	//�򿪶˿�F��Ӳ��ʱ�ӣ����ǶԶ˿�F����
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);

	
	//����GPIOF�ĵ�9 10��
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	
	//��ʼ��
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	
	PFout(8)=0;	
}

void beep_on(void)
{
	PFout(8)=1;	

}

void beep_off(void)
{
	PFout(8)=0;	

}