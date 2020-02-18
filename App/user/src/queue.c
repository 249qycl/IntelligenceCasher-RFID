#include "common.h"
#include "include.h"

/***********************************************************************************************
*功  能	: 串口数据接收缓冲队列
*参  数	: None
*返回值	: None
*作  者	: zyl
*日  期	: 2019/12/31  
***********************************************************************************************/
Queue dataQueue;

void queueInit()
{
	dataQueue.front = 0;
	dataQueue.rear = 0;
	dataQueue.pop = queuePop;
	dataQueue.push = queuePush;
	dataQueue.isEmpty = queueIsEmpty;
}

uint8 queuePush(uint8 data)
{
	if ((dataQueue.rear + 1) % QUEUE_SIZE == dataQueue.front)
		return Error;
	dataQueue.array[dataQueue.rear] = data;
	dataQueue.rear = (dataQueue.rear + 1) % QUEUE_SIZE;
	return Ok;
}

uint8 queuePop()
{
	if(Ok==queueIsEmpty())
    	return Error;
    uint8 data = dataQueue.array[dataQueue.front];
    dataQueue.front = (dataQueue.front+1)%QUEUE_SIZE;
    	return data;
}

uint8 queueIsEmpty()
{
	return dataQueue.front == dataQueue.rear;
}

