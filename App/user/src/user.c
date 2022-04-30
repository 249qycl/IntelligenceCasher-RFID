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
	uart_init(UART3, 115200);
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
		while (Error == getBuffer(pBuff));
		if (Ok == bufcmp(pBuff, rHardwareInfo, 4))
		{
			printf("RFID��ʼ���ɹ���\n"); //��ʾ�豸��ʼ���ɹ���Ϣ
			break;
		}
	}
	memset(pBuff, 0, 40);
}
/***********************************************************************************************
*������	: accountBalance 
*��  ��	: ��Ŀ���� 
*��  ��	: None
*����ֵ	: None
*��  ��	: zyl
*��  ��	: 20I19/12/31  
***********************************************************************************************/
void msgDebug()
{
	printf("��Ʒ����%d ��\n ",msgStack.sp);
	for (int i = 0; i < msgStack.sp; i++)
	{
		printf("��%d��:\n", i+1);
		for (int j = 0; j < 12; j++)
			printf("%2x ", msgStack.mem[i].EPC.buff[j]);
		printf("---\n");
	}
	printf("��ݿ���\n");
	for(int i=0;i<12;i++)
		printf("%2x ",msgStack.personMem.EPC.buff[i]);
	printf("\n");
}

void accountBalance()
{
	static uint8 step = 0;
	int sum1 = 0,sum2=0; //������
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
	case 1: //�ж��Ƿ�ɨ�����
		if(2==cmdCtrl.isPollStart)//������ʧ�ܣ��ط�
			cmdCtrl.isPollStart=1;
		if (1 == msgStack.tFlag&&0==cmdCtrl.isPollStart)
		{
			msgStack.tFlag = 0;
			if (msgStack.timer++ > 200) //1.0s
			{
				//�ж��Ƿ��������
				//msgDebug();
				printf("ɨ�����\n");
				if(0xFFFF==msgStack.personMem.EPC.person.man)//��������
					step=2;
				else
				{
					step=0;//debug =0
					printf("δ��⵽���\n");
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
			printf("����\n");
		}
		//step=3;//debug
		break;
	case 3:
		memWrite(&step);
		break;
	case 4:
		if (0 == cmdCtrl.isWriteEPC)
			step=isLeave();
			//����Ƿ�ȡ��
		break;
	}
	//�����������һ�֣������޴����жϣ�����Ϊ�������
} 

void memWrite(uint8 *step)
{
	static uint8 cmdSort = 0;//,flag=0;
	//��ȫ��ǩѡ������
	switch (cmdSort)
	{
	case 0: //װ�����ѡ��ָ��
		if (0 == cmdCtrl.isWriteEPC)//ȷ���޴�д������
		{
			cmdSort = 1;
			cmdCtrl.isSelectParam = 1;
			bufcpy(tSelectCmd.msg.EPC.buff, msgStack.personMem.EPC.buff, 12);
			bufsum(tSelectCmd.buff);
		}
		break;
	case 1:								//����д
		if (0 == cmdCtrl.isSelectParam) //ѡ��ɹ�
		{
			cmdSort = 2;
			cmdCtrl.isWriteEPC = 1;
			msgStack.personMem.EPC.person.remain1 = msgStack.tmpMem.EPC.person.remain1;
			msgStack.personMem.EPC.person.remain2 = msgStack.tmpMem.EPC.person.remain2;
			bufcpy(tWriteEPC.msg.EPC.buff, msgStack.personMem.EPC.buff, 12); //��ȫ�ڴ�д������
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
			bufcpy(tWriteEPC.msg.EPC.buff, msgStack.mem[msgStack.sp - 1].EPC.buff, 12); //��ȫ�ڴ�д������
			bufsum(tWriteEPC.buff);
			if (msgStack.sp > 1) //���ջ���Ƿ��ѿ�
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
		printf("�������,��ȡ��\n");
	}
	switch(state)
	{
	case 0:
		state = 1;
		timer = 0;
		cmdCtrl.isOnce = 1; 
		break;//���͵�����ѯ
	case 1:
		if (1 == msgStack.tFlag && 1==cmdCtrl.isOnce)//��Ƭδȡ��
		{
			msgStack.tFlag = 0;
			if (timer++ > 200) //1.0sһ��ʱ����,δ������Ϣ,�ж���ȡ��
			{
				flag=0;
				printf("����ȡ�룡\n");
				memset(msgStack.personMem.EPC.buff,0,12);
				DELAY_MS(5000);
				return 0;
			}
		}
		else if(0==cmdCtrl.isOnce)//�ظ����
			state=0;
		msgStack.sp=0;
		break;//���
	}
	return 4;
}
//bb  0  c  0 13  1  0  0  0 20 60  0 dd d9 ff ff  0  0 ff ff  3  3  0  0 58 7e 
//bb  0 49  0 15  0 45 54  0  1  0  2  0  6 dd d9 ff ff  0  0 ff ff  0  0  0  0 b2 7e 