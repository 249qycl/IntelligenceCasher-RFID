#ifndef __BUFFER_H__
#define __BUFFER_H__

extern uint8 pBuff[40];

void putBuff (UARTn_e uratn, uint8 *buff, uint32 len);

uint8 getBuffer(uint8 *p);
uint8 bufcmp(uint8 *buf1,uint8 *buf2,uint8 len);
uint8 bufcpy(uint8 *buf1, uint8 *buf2, uint8 len);
uint8 bufcheck(uint8 *buf);
uint8 bufsum(uint8 *buf);
#endif