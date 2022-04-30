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
	uart_init(UART3, 115200);
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
		while (Error == getBuffer(pBuff));
		if (Ok == bufcmp(pBuff, rHardwareInfo, 4))
		{
			printf("RFID初始化成功！\n"); //显示设备初始化成功信息
			break;
		}
	}
	memset(pBuff, 0, 40);
}
/***********************************************************************************************
*函数名	: accountBalance 
*功  能	: 账目结算 
*参  数	: None
*返回值	: None
*作  者	: zyl
*日  期	: 20I19/12/31  
***********************************************************************************************/
void msgDebug()
{
	printf("商品卡：%d 张\n ",msgStack.sp);
	for (int i = 0; i < msgStack.sp; i++)
	{
		printf("卡%d号:\n", i+1);
		for (int j = 0; j < 12; j++)
			printf("%2x ", msgStack.mem[i].EPC.buff[j]);
		printf("---\n");
	}
	printf("身份卡：\n");
	for(int i=0;i<12;i++)
		printf("%2x ",msgStack.personMem.EPC.buff[i]);
	printf("\n");
}

void accountBalance()
{
	static uint8 step = 0;
	int sum1 = 0,sum2=0; //金额结算
	switch (step)
	{
	case 0:
		step = 1;
		msgStack.sp = 0;
		msgStack.timer = 0;
		msgStack.tmpMem.EPC.person.remain1=0;
		msgStack.tmpMem.EPC.person.remain2=0;
		cmdCtrl.isPollStart = 1; 
		break;
	case 1: //判断是否扫描完毕
		if(2==cmdCtrl.isPollStart)//若发送失败，重发
			cmdCtrl.isPollStart=1;
		if (1 == msgStack.tFlag&&0==cmdCtrl.isPollStart)
		{
			msgStack.tFlag = 0;
			if (msgStack.timer++ > 200) //1.0s
			{
				//判断是否存在人物
				//msgDebug();
				printf("扫描完毕\n");
				if(0xFFFF==msgStack.personMem.EPC.person.man)//存在人物
					step=2;
				else
				{
					step=0;//debug =0
					printf("未检测到付款卡\n");
				}
				DELAY_MS(2000);
			}
		}
		break;
	case 2:
		for (int i = 0; i < msgStack.sp; i++)
		{	
			sum1 += msgStack.mem[i].EPC.goods.price1;
			sum2 += msgStack.mem[i].EPC.goods.price2;
		}
		if (msgStack.personMem.EPC.person.remain1 > sum1)
		{
			//msgStack.tmpMem.EPC.person.remain1 = msgStack.personMem.EPC.person.remain1*10+msgStack.personMem.EPC.person.remain2- sum1*10-sum2;
			goodsPrint(sum1,sum2);
			step = 3;
		}
		else
		{
			step = 0;
			printf("余额不足\n");
		}
		//step=3;//debug
		break;
	case 3:
		memWrite(&step);
		break;
	case 4:
		if (0 == cmdCtrl.isWriteEPC)
			step=isLeave();
			//检测是否取卡
		break;
	}
	//结算完后开启新一轮，长期无串口中断，则认为接收完毕
} 

void memWrite(uint8 *step)
{
	static uint8 cmdSort = 0;//,flag=0;
	//补全标签选择命令
	switch (cmdSort)
	{
	case 0: //装填并发送选择指令
		if (0 == cmdCtrl.isWriteEPC)//确保无待写入数据
		{
			cmdSort = 1;
			cmdCtrl.isSelectParam = 1;
			bufcpy(tSelectCmd.msg.EPC.buff, msgStack.personMem.EPC.buff, 12);
			bufsum(tSelectCmd.buff);
		}
		break;
	case 1:								//余额读写
		if (0 == cmdCtrl.isSelectParam) //选择成功
		{
			cmdSort = 2;
			cmdCtrl.isWriteEPC = 1;
			msgStack.personMem.EPC.person.remain1 = msgStack.tmpMem.EPC.person.remain1;
			msgStack.personMem.EPC.person.remain2 = msgStack.tmpMem.EPC.person.remain2;
			bufcpy(tWriteEPC.msg.EPC.buff, msgStack.personMem.EPC.buff, 12); //补全内存写入数据
			bufsum(tWriteEPC.buff);
			
			DELAY_MS(100);
		}
		break;
	case 2:	
		if (0 == cmdCtrl.isWriteEPC)
		{
			DELAY_MS(100);
			cmdSort = 3;
			cmdCtrl.isSelectParam = 1;
			bufcpy(tSelectCmd.msg.EPC.buff, msgStack.mem[msgStack.sp - 1].EPC.buff, 12);
			bufsum(tSelectCmd.buff);
		}
		break;
	case 3: 
		if (0 == cmdCtrl.isSelectParam)
		{
			cmdCtrl.isWriteEPC = 1;
			msgStack.mem[msgStack.sp - 1].EPC.goods.productID = 0x00;
			bufcpy(tWriteEPC.msg.EPC.buff, msgStack.mem[msgStack.sp - 1].EPC.buff, 12); //补全内存写入数据
			bufsum(tWriteEPC.buff);
			if (msgStack.sp > 1) //检测栈区是否已空
				cmdSort = 2;
			else
			{	
				cmdSort=0;
				*step=4;
			}
			if(msgStack.sp>0)
				msgStack.sp--;
		}
		break;
	}
}

uint8 isLeave()
{
	static uint8 state=0,flag=0;
	static uint16 timer=0;
	
	if(0==flag)
	{
		flag=!flag;
		printf("结算完成,请取卡\n");
	}
	switch(state)
	{
	case 0:
		state = 1;
		timer = 0;
		cmdCtrl.isOnce = 1; 
		break;//发送单次轮询
	case 1:
		if (1 == msgStack.tFlag && 1==cmdCtrl.isOnce)//卡片未取走
		{
			msgStack.tFlag = 0;
			if (timer++ > 200) //1.0s一定时间内,未读到信息,判定已取走
			{
				flag=0;
				printf("卡已取离！\n");
				memset(msgStack.personMem.EPC.buff,0,12);
				DELAY_MS(5000);
				return 0;
			}
		}
		else if(0==cmdCtrl.isOnce)//重复检测
			state=0;
		msgStack.sp=0;
		break;//检测
	}
	return 4;
}
//bb  0  c  0 13  1  0  0  0 20 60  0 dd d9 ff ff  0  0 ff ff  3  3  0  0 58 7e 
//bb  0 49  0 15  0 45 54  0  1  0  2  0  6 dd d9 ff ff  0  0 ff ff  0  0  0  0 b2 7e 