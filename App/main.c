#include "common.h"
#include "include.h"



uint8 isPut=0;                                         
uint8 array1;
uint8 array2;
uint8 array3;
uint8 array4;
uint8 array5;
void main()
{
	systemInit(); 
	queueInit();
	rfidReaderInit();
    while(1)
    {  
		//printf("hello world");
		DELAY_MS(20);
//		printf("%2x",dataQueue.array[0]);
//		printf("%2x",dataQueue.array[1]);
//		printf("%2x",dataQueue.array[2]);
//		printf("%2x",dataQueue.array[3]);
//		printf("   ");
    }
}
