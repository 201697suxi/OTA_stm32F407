#include "stm32f4xx.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "beep.h"
#include "flash.h"
#include "key.h"
#include "tim.h"
#include "ymodem.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @bieaf ����BootLoader������
 *
 * @param  none
 * @return none
 */
void bootloader_start(void)
{
    /*==========��ӡ��Ϣ==========*/

    switch(read_start_mode())										//��ȡ�Ƿ�����Ӧ�ó���
    {
		case STARTUP_NORMAL:										//��������
		{
			printf("> normal start......\r\n");
			break;
		}
		case STARTUP_UPDATE:										//����������
		{
			printf("> start update......\r\n");

			move_code(APPLICATION_1_ADDR,APPLICATION_2_ADDR,APPLICATION_2_SIZE);

			printf("> update success......\r\n");
			break;
		}
		case STARTUP_RESET:											//�ָ��������� Ŀǰûʹ��
		{
			printf("> restore to factory program......\r\n");
			break;
		}
		default:													//����ʧ��
		{
			printf("> error:%X!!!......\r\n", read_start_mode());
			return;
		}
    }

    /* ��ת��Ӧ�ó��� */
    printf("> start up......\r\n\r\n");

    iap_execute_app(APPLICATION_1_ADDR);
}

//������
int main(void)
{
	//led��ʼ��
	led_init();
	
	//beep��ʼ��
	beep_init();	
	
	//�������
	key_init();
	
	//��ʱ��3��ʼ��
	tim3_init();
	
	//����1��ʼ��������Ϊ115200bps
	usart1_init(115200);
	
	//�����ӳ�һ�ᣬȷ��оƬ�ڲ����ȫ����ʼ��,printf���������
	delay_ms(1000);
	
	printf("This is bootloader test by teacher.wen\r\n");

	//������û���κΰ������£������bootloader_start����
	if(key_sta_get() == 0)
		bootloader_start();

	printf("now start ymodem download\r\n");
	
    while(1)
    {
		ymodem_download();
    }


    return 0;
}



