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
    STOP_OK = 0x28,
    SELECT_OK = 0x0C,
    WRITE_OK = 0x49,
    READ_MSG = 0x39,
    QUERY_MSG = 0x22,
    OTHER = 0x00,
} recorder;
//指令发出时进行装填
CMD_Ctrl cmdCtrl = {0};

void answerAnalysis(uint8 *pBuff)
{
    switch (pBuff[2])
    {
    case QUERY_MSG: //截取EPC信息
        memcpy(rQueryMsg.buff, pBuff, 24);
        if (Ok == memFilter(rQueryMsg.msg.EPC.buff))
        {
            memcpy(msgStack.mem[msgStack.SP++].EPC.buff, rQueryMsg.msg.EPC.buff, 12);
            if (msgStack.SP > 29)
                msgStack.SP = 29; //防止栈区溢出
        }
        cmdCtrl.isOnce = 0;
        cmdCtrl.isPollStart = 0;
        break;
    case READ_MSG:
        memReadSave();
        break;

    //针对指令发出类别进行处理
    case SELECT_OK:
        cmdCtrl.isSelectParam = 0;
        break;
    case WRITE_OK:
        if (1 == cmdCtrl.isWriteRFU)
            cmdCtrl.isWriteRFU = 0;
        else if (1 == cmdCtrl.isWriteEPC)
            cmdCtrl.isWriteEPC = 0;
        else if (1 == cmdCtrl.isWriteUSER)
            cmdCtrl.isWriteUSER = 0;
        break;
    case STOP_OK:
        cmdCtrl.isPollStop = 0;
        break;
    case ERROR:
        //按照recorder分类处理
        break;
    default:
        break;
    }
}

void cmdSend()
{
    if (1 == cmdCtrl.isOnce)
        putBuff(UART3, tOnceCmd, 7);
    else if (1 == cmdCtrl.isPollStart)
        putBuff(UART3, tPoll_100, 10);
    else if (1 == cmdCtrl.isPollStop)
        putBuff(UART3, tPollStop, 7);
    else if (1 == cmdCtrl.isSelectParam)
        putBuff(UART3, tSelectCmd.buff, 26);
    else if (1 == cmdCtrl.isReadRFU)
        putBuff(UART3, tReadRFU.buff, 16);

    else if (1 == cmdCtrl.isReadUSER)
        putBuff(UART3, tReadUSER.buff, 16);
    else if (1 == cmdCtrl.isWriteRFU)
        putBuff(UART3, tWriteRFU.buff, 16);
    else if (1 == cmdCtrl.isWriteEPC)
        putBuff(UART3, tWriteEPC.buff, 16);
    else if (1 == cmdCtrl.isWriteUSER)
        putBuff(UART3, tWriteUSER.buff, 16);
} //读取操作按循环来，三个都读一遍构成一轮

void memReadSave(uint8 *pBuff)
{
    //信息处理：查重储存
    if (1 == cmdCtrl.isReadRFU)
    { //存进当前EPC所处位置
        memcpy(rReadRFU.buff, pBuff, 26);
        memcpy(msgStack.mem[msgStack.nowPointer].RFU.buff, rReadRFU.msg.RFU.buff, 4);
        cmdCtrl.isReadRFU = 0;
    }
    else if (1 == cmdCtrl.isReadUSER) //作为数据
    {                                 //存进当前EPC所处位置
        memcpy(rReadUSER.buff, pBuff, 26);
        memcpy(msgStack.mem[msgStack.nowPointer].USER.buff, rReadUSER.msg.USER.buff, 12);
        cmdCtrl.isReadUSER = 0;
    }
}
//商品结算完成后，更改其身份信息
uint8 memFilter(uint8 *pBuff)
{
    for (int i = 0; i < msgStack.SP; i++)
    {
        if (Ok == bufcmp(pBuff, msgStack.mem[i].EPC.buff, 12))
            return Error;
    }
    return Ok;
}