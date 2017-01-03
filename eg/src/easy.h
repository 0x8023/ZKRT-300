#ifndef __EASY_H__
#define __EASY_H__

//等待按键
	#define WT {fun_wait();}

//手抓单步运动
	#define SJ {fun_sz(han_j);}
	#define SS {fun_sz(han_s);}

//平移单步运动
	#define PQ {fun_py(tra_q);}
	#define PKQ {fun_py(tra_kq);}
	#define PZ {fun_py(tra_z);}
	#define PKH {fun_py(tra_kh);}
	#define PH {fun_py(tra_h);}

//升降单步运动
	#define J1 {fun_sj(sjp_1);}
	#define J12 {fun_sj(sjp_12);}
	#define J2 {fun_sj(sjp_2);}
	#define J23 {fun_sj(sjp_23);}
	#define J3 {fun_sj(sjp_3);}
	#define J34 {fun_sj(sjp_34);}
	#define J4 {fun_sj(sjp_4);}
	#define J45 {fun_sj(sjp_45);}
	#define J5 {fun_sj(sjp_5);}

//回转单步运动
	#define HS {fun_hz(dir_up);}
	#define HX {fun_hz(dir_down);}
	#define HZ {fun_hz(dir_left);}
	#define HY {fun_hz(dir_right);}

//回转平移同步
    #define SQ {fun_pyhz(tra_q,dir_up);}
    #define SKQ {fun_pyhz(tra_kq,dir_up);}
    #define SZ {fun_pyhz(tra_z,dir_up);}
    #define SKH {fun_pyhz(tra_kh,dir_up);}
    #define SH {fun_pyhz(tra_h,dir_up);}

    #define XQ {fun_pyhz(tra_q,dir_down);}
    #define XKQ {fun_pyhz(tra_kq,dir_down);}
    #define XZ {fun_pyhz(tra_z,dir_down);}
    #define XKH {fun_pyhz(tra_kh,dir_down);}
    #define XH {fun_pyhz(tra_h,dir_down);}

    #define ZQ {fun_pyhz(tra_q,dir_left);}
    #define ZKQ {fun_pyhz(tra_kq,dir_left);}
    #define ZZ {fun_pyhz(tra_z,dir_left);}
    #define ZKH {fun_pyhz(tra_kh,dir_left);}
    #define ZH {fun_pyhz(tra_h,dir_left);}

    #define YQ {fun_pyhz(tra_q,dir_right);}
    #define YKQ {fun_pyhz(tra_kq,dir_right);}
    #define YZ {fun_pyhz(tra_z,dir_right);}
    #define YKH {fun_pyhz(tra_kh,dir_right);}
    #define YH {fun_pyhz(tra_h,dir_right);}

//升降回转同步运动
	#define S1 {fun_sjhz(sjp_1,dir_up);}
	#define S12 {fun_sjhz(sjp_12,dir_up);}
	#define S2 {fun_sjhz(sjp_2,dir_up);}
	#define S23 {fun_sjhz(sjp_23,dir_up);}
	#define S3 {fun_sjhz(sjp_3,dir_up);}
	#define S34 {fun_sjhz(sjp_34,dir_up);}
	#define S4 {fun_sjhz(sjp_4,dir_up);}
	#define S45 {fun_sjhz(sjp_45,dir_up);}
	#define S5 {fun_sjhz(sjp_5,dir_up);}

	#define X1 {fun_sjhz(sjp_1,dir_down);}
	#define X12 {fun_sjhz(sjp_12,dir_down);}
	#define X2 {fun_sjhz(sjp_2,dir_down);}
	#define X23 {fun_sjhz(sjp_23,dir_down);}
	#define X3 {fun_sjhz(sjp_3,dir_down);}
	#define X34 {fun_sjhz(sjp_34,dir_down);}
	#define X4 {fun_sjhz(sjp_4,dir_down);}
	#define X45 {fun_sjhz(sjp_45,dir_down);}
	#define X5 {fun_sjhz(sjp_5,dir_down);}

	#define Z1 {fun_sjhz(sjp_1,dir_left);}
	#define Z12 {fun_sjhz(sjp_12,dir_left);}
	#define Z2 {fun_sjhz(sjp_2,dir_left);}
	#define Z23 {fun_sjhz(sjp_23,dir_left);}
	#define Z3 {fun_sjhz(sjp_3,dir_left);}
	#define Z34 {fun_sjhz(sjp_34,dir_left);}
	#define Z4 {fun_sjhz(sjp_4,dir_left);}
	#define Z45 {fun_sjhz(sjp_45,dir_left);}
	#define Z5 {fun_sjhz(sjp_5,dir_left);}

	#define Y1 {fun_sjhz(sjp_1,dir_right);}
	#define Y12 {fun_sjhz(sjp_12,dir_right);}
	#define Y2 {fun_sjhz(sjp_2,dir_right);}
	#define Y23 {fun_sjhz(sjp_23,dir_right);}
	#define Y3 {fun_sjhz(sjp_3,dir_right);}
	#define Y34 {fun_sjhz(sjp_34,dir_right);}
	#define Y4 {fun_sjhz(sjp_4,dir_right);}
	#define Y45 {fun_sjhz(sjp_45,dir_right);}
	#define Y5 {fun_sjhz(sjp_5,dir_right);}
	
	
//升降回转平移同步运动
	#define SQ1 {fun_pysjhz(tra_q,sjp_1,dir_up);}
	#define SQ12 {fun_pysjhz(tra_q,sjp_12,dir_up);}
	#define SQ2 {fun_pysjhz(tra_q,sjp_2,dir_up);}
	#define SQ23 {fun_pysjhz(tra_q,sjp_23,dir_up);}
	#define SQ3 {fun_pysjhz(tra_q,sjp_3,dir_up);}
	#define SQ34 {fun_pysjhz(tra_q,sjp_34,dir_up);}
	#define SQ4 {fun_pysjhz(tra_q,sjp_4,dir_up);}
	#define SQ45 {fun_pysjhz(tra_q,sjp_45,dir_up);}
	#define SQ5 {fun_pysjhz(tra_q,sjp_5,dir_up);}
	#define XQ1 {fun_pysjhz(tra_q,sjp_1,dir_down);}
	#define XQ12 {fun_pysjhz(tra_q,sjp_12,dir_down);}
	#define XQ2 {fun_pysjhz(tra_q,sjp_2,dir_down);}
	#define XQ23 {fun_pysjhz(tra_q,sjp_23,dir_down);}
	#define XQ3 {fun_pysjhz(tra_q,sjp_3,dir_down);}
	#define XQ34 {fun_pysjhz(tra_q,sjp_34,dir_down);}
	#define XQ4 {fun_pysjhz(tra_q,sjp_4,dir_down);}
	#define XQ45 {fun_pysjhz(tra_q,sjp_45,dir_down);}
	#define XQ5 {fun_pysjhz(tra_q,sjp_5,dir_down);}
	#define ZQ1 {fun_pysjhz(tra_q,sjp_1,dir_left);}
	#define ZQ12 {fun_pysjhz(tra_q,sjp_12,dir_left);}
	#define ZQ2 {fun_pysjhz(tra_q,sjp_2,dir_left);}
	#define ZQ23 {fun_pysjhz(tra_q,sjp_23,dir_left);}
	#define ZQ3 {fun_pysjhz(tra_q,sjp_3,dir_left);}
	#define ZQ34 {fun_pysjhz(tra_q,sjp_34,dir_left);}
	#define ZQ4 {fun_pysjhz(tra_q,sjp_4,dir_left);}
	#define ZQ45 {fun_pysjhz(tra_q,sjp_45,dir_left);}
	#define ZQ5 {fun_pysjhz(tra_q,sjp_5,dir_left);}
	#define YQ1 {fun_pysjhz(tra_q,sjp_1,dir_right);}
	#define YQ12 {fun_pysjhz(tra_q,sjp_12,dir_right);}
	#define YQ2 {fun_pysjhz(tra_q,sjp_2,dir_right);}
	#define YQ23 {fun_pysjhz(tra_q,sjp_23,dir_right);}
	#define YQ3 {fun_pysjhz(tra_q,sjp_3,dir_right);}
	#define YQ34 {fun_pysjhz(tra_q,sjp_34,dir_right);}
	#define YQ4 {fun_pysjhz(tra_q,sjp_4,dir_right);}
	#define YQ45 {fun_pysjhz(tra_q,sjp_45,dir_right);}
	#define YQ5 {fun_pysjhz(tra_q,sjp_5,dir_right);}

	#define SKQ1 {fun_pysjhz(tra_kq,sjp_1,dir_up);}
	#define SKQ12 {fun_pysjhz(tra_kq,sjp_12,dir_up);}
	#define SKQ2 {fun_pysjhz(tra_kq,sjp_2,dir_up);}
	#define SKQ23 {fun_pysjhz(tra_kq,sjp_23,dir_up);}
	#define SKQ3 {fun_pysjhz(tra_kq,sjp_3,dir_up);}
	#define SKQ34 {fun_pysjhz(tra_kq,sjp_34,dir_up);}
	#define SKQ4 {fun_pysjhz(tra_kq,sjp_4,dir_up);}
	#define SKQ45 {fun_pysjhz(tra_kq,sjp_45,dir_up);}
	#define SKQ5 {fun_pysjhz(tra_kq,sjp_5,dir_up);}
	#define XKQ1 {fun_pysjhz(tra_kq,sjp_1,dir_down);}
	#define XKQ12 {fun_pysjhz(tra_kq,sjp_12,dir_down);}
	#define XKQ2 {fun_pysjhz(tra_kq,sjp_2,dir_down);}
	#define XKQ23 {fun_pysjhz(tra_kq,sjp_23,dir_down);}
	#define XKQ3 {fun_pysjhz(tra_kq,sjp_3,dir_down);}
	#define XKQ34 {fun_pysjhz(tra_kq,sjp_34,dir_down);}
	#define XKQ4 {fun_pysjhz(tra_kq,sjp_4,dir_down);}
	#define XKQ45 {fun_pysjhz(tra_kq,sjp_45,dir_down);}
	#define XKQ5 {fun_pysjhz(tra_kq,sjp_5,dir_down);}
	#define ZKQ1 {fun_pysjhz(tra_kq,sjp_1,dir_left);}
	#define ZKQ12 {fun_pysjhz(tra_kq,sjp_12,dir_left);}
	#define ZKQ2 {fun_pysjhz(tra_kq,sjp_2,dir_left);}
	#define ZKQ23 {fun_pysjhz(tra_kq,sjp_23,dir_left);}
	#define ZKQ3 {fun_pysjhz(tra_kq,sjp_3,dir_left);}
	#define ZKQ34 {fun_pysjhz(tra_kq,sjp_34,dir_left);}
	#define ZKQ4 {fun_pysjhz(tra_kq,sjp_4,dir_left);}
	#define ZKQ45 {fun_pysjhz(tra_kq,sjp_45,dir_left);}
	#define ZKQ5 {fun_pysjhz(tra_kq,sjp_5,dir_left);}
	#define YKQ1 {fun_pysjhz(tra_kq,sjp_1,dir_right);}
	#define YKQ12 {fun_pysjhz(tra_kq,sjp_12,dir_right);}
	#define YKQ2 {fun_pysjhz(tra_kq,sjp_2,dir_right);}
	#define YKQ23 {fun_pysjhz(tra_kq,sjp_23,dir_right);}
	#define YKQ3 {fun_pysjhz(tra_kq,sjp_3,dir_right);}
	#define YKQ34 {fun_pysjhz(tra_kq,sjp_34,dir_right);}
	#define YKQ4 {fun_pysjhz(tra_kq,sjp_4,dir_right);}
	#define YKQ45 {fun_pysjhz(tra_kq,sjp_45,dir_right);}
	#define YKQ5 {fun_pysjhz(tra_kq,sjp_5,dir_right);}

	#define SZ1 {fun_pysjhz(tra_z,sjp_1,dir_up);}
	#define SZ12 {fun_pysjhz(tra_z,sjp_12,dir_up);}
	#define SZ2 {fun_pysjhz(tra_z,sjp_2,dir_up);}
	#define SZ23 {fun_pysjhz(tra_z,sjp_23,dir_up);}
	#define SZ3 {fun_pysjhz(tra_z,sjp_3,dir_up);}
	#define SZ34 {fun_pysjhz(tra_z,sjp_34,dir_up);}
	#define SZ4 {fun_pysjhz(tra_z,sjp_4,dir_up);}
	#define SZ45 {fun_pysjhz(tra_z,sjp_45,dir_up);}
	#define SZ5 {fun_pysjhz(tra_z,sjp_5,dir_up);}
	#define XZ1 {fun_pysjhz(tra_z,sjp_1,dir_down);}
	#define XZ12 {fun_pysjhz(tra_z,sjp_12,dir_down);}
	#define XZ2 {fun_pysjhz(tra_z,sjp_2,dir_down);}
	#define XZ23 {fun_pysjhz(tra_z,sjp_23,dir_down);}
	#define XZ3 {fun_pysjhz(tra_z,sjp_3,dir_down);}
	#define XZ34 {fun_pysjhz(tra_z,sjp_34,dir_down);}
	#define XZ4 {fun_pysjhz(tra_z,sjp_4,dir_down);}
	#define XZ45 {fun_pysjhz(tra_z,sjp_45,dir_down);}
	#define XZ5 {fun_pysjhz(tra_z,sjp_5,dir_down);}
	#define ZZ1 {fun_pysjhz(tra_z,sjp_1,dir_left);}
	#define ZZ12 {fun_pysjhz(tra_z,sjp_12,dir_left);}
	#define ZZ2 {fun_pysjhz(tra_z,sjp_2,dir_left);}
	#define ZZ23 {fun_pysjhz(tra_z,sjp_23,dir_left);}
	#define ZZ3 {fun_pysjhz(tra_z,sjp_3,dir_left);}
	#define ZZ34 {fun_pysjhz(tra_z,sjp_34,dir_left);}
	#define ZZ4 {fun_pysjhz(tra_z,sjp_4,dir_left);}
	#define ZZ45 {fun_pysjhz(tra_z,sjp_45,dir_left);}
	#define ZZ5 {fun_pysjhz(tra_z,sjp_5,dir_left);}
	#define YZ1 {fun_pysjhz(tra_z,sjp_1,dir_right);}
	#define YZ12 {fun_pysjhz(tra_z,sjp_12,dir_right);}
	#define YZ2 {fun_pysjhz(tra_z,sjp_2,dir_right);}
	#define YZ23 {fun_pysjhz(tra_z,sjp_23,dir_right);}
	#define YZ3 {fun_pysjhz(tra_z,sjp_3,dir_right);}
	#define YZ34 {fun_pysjhz(tra_z,sjp_34,dir_right);}
	#define YZ4 {fun_pysjhz(tra_z,sjp_4,dir_right);}
	#define YZ45 {fun_pysjhz(tra_z,sjp_45,dir_right);}
	#define YZ5 {fun_pysjhz(tra_z,sjp_5,dir_right);}

	#define SKH1 {fun_pysjhz(tra_kh,sjp_1,dir_up);}
	#define SKH12 {fun_pysjhz(tra_kh,sjp_12,dir_up);}
	#define SKH2 {fun_pysjhz(tra_kh,sjp_2,dir_up);}
	#define SKH23 {fun_pysjhz(tra_kh,sjp_23,dir_up);}
	#define SKH3 {fun_pysjhz(tra_kh,sjp_3,dir_up);}
	#define SKH34 {fun_pysjhz(tra_kh,sjp_34,dir_up);}
	#define SKH4 {fun_pysjhz(tra_kh,sjp_4,dir_up);}
	#define SKH45 {fun_pysjhz(tra_kh,sjp_45,dir_up);}
	#define SKH5 {fun_pysjhz(tra_kh,sjp_5,dir_up);}
	#define XKH1 {fun_pysjhz(tra_kh,sjp_1,dir_down);}
	#define XKH12 {fun_pysjhz(tra_kh,sjp_12,dir_down);}
	#define XKH2 {fun_pysjhz(tra_kh,sjp_2,dir_down);}
	#define XKH23 {fun_pysjhz(tra_kh,sjp_23,dir_down);}
	#define XKH3 {fun_pysjhz(tra_kh,sjp_3,dir_down);}
	#define XKH34 {fun_pysjhz(tra_kh,sjp_34,dir_down);}
	#define XKH4 {fun_pysjhz(tra_kh,sjp_4,dir_down);}
	#define XKH45 {fun_pysjhz(tra_kh,sjp_45,dir_down);}
	#define XKH5 {fun_pysjhz(tra_kh,sjp_5,dir_down);}
	#define ZKH1 {fun_pysjhz(tra_kh,sjp_1,dir_left);}
	#define ZKH12 {fun_pysjhz(tra_kh,sjp_12,dir_left);}
	#define ZKH2 {fun_pysjhz(tra_kh,sjp_2,dir_left);}
	#define ZKH23 {fun_pysjhz(tra_kh,sjp_23,dir_left);}
	#define ZKH3 {fun_pysjhz(tra_kh,sjp_3,dir_left);}
	#define ZKH34 {fun_pysjhz(tra_kh,sjp_34,dir_left);}
	#define ZKH4 {fun_pysjhz(tra_kh,sjp_4,dir_left);}
	#define ZKH45 {fun_pysjhz(tra_kh,sjp_45,dir_left);}
	#define ZKH5 {fun_pysjhz(tra_kh,sjp_5,dir_left);}
	#define YKH1 {fun_pysjhz(tra_kh,sjp_1,dir_right);}
	#define YKH12 {fun_pysjhz(tra_kh,sjp_12,dir_right);}
	#define YKH2 {fun_pysjhz(tra_kh,sjp_2,dir_right);}
	#define YKH23 {fun_pysjhz(tra_kh,sjp_23,dir_right);}
	#define YKH3 {fun_pysjhz(tra_kh,sjp_3,dir_right);}
	#define YKH34 {fun_pysjhz(tra_kh,sjp_34,dir_right);}
	#define YKH4 {fun_pysjhz(tra_kh,sjp_4,dir_right);}
	#define YKH45 {fun_pysjhz(tra_kh,sjp_45,dir_right);}
	#define YKH5 {fun_pysjhz(tra_kh,sjp_5,dir_right);}

	#define SH1 {fun_pysjhz(tra_h,sjp_1,dir_up);}
	#define SH12 {fun_pysjhz(tra_h,sjp_12,dir_up);}
	#define SH2 {fun_pysjhz(tra_h,sjp_2,dir_up);}
	#define SH23 {fun_pysjhz(tra_h,sjp_23,dir_up);}
	#define SH3 {fun_pysjhz(tra_h,sjp_3,dir_up);}
	#define SH34 {fun_pysjhz(tra_h,sjp_34,dir_up);}
	#define SH4 {fun_pysjhz(tra_h,sjp_4,dir_up);}
	#define SH45 {fun_pysjhz(tra_h,sjp_45,dir_up);}
	#define SH5 {fun_pysjhz(tra_h,sjp_5,dir_up);}
	#define XH1 {fun_pysjhz(tra_h,sjp_1,dir_down);}
	#define XH12 {fun_pysjhz(tra_h,sjp_12,dir_down);}
	#define XH2 {fun_pysjhz(tra_h,sjp_2,dir_down);}
	#define XH23 {fun_pysjhz(tra_h,sjp_23,dir_down);}
	#define XH3 {fun_pysjhz(tra_h,sjp_3,dir_down);}
	#define XH34 {fun_pysjhz(tra_h,sjp_34,dir_down);}
	#define XH4 {fun_pysjhz(tra_h,sjp_4,dir_down);}
	#define XH45 {fun_pysjhz(tra_h,sjp_45,dir_down);}
	#define XH5 {fun_pysjhz(tra_h,sjp_5,dir_down);}
	#define ZH1 {fun_pysjhz(tra_h,sjp_1,dir_left);}
	#define ZH12 {fun_pysjhz(tra_h,sjp_12,dir_left);}
	#define ZH2 {fun_pysjhz(tra_h,sjp_2,dir_left);}
	#define ZH23 {fun_pysjhz(tra_h,sjp_23,dir_left);}
	#define ZH3 {fun_pysjhz(tra_h,sjp_3,dir_left);}
	#define ZH34 {fun_pysjhz(tra_h,sjp_34,dir_left);}
	#define ZH4 {fun_pysjhz(tra_h,sjp_4,dir_left);}
	#define ZH45 {fun_pysjhz(tra_h,sjp_45,dir_left);}
	#define ZH5 {fun_pysjhz(tra_h,sjp_5,dir_left);}
	#define YH1 {fun_pysjhz(tra_h,sjp_1,dir_right);}
	#define YH12 {fun_pysjhz(tra_h,sjp_12,dir_right);}
	#define YH2 {fun_pysjhz(tra_h,sjp_2,dir_right);}
	#define YH23 {fun_pysjhz(tra_h,sjp_23,dir_right);}
	#define YH3 {fun_pysjhz(tra_h,sjp_3,dir_right);}
	#define YH34 {fun_pysjhz(tra_h,sjp_34,dir_right);}
	#define YH4 {fun_pysjhz(tra_h,sjp_4,dir_right);}
	#define YH45 {fun_pysjhz(tra_h,sjp_45,dir_right);}
	#define YH5 {fun_pysjhz(tra_h,sjp_5,dir_right);}

//设置巡线速度/转弯速度/前冲速度
	#define SP(par_gospeed,par_turnspeed,par_cachespeed) {str_tfl.gospeed=par_gospeed;str_tfl.turnspeed=par_turnspeed;str_tfl.cachespeed=par_cachespeed;}

//主函数转弯, 依赖str_tfl中的turnspeed, 使用SS向其赋值
	#define ZL1 {fun_turn(tur_l90,str_tfl.turnspeed);}
	#define ZR1 {fun_turn(tur_r90,str_tfl.turnspeed);}
	#define ZL2 {fun_turn(tur_l180,str_tfl.turnspeed);}
	#define ZR2 {fun_turn(tur_r180,str_tfl.turnspeed);}

//主函数前冲(前冲完了纠偏), 依赖str_tfl中的cachespeed, 使用SS向其赋值
	#define QC {fun_qc(40,str_tfl.cachespeed);fun_jtjp();}

//巡线, 依赖str_tfl中的gospeed, 使用SS向其赋值
	#define FL1 {fun_folline(1,str_tfl.gospeed);}
	#define FL2 {fun_folline(2,str_tfl.gospeed);}
	#define FL3 {fun_folline(3,str_tfl.gospeed);}
	#define FL4 {fun_folline(4,str_tfl.gospeed);}
	#define FL5 {fun_folline(5,str_tfl.gospeed);}
	#define FL6 {fun_folline(6,str_tfl.gospeed);}
	#define FL7 {fun_folline(7,str_tfl.gospeed);}
	#define FL8 {fun_folline(8,str_tfl.gospeed);}
	#define FL9 {fun_folline(9,str_tfl.gospeed);}
	#define FL10 {fun_folline(10,str_tfl.gospeed);}
	#define FL11 {fun_folline(11,str_tfl.gospeed);}
	#define FL12 {fun_folline(12,str_tfl.gospeed);}
	#define FL13 {fun_folline(13,str_tfl.gospeed);}
	#define FL14 {fun_folline(14,str_tfl.gospeed);}
	#define FL15 {fun_folline(15,str_tfl.gospeed);}
	#define FL16 {fun_folline(16,str_tfl.gospeed);}
	#define FL17 {fun_folline(17,str_tfl.gospeed);}
	#define FL18 {fun_folline(18,str_tfl.gospeed);}
	#define FL19 {fun_folline(19,str_tfl.gospeed);}
	#define FL20 {fun_folline(20,str_tfl.gospeed);}
	#define FL21 {fun_folline(21,str_tfl.gospeed);}
	#define FL22 {fun_folline(22,str_tfl.gospeed);}
	#define FL23 {fun_folline(23,str_tfl.gospeed);}
	#define FL24 {fun_folline(24,str_tfl.gospeed);}
	#define FL25 {fun_folline(25,str_tfl.gospeed);}
	#define FL26 {fun_folline(26,str_tfl.gospeed);}
	#define FL27 {fun_folline(27,str_tfl.gospeed);}
	#define FL28 {fun_folline(28,str_tfl.gospeed);}
	#define FL29 {fun_folline(29,str_tfl.gospeed);}
	#define FL30 {fun_folline(30,str_tfl.gospeed);}
	#define FL31 {fun_folline(31,str_tfl.gospeed);}
	#define FL32 {fun_folline(32,str_tfl.gospeed);}

//没有同步的定时器坐标巡线
	#define OG1 {fun_go(go_1);fun_zbtfl();}
	#define OG2 {fun_go(go_2);fun_zbtfl();}
	#define OG3 {fun_go(go_3);fun_zbtfl();}
	#define OG4 {fun_go(go_4);fun_zbtfl();}
	#define OG5 {fun_go(go_5);fun_zbtfl();}

//同步定时器坐标巡线
	#define TG1 {fun_go(go_1);}
	#define TG2 {fun_go(go_2);}
	#define TG3 {fun_go(go_3);}
	#define TG4 {fun_go(go_4);}
	#define TG5 {fun_go(go_5);}

//同步定时器坐标巡线结束
	#define GE {fun_zbtfl();}

#endif