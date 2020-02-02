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
				uint8 user_means[12];
			} msg;
		} EPC;
		union {
			uint8 buff[2];
			uint16 data;
		} CRC;
		uint8 check_sum;
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
		uint8 check_sum;
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
		uint16 DL;	 //数据长度2	6	0CH	20H
		uint8 check_sum;
		uint8 end;
	} msg;
} T_read_RFU_Typedef;

typedef union {
	uint8 buff[26];
	struct
	{
		uint8 buff[8];
		union {
			uint8 buff[12];
			uint8 user_means[12];
		} EPC; //标签选择码
		union {
			uint8 buff[4];
			uint8 user_means[4];
		} DATA; //保存密码的区域
		uint8 check_sum;
		uint8 end;
	} msg;
} R_read_RFU_Typedef;

typedef union {
	uint8 buff[16];
	struct
	{
		uint8 buff[5];
		uint32 password;
		uint8 membank; //0x00:RFU	0x01:EPC	0x02:TID	0x03:USER区
		uint16 SA;	 //地址偏移2	2	0	0
		uint16 DL;	 //数据长度2	6	6H	8H
		uint8 check_sum;
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
		uint8 check_sum;
		uint8 end;
	} msg;
} R_read_EPC_Typedef;

typedef union {
	uint8 buff[16];
	struct
	{
		uint8 buff[5];
		uint32 password;
		uint8 membank; //0x00:RFU	0x01:EPC	0x02:TID	0x03:USER区
		uint16 SA;	 //地址偏移2	2	0	0
		uint16 DL;	 //数据长度2	6	6H	8H
		uint8 check_sum;
		uint8 end;
	} msg;
} T_read_TID_Typedef;

typedef union {
	uint8 buff[26];
	struct
	{
		uint8 buff[8];
		union {
			uint8 buff[12];
			uint8 user_means[12];
		} EPC; //标签选择码
		union {
			uint8 buff[12];
			uint8 user_means[12];
		} TID; //TID数据存储区域
		uint8 check_sum;
		uint8 end;
	} msg;
} R_read_TID_Typedef;

typedef union {
	uint8 buff[16];
	struct
	{
		uint8 buff[5];
		uint32 password;
		uint8 membank; //0x00:RFU	0x01:EPC	0x02:TID	0x03:USER区
		uint16 SA;	 //地址偏移2	2	0	0
		uint16 DL;	 //数据长度2	6	6H	6H
		uint8 check_sum;
		uint8 end;
	} msg;
} T_read_USER_Typedef;

typedef union {
	uint8 buff[26];
	struct
	{
		uint8 buff[8];
		union {
			uint8 buff[12];
			uint8 user_means[12];
		} EPC; //标签选择码
		union {
			uint8 buff[12];
			uint8 user_means[12];
		} USER; //USER数据存储区域
		uint8 check_sum;
		uint8 end;
	} msg;
} R_read_USER_Typedef;

typedef union {
	uint8 buff[16];
	struct
	{
		uint8 buff[5];
		uint32 password;
		uint8 membank; //0x00:RFU	0x01:EPC	0x02:TID	0x03:USER区
		uint16 SA;	 //地址偏移2	2	0	0
		uint16 DL;	 //数据长度2	6	6H	6H
		struct
		{
			uint8 buff[4];
		} DATA; //密码写入
		uint8 check_sum;
		uint8 end;
	} msg;
} T_write_RFU_Typedef;

typedef union {
	uint8 buff[16];
	struct
	{
		uint8 buff[5];
		uint32 password;
		uint8 membank; //0x00:RFU	0x01:EPC	0x02:TID	0x03:USER区
		uint16 SA;	 //地址偏移2	2	0	0
		uint16 DL;	 //数据长度2	6	6H	6H
		struct
		{
			uint8 buff[12];
		} EPC;
		uint8 check_sum;
		uint8 end;
	} msg;
} T_write_EPC_Typedef;

typedef union {
	uint8 buff[16];
	struct
	{
		uint8 buff[5];
		uint32 password;
		uint8 membank; //0x00:RFU	0x01:EPC	0x02:TID	0x03:USER区
		uint16 SA;	 //地址偏移2	2	0	0
		uint16 DL;	 //数据长度2	6	6H	6H
		struct
		{
			uint8 buff[12];
		} USER;
		uint8 check_sum;
		uint8 end;
	} msg;
} T_write_USER_Typedef;

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
		uint8 check_sum;
		uint8 end;
	} msg;
} R_write_right_Typedef;
//通过切换接收容器，实现对多次查询数组的接收
typedef struct
{
	uint8 RX_flag;	 //接收状态指示
	uint8 RX_finish;   //接收结束标志
	uint8 RX_count;	//接收时间间隔判断
	uint8 RX_buff[30]; //字符接收缓冲区
	uint8 RX_num;	  //接收的字符串长度统计
	uint8 RX_times;
	uint8 query_times; //轮询次数
	uint8 SP;		   //堆栈栈顶指针【数据先进栈,然后指针加一】
	uint8 run_state;   //RFID设备状态指示
	enum
	{
		ERROR = 0xFF,
		STOP_SUCCESS = 0x28,
		SELECT_SUCCESS = 0x0C,
		MEMORY_READ = 0x39,
		MEMORY_WRITE = 0x49,
		RX_GENERAL = 0x01,
		RX_NONE = 0x00,
		RX_QUERY = 0x02,
		BEGIN = 0xBB, //帧起始
		END = 0x7E,   //帧结尾
	}R_MSG;

	union {
		uint8 buff[4];
		uint32 password;
	} RFU[30]; //2--2H=2

	union {
		uint8 buff[12];
		uint8 user_means[12];
	} EPC[30]; //2--6H=6

	union {
		uint8 buff[12];
		uint8 user_means[12];
	} TID[30]; //0--6H=6

	union {
		uint8 buff[12];
		uint8 user_means[12];
	} USER[30]; //0--6H=6

} MSG_stack_Typedef;

#endif