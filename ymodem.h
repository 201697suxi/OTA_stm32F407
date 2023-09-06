#ifndef __YMODEM_H__
#define __YMODEM_H__


//AsCllУ���� 
#define SOH		0x01
#define STX		0x02
#define ACK		0x06
#define NACK	0x15
#define EOT		0x04
#define CCC		0x43



/* �����Ĳ��� 

ö��ֵ���������ڴ����б�ʾ���жϵ�ǰ����������״̬���Ӷ�ִ����Ӧ���߼�������

*/
enum UPDATE_STATE
{
	TO_START = 0x01, //��ʾ������ʼ�Ĳ��衣
	TO_RECEIVE_DATA = 0x02, //��ʾ�������ݵĲ��衣
	TO_RECEIVE_EOT1 = 0x03, //��ʾ���ս�����־1�Ĳ��衣
	TO_RECEIVE_EOT2 = 0x04, //��ʾ���ս�����־2�Ĳ��衣
	TO_RECEIVE_END = 0x05   //��ʾ���ս����Ĳ��衣
};



extern void ymodem_download(void);



#endif

