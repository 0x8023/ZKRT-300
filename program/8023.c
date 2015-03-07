#include "./output/8023.h"
xdata struct str_state str_begin,str_now,str_next;//分别为:起始状态/当前状态/目标状态
xdata struct str_parameter str_cod={
    /*ui str_cod.mlinerqd*/25000,//默认主函数巡线软起动路程为25000
    /*ui str_cod.mlineqc*/200,//默认主函数巡线前冲时间为500毫秒

    /*ui str_cod.sj1bzw*/58,
    /*ui str_cod.sj1zjw*/800,

    /*ui str_cod.py1qkq*/666,
    /*ui str_cod.py1kqz*/684,
    /*ui str_cod.py1zkh*/684,
    /*ui str_cod.py1khh*/666,
    /*ui str_cod.py1qz*/500,
    /*ui str_cod.py1zh*/500,
    /*ui str_cod.py1kqkh*/1480,
    /*ui str_cod.py1qkh*/2122,
    /*ui str_cod.py1kqh*/2122,
};
ui var_timer0=0;
void fun_delay(ui par_value,enum varENU_del par_model){
    ui loc_con=par_value;
    switch(par_model){
        case del_us://微秒级延时
            while(loc_con-->0){
                _nop_();
                _nop_();
            }
            return;
        case del_ms://毫秒级延时
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
        case del_s://秒级延时
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
    AUXR|=0x80;       //定时器时钟1T模式
    TMOD&=0xF0;       //设置定时器模式
    TMOD|=0x01;       //设置定时器模式
    TL0=0x20;     //设置定时初值
    TH0=0xD1;     //设置定时初值
    TF0=0;        //清除TF0标志
    ET0=1;
    EA=1;
}//1毫秒定时器0初始化
void fun_timer1init(){
    AUXR&=0xBF;
    TMOD&=0x0F;
    TMOD|=0x10;
    TL1=0xE0;
    TH1=0xB1;
    TF1=0;
    ET1=1;
    EA=1;
}//20毫秒定时器1初始化
void fun_timer0(){
    TL0=0x20;
    TH0=0xD1;
    _nop_();
    var_timer0++;
}//1毫秒定时器0处理函数
void fun_timer1(){
    TL1=0xE0;
    TH1=0xB1;
    _nop_();
}//20毫秒定时器1处理函数
void fun_wait(){
    while(in_start==1);
    fun_delay(20,del_ms);
    while(in_start==0);
    fun_delay(256,del_ms);
}//等待按键
void fun_select(enum varENU_sel par_model){
    if(par_model==sel_58)
        out_switchselect=0;
    else if(par_model==sel_912)
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
    //out_motorselect=1;//电机片选为1 $?$
    //fun_delay(del_ms,1);//延时1毫秒 $?$
    out_motorselect=0;//电机片选为0 $?$
    //PS_5=PS_1;// $?$

    fun_pwminit();//PWM的初始化设置
    fun_timer0init();//初始化定时器0
    fun_timer1init();//初始化定时器1
    fun_port();//初始化串口
    in_start=1;//按键置1

    fun_wait();
}//初始化
void fun_pwminit(){
    CCON=0x00;
    CH=0;
    CL=0;
    CMOD=0x00;
}//PWM初始化
void fun_pwmr(uc par_value){
    CCAP0H=CCAP0L=par_value*2.5;//控制输出的占空比
    CCAPM0=0X42;//8位PWM输出，无中断
    PCA_PWM0=0x00;
}//右路PWM输出
void fun_pwml(uc par_value){
    CCAP1H=CCAP1L=par_value*2.5;//控制输出的占空比
    CCAPM1=0X42;//8位PWM输出，无中断
    PCA_PWM1=0x00;
}//左路PWM输出
void fun_startdj(enum varENU_mot par_model,char par_speed){
    if(par_speed==0)
        return;
    else if(par_speed>100)
        par_speed=100;
    else if(par_speed<-100)
        par_speed=-100;
    switch(par_model){
        case mot_l://左轮电机
            CR=1;
            if(par_speed>0){
                fun_pwml(par_speed);out_pwml=0;
            }
            else if(par_speed<0){
                fun_pwml(cabs(par_speed));out_pwml=1;
            }
            break;
        case mot_r://右轮电机
            CR=1;
            if(par_speed>0){
                fun_pwmr(par_speed);out_pwmr=0;
            }
            else if(par_speed<0){
                fun_pwmr(cabs(par_speed));out_pwmr=1;
            }
            break;
        case mot_rl://左右轮同步
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
        case mot_dj1://正转为抓紧，反转为松开
            out_motorselect=1;
            if(par_speed>0)
                out_dir1=1;
            else if(par_speed<0)
                out_dir1=0;
            out_en1=0;
            break;
        case mot_dj2://正转是向无电机一方转,反转为向有电机一方转
            out_motorselect=1;
            if(par_speed>0)
                out_dir2=1;
            else if(par_speed<0)
                out_dir2=0;
            out_en2=0;
            break;
        case mot_dj3://向上为正转,向下为反转
            out_motorselect=0;
            if(par_speed>0)
                out_dir1=0;
            else if(par_speed<0)
                out_dir1=1;
            out_en1=0;
            break;
        case mot_dj4://顺时针为正转,逆时针为反转
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
}//启动电机
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
}//停止电机
void fun_sz1(enum varENU_han par_model){
    if(par_model==han_s){//手抓松
        while(1){
            fun_startdj(mot_dj1,-100);
            while(in_s==1);
            fun_delay(20,del_ms);
            if(in_s==0)
                break;
        }
    }
    else{//手抓紧
        while(1){
            fun_startdj(mot_dj1,100);
            while(in_j==1);
            fun_delay(20,del_ms);
            if(in_j==0)
                break;
        }
    }
    fun_stop(mot_dj1);
    str_begin.szzt=par_model;//存储运行结果
}//手抓单步运动
void fun_sj1(enum varENU_sjp par_model){
    if(par_model==str_begin.sjwz)
       return;
    switch(par_model){
        case sjp_wz1://升降位置1(最上位)
            fun_startdj(mot_dj3,100);
            fun_select(sel_58);
            fun_delay(50,del_ms);
            while(1){//只有向上
                while(in_wz1==1);
                fun_delay(20,del_ms);
                if(in_wz1==0){
                    fun_delay(20,del_ms);
                    break;                    
                }
            }
            break;
        case sjp_wz12:
            if(par_model>str_begin.sjwz){
                fun_startdj(mot_dj3,-100);
                fun_delay(str_cod.sj1zjw,del_ms);
            }
            else{//要去的地方在上面，向上走
                fun_sj1(sjp_wz2);
                fun_startdj(mot_dj3,100);
                fun_delay(str_cod.sj1zjw,del_ms);
            }
            break;
        case sjp_wz2://升降位置2
            if(par_model>str_begin.sjwz)
                fun_startdj(mot_dj3,-100);
            else
                fun_startdj(mot_dj3,100);
            fun_select(sel_58);
            fun_delay(50,del_ms);
            while(1){//要去的地方比较靠下,向下走                    
                while(in_wz2==1);
                fun_delay(20,del_ms);
                if(in_wz2==0){
                    fun_delay(str_cod.sj1bzw,del_ms);
                    break;
                }
            }
            break;
        case sjp_wz23:
            if(par_model>str_begin.sjwz){
                fun_sj1(sjp_wz2);
                fun_startdj(mot_dj3,-100);
                fun_delay(str_cod.sj1zjw,del_ms);
            }
            else{//要去的地方在上面，向上走
                fun_sj1(sjp_wz3);
                fun_startdj(mot_dj3,100);
                fun_delay(str_cod.sj1zjw,del_ms);
            }
            break;
        case sjp_wz3://升降位置3
            if(par_model>str_begin.sjwz)
                fun_startdj(mot_dj3,-100);
            else
                fun_startdj(mot_dj3,100);
            fun_select(sel_58);
            fun_delay(50,del_ms);
            while(1){
                while(in_wz3==1);
                fun_delay(str_cod.sj1bzw,del_ms);
                if(in_wz3==0)
                    break;
            }
            break;
        case sjp_wz34:
            if(par_model>str_begin.sjwz){
                fun_sj1(sjp_wz3);
                fun_startdj(mot_dj3,-100);
                fun_delay(str_cod.sj1zjw,del_ms);
            }
            else{//要去的地方在上面，向上走
                fun_sj1(sjp_wz4);
                fun_startdj(mot_dj3,100);
                fun_delay(str_cod.sj1zjw,del_ms);
            }
            break;
        case sjp_wz4://升降位置4
            if(par_model>str_begin.sjwz)
                fun_startdj(mot_dj3,-100);
            else
                fun_startdj(mot_dj3,100);
            fun_select(sel_58);
            fun_delay(50,del_ms);
            while(1){
                while(in_wz4==1);
                fun_delay(str_cod.sj1bzw,del_ms);
                if(in_wz4==0)
                    break;
            }
            break;
        case sjp_wz45:
            if(par_model>str_begin.sjwz){
                fun_sj1(sjp_wz4);
                fun_startdj(mot_dj3,-100);
                fun_delay(str_cod.sj1zjw,del_ms);
            }
            else{//要去的地方在上面，向上走
                fun_startdj(mot_dj3,100);
                fun_delay(str_cod.sj1zjw,del_ms);
            }
            break;
        case sjp_wz5://升降位置5
            fun_startdj(mot_dj3,-100);
            fun_select(sel_912);
            fun_delay(50,del_ms);
            while(1){//要去的地方比较靠下,向下走                
                while(in_wz5==1);
                fun_delay(20,del_ms);
                if(in_wz5==0){
                    fun_delay(str_cod.sj1bzw,del_ms);
                    break;
                }
            }
            break;
        default:
            break;
    }
    fun_stop(mot_dj3);
    str_begin.sjwz=par_model;//存储运行结果
}//升降单步运动
void fun_py1(enum varENU_tra par_model){
    switch(par_model){
        case tra_q://前平移(没有电机的呢个方向)
            while(1){
                fun_startdj(mot_dj2,100);
                while(in_qpy==1);
                fun_delay(20,del_ms);
                if(in_qpy==0){
                    fun_delay(20,del_ms);
                    break;
                }
            }
            break;
        case tra_kq:
            switch(str_begin.pywz){
                case tra_q:
                    fun_startdj(mot_dj2,-100);
                    fun_delay(str_cod.py1qkq,del_ms);
                    break;
                case tra_z:
                    fun_startdj(mot_dj2,100);
                    fun_delay(str_cod.py1kqz,del_ms);
                    break;
                case tra_kh:
                    fun_startdj(mot_dj2,100);
                    fun_delay(str_cod.py1kqkh,del_ms);
                    break;
                case tra_h:
                    fun_startdj(mot_dj2,100);
                    fun_delay(str_cod.py1kqh,del_ms);
                    break;
            }
            break;
        case tra_z:
            switch(str_begin.pywz){
                case tra_q:
                    fun_startdj(mot_dj2,-100);
                    fun_delay(str_cod.py1qz,del_ms);
                    break;
                case tra_kq:
                    fun_startdj(mot_dj2,-100);
                    fun_delay(str_cod.py1kqz,del_ms);
                    break;
                case tra_kh:
                    fun_startdj(mot_dj2,100);
                    fun_delay(str_cod.py1zkh,del_ms);
                    break;
                case tra_h:
                    fun_startdj(mot_dj2,100);
                    fun_delay(str_cod.py1zh,del_ms);
                    break;
            }
            break;
        case tra_kh:
            switch(str_begin.pywz){
                case tra_q:
                    fun_startdj(mot_dj2,-100);
                    fun_delay(str_cod.py1qkh,del_ms);
                    break;
                case tra_kq:
                    fun_startdj(mot_dj2,-100);
                    fun_delay(str_cod.py1kqkh,del_ms);
                    break;
                case tra_z:
                    fun_startdj(mot_dj2,-100);
                    fun_delay(str_cod.py1zkh,del_ms);
                    break;
                case tra_h:
                    fun_startdj(mot_dj2,100);
                    fun_delay(str_cod.py1khh,del_ms);
                    break;
            }
            break;
        case tra_h://后平移(有电机的呢个方向)
            while(1){
                fun_startdj(mot_dj2,-100);
                while(in_hpy==1);
                fun_delay(20,del_ms);
                if(in_hpy==0){
                    fun_delay(20,del_ms);
                    break;
                }
            }
            break;
        default:
            break;
    }
    fun_stop(mot_dj2);
    str_begin.pywz=par_model;//存储运行结果
}//平移单步运动
void fun_hz1(enum varENU_dir par_model){
    fun_select(sel_912);
    switch(par_model){
        case dir_up://回转至前方
            switch(str_begin.hzfx){
                case dir_down://现在在下方
                    fun_startdj(mot_dj4,-100);
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
                case dir_left://现在在左边
                    fun_startdj(mot_dj4,100);
                    fun_delay(1,del_s);
                    while(1){
                        while(in_hz==1);
                        fun_delay(25,del_ms);
                        if(in_hz==0)
                            break;
                    }
                    break;
                case dir_right://现在在右边
                    fun_startdj(mot_dj4,-100);
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
        case dir_down://要去下面
            switch(str_begin.hzfx){
                case dir_up://现在在上面
                    fun_startdj(mot_dj4,100);
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
                case dir_left://现在在左面
                    fun_startdj(mot_dj4,-100);
                    fun_delay(1,del_s);
                    while(1){
                        while(in_hz==1);
                        fun_delay(25,del_ms);
                        if(in_hz==0)
                            break;
                    }
                    break;
                case dir_right://现在在右面
                    fun_startdj(mot_dj4,100);
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
        case dir_left://要去左边
            switch(str_begin.hzfx){
                case dir_up://现在在上面
                    fun_startdj(mot_dj4,-100);
                    fun_delay(1,del_s);
                    while(1){
                        while(in_hz==1);
                        fun_delay(25,del_ms);
                        if(in_hz==0)
                            break;
                    }
                    break;
                case dir_down://现在在下面
                    fun_startdj(mot_dj4,100);
                    fun_delay(1,del_s);
                    while(1){
                        while(in_hz==1);
                        fun_delay(25,del_ms);
                        if(in_hz==0)
                            break;
                    }
                    break;
                case dir_right://现在在右面
                    fun_startdj(mot_dj4,-100);
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
        case dir_right://要去右面
            switch(str_begin.hzfx){
                case dir_up://现在在前面
                    fun_startdj(mot_dj4,100);
                    fun_delay(1,del_s);
                    while(1){
                        while(in_hz==1);
                        fun_delay(25,del_ms);
                        if(in_hz==0)
                            break;
                    }
                    break;
                case dir_down://现在在下面
                    fun_startdj(mot_dj4,-100);
                    fun_delay(1,del_s);
                    while(1){
                        while(in_hz==1);
                        fun_delay(25,del_ms);
                        if(in_hz==0)
                            break;
                    }
                    break;
                case dir_left://现在在左面
                    fun_startdj(mot_dj4,100);
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
    str_begin.hzfx=par_model;//存储运行结果
}//回转单步运动
void fun_pyhz2(enum varENU_tra par_py,enum varENU_dir par_hz){
    if(str_begin.hzfx!=par_hz){
        fun_py1(tra_z);
        switch(par_hz){//启动回转,在位则不启动
            case dir_up://回转至前方
                switch(str_begin.hzfx){
                    case dir_down://现在在下方
                        fun_startdj(mot_dj4,-100);
                        break;
                    case dir_left://现在在左边
                        fun_startdj(mot_dj4,100);
                        break;
                    case dir_right://现在在右边
                        fun_startdj(mot_dj4,-100);
                        break;
                    default:
                        break;
                }
                break;
            case dir_down://要去下面
                switch(str_begin.hzfx){
                    case dir_up://现在在上面
                        fun_startdj(mot_dj4,100);
                        break;
                    case dir_left://现在在左面
                        fun_startdj(mot_dj4,-100);
                        break;
                    case dir_right://现在在右面
                        fun_startdj(mot_dj4,100);
                        break;
                    default:
                        break;
                }
                break;
            case dir_left://要去左边
                switch(str_begin.hzfx){
                    case dir_up://现在在上面
                        fun_startdj(mot_dj4,-100);
                        break;
                    case dir_down://现在在下面
                        fun_startdj(mot_dj4,100);
                        break;
                    case dir_right://现在在右面
                        fun_startdj(mot_dj4,-100);
                        break;
                    default:
                        break;
                }
                break;
            case dir_right://要去右面
                switch(str_begin.hzfx){
                    case dir_up://现在在前面
                        fun_startdj(mot_dj4,100);
                        break;
                    case dir_down://现在在下面
                        fun_startdj(mot_dj4,-100);
                        break;
                    case dir_left://现在在左面
                        fun_startdj(mot_dj4,100);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
    switch(par_py){
        case tra_q://前平移(没有电机的呢个方向)
            while(1){
                fun_startdj(mot_dj2,100);
                while(in_qpy==1);
                fun_delay(20,del_ms);
                if(in_qpy==0){
                    fun_delay(20,del_ms);
                    break;
                }
            }
            break;
        case tra_kq:
            fun_startdj(mot_dj2,100);
            fun_delay(str_cod.py1kqz,del_ms);
            break;
        case tra_kh:
            fun_startdj(mot_dj2,-100);
            fun_delay(str_cod.py1zkh,del_ms);
            break;
        case tra_h://后平移(有电机的呢个方向)
            while(1){
                fun_startdj(mot_dj2,-100);
                while(in_hpy==1);
                fun_delay(20,del_ms);
                if(in_hpy==0){
                    fun_delay(20,del_ms);
                    break;
                }
            }
            break;
        default:
            break;
    }
    fun_stop(mot_dj2);
    str_begin.pywz=par_py;//存储平移位置
    if(str_begin.hzfx!=par_hz){
        fun_select(sel_912);
        switch(par_hz){
            case dir_up://回转至前方
                switch(str_begin.hzfx){
                    case dir_down://现在在下方
                        while(1){
                            while(in_hz==1);
                            fun_delay(25,del_ms);
                            if(in_hz==0)
                                break;
                        }
                        while(1){
                            while(in_hz==0);
                            fun_delay(1,del_s);
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
                    case dir_left://现在在左边
                        while(1){
                            while(in_hz==1);
                            fun_delay(25,del_ms);
                            if(in_hz==0)
                                break;
                        }
                        break;
                    case dir_right://现在在右边
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
            case dir_down://要去下面
                switch(str_begin.hzfx){
                    case dir_up://现在在上面
                        while(1){
                            while(in_hz==1);
                            fun_delay(25,del_ms);
                            if(in_hz==0)
                                break;
                        }
                        while(1){
                            while(in_hz==0);
                            fun_delay(1,del_s);
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
                    case dir_left://现在在左面
                        while(1){
                            while(in_hz==1);
                            fun_delay(25,del_ms);
                            if(in_hz==0)
                                break;
                        }
                        break;
                    case dir_right://现在在右面
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
            case dir_left://要去左边
                switch(str_begin.hzfx){
                    case dir_up://现在在上面
                        while(1){
                            while(in_hz==1);
                            fun_delay(25,del_ms);
                            if(in_hz==0)
                                break;
                        }
                        break;
                    case dir_down://现在在下面
                        while(1){
                            while(in_hz==1);
                            fun_delay(25,del_ms);
                            if(in_hz==0)
                                break;
                        }
                        break;
                    case dir_right://现在在右面
                        while(1){
                            while(in_hz==1);
                            fun_delay(25,del_ms);
                            if(in_hz==0)
                                break;
                        }
                        while(1){
                            while(in_hz==0);
                            fun_delay(1,del_s);
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
            case dir_right://要去右面
                switch(str_begin.hzfx){
                    case dir_up://现在在前面
                        while(1){
                            while(in_hz==1);
                            fun_delay(25,del_ms);
                            if(in_hz==0)
                                break;
                        }
                        break;
                    case dir_down://现在在下面
                        while(1){
                            while(in_hz==1);
                            fun_delay(25,del_ms);
                            if(in_hz==0)
                                break;
                        }
                        break;
                    case dir_left://现在在左面
                        while(1){
                            while(in_hz==1);
                            fun_delay(25,del_ms);
                            if(in_hz==0)
                                break;
                        }
                        while(1){
                            while(in_hz==0);
                            fun_delay(1,del_s);
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
        str_begin.hzfx=par_hz;//存储回转位置
    }
}//回转单步运动
void fun_mptline(uc par_num,uc par_sd,enum varENU_dir par_model){
    bit loc_flag=0;
    ui loc_xh=str_cod.mlinerqd/(0.5*(par_sd*par_sd+par_sd));
    uc loc_con;
    uc loc_l=par_sd,loc_r=par_sd;
    for(loc_con=1;loc_con<par_sd;fun_delay(loc_xh,del_ms)){//确定路程的软启动程序
        loc_r=loc_l=loc_con++;//恢复默认参数
        if(in_ls3){//纠偏
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
        fun_startdj(mot_r,loc_r);
        fun_startdj(mot_l,loc_l);
    }
    loc_con=0;
    while(1){
        if(((in_ls1)&&(in_ls7))||((in_ls2)&&(in_ls8)))
            loc_flag=1;
        else if(loc_flag==1){
            loc_con++;
            loc_flag=0;
            if(loc_con>=par_num){
                if(par_model!=dir_up){
                    if(par_model==dir_left){//左转
                        fun_startdj(mot_r,par_sd);
                        fun_startdj(mot_l,-10);
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
                        fun_startdj(mot_l,par_sd);
                        fun_startdj(mot_r,-10);
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
                else{
                    for(loc_con=par_sd;loc_con>0;fun_delay(loc_xh,del_ms)){//确定路程的软启动程序
                        loc_r=loc_l=loc_con--;//恢复默认参数
                        if(in_ls3){//纠偏
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
                        fun_startdj(mot_r,loc_r);
                        fun_startdj(mot_l,loc_l);
                    }
                    fun_stop(mot_rl);
                    return;
                }
            }
        }
        loc_r=loc_l=par_sd;
        if(in_ls3){//纠偏
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
        fun_startdj(mot_l,loc_l);//更新电机参数
        fun_startdj(mot_r,loc_r);
    }
}//主函数普通巡线
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
    // fun_sj1(sjp_wz1);//升到最上位
    fun_py1(tra_q);//移动到最前端
    fun_py1(tra_h);//移动到最后端
    def_timer0start//开始定时器
    fun_py1(tra_q);//移动到前端并计时
    fun_py1(tra_h);//移动到后端
    def_timer0stop//停止定时器
    var_timer0*=0.39;
    str_cod.py1zh=str_cod.py1qz=var_timer0*0.5;
    str_cod.py1qkh=str_cod.py1kqh=var_timer0*0.75;
    str_cod.py1qkq=str_cod.py1khh=var_timer0*0.25;
    str_cod.py1kqz=str_cod.py1zkh=var_timer0*0.25;
    str_cod.py1kqkh=var_timer0*0.5;
    var_timer0=0;
    OUT(var_timer0)
}//自动校准参数
void fun_port(){
    PCON|=0x80;       //使能波特率倍速位SMOD
    SCON=0x50;        //8位数据,可变波特率
    AUXR|=0x04;       //独立波特率发生器时钟为Fosc,即1T
    BRT=0xD9;     //设定独立波特率发生器重装值
    AUXR|=0x01;       //串口1选择独立波特率发生器为波特率发生器
    AUXR|=0x10;       //启动独立波特率发生器
    TI=1;//打开串口传输功能
}//串口初始化
void fun_zhuajian(
    uc par_01,uc par_02,uc par_03,uc par_04,uc par_41,uc par_42,uc par_43,uc par_44,
    uc par_31,uc par_32,uc par_33,uc par_34,uc par_71,uc par_72,uc par_73,uc par_74){

    xdata uc loc_data[8][5][2];//三维数组,8个区,5个高度
    xdata uc loc_high[8];
    xdata uc loc_high03;
    xdata uc loc_high47;
    xdata uc loc_high07;
    xdata uc loc_xh1,loc_xh2;

    memset(loc_data,0,sizeof(loc_data));//清空数组
    //起始区件号
    loc_data[0][1][0]=par_01;//传入形参:区0的第1号件件号(最高位)
    loc_data[0][2][0]=par_02;//传入形参:区0的第2号件件号
    loc_data[0][3][0]=par_03;//传入形参:区0的第3号件件号
    loc_data[0][4][0]=par_04;//传入形参:区0的第4号件件号(最低位)
    loc_data[4][1][0]=par_41;//传入形参:区4的第1号件件号(最高位)
    loc_data[4][2][0]=par_42;//传入形参:区4的第2号件件号
    loc_data[4][3][0]=par_43;//传入形参:区4的第3号件件号
    loc_data[4][4][0]=par_44;//传入形参:区4的第4号件件号(最低位)
    //目的区件号
    loc_data[3][1][0]=par_31;//传入形参:区0的第1号件件号(最高位)
    loc_data[3][2][0]=par_32;//传入形参:区0的第2号件件号
    loc_data[3][3][0]=par_33;//传入形参:区0的第3号件件号
    loc_data[3][4][0]=par_34;//传入形参:区0的第4号件件号(最低位)
    loc_data[7][1][0]=par_71;//传入形参:区4的第1号件件号(最高位)
    loc_data[7][2][0]=par_72;//传入形参:区4的第2号件件号
    loc_data[7][3][0]=par_73;//传入形参:区4的第3号件件号
    loc_data[7][4][0]=par_74;//传入形参:区4的第4号件件号(最低位)
    //目的次序
    loc_data[3][1][1]=1;//标准次序:区3的第1号目的次序号(最高位)
    loc_data[3][2][1]=2;//标准次序:区3的第2号目的次序号
    loc_data[3][3][1]=3;//标准次序:区3的第3号目的次序号
    loc_data[3][4][1]=4;//标准次序:区3的第4号目的次序号(最低位)
    loc_data[7][1][1]=5;//标准次序:区7的第1号目的次序号(最高位)
    loc_data[7][2][1]=6;//标准次序:区7的第2号目的次序号
    loc_data[7][3][1]=7;//标准次序:区7的第3号目的次序号
    loc_data[7][4][1]=8;//标准次序:区7的第4号目的次序号(最低位)
    //根据形参统一次序
    for(loc_xh1=4;loc_xh1>0;loc_xh1--){
             if((loc_data[0][loc_xh1][0]==loc_data[3][1][0])&&(loc_data[0][loc_xh1][0]!=0))
            loc_data[0][loc_xh1][1]=loc_data[3][1][1];
        else if((loc_data[0][loc_xh1][0]==loc_data[3][2][0])&&(loc_data[0][loc_xh1][0]!=0))
            loc_data[0][loc_xh1][1]=loc_data[3][2][1];
        else if((loc_data[0][loc_xh1][0]==loc_data[3][3][0])&&(loc_data[0][loc_xh1][0]!=0))
            loc_data[0][loc_xh1][1]=loc_data[3][3][1];
        else if((loc_data[0][loc_xh1][0]==loc_data[3][4][0])&&(loc_data[0][loc_xh1][0]!=0))
            loc_data[0][loc_xh1][1]=loc_data[3][4][1];
        else if((loc_data[0][loc_xh1][0]==loc_data[7][1][0])&&(loc_data[0][loc_xh1][0]!=0))
            loc_data[0][loc_xh1][1]=loc_data[7][1][1];
        else if((loc_data[0][loc_xh1][0]==loc_data[7][2][0])&&(loc_data[0][loc_xh1][0]!=0))
            loc_data[0][loc_xh1][1]=loc_data[7][2][1];
        else if((loc_data[0][loc_xh1][0]==loc_data[7][3][0])&&(loc_data[0][loc_xh1][0]!=0))
            loc_data[0][loc_xh1][1]=loc_data[7][3][1];
        else if((loc_data[0][loc_xh1][0]==loc_data[7][4][0])&&(loc_data[0][loc_xh1][0]!=0))
            loc_data[0][loc_xh1][1]=loc_data[7][4][1];

             if((loc_data[4][loc_xh1][0]==loc_data[3][1][0])&&(loc_data[4][loc_xh1][0]!=0))
            loc_data[4][loc_xh1][1]=loc_data[3][1][1];
        else if((loc_data[4][loc_xh1][0]==loc_data[3][2][0])&&(loc_data[4][loc_xh1][0]!=0))
            loc_data[4][loc_xh1][1]=loc_data[3][2][1];
        else if((loc_data[4][loc_xh1][0]==loc_data[3][3][0])&&(loc_data[4][loc_xh1][0]!=0))
            loc_data[4][loc_xh1][1]=loc_data[3][3][1];
        else if((loc_data[4][loc_xh1][0]==loc_data[3][4][0])&&(loc_data[4][loc_xh1][0]!=0))
            loc_data[4][loc_xh1][1]=loc_data[3][4][1];
        else if((loc_data[4][loc_xh1][0]==loc_data[7][1][0])&&(loc_data[4][loc_xh1][0]!=0))
            loc_data[4][loc_xh1][1]=loc_data[7][1][1];
        else if((loc_data[4][loc_xh1][0]==loc_data[7][2][0])&&(loc_data[4][loc_xh1][0]!=0))
            loc_data[4][loc_xh1][1]=loc_data[7][2][1];
        else if((loc_data[4][loc_xh1][0]==loc_data[7][3][0])&&(loc_data[4][loc_xh1][0]!=0))
            loc_data[4][loc_xh1][1]=loc_data[7][3][1];
        else if((loc_data[4][loc_xh1][0]==loc_data[7][4][0])&&(loc_data[4][loc_xh1][0]!=0))
            loc_data[4][loc_xh1][1]=loc_data[7][4][1];
    }
    //清空形参表(实际件序)
    for(loc_xh1=0;loc_xh1<=7;loc_xh1++)
        for(loc_xh2=0;loc_xh2<=4;loc_xh2++)
            loc_data[loc_xh1][loc_xh2][0]=0;
    //转移04的序号
    for(loc_xh1=0;loc_xh1<=4;loc_xh1++){
        loc_data[0][loc_xh1][0]=loc_data[0][loc_xh1][1];
        loc_data[4][loc_xh1][0]=loc_data[4][loc_xh1][1];
    }
    //目的区除了3.7区全部清零
    for(loc_xh1=0;loc_xh1<=4;loc_xh1++){
        loc_data[0][loc_xh1][1]=0;
        loc_data[1][loc_xh1][1]=0;
        loc_data[2][loc_xh1][1]=0;
        loc_data[4][loc_xh1][1]=0;
        loc_data[5][loc_xh1][1]=0;
        loc_data[6][loc_xh1][1]=0;
    }
    //8个区的循环
    for(loc_xh1=0;loc_xh1<=7;loc_xh1++){
        loc_high[loc_xh1]=4;//默认为没有件
        for(loc_xh2=0;loc_xh2<=4;loc_xh2++){//5个高度的循环
            if(loc_data[loc_xh1][loc_xh2][0]!=0){//如果放了件了
                loc_high[loc_xh1]=loc_xh2-1;//记录这个区最高空闲位置
                break;//继续区的循环
            }
        }
    }

    fun_sj1(sjp_wz1);
    fun_sz1(han_s);

    while(1){
        loc_high03=fun_min4(loc_high[0],loc_high[1],loc_high[2],loc_high[3]);
        loc_high47=fun_min4(loc_high[4],loc_high[5],loc_high[6],loc_high[7]);
        loc_high07=fun_min2(loc_high03,loc_high47);
        if(str_begin.hzfx==dir_left){
            if(loc_high[0]<4){//如果区0有件
                if(loc_data[0][loc_high[0]+1][0]==loc_data[3][loc_high[3]][1]){//如果区0最高位等于区3最高位件
                    fun_sj1zt(loc_high03);//上升到03方最高位
                    fun_pyhz2(tra_h,dir_left);//抓件位置0
                    fun_sj1zt(loc_high[0]+1);//下降到区0最高位
                    fun_sz1(han_j);//抓件
                    fun_sj1zt(loc_high03);//上升到03方最高位
                    fun_pyhz2(tra_q,dir_left);//抓件位置3
                    fun_sj1zt(loc_high[3]);//下降到区3最高位
                    fun_sz1(han_s);//松件

                    loc_data[3][loc_high[3]+1][0]=loc_data[0][loc_high[0]+1][0];//件已经从0区拿到了3区
                    loc_data[0][loc_high[0]+1][0]=0;//0区木有了
                    loc_high[0]++;//更新区0最高位
                    loc_high[3]--;//更新区3最高位
                }
                else if(loc_data[0][loc_high[0]+1][0]==loc_data[7][loc_high[7]][1]){//如果区0最高位等于区7最高位件
                    fun_sj1zt(loc_high03);//上升到03方最高位
                    fun_pyhz2(tra_h,dir_left);//抓件位置0
                    fun_sj1zt(loc_high[0]+1);//下降到区0最高位
                    fun_sz1(han_j);//抓件
                    fun_sj1zt(loc_high07);//上升到07方最高位
                    fun_pyhz2(tra_h,dir_right);//抓件位置7
                    fun_sj1zt(loc_high[7]);//下降到区7最高位
                    fun_sz1(han_s);//松件

                    loc_data[7][loc_high[7]+1][0]=loc_data[0][loc_high[0]+1][0];//件已经从0区拿到了7区
                    loc_data[0][loc_high[0]+1][0]=0;//0区木有了
                    loc_high[0]++;//更新区0最高位
                    loc_high[7]--;//更新区7最高位
                }
                else{
                    if((loc_high[1]>=4)||(loc_data[0][loc_high[0]+1][0]>loc_data[1][loc_high[1]][0])){//如果区1能放得下,放在区1
                        fun_sj1zt(loc_high03);//上升到03方最高位
                        fun_pyhz2(tra_h,dir_left);//抓件位置0
                        fun_sj1zt(loc_high[0]+1);//下降到区0最高位
                        fun_sz1(han_j);//抓件
                        fun_sj1zt(loc_high03);//上升到03方最高位
                        fun_pyhz2(tra_kh,dir_left);//抓件位置1
                        fun_sj1zt(loc_high[1]);//下降到区1最高位
                        fun_sz1(han_s);//松件

                        loc_data[1][loc_high[1]+1][0]=loc_data[0][loc_high[0]+1][0];//件已经从0区拿到了3区
                        loc_data[0][loc_high[0]+1][0]=0;//0区木有了
                        loc_high[0]++;//更新区0最高位
                        loc_high[1]--;//更新区3最高位
                    }
                    else{//否则放在区2
                        fun_sj1zt(loc_high03);//上升到03方最高位
                        fun_pyhz2(tra_h,dir_left);//抓件位置0
                        fun_sj1zt(loc_high[0]+1);//下降到区0最高位
                        fun_sz1(han_j);//抓件
                        fun_sj1zt(loc_high03);//上升到03方最高位
                        fun_pyhz2(tra_kq,dir_left);//抓件位置2
                        fun_sj1zt(loc_high[2]);//下降到区2最高位
                        fun_sz1(han_s);//松件

                        loc_data[2][loc_high[2]+1][0]=loc_data[0][loc_high[0]+1][0];//件已经从0区拿到了3区
                        loc_data[0][loc_high[0]+1][0]=0;//0区木有了
                        loc_high[0]++;//更新区0最高位
                        loc_high[2]--;//更新区3最高位
                    }
                }
            }
            else if(loc_high[1]<4){//如果区1有件
                if(loc_data[1][loc_high[1]+1][0]==loc_data[3][loc_high[3]][1]){//如果区1最高位等于区3最高位件
                    fun_sj1zt(loc_high03);//上升到03方最高位
                    fun_pyhz2(tra_kh,dir_left);//抓件位置1
                    fun_sj1zt(loc_high[1]+1);//下降到区1最高位
                    fun_sz1(han_j);//抓件
                    fun_sj1zt(loc_high03);//上升到03方最高位
                    fun_pyhz2(tra_q,dir_left);//抓件位置2
                    fun_sj1zt(loc_high[3]);//下降到区2最高位
                    fun_sz1(han_s);//松件

                    loc_data[3][loc_high[3]+1][0]=loc_data[1][loc_high[1]+1][0];//件已经从1区拿到了3区
                    loc_data[1][loc_high[1]+1][0]=0;//1区木有了
                    loc_high[1]++;//更新区1最高位
                    loc_high[3]--;//更新区3最高位
                }
                else if(loc_data[1][loc_high[1]+1][0]==loc_data[7][loc_high[7]][1]){//如果区1最高位等于区7最高位件
                    fun_sj1zt(loc_high03);//上升到03方最高位
                    fun_pyhz2(tra_kh,dir_left);//抓件位置1
                    fun_sj1zt(loc_high[1]+1);//下降到区1最高位
                    fun_sz1(han_j);//抓件
                    fun_sj1zt(loc_high07);//上升到07方最高位
                    fun_pyhz2(tra_h,dir_right);//抓件位置7
                    fun_sj1zt(loc_high[7]);//下降到区7最高位
                    fun_sz1(han_s);//松件

                    loc_data[7][loc_high[7]+1][0]=loc_data[1][loc_high[1]+1][0];//件已经从1区拿到了7区
                    loc_data[1][loc_high[1]+1][0]=0;//1区木有了
                    loc_high[1]++;//更新区1最高位
                    loc_high[7]--;//更新区3最高位
                }
                else if(loc_data[1][loc_high[1]+1][0]>loc_data[2][loc_high[2]][0]){//如果区2能放得下,放在区2
                    fun_sj1zt(loc_high03);//上升到03方最高位
                    fun_pyhz2(tra_kh,dir_left);//抓件位置1
                    fun_sj1zt(loc_high[1]+1);//下降到区1最高位
                    fun_sz1(han_j);//抓件
                    fun_sj1zt(loc_high03);//上升到03方最高位
                    fun_pyhz2(tra_kq,dir_left);//抓件位置2
                    fun_sj1zt(loc_high[2]);//下降到区2最高位
                    fun_sz1(han_s);//松件

                    loc_data[2][loc_high[2]+1][0]=loc_data[1][loc_high[1]+1][0];//件已经从1区拿到了2区
                    loc_data[1][loc_high[1]+1][0]=0;//1区木有了
                    loc_high[1]++;//更新区1最高位
                    loc_high[2]--;//更新区3最高位
                }
            }
            else if(loc_high[2]<4){//如果区2有件
                if(loc_data[2][loc_high[2]+1][0]==loc_data[3][loc_high[3]][1]){//如果区2最高位等于区3最高位件
                    fun_sj1zt(loc_high03);//上升到03方最高位
                    fun_pyhz2(tra_kq,dir_left);//抓件位置2
                    fun_sj1zt(loc_high[2]+1);//下降到区2最高位
                    fun_sz1(han_j);//抓件
                    fun_sj1zt(loc_high03);//上升到03方最高位
                    fun_pyhz2(tra_q,dir_left);//抓件位置3
                    fun_sj1zt(loc_high[2]);//下降到区3最高位
                    fun_sz1(han_s);//松件

                    loc_data[3][loc_high[3]+1][0]=loc_data[2][loc_high[2]+1][0];//件已经从2区拿到了3区
                    loc_data[2][loc_high[2]+1][0]=0;//2区木有了
                    loc_high[2]++;//更新区2最高位
                    loc_high[3]--;//更新区3最高位
                }
                else if(loc_data[2][loc_high[2]+1][0]==loc_data[7][loc_high[7]][1]){//如果区2最高位等于区7最高位件
                    fun_sj1zt(loc_high03);//上升到03方最高位
                    fun_pyhz2(tra_kq,dir_left);//抓件位置2
                    fun_sj1zt(loc_high[2]+1);//下降到区2最高位
                    fun_sz1(han_j);//抓件
                    fun_sj1zt(loc_high07);//上升到07方最高位
                    fun_pyhz2(tra_h,dir_right);//抓件位置7
                    fun_sj1zt(loc_high[7]);//下降到区7最高位
                    fun_sz1(han_s);//松件

                    loc_data[7][loc_high[7]+1][0]=loc_data[2][loc_high[2]+1][0];//件已经从2区拿到了7区
                    loc_data[2][loc_high[2]+1][0]=0;//2区木有了
                    loc_high[2]++;//更新区2最高位
                    loc_high[7]--;//更新区7最高位
                }
            }
            if((loc_data[3][4][0]==loc_data[3][4][1])&&
               (loc_data[3][3][0]==loc_data[3][3][1])&&
               (loc_data[3][2][0]==loc_data[3][2][1])&&
               (loc_data[3][1][0]==loc_data[3][1][1])){
                if((loc_data[7][4][0]==loc_data[7][4][1])&&
                   (loc_data[7][3][0]==loc_data[7][3][1])&&
                   (loc_data[7][2][0]==loc_data[7][2][1])&&
                   (loc_data[7][1][0]==loc_data[7][1][1])){
                    return;
                }
                else
                    fun_hz1(dir_right);
            }
        }
        else if(str_begin.hzfx==dir_right){
            if(loc_high[4]<4){//如果区4有件
                if(loc_data[4][loc_high[4]+1][0]==loc_data[7][loc_high[7]][1]){//如果区4最高位等于区7最高位件
                    fun_sj1zt(loc_high47);//上升到47方最高位
                    fun_pyhz2(tra_q,dir_right);//抓件位置4
                    fun_sj1zt(loc_high[4]+1);//下降到区4最高位
                    fun_sz1(han_j);//抓件
                    fun_sj1zt(loc_high47);//上升到47方最高位
                    fun_pyhz2(tra_h,dir_right);//抓件位置7
                    fun_sj1zt(loc_high[7]);//下降到区7最高位
                    fun_sz1(han_s);//松件

                    loc_data[7][loc_high[7]+1][0]=loc_data[4][loc_high[4]+1][0];//件已经从4区拿到了7区
                    loc_data[4][loc_high[4]+1][0]=0;//4区木有了
                    loc_high[4]++;//更新区4最高位
                    loc_high[7]--;//更新区7最高位
                }
                else if(loc_data[4][loc_high[4]+1][0]==loc_data[3][loc_high[3]][1]){//如果区4最高位等于区3最高位件
                    fun_sj1zt(loc_high47);//上升到47方最高位
                    fun_pyhz2(tra_q,dir_right);//抓件位置4
                    fun_sj1zt(loc_high[4]+1);//下降到区4最高位
                    fun_sz1(han_j);//抓件
                    fun_sj1zt(loc_high07);//上升到07方最高位
                    fun_pyhz2(tra_q,dir_left);//抓件位置3
                    fun_sj1zt(loc_high[3]);//下降到区3最高位
                    fun_sz1(han_s);//松件

                    loc_data[3][loc_high[3]+1][0]=loc_data[4][loc_high[4]+1][0];//件已经从4区拿到了3区
                    loc_data[4][loc_high[4]+1][0]=0;//4区木有了
                    loc_high[4]++;//更新区4最高位
                    loc_high[3]--;//更新区7最高位
                }
                else{
                    if((loc_high[6]>=4)||(loc_data[4][loc_high[4]+1][0]>loc_data[6][loc_high[6]][0])){//如果区6能放得下,放在区6
                        fun_sj1zt(loc_high47);//上升到47方最高位
                        fun_pyhz2(tra_q,dir_right);//抓件位置4
                        fun_sj1zt(loc_high[4]+1);//下降到区4最高位
                        fun_sz1(han_j);//抓件
                        fun_sj1zt(loc_high07);//上升到07方最高位
                        fun_pyhz2(tra_kq,dir_right);//抓件位置6
                        fun_sj1zt(loc_high[6]);//下降到区6最高位
                        fun_sz1(han_s);//松件

                        loc_data[6][loc_high[6]+1][0]=loc_data[4][loc_high[4]+1][0];//件已经从4区拿到了6区
                        loc_data[4][loc_high[4]+1][0]=0;//4区木有了
                        loc_high[4]++;//更新区4最高位
                        loc_high[6]--;//更新区6最高位
                    }
                    else{//否则放在区5
                        fun_sj1zt(loc_high47);//上升到47方最高位
                        fun_pyhz2(tra_q,dir_right);//抓件位置4
                        fun_sj1zt(loc_high[4]+1);//下降到区4最高位
                        fun_sz1(han_j);//抓件
                        fun_sj1zt(loc_high47);//上升到47方最高位
                        fun_pyhz2(tra_kq,dir_right);//抓件位置2
                        fun_sj1zt(loc_high[5]);//下降到区5最高位
                        fun_sz1(han_s);//松件

                        loc_data[5][loc_high[5]+1][0]=loc_data[4][loc_high[4]+1][0];//件已经从4区拿到了5区
                        loc_data[4][loc_high[4]+1][0]=0;//4区木有了
                        loc_high[4]++;//更新区4最高位
                        loc_high[5]--;//更新区6最高位
                    }
                }
            }
            else if(loc_high[5]<4){//如果区5有件
                if(loc_data[5][loc_high[5]+1][0]==loc_data[7][loc_high[7]][1]){//如果区5最高位等于区7最高位件
                    fun_sj1zt(loc_high47);//上升到47方最高位
                    fun_pyhz2(tra_kq,dir_right);//抓件位置5
                    fun_sj1zt(loc_high[5]+1);//下降到区5最高位
                    fun_sz1(han_j);//抓件
                    fun_sj1zt(loc_high47);//上升到47方最高位
                    fun_pyhz2(tra_h,dir_right);//抓件位置2
                    fun_sj1zt(loc_high[7]);//下降到区7最高位
                    fun_sz1(han_s);//松件

                    loc_data[7][loc_high[7]+1][0]=loc_data[5][loc_high[5]+1][0];//件已经从5区拿到了7区
                    loc_data[5][loc_high[5]+1][0]=0;//5区木有了
                    loc_high[5]++;//更新区5最高位
                    loc_high[7]--;//更新区7最高位
                }
                else if(loc_data[5][loc_high[5]+1][0]==loc_data[3][loc_high[3]][1]){//如果区5最高位等于区3最高位件
                    fun_sj1zt(loc_high47);//上升到47方最高位
                    fun_pyhz2(tra_kq,dir_right);//抓件位置5
                    fun_sj1zt(loc_high[5]+1);//下降到区5最高位
                    fun_sz1(han_j);//抓件
                    fun_sj1zt(loc_high07);//上升到07方最高位
                    fun_pyhz2(tra_q,dir_left);//抓件位置3
                    fun_sj1zt(loc_high[3]);//下降到区3最高位
                    fun_sz1(han_s);//松件

                    loc_data[3][loc_high[3]+1][0]=loc_data[5][loc_high[5]+1][0];//件已经从5区拿到了3区
                    loc_data[5][loc_high[5]+1][0]=0;//5区木有了
                    loc_high[5]++;//更新区5最高位
                    loc_high[3]--;//更新区3最高位
                }
                else if(loc_data[5][loc_high[5]+1][0]>loc_data[6][loc_high[6]][0]){//如果区6能放得下,放在区6
                    fun_sj1zt(loc_high47);//上升到47方最高位
                    fun_pyhz2(tra_kq,dir_right);//抓件位置5
                    fun_sj1zt(loc_high[5]+1);//下降到区5最高位
                    fun_sz1(han_j);//抓件
                    fun_sj1zt(loc_high47);//上升到47方最高位
                    fun_pyhz2(tra_kh,dir_right);//抓件位置2
                    fun_sj1zt(loc_high[6]);//下降到区7最高位
                    fun_sz1(han_s);//松件

                    loc_data[6][loc_high[6]+1][0]=loc_data[5][loc_high[5]+1][0];//件已经从5区拿到了6区
                    loc_data[5][loc_high[5]+1][0]=0;//5区木有了
                    loc_high[5]++;//更新区5最高位
                    loc_high[6]--;//更新区7最高位
                }
            }
            else if(loc_high[6]<4){//如果区6有件
                if(loc_data[6][loc_high[6]+1][0]==loc_data[7][loc_high[7]][1]){//如果区6最高位等于区7最高位件
                    fun_sj1zt(loc_high47);//上升到47方最高位
                    fun_pyhz2(tra_kh,dir_right);//抓件位置6
                    fun_sj1zt(loc_high[6]+1);//下降到区6最高位
                    fun_sz1(han_j);//抓件
                    fun_sj1zt(loc_high47);//上升到47方最高位
                    fun_pyhz2(tra_h,dir_right);//抓件位置7
                    fun_sj1zt(loc_high[7]);//下降到区7最高位
                    fun_sz1(han_s);//松件

                    loc_data[7][loc_high[7]+1][0]=loc_data[6][loc_high[6]+1][0];//件已经从6区拿到了7区
                    loc_data[6][loc_high[6]+1][0]=0;//2区木有了
                    loc_high[6]++;//更新区2最高位
                    loc_high[7]--;//更新区7最高位
                }
                else if(loc_data[6][loc_high[6]+1][0]==loc_data[3][loc_high[3]][1]){//如果区6最高位等于区3最高位件
                    fun_sj1zt(loc_high47);//上升到47方最高位
                    fun_pyhz2(tra_kh,dir_right);//抓件位置6
                    fun_sj1zt(loc_high[6]+1);//下降到区6最高位
                    fun_sz1(han_j);//抓件
                    fun_sj1zt(loc_high47);//上升到47方最高位
                    fun_pyhz2(tra_q,dir_left);//抓件位置3
                    fun_sj1zt(loc_high[3]);//下降到区7最高位
                    fun_sz1(han_s);//松件

                    loc_data[3][loc_high[3]+1][0]=loc_data[6][loc_high[6]+1][0];//件已经从6区拿到了3区
                    loc_data[6][loc_high[6]+1][0]=0;//2区木有了
                    loc_high[6]++;//更新区2最高位
                    loc_high[3]--;//更新区7最高位
                }
            }
            if((loc_data[7][4][0]==loc_data[7][4][1])&&
               (loc_data[7][3][0]==loc_data[7][3][1])&&
               (loc_data[7][2][0]==loc_data[7][2][1])&&
               (loc_data[7][1][0]==loc_data[7][1][1])){
                if((loc_data[3][4][0]==loc_data[3][4][1])&&
                   (loc_data[3][3][0]==loc_data[3][3][1])&&
                   (loc_data[3][2][0]==loc_data[3][2][1])&&
                   (loc_data[3][1][0]==loc_data[3][1][1])){
                    return;
                }
                else
                    fun_hz1(dir_left);
            }
        }
        else{
            fun_hz1(dir_left);
        }
    }
}//自动抓奸
uc fun_min4(uc par_num1,uc par_num2,uc par_num3,uc par_num4){
    return 
    par_num1<par_num2?par_num1:par_num2<par_num2<par_num3?par_num2:par_num3?
    par_num1<par_num2?par_num1:par_num2<par_num3<par_num4?par_num3:par_num4?
    par_num1<par_num2?par_num1:par_num2:par_num3<par_num4?par_num3:par_num4:
    par_num2<par_num3?par_num2:par_num3<par_num3<par_num4?par_num3:par_num4?
    par_num2<par_num3?par_num2:par_num3:par_num3<par_num4?par_num3:par_num4;
}//求4个数的最小值
uc fun_min2(uc par_num1,uc par_num2){
    return 
    par_num1<par_num2?par_num1:par_num2;
}//求2个数的最小值
void fun_sj1zt(uc par_value){
    switch(par_value){
        case 0:
            fun_sj1(sjp_wz1);
            break;
        case 1:
            fun_sj1(sjp_wz2);
            break;
        case 2:
            fun_sj1(sjp_wz3);
            break;
        case 3:
            fun_sj1(sjp_wz4);
            break;
        case 4:
            fun_sj1(sjp_wz5);
            break;
        default:
            break;
    }
}//状态的升降单步,用来配合自动抓奸

