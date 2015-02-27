#include "./output/8023.h"
xdata struct str_state str_begin,str_now,str_next;//�ֱ�Ϊ:��ʼ״̬/��ǰ״̬/Ŀ��״̬
void fun_delay(ui par_value,enum varENU_del par_model){
    ui loc_con=par_value;
    switch(par_model){
        case del_us:
            while(loc_con-->0){
                _nop_();
                _nop_();
            }
            return;
        case del_ms:
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
        case del_s:
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
    fun_delay(20,del_ms);
    while(in_start==0);
    fun_delay(256,del_ms);
}//�ȴ�����
void fun_select(enum varENU_sel par_model){
    if(par_model==sel_58)
        out_switchselect=0;
    else if(par_model==sel_912)
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
    fun_delay(del_ms,1);//��ʱ1���� $?$
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
void fun_pwmr(uc par_value){
    CCAP0H=CCAP0L=par_value*2.5;//���������ռ�ձ�
    CCAPM0=0X42;//8λPWM��������ж�
    PCA_PWM0=0x00;
}//��·PWM���
void fun_pwml(uc par_value){
    CCAP1H=CCAP1L=par_value*2.5;//���������ռ�ձ�
    CCAPM1=0X42;//8λPWM��������ж�
    PCA_PWM1=0x00;
}//��·PWM���
void fun_startdj(enum varENU_mot par_model,char par_speed){
    if(par_speed==0)
        return;
    else if(par_speed>100)
        par_speed=100;
    else if(par_speed<-100)
        par_speed=-100;
    switch(par_model){
        case mot_l:
            CR=1;
            if(par_speed>0){
                fun_pwml(par_speed);out_pwml=0;
            }
            else if(par_speed<0){
                fun_pwml(cabs(par_speed));out_pwml=1;
            }
            break;
        case mot_r:
            CR=1;
            if(par_speed>0){
                fun_pwmr(par_speed);out_pwmr=0;
            }
            else if(par_speed<0){
                fun_pwmr(cabs(par_speed));out_pwmr=1;
            }
            break;
        case mot_rl:
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
        case mot_dj1://��תΪץ������תΪ�ɿ�
            out_motorselect=1;
            if(par_speed>0)
                out_dir1=1;
            else if(par_speed<0)
                out_dir1=0;
            out_en1=0;
            break;
        case mot_dj2://��ת�����޵��һ��ת,��תΪ���е��һ��ת
            out_motorselect=1;
            if(par_speed>0)
                out_dir2=1;
            else if(par_speed<0)
                out_dir2=0;
            out_en2=0;
            break;
        case mot_dj3://����Ϊ��ת,����Ϊ��ת
            out_motorselect=0;
            if(par_speed>0)
                out_dir1=0;
            else if(par_speed<0)
                out_dir1=1;
            out_en1=0;
            break;
        case mot_dj4://˳ʱ��Ϊ��ת,��ʱ��Ϊ��ת
            out_motorselect=0;
            if(par_speed>0)
                out_dir2=0;
            else if(par_speed<0)
                out_dir2=1;
            out_en2=0;
            break;
        default:
            break;
    }
}//�������
void fun_stop(enum varENU_mot par_model){
    switch(par_model){
        case mot_l:
            fun_pwml(0);out_pwml=0;break;
        case mot_r:
            fun_pwmr(0);out_pwmr=0;break;
        case mot_rl:
            CR=0;fun_pwmr(0);out_pwmr=0;fun_pwml(0);out_pwml=0;break;
        case mot_dj1:
            out_motorselect=1;out_dir1=0;out_en1=1;break;
        case mot_dj2:
            out_motorselect=1;out_dir2=0;out_en2=1;break;
        case mot_dj3:
            out_motorselect=0;out_dir1=0;out_en1=1;break;
        case mot_dj4:
            out_motorselect=0;out_dir2=0;out_en2=1;break;
        default:
            break;
    }
}//ֹͣ���
void fun_sz1(enum varENU_han par_model){
    if(par_model==han_s){
        while(1){
            fun_startdj(mot_dj1,-100);
            while(in_s==1);
            fun_delay(20,del_ms);
            if(in_s==0){
                fun_stop(mot_dj1);
                break;
            }
        }
    }
    else{
        while(1){
            fun_startdj(mot_dj1,100);
            while(in_j==1);
            fun_delay(20,del_ms);
            if(in_j==0){
                fun_stop(mot_dj1);
                break;
            }
        }
    }
    str_begin.szzt=par_model;
}//��ץ�����˶�
void fun_sj1(enum varENU_sjp par_model){
    switch(par_model){
        case sjp_wz1:
            while(1){
                fun_startdj(mot_dj3,100);
                fun_select(sel_58);
                fun_delay(50,del_ms);
                while(in_wz1==1);
                fun_delay(50,del_ms);
                if(in_wz1==0){
                    fun_stop(mot_dj3);
                    break;
                }
            }
            break;
        case sjp_wz2:
            if(par_model>str_begin.sjwz){
                while(1){
                    fun_startdj(mot_dj3,-100);
                    fun_select(sel_58);
                    fun_delay(50,del_ms);
                    while(in_wz2==1);
                    fun_delay(50,del_ms);
                    if(in_wz2==0){
                        fun_stop(mot_dj3);
                        break;
                    }
                }
            }
            else{
                while(1){
                    fun_startdj(mot_dj3,100);
                    fun_select(sel_58);
                    fun_delay(50,del_ms);
                    while(in_wz2==1);
                    fun_delay(50,del_ms);
                    if(in_wz2==0){
                        fun_stop(mot_dj3);
                        break;
                    }
                }
            }
            break;
        case sjp_wz3:
            if(par_model>str_begin.sjwz){
                while(1){
                    fun_startdj(mot_dj3,-100);
                    fun_select(sel_58);
                    fun_delay(50,del_ms);
                    while(in_wz3==1);
                    fun_delay(50,del_ms);
                    if(in_wz3==0){
                        fun_stop(mot_dj3);
                        break;
                    }
                }
            }
            else{
                while(1){
                    fun_startdj(mot_dj3,100);
                    fun_select(sel_58);
                    fun_delay(50,del_ms);
                    while(in_wz3==1);
                    fun_delay(50,del_ms);
                    if(in_wz3==0){
                        fun_stop(mot_dj3);
                        break;
                    }
                }
            }
            break;
        case sjp_wz4:
            if(par_model>str_begin.sjwz){
                while(1){
                    fun_startdj(mot_dj3,-100);
                    fun_select(sel_58);
                    fun_delay(50,del_ms);
                    while(in_wz4==1);
                    fun_delay(50,del_ms);
                    if(in_wz4==0){
                        fun_stop(mot_dj3);
                        break;
                    }
                }
            }
            else{
                while(1){
                    fun_startdj(mot_dj3,100);
                    fun_select(sel_58);
                    fun_delay(50,del_ms);
                    while(in_wz4==1);
                    fun_delay(50,del_ms);
                    if(in_wz4==0){
                        fun_stop(mot_dj3);
                        break;
                    }
                }
            }
            break;
        case sjp_wz5:
            while(1){
                fun_startdj(mot_dj3,-100);
                fun_select(sel_912);
                fun_delay(50,del_ms);
                while(in_wz5==1);
                fun_delay(50,del_ms);
                if(in_wz5==0){
                    fun_stop(mot_dj3);
                    return;
                }
            }
            break;
        default:
            break;
    }
    str_begin.sjwz=par_model;
}//���������˶�
void fun_py1(enum varENU_tra par_model){
    switch(par_model){
        case tra_q:
            while(1){
                fun_startdj(mot_dj2,100);
                while(in_qpy==1);
                fun_delay(20,del_ms);
                if(in_qpy==0){
                    fun_stop(mot_dj2);
                    break;
                }
            }
            break;
        case tra_h:
            while(1){
                fun_startdj(mot_dj2,-100);
                while(in_hpy==1);
                fun_delay(20,del_ms);
                if(in_hpy==0){
                    fun_stop(mot_dj2);
                    break;
                }
            }
            break;
        default:
            break;
    }
    str_begin.pywz=par_model;
}//ƽ�Ƶ����˶�
// void fun_hz1(enum varENU_dir par_model){
//     switch(par_model){
//         ;
//     }
// }