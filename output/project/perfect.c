#include "../8023.h"
void main(){
    def_start(//在此输入小车目前的状态
        0,//X坐标
        0,//Y坐标
        dir_up,//车头方向
        han_s,//手抓状态
        sjp_3,//升降位置
        tra_h,//平移位置
        dir_up)//回转方向
    /*请从下一行开始写你的程序*/
	//fun_test();
	
	def_timer0start
	def_timer1start

	str_tfl.step[0]=tfl_line;
	str_tfl.step[1]=5;
	str_tfl.step[2]=def_end;
	
	str_tfl.run=&str_tfl.step[0];
	str_tfl.gospeed=50;
	str_tfl.online=tf_false;
	str_tfl.doing=tf_ture;
	
	while(1);
	

	/*
    fun_sj1(sjp_3);
	fun_sj1(sjp_5);
	//D(2000);
	fun_py1(tra_q);
	//D(2000);
	fun_py1(tra_h);
	//D(2000);
	
	fun_py1(tra_kh);
	//D(2000);
	fun_sj1(sjp_5);
	fun_sz1(han_j);
	//D(2000);
	fun_sj1(sjp_3);
	//D(2000);
	fun_py1(tra_q);
	//D(2000);
	fun_sj1(sjp_5);
	//D(2000);
	fun_sz1(han_s);
	//D(2000);
	
    fun_sj1(sjp_3);
	//D(2000);
 	fun_py1(tra_kq);
	//D(2000);
	fun_sj1(sjp_5);
	//D(2000);
	fun_sz1(han_j);
	//D(2000);
	fun_sj1(sjp_3);
	//D(2000);
	fun_py1(tra_h);
	//D(2000);
	fun_sj1(sjp_5);
	//D(2000);
	fun_sz1(han_s);
	//D(2000);
	

	fun_py1(tra_h);

	def_stop
	*/
	
	

	/*
	fun_sj1(sjp_1);
	fun_calibration();
	fun_sj1(sjp_4);
	
	fun_py1(tra_q);
	fun_sj1(sjp_5);
	
	fun_py1(tra_q);
	
	fun_py1(tra_h);
	D(2000)
	fun_py1(tra_kh);
	D(2000)
	fun_py1(tra_z);
	D(2000)
	fun_py1(tra_kq);
	D(2000)
	fun_py1(tra_q);

	D(2000)
	fun_py1(tra_q);
	D(2000)
	fun_py1(tra_kq);
	D(2000)
	fun_py1(tra_z);
	D(2000)
	fun_py1(tra_kh);
	D(2000)
	fun_py1(tra_h);
	*/
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