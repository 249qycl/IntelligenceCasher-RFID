#include "common.h"
#include "include.h"


MSG_stack_Typedef MSG_stack={.SP=0,.run_state=0,.RX_flag=0,.RX_finish=0,.RX_count=0,.RX_num=0,.query_times=0};//�û���Ϣջ

//5ms��ʱ���ж�
void PIT_Hander(void)
{
	PIT_Flag_Clear(PIT0);
	if( RX_GENERAL==MSG_stack.RX_flag )
	{
		MSG_stack.RX_count++;
		if(MSG_stack.RX_count>1)
		{				
			RX_buff_reset();
			//��ȡ�ַ���
		}
	}	
	if (1==MSG_stack.RX_finish)
	{
		answer_analysis();
		MSG_stack.RX_finish=0;
	}		
}
//strncpy(char *dst , char const *src , size_t len);
// int bcmp(const void *s1, const void *s2, int n);�Ƚ��ַ���s1��s2��ǰn���ֽ��Ƿ����˵�������s1=s2��n=0�򷵻��㣬���򷵻ط���ֵ��bcmp�����NULL
//uart_putbuff (UART3,"1234567", 3); //ʵ�ʷ�����3���ֽ�'1','2','3'
//memcpy(void *dest, void *src, unsigned int count);
//void bzero(void *s, int n);���ֽ��ַ���s��ǰn���ֽ�Ϊ�㡣
void UART3_RX_Handler(void)
{
	uint8 data;
	if(UART_S1_REG(UARTN[UART3]) & UART_S1_RDRF_MASK)   //�������ݼĴ�����
    {
		data=UART_D_REG(UARTN[UART3]); //���ܵ�8λ������//�û���Ҫ�����������
		if(RX_QUERY!=MSG_stack.RX_flag)
			RX_buff_run(data);
		else
			RX_query(data);//�����������������ԭ����ģʽ	
    }	
}
