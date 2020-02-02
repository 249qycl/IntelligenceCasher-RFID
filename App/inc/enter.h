#ifndef _ENTER_H_
#define _ENTER_H_
#include <stdint.h>

/*
    FWD �ļ�Ϊɽ��UD����İ�ר�õĹ̼��ļ����ṩ�����ֿ�ͺ������ܣ��ӿ쿪���ٶȺ͵����ٶȡ�
    FWD�ǿ�ִ�е��ļ���ֱ����¼��ָ����λ�ã������� APP�е�����ص� API ��������UD�棬����ʹ��FWD�̼���

    ��¼������

        ���usb�ߣ����� ��������(Ĭ���� PTD7�������İ��ϵĶ�������)��Ȼ��λ�����ɽ���UDģʽ��

        ���Ի�ʶ�𵽲���UD�����̣���FWD�ļ����Ƶ�U�̵ĸ�Ŀ¼���ɡ�


    ����ʹ���з�����bug���뷢�ʼ��������䣺minimcu@foxmail.com�����ǻᾡ����¡�

*/


//�û���API �����ӿڣ��ɿ�����Ľṹ���ע�ͣ���ע������ԭ��
//һ�㿴ע����ĺ���ԭ�ͼ���ʹ�õġ�
//APP��Ҫ��ʼ��ʱִ�� ASSERT(enter_init());�ж��Ƿ��Ѿ���¼�˹̼�

#define BOOT_VER    102      // �̼��汾�� �������޸ģ��������ϲ�ʶ��
#define FWD_VER     602      // �̼��汾�� �������޸ģ��������ϲ�ʶ��

#define USE_FOUNT_SIZE      16 //12 �� 16������ �������޸ģ��������ϲ�ʶ��


#define FOUNT12_ADDR        //����12������ĺ����ֿ��ַ ����� USE_FOUNT_SIZE Ϊ12������Ҫд�����ռ��ɣ�
#define FOUNT16_ADDR        //����16������ĺ����ֿ��ַ ����� USE_FOUNT_SIZE Ϊ16������Ҫд�����ռ��ɡ������ģ�����Ҫд���������� 16�ŵ����庯����


//printf / tpm_pwm_init / tpm_pwm_freq /tpm_input_init /  ftm_quad_init   LCD 6X12    ���⴦��



typedef struct
{
    uint16_t    flag;                   //���
    uint16_t    ver;                    //�汾

    //�ֿ�
    uint8_t *   ascii12;                //Ӣ���ֿ⣬char *  ascii_6x12 ;
    uint8_t *   ascii16;                //Ӣ���ֿ⣬char *  ascii_8x16 ;


    //�ַ��� ���� ת��
    void *      sprintf;                //int       sprintf         (char *buf, const char *fmt, ...) ;          //�ַ�����ʽ����������
    void *      printf;                 //void      printf          (fp,fmt, ...);                               //�ַ�����ʽ�������ָ���˿� fp ������Ϊ���ڣ�
    void *      atoi;                   //int       atoi            (char *str);                                //�ַ���ת������
    void *      itoa;                   //char *    itoa            (int n, char * chBuffer);                   //����ת��Ϊ�ַ���
    void *      ftoa;                   //char *    ftoa            (double dValue, char * chBuffer);           //����ת��Ϊ�ַ���



    //����С����
    void *      memcpy;                 //void *    memcpy  ( uint8_t *dst, uint8_t *src, uint32_t count);      //�ڴ渴��
    void *      memset;                 //void *    memset  (void *src, int c, int count);                      //�ڴ�������ֵ
    void *      strlen;                 //int       strlen(const char * str);                                   //���ַ����ĳ���
    void *      img_extract;            //void      img_extract(void *dst, void *src, uint32_t srclen);         //����ͷ��ѹ

    void *      get_isr_info;           //int       get_isr_info    (char * str);                               //��ȡ�жϺ�����Ӧ�ľ�������


    //MCG ��Ƶ����
    void *      pll_init;               //uint16_t    pll_init        (PLL_e pll,uint16_t max_bus_mhz,uint16_t max_flexbus_mhz,uint16_t max_flash_mhz);         //��Ƶ����

    //flash API
    void *      flash_init;             //void      flash_init          ();                                     //��ʼ��Flash
    void *      flash_erase_sector;     //uint8_t   flash_erase_sector  (uint16_t sectorNum);                     //����ָ��flash����
    void *      flash_write;            //uint8_t   flash_write         (uint16_t sectorNum, uint16_t offset, FLASH_WRITE_TYPE data);       //д��flash����
    void *      flash_write_buf;        //uint8_t   flash_write_buf     (uint16_t sectorNum, uint16_t offset, uint16_t cnt, uint8 buf[]);     //�ӻ�����д��flash����
    //����һ��flash API�ӿڣ�                        flash_read          (sectorNum,offset,type)                  //��ȡָ����ַ������


    //flash �洢����
    void *      flash_data_init;        //void      flash_data_init     (flash_data_t *d);                      //�Խṹ�����ݽ���Ԥ������flash�����ݻ�û��ʼ����������flash
    void *      flash_data_reset;       //void      flash_data_reset    (flash_data_t *d);                      //����flash�����ǶԴ洢���ݽ������
    void *      flash_data_load;        //uint8_t   flash_data_load     (flash_data_t *d);                      //�� flash ��������
    void *      flash_data_save;        //uint8_t   flash_data_save     (flash_data_t *d);                      //�������ݵ�flash


    //dwt ��ʱ����
    void *      dwt_delay_us;           //void      dwt_delay_us        (uint32_t core_clk,uint32_t us);          //dwt��ʱ������������ DWT_DELAY_US(us) ������
    void *      dwt_delay_ms;           //void      dwt_delay_ms        (uint32_t core_clk,uint32_t ms);          //dwt��ʱ������������ DWT_DELAY_MS(ms) ������

    //SYSTICK ��ʱ����
    void *      systick_delay;          //void      systick_delay       (uint32_t time);;                         //��ʱ time ��core���ڣ�24λ����
    void *      systick_delay_ms;       //void      systick_delay_ms    (uint32_t ms,uint32_t core_khz);          //��ʱ time ���ס����ջ��Ժ궨�� SYSTICK_DELAY_MS(ms) �滻

    //SYSTICK ��ʱ����
    void *      systick_timing;         //void      systick_timing      (uint32_t time);                          //��ʱ�жϳ�ʼ�������� time��core���ڣ�24bit




    //PIT. ��ʱ����
    void *      pit_init;               //void      pit_init            (PITn_e, uint32_t cnt);                   //��ʼ��PITn�������ö�ʱʱ��(��λΪbusʱ������)

    //PIT. ��ʱ����
    void *      pit_delay;               //void     pit_delay           (PITn_e, uint32_t cnt);                   //PIT��ʱ������Ҫ��ʼ���ģ�

    //PIT. ��ʱ����
    void *      pit_time_start;         //void      pit_time_start      (PITn_e);                               //PIT��ʼ��ʱ
    void *      pit_time_get;           //uint32_t  pit_time_get        (PITn_e);                               //��ȡ PITn��ʱʱ��(��ʱʱ��ر� ��ʱ��)����λΪ busʱ�ӣ�(��ֵΪ 0xFFFFFFFF�����ʾ���)
    void *      pit_close;              //void      pit_close           (PITn_e);                               //�ر� PIT ��ʱ


    //LPT  ��ʱ����
    void *      lptmr_delay_ms;         //void      lptmr_delay_ms       (uint16_t ms);                           //��ʱ(ms)
    void *      lptmr_delay_us;         //void      lptmr_delay_us       (uint16_t us);                           //��ʱ(us)

    //LPT  ��ʱ�жϺ���
    void *      lptmr_timing_ms;        //void      lptmr_timing_ms      (uint16_t ms);                           //��ʱ(ms)
    void *      lptmr_timing_us;        //void      lptmr_timing_us      (uint16_t us);                           //��ʱ(us)

    //LPT  ��ʱ����
    void *      lptmr_time_start_ms;    //void      lptmr_time_start_ms  (void);                                //��ʼ��ʱ(ms)
    void *      lptmr_time_get_ms;      //uint32_t  lptmr_time_get_ms    (void);                                //��ȡ��ʱʱ��
    void *      lptmr_time_start_us;    //void      lptmr_time_start_us  (void);                                //��ʼ��ʱ(ns)
    void *      lptmr_time_get_us;      //uint32_t  lptmr_time_get_us    (void);                                //��ȡ��ʱʱ��
    void *      lptmr_time_close;       //void      lptmr_time_close     ();                                    //�رռ�ʱ��

    //LPT  �����������
    void *      lptmr_pulse_init;       //void      lptmr_pulse_init     (LPT0_ALTn, uint16_t count, LPT_CFG);   //�����������ʼ������
    void *      lptmr_pulse_get;        //uint16_t  lptmr_pulse_get      (void);                               //��ȡ����ֵ
    void *      lptmr_pulse_clean;      //void      lptmr_pulse_clean    (void);                               //��ռ���ֵ


    //TPM  PWM���
    void *      tpm_pwm_init;           //int8_t    tpm_pwm_init        (TPMn_e, TPM_CHn_e, uint32_t freq, float duty,PTXn_e pin,uint32_t core_khz);    //��ʼ��TPM��PWM���ܲ�����Ƶ�ʡ�ռ�ձȡ�����ͨ�����ռ�ձȡ�ͬһ��TPM����ͨ����PWMƵ����һ����
    void *      tpm_pwm_duty;           //void      tpm_pwm_duty        (TPMn_e, TPM_CHn_e,                float duty);                                 //����ͨ��ռ�ձ�,ռ�ձ�Ϊ duty%
    void *      tpm_pwm_freq;           //int8_t    tpm_pwm_freq        (TPMn_e,            uint32_t freq, uint32_t core_khz);                          //����TPM��Ƶ�ʣ���Ƶ�ʺ���Ҫ��������ռ�ձȣ�

    //TPM  ���벶׽
    void *      tpm_input_init;         //void      tpm_input_init      (TPMn_e, TPM_CHn_e, TPM_Input_cfg cfg,TPM_PS_e ps,PTXn_e pin);      //���벶׽��ʼ��
    void *      tpm_input_get;          //uint16_t  tpm_input_get       (TPMn_e, TPM_CHn_e);                                                //���벶׽ģʽ�£���ȡ��׽�¼�����ʱ�ļ�����ֵ(�������β�׽֮��Ĳ�ֵ���ж�����Ƶ��)
    void *      tpm_input_clean;        //void      tpm_input_clean     (TPMn_e );                                                          //��ռ�������ֵ

    //TPM  �������
    void *      tpm_pulse_init;         //void      tpm_pulse_init      (TPMn_e tpmn,TPM_CLKIN_e clkin,TPM_PS_e ps,PTXn_e pin);             //���������ʼ��
    void *      tpm_pulse_get;          //uint16_t  tpm_pulse_get       (TPMn_e tpmn);                                                      //��ȡ������
    void *      tpm_pulse_clean;        //void      tpm_pulse_clean     (TPMn_e tpmn);                                                      //���������

    //FTM  PWM���
    void *      ftm_pwm_init;           //int8_t    ftm_pwm_init        (FTMn_e, FTM_CHn_e, uint32_t freq, float duty,PTXn_e pin,uint32_t bus_khz);     //��ʼ��FTM��PWM���ܲ�����Ƶ�ʡ�ռ�ձȡ�����ͨ�����ռ�ձȡ�ͬһ��FTM����ͨ����PWMƵ����һ���ģ���3��FTM(FX��4��)
    void *      ftm_pwm_duty;           //void      ftm_pwm_duty        (FTMn_e, FTM_CHn_e,              float duty);                                   //����ͨ��ռ�ձ�,ռ�ձ�Ϊ ��duty * ���ȣ� % ����� FTM_PRECISON ����Ϊ 1000 ��duty = 100 ����ռ�ձ� 100*0.1%=10%
    void *      ftm_pwm_freq;           //int8_t    ftm_pwm_freq        (FTMn_e,            uint32_t freq,uint32_t bus_khz);                            //����FTM��Ƶ�ʣ���Ƶ�ʺ���Ҫ��������ռ�ձȣ�

    //FTM  ���벶׽
    void *      ftm_input_init;         //void      ftm_input_init      (FTMn_e, FTM_CHn_e, FTM_Input_cfg,FTM_PS_e ps,PTXn_e pin);      //���벶׽��ʼ������
    void *      ftm_input_get;          //uint16_t  ftm_input_get       (FTMn_e, FTM_CHn_e);                                            //���벶׽ģʽ�£���ȡ��׽�¼�����ʱ�ļ�����ֵ(�������β�׽֮��Ĳ�ֵ���ж�����Ƶ��)
    void *      ftm_input_clean;        //void      ftm_input_clean     (FTMn_e );                                                      //��ռ�������ֵ

    //FTM  ��������
    void *      ftm_quad_init;          //void      ftm_quad_init       (FTMn_e, FTM_PS_e ps,PTXn_e Apin,PTXn_e Bpin);                  //��ʼ��FTM ���������� ����
    void *      ftm_quad_get;           //int16_t   ftm_quad_get        (FTMn_e);                                                       //��ȡFTM �������� ��������(������ʾ������)
    void *      ftm_quad_clean;         //void      ftm_quad_clean      (FTMn_e);           //�� FTM �������� ��������

    //DAC ģ�����
    void *      dac_init;               //void      dac_init            (DACn_e);               //DACһ��ת����ʼ��
    void *      dac_out;                //void      dac_out             (DACn_e, uint16_t val);    //DACһ��ת������


    //LCD ��ʾ
    void *      lcd_init;               //void      lcd_init            (lcd_t * lcd,uint16_t rgb565);

    void *      lcd_point;              //void      lcd_point           (lcd_t * lcd,Site_t,                            uint16_t rgb565);           //����
    void *      lcd_points;             //void      lcd_points          (lcd_t * lcd,Site_t *site,  uint32_t point_num, uint16_t rgb565);           //��һ�ѵ�

    void *      lcd_rectangle;          //void      lcd_rectangle       (lcd_t * lcd,Site_t,Size_t,                     uint16_t rgb565);           //������
    void *      lcd_cross;              //void      lcd_cross           (lcd_t * lcd,Site_t,uint16_t len,               uint16_t rgb565);           //��ʮ����
    void *      lcd_clear;              //void      lcd_clear           (lcd_t * lcd,uint16_t rgb565);                                              //����


    //LCD Ӣ���ַ���������ʾ
    void *      lcd_char_6x12;          //void      lcd_char_6x12       (lcd_t * lcd,Site_t site, uint8 ascii, uint16_t Color, uint16_t bkColor) ;                          //��ʾӢ���ַ�
    void *      lcd_str_6x12;           //void      lcd_str_6x12        (lcd_t * lcd,Site_t site, uint8 *Str,  uint16_t Color, uint16_t bkColor);                           //��ʾӢ���ַ���
    void *      lcd_num_6x12;           //uint8_t   lcd_num_6x12        (lcd_t * lcd,Site_t site, uint32_t num,uint16_t Color, uint16_t bkColor);                           //��ʾ�޷�������
    void *      lcd_snum_6x12;          //uint8_t   lcd_snum_6x12       (lcd_t * lcd,Site_t site, int32 num,   uint16_t Color, uint16_t bkColor);                           //��ʾ�з�������

    void *      lcd_num_bc_6x12;        //void      lcd_num_bc_6x12     (lcd_t * lcd,Site_t site, uint32 num, uint8_t max_num_bit,uint16 Color, uint16 bkColor);            //��ʾ�޷�������(������������)
    void *      lcd_snum_bc_6x12;       //void      lcd_snum_bc_6x12    (lcd_t * lcd,Site_t site, uint32 num, uint8_t max_num_bit,uint16 Color, uint16 bkColor);            //��ʾ�з�������(������������)

    //LCD Ӣ��������ʾ
    void *      lcd_char_8x16;          //void      lcd_char_8x16       (lcd_t * lcd,Site_t site, uint8 ascii, uint16_t Color, uint16_t bkColor);                               //��ʾӢ���ַ�
    void *      lcd_str_8x16;           //void      lcd_str_8x16        (lcd_t * lcd,Site_t site, uint8 *Str,  uint16_t Color, uint16_t bkColor);                               //��ʾӢ���ַ���
    void *      lcd_num_8x16;           //uint8_t   lcd_num_8x16        (lcd_t * lcd,Site_t site, uint32_t num,uint16_t Color, uint16_t bkColor) ;                              //��ʾ�޷�������
    void *      lcd_snum_8x16;          //uint8_t   lcd_snum_8x16       (lcd_t * lcd,Site_t site, int32 num,   uint16_t Color, uint16_t bkColor) ;                              //��ʾ�з�������

    void *      lcd_num_bc_8x16;        //void      lcd_num_bc_8x16     (lcd_t * lcd,Site_t site, uint32 num, uint8_t max_num_bit,uint16 Color, uint16 bkColor);                //��ʾ�޷�������(������������)
    void *      lcd_snum_bc_8x16;       //void      lcd_snum_bc_8x16    (lcd_t * lcd,Site_t site, uint32 num, uint8_t max_num_bit,uint16 Color, uint16 bkColor);                //��ʾ�з�������(������������)




    //LCD ͼ����ʾ
    void *      lcd_img_binary;         //void      lcd_img_binary      (lcd_t * lcd,Site_t site, Size_t size, uint8 *img,                uint16_t Color, uint16_t bkColor);    //��ʾ��ֵ��ͼ��
    void *      lcd_img_binary_z;       //void      lcd_img_binary_z    (lcd_t * lcd,Site_t site, Size_t size, uint8 *img, Size_t imgsize,uint16_t Color, uint16_t bkColor);    //��ʾ��ֵ��ͼ��(������)
    void *      lcd_img_gray;           //void      lcd_img_gray        (lcd_t * lcd,Site_t site, Size_t size, uint8 *img);                                                     //��ʾ�Ҷ�ͼ��
    void *      lcd_img_gray_z;         //void      lcd_img_gray_z      (lcd_t * lcd,Site_t site, Size_t size, uint8 *img, Size_t imgsize);                                     //��ʾ�Ҷ�ͼ��(������)
    void *      lcd_img_rgb565;         //void      lcd_img_rgb565      (lcd_t * lcd,Site_t site, Size_t size, uint8 *img) ;                                                    //��ɫ
    void *      lcd_img_rgb565_z;       //void      lcd_img_rgb565_z    (lcd_t * lcd,Site_t site, Size_t size, uint8 *img, Size_t imgsize);                                     //��ɫ(������)

    //LCD ������ʾ
    void *      lcd_wave;               //void      lcd_wave            (lcd_t * lcd,Site_t site,Size_t size,uint8 *img,uint8 maxval,uint16_t Color ,uint16_t bkColor);         //������ʾ����������ɫ��maxval ���ֵ��ʾ������ֵ�������������ֵ����
    void *      lcd_wave_display;       //void      lcd_wave_display    (lcd_t * lcd,Site_t site,Size_t size,uint8 *img,uint8 maxval,uint16_t Color);                           //������ʾ������������ɫ


    //ִ����APP API�ӿ� ������ͨ�� �������ò�ͬ������ĺ���������ջ��ַ��
    void *      jmp_app;                //void      jmp_app             (uint32_t sp, uint32_t pc);          //��ת���µ�APP
    void *      jmp_bin;                //void      jmp_bin             (uint32_t addr);                     //��ת���µ�APP BIN�ļ� ��bin�ļ��ĵ�1��32λ������ջ��ַ����2��32λ����������������ڣ�

}mydata_boot_in_t;




typedef struct
{
    uint16_t    flag;                   //���
    uint16_t    ver;                    //�汾

    uint8_t *   chinese;                //�����ֿ����  ��С�� USE_FOUNT_SIZE �ж�


    //void *      get_isr;                //int       get_isr_info    (char * str);                               //��ȡ�жϺ�����Ӧ�ľ�������




    //LCD ������ʾ
    void *      lcd_char_ch_12x12;      //void      lcd_char_ch_12x12   (lcd_t * lcd,Site_t site, const uint8 *str, uint16_t Color, uint16_t bkColor,char * chinese_12x12);     //��ʾ�����ַ�          ���� USE_FOUNT_SIZE Ϊ12�����һ����������Ҫд��
    void *      lcd_str_ch_12x12;       //void      lcd_str_ch_12x12    (lcd_t * lcd,Site_t site, const uint8 *str, uint16_t Color, uint16_t bkColor,char * chinese_12x12);     //��ʾ�����ַ���        ���� USE_FOUNT_SIZE Ϊ12�����һ����������Ҫд��
    void *      lcd_str_ench_12x12;     //void      lcd_str_ench_12x12  (lcd_t * lcd,Site_t site, const uint8 *str, uint16_t Color, uint16_t bkColor,char * chinese_12x12);     //��ʾ����Ӣ�Ļ���ַ��� ���� USE_FOUNT_SIZE Ϊ12�����һ����������Ҫд��




    void *      lcd_char_ch_16x16;      //void      lcd_char_ch_16x16   (lcd_t * lcd,Site_t site, const uint8 *str, uint16_t Color, uint16_t bkColor,char * chinese_16x16);     //��ʾ�����ַ�          ���� USE_FOUNT_SIZE Ϊ16�����һ����������Ҫд��
    void *      lcd_str_ch_16x16;       //void      lcd_str_ch_16x16    (lcd_t * lcd,Site_t site, const uint8 *str, uint16_t Color, uint16_t bkColor,char * chinese_16x16);     //��ʾ�����ַ���        ���� USE_FOUNT_SIZE Ϊ16�����һ����������Ҫд��
    void *      lcd_str_ench_16x16;     //void      lcd_str_ench_16x16  (lcd_t * lcd,Site_t site, const uint8 *str, uint16_t Color, uint16_t bkColor,char * chinese_16x16);     //��ʾ����Ӣ�Ļ���ַ��� ���� USE_FOUNT_SIZE Ϊ16�����һ����������Ҫд��


}mydata_in_t;


#ifndef FWD_BOOT_LIB

#define    FTMN_addr                              0x0000dcec
#define    TPMN_addr                              0x0000e010
#define    ascii_6x12_addr                        0x0000cba0
#define    ascii_8x16_addr                        0x0000c5b0
#define    atoi_addr                              0x00008187
#define    dac_init_addr                          0x0000d9b5
#define    dac_out_addr                           0x0000da09
#define    dwt_delay_ms_addr                      0x0000da85
#define    dwt_delay_us_addr                      0x0000da2d
#define    flash_data_init_addr                   0x0000c339
#define    flash_data_load_addr                   0x0000c495
#define    flash_data_reset_addr                  0x0000c40f
#define    flash_data_save_addr                   0x0000c4c1
#define    flash_erase_sector_addr                0x0000c031
#define    flash_init_addr                        0x0000c003
#define    flash_write_addr                       0x0000c095
#define    flash_write_buf_addr                   0x0000c13b
#define    ftm_input_clean_addr                   0x0000b6ef
#define    ftm_input_get_addr                     0x0000b6db
#define    ftm_input_init_addr                    0x0000b553
#define    ftm_pwm_duty_addr                      0x0000b3bd
#define    ftm_pwm_freq_addr                      0x0000b4cb
#define    ftm_pwm_init_addr                      0x0000b197
#define    ftm_quad_clean_addr                    0x0000b8af
#define    ftm_quad_get_addr                      0x0000b89d
#define    ftm_quad_init_addr                     0x0000b6fd
#define    ftoa_addr                              0x00008809
#define    get_isr_info_addr                      0x00009fc5
#define    img_extract_addr                       0x00009e1d
#define    itoa_addr                              0x000082b1
#define    jmp_app_addr                           0x00009e09
#define    jmp_bin_addr                           0x00009e0f
#define    lcd_char_6x12_addr                     0x0000a551
#define    lcd_char_8x16_addr                     0x0000a1d1
#define    lcd_clear_addr                         0x0000a05f
#define    lcd_cross_addr                         0x0000a089
#define    lcd_img_binary_addr                    0x0000aadf
#define    lcd_img_binary_z_addr                  0x0000ab59
#define    lcd_img_gray_addr                      0x0000a8f3
#define    lcd_img_gray_z_addr                    0x0000a997
#define    lcd_img_rgb565_addr                    0x0000a95b
#define    lcd_img_rgb565_z_addr                  0x0000aa4d
#define    lcd_init_addr                          0x00009ff5
#define    lcd_num_6x12_addr                      0x0000a6e5
#define    lcd_num_8x16_addr                      0x0000a349
#define    lcd_num_bc_6x12_addr                   0x0000a7af
#define    lcd_num_bc_8x16_addr                   0x0000a46d
#define    lcd_point_addr                         0x0000a185
#define    lcd_points_addr                        0x0000a1a9
#define    lcd_rectangle_addr                     0x0000a025
#define    lcd_snum_6x12_addr                     0x0000a823
#define    lcd_snum_8x16_addr                     0x0000a411
#define    lcd_snum_bc_6x12_addr                  0x0000a87f
#define    lcd_snum_bc_8x16_addr                  0x0000a4df
#define    lcd_str_6x12_addr                      0x0000a629
#define    lcd_str_8x16_addr                      0x0000a28d
#define    lcd_wave_addr                          0x0000ac13
#define    lcd_wave_display_addr                  0x0000acb9
#define    lptmr_delay_ms_addr                    0x0000d35b
#define    lptmr_delay_us_addr                    0x0000d3c7
#define    lptmr_pulse_clean_addr                 0x0000d341
#define    lptmr_pulse_get_addr                   0x0000d321
#define    lptmr_pulse_init_addr                  0x0000d2b5
#define    lptmr_time_close_addr                  0x0000d495
#define    lptmr_time_get_ms_addr                 0x0000d477
#define    lptmr_time_get_us_addr                 0x0000d4d1
#define    lptmr_time_start_ms_addr               0x0000d44f
#define    lptmr_time_start_us_addr               0x0000d49d
#define    lptmr_timing_ms_addr                   0x0000d39b
#define    lptmr_timing_us_addr                   0x0000d415
#define    memcpy_addr                            0x00009f1f
#define    memset_addr                            0x00009f9b
#define    pit_close_addr                         0x0000d705
#define    pit_delay_addr                         0x0000d573
#define    pit_init_addr                          0x0000d511
#define    pit_time_get_addr                      0x0000d6a1
#define    pit_time_start_addr                    0x0000d627
#define    pll_init_addr                          0x0000d07f
#define    printf_addr                            0x0000d915
#define    sprintf_addr                           0x000094dd
#define    strlen_addr                            0x00009fb1
#define    systick_delay_addr                     0x0000daa1
#define    systick_delay_ms_addr                  0x0000dac5
#define    systick_timing_addr                    0x0000dadd
#define    tpm_input_clean_addr                   0x0000be29
#define    tpm_input_get_addr                     0x0000be15
#define    tpm_input_init_addr                    0x0000bcb3
#define    tpm_pulse_clean_addr                   0x0000bf4f
#define    tpm_pulse_get_addr                     0x0000bf5d
#define    tpm_pulse_init_addr                    0x0000be37
#define    tpm_pwm_duty_addr                      0x0000bbd3
#define    tpm_pwm_freq_addr                      0x0000bc49
#define    tpm_pwm_init_addr                      0x0000ba43







#define     ascii_6x12      ((const char *)ascii_6x12_addr)
#define     ascii_8x16      ((const char *)ascii_8x16_addr)


#endif

//���ݵĳߴ� ������ FLASH_ALIGN_ADDR ����
//
typedef struct
{
    uint16_t    sectornum_start;            //��ʼ������
    uint16_t    sectornum_end;              //����������
    void *     data_addr;                   //���ݵĵ�ַ
    uint16_t    data_size;                  //���ݵĳߴ�
    uint16_t    res1;                       //�������ײ�ʹ�� ����ɾ��
    uint32_t    res2[2];                    // �������ײ�ʹ�� ����ɾ��


}flash_data_t;

//     �̼�����ʼ��ַ (�û����ɸ��ģ�����APP����ʶ��)
#define START_APP_ADDR  (32*1024)               //APP������ַ
#if defined(MK60DZ10)
#define START_FWD_ADDR  (256*1024)              //DN ����¼����벿��flash��256k
#elif defined(MK60FN15)
#define START_FWD_ADDR  (512*1024)              //FN ����¼����벿��flash��512k
#elif defined(MK60FX15)
#define START_FWD_ADDR  (0x10000000)            //FX ����¼�� flexNVM
#elif defined(MK66FX18)
#define START_FWD_ADDR  (0x10000000)            //K66FX ����¼�� flexNVM
#endif

#define BOOT_FWD_ADDR   (0x8000)

//�ڲ��ã��û������ע
#define     OFFSET(type, member)                (uint32)(&(((type *)0)->member))
#define     IN_ADDR(member)                     (*((uint32_t *)(START_FWD_ADDR + OFFSET(mydata_in_t, member)) ))
#define     ENTER_FUN(func,...)                 (*(func##_t)(IN_ADDR(func)))(##__VA_ARGS__)
#define     ENTER_FUN_ADDR(func,...)            (*(func##_t)(func##_addr))(##__VA_ARGS__)
#define     PENTER_FUN_ADDR(func,...)            (*(func##_t)(func##_addr))(##__VA_ARGS__)

#define     BOOT_ADDR(member)                   (*((uint32_t *)(BOOT_FWD_ADDR + OFFSET(mydata_boot_in_t, member)) ))


//����4���Ǳ��ã���ENTER_FUN_ADDR��һ���ġ������enter�������뵽����enter�������βΣ��ͻᵼ����ʾ��
// no definition for "ENTER_FUN_ADDR"
//�����β���ĺ�û������������ֻ��Ҫ���βεĺ껻���·��ļ���
#define     ENTER_FUN_ADDR0(func,...)            (*(func##_t)(func##_addr))(##__VA_ARGS__)
#define     ENTER_FUN_ADDR1(func,...)            (*(func##_t)(func##_addr))(##__VA_ARGS__)
#define     ENTER_FUN_ADDR2(func,...)            (*(func##_t)(func##_addr))(##__VA_ARGS__)
#define     ENTER_FUN_ADDR3(func,...)            (*(func##_t)(func##_addr))(##__VA_ARGS__)


//�û��� API �ӿڵ���
//
#ifndef FWD_LIB         //�����ڹ����ж���˺궨��(�ڲ�ʶ���õ�) by ɽ��

//#define  enter_init()      (((uint16_t)IN_ADDR(flag)==0x55A5) && (uint16_t)IN_ADDR(ver)==FWD_VER)      //�����жϹ̼��ļ��Ƿ���� ,APP��Ҫ��ʼ��ʱִ�� ASSERT(enter_init());


//K66FX1M0VLQ18     Flash����     1M��flash��256K ROM API ,256K RAM
#define     FLASH_SECTOR_SIZE       (4*1024)                //������С Ϊ 4k �ֽ�
#define     FLASH_SECTOR_NUM        (256)                   //������

#define     FLASH_ALIGN_ADDR        8                       //��ַ����������
typedef     uint64                  FLASH_WRITE_TYPE;       //flash_write ����д�� ����������

extern int core_clk_khz;
extern int core_clk_mhz;
extern int bus_clk_khz;

typedef enum
{
    PLLUSR      ,  //������Ƶ�ʣ����б�д��Ƶ������
    PLL80       ,
    PLL88       ,
    PLL96       ,
    PLL100       ,
    PLL120       ,
    PLL140       ,
    PLL152       ,
    PLL160       ,
    PLL180       ,
    PLL188       ,
    PLL200       ,
    PLL224       ,
    PLL232       ,
    PLL240       ,
    PLL248       ,
    PLL256       ,
    PLL264       ,

    //�������Ǻ�����ʱ������MHzΪ��λ����֧��С����
    PLL_MAX,
} PLL_e;

typedef void lcd_modeinit_t(Size_t *size);              //��ʼ�����ѷֱ���д�뵽size
typedef void lcd_ptlon_t(Site_t site, Size_t size);
typedef void lcd_ramwr_t(void);
typedef void lcd_wr_data_t(uint16_t data);


typedef struct
{
    union {
        struct{
            uint16_t lcd_w;         //LCD ��
            uint16_t lcd_h;         //LCD ��
        };
        Size_t size;
    } ;

    lcd_modeinit_t  *   init;      //��ʼ��
    lcd_ptlon_t *       ptlon;     //����

    lcd_ramwr_t *       ramwr;     //дģʽ
    lcd_wr_data_t *     wr_data;   //д����


}lcd_t;

extern lcd_t *  glcd;   //��Ҫ�ⲿ��Ӷ���

#define LCD_H   glcd->lcd_h
#define LCD_W   glcd->lcd_w

/******������ɫ*****/
#define RED     0XF800    //��ɫ
#define GREEN   0X07E0    //��ɫ
#define BLUE    0X001F    //��ɫ
#define BRED    0XF81F
#define GRED    0XFFE0    //��ɫ
#define GBLUE   0X07FF    //
#define BLACK   0X0000    //��ɫ
#define WHITE   0XFFFF    //��ɫ
#define YELLOW  0xFFE0    //��ɫ

#define FCOLOUR         BLUE    //����������ɫ
#define BCOLOUR         RED     //���屳����ɫ

//��ȡRGB��3Ԫ�أ�rgb565������16λ
#define RGB565_R(rgb565)                ((uint8)(((uint16)(rgb565)>>11) &0x1F))
#define RGB565_G(rgb565)                ((uint8)(((uint16)(rgb565)>> 5) &0x3F))
#define RGB565_B(rgb565)                ((uint8)( (uint16)(rgb565)      &0x1F))


#define GRAY_2_RGB565(gray)             ((uint16)((((uint8)(gray)>>3)<<11)|(((uint8)(gray)>>2)<<5)|((uint8)(gray)>>3)))

#define RGB565_2_GRAY(rgb565)           ((uint8)(((RGB565_R(rgb565)*235+RGB565_G(rgb565)*613+RGB565_B(rgb565)*625)+1)>>8))  //  31*235+63*613+31*625+1  = 255*256


#define RGB565_H(rgb565)                ((uint8)(((uint16)(rgb565))>>8))
#define RGB565_L(rgb565)                (uint8)(rgb565))

#define RGB24_RGB565(R,G,B)             ((uint16)((((uint8)(R)>>3)<<11)|(((uint8)(G)>>2)<<5)|((uint8)(B)>>3)))
#define RGB555_RGB565(rgb555)           (((((uint16)(rgb555)) & (uint16)(~0x1F)) << 1) |  (((uint16)(rgb555)) & 0x1F))
#define BGR555_RGB565(bgr555)           ((((uint16)(bgr555)<<11) & (uint16)(0x1F<<11)) | (((uint16)(bgr555)) & (uint16)(0x1F<<5)) | (((uint16)(bgr555)>>10) & (uint16)(0x1F)))

#define LCD_MAX_NUM_BIT  5

#define lcd_num_c_6x12(site,num,color,bkColor)           lcd_num_bc_6x12(site, num,LCD_MAX_NUM_BIT,color,bkColor)
#define lcd_snum_c_6x12(site,num,color,bkColor)          lcd_snum_bc_6x12(site, num,LCD_MAX_NUM_BIT,color,bkColor)

#define lcd_num_c_8x16(site,num,color,bkColor)           lcd_num_bc_8x16(site, num,LCD_MAX_NUM_BIT,color,bkColor)
#define lcd_snum_c_8x16(site,num,color,bkColor)          lcd_snum_bc_8x16(site, num,LCD_MAX_NUM_BIT,color,bkColor)


#define  CHINESE            ((uint8_t *)(IN_ADDR(chinese)))            // �����ֿ�  (�ߴ翴�ṹ��mydata_in_t��ע��)

#if( USE_FOUNT_SIZE == 16 )

#define    ASCII              ascii_8x16

#define    lcd_char           lcd_char_8x16
#define    lcd_str            lcd_str_8x16
#define    lcd_num            lcd_num_8x16
#define    lcd_snum           lcd_snum_8x16
#define    lcd_num_bc         lcd_num_bc_8x16
#define    lcd_snum_bc        lcd_snum_bc_8x16
#define    lcd_char_ch        lcd_char_ch_16x16
#define    lcd_str_ch         lcd_str_ch_16x16
#define    lcd_str_ench       lcd_str_ench_16x16

#define    lcd_num_c          lcd_num_c_8x16
#define    lcd_snum_c         lcd_snum_c_8x16

#elif ( USE_FOUNT_SIZE == 12 )

#define    ASCII              ascii_6x12

#define    lcd_char           lcd_char_6x12
#define    lcd_str            lcd_str_6x12
#define    lcd_num            lcd_num_6x12
#define    lcd_snum           lcd_snum_6x12
#define    lcd_num_bc         lcd_num_bc_6x12
#define    lcd_snum_bc        lcd_snum_bc_6x12
#define    lcd_char_ch        lcd_char_ch_12x12
#define    lcd_str_ch         lcd_str_ch_12x12
#define    lcd_str_ench       lcd_str_ench_12x12

#define    lcd_num_c          lcd_num_c_6x12
#define    lcd_snum_c         lcd_snum_c_6x12
#endif



//����TPMģ���
typedef enum
{
    //TPM0,
    TPM1,
    TPM2,

    TPM_MAX,
} TPMn_e;

//����TPM ͨ����
typedef enum
{

    TPM_CH0,
    TPM_CH1,
    TPM_CH2,
    TPM_CH3,
    TPM_CH4,
    TPM_CH5,
    TPM_CH6,
    TPM_CH7,

} TPM_CHn_e;

typedef enum
{
    TPM_CLKIN0,         // ��Ӧ�Ĺܽ��뿴 TPM_CLKIN0_PIN �Ķ���
    TPM_CLKIN1,         // ��Ӧ�Ĺܽ��뿴 TPM_CLKIN1_PIN �Ķ���
} TPM_CLKIN_e;

//��Ƶϵ��
typedef enum
{
    TPM_PS_1,
    TPM_PS_2,
    TPM_PS_4,
    TPM_PS_8,
    TPM_PS_16,
    TPM_PS_32,
    TPM_PS_64,
    TPM_PS_128,

    TPM_PS_MAX,
}TPM_PS_e;

//���ڿ�ʼ���� ���� ���ؼ��� (��ʱû�õ�)
typedef enum
{
    EXTRG_IN,       //�ⲿ����
    CMP0_OUT,       //CMP0 ���

    TRG_CFG_RES0,   //����
    TRG_CFG_RES1,   //����

    PIT0_TRG,       //PIT0 ����
    PIT1_TRG,       //PIT0 ����

    TRG_CFG_RES2,   //����
    TRG_CFG_RES3,   //����

    TPM0_OVER,      //TPM0���
    TPM1_OVER,      //TPM1���
    TPM2_OVER,      //TPM2���

    TRG_CFG_RES4,   //����

    RTC_ALARM,      //RTC����
    RTC_SEC,        //RTC���ж�

    LPTMR_TRG,      //LPTMR ����

    TRG_CFG_RES5,   //����


}TPMx_TRG_CFG_e;



//TPM ���벶׽����
typedef enum
{
    TPM_Rising,               //�����ز�׽
    TPM_Falling,              //�½��ز�׽
    TPM_Rising_or_Falling     //�����ز�׽
} TPM_Input_cfg;


#define TPMN     ((TPM_MemMapPtr *) TPMN_addr )

#define TPM_IRQ_EN(TPMn,CHn)        TPM_CnSC_REG(TPMN[TPMn],CHn) |= TPM_CnSC_CHIE_MASK       //���� TPMn_CHn �ж�
#define TPM_IRQ_DIS(TPMn,CHn)       TPM_CnSC_REG(TPMN[TPMn],CHn) &= ~TPM_CnSC_CHIE_MASK      //�ر� TPMn_CHn �ж�



//����FTMģ���
typedef enum
{
    FTM0,
    FTM1,
    FTM2,
    FTM3,

    FTM_MAX,
} FTMn_e;

//����FTM ͨ����
typedef enum
{

    FTM_CH0,
    FTM_CH1,
    FTM_CH2,
    FTM_CH3,
    FTM_CH4,
    FTM_CH5,
    FTM_CH6,
    FTM_CH7,

} FTM_CHn_e;

//��Ƶϵ��
typedef enum
{
    FTM_PS_1,
    FTM_PS_2,
    FTM_PS_4,
    FTM_PS_8,
    FTM_PS_16,
    FTM_PS_32,
    FTM_PS_64,
    FTM_PS_128,

    FTM_PS_MAX,
}FTM_PS_e;      //��Ƶֵ =  (1<< FTM_PS_e) ,����  FTM_PS_2  ��Ӧ�� ��Ƶֵ = (1<<FTM_PS_2) = (1<<1) = 2

/*********************** ���벶׽ **************************/
//FTM ���벶׽����
typedef enum
{
    FTM_Rising,               //�����ز�׽
    FTM_Falling,              //�½��ز�׽
    FTM_Rising_or_Falling     //�����ز�׽
} FTM_Input_cfg;

#define FTMN     ((FTM_MemMapPtr *) FTMN_addr )


#define FTM_IRQ_EN(FTMn,CHn)        FTM_CnSC_REG(FTMN[FTMn],CHn) |= FTM_CnSC_CHIE_MASK       //���� FTMn_CHn �ж�
#define FTM_IRQ_DIS(FTMn,CHn)       FTM_CnSC_REG(FTMN[FTMn],CHn) &= ~FTM_CnSC_CHIE_MASK      //�ر� FTMn_CHn �ж�


//����PITģ���
typedef enum
{
    PIT0,
    PIT1,
    PIT2,
    PIT3,

    PIT_MAX,
} PITn_e;

#define     PIT_Flag_Clear(PITn_e)          PIT_TFLG(PITn_e)|=PIT_TFLG_TIF_MASK        //���жϱ�־��д1 ��ձ�־λ��

//ms�Ǻ���=0.001�� us��΢��=0.000001�� ns������=0.000000001��
#define     pit_clk_khz         bus_clk_khz
#define     pit_init_ms(PITn_e,ms)          pit_init(PITn_e,ms * pit_clk_khz);         //��ʼ��PITn�������ö�ʱʱ��(��λΪ ms)
#define     pit_init_us(PITn_e,us)          pit_init(PITn_e,us * pit_clk_khz/1000);    //��ʼ��PITn�������ö�ʱʱ��(��λΪ us)
#define     pit_init_ns(PITn_e,ns)          pit_init(PITn_e,ns * pit_clk_khz/1000000); //��ʼ��PITn�������ö�ʱʱ��(��λΪ ns)

#define     pit_delay_ms(PITn_e,ms)          pit_delay(PITn_e,ms * pit_clk_khz);        //PIT��ʱ ms
#define     pit_delay_us(PITn_e,us)          pit_delay(PITn_e,us * pit_clk_khz/1000);   //PIT��ʱ us
#define     pit_delay_ns(PITn_e,ns)          pit_delay(PITn_e,ns * pit_clk_khz/1000000);//PIT��ʱ ns

#define     pit_time_get_ms(PITn_e)   (pit_time_get(PITn_e)/pit_clk_khz)                    //��ȡ��ʱʱ�䣨��λΪ ms��
#define     pit_time_get_us(PITn_e)   (pit_time_get(PITn_e)/(pit_clk_khz/1000))             //��ȡ��ʱʱ�䣨��λΪ us��

/**
 *  @brief LPTMR�����������ܽ�ѡ��
 */
typedef enum
{
    //ֻ��1��2�ܽţ���û��0��3�ܽ�
    LPT0_ALT1 = 1,      // PTA19
    LPT0_ALT2 = 2       // PTC5
} LPT0_ALTn;

/**
 *  @brief LPTMR�������������ʽ
 */
typedef enum LPT_CFG
{
    LPT_Rising  = 0,    //�����ش���
    LPT_Falling = 1     //�½��ش���
} LPT_CFG;

#define LPTMR_Flag_Clear()  (LPTMR0_CSR |= LPTMR_CSR_TCF_MASK)         //���LPT�Ƚϱ�־λ

typedef enum DACn       //DACģ��
{
    DAC0,
    DAC1
} DACn_e;


    //MCG ��Ƶ����                                    ************************************************
//��Ƶ����
typedef uint16_t    (*pll_init_t)        (PLL_e pll,uint16_t max_bus_mhz,uint16_t max_flexbus_mhz,uint16_t max_flash_mhz);
#define pll_init(pll)                             ENTER_FUN_ADDR(pll_init,pll,MAX_BUS_CLK,MAX_FLEXBUS_CLK,MAX_FLASH_CLK)

    //dwt ��ʱ����                                    ************************************************
//dwt��ʱ������������ DWT_DELAY_US(us) ������
typedef void      (*dwt_delay_us_t)        (uint32_t core_clk,uint32_t us);
#define dwt_delay_us(...)                         ENTER_FUN_ADDR(dwt_delay_us,core_clk_khz,##__VA_ARGS__)


//dwt��ʱ������������ DWT_DELAY_MS(ms) ������
typedef void      (*dwt_delay_ms_t)        (uint32_t core_clk,uint32_t ms);
#define dwt_delay_ms(...)                         ENTER_FUN_ADDR(dwt_delay_ms,core_clk_khz,##__VA_ARGS__)



    //SYSTICK ��ʱ����                                ************************************************
#define     SYSTICK_CLK_KHZ                 core_clk_khz
//��ʱ time ��core���ڣ�24λ����
typedef void      (*systick_delay_t)       (uint32_t time);
#define systick_delay(...)                        ENTER_FUN_ADDR(systick_delay,##__VA_ARGS__)



//��ʱ time ���ס����ջ��Ժ궨�� SYSTICK_DELAY_MS(ms) �滻
typedef void      (*systick_delay_ms_t)    (uint32_t ms,uint32_t core_khz);
#define     systick_delay_ms(ms)                     ENTER_FUN_ADDR(systick_delay_ms,ms,SYSTICK_CLK_KHZ)
#define     systick_delay_us(us)          systick_delay(us * SYSTICK_CLK_KHZ/1000);   //��ʱ us
#define     systick_delay_ns(ns)          systick_delay(ns * SYSTICK_CLK_KHZ/1000000);//��ʱ ns


    //SYSTICK ��ʱ����                                ************************************************
//��ʱ�жϳ�ʼ�������� time��core���ڣ�24bit
typedef void      (*systick_timing_t)      (uint32_t time);
#define systick_timing(...)                       ENTER_FUN_ADDR(systick_timing,##__VA_ARGS__)

#define systick_timing_ms(ms)               systick_timing(ms * SYSTICK_CLK_KHZ);        //��ʱ us
#define systick_timing_us(us)               systick_timing(us * SYSTICK_CLK_KHZ/1000);   //��ʱ us
#define systick_timing_ns(ns)               systick_timing(ns * SYSTICK_CLK_KHZ/1000000);//��ʱ ns



    //ִ����APP API�ӿ� ������ͨ�� �������ò�ͬ������ĺ���������ջ��ַ��      ************************************************
//��ת���µ�APP
typedef void      (*jmp_app_t)             (uint32_t sp, uint32_t pc);
#define jmp_app(...)                              ENTER_FUN_ADDR(jmp_app,##__VA_ARGS__)


//��ת���µ�APP BIN�ļ� ��bin�ļ��ĵ�1��32λ������ջ��ַ����2��32λ����������������ڣ�
typedef void      (*jmp_bin_t)             (uint32_t addr);
#define jmp_bin(...)                              ENTER_FUN_ADDR(jmp_bin,##__VA_ARGS__)








    //����С����                                       ************************************************
//�ڴ渴��
typedef void *    (*memcpy_t)  ( uint8_t *dst, uint8_t *src, uint32_t count);
#define memcpy(...)                               ENTER_FUN_ADDR(memcpy,##__VA_ARGS__)


//�ڴ�������ֵ
typedef void *    (*memset_t)  (void *src, int c, int count);
#define memset(...)                               ENTER_FUN_ADDR(memset,##__VA_ARGS__)

//���ַ����ĳ���
typedef int       (*strlen_t)(const char * str);
#define strlen(...)                               ENTER_FUN_ADDR0(strlen,##__VA_ARGS__)


//����ͷ��ѹ
typedef void      (*img_extract_t)(void *dst, void *src, uint32_t srclen);
#define img_extract(...)                          ENTER_FUN_ADDR(img_extract,##__VA_ARGS__)



//��ȡ�жϺ�����Ӧ�ľ�������
typedef int       (*get_isr_info_t)    (char * str);
#define get_isr_info(...)                         ENTER_FUN_ADDR(get_isr_info,##__VA_ARGS__)




    //�ַ��� ���� ת��                                   ************************************************
//�ַ�����ʽ����������
typedef int       (*sprintf_t)         (char *buf, const char *fmt, ...) ;
#define sprintf(...)                              ENTER_FUN_ADDR(sprintf,##__VA_ARGS__)


//printf����ӡ��������Ҫ�Լ�ʵ�� enter_fputc ����
extern int enter_fputc(char ch);                    //��Ҫ�û��Զ���ʵ�ִ˺���
typedef int fputc_t (char c);
typedef int (*printf_t)(fputc_t *fp, const char *fmt, ...);
#define  PRINTF_ENTER_FUN_ADDR(a,b,c,...)                 PENTER_FUN_ADDR(a,b,c,##__VA_ARGS__)
#define printf(fmt,...)                               PRINTF_ENTER_FUN_ADDR(printf,enter_fputc,fmt,##__VA_ARGS__)




//�ַ���ת������
typedef int       (*atoi_t)            (char *str);
#define atoi(...)                                 ENTER_FUN_ADDR(atoi,##__VA_ARGS__)


//����ת��Ϊ�ַ���
typedef char *    (*itoa_t)            (int n, char * chBuffer);
#define itoa(...)                                 ENTER_FUN_ADDR(itoa,##__VA_ARGS__)


//����ת��Ϊ�ַ���
typedef char *    (*ftoa_t)            (double dValue, char * chBuffer);
#define ftoa(...)                                 ENTER_FUN_ADDR(ftoa,##__VA_ARGS__)




// ****************** FLASH API ר�� ******************

//��ʼ��Flash
typedef void      (*flash_init_t)          ();
#define flash_init(...)                           ENTER_FUN_ADDR(flash_init,##__VA_ARGS__)


//����ָ��flash����
typedef uint8_t   (*flash_erase_sector_t)  (uint16_t sectorNum);
#define flash_erase_sector(...)                   ENTER_FUN_ADDR(flash_erase_sector,##__VA_ARGS__)


//д��flash����
typedef uint8_t   (*flash_write_t)         (uint16_t sectorNum, uint16_t offset, FLASH_WRITE_TYPE data);
#define flash_write(...)                          ENTER_FUN_ADDR(flash_write,##__VA_ARGS__)


//�ӻ�����д��flash����
typedef uint8_t   (*flash_write_buf_t)     (uint16_t sectorNum, uint16_t offset, uint16_t cnt, uint8 buf[]);
#define flash_write_buf(...)                      ENTER_FUN_ADDR(flash_write_buf,##__VA_ARGS__)



#define     flash_off(sectorNo,offset)              ((uint32)(((sectorNo)*FLASH_SECTOR_SIZE) + (offset)))
#define     flash_read(sectorNo,offset,type)        (*(type *)flash_off(sectorNo,offset) )         //��ȡ����

    //flash �洢����                                  ************************************************
//�Խṹ�����ݽ���Ԥ������flash�����ݻ�û��ʼ����������flash
typedef void      (*flash_data_init_t)     (flash_data_t *d);
#define flash_data_init(...)                      ENTER_FUN_ADDR(flash_data_init,##__VA_ARGS__)


//����flash�����ǶԴ洢���ݽ������
typedef void      (*flash_data_reset_t)    (flash_data_t *d);
#define flash_data_reset(...)                     ENTER_FUN_ADDR(flash_data_reset,##__VA_ARGS__)


//�� flash ��������
typedef uint8_t   (*flash_data_load_t)     (flash_data_t *d);
#define flash_data_load(...)                      ENTER_FUN_ADDR(flash_data_load,##__VA_ARGS__)


//�������ݵ�flash
typedef uint8_t   (*flash_data_save_t)     (flash_data_t *d);
#define flash_data_save(...)                      ENTER_FUN_ADDR(flash_data_save,##__VA_ARGS__)








    //PIT. ��ʱ����                                   ************************************************
//��ʼ��PITn�������ö�ʱʱ��(��λΪbusʱ������)
typedef void      (*pit_init_t)            (PITn_e, uint32_t cnt);
#define pit_init(...)                             ENTER_FUN_ADDR(pit_init,##__VA_ARGS__)



    //PIT. ��ʱ����                                   ************************************************
//PIT��ʱ������Ҫ��ʼ���ģ�
typedef void     (*pit_delay_t)           (PITn_e, uint32_t cnt);
#define pit_delay(...)                            ENTER_FUN_ADDR(pit_delay,##__VA_ARGS__)



    //PIT. ��ʱ����                                   ************************************************
//PIT��ʼ��ʱ
typedef void      (*pit_time_start_t)      (PITn_e);
#define pit_time_start(...)                       ENTER_FUN_ADDR(pit_time_start,##__VA_ARGS__)


//��ȡ PITn��ʱʱ��(��ʱʱ��ر� ��ʱ��)����λΪ busʱ�ӣ�(��ֵΪ 0xFFFFFFFF�����ʾ���)
typedef uint32_t  (*pit_time_get_t)        (PITn_e);
#define pit_time_get(...)                         ENTER_FUN_ADDR(pit_time_get,##__VA_ARGS__)


//�ر� PIT ��ʱ
typedef void      (*pit_close_t)           (PITn_e);
#define pit_close(...)                            ENTER_FUN_ADDR(pit_close,##__VA_ARGS__)




    //LPT  ��ʱ����                                   ************************************************
//��ʱ(ms)
typedef void      (*lptmr_delay_ms_t)       (uint16_t ms);
#define lptmr_delay_ms(...)                       ENTER_FUN_ADDR(lptmr_delay_ms,##__VA_ARGS__)


//��ʱ(us)
typedef void      (*lptmr_delay_us_t)       (uint16_t us);
#define lptmr_delay_us(...)                       ENTER_FUN_ADDR(lptmr_delay_us,##__VA_ARGS__)



    //LPT  ��ʱ�жϺ���                                 ************************************************
//��ʱ(ms)
typedef void      (*lptmr_timing_ms_t)      (uint16_t ms);
#define lptmr_timing_ms(...)                      ENTER_FUN_ADDR(lptmr_timing_ms,##__VA_ARGS__)


//��ʱ(us)
typedef void      (*lptmr_timing_us_t)      (uint16_t us);
#define lptmr_timing_us(...)                      ENTER_FUN_ADDR(lptmr_timing_us,##__VA_ARGS__)



    //LPT  ��ʱ����                                   ************************************************
//��ʼ��ʱ(ms)
typedef void      (*lptmr_time_start_ms_t)  (void);
#define lptmr_time_start_ms(...)                  ENTER_FUN_ADDR(lptmr_time_start_ms,##__VA_ARGS__)


//��ȡ��ʱʱ��
typedef uint32_t  (*lptmr_time_get_ms_t)    (void);
#define lptmr_time_get_ms(...)                    ENTER_FUN_ADDR(lptmr_time_get_ms,##__VA_ARGS__)


//��ʼ��ʱ(ns)
typedef void      (*lptmr_time_start_us_t)  (void);
#define lptmr_time_start_us(...)                  ENTER_FUN_ADDR(lptmr_time_start_us,##__VA_ARGS__)


//��ȡ��ʱʱ��
typedef uint32_t  (*lptmr_time_get_us_t)    (void);
#define lptmr_time_get_us(...)                    ENTER_FUN_ADDR(lptmr_time_get_us,##__VA_ARGS__)


//�رռ�ʱ��
typedef void      (*lptmr_time_close_t)     ();
#define lptmr_time_close(...)                     ENTER_FUN_ADDR(lptmr_time_close,##__VA_ARGS__)



    //LPT  �����������                                 ************************************************
//�����������ʼ������
typedef void      (*lptmr_pulse_init_t)     (LPT0_ALTn, uint16_t count, LPT_CFG);
#define lptmr_pulse_init(...)                     ENTER_FUN_ADDR(lptmr_pulse_init,##__VA_ARGS__)


//��ȡ����ֵ
typedef uint16_t  (*lptmr_pulse_get_t)      (void);
#define lptmr_pulse_get(...)                      ENTER_FUN_ADDR(lptmr_pulse_get,##__VA_ARGS__)


//��ռ���ֵ
typedef void      (*lptmr_pulse_clean_t)    (void);
#define lptmr_pulse_clean(...)                    ENTER_FUN_ADDR(lptmr_pulse_clean,##__VA_ARGS__)




    //TPM  PWM���                                  ************************************************
//��ʼ��TPM��PWM���ܲ�����Ƶ�ʡ�ռ�ձȡ�����ͨ�����ռ�ձȡ�ͬһ��TPM����ͨ����PWMƵ����һ����
typedef int8_t    (*tpm_pwm_init_t)        (TPMn_e, TPM_CHn_e, uint32_t freq, float duty,PTXn_e pin,uint32_t core_khz);
#define tpm_pwm_init(tpn,ch,freq,duty,pin)                         ENTER_FUN_ADDR(tpm_pwm_init,tpn,ch,freq,duty,pin,core_clk_khz)


//����ͨ��ռ�ձ�,ռ�ձ�Ϊ duty%
typedef void      (*tpm_pwm_duty_t)        (TPMn_e, TPM_CHn_e,                float duty);
#define tpm_pwm_duty(...)                         ENTER_FUN_ADDR(tpm_pwm_duty,##__VA_ARGS__)


//����TPM��Ƶ�ʣ���Ƶ�ʺ���Ҫ��������ռ�ձȣ�
typedef int8_t    (*tpm_pwm_freq_t)        (TPMn_e,            uint32_t freq, uint32_t core_khz);
#define tpm_pwm_freq(tpn,freq)                         ENTER_FUN_ADDR(tpm_pwm_freq,tpn,freq,core_clk_khz)



    //TPM  ���벶׽                                   ************************************************
//���벶׽��ʼ��
typedef void      (*tpm_input_init_t)      (TPMn_e, TPM_CHn_e, TPM_Input_cfg cfg,TPM_PS_e ps,PTXn_e pin);
#define tpm_input_init(...)                       ENTER_FUN_ADDR(tpm_input_init,##__VA_ARGS__)


//���벶׽ģʽ�£���ȡ��׽�¼�����ʱ�ļ�����ֵ(�������β�׽֮��Ĳ�ֵ���ж�����Ƶ��)
typedef uint16_t  (*tpm_input_get_t)       (TPMn_e, TPM_CHn_e);
#define tpm_input_get(...)                        ENTER_FUN_ADDR(tpm_input_get,##__VA_ARGS__)


//��ռ�������ֵ
typedef void      (*tpm_input_clean_t)     (TPMn_e );
#define tpm_input_clean(...)                      ENTER_FUN_ADDR(tpm_input_clean,##__VA_ARGS__)



    //TPM  �������                                   ************************************************
//���������ʼ��
typedef void      (*tpm_pulse_init_t)      (TPMn_e tpmn,TPM_CLKIN_e clkin,TPM_PS_e ps,PTXn_e pin);
#define tpm_pulse_init(...)                       ENTER_FUN_ADDR(tpm_pulse_init,##__VA_ARGS__)


//��ȡ������
typedef uint16_t  (*tpm_pulse_get_t)       (TPMn_e tpmn);
#define tpm_pulse_get(...)                        ENTER_FUN_ADDR(tpm_pulse_get,##__VA_ARGS__)


//���������
typedef void      (*tpm_pulse_clean_t)     (TPMn_e tpmn);
#define tpm_pulse_clean(...)                      ENTER_FUN_ADDR(tpm_pulse_clean,##__VA_ARGS__)



    //FTM  PWM���                                  ************************************************
//��ʼ��FTM��PWM���ܲ�����Ƶ�ʡ�ռ�ձȡ�����ͨ�����ռ�ձȡ�ͬһ��FTM����ͨ����PWMƵ����һ���ģ���3��FTM(FX��4��)
typedef int8_t    (*ftm_pwm_init_t)        (FTMn_e, FTM_CHn_e, uint32_t freq, float duty,PTXn_e pin,uint32_t bus_khz);
#define ftm_pwm_init(ftm,ch,freq,duty,pin)                         ENTER_FUN_ADDR(ftm_pwm_init,ftm,ch,freq,duty,pin,bus_clk_khz)


//����ͨ��ռ�ձ�,ռ�ձ�Ϊ ��duty * ���ȣ� % ����� FTM_PRECISON ����Ϊ 1000 ��duty = 100 ����ռ�ձ� 100*0.1%=10%
typedef void      (*ftm_pwm_duty_t)        (FTMn_e, FTM_CHn_e,              float duty);
#define ftm_pwm_duty(...)                         ENTER_FUN_ADDR(ftm_pwm_duty,##__VA_ARGS__)


//����FTM��Ƶ�ʣ���Ƶ�ʺ���Ҫ��������ռ�ձȣ�
typedef int8_t    (*ftm_pwm_freq_t)        (FTMn_e,            uint32_t freq,uint32_t bus_khz);
#define ftm_pwm_freq(ftm,freq)                         ENTER_FUN_ADDR(ftm_pwm_freq,ftm,freq,bus_clk_khz)



    //FTM  ���벶׽                                   ************************************************
//���벶׽��ʼ������
typedef void      (*ftm_input_init_t)      (FTMn_e, FTM_CHn_e, FTM_Input_cfg,FTM_PS_e ps,PTXn_e pin);
#define ftm_input_init(...)                       ENTER_FUN_ADDR(ftm_input_init,##__VA_ARGS__)


//���벶׽ģʽ�£���ȡ��׽�¼�����ʱ�ļ�����ֵ(�������β�׽֮��Ĳ�ֵ���ж�����Ƶ��)
typedef uint16_t  (*ftm_input_get_t)       (FTMn_e, FTM_CHn_e);
#define ftm_input_get(...)                        ENTER_FUN_ADDR(ftm_input_get,##__VA_ARGS__)


//��ռ�������ֵ
typedef void      (*ftm_input_clean_t)     (FTMn_e );
#define ftm_input_clean(...)                      ENTER_FUN_ADDR(ftm_input_clean,##__VA_ARGS__)



    //FTM  ��������                                   ************************************************
//��ʼ��FTM ���������� ����
typedef void      (*ftm_quad_init_t)       (FTMn_e, FTM_PS_e ps,PTXn_e Apin,PTXn_e Bpin);
#define ftm_quad_init(...)                        ENTER_FUN_ADDR(ftm_quad_init,##__VA_ARGS__)


//��ȡFTM �������� ��������(������ʾ������)
typedef int16_t   (*ftm_quad_get_t)        (FTMn_e);
#define ftm_quad_get(...)                         ENTER_FUN_ADDR(ftm_quad_get,##__VA_ARGS__)


//�� FTM �������� ��������
typedef void      (*ftm_quad_clean_t)      (FTMn_e);
#define ftm_quad_clean(...)                       ENTER_FUN_ADDR(ftm_quad_clean,##__VA_ARGS__)



    //DAC ģ�����                                    ************************************************
//DACһ��ת����ʼ��
typedef void      (*dac_init_t)            (DACn_e);
#define dac_init(...)                             ENTER_FUN_ADDR(dac_init,##__VA_ARGS__)


//DACһ��ת������
typedef void      (*dac_out_t)             (DACn_e, uint16_t val);
#define dac_out(...)                              ENTER_FUN_ADDR(dac_out,##__VA_ARGS__)



    //LCD ��ʾ                                      ************************************************
typedef void      (*lcd_init_t)            (lcd_t * lcd,uint16_t rgb565);
#define lcd_init(...)                             ENTER_FUN_ADDR(lcd_init,glcd,##__VA_ARGS__)



//����
typedef void      (*lcd_point_t)           (lcd_t * lcd,Site_t,                            uint16_t rgb565);
#define lcd_point(...)                            ENTER_FUN_ADDR(lcd_point,glcd,##__VA_ARGS__)


//��һ�ѵ�
typedef void      (*lcd_points_t)          (lcd_t * lcd,Site_t *site,  uint32_t point_num, uint16_t rgb565);
#define lcd_points(...)                           ENTER_FUN(lcd_points,glcd,##__VA_ARGS__)



//������
typedef void      (*lcd_rectangle_t)       (lcd_t * lcd,Site_t,Size_t,                     uint16_t rgb565);
#define lcd_rectangle(...)                        ENTER_FUN_ADDR(lcd_rectangle,glcd,##__VA_ARGS__)


//��ʮ����
typedef void      (*lcd_cross_t)           (lcd_t * lcd,Site_t,uint16_t len,               uint16_t rgb565);
#define lcd_cross(...)                            ENTER_FUN_ADDR(lcd_cross,glcd,##__VA_ARGS__)


//����
typedef void      (*lcd_clear_t)           (lcd_t * lcd,uint16_t rgb565);
#define lcd_clear(...)                            ENTER_FUN_ADDR(lcd_clear,glcd,##__VA_ARGS__)




    //LCD Ӣ���ַ���������ʾ                               ************************************************
//��ʾӢ���ַ�
typedef void      (*lcd_char_6x12_t)       (lcd_t * lcd,Site_t site, uint8 ascii, uint16_t Color, uint16_t bkColor) ;
#define lcd_char_6x12(...)                        ENTER_FUN_ADDR(lcd_char_6x12,glcd,##__VA_ARGS__)


//��ʾӢ���ַ���
typedef void      (*lcd_str_6x12_t)        (lcd_t * lcd,Site_t site, uint8 *Str,  uint16_t Color, uint16_t bkColor);
#define lcd_str_6x12(...)                         ENTER_FUN_ADDR(lcd_str_6x12,glcd,##__VA_ARGS__)


//��ʾ�޷�������
typedef uint8_t   (*lcd_num_6x12_t)        (lcd_t * lcd,Site_t site, uint32_t num,uint16_t Color, uint16_t bkColor);
#define lcd_num_6x12(...)                         ENTER_FUN_ADDR(lcd_num_6x12,glcd,##__VA_ARGS__)


//��ʾ�з�������
typedef uint8_t   (*lcd_snum_6x12_t)       (lcd_t * lcd,Site_t site, int32 num,   uint16_t Color, uint16_t bkColor);
#define lcd_snum_6x12(...)                        ENTER_FUN_ADDR(lcd_snum_6x12,glcd,##__VA_ARGS__)


//��ʾ�޷�������(������������)
typedef void      (*lcd_num_bc_6x12_t)     (lcd_t * lcd,Site_t site, uint32 num, uint8_t max_num_bit,uint16 Color, uint16 bkColor);
#define lcd_num_bc_6x12(...)                      ENTER_FUN_ADDR(lcd_num_bc_6x12,glcd,##__VA_ARGS__)


//��ʾ�з�������(������������)
typedef void      (*lcd_snum_bc_6x12_t)    (lcd_t * lcd,Site_t site, uint32 num, uint8_t max_num_bit,uint16 Color, uint16 bkColor);
#define lcd_snum_bc_6x12(...)                     ENTER_FUN_ADDR(lcd_snum_bc_6x12,glcd,##__VA_ARGS__)




    //LCD ������ʾ                                    ************************************************
#if (USE_FOUNT_SIZE == 12)
//��ʾ�����ַ�
typedef void      (*lcd_char_ch_12x12_t)   (lcd_t * lcd,Site_t site, const uint8 *str, uint16_t Color, uint16_t bkColor);
//��ʾ�����ַ���
typedef void      (*lcd_str_ch_12x12_t)    (lcd_t * lcd,Site_t site, const uint8 *str, uint16_t Color, uint16_t bkColor);
//��ʾ����Ӣ�Ļ���ַ���
typedef void      (*lcd_str_ench_12x12_t)  (lcd_t * lcd,Site_t site, const uint8 *str, uint16_t Color, uint16_t bkColor);

#else
//��ʾ�����ַ�          ���� USE_FOUNT_SIZE Ϊ12�����һ����������Ҫд��
typedef void      (*lcd_char_ch_12x12_t)   (lcd_t * lcd,Site_t site, const uint8 *str, uint16_t Color, uint16_t bkColor,char * chinese_12x12);
//��ʾ�����ַ���        ���� USE_FOUNT_SIZE Ϊ12�����һ����������Ҫд��
typedef void      (*lcd_str_ch_12x12_t)    (lcd_t * lcd,Site_t site, const uint8 *str, uint16_t Color, uint16_t bkColor,char * chinese_12x12);
//��ʾ����Ӣ�Ļ���ַ��� ���� USE_FOUNT_SIZE Ϊ12�����һ����������Ҫд��
typedef void      (*lcd_str_ench_12x12_t)  (lcd_t * lcd,Site_t site, const uint8 *str, uint16_t Color, uint16_t bkColor,char * chinese_12x12);
#endif

#define lcd_char_ch_12x12(...)                    ENTER_FUN(lcd_char_ch_12x12,glcd,##__VA_ARGS__)
#define lcd_str_ch_12x12(...)                     ENTER_FUN(lcd_str_ch_12x12,glcd,##__VA_ARGS__)
#define lcd_str_ench_12x12(...)                   ENTER_FUN(lcd_str_ench_12x12,glcd,##__VA_ARGS__)



//��ʾӢ���ַ�
typedef void      (*lcd_char_8x16_t)       (lcd_t * lcd,Site_t site, uint8 ascii, uint16_t Color, uint16_t bkColor);
#define lcd_char_8x16(...)                        ENTER_FUN_ADDR(lcd_char_8x16,glcd,##__VA_ARGS__)


//��ʾӢ���ַ���
typedef void      (*lcd_str_8x16_t)        (lcd_t * lcd,Site_t site, uint8 *Str,  uint16_t Color, uint16_t bkColor);
#define lcd_str_8x16(...)                         ENTER_FUN_ADDR(lcd_str_8x16,glcd,##__VA_ARGS__)


//��ʾ�޷�������
typedef uint8_t   (*lcd_num_8x16_t)        (lcd_t * lcd,Site_t site, uint32_t num,uint16_t Color, uint16_t bkColor) ;
#define lcd_num_8x16(...)                         ENTER_FUN_ADDR(lcd_num_8x16,glcd,##__VA_ARGS__)


//��ʾ�з�������
typedef uint8_t   (*lcd_snum_8x16_t)       (lcd_t * lcd,Site_t site, int32 num,   uint16_t Color, uint16_t bkColor) ;
#define lcd_snum_8x16(...)                        ENTER_FUN_ADDR(lcd_snum_8x16,glcd,##__VA_ARGS__)


//��ʾ�޷�������(������������)
typedef void      (*lcd_num_bc_8x16_t)     (lcd_t * lcd,Site_t site, uint32 num, uint8_t max_num_bit,uint16 Color, uint16 bkColor);
#define lcd_num_bc_8x16(...)                      ENTER_FUN_ADDR(lcd_num_bc_8x16,glcd,##__VA_ARGS__)


//��ʾ�з�������(������������)
typedef void      (*lcd_snum_bc_8x16_t)    (lcd_t * lcd,Site_t site, uint32 num, uint8_t max_num_bit,uint16 Color, uint16 bkColor);
#define lcd_snum_bc_8x16(...)                     ENTER_FUN_ADDR(lcd_snum_bc_8x16,glcd,##__VA_ARGS__)





#if (USE_FOUNT_SIZE == 16)
//��ʾ�����ַ�
typedef void      (*lcd_char_ch_16x16_t)   (lcd_t * lcd,Site_t site, const uint8 *str, uint16_t Color, uint16_t bkColor);
//��ʾ�����ַ���
typedef void      (*lcd_str_ch_16x16_t)    (lcd_t * lcd,Site_t site, const uint8 *str, uint16_t Color, uint16_t bkColor);
//��ʾ����Ӣ�Ļ���ַ���
typedef void      (*lcd_str_ench_16x16_t)  (lcd_t * lcd,Site_t site, const uint8 *str, uint16_t Color, uint16_t bkColor);
#else
//��ʾ�����ַ�          ���� USE_FOUNT_SIZE Ϊ16�����һ����������Ҫд��
typedef void      (*lcd_char_ch_16x16_t)   (lcd_t * lcd,Site_t site, const uint8 *str, uint16_t Color, uint16_t bkColor,char * chinese_16x16);
//��ʾ�����ַ���        ���� USE_FOUNT_SIZE Ϊ16�����һ����������Ҫд��
typedef void      (*lcd_str_ch_16x16_t)    (lcd_t * lcd,Site_t site, const uint8 *str, uint16_t Color, uint16_t bkColor,char * chinese_16x16);
//��ʾ����Ӣ�Ļ���ַ��� ���� USE_FOUNT_SIZE Ϊ16�����һ����������Ҫд��
typedef void      (*lcd_str_ench_16x16_t)  (lcd_t * lcd,Site_t site, const uint8 *str, uint16_t Color, uint16_t bkColor,char * chinese_16x16);
#endif


#define lcd_char_ch_16x16(...)                    ENTER_FUN(lcd_char_ch_16x16,glcd,##__VA_ARGS__)
#define lcd_str_ch_16x16(...)                     ENTER_FUN(lcd_str_ch_16x16,glcd,##__VA_ARGS__)
#define lcd_str_ench_16x16(...)                   ENTER_FUN(lcd_str_ench_16x16,glcd,##__VA_ARGS__)



    //LCD ͼ����ʾ                                    ************************************************
//��ʾ��ֵ��ͼ��
typedef void      (*lcd_img_binary_t)      (lcd_t * lcd,Site_t site, Size_t size, uint8 *img,                uint16_t Color, uint16_t bkColor);
#define lcd_img_binary(...)                       ENTER_FUN_ADDR(lcd_img_binary,glcd,##__VA_ARGS__)


//��ʾ��ֵ��ͼ��(������)
typedef void      (*lcd_img_binary_z_t)    (lcd_t * lcd,Site_t site, Size_t size, uint8 *img, Size_t imgsize,uint16_t Color, uint16_t bkColor);
#define lcd_img_binary_z(...)                     ENTER_FUN_ADDR(lcd_img_binary_z,glcd,##__VA_ARGS__)


//��ʾ�Ҷ�ͼ��
typedef void      (*lcd_img_gray_t)        (lcd_t * lcd,Site_t site, Size_t size, uint8 *img);
#define lcd_img_gray(...)                         ENTER_FUN_ADDR(lcd_img_gray,glcd,##__VA_ARGS__)


//��ʾ�Ҷ�ͼ��(������)
typedef void      (*lcd_img_gray_z_t)      (lcd_t * lcd,Site_t site, Size_t size, uint8 *img, Size_t imgsize);
#define lcd_img_gray_z(...)                       ENTER_FUN_ADDR(lcd_img_gray_z,glcd,##__VA_ARGS__)


//��ɫ
typedef void      (*lcd_img_rgb565_t)      (lcd_t * lcd,Site_t site, Size_t size, uint8 *img) ;
#define lcd_img_rgb565(...)                       ENTER_FUN_ADDR(lcd_img_rgb565,glcd,##__VA_ARGS__)


//��ɫ(������)
typedef void      (*lcd_img_rgb565_z_t)    (lcd_t * lcd,Site_t site, Size_t size, uint8 *img, Size_t imgsize);
#define lcd_img_rgb565_z(...)                     ENTER_FUN_ADDR(lcd_img_rgb565_z,glcd,##__VA_ARGS__)



    //LCD ������ʾ                                    ************************************************
//������ʾ����������ɫ��maxval ���ֵ��ʾ������ֵ�������������ֵ����
typedef void      (*lcd_wave_t)            (lcd_t * lcd,Site_t site,Size_t size,uint8 *img,uint8 maxval,uint16_t Color ,uint16_t bkColor);
#define lcd_wave(...)                             ENTER_FUN_ADDR(lcd_wave,glcd,##__VA_ARGS__)


//������ʾ������������ɫ
typedef void      (*lcd_wave_display_t)    (lcd_t * lcd,Site_t site,Size_t size,uint8 *img,uint8 maxval,uint16_t Color);
#define lcd_wave_display(...)                     ENTER_FUN_ADDR(lcd_wave_display,glcd,##__VA_ARGS__)



static inline char   enter_init(void)
{
    while(  ( (uint16_t)BOOT_ADDR(flag)!=0x55A5)  ||  (uint16_t)BOOT_ADDR(ver)!=BOOT_VER  )
    {
        //����������ѭ��������UD�������ߣ����¸�������
        printf("\nBOOT�汾�����쳣����־λ:0x%x���汾�ţ�0x%x", (uint16_t)BOOT_ADDR(flag),(uint16_t)BOOT_ADDR(ver)) ;

    }

    while(  ( (uint16_t)IN_ADDR(flag)!=0x55A5)  ||  (uint16_t)IN_ADDR(ver)!=FWD_VER  )
    {
        //����������ѭ��������UD���أ�����EXT FWD
        printf("\nEXT FWD�汾�����쳣����־λ:0x%x���汾�ţ�0x%x", (uint16_t)IN_ADDR(flag),(uint16_t)IN_ADDR(ver)) ;
    }
    return 1;

}


#endif    //

#endif   //_ENTER_H_

