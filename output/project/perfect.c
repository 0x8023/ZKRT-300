//#include "HANS.h"
#include "../8023.h"
void main(){
    fun_start(//在此输入小车目前的状态
        0,//X坐标
        0,//Y坐标
        dir_up,//车头方向
        han_s,//手抓状态
        sjp_1,//升降位置
        tra_h,//平移位置
        dir_right);//回转方向
    fun_setxy(//x轴坐标,y轴坐标,工位号,到达此坐标时需要的朝向,工位在小车的哪一侧
        1,6,2,dir_up,dir_right,
        1,8,5,dir_up,dir_left,
        2,7,3,dir_up,dir_right,
        2,9,1,dir_up,dir_left,
        4,dir_right);
    /*请从下一行开始写你的程序*/
	fun_delay(1,del_s);
    fun_go(gw_2);
    fun_zbtfl();
    /*你的程序到此为止,请不要再继续改动*/
    fun_stop();
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