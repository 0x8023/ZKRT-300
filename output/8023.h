#ifndef __8023_H__
#define __8023_H__
/*-------------------------------------------------------------头文件引入-----*/
    #include "STC12c5a60s2.h"   //单片机头文件
    #include "intrins.h"        //_nop_与循环位移
    #include "math.h"           //数学运算
    #include "string.h"         //字符串
    #include "stdio.h"          //串口调戏
    #include "stdarg.h"         //可变参数
/*----------------------------------------------------------define 宏定义-----*/
    #define def_timer0start TR0=1;  //定时器0开启
    #define def_timer0stop TR0=0;   //定时器0关闭
    #define def_timer1start TR1=1;  //定时器1开启
    #define def_timer1stop TR1=0;   //定时器1关闭
    #define def_end 0xFF            //不确定元素结束标志位
    #define def_select(par_model) out_switchselect=par_model==sel_58?0:1;//传感器片选
    #define def_start(par_x,par_y,par_ctfx,par_szzt,par_sjwz,par_pywz,par_hzfx) \
    /*不分频*/        CLK_DIV=0x00;\
    /*P0用于输入*/    P0M1=0xff;\
    /*P0不能输出*/    P0M0=0x00;\
    /*P1口0-1双向*/   P1M1=0x00;\
    /*P1口2-7输出*/   P1M0=0xfc;\
    /*P2口4-7输入*/   P2M1=0xf0;\
    /*P2口0-3输出*/   P2M0=0x0f;\
    /*-------------*/ \
    /*电机1/3使能*/   out_en1=1;\
    /*电机2/4使能*/   out_en2=1;\
    /*电机片选为0*/   out_motorselect=0;\
                      \
    /*PWM的初始化*/   fun_pwminit();\
    /*初始化定时器0*/ fun_timer0init();\
    /*初始化定时器1*/ fun_timer1init();\
    /*初始化串口*/    fun_port();\
    /*打开定时器0*/   TR0=1;\
    /*-------------*/ \
    /*X坐标*/         str_begin.x=par_x;\
    /*Y坐标*/         str_begin.y=par_y;\
    /*车头方向*/      str_begin.ctfx=par_ctfx;\
    /*手抓状态*/      str_begin.szzt=par_szzt;\
    /*升降位置*/      str_begin.sjwz=par_sjwz;\
    /*平移位置*/      str_begin.pywz=par_pywz;\
    /*回转方向*/      str_begin.hzfx=par_hzfx;\
    /*-------------*/ \
    /*速度归零*/      str_tfl.gospeed=0;\
    /*手抓速度归零*/  fun_motors(mot_sz,0);\
    /*平移速度归零*/  fun_motors(mot_py,0);\
    /*手抓速度归零*/  fun_motors(mot_sj,0);\
    /*手抓速度归零*/  fun_motors(mot_hz,0);\
    /*左右速度归零*/  fun_motors(mot_rl,0);\
    /*-------------*/ \
    /*按键置1*/       in_start=1;\
    /*输出Ready!*/    MSG("Ready!")\
    /*等待按键*/      fun_wait();
    #define def_stop EA=0;\
    /*速度归零*/     str_tfl.gospeed=0;\
    /*手抓速度归零*/ fun_motors(mot_sz,0);\
    /*平移速度归零*/ fun_motors(mot_py,0);\
    /*手抓速度归零*/ fun_motors(mot_sj,0);\
    /*手抓速度归零*/ fun_motors(mot_hz,0);\
    /*左右速度归零*/ fun_motors(mot_rl,0);\
    /*死循环*/       while(1);
/*-------------------------------------------------------------简化宏定义-----*/
    #define D(par_ms) fun_delay(par_ms,del_ms);
    #define J fun_sz1(han_j);
    #define S fun_sz1(han_s);
    #define WZ1 fun_sj1(sjp_1);
    #define WZ2 fun_sj1(sjp_2);
    #define WZ3 fun_sj1(sjp_3);
    #define WZ4 fun_sj1(sjp_4);
    #define WZ5 fun_sj1(sjp_5);
    #define MSG(par_value) printf("%s\n",par_value);
    #define OUT(par_value) printf("%d\n",par_value);
/*-----------------------------------------------------------变量类型说明-----*/
    typedef unsigned int ui;       //unsigned int --> ui
    typedef unsigned char uc;  //unsigned char uc --> uc
    typedef unsigned int* pui;     //unsigned int --> pui
    typedef unsigned char* puc;   //unsigned char --> puc
    typedef int* pi;                       //int* --> pi
    typedef char* pc;                     //char* --> pc
    typedef unsigned long ul;     //unsigned long --> ul
/*-----------------------------------------------------------------In Put-----*/
    sbit in_start=P3^2; //启动按键(start_)
    sbit in_ls1=P0^7;   //1号传感器(靠近左侧,下侧传感器灯,无信号低电平)
    sbit in_ls2=P0^6;   //2号传感器
    sbit in_ls3=P0^5;   //3号传感器
    sbit in_ls4=P0^4;   //4号传感器
    sbit in_ls5=P0^3;   //5号传感器
    sbit in_ls6=P0^2;   //6号传感器
    sbit in_ls7=P0^1;   //7号传感器
    sbit in_ls8=P0^0;   //8号传感器(靠近右侧,上侧传感器灯)

    sbit in_j=P3^4;     //手抓紧传感器
    sbit in_s=P3^3;     //手抓松传感器
    sbit in_qpy=P3^5;   //平移前平移传感器
    sbit in_hpy=P3^6;   //平移后平移传感器

    sbit in_wz1=P2^4;   //升降位置1传感器(最上位)
    sbit in_wz2=P2^5;   //升降位置2传感器
    sbit in_wz3=P2^6;   //升降位置3传感器
    sbit in_wz4=P2^7;   //升降位置4传感器

    sbit in_wz5=P2^4;   //升降位置5传感器(最下位)
    sbit in_hz=P2^5;    //回转传感器
/*----------------------------------------------------------------Out Put-----*/
    sbit out_pwmr=P1^2;         //PWMR的正反转控制位,1代表正(DIR_R)
    sbit out_pwml=P1^5;         //PWML的正反转控制位,1代表正(DIR_L)
    sbit out_dir1=P2^0;         //电机1/3方向(MOT_DIR1)
    sbit out_en1=P2^1;          //电机1/3使能(MOT_EN1)
    sbit out_dir2=P2^2;         //电机2/4方向(MOT_DIR2)
    sbit out_en2=P2^3;          //电机2/4使能(MOT_EN2)
    sbit out_switchselect=P1^6; //接近开关片选(SER_BS)
    sbit out_motorselect=P1^7;  //电机输出片选(MOT_BS)
    sbit out_lamp=P3^7;         //红外输出(LAMP)(低电平打开)
/*---------------------------------------------------------------变量声明-----*/
    enum varENU_tf{
        tf_null=0,
        tf_ture=1,
        tf_false=2
    };//判断用的,空,对和错
    enum varENU_del{
        del_us=10,
        del_ms=11,
        del_s=12
    };//延时模式选择
    enum varENU_sel{
        sel_58=20,
        sel_912=21
    };//传感器片选
    enum varENU_mot{
        mot_l=30,
        mot_r=31,
        mot_rl=32,
        mot_sz=33,   //电机1
        mot_py=34,   //电机2
        mot_sj=35,   //电机3
        mot_hz=36    //电机4
    };//电机选择
    enum varENU_dir{
        dir_up=40,
        dir_down=41,
        dir_left=42,
        dir_right=43
    };//方向
    enum varENU_tra{
        tra_q=50,//没有电机的一方
        tra_kq=51,
        tra_z=52,
        tra_kh=53,
        tra_h=54//有电机的一方
    };//平移位置
    enum varENU_sjp{
        sjp_1=60,
        sjp_12=61,
        sjp_2=62,
        sjp_23=63,
        sjp_3=64,
        sjp_34=65,
        sjp_4=66,
        sjp_45=67,
        sjp_5=68
    };//升降位置
    enum varENU_han{
        han_j=70,
        han_s=71
    };//手抓状态
    enum varENU_tur{
        tur_l90=80,
        tur_r90=81,
        tur_l180=82,
        tur_r180=83
    };//转弯模式
    enum varENU_tfl{
        tfl_line=90,    //巡线
        tfl_cache=91,   //前冲
        tfl_turn=92,    //转弯
        tfl_start=93,   //带加速的前冲
        tfl_end=94      //带减速的前冲
    };//定时器巡线执行动作

    struct str_state{
        char x;                 //X坐标
        char y;                 //Y坐标
        char szsd;              //手抓速度
        char pysd;              //平移速度
        char sjsd;              //升降速度
        char hzsd;              //回转速度
        char leftsd;            //左轮电机速度
        char rightsd;           //右轮电机速度
        enum varENU_dir ctfx;   //车头方向
        enum varENU_han szzt;   //手抓状态
        enum varENU_sjp sjwz;   //升降位置
        enum varENU_tra pywz;   //平移位置
        enum varENU_dir hzfx;   //回转方向
    };
    struct str_parameter{
        ui mlinerqd; //默认主函数巡线软起动时间为500毫秒
        ui mlineqc;  //默认主函数巡线前冲时间为500毫秒

        ui sj1bzw;   //升降标准位延时
        ui sj1zjw;   //升降中间位延时

        uc py1bz;    //fun_py1标准位延时
        ui py1qkq;   //fun_py1前到靠前延时参数
        ui py1kqz;   //fun_py1靠前到中间延时
        ui py1zkh;   //fun_py1中间到靠后延时
        ui py1khh;   //fun_py1靠后到后延时
        ui py1qz;    //fun_py1前到中间延时
        ui py1zh;    //fun_py1中间到后延时
        ui py1kqkh;  //fun_py1靠前到靠后延时
        ui py1qkh;   //fun_py1前到靠后延时
        ui py1kqh;   //fun_py1靠前到后延时

        ui hz1bz;    //fun_hz1标准位延时

        ui turn90;   //90度转弯屏蔽延时
        ui turn180;  //180度转弯屏蔽延时
    };//参数
    struct str_timerfolline{
        char step[32];      //步骤参数数据
        pc run;             //正在运行的步骤(指针)
        char gospeed;       //运巡线行速度
        char turnspeed;     //转弯运行速度
        char doing;         //正在移动标志位
        char online;        //在线标志位
        ul delay;           //延时变量
    };//定时器移动
    extern xdata struct str_state str_begin,str_now,str_next;   //分别为:起始状态/当前状态/目标状态
    extern xdata struct str_parameter str_cod;                  //一些固定的参数,一般保持默认即可
    extern xdata struct str_timerfolline str_tfl;               //定时器巡线
    extern ul var_timer0;                                       //timer0毫秒级计时器计数位
/*---------------------------------------------------------------函数声明-----*/
    extern void fun_delay(ui par_value,enum varENU_del par_model); //延时
    extern void fun_timer0init();//1毫秒定时器0初始化
    extern void fun_timer1init();//20毫秒定时器1初始化
    extern void fun_timer0();//1毫秒定时器0处理函数
    extern void fun_timer1();//20毫秒定时器1处理函数
    extern void fun_wait();//等待按键
    extern void fun_pwminit();//PWM初始化
    extern void fun_pwmr(uc par_value);//右路PWM输出
    extern void fun_pwml(uc par_value);//左路PWM输出
    extern void fun_motors(enum varENU_mot par_model,char par_speed);//操作电机
    extern void fun_sz1(enum varENU_han par_model);//手抓单步运动
    extern void fun_sj1(enum varENU_sjp par_model);//升降单步运动
    extern void fun_py1(enum varENU_tra par_model);//平移单步运动
    extern void fun_hz1(enum varENU_dir par_model);//回转单步运动
    extern void fun_dtjp();//动态纠偏
    extern void fun_jtjp();//静态纠偏
    extern void fun_timermove();//定时器移动
    extern void fun_stope2prom();//停止EEPROM服务
    extern uc   fun_reade2prom(ui par_add);//读取EEPROM数据
    extern void fun_writee2prom(ui par_add,uc par_dat);//写入数据至EEPROM
    extern void fun_cleane2prom(ui par_add);//清除EEPROM数据
    extern void fun_calibration();//自动校准参数
    extern void fun_port();//串口初始化
    extern void fun_test();//测试
    extern uc   fun_min(uc par_num,...);//求最小值
    extern void fun_coordinate();//自动巡线之坐标

/*---------------------------------------------------------------更新日志-----*/
#endif