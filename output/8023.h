#ifndef __8023_H__
#define __8023_H__
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
    #define def_start(par_x,par_y,par_ctfx,par_szzt,par_sjwz,par_pywz,par_hzfx) \
    /*初始化*/        fun_initialization();\
    /*X坐标*/         str_begin.x=par_x;\
    /*Y坐标*/         str_begin.y=par_y;\
    /*车头方向*/      str_begin.ctfx=par_ctfx;\
    /*手抓状态*/      str_begin.szzt=par_szzt;\
    /*升降位置*/      str_begin.sjwz=par_sjwz;\
    /*平移位置*/      str_begin.pywz=par_pywz;\
    /*回转方向*/      str_begin.hzfx=par_hzfx; 
    #define def_stop fun_stop(mot_dj1);\
                     fun_stop(mot_dj2);\
                     fun_stop(mot_dj3);\
                     fun_stop(mot_dj4);\
                     fun_stop(mot_rl);\
                     EA=0;\
                     while(1);
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
    typedef unsigned int* pui;     //unsigned int --> pui
    typedef unsigned char* puc;   //unsigned char --> puc
    typedef int* pi;                       //int* --> pi
    typedef char* pc;                     //char* --> pc
    typedef unsigned long ul;     //unsigned long --> ul
/*-----------------------------------------------------------------In Put-----*/
    sbit in_start=P3^2;//启动按键(start_)
    sbit in_ls1=P0^7;//1号传感器(靠近左侧,下侧传感器灯,无信号低电平)
    sbit in_ls2=P0^6;//2号传感器
    sbit in_ls3=P0^5;//3号传感器
    sbit in_ls4=P0^4;//4号传感器
    sbit in_ls5=P0^3;//5号传感器
    sbit in_ls6=P0^2;//6号传感器
    sbit in_ls7=P0^1;//7号传感器
    sbit in_ls8=P0^0;//8号传感器(靠近右侧,上侧传感器灯)

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
/*---------------------------------------------------------------变量声明-----*/
    enum varENU_del{
        del_us,
        del_ms,
        del_s
    };//延时模式选择
    enum varENU_sel{
        sel_58,
        sel_912
    };//传感器片选
    enum varENU_mot{
        mot_l,
        mot_r,
        mot_rl,
        mot_dj1,
        mot_dj2,
        mot_dj3,
        mot_dj4
    };//电机选择
    enum varENU_dir{
        dir_up,
        dir_down,
        dir_left,
        dir_right
    };//车头方向
    enum varENU_tra{
        tra_q,
        tra_kq,
        tra_z,
        tra_kh,
        tra_h
    };//平移位置
    enum varENU_sjp{
        sjp_wz1,
        sjp_wz12,
        sjp_wz2,
        sjp_wz23,
        sjp_wz3,
        sjp_wz34,
        sjp_wz4,
        sjp_wz45,
        sjp_wz5
    };//升降位置
    enum varENU_han{
        han_j,
        han_s
    };//手抓状态
    enum varENU_tur{
        tur_l,
        tur_r
    };//回转状态
    struct str_state{
        char x;//X坐标
        char y;//Y坐标
        enum varENU_dir ctfx;//车头方向
        enum varENU_han szzt;//手抓状态
        enum varENU_sjp sjwz;//升降位置
        enum varENU_tra pywz;//平移位置
        enum varENU_dir hzfx;//回转方向
    };

    extern xdata struct str_state str_begin,str_now,str_next;//分别为:起始状态/当前状态/目标状态
    extern xdata ui cod_mlinerqd,//主函数软起动时间(毫秒)
                    cod_mlineqc;//组函数前冲时间(毫秒)
/*---------------------------------------------------------------函数声明-----*/
    extern void fun_delay(ui par_value,enum varENU_del par_model);//延时
    extern void fun_timer0init();//50毫秒定时器0初始化
    extern void fun_timer1init();//20毫秒定时器1初始化
    extern void fun_timer0();//50毫秒定时器0处理函数
    extern void fun_timer1();//20毫秒定时器1处理函数
    extern void fun_wait();//等待按键
    extern void fun_select(enum varENU_sel par_model);//传感器片选
    extern void fun_initialization();//初始化函数
    extern void fun_pwminit();//PWM初始化
    extern void fun_pwmr(uc par_value);//右路PWM输出
    extern void fun_pwml(uc par_value);//左路PWM输出
    extern void fun_startdj(enum varENU_mot par_model,char par_speed);//启动电机
    extern void fun_stop(enum varENU_mot par_model);//停止电机
    extern void fun_sz1(enum varENU_han par_model);//手抓单步运动
    extern void fun_sj1(enum varENU_sjp par_model);//升降单步运动
    extern void fun_py1(enum varENU_tra par_model);//平移单步运动
    extern void fun_hz1(enum varENU_dir par_model);//回转单步运动
    extern void fun_mptline(uc par_num,uc par_sd,enum varENU_dir);//主函数普通巡线
/*---------------------------------------------------------------更新日志-----*/
#endif