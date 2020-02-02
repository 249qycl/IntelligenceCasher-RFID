#include "common.h"
#include "include.h"


MSG_stack_Typedef MSG_stack={.SP=0,.run_state=0,.RX_flag=0,.RX_finish=0,.RX_count=0,.RX_num=0,.query_times=0};//用户信息栈

//5ms定时器中断
void PIT_Hander(void)
{
	PIT_Flag_Clear(PIT0);
	if( RX_GENERAL==MSG_stack.RX_flag )
	{
		MSG_stack.RX_count++;
		if(MSG_stack.RX_count>1)
		{				
			RX_buff_reset();
			//读取字符串
		}
	}	
	if (1==MSG_stack.RX_finish)
	{
		answer_analysis();
		MSG_stack.RX_finish=0;
	}		
}
//strncpy(char *dst , char const *src , size_t len);
// int bcmp(const void *s1, const void *s2, int n);比较字符串s1和s2的前n个字节是否相等说明：如果s1=s2或n=0则返回零，否则返回非零值。bcmp不检查NULL
//uart_putbuff (UART3,"1234567", 3); //实际发送了3个字节'1','2','3'
//memcpy(void *dest, void *src, unsigned int count);
//void bzero(void *s, int n);置字节字符串s的前n个字节为零。
void UART3_RX_Handler(void)
{
	uint8 data;
	if(UART_S1_REG(UARTN[UART3]) & UART_S1_RDRF_MASK)   //接收数据寄存器满
    {
		data=UART_D_REG(UARTN[UART3]); //接受到8位的数据//用户需要处理接收数据
		if(RX_QUERY!=MSG_stack.RX_flag)
			RX_buff_run(data);
		else
			RX_query(data);//接收完后，轮数结束还原接收模式	
    }	
}
