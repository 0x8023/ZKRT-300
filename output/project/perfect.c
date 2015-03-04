#include "../8023.h"
    int a=5;
void main(){
    def_start(
        0,//X坐标
        0,//Y坐标
        dir_up,//车头方向
        han_j,//手抓状态
        sjp_wz5,//升降位置
        tra_kq,//平移位置
        dir_right)//回转方向
//    fun_sj1(sjp_wz1);
//    fun_delay(1,del_s);
//    WZ5
//    D(2000)
//    WZ2
//    def_stop
    WZ1
    fun_pyhz2(tra_h,dir_left);
    

	   
	def_stop
    WZ4
    
    fun_calibration();
    //fun_py1(tra_q);
    fun_py1(tra_kq);
    MSG("stop")

    




    fun_sj1(sjp_wz1);
    fun_delay(1,del_s);
    fun_sj1(sjp_wz12);
    fun_delay(1,del_s);
    fun_sj1(sjp_wz2);
    fun_delay(1,del_s);
    fun_sj1(sjp_wz23);
    fun_delay(1,del_s);
    fun_sj1(sjp_wz3);
    fun_delay(1,del_s);
    fun_sj1(sjp_wz34);
    fun_delay(1,del_s);
    fun_sj1(sjp_wz4);
    fun_delay(1,del_s);
    fun_sj1(sjp_wz45);
    fun_delay(1,del_s);
    fun_sj1(sjp_wz5);
    fun_delay(1,del_s);

    fun_sj1(sjp_wz45);
    fun_delay(1,del_s);
    fun_sj1(sjp_wz4);
    fun_delay(1,del_s);
    fun_sj1(sjp_wz34);
    fun_delay(1,del_s);
    fun_sj1(sjp_wz3);
    fun_delay(1,del_s);
    fun_sj1(sjp_wz23);
    fun_delay(1,del_s);
    fun_sj1(sjp_wz2);
    fun_delay(1,del_s);
    fun_sj1(sjp_wz12);
    fun_delay(1,del_s);
    fun_sj1(sjp_wz1);

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
