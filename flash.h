#ifndef __FLASH_H__
#define __FLASH_H__



/*=====�û�����(�����Լ��ķ�����������)=====*/
#define BootLoader_Size 		0x4000U			///< BootLoader�Ĵ�С 16K
#define Application_Size		0x20000U		///< Ӧ�ó���Ĵ�С 128K

#define APPLICATION_1_ADDR		0x08020000U		///< Ӧ�ó���1���׵�ַ������5�׵�ַ
#define APPLICATION_2_ADDR		0x08040000U		///< Ӧ�ó���2���׵�ַ������6�׵�ַ

#define APPLICATION_1_SECTOR	FLASH_Sector_5	///< Ӧ�ó���1������
#define APPLICATION_2_SECTOR	FLASH_Sector_6	///< Ӧ�ó���2������


#define APPLICATION_1_SIZE		0x20000U		///< Ӧ�ó���1�Ĵ�С
#define APPLICATION_2_SIZE		0x20000U		///< Ӧ�ó���2�Ĵ�С

/*==========================================*/


/* �����Ĳ��� */
#define STARTUP_NORMAL 0xFFFFFFFF	///< ��������
#define STARTUP_UPDATE 0xAAAAAAAA	///< ����������
#define STARTUP_RESET  0x5555AAAA	///< �ָ�����,Ŀǰûʹ��


/* ������ת���� */
typedef void (*jump_func)(void);


extern void flash_program(uint32_t addr, uint32_t * buf, uint32_t word_size);

extern void flash_read(uint32_t addr, uint32_t * buf, uint32_t word_size);

extern int32_t sector_erase(uint32_t sector_num);

extern uint32_t read_start_mode(void);

extern void move_code(uint32_t dest_addr, uint32_t src_addr,uint32_t word_size);

extern void iap_execute_app (uint32_t app_addr);


#endif
