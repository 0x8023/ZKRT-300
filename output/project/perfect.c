#include "../8023.h"
#define D2 D(2000);
#define D3 D(3000);
#define D4 D(4000);
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

	  str_tfl.step[0]=tfl_line;
	  str_tfl.step[1]=3;

	  str_tfl.step[2]=tfl_cache;
	  str_tfl.step[3]=80;
	
	  str_tfl.step[4]=tfl_turn;
	  str_tfl.step[5]=tur_r90;
	

	  str_tfl.step[6]=tfl_line;
	  str_tfl.step[7]=2;
	  
	  str_tfl.step[8]=def_end;
	
	  str_tfl.online=tf_false;
      str_tfl.run=str_tfl.step;
	  str_tfl.gospeed=40;
	  str_tfl.turnspeed=40;
	  str_tfl.doing=tf_ture;
	  while(1);
	  
	 // fun_hz1(dir_up);
	 // fun_motorsrl(mot_r,60);
	

	  
	 /*
   	  fun_hz1(dir_up);
	  fun_sj1(sjp_3);
      fun_hz1(dir_right);  //回转180
      D3
      fun_hz1(dir_left);   //回转180

      fun_py1(tra_q);  //前移
      D3
      fun_py1(tra_h);  //后移

      fun_sz1(han_j);  //手抓紧
      D3
      fun_sz1(han_s);   //手抓松

      fun_sj1(sjp_5);  //下降5
      fun_sj1(sjp_2);  //上升2
      D3
      fun_sj1(sjp_1);  //上升1
      D3
      fun_sj1(sjp_2);//下降2
      D3
      fun_sj1(sjp_5);//下降5
      D3


      
	  fun_motors(mot_rl,-58);//后退5秒
      D2
      
	  fun_motors(mot_rl,45);//前进4秒
      D2
	  
	  
      fun_motors(mot_l,-15);  //左转90
	  
	  fun_motors(mot_r,18);
      D3
 */
      
	/*	
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
	
*/
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