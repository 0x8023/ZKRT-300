#include "./output/8023.h"
xdata struct str_state str_begin,str_now,str_next;//�ֱ�Ϊ:��ʼ״̬/��ǰ״̬/Ŀ��״̬
xdata ui cod_mlinerqd=500,//Ĭ��������Ѳ������ʱ��Ϊ500����
         cod_mlineqc=300;//Ĭ��������Ѳ��ǰ��ʱ��Ϊ500����
void fun_delay(ui par_value,enum varENU_del par_model){
    ui loc_con=par_value;
    switch(par_model){
        case del_us://΢�뼶��ʱ
            while(loc_con-->0){
                _nop_();
                _nop_();
            }
            return;
        case del_ms://���뼶��ʱ
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
        case del_s://�뼶��ʱ
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
    //out_motorselect=1;//���ƬѡΪ1 $?$
    //fun_delay(del_ms,1);//��ʱ1���� $?$
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
        case mot_l://���ֵ��
            CR=1;
            if(par_speed>0){
                fun_pwml(par_speed);out_pwml=0;
            }
            else if(par_speed<0){
                fun_pwml(cabs(par_speed));out_pwml=1;
            }
            break;
        case mot_r://���ֵ��
            CR=1;
            if(par_speed>0){
                fun_pwmr(par_speed);out_pwmr=0;
            }
            else if(par_speed<0){
                fun_pwmr(cabs(par_speed));out_pwmr=1;
            }
            break;
        case mot_rl://������ͬ��
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
            CR=0;
            fun_pwmr(0);out_pwmr=0;
            fun_pwml(0);out_pwml=0;
            break;
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
    if(par_model==han_s){//��ץ��
        while(1){
            fun_startdj(mot_dj1,-100);
            while(in_s==1);
            fun_delay(20,del_ms);
            if(in_s==0)
                break;
        }
    }
    else{//��ץ��
        while(1){
            fun_startdj(mot_dj1,100);
            while(in_j==1);
            fun_delay(20,del_ms);
            if(in_j==0)
                break;
        }
    }
    fun_stop(mot_dj1);
    str_begin.szzt=par_model;//�洢���н��
}//��ץ�����˶�
void fun_sj1(enum varENU_sjp par_model){
    switch(par_model){
        case sjp_wz1://����λ��1(����λ)
            while(1){//ֻ������
                fun_startdj(mot_dj3,100);
                fun_select(sel_58);
                fun_delay(50,del_ms);
                while(in_wz1==1);
                fun_delay(50,del_ms);
                if(in_wz1==0)
                    break;
            }
            break;
        case sjp_wz2://����λ��2
            if(par_model>str_begin.sjwz){
                while(1){//Ҫȥ�ĵط��ȽϿ���,������
                    fun_startdj(mot_dj3,-100);
                    fun_select(sel_58);
                    fun_delay(50,del_ms);
                    while(in_wz2==1);
                    fun_delay(50,del_ms);
                    if(in_wz2==0)
                        break;
                }
            }
            else{//Ҫȥ�ĵط������棬������
                while(1){
                    fun_startdj(mot_dj3,100);
                    fun_select(sel_58);
                    fun_delay(50,del_ms);
                    while(in_wz2==1);
                    fun_delay(50,del_ms);
                    if(in_wz2==0)
                        break;
                }
            }
            break;
        case sjp_wz3://����λ��3
            if(par_model>str_begin.sjwz){
                while(1){//Ҫȥ�ĵط��ȽϿ���,������
                    fun_startdj(mot_dj3,-100);
                    fun_select(sel_58);
                    fun_delay(50,del_ms);
                    while(in_wz3==1);
                    fun_delay(50,del_ms);
                    if(in_wz3==0)
                        break;
                }
            }
            else{//Ҫȥ�ĵط������棬������
                while(1){
                    fun_startdj(mot_dj3,100);
                    fun_select(sel_58);
                    fun_delay(50,del_ms);
                    while(in_wz3==1);
                    fun_delay(50,del_ms);
                    if(in_wz3==0)
                        break;
                }
            }
            break;
        case sjp_wz4://����λ��4
            if(par_model>str_begin.sjwz){
                while(1){//Ҫȥ�ĵط��ȽϿ���,������
                    fun_startdj(mot_dj3,-100);
                    fun_select(sel_58);
                    fun_delay(50,del_ms);
                    while(in_wz4==1);
                    fun_delay(50,del_ms);
                    if(in_wz4==0)
                        break;
                }
            }
            else{//Ҫȥ�ĵط������棬������
                while(1){
                    fun_startdj(mot_dj3,100);
                    fun_select(sel_58);
                    fun_delay(50,del_ms);
                    while(in_wz4==1);
                    fun_delay(50,del_ms);
                    if(in_wz4==0)
                        break;
                }
            }
            break;
        case sjp_wz5://����λ��5
            while(1){//Ҫȥ�ĵط��ȽϿ���,������
                fun_startdj(mot_dj3,-100);
                fun_select(sel_912);
                fun_delay(50,del_ms);
                while(in_wz5==1);
                fun_delay(50,del_ms);
                if(in_wz5==0){
                    break;
                }
            }
            break;
        default:
            break;
    }
    fun_stop(mot_dj3);
    str_begin.sjwz=par_model;//�洢���н��
}//���������˶�
void fun_py1(enum varENU_tra par_model){
    switch(par_model){
        case tra_q://ǰƽ��(û�е�����ظ�����)
            while(1){
                fun_startdj(mot_dj2,100);
                while(in_qpy==1);
                fun_delay(20,del_ms);
                if(in_qpy==0)
                    break;
            }
            break;
        case tra_h://��ƽ��(�е�����ظ�����)
            while(1){
                fun_startdj(mot_dj2,-100);
                while(in_hpy==1);
                fun_delay(20,del_ms);
                if(in_hpy==0)
                    break;
            }
            break;
        default:
            break;
    }
    fun_stop(mot_dj2);
    str_begin.pywz=par_model;//�洢���н��
}//ƽ�Ƶ����˶�
void fun_hz1(enum varENU_dir par_model){
    switch(par_model){
        case dir_up://��ת��ǰ��
            switch(str_begin.hzfx){
                case dir_down://�������·�
                    fun_startdj(mot_dj4,-100);
                    fun_select(sel_912);
                    fun_delay(1,del_s);
                    while(1){
                        while(in_hz==1);
                        fun_delay(25,del_ms);
                        if(in_hz==0)
                            break;
                    }
                    while(1){
                        while(in_hz==0);
                        fun_delay(25,del_ms);
                        if(in_hz==1)
                            break;
                    }
                    while(1){
                        while(in_hz==1);
                        fun_delay(25,del_ms);
                        if(in_hz==0)
                            break;
                    }
                    break;
                case dir_left://���������
                    fun_startdj(mot_dj4,100);
                    fun_select(sel_912);
                    fun_delay(1,del_s);
                    while(1){
                        while(in_hz==1);
                        fun_delay(25,del_ms);
                        if(in_hz==0)
                            break;
                    }
                    break;
                case dir_right://�������ұ�
                    fun_startdj(mot_dj4,-100);
                    fun_select(sel_912);
                    fun_delay(1,del_s);
                    while(1){
                        while(in_hz==1);
                        fun_delay(25,del_ms);
                        if(in_hz==0)
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;
        case dir_down://Ҫȥ����
            switch(str_begin.hzfx){
                case dir_up://����������
                    fun_startdj(mot_dj4,100);
                    fun_select(sel_912);
                    fun_delay(1,del_s);
                    while(1){
                        while(in_hz==1);
                        fun_delay(25,del_ms);
                        if(in_hz==0)
                            break;
                    }
                    while(1){
                        while(in_hz==0);
                        fun_delay(25,del_ms);
                        if(in_hz==1)
                            break;
                    }
                    while(1){
                        while(in_hz==1);
                        fun_delay(25,del_ms);
                        if(in_hz==0)
                            break;
                    }
                    break;
                case dir_left://����������
                    fun_startdj(mot_dj4,-100);
                    fun_select(sel_912);
                    fun_delay(1,del_s);
                    while(1){
                        while(in_hz==1);
                        fun_delay(25,del_ms);
                        if(in_hz==0)
                            break;
                    }
                    break;
                case dir_right://����������
                    fun_startdj(mot_dj4,100);
                    fun_select(sel_912);
                    fun_delay(1,del_s);
                    while(1){
                        while(in_hz==1);
                        fun_delay(25,del_ms);
                        if(in_hz==0)
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;
        case dir_left://Ҫȥ���
            switch(str_begin.hzfx){
                case dir_up://����������
                    fun_startdj(mot_dj4,-100);
                    fun_select(sel_912);
                    fun_delay(1,del_s);
                    while(1){
                        while(in_hz==1);
                        fun_delay(25,del_ms);
                        if(in_hz==0)
                            break;
                    }
                    break;
                case dir_down://����������
                    fun_startdj(mot_dj4,100);
                    fun_select(sel_912);
                    fun_delay(1,del_s);
                    while(1){
                        while(in_hz==1);
                        fun_delay(25,del_ms);
                        if(in_hz==0)
                            break;
                    }
                    break;
                case dir_right://����������
                    fun_startdj(mot_dj4,-100);
                    fun_select(sel_912);
                    fun_delay(1,del_s);
                    while(1){
                        while(in_hz==1);
                        fun_delay(25,del_ms);
                        if(in_hz==0)
                            break;
                    }
                    while(1){
                        while(in_hz==0);
                        fun_delay(25,del_ms);
                        if(in_hz==1)
                            break;
                    }
                    while(1){
                        while(in_hz==1);
                        fun_delay(25,del_ms);
                        if(in_hz==0){
                            break;
                        }
                    }
                    break;
                default:
                    break;
            }
            break;
        case dir_right://Ҫȥ����
            switch(str_begin.hzfx){
                case dir_up://������ǰ��
                    fun_startdj(mot_dj4,100);
                    fun_select(sel_912);
                    fun_delay(1,del_s);
                    while(1){
                        while(in_hz==1);
                        fun_delay(25,del_ms);
                        if(in_hz==0)
                            break;
                    }
                    break;
                case dir_down://����������
                    fun_startdj(mot_dj4,-100);
                    fun_select(sel_912);
                    fun_delay(1,del_s);
                    while(1){
                        while(in_hz==1);
                        fun_delay(25,del_ms);
                        if(in_hz==0)
                            break;
                    }
                    break;
                case dir_left://����������
                    fun_startdj(mot_dj4,100);
                    fun_select(sel_912);
                    fun_delay(1,del_s);
                    while(1){
                        while(in_hz==1);
                        fun_delay(25,del_ms);
                        if(in_hz==0)
                            break;
                    }
                    while(1){
                        while(in_hz==0);
                        fun_delay(25,del_ms);
                        if(in_hz==1)
                            break;
                    }
                    while(1){
                        while(in_hz==1);
                        fun_delay(25,del_ms);
                        if(in_hz==0){
                            break;
                        }
                    }
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    fun_stop(mot_dj4);
    str_begin.hzfx=par_model;//�洢���н��
}//��ת�����˶�
void fun_mptline(uc par_num,uc par_sd,enum varENU_dir par_model){
    bit loc_flag=0;
    ui loc_i;
    uc loc_con=0;
    uc loc_l=par_sd,loc_r=par_sd;
    for(loc_i=2;loc_i<par_sd;fun_startdj(mot_rl,loc_i++))//����
        fun_delay(cod_mlinerqd/par_sd,del_ms);
    while(1){
        loc_l=par_sd;//�ָ�Ĭ�ϲ���
        loc_r=par_sd;
        if((in_ls1&&in_ls7)||(in_ls2&&in_ls8)){//Ѳ�߼���
            loc_flag=1;
            if(loc_con>=par_num){
                if(par_model==dir_left){//��ת
                    fun_startdj(mot_l,-20);
                    fun_delay(500,del_ms);
                    while(1){
                        while(!in_ls4||!in_ls5);
                        fun_delay(100,del_us);
                        if(in_ls4&&in_ls5){
                            fun_stop(mot_rl);
                            return;
                        }
                    }
                }
                else if(par_model==dir_right){
                    fun_startdj(mot_r,-20);
                    fun_delay(500,del_ms);
                    while(1){
                        while(!in_ls4||!in_ls5);
                        fun_delay(100,del_us);
                        if(in_ls4&&in_ls5){
                            fun_stop(mot_rl);
                            return;
                        }
                    }
                }
            }
        }
        else if(loc_flag==1){
            if(++loc_con>=par_num){
                if(par_model==dir_up){
                    for(loc_i=0;loc_i<cod_mlineqc;loc_i++){
                        loc_l=par_sd*0.7;//�ָ�Ĭ�ϲ���
                        loc_r=par_sd*0.7;
                        if(in_ls3){//��ƫ
                            loc_l*=0.9;
                            loc_r*=1.1;
                        }
                        if(in_ls6){
                            loc_l*=1.1;
                            loc_r*=0.9;
                        }
                        if(in_ls2){
                            loc_l*=0.8;
                            loc_r*=1.2;
                        }
                        if(in_ls7){
                            loc_l*=1.2;
                            loc_r*=0.8;
                        }
                        if(in_ls1){
                            loc_l*=0.7;
                            loc_r*=1.3;
                        }
                        if(in_ls8){
                            loc_l*=1.3;
                            loc_r*=0.7;
                        }
                        fun_startdj(mot_l,loc_l);//���µ������
                        fun_startdj(mot_r,loc_r);
                        fun_delay(1,del_ms);
                    }
                    fun_stop(mot_rl);
                    return;
                }
            }
            loc_flag=0;
        }
        if(in_ls3){//��ƫ
            loc_l*=0.9;
            loc_r*=1.1;
        }
        if(in_ls6){
            loc_l*=1.1;
            loc_r*=0.9;
        }  
        if(in_ls2){
            loc_l*=0.8;
            loc_r*=1.2;
        }
        if(in_ls7){
            loc_l*=1.2;
            loc_r*=0.8;
        }
        if(in_ls1){
            loc_l*=0.7;
            loc_r*=1.3;
        }
        if(in_ls8){
            loc_l*=1.3;
            loc_r*=0.7;
        }
        fun_startdj(mot_l,loc_l);//���µ������
        fun_startdj(mot_r,loc_r);
    }
}//��������ͨѲ��
