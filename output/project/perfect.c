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
        0,8,4,dir_down,dir_left,
        1,8,1,dir_up,dir_right,
        3,8,5,dir_down,dir_right,
        3,10,2,dir_up,dir_right,
        3,dir_right);
    /*请从下一行开始写你的程序*/
    //fun_delay(1,del_s);
    //fun_go(gw_5);

    //fun_sj(sjp_1);fun_py(tra_h);fun_hz(dir_right);fun_sz(han_s);
    printf("main output :%d\n",(int)fun_getpublicy(3,10,0,8,dir_down));
   // fun_folline(1,30);
    
    // // F(A,L(6),C(45),L90,L(3),C(45),R90,L(2),C(45),E);
    // fun_go(gw_1);
    // deb_outstep(32);
    // fun_zbtfl();

    
    // // F(A,L(4),C(45),R90,L(1),C(45),R90,L(1),C(45),E);
    // fun_go(gw_2);
    // deb_outstep(32);
    // fun_zbtfl();

    
    // // F(A,L(5),C(45),R90,L(3),C(45),R90,L(1),C(45),E);
    // fun_go(gw_3);
    // deb_outstep(32);
    // fun_zbtfl();

    
    // // F(K,L(6),C(45),E);
    // fun_go(gw_4);
    // deb_outstep(32);
    // fun_zbtfl();

    
    // // F(K,L(2),C(45),R90,L(1),C(45),L90,L(4),C(45),E);
    // fun_go(gw_5);
    // deb_outstep(32);
    // fun_zbtfl();

    
    // // F(K,L(5),C(45),R90,L(3),C(45),L90,L(4),E);

    // // fun_zbtfl();

    // fun_zbtfl();
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