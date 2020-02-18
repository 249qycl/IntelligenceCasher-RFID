#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

typedef union {
	uint8 buff[24];
	struct
	{
		uint8 other[8];
		union {
			uint8 buff[12];
			uint8 user_means[12];
		} EPC;
		union {
			uint8 buff[2];
			uint16 data;
		} CRC; //�ݲ�ʹ��
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
		uint8 membank; //0x00:RFU	0x01:EPC	0x02:TID	0x03:USER��
		uint16 SA;	 //��ַƫ��2	2	0	0
		uint16 DL;	 //���ݳ���2	6	0CH	20H
		uint8 checkSum;
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
		} EPC; //��ǩѡ����
		union {
			uint8 buff[4];
			uint8 user_means[4];
		} RFU; //�������������
		uint8 checkSum;
		uint8 end;
	} msg;
} R_read_RFU_Typedef;

typedef union {
	uint8 buff[16];
	struct
	{
		uint8 buff[5];
		uint32 password;
		uint8 membank; //0x00:RFU	0x01:EPC	0x02:TID	0x03:USER��
		uint16 SA;	 //��ַƫ��2	2	0	0
		uint16 DL;	 //���ݳ���2	6	6H	8H
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
		} EPC1; //��ǩѡ����
		union {
			uint8 buff[12];
			uint8 user_means[12];
		} EPC2; //EPC���ݴ洢����
		uint8 checkSum;
		uint8 end;
	} msg;
} R_read_EPC_Typedef;

typedef union {
	uint8 buff[16];
	struct
	{
		uint8 buff[5];
		uint32 password;
		uint8 membank; //0x00:RFU	0x01:EPC	0x02:TID	0x03:USER��
		uint16 SA;	 //��ַƫ��2	2	0	0
		uint16 DL;	 //���ݳ���2	6	6H	8H
		uint8 checkSum;
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
		} EPC; //��ǩѡ����
		union {
			uint8 buff[12];
			uint8 user_means[12];
		} TID; //TID���ݴ洢����
		uint8 checkSum;
		uint8 end;
	} msg;
} R_read_TID_Typedef;

typedef union {
	uint8 buff[16];
	struct
	{
		uint8 buff[5];
		uint32 password;
		uint8 membank; //0x00:RFU	0x01:EPC	0x02:TID	0x03:USER��
		uint16 SA;	 //��ַƫ��2	2	0	0
		uint16 DL;	 //���ݳ���2	6	6H	6H
		uint8 checkSum;
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
		} EPC; //��ǩѡ����
		union {
			uint8 buff[12];
			uint8 user_means[12];
		} USER; //USER���ݴ洢����
		uint8 checkSum;
		uint8 end;
	} msg;
} R_read_USER_Typedef;

typedef union {
	uint8 buff[16];
	struct
	{
		uint8 buff[5];
		uint32 password;
		uint8 membank; //0x00:RFU	0x01:EPC	0x02:TID	0x03:USER��
		uint16 SA;	 //��ַƫ��2	2	0	0
		uint16 DL;	 //���ݳ���2	6	6H	6H
		struct
		{
			uint8 buff[4];
		} DATA; //����д��
		uint8 checkSum;
		uint8 end;
	} msg;
} T_write_RFU_Typedef;

typedef union {
	uint8 buff[16];
	struct
	{
		uint8 buff[5];
		uint32 password;
		uint8 membank; //0x00:RFU	0x01:EPC	0x02:TID	0x03:USER��
		uint16 SA;	 //��ַƫ��2	2	0	0
		uint16 DL;	 //���ݳ���2	6	6H	6H
		struct
		{
			uint8 buff[12];
		} EPC;
		uint8 checkSum;
		uint8 end;
	} msg;
} T_write_EPC_Typedef;

typedef union {
	uint8 buff[16];
	struct
	{
		uint8 buff[5];
		uint32 password;
		uint8 membank; //0x00:RFU	0x01:EPC	0x02:TID	0x03:USER��
		uint16 SA;	 //��ַƫ��2	2	0	0
		uint16 DL;	 //���ݳ���2	6	6H	6H
		struct
		{
			uint8 buff[12];
		} USER;
		uint8 checkSum;
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
		} EPC; //��ǩѡ����
		uint8 parameter;
		uint8 checkSum;
		uint8 end;
	} msg;
} R_write_right_Typedef;

typedef struct
{
	uint8 SP;		  //��ջջ��ָ�롾�����Ƚ�ջ,Ȼ��ָ���һ��
	uint8 nowPointer; //ָ����ָ���EPC����λ��
	enum
	{
		BEGIN = 0xBB, //֡��ʼ
		END = 0x7E,   //֡��β
	} R_MSG;
	enum
	{
		Error,
		Ok,
	} Return;
	struct
	{
		union {
			uint8 buff[4];
			uint32 password;
		} RFU; //2--2H=2
		union {
			uint8 buff[12];
			union {
				struct
				{
					float price; //4�ֽ�
					uint8 area;  //����
					uint8 kind1; //�ջ���������ʵ�
					uint8 kind2;
					uint8 grade;	  //Ʒ��
					uint8 row;		  //��
					uint8 column;	 //��
					uint16 productID; //ͬ����Ʒ��ID���֣��۳���ID����
				}goods;
				struct 
				{
					float remain;//8�ֽ�
					uint8 ID[8];
				}person;
			} means;
		} EPC; //2--6H=6
		union {
			uint8 buff[12];
			uint8 user_means[12];
		} TID; //0--6H=6
		union {
			uint8 buff[12];
			uint8 user_means[12];
		} USER;			  //0--6H=6
	} mem[30], personMem; //�ṹ��֮��ɻ��ഫֵ
} MSG_stack_Typedef;

#endif