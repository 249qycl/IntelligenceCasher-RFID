#include "common.h"
#include "include.h"

//5ms��ʱ���ж�
void PIT_Hander(void)
{
	PIT_Flag_Clear(PIT0);
	msgStack.tFlag=1;
}
//strncpy(char *dst , char const *src , size_t len);
// int bcmp(const void *s1, const void *s2, int n);�Ƚ��ַ���s1��s2��ǰn���ֽ��Ƿ����˵�������s1=s2��n=0�򷵻��㣬���򷵻ط���ֵ��bcmp�����NULL
//uart_putbuff (UART3,"1234567", 3); //ʵ�ʷ�����3���ֽ�'1','2','3'
//memcpy(void *dest, void *src, unsigned int count);
//void bzero(void *s, int n);���ֽ��ַ���s��ǰn���ֽ�Ϊ�㡣

void UART3_RX_Handler(void)
{
	uint8 data;
	if (UART_S1_REG(UARTN[UART3]) & UART_S1_RDRF_MASK) //�������ݼĴ�����
	{
		data = UART_D_REG(UARTN[UART3]); //���ܵ�8λ������//�û���Ҫ�����������
		//uart_putchar (UART4,data);
		//printf("%2x",data);
		dataQueue.push(data);
	}
}
