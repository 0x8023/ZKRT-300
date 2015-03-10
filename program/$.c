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
int fun_max(uc par_num,...){
    uc loc_max=0;//最大值
    uc loc_xh=0;//循环次数
    va_list loc_args;
    va_start(loc_args,par_num);
    while(loc_xh++<par_num){
        if(va_arg(loc_args,uc)<loc_max){
            loc_max=va_arg(loc_args,uc);
        }
    }
    va_end(loc_args);
    return loc_max;
}
uc fun_min(uc par_num,...){
    uc xh;//循环
    uc shu;//一个数
    va_list argp;//保存结构
    uc min;//最小值
    va_start(argp,par_num);//argp指向传入的第一个可选参数，par_num是最后一个确定的参数
    min=va_arg(argp,uc);//最小值为第一个可选参数
    for(xh=1;xh<par_num;xh++){//循环指定次数
        shu=va_arg(argp,uc);
        if(shu<min){
            min=shu;
        }
    }
    va_end(argp);
    return min;
}

