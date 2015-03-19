#include "../8023.h"
    int a=5;
void main(){
    def_start(
        0,//X坐标
        0,//Y坐标
        dir_up,//车头方向
        han_s,//手抓状态
        sjp_wz3,//升降位置
        tra_h,//平移位置
        dir_right)//回转方向
//    fun_sj1(sjp_wz1);
//    fun_delay(1,del_s);
//    WZ5
//    D(2000)
//    WZ2
//    def_stop
//    
    
    fun_test();
    def_stop

    fun_hz1(dir_left);
    fun_calibration();
    fun_zhuajian(62514387,85237164);

    MSG("STOP")
    def_stop
    //fun_mptline(5,60,dir_left);

    




    WZ4
    
    fun_calibration();
    //fun_py1(tra_q);
    fun_py1(tra_kq);

    def_stop
}
void Int0Interrupt() interrupt 0{
    ;
}
void Timer0Interrupt() interrupt 1 using 1{
    fun_timer0();
}
void Timer1Interrupt() interrupt 3 using 1{
    fun_timer1();
}
