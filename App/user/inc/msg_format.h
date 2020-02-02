#ifndef	__MSG_FORMAT_H__
#define __MSG_FORMAT_H__
#include  "rfid_type.h"
/*********************************
*		Ӳ���豸��ѯָ������֡
**********************************/
extern uint8 T_hardware_query[8];
/*********************************
*		Ӳ���豸��ѯ��Ӧ
**********************************/
extern uint8 R_hardware_answer[18];
/*********************************
*		���β�ѯָ������֡
**********************************/
extern uint8 T_single_query[7];

/*********************************
*		����֡����0x01 0xFF
**********************************/


/*********************************
*		��ѯָ�����Ϣ֡
**********************************/
extern R_answer_right_Type R_answer_right;
/*********************************
*		��ѯ100������֡
**********************************/
extern uint8 T_repeat_query_100[10];
/*********************************
*		�����ѯֹͣ����֡
**********************************/
extern uint8 T_repeat_query_stop[7];
/*********************************
*		�����ѯֹͣ��Ӧ֡
**********************************/
extern uint8 R_repeat_answer_stop[8];


/*********************************
*		��ǩѡ������֡
**********************************/
extern T_select_command_Typedef T_select_command;
/*********************************
*		ѡ��ɹ���Ӧ֡
**********************************/
extern uint8 R_select_command[8];


/*********************************
*		��RFU�洢������֡
**********************************/
extern T_read_RFU_Typedef T_read_RFU;
/*********************************
*		��RFU�洢����Ϣ֡
**********************************/
extern R_read_RFU_Typedef R_read_RFU;
/*********************************
*		��EPC�洢������֡
**********************************/
extern T_read_EPC_Typedef T_read_EPC;
/*********************************
*		��EPC�洢����Ϣ֡
**********************************/
extern R_read_EPC_Typedef R_read_EPC;
/*********************************
*		��TID�洢������֡
**********************************/
extern T_read_TID_Typedef T_read_TID;
/*********************************
*		��TID�洢����Ϣ֡
**********************************/
extern R_read_TID_Typedef R_read_TID;
/*********************************
*		��USER�洢������֡
**********************************/
extern T_read_USER_Typedef T_read_USER;
/*********************************
*		��USER�洢����Ϣ֡
**********************************/
extern R_read_USER_Typedef R_read_USER;
/*********************************
*		����ǩ�洢��������Ӧ֡
**********************************/
extern uint8 R_read_error[8];


/*********************************
*		дRFU�洢������֡
**********************************/
extern T_write_RFU_Typedef T_write_RFU;
/*********************************
*		дEPC�洢������֡
**********************************/
extern T_write_EPC_Typedef T_write_EPC;
/*********************************
*		дUSER�洢������֡
**********************************/
extern T_write_USER_Typedef T_write_USER;
/*********************************
*		д��ǩ�洢���ɹ�֪ͨ֡
**********************************/
extern R_write_right_Typedef R_write_right;
/*********************************
*		д��ǩ�洢��ʧ�ܴ���֡
**********************************/
extern uint8 R_write_error[8];
/*********************************
*		ȫ�����ݹ�������
**********************************/
extern MSG_stack_Typedef MSG_stack;
#endif