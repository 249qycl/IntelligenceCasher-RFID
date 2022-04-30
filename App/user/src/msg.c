#include "common.h"
#include "include.h"

/***********************************************************************************************
*函数名	: answerAnalysis 
*功  能	: 信息帧信息解析 
*参  数	: None
*返回值	: None
*作  者	: zyl
*日  期	: 2019/12/31  
***********************************************************************************************/

enum
{
    ERROR = 0xFF,
    SELECT_OK = 0x0C,
    WRITE_OK = 0x49,
    QUERY_MSG = 0x22,
} recorder;
//指令发出时进行装填
CMD_Ctrl cmdCtrl = {.isOnce=0,
.isPollStart=0,
.isPollStop=0,
.isSelectParam=0,
.isSelectMode=0,
.isWriteEPC=0};

void answerAnalysis(uint8 *buf)
{
	static uint8 timer=0;
    switch (buf[2])
    {
    case QUERY_MSG: //截取EPC信息
        memcpy(rQueryMsg.buff, buf, 24);
        if (Ok == memFilter(rQueryMsg.msg.EPC.buff))
        {
            if (0xFFFF == rQueryMsg.msg.EPC.person.man )
                memcpy(msgStack.personMem.EPC.buff, rQueryMsg.msg.EPC.buff, 12);
            else
            {
                memcpy(msgStack.mem[msgStack.sp].EPC.buff, rQueryMsg.msg.EPC.buff, 12);
                msgStack.sp++;
            }

            if (msgStack.sp > 29)
                msgStack.sp = 29; //防止栈区溢出
        }
        cmdCtrl.isOnce = 0;
        cmdCtrl.isPollStart = 0;
        break;
    case SELECT_OK:
        cmdCtrl.isSelectParam = 0;
        break;
    case WRITE_OK:
		if (1 == cmdCtrl.isWriteEPC)
		{   cmdCtrl.isWriteEPC = 0;
			timer=0;
		}
        break;
	case ERROR:
		if (2 == cmdCtrl.isPollStart)
			cmdCtrl.isPollStart = 1;
		if(1 == cmdCtrl.isWriteEPC)
		{
			if(timer++>100)
			{	
				cmdCtrl.isSelectParam=1;
				timer=0;
			}
		}
		break;
    }
    memset(buf, 0, 40); //清空pBuff
}

void cmdSend()
{
    if (1 == cmdCtrl.isOnce)
	{    
		putBuff(UART3, tOnceCmd, 7);
	//cmdCtrl.isOnce=0;
	}
    else if (1 == cmdCtrl.isPollStart)
    {
        putBuff(UART3, tPoll_20, 10);
        cmdCtrl.isPollStart = 2;
    }
    else if (1 == cmdCtrl.isSelectParam)
	{    
		putBuff(UART3, tSelectCmd.buff, 26);
		//cmdCtrl.isSelectParam=0;
	}
    else if (1 == cmdCtrl.isWriteEPC)
	{
		putBuff(UART3, tWriteEPC.buff, 28);
	}
}

uint8 memFilter(uint8 *buf)
{
    for (int i = 0; i < msgStack.sp; i++)
    {
        if (Ok == bufcmp(buf, msgStack.mem[i].EPC.buff, 12))
            return Error;
    }
    return Ok;
}
