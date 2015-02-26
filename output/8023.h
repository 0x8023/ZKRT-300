/*-------------------------------------------------------------头文件引入-----*/
    #include "STC12c5a60s2.h"//单片机头文件
    #include "intrins.h"//_nop_与循环位移
    #include "math.h"//数学运算
    #include "string.h"//字符串
    #include "stdio.h"//串口调戏
    #include "stdarg.h"//可变参数
/*----------------------------------------------------------define 宏定义-----*/
    #define def_timer0start TR0=1;//定时器0开启
    #define def_timer0stop TR0=0;//定时器0关闭
    #define def_timer1start TR1=1;//定时器1开启
    #define def_timer1stop TR1=0;//定时器1关闭
    #define def_start fun_initialization();//初始化
    // #define j 0//手爪夹紧
    // #define s 1//手爪松开   

    // #define qpy 0//手爪前平移 
    // #define hpy 1//手爪后平移
    
    // #define xs 0//向上升
    // #define xx 1//向下降

    // #define qhz 0//前回转 
    // #define hhz 1//后回转

    // #define f 0//代表电机正转
    // #define b 1//代表电机反转

    // #define up 25
    // #define down 26
    // #define left 27
    // #define right 28
    // #define home 29//回家
    // #define start 30//起始区
    // #define tz 31//抓取工位的台子
/*-----------------------------------------------------------变量类型说明-----*/
    typedef unsigned int ui;       //unsigned int --> ui
    typedef unsigned char uc;  //unsigned char uc --> uc
//    typedef unsigned int* pui;     //unsigned int --> pui
 //   typedef unsigned char* puc;   //unsigned char --> puc
//    typedef int* pi;                       //int* --> pi
 //   typedef char* pc;                     //char* --> pc
//    typedef unsigned long ul;     //unsigned long --> ul
/*-----------------------------------------------------------------In Put-----*/
    sbit in_start=P3^2;//启动按键(start_)
    sbit in_ls1=P0^0;//1号传感器(靠近？侧)
    sbit in_ls2=P0^1;//2号传感器
    sbit in_ls3=P0^2;//3号传感器
    sbit in_ls4=P0^3;//4号传感器
    sbit in_ls5=P0^4;//5号传感器
    sbit in_ls6=P0^5;//6号传感器
    sbit in_ls7=P0^6;//7号传感器
    sbit in_ls8=P0^7;//8号传感器(靠近？侧)

    sbit in_j=P3^4;//手抓紧传感器
    sbit in_s=P3^3;//手抓松传感器
    sbit in_qpy=P3^5;//平移前平移传感器
    sbit in_hpy=P3^6;//平移后平移传感器

    sbit in_wz1=P2^4;//升降位置1传感器(最上位)
    sbit in_wz2=P2^5;//升降位置2传感器
    sbit in_wz3=P2^6;//升降位置3传感器
    sbit in_wz4=P2^7;//升降位置4传感器

    sbit in_wz5=P2^4;//升降位置5传感器(最下位)
    sbit in_hz=P2^5;//回转传感器
    /*
        sbit DIR_R=P1^2;//PWMR的正反转控制位，1代表正
        sbit DIR_L=P1^5;//PWML的正反转控制位，1代表正
        sbit MOT_DIR1=P2^0;//电机1/3方向
        sbit MOT_EN1=P2^1;//电机1/3使能
        sbit MOT_DIR2=P2^2;//电机2/4方向
        sbit MOT_EN2=P2^3;//电机2/4使能
        sbit start_=P3^2;//启动按键
        sbit SER_BS=P1^6;//接近开关片选
        sbit MOT_BS=P1^7;//电机输出片选
        sbit LAMP=P3^7;//警灯输出

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
    sbit out_pwmr=P1^2;//PWMR的正反转控制位，1代表正(DIR_R)
    sbit out_pwml=P1^5;//PWML的正反转控制位，1代表正(DIR_L)
    sbit out_dir1=P2^0;//电机1/3方向(MOT_DIR1)
    sbit out_en1=P2^1;//电机1/3使能(MOT_EN1)
    sbit out_dir2=P2^2;//电机2/4方向(MOT_DIR2)
    sbit out_en2=P2^3;//电机2/4使能(MOT_EN2)
    sbit out_switchselect=P1^6;//接近开关片选(SER_BS)
    sbit out_motorselect=P1^7;//电机输出片选(MOT_BS)
    sbit out_lamp=P3^7;//警灯输出(LAMP)
/*---------------------------------------------------------------变量定义-----*/
    xdata enum varENU_delaymodel{us,ms,s};//延时模式选择
    xdata enum varENU_selectsensor{ps58,ps912};//传感器片选
    xdata enum varENU_motor{l,r,rl,dj1,dj2,dj3,dj4};//电机选择
    xdata enum varENU_direction{up,down,left,right};//车头方向
    xdata enum varENU_translationplace{q,kq,zj,kh,h};//平移位置
    xdata enum varENU_sjplace{wz1,wz12,wz2,wz23,wz3,wz34,wz4,wz45,wz5};//升降位置

    xdata struct str_state{
        char str_x;//X坐标
        char str_y;//Y坐标
        enum varENU_direction str_ctfx;//车头方向
        enum varENU_sjplace str_sjwz;//升降位置
        enum varENU_translationplace str_pywz;//平移位置

    }begin,now,next;
/*---------------------------------------------------------------函数声明-----*/
    void fun_delay(enum varENU_delaymodel par_model,ui par_value);//延时
    void fun_timer0init();//50毫秒定时器0初始化
    void fun_timer1init();//20毫秒定时器1初始化
    void fun_timer0();//50毫秒定时器0处理函数
    void fun_timer1();//20毫秒定时器1处理函数
    void fun_wait();//等待按键
    void fun_select(enum varENU_selectsensor par_model);//传感器片选
    void fun_initialization();//初始化函数
    void fun_pwminit();//PWM初始化
    void fun_pwmr(ui par_value);//右路PWM输出
    void fun_pwml(ui par_value);//左路PWM输出
    void fun_startdj(enum varENU_motor par_model,char par_speed);//启动电机
    void stop(enum varENU_motor par_model);//停止电机
/*---------------------------------------------------------------更新日志-----*/