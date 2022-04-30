#ifndef __TOOL_H__
#define __TOOL_H__

#define QUEUE_SIZE 1000
typedef struct queue
{
	uint8 array[QUEUE_SIZE];
	uint16 front;
	uint16 rear;
	uint8 (*pop)();
	uint8 (*push)(uint8);
	uint8 (*isEmpty)();
}Queue;

extern Queue dataQueue;

void queueInit();

uint8 queueIsEmpty();
uint8 queuePop();
uint8 queuePush(uint8 data);

#endif