#include "../8023.h"
    int a=5;
void main(){
    def_start(
        0,//X坐标
        0,//Y坐标
        dir_up,//车头方向
        han_s,//手抓状态
        sjp_wz1,//升降位置
        tra_q,//平移位置
        dir_left)//回转方向
//    fun_sj1(sjp_wz1);
//    fun_delay(1,del_s);
//    WZ5
//    D(2000)
//    WZ2
//    def_stop
    //fun_zhuajian(1,2,3,4,5,6,7,8,4,3,2,1,8,7,6,5);


    fun_mptline(2,60,dir_up);

	MSG("stop")  
	def_stop
    WZ4
    
    fun_calibration();
    //fun_py1(tra_q);
    fun_py1(tra_kq);
    

    




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
