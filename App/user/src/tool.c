#include "common.h"
#include "include.h"


#define Header	0xBB
#define End		0x7E
uint8 check_sum(uint8 *buff)
{
	uint16 sum=0;
	uint8 i=1;
	while(buff[i+1]!=End)
	{
		sum+=buff[i];
		i++;
	}
	return sum%256;
}

uint32 parameter_length(uint8 *buff)
{
	uint32 i=4;
	while(buff[i+2]!=End)
	{
		i++;
	}
	return (i-4);	
}