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
    #define def_start fun_initialization();//��ʼ��
    // #define j 0//��צ�н�
    // #define s 1//��צ�ɿ�   

    // #define qpy 0//��צǰƽ�� 
    // #define hpy 1//��צ��ƽ��
    
    // #define xs 0//������
    // #define xx 1//���½�

    // #define qhz 0//ǰ��ת 
    // #define hhz 1//���ת

    // #define f 0//��������ת
    // #define b 1//��������ת

    // #define up 25
    // #define down 26
    // #define left 27
    // #define right 28
    // #define home 29//�ؼ�
    // #define start 30//��ʼ��
    // #define tz 31//ץȡ��λ��̨��
/*-----------------------------------------------------------��������˵��-----*/
    typedef unsigned int ui;       //unsigned int --> ui
    typedef unsigned char uc;  //unsigned char uc --> uc
//    typedef unsigned int* pui;     //unsigned int --> pui
 //   typedef unsigned char* puc;   //unsigned char --> puc
//    typedef int* pi;                       //int* --> pi
 //   typedef char* pc;                     //char* --> pc
//    typedef unsigned long ul;     //unsigned long --> ul
/*-----------------------------------------------------------------In Put-----*/
    sbit in_start=P3^2;//��������(start_)
    sbit in_ls1=P0^0;//1�Ŵ�����(��������)
    sbit in_ls2=P0^1;//2�Ŵ�����
    sbit in_ls3=P0^2;//3�Ŵ�����
    sbit in_ls4=P0^3;//4�Ŵ�����
    sbit in_ls5=P0^4;//5�Ŵ�����
    sbit in_ls6=P0^5;//6�Ŵ�����
    sbit in_ls7=P0^6;//7�Ŵ�����
    sbit in_ls8=P0^7;//8�Ŵ�����(��������)

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
    sbit out_lamp=P3^7;//�������(LAMP)
/*---------------------------------------------------------------��������-----*/
    xdata enum varENU_delaymodel{us,ms,s};//��ʱģʽѡ��
    xdata enum varENU_selectsensor{ps58,ps912};//������Ƭѡ
    xdata enum varENU_motor{l,r,rl,dj1,dj2,dj3,dj4};//���ѡ��
    xdata enum varENU_direction{up,down,left,right};//��ͷ����
    xdata enum varENU_translationplace{q,kq,zj,kh,h};//ƽ��λ��
    xdata enum varENU_sjplace{wz1,wz12,wz2,wz23,wz3,wz34,wz4,wz45,wz5};//����λ��

    xdata struct str_state{
        char str_x;//X����
        char str_y;//Y����
        enum varENU_direction str_ctfx;//��ͷ����
        enum varENU_sjplace str_sjwz;//����λ��
        enum varENU_translationplace str_pywz;//ƽ��λ��

    }begin,now,next;
/*---------------------------------------------------------------��������-----*/
    void fun_delay(enum varENU_delaymodel par_model,ui par_value);//��ʱ
    void fun_timer0init();//50���붨ʱ��0��ʼ��
    void fun_timer1init();//20���붨ʱ��1��ʼ��
    void fun_timer0();//50���붨ʱ��0������
    void fun_timer1();//20���붨ʱ��1������
    void fun_wait();//�ȴ�����
    void fun_select(enum varENU_selectsensor par_model);//������Ƭѡ
    void fun_initialization();//��ʼ������
    void fun_pwminit();//PWM��ʼ��
    void fun_pwmr(ui par_value);//��·PWM���
    void fun_pwml(ui par_value);//��·PWM���
    void fun_startdj(enum varENU_motor par_model,char par_speed);//�������
    void stop(enum varENU_motor par_model);//ֹͣ���
/*---------------------------------------------------------------������־-----*/