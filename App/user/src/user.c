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
	//    pit_init_ms(PIT0,5);
	//    NVIC_SetPriorityGrouping(NVIC_PriorityGroup_4);
	//
	//    NVIC_SetPriority(UART3_RX_TX_VECTORn,0);
	//    NVIC_SetPriority(PIT0_IRQn,1);
	//
	//    set_vector_handler(UART3_RX_TX_VECTORn , UART3_RX_Handler);
	//    set_vector_handler(PIT0_VECTORn , PIT_Hander);

	//    enable_irq(PIT0_IRQn);
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
		if (0 == MSG_stack.run_state)
		{
			uart_putbuff(UART3, T_hardware_query, 8);
			//��ʾ�豸��Ϣ�˶���
			DELAY_MS(20);
			if (1 == MSG_stack.rx_finish)
			{
				if (0 == strncmp((const char *)MSG_stack.rx_buff, (const char *)R_hardware_answer, 18))
				{
					MSG_stack.run_state = 1;
					MSG_stack.rx_finish = 0;
					//��ʾ�豸��ʼ���ɹ���Ϣ
					break;
				}
				else
				{
					MSG_stack.rx_finish = 0;
				}
			}
		}
	}
}

/***********************************************************************************************
*������	: rxBuffReset 
*��  ��	: �������ݽ��ջ�������λ 
*��  ��	: None
*����ֵ	: None
*��  ��	: zyl
*��  ��	: 2019/12/31  
***********************************************************************************************/
void rxBuffReset()
{
	MSG_stack.rx_timer = 0;
	MSG_stack.rx_flag = 0;
	MSG_stack.rx_len = 0;
	MSG_stack.rx_finish = 1;
}

/***********************************************************************************************
*������	: rxBuffRun 
*��  ��	: �������ݽ��ջ��������� 
*��  ��	: None
*����ֵ	: None
*��  ��	: zyl
*��  ��	: 2019/12/31  
***********************************************************************************************/
void rxBuffRun(uint8 data)
{
	MSG_stack.rx_buff[MSG_stack.rx_len] = data;
	MSG_stack.rx_len++;
	MSG_stack.rx_flag = 1;
	MSG_stack.rx_timer = 0;
}

/***********************************************************************************************
*������	: answerAnalysis 
*��  ��	: ��Ϣ֡��Ϣ���� 
*��  ��	: None
*����ֵ	: None
*��  ��	: zyl
*��  ��	: 2019/12/31  
***********************************************************************************************/
void answerAnalysis()
{
	if (0x01 == MSG_stack.rx_buff[1])
	{
		switch (MSG_stack.rx_buff[2])
		{
		case ERROR:
			MSG_stack.run_state = ERROR;
			break;
		case STOP_SUCCESS:
			MSG_stack.run_state = STOP_SUCCESS;
			break;
		case SELECT_SUCCESS:
			MSG_stack.run_state = SELECT_SUCCESS;
			break;
		case MEMORY_READ:
			MSG_stack.run_state = MEMORY_READ;
			break;
		case MEMORY_WRITE:
			MSG_stack.run_state = MEMORY_WRITE;
			break;
		}
	}
}

/***********************************************************************************************
*������	: RX_query
*��  ��	: ��ѯ��Ϣ���� 
*��  ��	: None
*����ֵ	: None
*��  ��	: zyl
*��  ��	: 2020/1/1  
***********************************************************************************************/
void rxQuery(uint8 data)
{
	static uint8 msg_flag = 0, counter = 0;
	if (RX_QUERY == MSG_stack.rx_flag && MSG_stack.query_times > 0)
	{
		R_answer_right.buff[counter++] = data;
		if (BEGIN == data && 0 == msg_flag)
		{
			msg_flag = !msg_flag;
		}
		else if (END == data && 1 == msg_flag)
		{
			msg_flag = !msg_flag;
			counter = 0;
			MSG_stack.query_times--;
			memcpy(MSG_stack.EPC[MSG_stack.SP++].buff, R_answer_right.msg.EPC.buff, 12);
			if (0 == MSG_stack.query_times)
				MSG_stack.rx_flag = RX_NONE;
		}
	}
}
//������ѯ��Ϣ����Flag=2��ͳ�ƽ��������������㹻���л�Flag
//������ѯʱ�������������
//��Ϊ�趨��ѯģʽ