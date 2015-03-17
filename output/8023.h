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
    #define def_timer0start TR0=1;//��ʱ��0����
    #define def_timer0stop TR0=0;//��ʱ��0�ر�
    #define def_timer1start TR1=1;//��ʱ��1����
    #define def_timer1stop TR1=0;//��ʱ��1�ر�
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
    #define def_stop fun_stop(mot_dj1);\
                     fun_stop(mot_dj2);\
                     fun_stop(mot_dj3);\
                     fun_stop(mot_dj4);\
                     fun_stop(mot_rl);\
                     EA=0;\
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
    #define MSG(par_value) printf("%s \n",par_value);
    #define OUT(par_value) printf("%d \n",par_value);
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
    /*
        sbit DIR_R=P1^2;//PWMR������ת����λ��1������
        sbit DIR_L=P1^5;//PWML������ת����λ��1������
        sbit MOT_DIR1=P2^0;//���1/3����
        sbit MOT_EN1=P2^1;//���1/3ʹ��
        sbit MOT_DIR2=P2^2;//���2/4����
        sbit MOT_EN2=P2^3;//���2/4ʹ��
        sbit start_=P3^2;//��������
        sbit SER_BS=P1^6;//�ӽ�����Ƭѡ
        sbit MOT_BS=P1^7;//������Ƭѡ
        sbit LAMP=P3^7;//�������

        sbit PS_1=P3^4;
        sbit PS_2=P3^3;
        sbit PS_3=P3^5;
        sbit PS_4=P3^6;
        bit PS_5;
        bit PS_6;
        bit PS_7; 
        bit PS_8;
        sbit PS_9 =P2^4;
        sbit PS_10=P2^5;
        sbit PS_11=P2^6; 
        sbit PS_12=P2^7;
    */
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
        mot_dj1,
        mot_dj2,
        mot_dj3,
        mot_dj4
    };//���ѡ��
    enum varENU_dir{
        dir_up,
        dir_down,
        dir_left,
        dir_right
    };//��ͷ����
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
        tur_l,
        tur_r
    };//��ת״̬
    struct str_state{
        char x;//X����
        char y;//Y����
        enum varENU_dir ctfx;//��ͷ����
        enum varENU_han szzt;//��ץ״̬
        enum varENU_sjp sjwz;//����λ��
        enum varENU_tra pywz;//ƽ��λ��
        enum varENU_dir hzfx;//��ת����
    };
    struct str_parameter{
        ui mlinerqd;//Ĭ��������Ѳ������ʱ��Ϊ500����
        ui mlineqc;//Ĭ��������Ѳ��ǰ��ʱ��Ϊ500����

        ui sj1bzw;
        ui sj1zjw;

        ui py1qkq;
        ui py1kqz;
        ui py1zkh;
        ui py1khh;
        ui py1qz;
        ui py1zh;
        ui py1kqkh;
        ui py1qkh;
        ui py1kqh;
    };//����

    extern xdata struct str_state str_begin,str_now,str_next;//�ֱ�Ϊ:��ʼ״̬/��ǰ״̬/Ŀ��״̬
    extern xdata struct str_parameter str_cod;
    extern ui var_timer0;
/*---------------------------------------------------------------��������-----*/
    extern void fun_delay(ui par_value,enum varENU_del par_model);//��ʱ
    extern void fun_timer0init();//1���붨ʱ��0��ʼ��
    extern void fun_timer1init();//20���붨ʱ��1��ʼ��
    extern void fun_timer0();//1���붨ʱ��0������
    extern void fun_timer1();//20���붨ʱ��1������
    extern void fun_wait();//�ȴ�����
    extern void fun_select(enum varENU_sel par_model);//������Ƭѡ
    extern void fun_initialization();//��ʼ������
    extern void fun_pwminit();//PWM��ʼ��
    extern void fun_pwmr(uc par_value);//��·PWM���
    extern void fun_pwml(uc par_value);//��·PWM���
    extern void fun_startdj(enum varENU_mot par_model,char par_speed);//�������
    extern void fun_stop(enum varENU_mot par_model);//ֹͣ���
    extern void fun_sz1(enum varENU_han par_model);//��ץ�����˶�
    extern void fun_sj1(enum varENU_sjp par_model);//���������˶�
    extern void fun_py1(enum varENU_tra par_model);//ƽ�Ƶ����˶�
    extern void fun_hz1(enum varENU_dir par_model);//��ת�����˶�
    extern void fun_sj2(char par_value);//������һ����д,�������ץ��
    extern void fun_pyhz2(enum varENU_tra par_py,enum varENU_dir par_hz);//ƽ�ƻ�תͬ���˶�,�����������
    extern void fun_planezt(uc par_model);
    extern void fun_mptline(uc par_num,uc par_sd,enum varENU_dir);//��������ͨѲ��
    extern void fun_stope2prom();//ֹͣEEPROM����
    extern uc fun_reade2prom(ui par_add);//��ȡEEPROM����
    extern void fun_writee2prom(ui par_add,uc par_dat);//д��������EEPROM
    extern void fun_cleane2prom(ui par_add);//���EEPROM����
    extern void fun_calibration();//�Զ�У׼����
    extern void fun_port();//���ڳ�ʼ��
    extern void fun_zhuajian(uc par_01,uc par_02,uc par_03,uc par_04,//�Զ�ץ��
                             uc par_41,uc par_42,uc par_43,uc par_44,
                             uc par_31,uc par_32,uc par_33,uc par_34,
                             uc par_71,uc par_72,uc par_73,uc par_74);
    extern uc fun_min(uc par_num,...);//����Сֵ
/*---------------------------------------------------------------������־-----*/
#endif