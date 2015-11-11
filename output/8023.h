#ifndef __8023_H__
#define __8023_H__
/*-----------------------------------------------------------开启模式选择-----*/
    #define Debug ok
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
    #define def_end 0x82            //不确定元素结束标志位
    #define def_select(par_model) out_switchselect=par_model==sel_58?0:1; //传感器片选
/*-------------------------------------------------------------简化宏定义-----*/
    #ifndef __HANS_H__
        #define D(par_ms) fun_delay(par_ms,del_ms);         // D --> 延时(毫秒)
        
        #define J fun_sz(han_j);                            // J --> 手抓抓紧
        #define S fun_sz(han_s);                            // S --> 手抓松
        
        #define WZ1 fun_sj(sjp_1);                          // WZ1 --> 升降到位置1
        #define WZ2 fun_sj(sjp_2);                          // WZ2 --> 升降到位置2
        #define WZ3 fun_sj(sjp_3);                          // WZ3 --> 升降到位置3
        #define WZ4 fun_sj(sjp_4);                          // WZ4 --> 升降到位置4
        #define WZ5 fun_sj(sjp_5);                          // WZ5 --> 升降到位置5
        
        #define L(par_con) tfl_line,par_con                 // L --> 定时器巡线
        #define R90 tfl_turn,tur_r90                        // R90 --> 定时器右转90度
        #define L90 tfl_turn,tur_l90                        // L90 --> 定时器左转90度
        #define R180 tfl_turn,tur_r180                      // R180 --> 定时器右转180度
        #define L180 tfl_turn,tur_l180                      // L180 --> 定时器左转180度
        #define C(par_value) tfl_cache,par_value            // C --> 定时器前冲
        
        #define MSG(par_value) printf("%s\n",par_value);
        #define OUT(par_value) printf("%d\n",par_value);
    #endif
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
        tf_null=10,
        tf_ture=11,
        tf_false=12
    };//判断用的,空,对和错
    enum varENU_del{
        del_us=20,
        del_ms=21,
        del_s=22
    };//延时模式选择
    enum varENU_sel{
        sel_58=30,
        sel_912=31
    };//传感器片选
    enum varENU_mot{
        mot_l=40,
        mot_r=41,
        mot_rl=42,
        mot_sz=43,   //电机1
        mot_py=44,   //电机2
        mot_sj=45,   //电机3
        mot_hz=46,   //电机4
        mot_pyhz=47  //平移回转同步运动(仅自动抓件函数用到)
    };//电机选择
    enum varENU_dir{
        dir_up=50,
        dir_down=51,
        dir_left=52,
        dir_right=53
    };//方向
    enum varENU_tra{
        tra_q=60,//没有电机的一方
        tra_kq=61,
        tra_z=62,
        tra_kh=63,
        tra_h=64//有电机的一方
    };//平移位置
    enum varENU_sjp{
        sjp_1=70,
        sjp_12=71,
        sjp_2=72,
        sjp_23=73,
        sjp_3=74,
        sjp_34=75,
        sjp_4=76,
        sjp_45=77,
        sjp_5=78
    };//升降位置
    enum varENU_han{
        han_j=80,
        han_s=81
    };//手抓状态
    enum varENU_tur{
        tur_l90=90,
        tur_r90=91,
        tur_l180=92,
        tur_r180=93
    };//转弯模式
    enum varENU_tfl{
        tfl_line=100,    //巡线
        tfl_cache=101,   //前冲
        tfl_turn=102     //转弯
    };//定时器巡线执行动作
    enum varENU_go{
        gw_1=110,
        gw_2=111,
        gw_3=112,
        gw_4=113,
        gw_5=114,
        get=115,
        start=116,
        end=117
    };

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
        ui py1khkq;  //fun_py1靠后到靠前延时
        ui py1qkh;   //fun_py1前到靠后延时
        ui py1kqh;   //fun_py1靠前到后延时

        ui hz1bz;    //fun_hz1标准位延时

        ui mainturn90;    //主函数90度转弯屏蔽延时
        ui timerturn90;   //定时器90度转弯屏蔽延时
        ui mainturn180;   //主函数180度转弯屏蔽延时
        ui timerturn180;  //主函数180度转弯屏蔽延时
    };//参数
    struct str_timerfolline{
        char step[64];      //步骤参数数据
        pc run;             //正在运行的步骤(指针)
        char gospeed;       //运巡线行速度
        char turnspeed;     //转弯运行速度
        char cachespeed;    //前冲速度
        char doing;         //正在移动标志位
        char online;        //在线标志位
        ul delay;           //延时变量
    };//定时器移动
    struct str_xyproperties{
        uc enup;            //允许车头向上标志位
        uc endown;          //允许车头向下标志位
        uc enleft;          //允许车头向左标志位
        uc enright;         //允许车头向右标志位
        uc value;           //当前坐标是哪个工位的
        enum varENU_dir fx; //来到当前坐标的时候需要的朝向
    };//坐标的属性(绝对位置)
    struct str_coordinates{
        struct str_xyproperties xy[5][14];  //坐标(包括第Y=13的虚拟坐标)
        struct str_xyproperties top;        //最顶上呢个没坐标的
    };//坐标巡线
    struct str_zdzj{
        uc jx[8][5];        //件序:8个抓件区(从左上到左下0-3,从右上到右下4-7);5个高度(0-5),最上空位为0,从上到下1-4,底座为5
    };//自动抓件
    extern struct str_state str_begin,str_now,str_next;   //分别为:起始状态/当前状态/目标状态
    extern struct str_parameter str_cod;                  //一些固定的参数,一般保持默认即可
    extern struct str_timerfolline str_tfl;               //定时器巡线
    extern struct str_coordinates str_zbfl;               //坐标巡线
    extern data ul var_timer0;                            //timer0毫秒级计时器计数位
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
    extern void fun_motors(enum varENU_mot par_model,char par_speed);//主函数操作电机
    extern void fun_motorsrl(enum varENU_mot par_model,int par_speed);//定时器操作左右轮
    extern void fun_sz(enum varENU_han par_model);//手抓单步运动
    extern void fun_sj(enum varENU_sjp par_model);//升降单步运动
    extern void fun_py(enum varENU_tra par_model);//平移单步运动
    extern void fun_hz(enum varENU_dir par_model);//回转单步运动
    extern void fun_pyhz(enum varENU_tra par_pymodel,enum varENU_dir par_hzmodel);//平移回转同步运动
    extern void fun_sjhz(enum varENU_sjp par_sjmodel,enum varENU_dir par_hzmodel);//升降回转同步运动
    extern void fun_pysjhz(enum varENU_tra par_pymodel,enum varENU_sjp par_sjmodel,enum varENU_dir par_hzmodel);//平移升降回转同步运动(先升降回转,再平移回转)
    extern void fun_jtjp();//静态纠偏
    extern void fun_timermove();//定时器移动
    extern void fun_flsetting(char par_gospeed,char par_turnspeed,char par_cachespeed,...);//主函数用定时器巡线调用函数
    extern void fun_folline(uc par_con,uc par_speed);//主函数巡线
    extern void fun_turn(enum varENU_tur par_model,uc par_speed);//主函数转弯
    extern void fun_qc(uc par_time,uc par_speed);//主函数前冲
    extern void fun_stope2prom();//停止EEPROM服务
    extern uc   fun_reade2prom(ui par_add);//读取EEPROM数据
    extern void fun_writee2prom(ui par_add,uc par_dat);//写入数据至EEPROM
    extern void fun_cleane2prom(ui par_add);//清除EEPROM数据
    extern void fun_calibration();//自动校准参数
    extern void fun_port();//串口初始化
    extern void fun_test();//测试
    extern uc   fun_min(uc par_num,...);//求最小值
    extern void fun_setxy(uc par_1x,uc par_1y,uc par_1value,enum varENU_dir par_1fx,enum varENU_dir par_1gw,
           par_2x,uc par_2y,uc par_2value,enum varENU_dir par_2fx,enum varENU_dir par_2gw,
           par_3x,uc par_3y,uc par_3value,enum varENU_dir par_3fx,enum varENU_dir par_3gw,
           par_4x,uc par_4y,uc par_4value,enum varENU_dir par_4fx,enum varENU_dir par_4gw,
           uc par_5value,uc par_5fx);
    extern void fun_pbxy(uc par_x,uc par_y,enum varENU_dir par_fx,enum varENU_dir par_gw);//通过工件的朝向和小车的车头方向屏蔽坐标
    extern void fun_getxy(char par_value);//通过想要去的工位号获得XY坐标并储存在str_next结构体中
    extern void fun_xymove(enum varENU_tfl par_model,char par_value);//坐标巡线单步累计步骤生成
    extern char fun_getpublicy(char par_xnow,char par_ynow,char par_xnext,char par_ynext,enum varENU_dir par_gwfx);//获取共有Y轴
    extern void fun_record(char par_xnow,char par_ynow,enum varENU_dir par_ctfxnow,char par_xnext,char par_ynext,enum varENU_dir par_ctfxnext);//定时器坐标巡线步骤生成
    extern void fun_go(enum varENU_go par_model);//定时器坐标巡线最终调用形式
    extern void fun_coordinate(char par_gospeed,char par_turnspeed,char par_cachespeed);//自动巡线之坐标
    extern void fun_maintfl();//主函数设置定时器等待巡线结束函数
    extern void fun_zbtfl();//坐标巡线设置定时器等待巡线结束函数
    extern void fun_zdzj(ul par_che,ul par_tai);//自动抓件
    extern void fun_zjzt(uc par_motor,uc par_model);//抓件状态
    extern void fun_najian(uc par_now,uc par_next,char par_high[8],uc par_data[8][5]);//拿件(配合自动抓件使用)
    extern void fun_zhuajian();//从起始区走到抓件区
    extern void fun_back90();//从抓件区回到起始区
    extern void fun_start(char par_x,char par_y,enum varENU_dir par_ctfx,//初始化函数
                enum varENU_han par_szzt,enum varENU_sjp par_sjwz,enum varENU_tra par_pywz,enum varENU_dir par_hzfx);
    extern void fun_stop();//结束函数
/*-----------------------------------------------------------调试函数声明-----*/
    #ifdef Debug
        extern void deb_outstep(uc par_model);//输出定时器巡线数组
    #endif
/*---------------------------------------------------------------更新日志-----*/
#endif