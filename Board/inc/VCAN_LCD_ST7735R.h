/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       VCAN_LCD_ST7735R.h
 * @brief      LCD ������
 * @author     ɽ��Ƽ�
 * @version    v6.0
 * @date       2017-11-04
 */

#ifndef _VCAN_LCD_ST7735R_H_
#define _VCAN_LCD_ST7735R_H_

#include "MK66_gpio.h"
#include "enter.h"

//�û�����
#define ST7735R_DIR_DEFAULT     0       //����Ĭ�Ϸ��� (0~3)


/********************* ST7735R�ڲ�ʵ�� ***********************/
//LCD �ĹܽŶ���
#define     LCD_ST7735R_WR      PTC9
#define     LCD_ST7735R_RD      PTC10
#define     LCD_ST7735R_CS      PTC11
#define     LCD_ST7735R_RS      PTC12
#define     LCD_ST7735R_RST     PTC13

//�˲�����Ҫ�޸ĳ�ʼ����Ĵ���
#define     LCD_ST7735R_P0              PTC_B0_OUT
#define     LCD_ST7735R_PIN             PTC_B0_IN
#define     LCD_ST7735R_PDDR_OUT()      (DDRC_B0 = 0xff)    //DDR[X]_B[N]_OUT   ,Xȡ A~E ,Nȡ0~3 ������  DDRD_B3_OUT  ��ʾ PTD ��Byte 3 ���� PTD24~31
#define     LCD_ST7735R_PDDR_IN()       (DDRC_B0 = 0)


#define ST7735R_DELAY()                         //do{asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");}while(0)
#define ST7735R_DELAY_MS(ms)    DELAY_MS(ms)


extern lcd_t   lcd_st7735r;





#endif  //_VCAN_LCD_ST7735R_H_
