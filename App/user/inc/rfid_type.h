#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

typedef union {
	uint8 buff[24];
	struct
	{
		uint8 other[8];
		union {
			uint8 buff[12];
			struct
			{
				uint8 ID[6];
				uint16 remain1; //8字节
				uint16 remain2; //8字节
				uint16 man; //此位为人时0xFFFF
			} person;
		} EPC;
		union {
			uint8 buff[2];
			uint16 data;
		} CRC; //暂不使用
		uint8 checkSum;
		uint8 end;
	} msg;
} R_answer_right_Type;

typedef union {
	uint8 buff[26];
	struct
	{
		uint8 buff[12];
		union {
			uint8 buff[12];
			uint8 user_means[12];
		} EPC;
		uint8 checkSum;
		uint8 end;
	} msg;
} T_select_command_Typedef;

typedef union {
	uint8 buff[16];
	struct
	{
		uint8 buff[5];
		uint32 password;
		uint8 membank; //0x00:RFU	0x01:EPC	0x02:TID	0x03:USER区
		uint16 SA;	 //地址偏移2	2	0	0
		uint16 DL;	 //数据长度2	6	6H	8H
		uint8 checkSum;
		uint8 end;
	} msg;
} T_read_EPC_Typedef;

typedef union {
	uint8 buff[26];
	struct
	{
		uint8 buff[8];
		union {
			uint8 buff[12];
			uint8 user_means[12];
		} EPC1; //标签选择码
		union {
			uint8 buff[12];
			uint8 user_means[12];
		} EPC2; //EPC数据存储区域
		uint8 checkSum;
		uint8 end;
	} msg;
} R_read_EPC_Typedef;

typedef union {
	uint8 buff[28];
	struct
	{
		uint8 buff[5];
		uint8 password[4];
		uint8 membank; //0x00:RFU	0x01:EPC	0x02:TID	0x03:USER区
		uint16 SA;	 //地址偏移2	2	0	0
		uint16 DL;	 //数据长度2	6	6H	6H
		struct
		{
			uint8 buff[12];
		} EPC;
		uint8 checkSum;
		uint8 end;
	} msg;
} T_write_EPC_Typedef;

typedef union {
	uint8 buff[23];
	struct
	{
		uint8 buff[8];
		union {
			uint8 buff[12];
			uint8 user_means[12];
		} EPC; //标签选择码
		uint8 parameter;
		uint8 checkSum;
		uint8 end;
	} msg;
} R_write_right_Typedef;

typedef struct
{
	uint8 sp;	//堆栈栈顶指针【数据先进栈,然后指针加一】
	uint8 tFlag;
	uint16 timer; //指向发送指令的EPC所在位置
	
	struct
	{
		union {
			uint8 buff[12];
			struct
			{
				uint8 area;  //产地
				uint8 kind1; //日化、生活、生鲜等
				uint8 kind2;
				uint8 grade;	  //品级
				uint8 number;	//号 均大于0
				uint8 floor;	 //层 均大于0
				uint16 price1; //2字节
				uint16 price2; //2字节
				uint16 productID; //同类商品按ID区分，售出后ID清零
			} goods;
			struct
			{
				uint8 ID[6];
				uint16 remain1; //8字节
				uint16 remain2; //8字节
				uint16 man; //此位为人时0xFFFF
			} person;
		} EPC;					  //2--6H=6
	} mem[30], personMem, tmpMem; //结构体之间可互相传值
} MSG_stack_Typedef;

extern enum
{
    Error,
    Ok,
    BEGIN = 0xBB, //帧起始
    END = 0x7E,   //帧结尾
} Ret;
#endif