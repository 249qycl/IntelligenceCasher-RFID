#include "common.h"
#include "include.h"

/***********************************************************************************************
*函数名	: systemInit 
*功  能	: 系统配置初始化 
*参  数	: None
*返回值	: None
*作  者	: zyl
*日  期	: 2019/12/30  
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
	//	lcd_init(WHITE);                    //屏幕初始化
}

/***********************************************************************************************
*函数名	: rfidReaderInit 
*功  能	: RFID读卡器初始化 
*参  数	: None
*返回值	: None
*作  者	: zyl
*日  期	: 20I19/12/31  
***********************************************************************************************/
void rfidReaderInit()
{
	while (1)
	{
		if (0 == MSG_stack.run_state)
		{
			uart_putbuff(UART3, T_hardware_query, 8);
			//显示设备信息核对中
			DELAY_MS(20);
			if (1 == MSG_stack.rx_finish)
			{
				if (0 == strncmp((const char *)MSG_stack.rx_buff, (const char *)R_hardware_answer, 18))
				{
					MSG_stack.run_state = 1;
					MSG_stack.rx_finish = 0;
					//显示设备初始化成功信息
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
*函数名	: rxBuffReset 
*功  能	: 串口数据接收缓冲区复位 
*参  数	: None
*返回值	: None
*作  者	: zyl
*日  期	: 2019/12/31  
***********************************************************************************************/
void rxBuffReset()
{
	MSG_stack.rx_timer = 0;
	MSG_stack.rx_flag = 0;
	MSG_stack.rx_len = 0;
	MSG_stack.rx_finish = 1;
}

/***********************************************************************************************
*函数名	: rxBuffRun 
*功  能	: 串口数据接收缓冲区运行 
*参  数	: None
*返回值	: None
*作  者	: zyl
*日  期	: 2019/12/31  
***********************************************************************************************/
void rxBuffRun(uint8 data)
{
	MSG_stack.rx_buff[MSG_stack.rx_len] = data;
	MSG_stack.rx_len++;
	MSG_stack.rx_flag = 1;
	MSG_stack.rx_timer = 0;
}

/***********************************************************************************************
*函数名	: answerAnalysis 
*功  能	: 信息帧信息解析 
*参  数	: None
*返回值	: None
*作  者	: zyl
*日  期	: 2019/12/31  
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
*函数名	: RX_query
*功  能	: 轮询信息接收 
*参  数	: None
*返回值	: None
*作  者	: zyl
*日  期	: 2020/1/1  
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
//启动轮询信息接收Flag=2，统计接收轮数，轮数足够则切换Flag
//启动轮询时，载入接收轮数
//人为设定轮询模式