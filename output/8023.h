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
    /*回转方向*/      str_begin.hzfx=par_hzfx;\
                      MSG("Ready!")
    #define def_stop fun_stop(mot_dj1);\
                     fun_stop(mot_dj2);\
                     fun_stop(mot_dj3);\
                     fun_stop(mot_dj4);\
                     fun_stop(mot_rl);\
                     EA=0;\
                     while(1);
/*-------------------------------------------------------------简化宏定义-----*/
    #define D(par_ms) fun_delay(par_ms,del_ms);
    #define J fun_sz1(han_j);
    #define S fun_sz1(han_s);
    #define WZ1 fun_sj1(sjp_wz1);
    #define WZ2 fun_sj1(sjp_wz2);
    #define WZ3 fun_sj1(sjp_wz3);
    #define WZ4 fun_sj1(sjp_wz4);
    #define WZ5 fun_sj1(sjp_wz5);
    #define MSG(par_value) printf("%s \n",par_value);
    #define OUT(par_value) printf("%d \n",par_value);
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
    sbit out_lamp=P3^7;//红外输出(LAMP)(低电平打开)
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
        tra_q,//没有电机的一方
        tra_kq,
        tra_z,
        tra_kh,
        tra_h//有电机的一方
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
    struct str_parameter{
        ui mlinerqd;//默认主函数巡线软起动时间为500毫秒
        ui mlineqc;//默认主函数巡线前冲时间为500毫秒

        ui sj1bzw;
        ui sj1zjw;

        ui py1qkq;
        ui py1kqz;
        ui py1zkh;
        ui py1khh;
        ui py1qz;
        ui py1zh;
        ui py1kqkh;
        ui py1qkh;
        ui py1kqh;
    };//参数

    extern xdata struct str_state str_begin,str_now,str_next;//分别为:起始状态/当前状态/目标状态
    extern xdata struct str_parameter str_cod;
    extern ui var_timer0;
/*---------------------------------------------------------------函数声明-----*/
    extern void fun_delay(ui par_value,enum varENU_del par_model);//延时
    extern void fun_timer0init();//1毫秒定时器0初始化
    extern void fun_timer1init();//20毫秒定时器1初始化
    extern void fun_timer0();//1毫秒定时器0处理函数
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
    extern void fun_sj2(char par_value);//升降第一次重写,用来配合抓件
    extern void fun_pyhz2(enum varENU_tra par_py,enum varENU_dir par_hz);//平移回转同步运动,用来配合升降
    extern void fun_planezt(uc par_model);
    extern void fun_mptline(uc par_num,uc par_sd,enum varENU_dir);//主函数普通巡线
    extern void fun_stope2prom();//停止EEPROM服务
    extern uc fun_reade2prom(ui par_add);//读取EEPROM数据
    extern void fun_writee2prom(ui par_add,uc par_dat);//写入数据至EEPROM
    extern void fun_cleane2prom(ui par_add);//清除EEPROM数据
    extern void fun_calibration();//自动校准参数
    extern void fun_port();//串口初始化
    extern void fun_zhuajian(uc par_01,uc par_02,uc par_03,uc par_04,//自动抓件
                             uc par_41,uc par_42,uc par_43,uc par_44,
                             uc par_31,uc par_32,uc par_33,uc par_34,
                             uc par_71,uc par_72,uc par_73,uc par_74);
    extern uc fun_min(uc par_num,...);//求最小值
/*---------------------------------------------------------------更新日志-----*/
#endif