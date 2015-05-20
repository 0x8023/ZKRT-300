#ifndef __8023_H__
#define __8023_H__
/*-------------------------------------------------------------ͷ�ļ�����-----*/
    #include "STC12c5a60s2.h"//��Ƭ��ͷ�ļ�
    #include "intrins.h"//_nop_��ѭ��λ��
    #include "math.h"//��ѧ����
    #include "string.h"//�ַ���
    #include "stdio.h"//���ڵ�Ϸ
    #include "stdarg.h"//�ɱ����
/*----------------------------------------------------------define �궨��-----*/
    #define def_timer0start TR0=1;  //��ʱ��0����
    #define def_timer0stop TR0=0;   //��ʱ��0�ر�
    #define def_timer1start TR1=1;  //��ʱ��1����
    #define def_timer1stop TR1=0;   //��ʱ��1�ر�
    #define def_end 0xFF         //��ȷ��Ԫ�ؽ�����־λ
    #define def_speed(par_model) str_tfl.speed=par_model;//�����߶��ٶ�
    #define def_select(par_model) out_switchselect=par_model==sel_58?0:1;//������Ƭѡ
    #define def_start(par_x,par_y,par_ctfx,par_szzt,par_sjwz,par_pywz,par_hzfx) \
    /*��ʼ��*/        fun_initialization();\
    /*X����*/         str_begin.x=par_x;\
    /*Y����*/         str_begin.y=par_y;\
    /*��ͷ����*/      str_begin.ctfx=par_ctfx;\
    /*��ץ״̬*/      str_begin.szzt=par_szzt;\
    /*����λ��*/      str_begin.sjwz=par_sjwz;\
    /*ƽ��λ��*/      str_begin.pywz=par_pywz;\
    /*��ת����*/      str_begin.hzfx=par_hzfx;\
                      MSG("Ready!")
    #define def_stop EA=0;\
                     str_tfl.speed=0;\
                     fun_motors(mot_szdj,0);\
                     fun_motors(mot_pydj,0);\
                     fun_motors(mot_sjdj,0);\
                     fun_motors(mot_hzdj,0);\
                     fun_motors(mot_rl,0);\
                     while(1);
/*-------------------------------------------------------------�򻯺궨��-----*/
    #define D(par_ms) fun_delay(par_ms,del_ms);
    #define J fun_sz1(han_j);
    #define S fun_sz1(han_s);
    #define WZ1 fun_sj1(sjp_wz1);
    #define WZ2 fun_sj1(sjp_wz2);
    #define WZ3 fun_sj1(sjp_wz3);
    #define WZ4 fun_sj1(sjp_wz4);
    #define WZ5 fun_sj1(sjp_wz5);
    #define MSG(par_value) printf("%s\n",par_value);
    #define OUT(par_value) printf("%d\n",par_value);
/*-----------------------------------------------------------��������˵��-----*/
    typedef unsigned int ui;       //unsigned int --> ui
    typedef unsigned char uc;  //unsigned char uc --> uc
    typedef unsigned int* pui;     //unsigned int --> pui
    typedef unsigned char* puc;   //unsigned char --> puc
    typedef int* pi;                       //int* --> pi
    typedef char* pc;                     //char* --> pc
    typedef unsigned long ul;     //unsigned long --> ul
/*-----------------------------------------------------------------In Put-----*/
    sbit in_start=P3^2;//��������(start_)
    sbit in_ls1=P0^7;//1�Ŵ�����(�������,�²ഫ������,���źŵ͵�ƽ)
    sbit in_ls2=P0^6;//2�Ŵ�����
    sbit in_ls3=P0^5;//3�Ŵ�����
    sbit in_ls4=P0^4;//4�Ŵ�����
    sbit in_ls5=P0^3;//5�Ŵ�����
    sbit in_ls6=P0^2;//6�Ŵ�����
    sbit in_ls7=P0^1;//7�Ŵ�����
    sbit in_ls8=P0^0;//8�Ŵ�����(�����Ҳ�,�ϲഫ������)

    sbit in_j=P3^4;//��ץ��������
    sbit in_s=P3^3;//��ץ�ɴ�����
    sbit in_qpy=P3^5;//ƽ��ǰƽ�ƴ�����
    sbit in_hpy=P3^6;//ƽ�ƺ�ƽ�ƴ�����

    sbit in_wz1=P2^4;//����λ��1������(����λ)
    sbit in_wz2=P2^5;//����λ��2������
    sbit in_wz3=P2^6;//����λ��3������
    sbit in_wz4=P2^7;//����λ��4������

    sbit in_wz5=P2^4;//����λ��5������(����λ)
    sbit in_hz=P2^5;//��ת������
/*----------------------------------------------------------------Out Put-----*/
    sbit out_pwmr=P1^2;//PWMR������ת����λ��1������(DIR_R)
    sbit out_pwml=P1^5;//PWML������ת����λ��1������(DIR_L)
    sbit out_dir1=P2^0;//���1/3����(MOT_DIR1)
    sbit out_en1=P2^1;//���1/3ʹ��(MOT_EN1)
    sbit out_dir2=P2^2;//���2/4����(MOT_DIR2)
    sbit out_en2=P2^3;//���2/4ʹ��(MOT_EN2)
    sbit out_switchselect=P1^6;//�ӽ�����Ƭѡ(SER_BS)
    sbit out_motorselect=P1^7;//������Ƭѡ(MOT_BS)
    sbit out_lamp=P3^7;//�������(LAMP)(�͵�ƽ��)
/*---------------------------------------------------------------��������-----*/
    enum varENU_del{
        del_us,
        del_ms,
        del_s
    };//��ʱģʽѡ��
    enum varENU_sel{
        sel_58,
        sel_912
    };//������Ƭѡ
    enum varENU_mot{
        mot_l,
        mot_r,
        mot_rl,
        mot_szdj,//���1
        mot_pydj,//���2
        mot_sjdj,//���3
        mot_hzdj//���4
    };//���ѡ��
    enum varENU_dir{
        dir_up,
        dir_down,
        dir_left,
        dir_right
    };//����
    enum varENU_tra{
        tra_q,//û�е����һ��
        tra_kq,
        tra_z,
        tra_kh,
        tra_h//�е����һ��
    };//ƽ��λ��
    enum varENU_sjp{
        sjp_wz1,
        sjp_wz12,
        sjp_wz2,
        sjp_wz23,
        sjp_wz3,
        sjp_wz34,
        sjp_wz4,
        sjp_wz45,
        sjp_wz5
    };//����λ��
    enum varENU_han{
        han_j,
        han_s
    };//��ץ״̬
    enum varENU_tur{
        tur_l90,
        tur_r90,
        tur_l180,
        tur_r180
    };//ת��ģʽ
    enum varENU_tfl{
        tfl_line,
        tfl_cache,
        tfl_turn
    };//ѡ��ִ�еĶ���
    enum varENU_tf{
        tf_null,
        tf_ture,
        tf_false
    };//�ж��õ�,��,�Ժʹ�
    struct str_state{
        char x;//X����
        char y;//Y����
        char szsd;//��ץ�ٶ�
        char pysd;//ƽ���ٶ�
        char sjsd;//�����ٶ�
        char hzsd;//��ת�ٶ�
        char leftsd;//���ֵ���ٶ�
        char rightsd;//���ֵ���ٶ�
        enum varENU_dir ctfx;//��ͷ����
        enum varENU_han szzt;//��ץ״̬
        enum varENU_sjp sjwz;//����λ��
        enum varENU_tra pywz;//ƽ��λ��
        enum varENU_dir hzfx;//��ת����
    };
    struct str_parameter{
        ui mlinerqd; //Ĭ��������Ѳ������ʱ��Ϊ500����
        ui mlineqc;  //Ĭ��������Ѳ��ǰ��ʱ��Ϊ500����

        ui sj1bzw;   //������׼λ��ʱ
        ui sj1zjw;   //�����м�λ��ʱ

        uc py1bz;    //fun_py1��׼λ��ʱ
        ui py1qkq;   //fun_py1ǰ����ǰ��ʱ����
        ui py1kqz;   //fun_py1��ǰ���м���ʱ
        ui py1zkh;   //fun_py1�м䵽������ʱ
        ui py1khh;   //fun_py1���󵽺���ʱ
        ui py1qz;    //fun_py1ǰ���м���ʱ
        ui py1zh;    //fun_py1�м䵽����ʱ
        ui py1kqkh;  //fun_py1��ǰ��������ʱ
        ui py1qkh;   //fun_py1ǰ��������ʱ
        ui py1kqh;   //fun_py1��ǰ������ʱ

        ui hz1bz;    //fun_hz1��׼λ��ʱ

        ui turn90;   //90��ת��������ʱ
        ui turn180;  //180��ת��������ʱ
    };//����
    struct str_timerfolline{
        char step[32];
        pc run;
        char gospeed;
        char turnspeed;
        char doing;
        uc online;
        ul delay;
    };//��ʱ���ƶ�
    extern xdata struct str_state str_begin,str_now,str_next;//�ֱ�Ϊ:��ʼ״̬/��ǰ״̬/Ŀ��״̬
    extern xdata struct str_parameter str_cod;//һЩ�̶��Ĳ���,һ�㱣��Ĭ�ϼ���
    extern xdata struct str_timerfolline str_tfl;//һЩ�̶��Ĳ���,һ�㱣��Ĭ�ϼ���
    extern ul var_timer0;//timer0���뼶��ʱ������λ
/*---------------------------------------------------------------��������-----*/
    extern void fun_delay(ui par_value,enum varENU_del par_model);//��ʱ
    extern void fun_timer0init();//1���붨ʱ��0��ʼ��
    extern void fun_timer1init();//20���붨ʱ��1��ʼ��
    extern void fun_timer0();//1���붨ʱ��0������
    extern void fun_timer1();//20���붨ʱ��1������
    extern void fun_wait();//�ȴ�����
    extern void fun_initialization();//��ʼ������
    extern void fun_pwminit();//PWM��ʼ��
    extern void fun_pwmr(uc par_value);//��·PWM���
    extern void fun_pwml(uc par_value);//��·PWM���
    extern void fun_motors(enum varENU_mot par_model,char par_speed);//�������
    extern void fun_sz1(enum varENU_han par_model);//��ץ�����˶�
    extern void fun_sj1(enum varENU_sjp par_model);//���������˶�
    extern void fun_py1(enum varENU_tra par_model);//ƽ�Ƶ����˶�
    extern void fun_hz1(enum varENU_dir par_model);//��ת�����˶�
    extern void fun_dtjp();//��̬��ƫ
    extern void fun_jtjp();//��̬��ƫ
    extern void fun_timermove();//��ʱ���ƶ�
    extern void fun_stope2prom();//ֹͣEEPROM����
    extern uc fun_reade2prom(ui par_add);//��ȡEEPROM����
    extern void fun_writee2prom(ui par_add,uc par_dat);//д��������EEPROM
    extern void fun_cleane2prom(ui par_add);//���EEPROM����
    extern void fun_calibration();//�Զ�У׼����
    extern void fun_port();//���ڳ�ʼ��
    extern void fun_test();//����
    extern uc fun_min(uc par_num,...);//����Сֵ

/*---------------------------------------------------------------������־-----*/
#endif