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
}//延时
void fun_timer0init(){
    AUXR&=0x7F;
    TMOD&=0xF0;
    TMOD|=0x01;
    TL0=0xB0;
    TH0=0x3C;
    TF0=0;
}//50毫秒定时器0初始化
void fun_timer1init(){
    AUXR&=0xBF;
    TMOD&=0x0F;
    TMOD|=0x10;
    TL1=0xE0;
    TH1=0xB1;
    TF1=0;
}//20毫秒定时器1初始化
void fun_timer0(){
    TL0=0xB0;
    TH0=0x3C;
    _nop_();
}//50毫秒定时器0处理函数
void fun_timer1(){
    TL1=0xE0;
    TH1=0xB1;
    _nop_();
}//20毫秒定时器1处理函数
void fun_wait(){
    while(in_start==1);
    fun_delay(ms,20);
    while(in_start==0);
    fun_delay(ms,256);
}//等待按键
void fun_select(enum varENU_selectsensor par_model){
    if(par_model==ps58)
        out_switchselect=0;
    else if(par_model==ps912)
        out_switchselect=1;
}//传感器片选
void fun_initialization(){
    CLK_DIV=0x00;//不分频

    P0M1=0xff;//P0用于输入
    P0M0=0x00;//P0不能输出
    
    P1M1=0x00;//P1口0-1双向，2中断输入，3-6输入，7输出
    P1M0=0xfc;//P1口2-7输出

    P2M1=0xf0;//P2口4-7输入
    P2M0=0x0f;//P2口0-3输出

    //PS_2=1;//手抓松传感器置1 $?$
    //PS_11=1;//升降位置3传感器置1 $?$

    out_en1=1;//电机1/3使能 $?$
    out_en2=1;//电机2/4使能 $?$
    out_motorselect=1;//电机片选为1 $?$
    fun_delay(ms,1);//延时1毫秒 $?$
    out_motorselect=0;//电机片选为0 $?$
    //PS_5=PS_1;// $?$

    fun_pwminit();//PWM的初始化设置
    fun_timer0init();//初始化定时器0
    fun_timer1init();//初始化定时器1
    in_start=1;//按键置1

    fun_wait();
}//初始化
void fun_pwminit(){
    CCON=0x00;
    CH=0;
    CL=0;
    CMOD=0x00;
}//PWM初始化
void fun_pwmr(ui par_value){
    CCAP0H=CCAP0L=par_value*2.5;//控制输出的占空比
    CCAPM0=0X42;//8位PWM输出，无中断
    PCA_PWM0=0x00;
}//右路PWM输出
void fun_pwml(ui par_value){
    CCAP1H=CCAP1L=par_value*2.5;//控制输出的占空比
    CCAPM1=0X42;//8位PWM输出，无中断
    PCA_PWM1=0x00;
}//左路PWM输出
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
}//启动电机
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
}//停止电机

