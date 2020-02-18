#include "common.h"
#include "include.h"

uint8 pBuff[40];
/***********************************************************************************************
*函数名	: putBuff 
*功  能	: 向rfid发送一帧数据 
*参  数	: uratn：串口号 buff：数据容器 len：数据长度
*返回值	: None
*作  者	: zyl
*日  期	: 2020/2/17  
***********************************************************************************************/
void putBuff(UARTn_e uratn, uint8 *buff, uint32 len)
{
    while (len--)
    {
        //等待发送缓冲区空
        while (!(UART_S1_REG(UARTN[uratn]) & UART_S1_TDRE_MASK))
        {
        }
        //发送数据
        UART_D_REG(UARTN[uratn]) = (uint8)*buff;
        buff++;
    }
}
/***********************************************************************************************
*函数名	: getBuffer 
*功  能	: 从队列中读取一组数据 
*参  数	: p：容器指针
*返回值	: Ok：成功 Error：失败
*作  者	: zyl
*日  期	: 2020/2/17  
***********************************************************************************************/
uint8 getBuffer(uint8 *p)
{
    static uint8 isReceive = 0, count = 0;
    uint8 data = dataQueue.pop();
    switch (isReceive)
    {
    case 0:
        if (data == BEGIN)
        {
            count = 0;
            isReceive = 1;
            p[count++] = data;
        }
        break;
    case 1:
        p[count++] = data;
        if (data == END)
        {
            isReceive = 0;
            if (Error == bufcheck(p))
                return Error;
            return Ok;
        }
        break;
    default:
        return Error;
    }
    return Error;
}
/***********************************************************************************************
*函数名	: bufcmp 
*功  能	: 数据组比较 
*参  数	: buf1：组一  buf2：组二 len：比较的长度
*返回值	: Ok：相等 Error：不等
*作  者	: zyl
*日  期	: 2020/2/17  
***********************************************************************************************/
uint8 bufcmp(uint8 *buf1, uint8 *buf2, uint8 len)
{
    for (int i = 0; i < len; i++)
    {
        if (buf1[i] != buf2[i])
            return Error;
    }
    return Ok;
}
/***********************************************************************************************
*函数名	: bufcpy 
*功  能	: 把目标数据复制给源数据 
*参  数	: buf1：源数据  buf2：目的数据 len：数据长度
*返回值	: Ok：成功 Error：失败
*作  者	: zyl
*日  期	: 2020/2/17  
***********************************************************************************************/
uint8 bufcpy(uint8 *buf1, uint8 *buf2, uint8 len)
{
    for (int i = 0; i < len; i++)
        buf1[i] = buf2[i];

    return Ok;
}
/***********************************************************************************************
*函数名	: bufCheck 
*功  能	: 数据组检查 
*参  数	: pbuf：数据组
*返回值	: Ok：成功 Error：失败
*作  者	: zyl
*日  期	: 2020/2/17  
***********************************************************************************************/
uint8 bufcheck(uint8 *pbuf)
{
    uint16 sum = 0, i = 1;
    while (pbuf[i + 1] != END)
    {
        sum += pbuf[i++];
    }
    if (pbuf[i] == (sum % 256))
        return Ok;
    else
        return Error;
}

/***********************************************************************************************
*函数名	: bufsum 
*功  能	: 数据组求校验和 
*参  数	: pbuf：数据组
*返回值	: Ok：成功 
*作  者	: zyl
*日  期	: 2020/2/17  
***********************************************************************************************/
uint8 bufsum(uint8 *pbuf)
{
    uint16 sum = 0, i = 1;
    while (pbuf[i + 1] != END)
    {
        sum += pbuf[i++];
    }
    pbuf[i] = (sum % 256);
    return Ok;
}