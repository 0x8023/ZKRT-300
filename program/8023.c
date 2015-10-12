#include "./output/8023.h"
struct str_state str_begin,str_now,str_next;//分别为:起始状态/当前状态/目标状态
struct str_parameter str_cod={
    /*ui str_cod.mlinerqd*/25000,//默认主函数巡线软起动路程为25000
    /*ui str_cod.mlineqc*/200,   //默认主函数巡线前冲时间为500毫秒

    /*ui str_cod.sj1bzw*/58,     //升降标准位延时
    /*ui str_cod.sj1zjw*/800,    //升降中间位延时

    /*ui str_cod.py1bz*/45,      //fun_py标准位延时
    /*ui str_cod.py1qkq*/600,    //fun_py前到靠前延时参数
    /*ui str_cod.py1kqz*/525,    //fun_py靠前到中间延时
    /*ui str_cod.py1zkh*/525,    //fun_py中间到靠后延时
    /*ui str_cod.py1khh*/540,    //fun_py靠后到后延时
    /*ui str_cod.py1qz*/1155,    //fun_py前到中间延时
    /*ui str_cod.py1zh*/1090,    //fun_py中间到后延时
    /*ui str_cod.py1kqkh*/1105,  //fun_py靠前到靠后延时
    /*ui str_cod.py1khkq*/1050,  //fun_py靠后到靠前延时
    /*ui str_cod.py1qkh*/1735,   //fun_py前到靠后延时
    /*ui str_cod.py1kqh*/1635,   //fun_py靠前到后延时

    /*ui str_cod.hz1bz*/20,      //fun_hz标准位延时

    /*ui turn90;*/500,           //90度转弯屏蔽延时
    /*ui turn180;*/2000          //180度转弯屏蔽延时
};
struct str_timerfolline str_tfl;
char var_gjt[4][8];
char var_top;
data ul var_timer;
void fun_delay(ui par_value,enum varENU_del par_model){
    data ui loc_con=par_value;
    switch(par_model){
        case del_us://微秒级延时
            #ifdef Debug
                printf("fun_delay(%d,del_us);\n",par_value);
            #else
                while(loc_con-->0){
                    _nop_();
                    _nop_();
                }
            #endif
            return;
        case del_ms://毫秒级延时
            #ifdef Debug
                printf("fun_delay(%d,del_ms);\n",par_value);
            #else
                while(loc_con-->0){
                    data uc loc_i, loc_j;
                    _nop_();
                    _nop_();
                    loc_i=12;
                    loc_j=168;
                    do{
                        while(--loc_j);
                    }while(--loc_i);
                }
            #endif
            return;
        case del_s://秒级延时
            #ifdef Debug
                printf("fun_delay(%d,del_s);\n",par_value);
            #else
                while(loc_con-->0){
                    data uc loc_i, loc_j, loc_k;
                    loc_i=46;
                    loc_j=153;
                    loc_k=245;
                    do{
                        do{
                            while(--loc_k);
                        }while(--loc_j);
                    }while(--loc_i);
                }
            #endif
            return;
        default:return;
    }
}//延时
void fun_timer0init(){
    #ifdef Debug
        printf("fun_timer0init();\n");
    #endif
    AUXR|=0x80;   //定时器时钟1T模式
    TMOD&=0xF0;   //定时器模式:16位
    TMOD|=0x01;   //定时器模式:16位
    TL0=0x20;     //定时初值:1ms
    TH0=0xD1;     //定时初值:1ms
    TF0=0;        //清除TF0标志
    ET0=1;
    EA=1;         //开启总中断
}//1毫秒定时器0初始化
void fun_timer1init(){
    #ifdef Debug
        printf("fun_timer1init();\n");
    #endif
    AUXR&=0xBF;     //定时器时钟12T模式
    TMOD&=0x0F;     //定时器模式:16位
    TMOD|=0x10;     //定时器模式:16位
    TL1=0xE0;       //定时初值:20ms
    TH1=0xB1;       //定时初值:20ms
    TF1=0;          //清除TF1标志
    ET1=1;
    EA=1;           //开启总中断
}//20毫秒定时器1初始化
void fun_timer0(){
    TL0=0x20;
    TH0=0xD1;//定时器初值恢复至1ms
    var_timer++;//全局计时器开始计时
    if(str_tfl.doing==tf_ture)//如果正在移动
        fun_timermove();//定时器移动
}//1毫秒定时器0处理函数
void fun_timer1(){
    TL1=0xE0;
    TH1=0xB1;
}//20毫秒定时器1处理函数
void fun_wait(){
    in_start=1;               //按键置1
    #ifdef Debug
        printf("fun_wait();\n");
    #else
        while(in_start==1);
        fun_delay(20,del_ms);
        while(in_start==0);
        fun_delay(256,del_ms);
    #endif
}//等待按键
void fun_pwminit(){
    #ifdef Debug
        printf("fun_pwminit();\n");
    #endif
    CCON=0x00;//PAC寄存控制器
    CH=0;//重置PAC计时器
    CL=0;
    CMOD=0x08;//不分频
}//PWM初始化
void fun_pwmr(uc par_value){
    CCAP0H=CCAP0L=par_value*25/10;//控制输出的占空比
    CCAPM0=0X42;//8位PWM输出，无中断
    PCA_PWM0=0x00;
}//右路PWM输出
void fun_pwml(uc par_value){
    CCAP1H=CCAP1L=par_value*25/10;//控制输出的占空比
    CCAPM1=0X42;//8位PWM输出，无中断
    PCA_PWM1=0x00;
}//左路PWM输出
void fun_motors(enum varENU_mot par_model,char par_speed){
    if(par_speed>100)
        par_speed=100;
    else if(par_speed<-100)
        par_speed=-100;//速度最多100,最少-100
    switch(par_model){
        case mot_l://左轮电机
            if(str_begin.leftsd==par_speed)
                return;
            else
                str_begin.leftsd=par_speed;
            if(par_speed==0){
                fun_pwml(0);out_pwml=0;
            }
            else if(par_speed>0){
                CR=1;fun_pwml(par_speed);out_pwml=0;
            }
            else if(par_speed<0){
                CR=1;fun_pwml(cabs(par_speed));out_pwml=1;
            }
            break;
        case mot_r://右轮电机
            if(str_begin.rightsd==par_speed)
                return;
            else
                str_begin.rightsd=par_speed;
            if(par_speed==0){
                fun_pwmr(0);out_pwmr=0;
            }
            else if(par_speed>0){
                CR=1;fun_pwmr(par_speed);out_pwmr=0;
            }
            else if(par_speed<0){
                CR=1;fun_pwmr(cabs(par_speed));out_pwmr=1;
            }
            break;
        case mot_rl://左右轮同步
            if((str_begin.leftsd==par_speed)&&(str_begin.rightsd==par_speed))
                return;
            else
                str_begin.leftsd=str_begin.rightsd=par_speed;
            if(par_speed==0){
                CR=0;
                fun_pwmr(0);out_pwmr=0;
                fun_pwml(0);out_pwml=0;
            }
            else if(par_speed>0){
                CR=1;
                fun_pwml(par_speed);out_pwml=0;
                fun_pwmr(par_speed);out_pwmr=0;
            }
            else if(par_speed<0){
                CR=1;
                fun_pwml(cabs(par_speed));out_pwml=1;
                fun_pwmr(cabs(par_speed));out_pwmr=1;
            }
            break;
        case mot_sz://正转为抓紧，反转为松开
            if(str_begin.szsd==par_speed)
                return;
            else
                str_begin.szsd=par_speed;
            if(par_speed==0){
                out_motorselect=1;out_dir1=0;out_en1=1;
            }
            else if(par_speed>0){
                out_motorselect=1;out_dir1=1;out_en1=0;
            }
            else if(par_speed<0){
                out_motorselect=1;out_dir1=0;out_en1=0;
            }
            break;
        case mot_py://正转是向无电机一方转,反转为向有电机一方转
            if(str_begin.pysd==par_speed)
                return;
            else
                str_begin.pysd=par_speed;
            if(par_speed==0){
                out_motorselect=1;out_dir2=0;out_en2=1;
            }
            else if(par_speed>0){
                out_motorselect=1;out_dir2=1;out_en2=0;
            }
            else if(par_speed<0){
                out_motorselect=1;out_dir2=0;out_en2=0;
            }
            break;
        case mot_sj://向上为正转,向下为反转
            if(str_begin.sjsd==par_speed)
                return;
            else
                str_begin.sjsd=par_speed;
            if(par_speed==0){
                out_motorselect=0;out_dir1=0;out_en1=1;
            }
            else if(par_speed>0){
                out_motorselect=0;out_dir1=0;out_en1=0;
            }
            else if(par_speed<0){
                out_motorselect=0;out_dir1=1;out_en1=0;
            }
            break;
        case mot_hz://顺时针为正转,逆时针为反转
            if(str_begin.hzsd==par_speed)
                return;
            else
                str_begin.hzsd=par_speed;
            if(par_speed==0){
                out_motorselect=0;out_dir2=0;out_en2=1;
            }
            else if(par_speed>0){
                out_motorselect=0;out_dir2=0;out_en2=0;
            }
            else if(par_speed<0){
                out_motorselect=0;out_dir2=1;out_en2=0;
            }
            break;
        default:
            break;
    }
}//主函数操作电机
void fun_motorsrl(enum varENU_mot par_model,char par_speed){
    if(par_speed>100)
        par_speed=100;
    else if(par_speed<-100)
        par_speed=-100;//速度最多100,最少-100
    switch(par_model){
        case mot_l://左轮电机
            if(str_begin.leftsd==par_speed)
                return;
            else
                str_begin.leftsd=par_speed;
            if(par_speed==0){
                fun_pwml(0);out_pwml=0;
            }
            else if(par_speed>0){
                CR=1;fun_pwml(par_speed);out_pwml=0;
            }
            else if(par_speed<0){
                CR=1;fun_pwml(cabs(par_speed));out_pwml=1;
            }
            break;
        case mot_r://右轮电机
            if(str_begin.rightsd==par_speed)
                return;
            else
                str_begin.rightsd=par_speed;
            if(par_speed==0){
                fun_pwmr(0);out_pwmr=0;
            }
            else if(par_speed>0){
                CR=1;fun_pwmr(par_speed);out_pwmr=0;
            }
            else if(par_speed<0){
                CR=1;fun_pwmr(cabs(par_speed));out_pwmr=1;
            }
            break;
        case mot_rl://左右轮同步
            if((str_begin.leftsd==par_speed)&&(str_begin.rightsd==par_speed))
                return;
            else
                str_begin.leftsd=str_begin.rightsd=par_speed;
            if(par_speed==0){
                CR=0;
                fun_pwmr(0);out_pwmr=0;
                fun_pwml(0);out_pwml=0;
            }
            else if(par_speed>0){
                CR=1;
                fun_pwml(par_speed);out_pwml=0;
                fun_pwmr(par_speed);out_pwmr=0;
            }
            else if(par_speed<0){
                CR=1;
                fun_pwml(cabs(par_speed));out_pwml=1;
                fun_pwmr(cabs(par_speed));out_pwmr=1;
            }
            break;
        default:
            break;
    }
}//定时器操作左右轮
void fun_sz(enum varENU_han par_model){
    if(str_begin.szzt==par_model)
        return;
    if(par_model==han_s){//手抓松
        #ifdef Debug
            printf("fun_sz(han_s);\n");
        #else
            fun_motors(mot_sz,-100);
            while(in_s==1);
        #endif
    }
    else{//手抓紧
        #ifdef Debug
            printf("fun_sz(han_j);\n");
        #else
            fun_motors(mot_sz,100);
            while(in_j==1);
        #endif
    }
        fun_delay(20,del_ms);
        fun_motors(mot_sz,0);
    str_begin.szzt=par_model;//存储运行结果
}//手抓单步运动
void fun_py(enum varENU_tra par_model){
    if(str_begin.pywz==par_model)
        return;
    switch(par_model){
        case tra_q://前平移(没有电机的呢个方向)
            #ifdef Debug
                printf("fun_py(tra_q);\n");
            #else
                fun_motors(mot_py,100);
                while(in_qpy==1);
                fun_delay(str_cod.py1bz,del_ms);
            #endif
                break;
        case tra_kq://靠前平移
            #ifdef Debug
                printf("fun_py(tra_kq);\n");
            #else
                switch(str_begin.pywz){
                    case tra_q://现在在前面
                        fun_motors(mot_py,-100);
                        fun_delay(str_cod.py1qkq,del_ms);
                        break;
                    case tra_z://现在在中间
                        fun_motors(mot_py,100);
                        fun_delay(str_cod.py1kqz,del_ms);
                        break;
                    case tra_kh://现在在靠后
                        fun_motors(mot_py,100);
                        fun_delay(str_cod.py1khkq,del_ms);
                        break;
                    case tra_h://现在在后
                        fun_motors(mot_py,100);
                        fun_delay(str_cod.py1kqh,del_ms);
                        break;
                }
            #endif
                break;
        case tra_z://平移到中间
            #ifdef Debug
                printf("fun_py(tra_z);\n");
            #else
                switch(str_begin.pywz){
                    case tra_q://现在在前面
                        fun_motors(mot_py,-100);
                        fun_delay(str_cod.py1qz,del_ms);
                        break;
                    case tra_kq://现在在靠前
                        fun_motors(mot_py,-100);
                        fun_delay(str_cod.py1kqz,del_ms);
                        break;
                    case tra_kh://现在在靠后
                        fun_motors(mot_py,100);
                        fun_delay(str_cod.py1zkh,del_ms);
                        break;
                    case tra_h://现在在后面
                        fun_motors(mot_py,100);
                        fun_delay(str_cod.py1zh,del_ms);
                        break;
                }
            #endif
                break;
        case tra_kh://平移到靠后
            #ifdef Debug
                printf("fun_py(tra_kh);\n");
            #else
                switch(str_begin.pywz){
                    case tra_q://现在在前面
                        fun_motors(mot_py,-100);
                        fun_delay(str_cod.py1qkh,del_ms);
                        break;
                    case tra_kq://现在在靠前
                        fun_motors(mot_py,-100);
                        fun_delay(str_cod.py1kqkh,del_ms);
                        break;
                    case tra_z://现在在中间
                        fun_motors(mot_py,-100);
                        fun_delay(str_cod.py1zkh,del_ms);
                        break;
                    case tra_h://现在在后面
                        fun_motors(mot_py,100);
                        fun_delay(str_cod.py1khh,del_ms);
                        break;
                }
            #endif
                break;
        case tra_h://后平移(有电机的呢个方向)
            #ifdef Debug
                printf("fun_py(tra_h);\n");
            #else
                fun_motors(mot_py,-100);
                while(in_hpy==1);
                fun_delay(str_cod.py1bz,del_ms);
            #endif
                break;
        default:
            break;
    }
    fun_motors(mot_py,0);
    str_begin.pywz=par_model;//存储运行结果
}//平移单步运动
void fun_sj(enum varENU_sjp par_model){
    if(str_begin.sjwz==par_model)
       return;
    def_select(sel_58)
    switch(par_model){
        case sjp_1://升降位置1(最上位)
            #ifdef Debug
                printf("fun_sj(sjp_1);\n");
            #else
                fun_motors(mot_sj,100);
                def_select(sel_58);
                while(in_wz1==1);
                fun_delay(str_cod.sj1bzw,del_ms);
            #endif
                break;
        case sjp_12:
            #ifdef Debug
                printf("fun_sj(sjp_12);\n");
            #else
                if(par_model>str_begin.sjwz){
                    fun_motors(mot_sj,-100);
                    fun_delay(str_cod.sj1zjw,del_ms);
                }
                else{//要去的地方在上面，向上走
                    fun_sj(sjp_2);
                    fun_motors(mot_sj,100);
                    fun_delay(str_cod.sj1zjw,del_ms);
                }
            #endif
                break;
        case sjp_2://升降位置2
            #ifdef Debug
                printf("fun_sj(sjp_2);\n");
            #else
                fun_motors(mot_sj,par_model<str_begin.sjwz?100:-100);
                def_select(sel_58);
                while(in_wz2==1);
                fun_delay(str_cod.sj1bzw,del_ms);
            #endif
                break;
        case sjp_23:
            #ifdef Debug
                printf("fun_sj(sjp_23);\n");
            #else
                if(par_model>str_begin.sjwz){
                    fun_sj(sjp_2);
                    fun_motors(mot_sj,-100);
                    fun_delay(str_cod.sj1zjw,del_ms);
                }
                else{//要去的地方在上面，向上走
                    fun_sj(sjp_3);
                    fun_motors(mot_sj,100);
                    fun_delay(str_cod.sj1zjw,del_ms);
                }
            #endif
                break;
        case sjp_3://升降位置3
            #ifdef Debug
                printf("fun_sj(sjp_3);\n");
            #else
                fun_motors(mot_sj,par_model<str_begin.sjwz?100:-100);
                def_select(sel_58);
                while(in_wz3==1);
                fun_delay(str_cod.sj1bzw,del_ms);
            #endif
            break;
        case sjp_34:
            #ifdef Debug
                printf("fun_sj(sjp_34);\n");
            #else
                if(par_model>str_begin.sjwz){
                    fun_sj(sjp_3);
                    fun_motors(mot_sj,-100);
                    fun_delay(str_cod.sj1zjw,del_ms);
                }
                else{//要去的地方在上面，向上走
                    fun_sj(sjp_4);
                    fun_motors(mot_sj,100);
                    fun_delay(str_cod.sj1zjw,del_ms);
                }
            #endif
                break;
        case sjp_4://升降位置4
            #ifdef Debug
                printf("fun_sj(sjp_4);\n");
            #else
                fun_motors(mot_sj,par_model<str_begin.sjwz?100:-100);
                def_select(sel_58);
                while(in_wz4==1);
                fun_delay(str_cod.sj1bzw,del_ms);
            #endif
                break;
        case sjp_45:
            #ifdef Debug
                printf("fun_sj(sjp_45);\n");
            #else
                if(par_model>str_begin.sjwz){
                    fun_sj(sjp_4);
                    fun_motors(mot_sj,-100);
                    fun_delay(str_cod.sj1zjw,del_ms);
                }
                else{//要去的地方在上面，向上走
                    fun_motors(mot_sj,100);
                    fun_delay(str_cod.sj1zjw,del_ms);
                }
            #endif
                break;
        case sjp_5://升降位置5
            #ifdef Debug
                printf("fun_sj(sjp_5);\n");
            #else
                fun_motors(mot_sj,-100);
                def_select(sel_912);
                while(in_wz5==1);
                fun_delay(str_cod.sj1bzw,del_ms);
            #endif
                break;
        default:
            break;
    }
    fun_motors(mot_sj,0);
    str_begin.sjwz=par_model;//存储运行结果
}//升降单步运动
void fun_hz(enum varENU_dir par_model){
    if(str_begin.hzfx==par_model)
        return;
    def_select(sel_912);
    switch(par_model){
        case dir_up://回转至前方
            #ifdef Debug
                printf("fun_hz(dir_up);\n");
            #else
                switch(str_begin.hzfx){
                    case dir_down://现在在下方
                        fun_motors(mot_hz,-100);
                        fun_delay(1,del_s);
                        while(in_hz==1);
                        while(in_hz==0);
                        while(in_hz==1);
                        fun_delay(str_cod.hz1bz,del_ms);
                        break;
                    case dir_left://现在在左边
                        fun_motors(mot_hz,100);
                        fun_delay(1,del_s);
                        while(in_hz==1);
                        fun_delay(str_cod.hz1bz,del_ms);
                        break;
                    case dir_right://现在在右边
                        fun_motors(mot_hz,-100);
                        fun_delay(1,del_s);
                        while(in_hz==1);
                        fun_delay(str_cod.hz1bz,del_ms);
                        break;
                    default:
                        break;
                }
            #endif
                break;
        case dir_down://要去下面
            #ifdef Debug
                printf("fun_hz(dir_down);\n");
            #else
                switch(str_begin.hzfx){
                    case dir_up://现在在上面
                        fun_motors(mot_hz,100);
                        fun_delay(1,del_s);
                        while(in_hz==1);
                        while(in_hz==0);
                        while(in_hz==1);
                        fun_delay(str_cod.hz1bz,del_ms);
                        break;
                    case dir_left://现在在左面
                        fun_motors(mot_hz,-100);
                        fun_delay(1,del_s);
                        while(in_hz==1);
                        fun_delay(str_cod.hz1bz,del_ms);
                        break;
                    case dir_right://现在在右面
                        fun_motors(mot_hz,100);
                        fun_delay(1,del_s);
                        while(in_hz==1);
                        fun_delay(str_cod.hz1bz,del_ms);
                        break;
                    default:
                        break;
                }
            #endif
                break;
        case dir_left://要去左边
            #ifdef Debug
                printf("fun_hz(dir_left);\n");
            #else
                switch(str_begin.hzfx){
                    case dir_up://现在在上面
                        fun_motors(mot_hz,-100);
                        fun_delay(1,del_s);
                        while(in_hz==1);
                        fun_delay(str_cod.hz1bz,del_ms);
                        break;
                    case dir_down://现在在下面
                        fun_motors(mot_hz,100);
                        fun_delay(1,del_s);
                        while(in_hz==1);
                        fun_delay(str_cod.hz1bz,del_ms);
                        break;
                    case dir_right://现在在右面
                        fun_motors(mot_hz,-100);
                        fun_delay(1,del_s);
                        while(in_hz==1);
                        while(in_hz==0);
                        while(in_hz==1);
                        fun_delay(str_cod.hz1bz,del_ms);
                        break;
                    default:
                        break;
                }
            #endif
                break;
        case dir_right://要去右面
            #ifdef Debug
                printf("fun_hz(dir_right);\n");
            #else
                switch(str_begin.hzfx){
                    case dir_up://现在在前面
                        fun_motors(mot_hz,100);
                        fun_delay(1,del_s);
                        while(in_hz==1);
                        fun_delay(str_cod.hz1bz,del_ms);
                        break;
                    case dir_down://现在在下面
                        fun_motors(mot_hz,-100);
                        fun_delay(1,del_s);
                        while(in_hz==1);
                        fun_delay(str_cod.hz1bz,del_ms);
                        break;
                    case dir_left://现在在左面
                        fun_motors(mot_hz,100);
                        fun_delay(1,del_s);
                        while(in_hz==1);
                        while(in_hz==0);
                        while(in_hz==1);
                        fun_delay(str_cod.hz1bz,del_ms);
                        break;
                    default:
                        break;
                }
            #endif
                break;
        default:
            break;
    }
    fun_motors(mot_hz,0);
    str_begin.hzfx=par_model;//存储运行结果
}//回转单步运动
void fun_pyhz(enum varENU_tra par_pymodel,enum varENU_dir par_hzmodel){
    switch(par_hzmodel){//获取想要到达的回转位置
        case dir_left://要去左边
            switch(str_begin.hzfx){
                case dir_right://现在在右边
                    fun_motors(mot_hz,-100);
                    break;
                case dir_up://现在在上面
                    fun_motors(mot_hz,-100);
                    break;
                case dir_down://现在在下面
                    fun_motors(mot_hz,100);
                    break;
                default:
                    break;
            }//获取现在回转所在的位置
            break;
        case dir_right://要去右边
            switch(str_begin.hzfx){
                case dir_left://现在在左边
                    fun_motors(mot_hz,100);
                    break;
                case dir_up://现在在上面
                    fun_motors(mot_hz,100);
                    break;
                case dir_down://现在在下面
                    fun_motors(mot_hz,-100);
                    break;
                default:
                    break;
            }//获取现在回转所在的位置
            break;
        case dir_up://要去上面
            switch(str_begin.hzfx){
                case dir_left://现在在左边
                    fun_motors(mot_hz,100);
                    break;
                case dir_right://现在在右边
                    fun_motors(mot_hz,-100);
                    break;
                case dir_down://现在在下面
                    fun_motors(mot_hz,-100);
                    break;
                default:
                    break;
            }//获取现在回转所在的位置
            break;
        case dir_down://要去下面
            switch(str_begin.hzfx){
                case dir_left://现在在左边
                    fun_motors(mot_hz,-100);
                    break;
                case dir_right://现在在右边
                    fun_motors(mot_hz,100);
                    break;
                case dir_up://现在在上面
                    fun_motors(mot_hz,100);
                    break;
                default:
                    break;
            }//获取现在回转所在的位置
            break;
        default:
            break;
    }//获取现在要去的回转位置
    fun_py(par_pymodel);//做平移
    def_select(sel_912);//传感器片选
    switch(par_hzmodel){//获取想要到达的回转位置
        case dir_up://回转至前方
            switch(str_begin.hzfx){
                case dir_down://现在在下方
                    while(in_hz==1);
                    while(in_hz==0);
                    while(in_hz==1);
                    fun_delay(str_cod.hz1bz,del_ms);
                    break;
                case dir_left://现在在左边
                    while(in_hz==1);
                    fun_delay(str_cod.hz1bz,del_ms);
                    break;
                case dir_right://现在在右边
                    while(in_hz==1);
                    fun_delay(str_cod.hz1bz,del_ms);
                    break;
                default:
                    break;
            }
            break;
        case dir_down://要去下面
            switch(str_begin.hzfx){
                case dir_up://现在在上面
                    while(in_hz==1);
                    while(in_hz==0);
                    while(in_hz==1);
                    fun_delay(str_cod.hz1bz,del_ms);
                    break;
                case dir_left://现在在左面
                    while(in_hz==1);
                    fun_delay(str_cod.hz1bz,del_ms);
                    break;
                case dir_right://现在在右面
                    while(in_hz==1);
                    fun_delay(str_cod.hz1bz,del_ms);
                    break;
                default:
                    break;
            }
            break;
        case dir_left://要去左边
            switch(str_begin.hzfx){
                case dir_up://现在在上面
                    while(in_hz==1);
                    fun_delay(str_cod.hz1bz,del_ms);
                    break;
                case dir_down://现在在下面
                    while(in_hz==1);
                    fun_delay(str_cod.hz1bz,del_ms);
                    break;
                case dir_right://现在在右面
                    while(in_hz==1);
                    while(in_hz==0);
                    while(in_hz==1);
                    fun_delay(str_cod.hz1bz,del_ms);
                    break;
                default:
                    break;
            }
            break;
        case dir_right://要去右面
            switch(str_begin.hzfx){
                case dir_up://现在在前面
                    while(in_hz==1);
                    fun_delay(str_cod.hz1bz,del_ms);
                    break;
                case dir_down://现在在下面
                    while(in_hz==1);
                    fun_delay(str_cod.hz1bz,del_ms);
                    break;
                case dir_left://现在在左面
                    while(in_hz==1);
                    while(in_hz==0);
                    while(in_hz==1);
                    fun_delay(str_cod.hz1bz,del_ms);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }//获取现在要去的回转位置
    fun_motors(mot_hz,0);//停止回转动作
    str_begin.hzfx=par_hzmodel;//存储运行结果
}//平移回转同步运动
void fun_sjhz(enum varENU_tra par_sjmodel,enum varENU_dir par_hzmodel){
    ul loc_sjdelay=0;//升降中间位延时
    ul loc_hzdelay=0xFFFF;//回转延时
    uc loc_sjcgq=0;//升降传感器检测标志位(0为不做升降,1为未到传感器,2为已到传感器)
    uc loc_hzcgq=0;//回转周期标志位(0为不做,1为一圈,2为两圈)
    uc loc_hzflag=0;//回转传感器标志位
    if(par_hzmodel!=str_begin.hzfx){
        switch(par_hzmodel){
            case dir_up://回转至前方
                switch(str_begin.hzfx){
                    case dir_down://现在在下方
                        fun_motors(mot_hz,-100);//反转
                        loc_hzcgq=2;//俩周期
                        break;
                    case dir_left://现在在左边
                        fun_motors(mot_hz,100);//正转
                        loc_hzcgq=1;//一个周期
                        break;
                    case dir_right://现在在右边
                        fun_motors(mot_hz,-100);//反转
                        loc_hzcgq=1;//一个周期
                        break;
                    default:
                        break;
                }
                break;
            case dir_down://要去下面
                switch(str_begin.hzfx){
                    case dir_up://现在在上面
                        fun_motors(mot_hz,100);//正转
                        loc_hzcgq=2;//俩周期
                        break;
                    case dir_left://现在在左面
                        fun_motors(mot_hz,-100);//反转
                        loc_hzcgq=1;//一个周期
                        break;
                    case dir_right://现在在右面
                        fun_motors(mot_hz,100);//正转
                        loc_hzcgq=1;//一个周期
                        break;
                    default:
                        break;
                }
                break;
            case dir_left://要去左边
                switch(str_begin.hzfx){
                    case dir_up://现在在上面
                        fun_motors(mot_hz,-100);//反转
                        loc_hzcgq=1;//一个周期
                        break;
                    case dir_down://现在在下面
                        fun_motors(mot_hz,100);//正转
                        loc_hzcgq=1;//一个周期
                        break;
                    case dir_right://现在在右面
                        fun_motors(mot_hz,-100);//反转
                        loc_hzcgq=2;//俩周期
                        break;
                    default:
                        break;
                }
                break;
            case dir_right://要去右面
                switch(str_begin.hzfx){
                    case dir_up://现在在前面
                        fun_motors(mot_hz,100);//正转
                        loc_hzcgq=1;//一个周期
                        break;
                    case dir_down://现在在下面
                        fun_motors(mot_hz,-100);//反转
                        loc_hzcgq=1;//一个周期
                        break;
                    case dir_left://现在在左面
                        fun_motors(mot_hz,100);//正转
                        loc_hzcgq=2;//俩周期
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }//选择需要的运动周期
        loc_hzdelay=var_timer+1000;//回转传感器隔1秒检测
    }//启动回转电机
    if(par_sjmodel!=str_begin.sjwz){//如果不在位
        fun_motors(mot_sj,par_sjmodel<str_begin.sjwz?100:-100);//通过高度计算并启动正反转
        loc_sjcgq=1;//标志位记录为等待传感器
    }//启动升降电机
    while(str_begin.hzsd!=0||str_begin.sjsd!=0){//非阻塞型Main函数循环检测
        if(loc_sjcgq==1){//如果还没到传感器
            switch(par_sjmodel){
                case sjp_1:
                    def_select(sel_58);//片选58传感器
                    fun_delay(20,del_us);//延时20us,给片选芯片一段时间切换
                    if(in_wz1==0){//如果第一个传感器有信号
                        loc_sjdelay=var_timer+str_cod.sj1bzw;//通过定时器全局时间标志位计算标准位延时
                        loc_sjcgq=2;//标志位记录已到传感器
                    }
                    break;
                case sjp_12:
                    def_select(sel_58);//片选58传感器
                    fun_delay(20,del_us);//延时20us,给片选芯片一段时间切换
                    if(str_begin.sjwz==sjp_1||in_wz2==0){//如果开始的时候时在位置1或已经到了位置2
                        loc_sjdelay=var_timer+str_cod.sj1zjw;//通过定时器全局时间标志位计算中间位延时
                        loc_sjcgq=2;//标志位记录已到传感器
                    }
                    break;
                case sjp_2:
                    def_select(sel_58);//片选58传感器
                    fun_delay(20,del_us);//延时20us,给片选芯片一段时间切换
                    if(in_wz2==0){//如果第二个传感器有信号
                        loc_sjdelay=var_timer+str_cod.sj1bzw;//通过定时器全局时间标志位计算标准位延时
                        loc_sjcgq=2;//标志位记录已到传感器
                    }
                    break;
                case sjp_23:
                    def_select(sel_58);//片选58传感器
                    fun_delay(20,del_us);//延时20us,给片选芯片一段时间切换
                    if(in_wz2==0||in_wz3==0){//如果已经到了位置2或已经到了位置3
                        loc_sjdelay=var_timer+str_cod.sj1zjw;//通过定时器全局时间标志位计算中间位延时
                        loc_sjcgq=2;//标志位记录已到传感器
                    }
                    break;
                case sjp_3:
                    def_select(sel_58);//片选58传感器
                    fun_delay(20,del_us);//延时20us,给片选芯片一段时间切换
                    if(in_wz3==0){//如果第三个传感器有信号
                        loc_sjdelay=var_timer+str_cod.sj1bzw;//通过定时器全局时间标志位计算标准位延时
                        loc_sjcgq=2;//标志位记录已到传感器
                    }
                    break;
                case sjp_34:
                    def_select(sel_58);//片选58传感器
                    fun_delay(20,del_us);//延时20us,给片选芯片一段时间切换
                    if(in_wz3==0||in_wz4==0){//如果已经到了位置3或已经到了位置4
                        loc_sjdelay=var_timer+str_cod.sj1zjw;//通过定时器全局时间标志位计算中间位延时
                        loc_sjcgq=2;//标志位记录已到传感器
                    }
                    break;
                case sjp_4:
                    def_select(sel_58);//片选58传感器
                    fun_delay(20,del_us);//延时20us,给片选芯片一段时间切换
                    if(in_wz4==0){//如果第四个传感器有信号
                        loc_sjdelay=var_timer+str_cod.sj1bzw;//通过定时器全局时间标志位计算标准位延时
                        loc_sjcgq=2;//标志位记录已到传感器
                    }
                    break;
                case sjp_45:
                    def_select(sel_58);//片选58传感器
                    fun_delay(20,del_us);//延时20us,给片选芯片一段时间切换
                    if(in_wz4==0||str_begin.sjwz==sjp_5){//如果已经到了位置4或开始的时候时在位置5
                        loc_sjdelay=var_timer+str_cod.sj1zjw;//通过定时器全局时间标志位计算中间位延时
                        loc_sjcgq=2;//标志位记录已到传感器
                    }
                    break;
                case sjp_5:
                    def_select(sel_912);//片选912传感器
                    fun_delay(20,del_us);//延时20us,给片选芯片一段时间切换
                    if(in_wz5==0){//如果第五个传感器有信号
                        loc_sjdelay=var_timer+str_cod.sj1bzw;//通过定时器全局时间标志位计算标准位延时
                        loc_sjcgq=2;//标志位记录已到传感器
                    }
                    break;
                default:
                    break;
            }
        }
        else if(loc_sjcgq==2){//如果延时时间到
            if(loc_sjdelay<=var_timer){
                fun_motors(mot_sj,0);//停止电机
                loc_sjcgq=0;//不做升降了
                str_begin.sjwz=par_sjmodel;//存储运行结果
            }
        }//已经到了传感器需要延时
        if(loc_hzdelay<=var_timer){//如果1秒延时已经过去
            if(loc_hzcgq!=0){//如果不是转0圈
                def_select(sel_912);//传感器片选
                fun_delay(20,del_us);//延时20us,给片选芯片一段时间切换
                if(in_hz==1){//如果传感器没亮
                    loc_hzflag=1;//标志位变1
                }
                else if(loc_hzflag==1){//如果标志位为1且传感器有信号
                    loc_hzcgq--;//算一个周期完成
                    loc_hzflag=0;//标志位变0
                }
            }
            else{//如果圈数为0
                fun_motors(mot_hz,0);//停止电机
                loc_hzdelay=0xFFFF;//不做回转了
                str_begin.hzfx=par_hzmodel;//存储运行结果
            }
        }
    }
}//升降回转同步运动
void fun_pysjhz(enum varENU_tra par_pymodel,enum varENU_tra par_sjmodel,enum varENU_dir par_hzmodel){
    ;
}
void fun_jtjp(){
    while(1){//循环纠偏
        if((!in_ls1&&!in_ls2&&in_ls4&&in_ls5&&!in_ls7&&!in_ls8)&&((in_ls3&&in_ls6)||(!in_ls3&&!in_ls6))){
            fun_delay(10,del_ms);
            fun_motors(mot_rl,0);
            return;
        }//1278不亮,45亮,36要么一起亮要么一起灭
        if(in_ls2||in_ls1){
            fun_motors(mot_l,16);
            fun_motors(mot_r,-16);
        }//12亮
        else if(in_ls7||in_ls8){
            fun_motors(mot_l,-16);
            fun_motors(mot_r,16);
        }//78亮
        else{
            if(!in_ls4){
                fun_motors(mot_l,-12);
                fun_motors(mot_r,12);
            }//4不亮
            else if(!in_ls5){
                fun_motors(mot_l,12);
                fun_motors(mot_r,-12);
            }//4亮5不亮
            else{
                if(in_ls6&&!in_ls3){//6亮3不亮
                    fun_motors(mot_l,-8);
                    fun_motors(mot_r,8);
                }
                if(in_ls3&&!in_ls6){//3亮6不亮
                    fun_motors(mot_l,8);
                    fun_motors(mot_r,-8);
                }
            }
        }
    }
}//静态纠偏
void fun_timermove(){
    static data uc loc_con=0;//需要分步做的动作需要用到此静态私有分步标志位
    data int loc_sdl,loc_sdr;//左轮速度和右轮速度的局部变量
    switch(*str_tfl.run){//选择运行方式
        case def_end://运行结束
            fun_motorsrl(mot_rl,0);//再次停止电机运动
            str_tfl.doing=tf_false;//移动结束
            memset(str_tfl.step,0,sizeof(str_tfl.step));//清空step数组
            str_tfl.run=str_tfl.step;//指针指向step的第一个元素
            break;
        case tfl_line://运行巡线
            if(*(str_tfl.run+1)){//如果参数为非0数
                if((in_ls1||in_ls8)&&(in_ls2&&in_ls3&&in_ls4&&in_ls5&in_ls6&&in_ls7)){//如果中间6个灯全亮,左右亮任意一个
                    str_tfl.online=tf_ture;//标志位记录在线
                    fun_motorsrl(mot_rl,str_tfl.gospeed);//按照常规速度过线
                }
                else if(str_tfl.online==tf_ture){//如果标志位记录在线,而且不符合在线特征
                    str_tfl.online=tf_false;//标志位记录不在线
                    (*(str_tfl.run+1))--;//参数值减1,记录已经走了一条线
                }
                else{
                    loc_sdl=loc_sdr=str_tfl.gospeed;//巡线速度为str_tfl.gospeed
                    if(in_ls3&&!in_ls6){//3亮6不亮
                        loc_sdl-=loc_sdl/10;
                        loc_sdr+=(100-loc_sdr)/10;
                    }//向左转
                    if(in_ls6&&!in_ls3){//6亮3不亮
                        loc_sdl+=(100-loc_sdl)/10;
                        loc_sdr-=loc_sdr/10;
                    }//向右转
                    if(in_ls2&&!in_ls7){//2亮7不亮
                        loc_sdl-=loc_sdl/10*3;
                        loc_sdr+=(100-loc_sdr)/10*3;
                    }//向左转
                    if(in_ls7&&!in_ls2){//7亮2不亮
                        loc_sdl+=(100-loc_sdl)/10*3;
                        loc_sdr-=loc_sdr/10*3;
                    }//向右转
                    if(in_ls1&&!in_ls8){//1亮8不亮
                        loc_sdl-=loc_sdl/10*5;
                        loc_sdr+=(100-loc_sdr)/10*5;
                    }//向左转
                    if(in_ls8&&!in_ls1){//8亮1不亮
                        loc_sdl+=(100-loc_sdl)/10*5;
                        loc_sdr-=loc_sdr/10*5;
                    }//向右转
                    fun_motorsrl(mot_r,loc_sdr);
                    fun_motorsrl(mot_l,loc_sdl);
                }
            }
            else{//如果线走完了
                str_tfl.run+=2;//指针指向下一组过程
                fun_motorsrl(mot_rl,0);//停止电机运动
            }
            break;
        case tfl_turn://运行转弯
            switch(loc_con){//分步运行标志位
                case 0://第一步
                    switch(*(str_tfl.run+1)){//获取参数
                        case tur_r90://右转90
                            fun_motorsrl(mot_l,str_tfl.turnspeed);//左轮向前
                            fun_motorsrl(mot_r,-str_tfl.turnspeed);//右轮向后
                            str_tfl.delay=var_timer+str_cod.turn90;//计时
                            break;
                        case tur_l90://左转90
                            fun_motorsrl(mot_l,-str_tfl.turnspeed);//左轮向后
                            fun_motorsrl(mot_r,str_tfl.turnspeed);//右轮向前
                            str_tfl.delay=var_timer+str_cod.turn90;//计时
                            break;
                        case tur_r180://右转180
                            fun_motorsrl(mot_l,str_tfl.turnspeed);//左轮向前
                            fun_motorsrl(mot_r,-str_tfl.turnspeed);//右轮向后
                            str_tfl.delay=var_timer+str_cod.turn180;//计时
                            break;
                        case tur_l180://左转180
                            fun_motorsrl(mot_l,-str_tfl.turnspeed);//左轮向后
                            fun_motorsrl(mot_r,str_tfl.turnspeed);//左轮向前
                            str_tfl.delay=var_timer+str_cod.turn180;//计时
                            break;
                    }
                    loc_con++;//执行下一步
                    break;
                case 1://第二步
                    if(str_tfl.delay<=var_timer)//计时时间到
                        loc_con++;//执行下一步
                    break;
                case 2://第三步
                    if(in_ls3||in_ls6){//如果中间两个灯亮
                        fun_motorsrl(mot_rl,0);//停止电机
                        str_tfl.run+=2;//指针指向下一组过程
                        str_tfl.delay=0;//延时计数器归零
                        loc_con=0;//分步运行标志位归零
                    }
                    break;
            }
            break;
        case tfl_cache://运行前冲
            switch(loc_con){
                case 0://第一步
                    str_tfl.delay=var_timer+((*(str_tfl.run+1))*10);//延时时间(毫秒)为参数的10倍
                    loc_con++;//执行下一步
                    break;
                case 1://第二步
                    if(str_tfl.delay<=var_timer){//计时时间到
                        fun_motorsrl(mot_rl,0);//停止电机
                        str_tfl.run+=2;//指针指向下一组过程
                        str_tfl.delay=0;//延时计数器归零
                        loc_con=0;//分步运行标志位归零
                    }
                    else{
                        loc_sdl=loc_sdr=str_tfl.cachespeed;//前冲速度为str_tfl.cachespeed
                        if(in_ls1&&!in_ls8){//1亮8不亮
                            loc_sdl*=0.7;//左减速
                            loc_sdr*=1.3;//右加速
                        }//向左转
                        if(in_ls8&&!in_ls1){//8亮1不亮
                            loc_sdl*=1.3;//左加速
                            loc_sdr*=0.7;//右减速
                        }//向右转
                        if(in_ls2&&!in_ls7){//2亮7不亮
                            loc_sdl*=0.8;//左减速
                            loc_sdr*=1.2;//右加速
                        }//向左转
                        if(in_ls7&&!in_ls2){//7亮2不亮
                            loc_sdl*=1.2;//左加速
                            loc_sdr*=0.8;//右减速
                        }//向右转
                        if(in_ls3&&!in_ls6){//3亮6不亮
                            loc_sdl*=0.9;//左减速
                            loc_sdr*=1.1;//右加速
                        }//向左转
                        if(in_ls6&&!in_ls3){//6亮3不亮
                            loc_sdl*=1.1;//左加速
                            loc_sdr*=0.9;//右减速
                        }//向右转
                        fun_motorsrl(mot_r,loc_sdr);
                        fun_motorsrl(mot_l,loc_sdl);
                    }
                    break;
            }
            break;
        default:
            break;
    }
}//定时器移动
void fun_flsetting(char par_gospeed,char par_turnspeed,char par_cachespeed,...){
    va_list loc_argp;//保存参数结构
    uc loc_step=0;//循环step数组用的东西
    uc loc_con;//当前参数
    va_start(loc_argp,par_cachespeed);//loc_argp指向传入的第一个可选参数,par_cachespeed是最后一个确定的参数
    loc_con=va_arg(loc_argp,char);//取出第一个参数
    while(loc_con!=def_end){
        str_tfl.step[loc_step++]=loc_con;//把给step数组,标志位+1
        loc_con=va_arg(loc_argp,char);//取出下一个参数
    }
    str_tfl.step[loc_step]=def_end;//step数组结束标志位
    va_end(loc_argp);//结束

    str_tfl.online=tf_false;//不在线
    str_tfl.run=str_tfl.step;//指针指向第一个数组
    str_tfl.gospeed=par_gospeed;//默认速度
    str_tfl.turnspeed=par_turnspeed;//拐弯速度
    str_tfl.cachespeed=par_cachespeed;//前冲速度
    str_tfl.doing=tf_ture;//开始做
}//主函数用定时器巡线调用函数
void fun_folline(uc par_con,uc par_speed){
    uc loc_con=par_con;//巡线条数标志位
    uc loc_sdr,loc_sdl;//左右轮速度
    uc loc_online;//在线标志位
    while(loc_con){
        if((in_ls1||in_ls8)&&(in_ls2&&in_ls3&&in_ls4&&in_ls5&in_ls6&&in_ls7)){//如果中间6个灯全亮,左右亮任意一个
            loc_online=tf_ture;//标志位记录在线
            fun_motors(mot_rl,par_speed);//按照常规速度过线
        }
        else if(loc_online==tf_ture){//如果标志位记录在线,而且不符合在线特征
            loc_online=tf_false;//标志位记录不在线
            loc_con--;//参数值减1,记录已经走了一条线
        }
        else{
            loc_sdr=loc_sdl=par_speed;
            if(in_ls3&&!in_ls6){//3亮6不亮
                loc_sdl-=loc_sdl/10;
                loc_sdr+=(100-loc_sdr)/10;
            }//向左转
            if(in_ls6&&!in_ls3){//6亮3不亮
                loc_sdl+=(100-loc_sdl)/10;
                loc_sdr-=loc_sdr/10;
            }//向右转
            if(in_ls2&&!in_ls7){//2亮7不亮
                loc_sdl-=loc_sdl/10*3;
                loc_sdr+=(100-loc_sdr)/10*3;
            }//向左转
            if(in_ls7&&!in_ls2){//7亮2不亮
                loc_sdl+=(100-loc_sdl)/10*3;
                loc_sdr-=loc_sdr/10*3;
            }//向右转
            if(in_ls1&&!in_ls8){//1亮8不亮
                loc_sdl-=loc_sdl/10*5;
                loc_sdr+=(100-loc_sdr)/10*5;
            }//向左转
            if(in_ls8&&!in_ls1){//8亮1不亮
                loc_sdl+=(100-loc_sdl)/10*5;
                loc_sdr-=loc_sdr/10*5;
            }//向右转
            fun_motors(mot_r,loc_sdr);
            fun_motors(mot_l,loc_sdl);
            fun_delay(1,del_ms);
        }
    }//如果巡线条数不为0
    fun_qc(60,40);//前冲
}//主函数巡线
void fun_turn(enum varENU_tur par_model,uc par_speed){
    switch(par_model){//获取参数
        case tur_r90://右转90
            fun_motors(mot_l,par_speed);//左轮向前
            fun_motors(mot_r,-par_speed);//右轮向后
            fun_delay(str_cod.turn90,del_ms);//计时
            break;
        case tur_l90://左转90
            fun_motors(mot_l,-par_speed);//左轮向后
            fun_motors(mot_r,par_speed);//右轮向前
            fun_delay(str_cod.turn90,del_ms);//计时
            break;
        case tur_r180://右转180
            fun_motors(mot_l,par_speed);//左轮向前
            fun_motors(mot_r,-par_speed);//右轮向后
            fun_delay(str_cod.turn180,del_ms);//计时
            break;
        case tur_l180://左转180
            fun_motors(mot_l,-par_speed);//左轮向后
            fun_motors(mot_r,par_speed);//左轮向前
            fun_delay(str_cod.turn180,del_ms);//计时
            break;
    }
    while(!in_ls4||!in_ls5);
    fun_motors(mot_rl,0);//停止电机
}//主函数转弯
void fun_qc(uc par_time,uc par_speed){
    uc loc_sdr,loc_sdl;//左右轮速度
    str_tfl.delay=var_timer+par_time*10;//延时时间(毫秒)为参数的10倍
    while(str_tfl.delay>var_timer){
        loc_sdr=loc_sdl=par_speed;
        if(in_ls1&&!in_ls8){//1亮8不亮
            loc_sdl*=0.7;//左减速
            loc_sdr*=1.3;//右加速
        }//向左转
        if(in_ls8&&!in_ls1){//8亮1不亮
            loc_sdl*=1.3;//左加速
            loc_sdr*=0.7;//右减速
        }//向右转
        if(in_ls2&&!in_ls7){//2亮7不亮
            loc_sdl*=0.8;//左减速
            loc_sdr*=1.2;//右加速
        }//向左转
        if(in_ls7&&!in_ls2){//7亮2不亮
            loc_sdl*=1.2;//左加速
            loc_sdr*=0.8;//右减速
        }//向右转
        if(in_ls3&&!in_ls6){//3亮6不亮
            loc_sdl*=0.9;//左减速
            loc_sdr*=1.1;//右加速
        }//向左转
        if(in_ls6&&!in_ls3){//6亮3不亮
            loc_sdl*=1.1;//左加速
            loc_sdr*=0.9;//右减速
        }//向右转
        fun_motors(mot_r,loc_sdr);
        fun_motors(mot_l,loc_sdl);
        fun_delay(1,del_ms);
    }
    fun_motors(mot_rl,0);//停止电机
}//主函数前冲
void fun_stope2prom(){
    IAP_CONTR = 0;                  //关闭IAP功能
    IAP_CMD = 0;                    //清除命令
    IAP_TRIG = 0;                   //清除触发寄存器
    IAP_ADDRH = 0x80;               //数据指针指向非EEPROM区
    IAP_ADDRL = 0;                  //清除IAP地址
}//关闭EEPROM功能(IapIdle)
uc fun_reade2prom(ui par_add){
    uc loc_dat;                     //数据缓冲区
    IAP_CONTR = 0x83;               //打开EEPROM功能,设置等待时间
    IAP_CMD = 1;                    //设置EEPROM读命令
    IAP_ADDRL = par_add;            //设置EEPROM地址低八位
    IAP_ADDRH = par_add >> 8;       //设置EEPROM地址高八位
    IAP_TRIG = 0x5a;                //触发
    IAP_TRIG = 0xa5;                //再次触发
    fun_delay(10,del_us);           //稍等一会儿
    loc_dat = IAP_DATA;             //读出EEPROM中的数据
    fun_stope2prom();               //关闭EEPROM功能
    return loc_dat;                 //返回读取结果
}//读取EEPROM数据
void fun_writee2prom(ui par_add,uc par_dat){
    IAP_CONTR = 0x83;               //打开EEPROM功能,设置等待时间
    IAP_CMD = 2;                    //设置EEPROM写入命令
    IAP_ADDRL = par_add;            //设置EEPROM地址低八位
    IAP_ADDRH = par_add >> 8;       //设置EEPROM地址高八位
    IAP_DATA = par_dat;             //写入数据
    IAP_TRIG = 0x5a;                //触发
    IAP_TRIG = 0xa5;                //再次触发
    fun_delay(10,del_us);           //稍等一会儿
    fun_stope2prom();               //关闭EEPROM功能
}//写EEPROM数据
void fun_cleane2prom(ui par_add){
    IAP_CONTR = 0x83;               //打开EEPROM功能,设置等待时间
    IAP_CMD = 3;                    //设置EEPROM擦除命令
    IAP_ADDRL = par_add;            //设置EEPROM地址低八位
    IAP_ADDRH = par_add >> 8;       //设置EEPROM地址高八位
    IAP_TRIG = 0x5a;                //触发
    IAP_TRIG = 0xa5;                //再次触发
    fun_delay(10,del_us);           //稍等一会儿
    fun_stope2prom();               //关闭EEPROM功能
}//清除EEPROM数据
void fun_calibration(){
    // fun_sj(sjp_1);//升到最上位
    ul loc_time;
    fun_py(tra_q);//移动到最前端
    fun_py(tra_h);//移动到最后端
    loc_time=var_timer;
    fun_py(tra_q);//移动到前端并计时
    fun_py(tra_h);//移动到后端
    loc_time=var_timer-loc_time;
    loc_time*=0.5;
    str_cod.py1zh=loc_time*0.5;//从后到中间
    str_cod.py1qz=loc_time*0.5;//从前到中间
    str_cod.py1qkh=loc_time*0.75;//从前到靠后
    str_cod.py1kqh=loc_time*0.564;//从靠前到后
    str_cod.py1qkq=loc_time*0.34;//从前到靠前
    str_cod.py1khh=loc_time*0.2701;//从后到靠后
    str_cod.py1kqz=loc_time*0.189;//从靠前到中间
    str_cod.py1zkh=loc_time*0.20;//从靠后到中间
    str_cod.py1kqkh=loc_time*0.5;//从靠前到靠后
    str_cod.py1khkq=loc_time*0.5;//从靠后到靠前
}//自动校准平移参数
void fun_port(){
    //19200bps@12.000MHz
    PCON |= 0x80;       //使能波特率倍速位SMOD
    SCON = 0x50;        //8位数据,可变波特率
    AUXR |= 0x04;       //独立波特率发生器时钟为Fosc,即1T
    BRT = 0xD9;         //设定独立波特率发生器重装值
    AUXR |= 0x01;       //串口1选择独立波特率发生器为波特率发生器
    AUXR |= 0x10;       //启动独立波特率发生器
}//串口初始化
void fun_test(){
    fun_sz(han_j);
    fun_delay(1,del_s);
    fun_sz(han_s);
    fun_delay(1,del_s);
    fun_sz(han_j);
    fun_delay(1,del_s);
    fun_sz(han_s);
    fun_delay(1,del_s);

    str_begin.pywz=tra_h;
    fun_py(tra_q);
    fun_delay(1,del_s);
    fun_py(tra_h);
    fun_delay(1,del_s);
    fun_py(tra_q);
    fun_delay(1,del_s);
    fun_py(tra_h);
    fun_delay(1,del_s);

    fun_sj(sjp_1);
    fun_delay(1,del_s);
    fun_sj(sjp_2);
    fun_delay(1,del_s);
    fun_sj(sjp_3);
    fun_delay(1,del_s);
    fun_sj(sjp_4);
    fun_delay(1,del_s);
    fun_sj(sjp_5);
    fun_delay(1,del_s);
    fun_sj(sjp_4);
    fun_delay(1,del_s);
    fun_sj(sjp_3);
    fun_delay(1,del_s);
    fun_sj(sjp_2);
    fun_delay(1,del_s);
    fun_sj(sjp_1);

    str_now.hzfx=str_begin.hzfx;
    str_begin.hzfx=dir_up;
    fun_hz(dir_right);
    fun_delay(1,del_s);
    fun_hz(dir_up);
    fun_delay(1,del_s);
    fun_hz(dir_right);
    fun_delay(1,del_s);
    fun_hz(dir_up);
    fun_delay(1,del_s);
    str_begin.hzfx=str_now.hzfx;

    fun_motors(mot_rl,60);
    fun_delay(1,del_s);
    fun_motors(mot_rl,0);
    fun_delay(1,del_s);

    fun_motors(mot_rl,-60);
    fun_delay(1,del_s);
    fun_motors(mot_rl,0);
    fun_delay(1,del_s);

    fun_motors(mot_r,40);
    fun_motors(mot_l,-40);
    fun_delay(1,del_s);
    fun_motors(mot_rl,0);
    fun_delay(1,del_s);

    fun_motors(mot_r,-40);
    fun_motors(mot_l,40);
    fun_delay(1,del_s);
    fun_motors(mot_rl,0);
}//测试程序
uc fun_min(uc par_num,...){
    va_list loc_argp;//保存参数结构
    uc loc_min=par_num;//现在的最小值就是第一个
    uc loc_shu;//当前参数
    va_start(loc_argp,par_num);//loc_argp指向传入的第一个可选参数，par_num是最后一个确定的参数
    loc_shu=va_arg(loc_argp,uc);//取出下一个参数
    do{
        if(loc_shu<loc_min)
            loc_min=loc_shu;
        loc_shu=va_arg(loc_argp,uc);//取出下一个参数
    }while(loc_shu!=def_end);
    va_end(loc_argp);//结束
    return loc_min;//退出
}//求最小值
void fun_coordinate(){
    
}//自动巡线之坐标
void fun_findtop(){
    uc loc_xh1,loc_xh2,loc_con=0;
    for(loc_xh1=0;loc_xh1<4;loc_xh1++)
        for(loc_xh2=0;loc_xh2<8;loc_xh2++)
            loc_con+=cabs(var_gjt[loc_xh1][loc_xh2]);
    var_top=15-loc_con;
}//
void fun_zdzj(ul par_04,ul par_37){//ul型数据,一次输入所有结果,无需等待
    struct str_zdzj str_pass,str_end;//str_zdzj(自动抓件)的结构体:现在的数据和结束时得到的结果
    char loc_high[8];         //每摞工件的高度
    uc loc_xh1;             //第一个循环

    memset(str_pass.jx,0,sizeof(str_pass.jx));//清空现在件序
    memset(str_end.jx,0,sizeof(str_end.jx)); //清空想要的件序
    memset(loc_high,5,sizeof(loc_high));     //每组高度置5(没有件)

    //起始区件号
    str_pass.jx[0][1]=(par_04/10000000)%10;  //传入现在件序:区0的第1号件件号(最高位)
    str_pass.jx[0][2]=(par_04/1000000)%10;   //传入现在件序:区0的第2号件件号
    str_pass.jx[0][3]=(par_04/100000)%10;    //传入现在件序:区0的第3号件件号
    str_pass.jx[0][4]=(par_04/10000)%10;     //传入现在件序:区0的第4号件件号(最低位)
    str_pass.jx[4][1]=(par_04/1000)%10;      //传入现在件序:区4的第1号件件号(最高位)
    str_pass.jx[4][2]=(par_04/100)%10;       //传入现在件序:区4的第2号件件号
    str_pass.jx[4][3]=(par_04/10)%10;        //传入现在件序:区4的第3号件件号
    str_pass.jx[4][4]=par_04%10;             //传入现在件序:区4的第4号件件号(最低位)
    //目的区件号
    str_pass.jx[3][1]=(par_37/10000000)%10;  //传入现在件序:区0的第1号件件号(最高位)
    str_pass.jx[3][2]=(par_37/1000000)%10;   //传入现在件序:区0的第2号件件号
    str_pass.jx[3][3]=(par_37/100000)%10;    //传入现在件序:区0的第3号件件号
    str_pass.jx[3][4]=(par_37/10000)%10;     //传入现在件序:区0的第4号件件号(最低位)
    str_pass.jx[7][1]=(par_37/1000)%10;      //传入现在件序:区4的第1号件件号(最高位)
    str_pass.jx[7][2]=(par_37/100)%10;       //传入现在件序:区4的第2号件件号
    str_pass.jx[7][3]=(par_37/10)%10;        //传入现在件序:区4的第3号件件号
    str_pass.jx[7][4]=par_37%10;             //传入现在件序:区4的第4号件件号(最低位)
    //目的次序
    str_end.jx[3][1]=1;                      //标准目标次序:区3的第1号目的次序号(最高位)
    str_end.jx[3][2]=2;                      //标准目标次序:区3的第2号目的次序号
    str_end.jx[3][3]=3;                      //标准目标次序:区3的第3号目的次序号
    str_end.jx[3][4]=4;                      //标准目标次序:区3的第4号目的次序号(最低位)
    str_end.jx[7][1]=5;                      //标准目标次序:区7的第1号目的次序号(最高位)
    str_end.jx[7][2]=6;                      //标准目标次序:区7的第2号目的次序号
    str_end.jx[7][3]=7;                      //标准目标次序:区7的第3号目的次序号
    str_end.jx[7][4]=8;                      //标准目标次序:区7的第4号目的次序号(最低位)

    for(loc_xh1=1;loc_xh1<=4;loc_xh1++){
        if((str_pass.jx[0][loc_xh1]==str_pass.jx[3][1])&&(str_pass.jx[0][loc_xh1]!=0))
            str_end.jx[0][loc_xh1]=str_end.jx[3][1];
        else if((str_pass.jx[0][loc_xh1]==str_pass.jx[3][2])&&(str_pass.jx[0][loc_xh1]!=0))
            str_end.jx[0][loc_xh1]=str_end.jx[3][2];
        else if((str_pass.jx[0][loc_xh1]==str_pass.jx[3][3])&&(str_pass.jx[0][loc_xh1]!=0))
            str_end.jx[0][loc_xh1]=str_end.jx[3][3];
        else if((str_pass.jx[0][loc_xh1]==str_pass.jx[3][4])&&(str_pass.jx[0][loc_xh1]!=0))
            str_end.jx[0][loc_xh1]=str_end.jx[3][4];
        else if((str_pass.jx[0][loc_xh1]==str_pass.jx[7][1])&&(str_pass.jx[0][loc_xh1]!=0))
            str_end.jx[0][loc_xh1]=str_end.jx[7][1];
        else if((str_pass.jx[0][loc_xh1]==str_pass.jx[7][2])&&(str_pass.jx[0][loc_xh1]!=0))
            str_end.jx[0][loc_xh1]=str_end.jx[7][2];
        else if((str_pass.jx[0][loc_xh1]==str_pass.jx[7][3])&&(str_pass.jx[0][loc_xh1]!=0))
            str_end.jx[0][loc_xh1]=str_end.jx[7][3];
        else if((str_pass.jx[0][loc_xh1]==str_pass.jx[7][4])&&(str_pass.jx[0][loc_xh1]!=0))
            str_end.jx[0][loc_xh1]=str_end.jx[7][4];

        if((str_pass.jx[4][loc_xh1]==str_pass.jx[3][1])&&(str_pass.jx[4][loc_xh1]!=0))
            str_end.jx[4][loc_xh1]=str_end.jx[3][1];
        else if((str_pass.jx[4][loc_xh1]==str_pass.jx[3][2])&&(str_pass.jx[4][loc_xh1]!=0))
            str_end.jx[4][loc_xh1]=str_end.jx[3][2];
        else if((str_pass.jx[4][loc_xh1]==str_pass.jx[3][3])&&(str_pass.jx[4][loc_xh1]!=0))
            str_end.jx[4][loc_xh1]=str_end.jx[3][3];
        else if((str_pass.jx[4][loc_xh1]==str_pass.jx[3][4])&&(str_pass.jx[4][loc_xh1]!=0))
            str_end.jx[4][loc_xh1]=str_end.jx[3][4];
        else if((str_pass.jx[4][loc_xh1]==str_pass.jx[7][1])&&(str_pass.jx[4][loc_xh1]!=0))
            str_end.jx[4][loc_xh1]=str_end.jx[7][1];
        else if((str_pass.jx[4][loc_xh1]==str_pass.jx[7][2])&&(str_pass.jx[4][loc_xh1]!=0))
            str_end.jx[4][loc_xh1]=str_end.jx[7][2];
        else if((str_pass.jx[4][loc_xh1]==str_pass.jx[7][3])&&(str_pass.jx[4][loc_xh1]!=0))
            str_end.jx[4][loc_xh1]=str_end.jx[7][3];
        else if((str_pass.jx[4][loc_xh1]==str_pass.jx[7][4])&&(str_pass.jx[4][loc_xh1]!=0))
            str_end.jx[4][loc_xh1]=str_end.jx[7][4];
    }//通过实际件序获得编号

    memset(str_pass.jx,0,sizeof(str_pass.jx));//清空现在实际件序
    for(loc_xh1=1;loc_xh1<=4;loc_xh1++){
        str_pass.jx[0][loc_xh1]=str_end.jx[0][loc_xh1];
        str_pass.jx[4][loc_xh1]=str_end.jx[4][loc_xh1];
    }//将现在的件序从str_end.jx中拿到str_pass.jx
    for(loc_xh1=1;loc_xh1<=4;loc_xh1++){
        str_end.jx[0][loc_xh1]=0;
        str_end.jx[4][loc_xh1]=0;
    }//删除str_end.jx中现在的件序
    loc_high[0]=loc_high[4]=1;//只有0号和4号放满了件
    loc_xh1=0;//循环标志位归零

    /*
        到目前为止准备工作结束,现在的数组中没有实际件序,
        现在的编号在str_pass.jx中,
        想要得到的结果件序编号在str_end.jx中
    */
    while(1){
        //退出条件
        if((str_pass.jx[3][1]==str_end.jx[3][1])&&
        (str_pass.jx[3][2]==str_end.jx[3][2])&&
        (str_pass.jx[3][3]==str_end.jx[3][3])&&
        (str_pass.jx[3][4]==str_end.jx[3][4])&&
        (str_pass.jx[7][1]==str_end.jx[7][1])&&
        (str_pass.jx[7][2]==str_end.jx[7][2])&&
        (str_pass.jx[7][3]==str_end.jx[7][3])&&
        (str_pass.jx[7][4]==str_end.jx[7][4])){
            if(str_begin.hzfx==dir_left){
                fun_sz(han_s);                 //手抓松
                fun_sj(sjp_1);                 //升降到最高位
                fun_zjzt(mot_pyhz,7);           //平面位置7
                fun_zjzt(mot_sj,loc_high[7]);   //升降到7的最高位
                fun_sz(han_j);                 //手抓紧
            }//如果停在左边
            return;
        }//如果小车一方的实际件序和想要达到的件序相等
        if(str_begin.hzfx==dir_left){
            //转向条件
            loc_xh1++;//标志位+1
            if(loc_xh1>=100){
                loc_xh1=0;
                fun_zjzt(mot_sj,fun_min(loc_high[0],loc_high[1],loc_high[2],loc_high[3],loc_high[4],loc_high[5],loc_high[6],loc_high[7],def_end)-1);
                fun_hz(dir_right);
            }
            //可以一次拿走,不需要中间位的
            if(loc_high[1]<5){
                if(str_pass.jx[1][loc_high[1]]==str_end.jx[3][loc_high[3]-1]){
                    fun_najian(1,3,loc_high,str_pass.jx);//1-->3
                    continue;
                }
            }//如果区1有件
            if(loc_high[2]<5){
                if(str_pass.jx[2][loc_high[2]]==str_end.jx[3][loc_high[3]-1]){
                    fun_najian(2,3,loc_high,str_pass.jx);//2-->3
                    continue;
                }
            }//如果区2有件
            if(loc_high[0]<5){
                if(str_pass.jx[0][loc_high[0]]==str_end.jx[3][loc_high[3]-1]){
                    fun_najian(0,3,loc_high,str_pass.jx);//0-->3
                    continue;
                }
                if(str_pass.jx[0][loc_high[0]]==str_end.jx[7][loc_high[7]-1]){
                    fun_najian(0,7,loc_high,str_pass.jx);//0-->7
                    continue;
                }
            }//如果区0有件

            //不可以一次拿走,需要中间位的
            if(loc_high[0]<5){
                if((str_pass.jx[0][loc_high[0]]==str_end.jx[3][1])||
                (str_pass.jx[0][loc_high[0]]==str_end.jx[3][2])||
                (str_pass.jx[0][loc_high[0]]==str_end.jx[3][3])||
                (str_pass.jx[0][loc_high[0]]==str_end.jx[3][4])){
                    if(((loc_high[1]==5)||//如果1区没放东西或者
                    (str_pass.jx[0][loc_high[0]]>str_pass.jx[1][loc_high[1]]))&&//0区的件编号大于1区的编号并且
                    (loc_high[1]>2)){//1区不能放超过2个件
                        fun_najian(0,1,loc_high,str_pass.jx);//0-->1
                        continue;
                    }
                    if(((loc_high[2]==5)||//如果2区没放东西或者
                    (str_pass.jx[0][loc_high[0]]>str_pass.jx[2][loc_high[2]]))&&//0区的件编号大于2区的编号并且
                    (loc_high[2]>2)){//2区不能放超过2个件
                        fun_najian(0,2,loc_high,str_pass.jx);//0-->2
                        continue;
                    }
                }//如果要放在3上,但目前不能放
                if((str_pass.jx[0][loc_high[0]]==str_end.jx[7][1])||
                (str_pass.jx[0][loc_high[0]]==str_end.jx[7][2])||
                (str_pass.jx[0][loc_high[0]]==str_end.jx[7][3])||
                (str_pass.jx[0][loc_high[0]]==str_end.jx[7][4])){
                    if(((loc_high[5]==5)||//如果5区没东西放或者
                    (str_pass.jx[0][loc_high[0]]>str_pass.jx[5][loc_high[5]]))&&//0区的件编号大于5区的编号并且
                    (loc_high[5]>2)){//5区不能放超过2个件
                        fun_najian(0,5,loc_high,str_pass.jx);//0-->5
                        continue;
                    }
                    if(((loc_high[6]==5)||//如果6区没东西放或者
                    (str_pass.jx[0][loc_high[0]]>str_pass.jx[6][loc_high[6]]))&&//0区的件编号大于6区的编号并且
                    (loc_high[6]>2)){//6区不能放超过2个件
                        fun_najian(0,6,loc_high,str_pass.jx);//0-->6
                        continue;
                    }
                }//如果要放在7上,但目前不能放
            }//如果区0有件

            //中间两个位置也不能一次搞定的
            if((loc_high[1]<5)&&(loc_high[2]<5)){
                if((str_pass.jx[1][loc_high[1]]>str_pass.jx[2][loc_high[2]])&&(loc_high[2]>1)){
                    fun_najian(1,2,loc_high,str_pass.jx);//1-->2
                    continue;
                }//1的件比2的件大且区2放了不到3个件
                if((str_pass.jx[2][loc_high[2]]>str_pass.jx[1][loc_high[1]])&&(loc_high[1]>1)){
                    fun_najian(2,1,loc_high,str_pass.jx);//2-->1
                    continue;
                }//2的件比1的件大且区1放了不到3个件
            }//如果区1和区2都有件

            //中间两个位置怎么也搞不定的
            if((loc_high[1]<5)&&(loc_high[2]<5)){
                if((loc_high[0]>1)&&(str_pass.jx[1][loc_high[1]]>str_pass.jx[0][loc_high[0]])){
                    fun_najian(1,0,loc_high,str_pass.jx);//1-->0
                    continue;
                }//1区的件比0区的大且0区放了不到3个件
                if((loc_high[0]>1)&&(str_pass.jx[2][loc_high[2]]>str_pass.jx[0][loc_high[0]])){
                    fun_najian(2,0,loc_high,str_pass.jx);//2-->0
                    continue;
                }//2区的件比0区的大且0区放了不到3个件
            }
        }//如果回转在左边 
        if(str_begin.hzfx==dir_right){
            //转向条件
            loc_xh1++;//标志位+1
            if(loc_xh1>=100){
                loc_xh1=0;
                fun_zjzt(mot_sj,fun_min(loc_high[0],loc_high[1],loc_high[2],loc_high[3],loc_high[4],loc_high[5],loc_high[6],loc_high[7],def_end)-1);
                fun_hz(dir_left);
            }
            //可以一次拿走,不需要中间位的
            if(loc_high[5]<5){
                if(str_pass.jx[5][loc_high[5]]==str_end.jx[7][loc_high[7]-1]){
                    fun_najian(5,7,loc_high,str_pass.jx);//5-->7
                    continue;
                }//5-->7
            }//如果区5有件
            if(loc_high[6]<5){
                if(str_pass.jx[6][loc_high[6]]==str_end.jx[7][loc_high[7]-1]){
                    fun_najian(6,7,loc_high,str_pass.jx);//6-->7
                    continue;
                }//6-->7
            }//如果区6有件
            if(loc_high[4]<5){
                if(str_pass.jx[4][loc_high[4]]==str_end.jx[7][loc_high[7]-1]){
                    fun_najian(4,7,loc_high,str_pass.jx);//4-->7
                    continue;
                }//4-->7
                if(str_pass.jx[4][loc_high[4]]==str_end.jx[3][loc_high[3]-1]){
                    fun_najian(4,3,loc_high,str_pass.jx);//4-->3
                    continue;
                }//4-->3
            }//如果区4有件

            //不可以一次拿走,需要中间位的
            if(loc_high[4]<5){
                if((str_pass.jx[4][loc_high[4]]==str_end.jx[7][1])||
                (str_pass.jx[4][loc_high[4]]==str_end.jx[7][2])||
                (str_pass.jx[4][loc_high[4]]==str_end.jx[7][3])||
                (str_pass.jx[4][loc_high[4]]==str_end.jx[7][4])){
                    if(((loc_high[5]==5)||//如果5区没东西放或者
                    (str_pass.jx[4][loc_high[4]]>str_pass.jx[5][loc_high[5]]))&&//4区的件编号大于5区的编号并且
                    (loc_high[5]>2)){//5区不能放超过2个件
                        fun_najian(4,5,loc_high,str_pass.jx);//4-->5
                        continue;
                    }
                    if(((loc_high[6]==5)||//如果6区没东西放或者
                    (str_pass.jx[4][loc_high[4]]>str_pass.jx[6][loc_high[6]]))&&//4区的件编号大于6区的编号并且
                    (loc_high[6]>2)){//6区不能放超过2个件
                        fun_najian(4,6,loc_high,str_pass.jx);//4-->6
                        continue;
                    }
                }//如果要放在7上,但目前不能放
                if((str_pass.jx[4][loc_high[4]]==str_end.jx[3][1])||
                (str_pass.jx[4][loc_high[4]]==str_end.jx[3][2])||
                (str_pass.jx[4][loc_high[4]]==str_end.jx[3][3])||
                (str_pass.jx[4][loc_high[4]]==str_end.jx[3][4])){
                    if(((loc_high[1]==5)||//如果1区没放东西或者
                    (str_pass.jx[4][loc_high[4]]>str_pass.jx[1][loc_high[1]]))&&//4区的件编号大于1区的编号并且
                    (loc_high[1]>2)){//1区不能放超过2个件
                        fun_najian(4,1,loc_high,str_pass.jx);//4-->1
                        continue;
                    }
                    if(((loc_high[2]==5)||//如果2区没放东西或者
                        (str_pass.jx[4][loc_high[4]]>str_pass.jx[2][loc_high[2]]))&&//4区的件编号大于2区的编号并且
                        (loc_high[2]>2)){//2区不能放超过2个件
                        fun_najian(4,2,loc_high,str_pass.jx);//4-->2
                        continue;
                    }
                }//如果要放在3上,但目前不能放
            }//如果区4有件

            //中间两个位置也不能一次搞定的
            if((loc_high[5]<5)&&(loc_high[6]<5)){
                if((str_pass.jx[5][loc_high[5]]>str_pass.jx[6][loc_high[6]])&&(loc_high[6]>1)){
                    fun_najian(5,6,loc_high,str_pass.jx);//5-->6
                    continue;
                }//5的件比6的件大且区6放了不到3个件
                if((str_pass.jx[6][loc_high[6]]>str_pass.jx[5][loc_high[5]])&&(loc_high[5]>1)){
                    fun_najian(6,5,loc_high,str_pass.jx);//6-->5
                    continue;
                }//6的件比5的件大且区5放了不到3个件
            }//如果区5和区6都有件

            //中间两个位置怎么也搞不定的
            if((loc_high[5]<5)&&(loc_high[6]<5)){
                if((loc_high[4]>1)&&(str_pass.jx[5][loc_high[5]]>str_pass.jx[4][loc_high[4]])){
                    fun_najian(5,4,loc_high,str_pass.jx);//5-->4
                    continue;
                }//5区的件比4区的大且4区放了不到3个件
                if((loc_high[4]>1)&&(str_pass.jx[6][loc_high[6]]>str_pass.jx[4][loc_high[4]])){
                    fun_najian(6,4,loc_high,str_pass.jx);//6-->4
                    continue;
                }//6区的件比4区的大且4区放了不到3个件
            }
        }//如果回转在右边
    }    
}//自动抓件
void fun_zjzt(uc par_motor,char par_model){
    if(par_motor==mot_pyhz){
        switch(par_model){
            case 0:
                if((str_begin.pywz==tra_h)&&(str_begin.hzfx==dir_left))
                    break;
                if(str_begin.hzfx==dir_right)
                    fun_pyhz(tra_z,dir_left);
                fun_py(tra_h);
                break;
            case 1:
                if((str_begin.pywz==tra_kh)&&(str_begin.hzfx==dir_left))
                    break;
                if(str_begin.hzfx==dir_right)
                    fun_pyhz(tra_z,dir_left);
                fun_py(tra_kh);
                break;
            case 2:
                if((str_begin.pywz==tra_kq)&&(str_begin.hzfx==dir_left))
                    break;
                if(str_begin.hzfx==dir_right)
                    fun_pyhz(tra_z,dir_left);
                fun_py(tra_kq);
                break;
            case 3:
                if((str_begin.pywz==tra_q)&&(str_begin.hzfx==dir_left))
                    break;
                if(str_begin.hzfx==dir_right)
                    fun_pyhz(tra_z,dir_left);
                fun_py(tra_q);
                break;
            case 4:
                if((str_begin.pywz==tra_q)&&(str_begin.hzfx==dir_right))
                    break;
                if(str_begin.hzfx==dir_left)
                    fun_pyhz(tra_z,dir_right);
                fun_py(tra_q);
                break;
            case 5:
                if((str_begin.pywz==tra_kq)&&(str_begin.hzfx==dir_right))
                    break;
                if(str_begin.hzfx==dir_left)
                    fun_pyhz(tra_z,dir_right);
                fun_py(tra_kq);
                break;
            case 6:
                if((str_begin.pywz==tra_kh)&&(str_begin.hzfx==dir_right))
                    break;
                if(str_begin.hzfx==dir_left)
                    fun_pyhz(tra_z,dir_right);
                fun_py(tra_kh);
                break;
            case 7:
                if((str_begin.pywz==tra_h)&&(str_begin.hzfx==dir_right))
                    break;
                if(str_begin.hzfx==dir_left)
                    fun_pyhz(tra_z,dir_right);
                fun_py(tra_h);
                break;
            default:
                break;
        }
    }
    else if(par_motor==mot_sj){
        switch(par_model){
            case 0:
                fun_sj(sjp_1);
                break;
            case 1:
                fun_sj(sjp_2);
                break;
            case 2:
                fun_sj(sjp_3);
                break;
            case 3:
                fun_sj(sjp_4);
                break;
            case 4:
                fun_sj(sjp_5);
                break;
            default:
                if(par_model<0)
                    fun_sj(sjp_1);
                else if(par_model>5)
                    fun_sj(sjp_5);
                break;
        }
    }
}//抓件状态,0为左上位,3为左下位,4为右上位,7为右下位
void fun_najian(uc par_now,uc par_next,char par_high[8],uc par_data[8][5]){
    #ifdef Debug
        printf("%d --> %d\n",(ui)par_now,(ui)par_next);
    #else
        //取各位置的最高位
        uc loc_high=fun_min(par_high[0],par_high[1],par_high[2],par_high[3],par_high[4],par_high[5],par_high[6],par_high[7],def_end);
        //升起
        if(par_now==0||par_now==1||par_now==2||par_now==3){
            if(str_begin.hzfx==dir_left)
                fun_zjzt(mot_sj,fun_min(par_high[0],par_high[1],par_high[2],par_high[3],def_end)-1);
            else if(str_begin.hzfx==dir_right)
                fun_zjzt(mot_sj,fun_min(par_high[0],par_high[1],par_high[2],par_high[3],par_high[4],par_high[5],par_high[6],par_high[7],def_end)-1);            
        }
        else if(par_now==4||par_now==5||par_now==6||par_now==7){
            if(str_begin.hzfx==dir_right)
                fun_zjzt(mot_sj,fun_min(par_high[4],par_high[5],par_high[6],par_high[7],def_end)-1);
            else if(str_begin.hzfx==dir_left)
                fun_zjzt(mot_sj,fun_min(par_high[0],par_high[1],par_high[2],par_high[3],par_high[4],par_high[5],par_high[6],par_high[7],def_end)-1);            
        }
        //平移回转到需要的地方
        fun_zjzt(mot_pyhz,par_now);
        //下降到工件的位置
        fun_zjzt(mot_sj,par_high[par_now]);
        //抓紧工件
        fun_sz(han_j);
        //上升到正确的最高位
        switch(par_now){
            case 0:
                switch(par_next){
                    case 1:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[par_next],def_end)-2);
                        break;
                    case 2:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[1],par_high[par_next],def_end)-2);
                        break;
                    case 3:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[1],par_high[2],par_high[par_next],def_end)-2);
                        break;
                    case 4:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[1],par_high[5],par_high[par_next],def_end)-2);
                        break;
                    case 5:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[1],par_high[par_next],def_end)-2);
                        break;
                    case 6:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[1],par_high[par_next],def_end)-2);
                        break;
                    case 7:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[1],par_high[6],par_high[par_next],def_end)-2);
                        break;
                    default:
                        break;
                }
                break;
            case 1:
                switch(par_next){
                    case 0:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[par_next],def_end)-2);
                        break;
                    case 2:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[par_next],def_end)-2);
                        break;
                    case 3:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[2],par_high[par_next],def_end)-2);
                        break;
                    case 4:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[5],par_high[par_next],def_end)-2);
                        break;
                    case 5:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[par_next],def_end)-2);
                        break;
                    case 6:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[par_next],def_end)-2);
                        break;
                    case 7:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[6],par_high[par_next],def_end)-2);
                        break;
                    default:
                        break;
                }
                break;
            case 2:
                switch(par_next){
                    case 0:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[1],par_high[par_next],def_end)-2);
                        break;
                    case 1:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[par_next],def_end)-2);
                        break;
                    case 3:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[par_next],def_end)-2);
                        break;
                    case 4:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[5],par_high[par_next],def_end)-2);
                        break;
                    case 5:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[par_next],def_end)-2);
                        break;
                    case 6:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[par_next],def_end)-2);
                        break;
                    case 7:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[6],par_high[par_next],def_end)-2);
                        break;
                    default:
                        break;
                }
                break;
            case 3:
                switch(par_next){
                    case 0:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[2],par_high[1],par_high[par_next],def_end)-2);
                        break;
                    case 1:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[2],par_high[par_next],def_end)-2);
                        break;
                    case 2:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[par_next],def_end)-2);
                        break;
                    case 4:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[2],par_high[5],par_high[par_next],def_end)-2);
                        break;
                    case 5:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[2],par_high[par_next],def_end)-2);
                        break;
                    case 6:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[2],par_high[par_next],def_end)-2);
                        break;
                    case 7:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[2],par_high[6],par_high[par_next],def_end)-2);
                        break;
                    default:
                        break;
                }
                break;
            case 4:
                switch(par_next){
                    case 0:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[5],par_high[1],par_high[par_next],def_end)-2);
                        break;
                    case 1:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[5],par_high[par_next],def_end)-2);
                        break;
                    case 2:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[5],par_high[par_next],def_end)-2);
                        break;
                    case 3:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[5],par_high[2],par_high[par_next],def_end)-2);
                        break;
                    case 5:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[par_next],def_end)-2);
                        break;
                    case 6:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[5],par_high[par_next],def_end)-2);
                        break;
                    case 7:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[5],par_high[6],par_high[par_next],def_end)-2);
                        break;
                    default:
                        break;
                }
                break;
            case 5:
                switch(par_next){
                    case 0:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[1],par_high[par_next],def_end)-2);
                        break;
                    case 1:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[par_next],def_end)-2);
                        break;
                    case 2:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[par_next],def_end)-2);
                        break;
                    case 3:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[2],par_high[par_next],def_end)-2);
                        break;
                    case 4:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[par_next],def_end)-2);
                        break;
                    case 6:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[par_next],def_end)-2);
                        break;
                    case 7:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[6],par_high[par_next],def_end)-2);
                        break;
                    default:
                        break;
                }
                break;
            case 6:
                switch(par_next){
                    case 0:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[1],par_high[par_next],def_end)-2);
                        break;
                    case 1:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[par_next],def_end)-2);
                        break;
                    case 2:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[par_next],def_end)-2);
                        break;
                    case 3:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[2],par_high[par_next],def_end)-2);
                        break;
                    case 4:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[5],par_high[par_next],def_end)-2);
                        break;
                    case 5:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[par_next],def_end)-2);
                        break;
                    case 7:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[par_next],def_end)-2);
                        break;
                    default:
                        break;
                }
                break;
            case 7:
                switch(par_next){
                    case 0:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[6],par_high[1],par_high[par_next],def_end)-2);
                        break;
                    case 1:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[6],par_high[par_next],def_end)-2);
                        break;
                    case 2:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[6],par_high[par_next],def_end)-2);
                        break;
                    case 3:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[6],par_high[2],par_high[par_next],def_end)-2);
                        break;
                    case 4:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[5],par_high[6],par_high[par_next],def_end)-2);
                        break;
                    case 5:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[6],par_high[par_next],def_end)-2);
                        break;
                    case 6:
                        fun_zjzt(mot_sj,fun_min(loc_high+2,par_high[par_now]+1,par_high[par_next],def_end)-2);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
        //平移回转至放件处
        fun_zjzt(mot_pyhz,par_next);
        //下降到要放下的位置
        fun_zjzt(mot_sj,par_high[par_next]-1);
        //松开手抓
        fun_sz(han_s);
    #endif

    //更新参数
    par_data[par_next][par_high[par_next]-1]=par_data[par_now][par_high[par_now]];
    par_data[par_now][par_high[par_now]]=0;
    par_high[par_now]++;
    par_high[par_next]--;
}//拿件(配合自动抓件使用)
void fun_zhuajian(){
    fun_sz(han_s);                 //手抓松
    fun_sj(sjp_1);                 //上升到最高位
    fun_py(tra_q);                 //平移到前端
    if(str_begin.hzfx!=dir_right)   //如果不在右边
        fun_hz(dir_right);         //就平移到右边

    fun_folline(2,60);
    fun_turn(tur_l90,40);
    fun_folline(1,60);
    fun_qc(100,40);
    while((!in_ls4||!in_ls5)||(in_ls1||in_ls2||in_ls3||in_ls6||in_ls7||in_ls8)){
        if(in_ls1||in_ls2||in_ls3||!in_ls5){
            fun_motors(mot_rl,-30);
            fun_delay(300,del_ms);
            fun_motors(mot_r,-20);
            fun_motors(mot_l,-30);
            fun_delay(300,del_ms);
            fun_motors(mot_rl,-30);
            fun_delay(300,del_ms);
        }//3亮或5不亮
        else if(in_ls6||in_ls7||in_ls8||!in_ls4){
            fun_motors(mot_rl,-30);
            fun_delay(300,del_ms);
            fun_motors(mot_r,-30);
            fun_motors(mot_l,-29);
            fun_delay(300,del_ms);
            fun_motors(mot_rl,-30);
            fun_delay(300,del_ms);
        }//6亮或4不亮
        fun_qc(150,40);//重新进行前冲
    }
    fun_motors(mot_rl,0);
}//从起始区走到抓件区
void fun_back(){
    fun_motors(mot_rl,-25);
    fun_delay(1,del_s);

    fun_motors(mot_r,-48);
    fun_motors(mot_l,-20);
    fun_delay(3,del_s);    

    fun_motors(mot_rl,-35);
    fun_delay(1,del_s);
}//从抓件区回到起始区
void fun_start(char par_x,char par_y,enum varENU_dir par_ctfx,
    enum varENU_han par_szzt,enum varENU_sjp par_sjwz,enum varENU_tra par_pywz,enum varENU_dir par_hzfx,
    uc par_1x,uc par_1y,char par_1,
    uc par_2x,uc par_2y,char par_2,
    uc par_3x,uc par_3y,char par_3,
    uc par_4x,uc par_4y,char par_4){
    CLK_DIV=0x00;             //不分频
    P0M1=0xff;                //P0用于输入
    P0M0=0x00;                //P0不能输出
    P1M1=0x00;                //P1口0-1双向
    P1M0=0xfc;                //P1口2-7输出
    P2M1=0xf0;                //P2口4-7输入
    P2M0=0x0f;                //P2口0-3输出

    out_en1=1;                //电机1/3使能
    out_en2=1;                //电机2/4使能
    CR=0;                     //PAC计数器归零
    out_motorselect=0;        //电机片选为0

    fun_port();               //初始化串口
    TI=1;                     //打开串口传输功能

    fun_pwminit();            //PWM的初始化

    fun_timer0init();         //初始化定时器0
    fun_timer1init();         //初始化定时器1
    TR0=1;                    //打开定时器0
    TR1=1;                    //打开定时器1
    var_timer=0;

    memset(str_tfl.step,0,sizeof(str_tfl.step));//清零巡线用步骤数组
    memset(var_gjt,0,sizeof(var_gjt));//清空工件台坐标
    var_top=0;
    var_gjt[par_1x][par_1y]=par_1;
    var_gjt[par_2x][par_2y]=par_2;
    var_gjt[par_3x][par_3y]=par_3;
    var_gjt[par_4x][par_4y]=par_4;
    fun_findtop();
    
    str_begin.x=par_x;        //X坐标
    str_begin.y=par_y;        //Y坐标
    str_begin.ctfx=par_ctfx;  //车头方向
    str_begin.szzt=par_szzt;  //手抓状态
    str_begin.sjwz=par_sjwz;  //升降位置
    str_begin.pywz=par_pywz;  //平移位置
    str_begin.hzfx=par_hzfx;  //回转方向

    str_tfl.gospeed=0;        //速度归零
    fun_motors(mot_sz,0);     //手抓速度归零
    fun_motors(mot_py,0);     //平移速度归零
    fun_motors(mot_sj,0);     //手抓速度归零
    fun_motors(mot_hz,0);     //手抓速度归零
    fun_motors(mot_rl,0);     //左右速度归零

    #ifdef Debug              //如果开启调试模式
        fun_delay(5,del_s);
        MSG("Ready!")         //输出Ready!
    #else
        fun_wait();           //等待按键
    #endif
}//初始化函数
void fun_stop(){
    EA=0;                   //关总中断
    str_tfl.gospeed=0;      //速度归零
    fun_motors(mot_sz,0);   //手抓速度归零
    fun_motors(mot_py,0);   //平移速度归零
    fun_motors(mot_sj,0);   //手抓速度归零
    fun_motors(mot_hz,0);   //手抓速度归零
    fun_motors(mot_rl,0);   //左右速度归零
    MSG("End!")             //输出End!
    while(1);               //死循环
}//结束函数
