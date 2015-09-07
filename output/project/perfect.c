#include "../8023.h"
void main(){
    def_start(//在此输入小车目前的状态
        0,//X坐标
        0,//Y坐标
        dir_up,//车头方向
        han_s,//手抓状态
        sjp_3,//升降位置
        tra_h,//平移位置
        dir_right)//回转方向
    /*请从下一行开始写你的程序*/
		fun_test();
    /*你的程序到此为止,请不要再继续改动*/
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