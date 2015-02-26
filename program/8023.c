#include "./output/8023.h"
void fun_delay(enum varENU_delaymodel par_model,ui par_value){
    ui loc_con=par_value;
    switch(par_model){
        case us:
            while(loc_con-->0){
                _nop_();
                _nop_();
            }
            return;
        case ms:
            while(loc_con-->0){
                uc loc_i, loc_j;
                _nop_();
                _nop_();
                loc_i=12;
                loc_j=168;
                do{
                    while(--loc_j);
                }while(--loc_i);
            }
            return;
        case s:
            while(loc_con-->0){
                uc loc_i, loc_j, loc_k;
                loc_i=46;
                loc_j=153;
                loc_k=245;
                do{
                    do{
                        while(--loc_k);
                    }while(--loc_j);
                }while(--loc_i);
            }
            return;
        default:return;
    }
}//��ʱ
void fun_timer0init(){
    AUXR&=0x7F;
    TMOD&=0xF0;
    TMOD|=0x01;
    TL0=0xB0;
    TH0=0x3C;
    TF0=0;
}//50���붨ʱ��0��ʼ��
void fun_timer1init(){
    AUXR&=0xBF;
    TMOD&=0x0F;
    TMOD|=0x10;
    TL1=0xE0;
    TH1=0xB1;
    TF1=0;
}//20���붨ʱ��1��ʼ��
void fun_timer0(){
    TL0=0xB0;
    TH0=0x3C;
    _nop_();
}//50���붨ʱ��0������
void fun_timer1(){
    TL1=0xE0;
    TH1=0xB1;
    _nop_();
}//20���붨ʱ��1������
void fun_wait(){
    while(in_start==1);
    fun_delay(ms,20);
    while(in_start==0);
    fun_delay(ms,256);
}//�ȴ�����
void fun_select(enum varENU_selectsensor par_model){
    if(par_model==ps58)
        out_switchselect=0;
    else if(par_model==ps912)
        out_switchselect=1;
}//������Ƭѡ
void fun_initialization(){
    CLK_DIV=0x00;//����Ƶ

    P0M1=0xff;//P0��������
    P0M0=0x00;//P0�������
    
    P1M1=0x00;//P1��0-1˫��2�ж����룬3-6���룬7���
    P1M0=0xfc;//P1��2-7���

    P2M1=0xf0;//P2��4-7����
    P2M0=0x0f;//P2��0-3���

    //PS_2=1;//��ץ�ɴ�������1 $?$
    //PS_11=1;//����λ��3��������1 $?$

    out_en1=1;//���1/3ʹ�� $?$
    out_en2=1;//���2/4ʹ�� $?$
    out_motorselect=1;//���ƬѡΪ1 $?$
    fun_delay(ms,1);//��ʱ1���� $?$
    out_motorselect=0;//���ƬѡΪ0 $?$
    //PS_5=PS_1;// $?$

    fun_pwminit();//PWM�ĳ�ʼ������
    fun_timer0init();//��ʼ����ʱ��0
    fun_timer1init();//��ʼ����ʱ��1
    in_start=1;//������1

    fun_wait();
}//��ʼ��
void fun_pwminit(){
    CCON=0x00;
    CH=0;
    CL=0;
    CMOD=0x00;
}//PWM��ʼ��
void fun_pwmr(ui par_value){
    CCAP0H=CCAP0L=par_value*2.5;//���������ռ�ձ�
    CCAPM0=0X42;//8λPWM��������ж�
    PCA_PWM0=0x00;
}//��·PWM���
void fun_pwml(ui par_value){
    CCAP1H=CCAP1L=par_value*2.5;//���������ռ�ձ�
    CCAPM1=0X42;//8λPWM��������ж�
    PCA_PWM1=0x00;
}//��·PWM���
void fun_startdj(enum varENU_motor par_model,char par_speed){
    if(par_speed==0)
        return;
    else if(par_speed>100)
        par_speed=100;
    else if(par_speed<-100)
        par_speed=-100;
    switch(par_model){
        case l:
            CR=1;
            if(par_speed>0){
                fun_pwml(par_speed);out_pwml=0;
            }
            else if(par_speed<0){
                fun_pwml(cabs(par_speed));out_pwml=1;
            }
            break;
        case r:
            CR=1;
            if(par_speed>0){
                fun_pwmr(par_speed);out_pwmr=0;
            }
            else if(par_speed<0){
                fun_pwmr(cabs(par_speed));out_pwmr=1;
            }
            break;
        case rl:
            CR=1;
            if(par_speed>0){
                fun_pwml(par_speed);out_pwml=0;
                fun_pwmr(par_speed);out_pwmr=0;
            }
            else if(par_speed<0){
                fun_pwml(cabs(par_speed));out_pwml=1;
                fun_pwmr(cabs(par_speed));out_pwmr=1;
            }
            break;
        case dj1:
            out_motorselect=1;
            if(par_speed>0)
                out_dir1=1;
            else if(par_speed<0)
                out_dir1=0;
            out_en1=0;
            break;
        case dj2:
            out_motorselect=1;
            if(par_speed>0)
                out_dir2=1;
            else if(par_speed<0)
                out_dir2=0;
            out_en2=0;
            break;
        case dj3:
            out_motorselect=0;
            if(par_speed>0)
                out_dir1=0;
            else if(par_speed<0)
                out_dir1=1;
            out_en1=0;
            break;
        case dj4:
            out_motorselect=0;
            if(par_speed>0)
                out_dir2=1;
            else if(par_speed<0)
                out_dir2=0;
            out_en2=0;
            break;
        default:
            break;
    }
}//�������
void stop(enum varENU_motor par_model){
    switch(par_model){
        case l:
            fun_pwml(0);out_pwml=0;break;
        case r:
            fun_pwmr(0);out_pwmr=0;break;
        case rl:
            CR=0;fun_pwmr(0);out_pwmr=0;fun_pwml(0);out_pwml=0;break;
        case dj1:
            out_motorselect=1;out_dir1=0;out_en1=1;break;
        case dj2:
            out_motorselect=1;out_dir2=0;out_en2=1;break;
        case dj3:
            out_motorselect=0;out_dir1=0;out_en1=1;break;
        case dj4:
            out_motorselect=0;out_dir2=0;out_en2=1;break;
        default:
            break;
    }
}//ֹͣ���

