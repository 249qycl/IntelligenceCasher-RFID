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
				uint16 remain1; //8�ֽ�
				uint16 remain2; //8�ֽ�
				uint16 man; //��λΪ��ʱ0xFFFF
			} person;
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
	uint8 buff[28];
	struct
	{
		uint8 buff[5];
		uint8 password[4];
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
	uint8 sp;	//��ջջ��ָ�롾�����Ƚ�ջ,Ȼ��ָ���һ��
	uint8 tFlag;
	uint16 timer; //ָ����ָ���EPC����λ��
	
	struct
	{
		union {
			uint8 buff[12];
			struct
			{
				uint8 area;  //����
				uint8 kind1; //�ջ���������ʵ�
				uint8 kind2;
				uint8 grade;	  //Ʒ��
				uint8 number;	//�� ������0
				uint8 floor;	 //�� ������0
				uint16 price1; //2�ֽ�
				uint16 price2; //2�ֽ�
				uint16 productID; //ͬ����Ʒ��ID���֣��۳���ID����
			} goods;
			struct
			{
				uint8 ID[6];
				uint16 remain1; //8�ֽ�
				uint16 remain2; //8�ֽ�
				uint16 man; //��λΪ��ʱ0xFFFF
			} person;
		} EPC;					  //2--6H=6
	} mem[30], personMem, tmpMem; //�ṹ��֮��ɻ��ഫֵ
} MSG_stack_Typedef;

extern enum
{
    Error,
    Ok,
    BEGIN = 0xBB, //֡��ʼ
    END = 0x7E,   //֡��β
} Ret;
#endif