#include "stm32f4xx.h"
#include "sys.h"
#include "usart.h"

void tim3_init(void)
{
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	NVIC_InitTypeDef   		NVIC_InitStructure;
	//��TIM3Ӳ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	
	//TIM3��Ӳ��ʱ��Ƶ��=84MHz/(TIM_Prescaler+1)=84MHz/(8399+1)=10000Hz
	TIM_TimeBaseStructure.TIM_Period = 9;//����ֵ�����ڶ�ʱʱ������ã�0 ->9��10�μ���
	TIM_TimeBaseStructure.TIM_Prescaler = 8399;//Ԥ��Ƶֵ������
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;//F407û�У�����Ҫ����
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���������0 -> TIM_Period��Ȼ��ͻᴥ��ʱ������ж�
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	
	/* ��ʱ��ʱ������ж�ʹ�� */
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	//����NVIC�����ڴ�TIM3���ж�����ͨ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;	//TIM3������ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//��ռ���ȼ�0xF
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//��Ӧ���ȼ�0xF
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//��������ͨ��
	NVIC_Init(&NVIC_InitStructure);
	
	
	/* ʹ��TIM3���� */
	TIM_Cmd(TIM3, ENABLE);	
}

void TIM3_IRQHandler(void)
{
	static uint32_t usart1_rx_cnt_last=0;
	
	//���ʱ������жϵı�־λ�Ƿ���λ
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{
		if(g_usart1_rx_cnt)
		{
			//����ȣ����ʾ����3Ŀǰ�����������
			if(g_usart1_rx_cnt == usart1_rx_cnt_last)
			{
				g_usart1_rx_end=1;
			}
			else
			{
				usart1_rx_cnt_last = g_usart1_rx_cnt;
			}
		}
		
		//��ձ�־λ
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}
