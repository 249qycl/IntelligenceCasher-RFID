#include "common.h"
#include "include.h"


void main()
{
	queueInit();
	systemInit();
	rfidReaderInit();
	while (1)
	{
		accountBalance();
		cmdSend();
		if (Ok == getBuffer(pBuff)) 
		{
			answerAnalysis(pBuff);
			//printf("  SP1=%d ",msgStack.sp);
			msgStack.timer = 0;
		}
		DELAY_MS(5);
	}
}

