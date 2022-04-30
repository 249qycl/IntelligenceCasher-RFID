#ifndef __MSG_H__
#define __MSG_H__

typedef struct {
   uint8 isOnce;
   uint8 isPollStart;
   uint8 isPollStop;
   uint8 isSelectParam;
   uint8 isSelectMode;

   uint8 isWriteEPC;
}CMD_Ctrl;
extern CMD_Ctrl cmdCtrl;


void answerAnalysis(uint8 *buf);
void cmdSend();
uint8 memFilter(uint8 *buf);

#endif