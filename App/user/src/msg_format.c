#include "common.h"
#include "include.h"

uint8 tHardwareCmd[8]={0xBB,0x00,0x03,0x00,0x01,0x00,0x04,0x7E};
uint8 rHardwareInfo[18]={0xBB,0x01,0x03,0x00,0x0B,0x00,0x4D,0x31,0x30,0x30,0x20,0x56,0x31,0x2E,0x30,0x30,0x22,0x7E};

uint8 tOnceCmd[7]={0xBB,0x00,0x22,0x00,0x00,0x22,0x7E };//正常

R_answer_right_Type rQueryMsg;

uint8 tPoll_20[10]={0xBB,0x00,0x27,0x00,0x03,0x22,0x00,0x14,0x60,0x7E};//正常

T_select_command_Typedef tSelectCmd={.msg.buff={0xBB,0x00,0x0C,0x00,0x13,0x01,0x00,0x00,0x00,0x20,0x60,0x00},.msg.end=0x7E};

uint8 rSelectOk[8]={0xBB,0x01,0x0C,0x00,0x01,0x00,0x0E,0x7E};

T_read_EPC_Typedef tReadEPC={.msg.buff={0xBB,0x00,0x39,0x00,0x09},.msg.password=0x00455400,.msg.membank=0x01,.msg.SA=0x0002,.msg.DL=0x0006,.msg.end=0x7E};

R_read_EPC_Typedef rReadEPC={.msg.buff={0xBB,0x01,0x39,0x00,0x1B,0x0E,0x30,0x00 },.msg.end=0x7E};

//写入时需带密码0x00455400
T_write_EPC_Typedef tWriteEPC={.msg.buff={0xBB,0x00,0x49,0x00,0x15},.msg.password={0x00,0x45,0x54,0x00},.msg.membank=0x01,.msg.SA=0x0200,.msg.DL=0x0600,.msg.end=0x7E};

R_write_right_Typedef rWriteOk={.msg.buff={0xBB,0x01,0x49,0x00,0x10,0x0E,0x30,0x00 },.msg.parameter=0x00,.msg.end=0x7E};

MSG_stack_Typedef msgStack = {.sp = 0,.timer =0,.tFlag=0}; //用户信息栈

//3.5->0x80806938 8.65->0x63 2.15->0xaa0a6e0