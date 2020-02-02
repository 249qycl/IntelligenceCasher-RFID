/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       MK66_conf.c
 * @brief      ɽ��K66 ƽ̨���ù���ʵ���ļ�
 * @author     ɽ��Ƽ�
 * @version    v6.0
 * @date       2017-11-04
 */

#include    "common.h"
#include    "include.h"


#if (USE_LCD == LCD_ILI9341)
extern lcd_t   lcd_ili9341;
lcd_t *  glcd =  &lcd_ili9341;

#elif  (USE_LCD == LCD_ST7735S)
extern lcd_t   lcd_st7735s;
lcd_t *  glcd =  &lcd_st7735s;

#elif  (USE_LCD == LCD_ST7735R)
extern lcd_t   lcd_st7735r;
lcd_t *  glcd =  &lcd_st7735r;

#elif  (USE_LCD == LCD_ILI9325)
extern lcd_t   lcd_ili9325;
lcd_t *  glcd =  &lcd_ili9325;
#endif



void soft_delay_us(uint32_t us)
{
    //�������������ʱ����׼�ģ������Ǵ��
    volatile  uint32_t i=us,j;

    while(i--)
    {
        j=0x1000;
        while(j--);
    }

}



void soft_delay_ms(uint32_t ms)
{
    //�������������ʱ����׼�ģ������Ǵ��
    volatile  uint32_t i=ms;

    while(i--)
    {
        soft_delay_us(1000);
    }

}

/*!
 *  @brief      ����ʧ����ִ�еĺ���
 *  @param      file    �ļ�·����ַ
 *  @param      line    ����
 *  @since      v5.0
 *  Sample usage:       assert_failed(__FILE__, __LINE__);
 */
const char ASSERT_FAILED_STR[] = "Assertion failed in %s at line %d\n";

void assert_failed(char *file, int line)
{
    led_init(LED0);
    while (1)
    {

        DEBUG_PRINTF(ASSERT_FAILED_STR, file, line);      //ͨ��������ʾ����ʧ��

        //��ѭ���ȴ�����Ա���Ϊ�ζ���ʧ��
        led_turn(LED0);
        soft_delay_ms(1000);

    }
}

/*!
 *  @brief      �ض���printf ������
 *  @param      ch      ��Ҫ��ӡ���ֽ�
 *  @param      stream  ������
 *  @since      v5.0
 *  @note       �˺�����ɽ���FWD���printf������
 */
int enter_fputc(char ch)
{
    uart_putchar(VCAN_PORT, (char)ch);
    return(ch);
}


/*!
 *  @brief      Ĭ���жϷ�����
 *  @since      v5.0
 *  @note       �˺���д���ж������������Ҫ�û�ִ��
 */
void default_isr(void)
{


#ifdef  DEBUG_MODE
#define VECTORNUM    ((SCB_ICSR & SCB_ICSR_VECTACTIVE_MASK)>>SCB_ICSR_VECTACTIVE_SHIFT)
                            //��Ч�� (*(volatile uint8_t*)(0xE000ED04))
    uint8 vtr = VECTORNUM;
    char  str[100];

    get_isr_info(str);       //��ȡ�ж���Ϣ

    led_init(LED1);

    while(1)
    {
        led_turn(LED1);
        DEBUG_PRINTF("\nvector=%d\n", vtr);
        DEBUG_PRINTF(str);      //���ж���Ϣ���ͳ�ȥ

        soft_delay_ms(1000);
    }
#else
    return;
#endif
}
