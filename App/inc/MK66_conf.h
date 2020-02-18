/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       MK66_conf.h
 * @brief      ɽ��K66 ƽ̨�����ļ�
 * @author     ɽ��Ƽ�
 * @version    v6.0
 * @date       2017-11-04
 */

#ifndef __MK66_CONF_H__
#define __MK66_CONF_H__



/*
 * ����ƽ̨[���ڹ���ѡ���ﶨ��]
 */
//#define  MK66F18


/*
 * ����LCD�ͺ�
 */
#define LCD_ILI9341     0       //Ұ��/����3.2���Һ��
#define LCD_ST7735S     1       //LCD_ST7735S �� LCD_ST7735R ���һ�����Ĵ����������в�ͬ
#define LCD_ST7735R     2       //
#define LCD_ILI9325     3       //ɽ��3.2���Һ��




#define USE_LCD         LCD_ILI9325             //ѡ��ʹ�õ� LCD


/*
 * ѡ���Ƿ����������Ϣ���������ע������ĺ궨��
 */
#define DEBUG_PRINT

/*
 * ���徧��ʱ�ӣ���λΪMHz
 */
#define EXTAL_IN_MHz            (16)


/*
 * ���� PLL ��Ƶ Ƶ�� (��ͬ��ƽ̨���в�ͬ�ĳ�Ƶ����)
 *
 * ����Գ�Ƶ���ò���Ϥ�����Կ���������:
 * K60 KL26 ��Ƶ������Ƶ�ʵĹ�ϵ - ���ܳ������� - ɽ����̳
 * http://www.vcan123.com/forum.php?mod=viewthread&tid=81&page=1&extra=#pid419
 */
#define CORE_CLK                PLL180      // �� PLL_e ��ѡ�� ���ṩ�� ���÷���
                                            // bus �� flex bus �� flash Ƶ�� ���� core ��������Ƶ����
#define MAX_BUS_CLK             100         // bus      (bus        >= core/16  )
#define MAX_FLEXBUS_CLK         25          // flex bus (flex bus   >= core/16  )
#define MAX_FLASH_CLK           28          // flash    (flash      >= core/16  )



/*
 * ���� printf���� �� ��������˿� �� ������Ϣ
 */
#define VCAN_PORT           UART4
#define VCAN_BAUD           115200

/*
 * ������ʱ����
 */
#if 0
#define DELAY()         dwt_delay_ms(500)
#define DELAY_MS(ms)    dwt_delay_ms(ms)
#define DELAY_US(us)    dwt_delay_us(us)
#elif   0
#define     DELAY()         lptmr_delay_ms(500)
#define     DELAY_MS(ms)    lptmr_delay_ms(ms)
#define     DELAY_US(us)    lptmr_delay_us(us)
#elif   0
#define DELAY()         pit_delay_ms(PIT3,500)
#define DELAY_MS(ms)    pit_delay_ms(PIT3,ms)
#define DELAY_US(us)    pit_delay_us(PIT3,us)
#elif   1
#define DELAY()         systick_delay_ms(500)
#define DELAY_MS(ms)    systick_delay_ms(ms)
#define DELAY_US(us)    systick_delay_us(us)
#else
extern void soft_delay_ms(uint32_t ms);
extern void soft_delay_us(uint32_t us);
#define DELAY()         soft_delay_ms(500)
#define DELAY_MS(ms)    soft_delay_ms(ms)
#define DELAY_US(us)    soft_delay_us(us)

#endif


/*
 * ���ö��Ժ���ʵ�ֺ���
 */
void assert_failed(char *, int);

#if defined( DEBUG_MODE )
#define ASSERT(expr) \
    if (!(expr)) \
        assert_failed(__FILE__, __LINE__)
#else
#define ASSERT(expr)
#endif

/*
 * ���õ����������
 */
#if( defined(DEBUG_MODE) && defined(DEBUG_PRINT))
#define DEBUG_PRINTF(FORMAT,...)        do{printf(FORMAT,##__VA_ARGS__);}while(0)	/*�����ӡ������Ϣʱ���뽫������ע�͵�*/
#else
#define DEBUG_PRINTF(FORMAT,...)
#endif


#endif /* __MK66_CONF_H__  */
