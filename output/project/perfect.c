#include "../8023.h"

#define D1 D(1000);
#define D2 D(2000);
#define D3 D(3000);
#define D4 D(4000);
#define D5 D(5000);
#define Q fun_py1(tra_q);
#define KQ fun_py1(tra_kq);
#define Z fun_py1(tra_z);
#define KH fun_py1(tra_kh);
#define H fun_py1(tra_h);
#define SJ1 fun_sj1(sjp_1);
#define SJ2 fun_sj1(sjp_2);
#define SJ3 fun_sj1(sjp_3);
#define SJ4 fun_sj1(sjp_4);
#define SJ5 fun_sj1(sjp_5);
#define HJ fun_sz1(han_j);
#define HS fun_sz1(han_s);
#define HZR fun_hz1(dir_right);
#define HZL fun_hz1(dir_left);
#define HZU fun_hz1(dir_up);
#define HZD fun_hz1(dir_down);

int a=0;
void main(){
    fun_start(//在此输入小车目前的状态
        0,//X坐标
        0,//Y坐标
        dir_up,//车头方向
        han_j,//手抓状态
        sjp_3,//升降位置
        tra_kq,//平移位置
        dir_left);//回转方向
    /*请从下一行开始写你的程序*/
	//fun_test();
	
	for(a=0;a++<100;){
	    H
		KH
		D5
		H
		
		Z
		D5
		H
		
		KQ
		D5
		KH
		D5
		Z
		D5
		Q
		KQ
		D5
		Q
		
		Z
		D5
		Q
		
		KH
		D5
		KQ
		Z

	}

  
	

/*
	
	  str_tfl.step[0]=tfl_line;
	  str_tfl.step[1]=2;
	  str_tfl.step[2]=tfl_cache;
      str_tfl.step[3]=75;

	  str_tfl.step[4]=tfl_turn;
	  str_tfl.step[5]=tur_l90;


	  str_tfl.step[6]=tfl_line;
	  str_tfl.step[7]=3;
      str_tfl.step[8]=tfl_cache;
      str_tfl.step[9]=75;
	  str_tfl.step[10]=tfl_turn;
	  str_tfl.step[11]=tur_l90;

	  str_tfl.step[12]=tfl_line;
	  str_tfl.step[13]=2;
      str_tfl.step[14]=tfl_cache;
      str_tfl.step[15]=75;

	  str_tfl.step[16]=tfl_turn;
	  str_tfl.step[17]=tur_r90;

	  str_tfl.step[18]=tfl_line;
	  str_tfl.step[19]=3;
      str_tfl.step[20]=tfl_cache;
      str_tfl.step[21]=75;

	  str_tfl.step[22]=tfl_turn;
	  str_tfl.step[23]=tur_r90;

	  str_tfl.step[24]=tfl_line;
	  str_tfl.step[25]=2;
      str_tfl.step[26]=tfl_cache;
      str_tfl.step[27]=75;

	  str_tfl.step[28]=tfl_turn;
	  str_tfl.step[29]=tur_r90;

	  str_tfl.step[30]=tfl_line;
	  str_tfl.step[31]=3;
      str_tfl.step[32]=tfl_cache;
      str_tfl.step[33]=75;

	  str_tfl.step[34]=tfl_turn;
	  str_tfl.step[35]=tur_r90;

	  str_tfl.step[36]=tfl_line;
	  str_tfl.step[37]=2;
      str_tfl.step[38]=tfl_cache;
      str_tfl.step[39]=75;

	  str_tfl.step[40]=tfl_turn;
	  str_tfl.step[41]=tur_l90;

	  str_tfl.step[42]=tfl_line;
	  str_tfl.step[43]=3;
      str_tfl.step[44]=tfl_cache;
      str_tfl.step[45]=75;

	  str_tfl.step[46]=tfl_turn;
	  str_tfl.step[47]=tur_l90;
	  
	  str_tfl.step[48]=def_end;
	 
	  str_tfl.online=tf_false;
      str_tfl.run=str_tfl.step;
	  str_tfl.gospeed=40;
	  str_tfl.turnspeed=40;
      str_tfl.cachespeed=40;
	  str_tfl.doing=tf_ture;


	  
	  fun_hz1(dir_up);
	  fun_motors(mot_r,60);
	

   	  fun_hz1(dir_up);
	  fun_sj1(sjp_3);
      fun_hz1(dir_right);  //回转180

      fun_hz1(dir_left);   //回转180

      fun_py1(tra_q);  //前移

      fun_py1(tra_h);  //后移

      fun_sz1(han_j);  //手抓紧

      fun_sz1(han_s);   //手抓松

      fun_sj1(sjp_5);  //下降5
      fun_sj1(sjp_2);  //上升2

      fun_sj1(sjp_1);  //上升1

      fun_sj1(sjp_2);//下降2

      fun_sj1(sjp_5);//下降5



      
	  fun_motors(mot_rl,-58);//后退5秒

      
	  fun_motors(mot_rl,45);//前进4秒

	  
	  
      fun_motors(mot_l,-15);  //左转90
	  
	  fun_motors(mot_r,18);


	def_timer0start
	def_timer1start

	str_tfl.step[0]=tfl_line;
	str_tfl.step[1]=5;
	str_tfl.step[2]=def_end;
	
	str_tfl.run=&str_tfl.step[0];
	str_tfl.gospeed=50;
	str_tfl.online=tf_false;
	str_tfl.doing=tf_ture;
	


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