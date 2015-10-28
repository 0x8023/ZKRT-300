#ifndef __HANS_H__
#define __HANS_H__
    #define A 40,35,45
    #define K 56,45,50
    #define Y 76,48,50

    #define GW fun_sj(sjp_1);fun_py(tra_h);fun_hz(dir_right);fun_sz(han_s);

    #define CD fun_flsetting(30,0,35,L(1),E);W

    #define R90 tfl_turn,tur_r90  
    #define L90 tfl_turn,tur_l90
    #define R180 tfl_turn,tur_r180
    #define L180 tfl_turn,tur_l180

    #define C(par_value) tfl_cache,par_value
    #define L(par_con) tfl_line,par_con

    #define S fun_sz(han_s);
    #define J fun_sz(han_j);

    #define D3 fun_delay(3,del_s);
    #define D5 fun_delay(5,del_s);

    #define SJ1 fun_sj(sjp_1);
    #define SJ12 fun_sj(sjp_12);
    #define SJ2 fun_sj(sjp_2);
    #define SJ23 fun_sj(sjp_23);
    #define SJ3 fun_sj(sjp_3);
    #define SJ4 fun_sj(sjp_4);
    #define SJ5 fun_sj(sjp_5);

    #define SJ2S fun_sj(sjp_12);fun_sz(han_s);
    #define SJ3S fun_sj(sjp_23);fun_sz(han_s);
    #define SJ4S fun_sj(sjp_34);fun_sz(han_s);

    #define S1 sjp_1
    #define S12 sjp_12
    #define S2 sjp_2
    #define S23 sjp_23
    #define S3 sjp_3
    #define S4 sjp_4
    #define S5 sjp_5

    #define DH tra_h
    #define DKH tra_kh
    #define DZ tra_z
    #define DKQ tra_kq
    #define DQ tra_q

    #define DD dir_down
    #define DR dir_right
    #define DU dir_up
    #define DL dir_left

    #define H fun_py(tra_h);
    #define KH fun_py(tra_kh);
    #define Z fun_py(tra_z);
    #define KQ fun_py(tra_kq);
    #define Q fun_py(tra_q);

    #define DOWN fun_hz(dir_down);
    #define R fun_hz(dir_right);
    #define LEFT fun_hz(dir_left);
    #define U fun_hz(dir_up);

    #define W def_waitfl
    #define E def_end

    #define F fun_flsetting
    #define ZJ fun_zhuajian();fun_delay(3,del_s);fun_py(tra_h);fun_back();

    #define SH(a,b)  fun_sjhz(a,b);
    #define PH(a,b)  fun_pyhz(a,b);
    #define ST(a,b,c) fun_pysjhz(b,a,c);

    #define T	fun_motors(mot_rl,-15);fun_delay(1250,del_ms);F(A,E);W
    #define JIN 	fun_motors(mot_rl,15);fun_delay(1250,del_ms);F(A,E);W
#endif