/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       system_MK66DZ10.h
 * @brief      ϵͳ������غ���
 * @author     ɽ��Ƽ�
 * @version    v6.0
 * @date       2013-07-02
 */

#ifndef __SYSTEM_MK66_H__
#define __SYSTEM_MK66_H__

extern int core_clk_khz;
extern int core_clk_mhz;
extern int bus_clk_khz;


void start(void);           //kinetis ��������
void sysinit (void);        //ϵͳ��ʼ��������ϵͳƵ�ʣ���ʼ��printf�˿�
void trace_clk_init(void);  //trace ʱ����� ��ʼ��
void fb_clk_init(void);     //fb ʱ����� ��ʼ��

void common_startup(void);  //�����ж������� �� ��Ҫ�����ݵ� RAM��

#endif  //__SYSTEM_MK66_H__
