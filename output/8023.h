#ifndef __8023_H__
#define __8023_H__
/*-----------------------------------------------------------����ģʽѡ��-----*/
//    #define Debug ok
/*-------------------------------------------------------------ͷ�ļ�����-----*/
    #include "STC12c5a60s2.h"   //��Ƭ��ͷ�ļ�
    #include "intrins.h"        //_nop_��ѭ��λ��
    #include "math.h"           //��ѧ����
    #include "string.h"         //�ַ���
    #include "stdio.h"          //���ڵ�Ϸ
    #include "stdarg.h"         //�ɱ����
/*----------------------------------------------------------define �궨��-----*/
    #define def_timer0start TR0=1;  //��ʱ��0����
    #define def_timer0stop TR0=0;   //��ʱ��0�ر�
    #define def_timer1start TR1=1;  //��ʱ��1����
    #define def_timer1stop TR1=0;   //��ʱ��1�ر�
    #define def_end 0xFF            //��ȷ��Ԫ�ؽ�����־λ
    #define def_select(par_model) out_switchselect=par_model==sel_58?0:1;//������Ƭѡ
/*-------------------------------------------------------------�򻯺궨��-----*/
    #define D(par_ms) fun_delay(par_ms,del_ms);
    #define J fun_sz1(han_j);
    #define S fun_sz1(han_s);
    #define WZ1 fun_sj1(sjp_1);
    #define WZ2 fun_sj1(sjp_2);
    #define WZ3 fun_sj1(sjp_3);
    #define WZ4 fun_sj1(sjp_4);
    #define WZ5 fun_sj1(sjp_5);
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
    sbit in_start=P3^2; //��������(start_)
    sbit in_ls1=P0^7;   //1�Ŵ�����(�������,�²ഫ������,���źŵ͵�ƽ)
    sbit in_ls2=P0^6;   //2�Ŵ�����
    sbit in_ls3=P0^5;   //3�Ŵ�����
    sbit in_ls4=P0^4;   //4�Ŵ�����
    sbit in_ls5=P0^3;   //5�Ŵ�����
    sbit in_ls6=P0^2;   //6�Ŵ�����
    sbit in_ls7=P0^1;   //7�Ŵ�����
    sbit in_ls8=P0^0;   //8�Ŵ�����(�����Ҳ�,�ϲഫ������)

    sbit in_j=P3^4;     //��ץ��������
    sbit in_s=P3^3;     //��ץ�ɴ�����
    sbit in_qpy=P3^5;   //ƽ��ǰƽ�ƴ�����
    sbit in_hpy=P3^6;   //ƽ�ƺ�ƽ�ƴ�����

    sbit in_wz1=P2^4;   //����λ��1������(����λ)
    sbit in_wz2=P2^5;   //����λ��2������
    sbit in_wz3=P2^6;   //����λ��3������
    sbit in_wz4=P2^7;   //����λ��4������

    sbit in_wz5=P2^4;   //����λ��5������(����λ)
    sbit in_hz=P2^5;    //��ת������
/*----------------------------------------------------------------Out Put-----*/
    sbit out_pwmr=P1^2;         //PWMR������ת����λ,1������(DIR_R)
    sbit out_pwml=P1^5;         //PWML������ת����λ,1������(DIR_L)
    sbit out_dir1=P2^0;         //���1/3����(MOT_DIR1)
    sbit out_en1=P2^1;          //���1/3ʹ��(MOT_EN1)
    sbit out_dir2=P2^2;         //���2/4����(MOT_DIR2)
    sbit out_en2=P2^3;          //���2/4ʹ��(MOT_EN2)
    sbit out_switchselect=P1^6; //�ӽ�����Ƭѡ(SER_BS)
    sbit out_motorselect=P1^7;  //������Ƭѡ(MOT_BS)
    sbit out_lamp=P3^7;         //�������(LAMP)(�͵�ƽ��)
/*---------------------------------------------------------------��������-----*/
    enum varENU_tf{
        tf_null=10,
        tf_ture=11,
        tf_false=12
    };//�ж��õ�,��,�Ժʹ�
    enum varENU_del{
        del_us=20,
        del_ms=21,
        del_s=22
    };//��ʱģʽѡ��
    enum varENU_sel{
        sel_58=30,
        sel_912=31
    };//������Ƭѡ
    enum varENU_mot{
        mot_l=40,
        mot_r=41,
        mot_rl=42,
        mot_sz=43,   //���1
        mot_py=44,   //���2
        mot_sj=45,   //���3
        mot_hz=46,   //���4
        mot_pyhz=47  //ƽ�ƻ�תͬ���˶�
    };//���ѡ��
    enum varENU_dir{
        dir_up=50,
        dir_down=51,
        dir_left=52,
        dir_right=53
    };//����
    enum varENU_tra{
        tra_q=60,//û�е����һ��
        tra_kq=61,
        tra_z=62,
        tra_kh=63,
        tra_h=64//�е����һ��
    };//ƽ��λ��
    enum varENU_sjp{
        sjp_1=70,
        sjp_12=71,
        sjp_2=72,
        sjp_23=73,
        sjp_3=74,
        sjp_34=75,
        sjp_4=76,
        sjp_45=77,
        sjp_5=78
    };//����λ��
    enum varENU_han{
        han_j=80,
        han_s=81
    };//��ץ״̬
    enum varENU_tur{
        tur_l90=90,
        tur_r90=91,
        tur_l180=92,
        tur_r180=93
    };//ת��ģʽ
    enum varENU_tfl{
        tfl_line=100,    //Ѳ��
        tfl_cache=101,   //ǰ��
        tfl_turn=102,    //ת��
        tfl_start=103,   //�����ٵ�ǰ��
        tfl_end=104      //�����ٵ�ǰ��
    };//��ʱ��Ѳ��ִ�ж���

    struct str_state{
        char x;                 //X����
        char y;                 //Y����
        char szsd;              //��ץ�ٶ�
        char pysd;              //ƽ���ٶ�
        char sjsd;              //�����ٶ�
        char hzsd;              //��ת�ٶ�
        char leftsd;            //���ֵ���ٶ�
        char rightsd;           //���ֵ���ٶ�
        enum varENU_dir ctfx;   //��ͷ����
        enum varENU_han szzt;   //��ץ״̬
        enum varENU_sjp sjwz;   //����λ��
        enum varENU_tra pywz;   //ƽ��λ��
        enum varENU_dir hzfx;   //��ת����
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
        ui py1khkq;  //fun_py1���󵽿�ǰ��ʱ
        ui py1qkh;   //fun_py1ǰ��������ʱ
        ui py1kqh;   //fun_py1��ǰ������ʱ

        ui hz1bz;    //fun_hz1��׼λ��ʱ

        ui turn90;   //90��ת��������ʱ
        ui turn180;  //180��ת��������ʱ
    };//����
    struct str_timerfolline{
        char step[64];      //�����������
        pc run;             //�������еĲ���(ָ��)
        char gospeed;       //��Ѳ�����ٶ�
        char turnspeed;     //ת�������ٶ�
        char cachespeed;    //ǰ���ٶ�
        char doing;         //�����ƶ���־λ
        char online;        //���߱�־λ
        ul delay;           //��ʱ����
    };//��ʱ���ƶ�
    struct str_zdzj{
        uc jx[8][5];        //����:8��ץ����(�����ϵ�����0-3,�����ϵ�����4-7);5���߶�(0-5),���Ͽ�λΪ0,���ϵ���1-4,����Ϊ5
    };//�Զ�ץ��
    extern xdata struct str_state str_begin,str_now,str_next;   //�ֱ�Ϊ:��ʼ״̬/��ǰ״̬/Ŀ��״̬
    extern xdata struct str_parameter str_cod;                  //һЩ�̶��Ĳ���,һ�㱣��Ĭ�ϼ���
    extern xdata struct str_timerfolline str_tfl;               //��ʱ��Ѳ��
    extern ul var_timer0;                                       //timer0���뼶��ʱ������λ
/*---------------------------------------------------------------��������-----*/
    extern void fun_delay(ui par_value,enum varENU_del par_model); //��ʱ
    extern void fun_timer0init();//1���붨ʱ��0��ʼ��
    extern void fun_timer1init();//20���붨ʱ��1��ʼ��
    extern void fun_timer0();//1���붨ʱ��0������
    extern void fun_timer1();//20���붨ʱ��1������
    extern void fun_wait();//�ȴ�����
    extern void fun_pwminit();//PWM��ʼ��
    extern void fun_pwmr(uc par_value);//��·PWM���
    extern void fun_pwml(uc par_value);//��·PWM���
    extern void fun_motors(enum varENU_mot par_model,char par_speed);//�������������
    extern void fun_motorsrl(enum varENU_mot par_model,char par_speed);//��ʱ������������
    extern void fun_sz1(enum varENU_han par_model);//��ץ�����˶�
    extern void fun_sj1(enum varENU_sjp par_model);//���������˶�
    extern void fun_py1(enum varENU_tra par_model);//ƽ�Ƶ����˶�
    extern void fun_hz1(enum varENU_dir par_model);//��ת�����˶�
    extern void fun_pyhz2(enum varENU_tra par_pymodel,enum varENU_dir par_hzmodel);//ƽ�ƻ�תͬ���˶�
    extern void fun_jtjp();//��̬��ƫ
    extern void fun_timermove();//��ʱ���ƶ�
    extern void fun_folline(uc par_con,uc par_speed);//������Ѳ��
    extern void fun_turn(enum varENU_tur par_model,uc par_speed);//������ת��
    extern void fun_qc(uc par_time,uc par_speed);//������ǰ��
    extern void fun_stope2prom();//ֹͣEEPROM����
    extern uc   fun_reade2prom(ui par_add);//��ȡEEPROM����
    extern void fun_writee2prom(ui par_add,uc par_dat);//д��������EEPROM
    extern void fun_cleane2prom(ui par_add);//���EEPROM����
    extern void fun_calibration();//�Զ�У׼����
    extern void fun_port();//���ڳ�ʼ��
    extern void fun_test();//����
    extern uc   fun_min(uc par_num,...);//����Сֵ
    extern void fun_coordinate();//�Զ�Ѳ��֮����
    extern void fun_zdzj(ul par_che,ul par_tai);//�Զ�ץ��
    extern void fun_zjzt(uc par_motor,uc par_model);//ץ��״̬
    extern void fun_najian(uc par_now,uc par_next,char par_high[8],uc par_data[8][5]);//�ü�(����Զ�ץ��ʹ��)
    extern void fun_zhuajian();//����ʼ���ߵ�ץ����
    extern void fun_back();//��ץ�����ص���ʼ��
    extern void fun_start(char par_x,char par_y,enum varENU_dir par_ctfx,enum varENU_han par_szzt,enum varENU_sjp par_sjwz,enum varENU_tra par_pywz,enum varENU_dir par_hzfx);//��ʼ������
    extern void fun_stop();//��������
/*---------------------------------------------------------------������־-----*/
#endif