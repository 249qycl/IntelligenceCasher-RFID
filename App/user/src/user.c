#include "common.h"
#include "include.h"

/***********************************************************************************************
*������	: systemInit 
*��  ��	: ϵͳ���ó�ʼ�� 
*��  ��	: None
*����ֵ	: None
*��  ��	: zyl
*��  ��	: 2019/12/30  
***********************************************************************************************/
void systemInit()
{
	pit_init_ms(PIT0, 5);
	uart_init (UART3, 115200); 
	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_4);

	NVIC_SetPriority(UART3_RX_TX_IRQn, 0);
	NVIC_SetPriority(PIT0_IRQn, 1);

	set_vector_handler(UART3_RX_TX_VECTORn, UART3_RX_Handler);
	set_vector_handler(PIT0_VECTORn, PIT_Hander);

	enable_irq(PIT0_IRQn);
	uart_rx_irq_en(UART3); //�����ڽ����ж�
	//	ASSERT(enter_init());
	//	lcd_init(WHITE);                    //��Ļ��ʼ��
}

/***********************************************************************************************
*������	: rfidReaderInit 
*��  ��	: RFID��������ʼ�� 
*��  ��	: None
*����ֵ	: None
*��  ��	: zyl
*��  ��	: 20I19/12/31  
***********************************************************************************************/
void rfidReaderInit()
{
	while (1)
	{
		uart_putbuff(UART3, tHardwareCmd, 8);
		//��ʾ�豸��Ϣ�˶���
		printf("��Ϣ�˶���\n");
		DELAY_MS(20);
		while(Error==getBuffer(pBuff));
 		if (Ok == bufcmp(pBuff, rHardwareInfo, 4))
		{
			printf("RFID��ʼ���ɹ���\n");//��ʾ�豸��ʼ���ɹ���Ϣ
			break;
		} 
	}
}

