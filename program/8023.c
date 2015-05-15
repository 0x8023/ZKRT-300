#include "./output/8023.h"
xdata struct str_state str_begin,str_now,str_next;//分别为:起始状态/当前状态/目标状态
xdata struct str_parameter str_cod={
    /*ui str_cod.mlinerqd*/25000,//默认主函数巡线软起动路程为25000
    /*ui str_cod.mlineqc*/200,//默认主函数巡线前冲时间为500毫秒

    /*ui str_cod.sj1bzw*/58,//升降标准位延时
    /*ui str_cod.sj1zjw*/800,//升降中间位延时

    /*ui str_cod.py1qkq*/666,
    /*ui str_cod.py1kqz*/684,
    /*ui str_cod.py1zkh*/684,
    /*ui str_cod.py1khh*/666,
    /*ui str_cod.py1qz*/500,
    /*ui str_cod.py1zh*/500,
    /*ui str_cod.py1kqkh*/1480,
    /*ui str_cod.py1qkh*/2122,
    /*ui str_cod.py1kqh*/2122
};
ul var_timer0=0;
bit var_online=0;

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
void fun_motors(enum varENU_mot par_model,char par_speed){
    if(par_speed>100)
        par_speed=100;
    else if(par_speed<-100)
        par_speed=-100;
    switch(par_model){
        case mot_l://左轮电机
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
        case mot_dj1://正转为抓紧，反转为松开
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
        case mot_dj2://正转是向无电机一方转,反转为向有电机一方转
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
        case mot_dj3://向上为正转,向下为反转
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
        case mot_dj4://顺时针为正转,逆时针为反转
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
}//操作电motors机
void fun_sz1(enum varENU_han par_model){
    if(str_begin.szzt==par_model)
        return;
    if(par_model==han_s){//手抓松
        fun_motors(mot_dj1,-100);
        while(in_s==1);
    }
    else{//手抓紧
        fun_motors(mot_dj1,100);
        while(in_j==1);
    }
    fun_delay(20,del_ms);
    fun_motors(mot_dj1,0);
    str_begin.szzt=par_model;//存储运行结果
}//手抓单步运动
void fun_sj1(enum varENU_sjp par_model){
    if(par_model==str_begin.sjwz)
       return;
    switch(par_model){
        case sjp_wz1://升降位置1(最上位)
            fun_motors(mot_dj3,100);
            def_select(sel_58);
            while(in_wz1==1);
            fun_delay(str_cod.sj1bzw,del_ms);
            break;
        case sjp_wz12:
            if(par_model>str_begin.sjwz){
                fun_motors(mot_dj3,-100);
                fun_delay(str_cod.sj1zjw,del_ms);
            }
            else{//要去的地方在上面，向上走
                fun_sj1(sjp_wz2);
                fun_motors(mot_dj3,100);
                fun_delay(str_cod.sj1zjw,del_ms);
            }
            break;
        case sjp_wz2://升降位置2
            fun_motors(mot_dj3,par_model<str_begin.sjwz?100:-100);
            def_select(sel_58);
            while(in_wz2==1);
            fun_delay(str_cod.sj1bzw,del_ms);
            break;
        case sjp_wz23:
            if(par_model>str_begin.sjwz){
                fun_sj1(sjp_wz2);
                fun_motors(mot_dj3,-100);
                fun_delay(str_cod.sj1zjw,del_ms);
            }
            else{//要去的地方在上面，向上走
                fun_sj1(sjp_wz3);
                fun_motors(mot_dj3,100);
                fun_delay(str_cod.sj1zjw,del_ms);
            }
            break;
        case sjp_wz3://升降位置3
            fun_motors(mot_dj3,par_model<str_begin.sjwz?100:-100);
            def_select(sel_58);
            while(in_wz3==1);
            fun_delay(str_cod.sj1bzw,del_ms);
            break;
        case sjp_wz34:
            if(par_model>str_begin.sjwz){
                fun_sj1(sjp_wz3);
                fun_motors(mot_dj3,-100);
                fun_delay(str_cod.sj1zjw,del_ms);
            }
            else{//要去的地方在上面，向上走
                fun_sj1(sjp_wz4);
                fun_motors(mot_dj3,100);
                fun_delay(str_cod.sj1zjw,del_ms);
            }
            break;
        case sjp_wz4://升降位置4
            fun_motors(mot_dj3,par_model<str_begin.sjwz?100:-100);
            def_select(sel_58);
            while(in_wz4==1);
            fun_delay(str_cod.sj1bzw,del_ms);
            break;
        case sjp_wz45:
            if(par_model>str_begin.sjwz){
                fun_sj1(sjp_wz4);
                fun_motors(mot_dj3,-100);
                fun_delay(str_cod.sj1zjw,del_ms);
            }
            else{//要去的地方在上面，向上走
                fun_motors(mot_dj3,100);
                fun_delay(str_cod.sj1zjw,del_ms);
            }
            break;
        case sjp_wz5://升降位置5
            fun_motors(mot_dj3,-100);
            def_select(sel_912);
            while(in_wz5==1);
            fun_delay(str_cod.sj1bzw,del_ms);
            break;
        default:
            break;
    }
    fun_motors(mot_dj3,0);
    str_begin.sjwz=par_model;//存储运行结果
}//升降单步运动
void fun_py1(enum varENU_tra par_model){
    if(str_begin.pywz==par_model)
        return;
    switch(par_model){
        case tra_q://前平移(没有电机的呢个方向)
            fun_motors(mot_dj2,100);
            while(in_qpy==1);
            fun_delay(str_cod.py1bz,del_ms);
            break;
        case tra_kq:
            switch(str_begin.pywz){
                case tra_q:
                    fun_motors(mot_dj2,-100);
                    fun_delay(str_cod.py1qkq,del_ms);
                    break;
                case tra_z:
                    fun_motors(mot_dj2,100);
                    fun_delay(str_cod.py1kqz,del_ms);
                    break;
                case tra_kh:
                    fun_motors(mot_dj2,100);
                    fun_delay(str_cod.py1kqkh,del_ms);
                    break;
                case tra_h:
                    fun_motors(mot_dj2,100);
                    fun_delay(str_cod.py1kqh,del_ms);
                    break;
            }
            break;
        case tra_z:
            switch(str_begin.pywz){
                case tra_q:
                    fun_motors(mot_dj2,-100);
                    fun_delay(str_cod.py1qz,del_ms);
                    break;
                case tra_kq:
                    fun_motors(mot_dj2,-100);
                    fun_delay(str_cod.py1kqz,del_ms);
                    break;
                case tra_kh:
                    fun_motors(mot_dj2,100);
                    fun_delay(str_cod.py1zkh,del_ms);
                    break;
                case tra_h:
                    fun_motors(mot_dj2,100);
                    fun_delay(str_cod.py1zh,del_ms);
                    break;
            }
            break;
        case tra_kh:
            switch(str_begin.pywz){
                case tra_q:
                    fun_motors(mot_dj2,-100);
                    fun_delay(str_cod.py1qkh,del_ms);
                    break;
                case tra_kq:
                    fun_motors(mot_dj2,-100);
                    fun_delay(str_cod.py1kqkh,del_ms);
                    break;
                case tra_z:
                    fun_motors(mot_dj2,-100);
                    fun_delay(str_cod.py1zkh,del_ms);
                    break;
                case tra_h:
                    fun_motors(mot_dj2,100);
                    fun_delay(str_cod.py1khh,del_ms);
                    break;
            }
            break;
        case tra_h://后平移(有电机的呢个方向)
            fun_motors(mot_dj2,-100);
            while(in_hpy==1);
            fun_delay(str_cod.py1bz,del_ms);
            break;
        default:
            break;
    }
    fun_motors(mot_dj2,0);
    str_begin.pywz=par_model;//存储运行结果
}//平移单步运动
void fun_hz1(enum varENU_dir par_model){
    def_select(sel_912);
    switch(par_model){
        case dir_up://回转至前方
            switch(str_begin.hzfx){
                case dir_down://现在在下方
                    fun_motors(mot_dj4,-100);
                    fun_delay(1,del_s);
                    while(in_hz==1);
                    while(in_hz==0);
                    while(in_hz==1);
                    fun_delay(str_cod.hz1bz,del_ms);
                    break;
                case dir_left://现在在左边
                    fun_motors(mot_dj4,100);
                    fun_delay(1,del_s);
                    while(in_hz==1);
                    fun_delay(str_cod.hz1bz,del_ms);
                    break;
                case dir_right://现在在右边
                    fun_motors(mot_dj4,-100);
                    fun_delay(1,del_s);
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
                    fun_motors(mot_dj4,100);
                    fun_delay(1,del_s);
                    while(in_hz==1);
                    while(in_hz==0);
                    while(in_hz==1);
                    fun_delay(str_cod.hz1bz,del_ms);
                    break;
                case dir_left://现在在左面
                    fun_motors(mot_dj4,-100);
                    fun_delay(1,del_s);
                    while(in_hz==1);
                    fun_delay(str_cod.hz1bz,del_ms);
                    break;
                    break;
                case dir_right://现在在右面
                    fun_motors(mot_dj4,100);
                    fun_delay(1,del_s);
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
                    fun_motors(mot_dj4,-100);
                    fun_delay(1,del_s);
                    while(in_hz==1);
                    fun_delay(str_cod.hz1bz,del_ms);
                    break;
                    break;
                case dir_down://现在在下面
                    fun_motors(mot_dj4,100);
                    fun_delay(1,del_s);
                    while(in_hz==1);
                    fun_delay(str_cod.hz1bz,del_ms);
                    break;
                    break;
                case dir_right://现在在右面
                    fun_motors(mot_dj4,-100);
                    fun_delay(1,del_s);
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
                    fun_motors(mot_dj4,100);
                    fun_delay(1,del_s);
                    while(in_hz==1);
                    fun_delay(str_cod.hz1bz,del_ms);
                    break;
                case dir_down://现在在下面
                    fun_motors(mot_dj4,-100);
                    fun_delay(1,del_s);
                    while(in_hz==1);
                    fun_delay(str_cod.hz1bz,del_ms);
                    break;
                case dir_left://现在在左面
                    fun_motors(mot_dj4,100);
                    fun_delay(1,del_s);
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
    }
    fun_motors(mot_dj4,0);
    str_begin.hzfx=par_model;//存储运行结果
}//回转单步运动
void fun_timerfl(){
    if((in_ls1||in_ls8)&&(in_ls2&&in_ls3&&in_ls4&&in_ls5&in_ls6&&in_ls7))
    var_online=1;
    else if(var_online==1){
        ;
        //走了一条线
    }
}//定时器巡线
void fun_timercorner(){
    ;
}//定时器转弯
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
    ul loc_time;
    fun_py1(tra_q);//移动到最前端
    fun_py1(tra_h);//移动到最后端
    loc_time=var_timer0;
    fun_py1(tra_q);//移动到前端并计时
    fun_py1(tra_h);//移动到后端
    loc_time=var_timer0-loc_time;
    loc_time*=0.39;
    str_cod.py1zh=str_cod.py1qz=loc_time*0.5;
    str_cod.py1qkh=str_cod.py1kqh=loc_time*0.75;
    str_cod.py1qkq=str_cod.py1khh=loc_time*0.25;
    str_cod.py1kqz=str_cod.py1zkh=loc_time*0.25;
    str_cod.py1kqkh=loc_time*0.5;
}//自动校准平移参数
void fun_port(){
    PCON|=0x80;       //使能波特率倍速位SMOD
    SCON=0x50;        //8位数据,可变波特率
    AUXR|=0x04;       //独立波特率发生器时钟为Fosc,即1T
    BRT=0xD9;     //设定独立波特率发生器重装值
    AUXR|=0x01;       //串口1选择独立波特率发生器为波特率发生器
    AUXR|=0x10;       //启动独立波特率发生器
    TI=1;//打开串口传输功能
}//串口初始化
void fun_test(){
    fun_sz1(han_j);
    fun_delay(1,del_s);
    fun_sz1(han_s);
    fun_delay(1,del_s);
    fun_sz1(han_j);
    fun_delay(1,del_s);
    fun_sz1(han_s);
    fun_delay(1,del_s);

    str_begin.pywz=tra_h;
    fun_py1(tra_q);
    fun_delay(1,del_s);
    fun_py1(tra_h);
    fun_delay(1,del_s);
    fun_py1(tra_q);
    fun_delay(1,del_s);
    fun_py1(tra_h);
    fun_delay(1,del_s);

    fun_sj1(sjp_wz1);
    fun_delay(1,del_s);
    fun_sj1(sjp_wz2);
    fun_delay(1,del_s);
    fun_sj1(sjp_wz3);
    fun_delay(1,del_s);
    fun_sj1(sjp_wz4);
    fun_delay(1,del_s);
    fun_sj1(sjp_wz5);
    fun_delay(1,del_s);
    fun_sj1(sjp_wz4);
    fun_delay(1,del_s);
    fun_sj1(sjp_wz3);
    fun_delay(1,del_s);
    fun_sj1(sjp_wz2);
    fun_delay(1,del_s);
    fun_sj1(sjp_wz1);

    str_now.hzfx=str_begin.hzfx;
    str_begin.hzfx=dir_up;
    fun_hz1(dir_right);
    fun_delay(1,del_s);
    fun_hz1(dir_up);
    fun_delay(1,del_s);
    fun_hz1(dir_right);
    fun_delay(1,del_s);
    fun_hz1(dir_up);
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
    uc loc_xh;//循环
    uc loc_shu;//当前参数
    uc loc_min;//最小值
    va_start(loc_argp,par_num);//loc_argp指向传入的第一个可选参数，par_num是最后一个确定的参数
    loc_min=va_arg(loc_argp,uc);//第一个参数传入
    for(loc_xh=1;loc_xh<par_num;loc_xh++){//指定循环次数
        loc_shu=va_arg(loc_argp,uc);//取出一个参数
        if(loc_shu<loc_min)
            loc_min=loc_shu;
    }
    va_end(loc_argp);//结束
    return loc_min;//退出
}//求最小值