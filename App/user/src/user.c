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
	pit_init_ms(PIT0, 5);
	uart_init (UART3, 115200); 
	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_4);

	NVIC_SetPriority(UART3_RX_TX_IRQn, 0);
	NVIC_SetPriority(PIT0_IRQn, 1);

	set_vector_handler(UART3_RX_TX_VECTORn, UART3_RX_Handler);
	set_vector_handler(PIT0_VECTORn, PIT_Hander);

	enable_irq(PIT0_IRQn);
	uart_rx_irq_en(UART3); //开串口接收中断
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
		uart_putbuff(UART3, tHardwareCmd, 8);
		//显示设备信息核对中
		printf("信息核对中\n");
		DELAY_MS(20);
		while(Error==getBuffer(pBuff));
 		if (Ok == bufcmp(pBuff, rHardwareInfo, 4))
		{
			printf("RFID初始化成功！\n");//显示设备初始化成功信息
			break;
		} 
	}
}

