#ifndef __MSG_H__
#define __MSG_H__

typedef struct {
   uint8 isOnce;
   uint8 isPollStart;
   uint8 isPollStop;
   uint8 isSelectParam;
   uint8 isSelectMode;

   uint8 isReadRFU;
   uint8 isReadEPC;
   uint8 isReadTID;
   uint8 isReadUSER;

   uint8 isWriteRFU;
   uint8 isWriteEPC;
   uint8 isWriteUSER;
}CMD_Ctrl;
extern CMD_Ctrl cmdCtrl;


void answerAnalysis();
void memReadSave();
void cmdSend();
uint8 memFilter(uint8 *pBuff);

#endif