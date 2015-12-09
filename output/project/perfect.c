#include "HANS.h"
#include "../8023.h"
void main(){
    fun_start(//在此输入小车目前的状态
        4,//X坐标
        0,//Y坐标
        dir_up,//车头方向
        han_s,//手抓状态
        sjp_1,//升降位置
        tra_h,//平移位置
        dir_right);//回转方向
    // fun_setxy(//x轴坐标,y轴坐标,工位号,到达此坐标时需要的朝向,工位在小车的哪一侧
    //     0,4,4,dir_up,dir_right,
    //     0,9,2,dir_up,dir_right,
    //     2,7,3,dir_up,dir_left,
    //     3,9,1,dir_up,dir_right,
    //     5,dir_right,dir_down);
    // /*请从下一行开始写你的程序*/
    
    fun_setxy(//x轴坐标,y轴坐标,工位号,到达此坐标时需要的朝向,工位在小车的哪一侧
        2,7,1,DU,DL,
        2,5,3,DU,DL,
        3,4,2,DU,DR,
        3,9,4,DU,DR,
        5,DR,DR);

    
    L1

while(1);

    SJ2
    J
    SJ1
    PH(DZ,DD)
    SJ2
    Q
    W
    SJ3
    S
    SJ1
    PH(DH,DR)
    SJ3
    J
    SJ1
    PH(DZ,DD)
    Q
    SJ2
    S
    SJ1
    
    L2
    PH(DQ,DL)
    SJ2
    J
    SJ1
    PH(DQ,DD)
    SJ2
    W
    SJ3
    S
    SJ1
    
    L3
    PH(DH,DR)
    SJ4
    J
    SJ1
    PH(DH,DD)
    W
    SJ3
    S
    SJ2
    PH(DH,DR)
    SJ5
    J
    SJ1
    PH(DH,DD)
    SJ2
    S
    SJ1
    
    O4
    PH(DQ,DL)
    SJ3
    J
    SJ1
    PH(DH,DD)
    SJ2
    W
    SJ3
    S
    SJ2
    PH(DQ,DL)
    SJ4
    J
    SJ1
    PH(DH,DD)
    SJ2
    S
    SJ1
    
    O5
    PH(DQ,DL)
    SJ5
    J
    SJ2
    PH(DQ,DD)
    W
    SJ3
    S
    SJ1
    
    //
    
    O4
    H
    W
    SJ2
    J
    SJ1
    JIN
    SJ3
    S
    SJ2
    T
    SJ3
    J
    SJ1
    Z
    
    O5
    W
    Q
    SJ2
    S
    SJ1
    
    L3
    H
    W
    SJ2
    J
    SJ1
    Z
    
    L2
    W
    Q
    JIN
    SJ3
    S
    SJ2
    T
    SJ3
    J
    SJ1
    JIN
    SJ2
    S
    SJ1
    T
    
    L1
    Q
    W
    SJ2
    J
    SJ1
    JIN
    SJ3
    S
    SJ2
    T
    SJ3
    J
    SJ1
    Z
    
    O4
    W
    H
    JIN
    SJ2
    S
    SJ1
    T
    
    O5
    Q
    W
    SJ2
    J
    SJ1
    JIN
    SJ3
    S
    SJ2
    T
    SJ3
    J
    SJ1
    Z
    
    L1
    W
    Q
    JIN
    SJ2
    S
    SJ1
    
    //
    O4
    H
    W
    JIN
    SJ2
    J
    SJ1
    PH(DQ,DL)
    SJ5
    S
    SJ2
    PH(DH,DD)
    SJ3
    J
    SJ2
    T
    PH(DQ,DL)
    SJ4
    S
    SJ1
    
    L1
    PH(DQ,DD)
    W
    JIN
    SJ2
    J
    SJ1
    PH(DH,DR)
    SJ5
    S
    SJ2
    PH(DQ,DD)
    SJ3
    J
    SJ2
    PH(DH,DR)
    SJ4
    S
    SJ1
    
    OE
    W
    

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