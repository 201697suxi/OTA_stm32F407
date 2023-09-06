#include "stm32f4xx.h"
#include "sys.h"



void delay_us(uint32_t n)
{

	SysTick->CTRL = 0; // �ر�ϵͳ��ʱ��
	SysTick->LOAD = (SystemCoreClock/1000000*n)-1; // ���ü���ֵ168-1,���Ǵ�167 ~ 0 ����168�εļ�����1usʱ��ĵ���
	SysTick->VAL = 0;  // �������ֵҲ��ȥ��ձ�־λ
	SysTick->CTRL = 5; // ʹ��ϵͳ��ʱ����������ʱ��ԴΪ������ʱ�ӣ�HCLK����168MHz
	while ((SysTick->CTRL & 0x10000)==0);// ������ֵ����0��SysTick->CTRL�Ĵ�����COUNTFLAG����1�����Ǽ������

	SysTick->CTRL = 0; // �ر�ϵͳ��ʱ��
}


void delay_ms(uint32_t n)
{
	while(n--)
	{
		SysTick->CTRL = 0; // �ر�ϵͳ��ʱ��
		SysTick->LOAD = (SystemCoreClock/1000)-1; // ���ü���ֵ168000-1,���Ǵ�167999 ~ 0 ����168000�εļ�����1msʱ��ĵ���
		SysTick->VAL = 0;  // �������ֵҲ��ȥ��ձ�־λ
		SysTick->CTRL = 5; // ʹ��ϵͳ��ʱ����������ʱ��ԴΪ������ʱ�ӣ�HCLK����168MHz
		while ((SysTick->CTRL & 0x10000)==0);// ������ֵ����0��SysTick->CTRL�Ĵ�����COUNTFLAG����1�����Ǽ������
	}
	
	SysTick->CTRL = 0; // �ر�ϵͳ��ʱ��
}
