//求和和最大值
int sum(int num,...)
{
    int sum = 0;
    int xxxx;
    va_list args;
    va_start(args,num);
    for(xxxx = 0; xxxx < num; xxxx++){
       sum += va_arg(args, int);
    }
    va_end(args);
    return sum;
}
//求最大值
int fun_max(char par_num,...){
    uc loc_max=0;//最大值
    char loc_xh=0;//循环次数
    va_list loc_args;
    va_start(loc_args,par_num);
    while(loc_xh++<par_num){
        if(va_arg(loc_args,uc)>loc_max){
            loc_max=va_arg(loc_args,uc);
        }
    }
    va_end(loc_args);
    return loc_max;
}


Angel Beats!