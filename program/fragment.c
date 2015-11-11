void fun_pbxy(uc par_x,uc par_y,enum varENU_dir par_fx,enum varENU_dir par_gw){
    /*
        屏蔽某一个坐标是指可以到达此坐标,但位于此坐标不允许相应的运动.
    */
    if(par_gw==dir_left){//如果工位在小车左边
        if(par_fx==dir_down){//如果需要向下停
            str_zbfl.xy[par_x][par_y].enleft=tf_false;//不允许左转
            str_zbfl.xy[par_x][par_y-1].enleft=tf_false;//下一个格也不准左转
            str_zbfl.xy[par_x-1][par_y].enright=tf_false;//工位左边的不允许右转
            str_zbfl.xy[par_x-1][par_y-1].enright=tf_false;//工位左边的下一个格也不准右转
        }else if(par_fx==dir_up){//如果需要向上停
            str_zbfl.xy[par_x][par_y].enleft=tf_false;//不允许左转
            str_zbfl.xy[par_x][par_y+1].enleft=tf_false;//上一个格也不准左转
            str_zbfl.xy[par_x-1][par_y].enright=tf_false;//工位左边的也不允许右转
            str_zbfl.xy[par_x-1][par_y+1].enright=tf_false;//工位左边的上一个格也不准右转
        }
    }else if(par_gw==dir_right){//如果工位在小车右边
        if(par_fx==dir_down){//如果需要向下停
            str_zbfl.xy[par_x][par_y].enright=tf_false;//不允许右转
            str_zbfl.xy[par_x][par_y-1].enright=tf_false;//下一个格也不准右转
            str_zbfl.xy[par_x+1][par_y].enleft=tf_false;//工位右边的不允许左转
            str_zbfl.xy[par_x+1][par_y-1].enleft=tf_false;//工位右边的下一个格也不准左转
        }else if(par_fx==dir_up){//如果需要向上停
            str_zbfl.xy[par_x][par_y].enright=tf_false;//不允许右转
            str_zbfl.xy[par_x][par_y+1].enright=tf_false;//上一个格也不准右转
            str_zbfl.xy[par_x+1][par_y].enleft=tf_false;//工位右边的不允许左转
            str_zbfl.xy[par_x+1][par_y+1].enleft=tf_false;//工位右边的上一个格也不准左转
        }
    }
}//通过工件的朝向和小车的车头方向屏蔽坐标

void fun_xymove(enum varENU_tfl par_model,char par_value){
    if(*str_tfl.run==0){//如果当前步骤没被编辑过
        if(par_model==tfl_cache){//如果第一个是前冲
            return;//不允许是前冲
        }
        (*str_tfl.run)=par_model;//那就等于现在的模式
    }else if(*str_tfl.run!=par_model){//如果当前步骤和传入的步骤不一样
        str_tfl.run+=2;//指针指向下一组数组
        (*str_tfl.run)=par_model;//存入步骤
    }
    switch(*str_tfl.run){//选择正在编辑的步骤
        case tfl_line://如果正在编辑巡线
            *(str_tfl.run+1)+=par_value;//巡线步骤的参数加上需要增加的参数(据说可以减去)
            break;
        case tfl_turn://如果正在编辑转完
            switch(*(str_tfl.run+1)){//选择正在编辑的步骤
                case 0://如果还没被写入值
                    *(str_tfl.run+1)=par_value;//直接写进去
                    break;
                case tur_l90://如果现在在左转
                    switch(par_value){//选择传入的参数
                        case tur_l90://如果需要左转
                            *(str_tfl.run+1)=tur_l180;//左转两个90°=左转180°
                            break;
                        case tur_r90://如果需要右转
                            #ifdef Debug
                                printf("W: #fun_xymove -tur_l90+tur_r90\n");//左转+右转不成立,报错
                            #endif
                            break;
                        case tur_l180://如果需要左转180°
                            *(str_tfl.run+1)=tur_r90;//左转90°+左转180°=右转90°
                            break;
                        case tur_r180://如果需要右转180°
                            *(str_tfl.run+1)=tur_r90;//左转90°+右转180°=右转90°
                            break;
                        default:
                            break;
                    }
                    break;
                case tur_r90:
                    switch(par_value){
                        case tur_l90:
                            #ifdef Debug
                                printf("W: #fun_xymove -tur_r90+tur_l90\n");
                            #endif
                            break;
                        case tur_r90:
                            *(str_tfl.run+1)=tur_r180;
                            break;
                        case tur_l180:
                            *(str_tfl.run+1)=tur_l90;
                            break;
                        case tur_r180:
                            *(str_tfl.run+1)=tur_l90;
                            break;
                        default:
                            break;
                    }
                    break;
                case tur_l180:
                    switch(par_value){
                        case tur_l90:
                            *(str_tfl.run+1)=tur_r90;
                            break;
                        case tur_r90:
                            *(str_tfl.run+1)=tur_l90;
                            break;
                        case tur_l180:
                            #ifdef Debug
                                printf("W: #fun_xymove -tur_l180+tur_l180\n");
                            #endif
                            break;
                        case tur_r180:
                            #ifdef Debug
                                printf("W: #fun_xymove -tur_l180+tur_r180\n");
                            #endif
                            break;
                        default:
                            break;
                    }
                    break;
                case tur_r180:
                    switch(par_value){
                        case tur_l90:
                            *(str_tfl.run+1)=tur_r90;
                            break;
                        case tur_r90:
                            *(str_tfl.run+1)=tur_l90;
                            break;
                        case tur_l180:
                            #ifdef Debug
                                printf("W: #fun_xymove -tur_r180+tur_l180\n");
                            #endif
                            break;
                        case tur_r180:
                            #ifdef Debug
                                printf("W: #fun_xymove -tur_r180+tur_l180\n");
                            #endif
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;
        case tfl_cache://如果正在编辑前冲
            *(str_tfl.run+1)+=par_value;
            break;
        default:
            break;
    }
}//坐标巡线单步累计步骤生成




char fun_getpublicy(char par_xnow,char par_ynow,char par_xnext,char par_ynext,enum varENU_dir par_gwfx){
    uc loc_xhx,loc_xhy,loc_flag=0,loc_con=0;
    uc loc_data[12];
    memset(loc_data,0,sizeof(loc_data));//清空数组
    if(par_xnext>par_xnow){//往右走
        for(loc_xhy=0;loc_xhy<=12;loc_xhy++){//循环扫描所有可能性的Y
            for(loc_xhx=par_xnow;loc_xhx<=par_xnext;loc_xhx++){//循环扫描两点之间的X
                if(str_zbfl.xy[loc_xhx][loc_xhy].enright==tf_ture){//如果允许右行
                    loc_flag++;//标志位+1
                }
            }
            if(loc_flag==par_xnext-par_xnow+1){//如果可以走的线就是一共需要走的线
                loc_data[loc_con++]=loc_xhy;//将Y轴数据记录至数组
            }
            loc_flag=0;//标志位清零
        }
    }else if(par_xnext<par_xnow){//往左走
        for(loc_xhy=0;loc_xhy<=12;loc_xhy++){//循环扫描所有可能性的Y
            for(loc_xhx=par_xnow;loc_xhx>=par_xnext;loc_xhx--){//循环扫描两点之间的X
                if(str_zbfl.xy[loc_xhx][loc_xhy].enleft==tf_ture){//如果允许左行
                    loc_flag++;//标志位+1
                }
            }
            if(loc_flag==par_xnow-par_xnext+1){//如果可以走的线就是一共需要走的线
                loc_data[loc_con++]=loc_xhy;//将Y轴数据记录至数组
            }
            loc_flag=0;//标志位清零
        }
    }else{//不往左不往右
        return (-1);
    }
    if(par_ynext>par_ynow){//要往上走
        if(par_gwfx==dir_up){//工位要求向上停
            for(loc_con=0;loc_data[loc_con]!=0;loc_con++){//循环已经赋值过的数组
                if(loc_data[loc_con]>=par_ynow && loc_data[loc_con]<par_ynext){//如果比现在的大,比要去的小
                    return (loc_data[loc_con]);//返回值
                }
            }
            for(loc_con=0;loc_data[loc_con]!=0;loc_con++){//循环已经赋值过的数组
                if(loc_data[loc_con]<par_ynow){//如果比现在的小
                    return (loc_data[loc_con]);//返回值
                }
            }
            for(loc_con=0;loc_data[loc_con]!=0;loc_con++){//循环已经赋值过的数组
                if(loc_data[loc_con]>par_ynext){//如果比要去的大
                    return (loc_data[loc_con]);//返回值
                }
            }
        }else if(par_gwfx==dir_down){//工位要求向下停
            for(loc_con=0;loc_data[loc_con]!=0;loc_con++){//循环已经赋值过的数组
                if(loc_data[loc_con]>par_ynext){//如果比要去的大
                    return (loc_data[loc_con]);//返回值
                }
                if(loc_data[loc_con]<par_ynext){//如果比要去的小
                    return (loc_data[loc_con]);//返回值
                }
            }
        }else{
            return (-1);
        }
    }else if(par_ynext<par_ynow){//往下走
        if(par_gwfx==dir_up){//工位要求向上停
            for(loc_con=0;loc_data[loc_con]!=0;loc_con++){//循环已经赋值过的数组
                if(loc_data[loc_con]<par_ynext){//如果比要去的小
                    return (loc_data[loc_con]);//返回值
                }
            }
            for(loc_con=0;loc_data[loc_con]!=0;loc_con++){//循环已经赋值过的数组
                if(loc_data[loc_con]>par_ynext){//如果比要去的大
                    return (loc_data[loc_con]);//返回值
                }
            }
        }else if(par_gwfx==dir_down){//如果工位要求朝下停
            for(loc_con=0;loc_data[loc_con]!=0;loc_con++){//循环已经赋值过的数组
                if(loc_data[loc_con]<=par_ynow && loc_data[loc_con]>par_ynext){//如果比现在的小,比要去的大
                    return (loc_data[loc_con]);//返回值
                }
            }
            for(loc_con=0;loc_data[loc_con]!=0;loc_con++){//循环已经赋值过的数组
                if(loc_data[loc_con]>par_ynow){//如果比现在的大
                    return (loc_data[loc_con]);//返回值
                }
            }
            for(loc_con=0;loc_data[loc_con]!=0;loc_con++){//循环已经赋值过的数组
                if(loc_data[loc_con]<par_ynext){//如果比要去的小
                    return (loc_data[loc_con]);//返回值
                }
            }
        }else{
            return (-1);
        }
    }else{
        return (-1);
    }
}





void fun_record(char par_x,char par_y,enum varENU_dir par_ctfx,char par_gospeed,char par_turnspeed,char par_cachespeed){
    /*
        优先左右走,其次考虑车头方向,再次考虑工件台的位置
    */
    str_tfl.run=str_tfl.step;//指针指向第一个步骤
    while((str_now.x!=par_x)||(str_now.y!=par_y)||(str_now.ctfx!=par_ctfx)){//如果xy轴到达了,车头方向一致了
        switch(str_now.ctfx){//判断当前车头方向
            case dir_up://现在车头朝上
                if(par_x>str_now.x){//如果要去的x值比现在的大,向右走
                    if(str_zbfl.xy[str_now.x][str_now.y].enright==tf_ture){//允许右转
                        fun_xymove(tfl_cache,40);//前冲
                        fun_xymove(tfl_turn,tur_r90);//右转
                    }else{//不允许右转
                        if(par_y>str_now.y){//要去的在现在的上面
                            fun_xymove(tfl_line,1);//走一条线
                        }else if(par_y<str_now.y){//要去的在现在的下面
                            if((str_now.y==0)||((str_zbfl.xy[str_now.x][str_now.y].enleft==tf_ture)&&(str_zbfl.xy[str_now.x][str_now.y].endown==tf_ture))){//如果在Y=0轴或允许左转和下转
                                fun_xymove(tfl_cache,40);//前冲
                                fun_xymove(tfl_turn,tur_l180);//左转180度
                            }else{//不然的话
                                fun_xymove(tfl_line,1);//走一条线
                            }
                        }else{

                        }
                    }
                    continue;
                }
                if(par_x<str_now.x){//如果要去的x值比现在的小,向左走
                    if(str_zbfl.xy[str_now.x][str_now.y].enleft==tf_ture){
                        fun_xymove(tfl_cache,40);
                        fun_xymove(tfl_turn,tur_l90);
                    }else{
                        ;
                    }
                    continue;
                }
                if(par_y>str_now.y){//如果要去的Y值比现在的大,向上走
                    if(str_zbfl.xy[str_now.x][str_now.y].enup==tf_ture){
                        fun_xymove(tfl_line,1);
                    }else{
                        ;
                    }
                    continue;
                }
                if(par_y<str_now.y){//如果要去的Y值比现在的小,向下走
                    if(str_zbfl.xy[str_now.x][str_now.y].endown==tf_ture){
                        fun_xymove(tfl_cache,40);
                        fun_xymove(tfl_turn,tur_r180);
                    }else{
                        ;
                    }
                    continue;
                }
                if(par_x==str_now.x&&par_y==str_now.y){//需要在原地转个弯
                    fun_xymove(tfl_cache,40);
                    switch(par_ctfx){
                        case dir_left:
                            if(str_zbfl.xy[str_now.x][str_now.y].enleft==tf_ture){
                                fun_xymove(tfl_turn,tur_l90);
                            }else{
                                ;
                            }
                            break;
                        case dir_right:
                            if(str_zbfl.xy[str_now.x][str_now.y].enright==tf_ture){
                                fun_xymove(tfl_turn,tur_r90);
                            }else{
                                ;
                            }
                            break;
                        case dir_down:
                            if(str_zbfl.xy[str_now.x][str_now.y].endown==tf_ture){
                                if(str_zbfl.xy[str_now.x][str_now.y].enleft==tf_ture){
                                    fun_xymove(tfl_turn,tur_l180);
                                }else if(str_zbfl.xy[str_now.x][str_now.y].enright==tf_ture){
                                    fun_xymove(tfl_turn,tur_r180);
                                }else{
                                    ;
                                }
                            }else{
                                ;
                            }
                            break;
                        default:
                            break;
                    }
                    continue;
                }
                break;
            case dir_down://现在车头朝下
                if(par_x>str_now.x){//如果要去的x值比现在的大//向右走
                    if(str_zbfl.xy[str_now.x][str_now.y].enright==tf_ture){
                        fun_xymove(tfl_cache,40);
                        fun_xymove(tfl_turn,tur_l90);
                    }else{
                        ;
                    }
                    continue;
                }
                if(par_x<str_now.x){//如果要去的x值比现在的小//向左走
                    if(str_zbfl.xy[str_now.x][str_now.y].enleft==tf_ture){
                        fun_xymove(tfl_cache,40);
                        fun_xymove(tfl_turn,tur_r90);
                    }else{
                        ;
                    }
                    continue;
                }
                if(par_y<str_now.y){//如果要去的Y值比现在的小//向下走
                    if(str_zbfl.xy[str_now.x][str_now.y].endown==tf_ture){
                        fun_xymove(tfl_line,1);
                    }else{
                        ;
                    }
                    continue;
                }
                if(par_y>str_now.y){//如果要去的Y值比现在的大//向上走
                    if(str_zbfl.xy[str_now.x][str_now.y].enup==tf_ture){
                        fun_xymove(tfl_cache,40);
                        fun_xymove(tfl_turn,tur_r180);
                    }else{
                        ;
                    }
                    continue;
                }
                if(par_x==str_now.x&&par_y==str_now.y){//需要在原地转个弯
                    fun_xymove(tfl_cache,40);
                    switch(par_ctfx){
                        case dir_left:
                            if(str_zbfl.xy[str_now.x][str_now.y].enright==tf_ture){
                                fun_xymove(tfl_turn,tur_r90);
                            }else{
                                ;
                            }
                            break;
                        case dir_right:
                            if(str_zbfl.xy[str_now.x][str_now.y].enleft==tf_ture){
                                fun_xymove(tfl_turn,tur_l90);
                            }else{
                                ;
                            }
                            break;
                        case dir_up:
                            if(str_zbfl.xy[str_now.x][str_now.y].enup==tf_ture){
                                if(str_zbfl.xy[str_now.x][str_now.y].enright==tf_ture){
                                    fun_xymove(tfl_turn,tur_l180);
                                }else if(str_zbfl.xy[str_now.x][str_now.y].enleft==tf_ture){
                                    fun_xymove(tfl_turn,tur_r180);
                                }else{
                                    ;
                                }
                            }else{
                                ;
                            }
                            break;
                        default:
                            break;
                    }
                    continue;
                }
                break;
            case dir_right://现在车头朝右
                if(par_x>str_now.x){//如果要去的x值比现在的大,向右走
                    if(str_zbfl.xy[str_now.x][str_now.y].enright==tf_ture){
                        fun_xymove(tfl_line,1);
                    }else{
                        ;
                    }
                    continue;
                }
                if(par_x<str_now.x){//如果要去的x值比现在的小,向左走
                    if(str_zbfl.xy[str_now.x][str_now.y].enleft==tf_ture){
                        fun_xymove(tfl_cache,40);
                        fun_xymove(tfl_turn,tur_l180);
                    }else{
                        ;
                    }
                    continue;
                }
                if(par_y>str_now.y){//如果要去的Y值比现在的大,向上走
                    if(str_zbfl.xy[str_now.x][str_now.y].enup==tf_ture){
                        fun_xymove(tfl_cache,40);
                        fun_xymove(tfl_turn,tur_l90);
                    }else{
                        ;
                    }
                    continue;
                }
                if(par_y<str_now.y){//如果要去的Y值比现在的小,向下走
                    if(str_zbfl.xy[str_now.x][str_now.y].endown==tf_ture){
                        fun_xymove(tfl_cache,40);
                        fun_xymove(tfl_turn,tur_r90);
                    }else{
                        ;
                    }
                    continue;
                }
                if(par_x==str_now.x&&par_y==str_now.y){//需要在原地转个弯
                    fun_xymove(tfl_cache,40);
                    switch(par_ctfx){
                        case dir_left:
                            if(str_zbfl.xy[str_now.x][str_now.y].enleft==tf_ture){
                                if(str_zbfl.xy[str_now.x][str_now.y].enup==tf_ture){
                                    fun_xymove(tfl_turn,tur_l180);
                                }else if(str_zbfl.xy[str_now.x][str_now.y].endown==tf_ture){
                                    fun_xymove(tfl_turn,tur_r180);
                                }else{
                                    ;
                                }
                            }
                            break;
                        case dir_down:
                            if(str_zbfl.xy[str_now.x][str_now.y].endown==tf_ture){
                                fun_xymove(tfl_turn,tur_r90);
                            }else{
                                ;
                            }
                            break;
                        case dir_up:
                            if(str_zbfl.xy[str_now.x][str_now.y].enup==tf_ture){
                                fun_xymove(tfl_turn,tur_l90);
                            }else{
                                ;
                            }
                            break;
                        default:
                            break;
                    }
                    continue;
                }
                break;
            case dir_left://现在车头朝左
                if(par_x<str_now.x){//如果要去的x值比现在的小,向左走
                    if(str_zbfl.xy[str_now.x][str_now.y].enleft==tf_ture){
                        fun_xymove(tfl_line,1);
                    }else{
                        ;
                    }
                    continue;
                }
                if(par_x>str_now.x){//如果要去的x值比现在的大,向右走
                    if(str_zbfl.xy[str_now.x][str_now.y].enright==tf_ture){
                        fun_xymove(tfl_cache,40);
                        fun_xymove(tfl_turn,tur_l180);
                    }else{
                        ;
                    }
                    continue;
                }
                if(par_y>str_now.y){//如果要去的Y值比现在的大,向上走
                    if(str_zbfl.xy[str_now.x][str_now.y].enup==tf_ture){
                        fun_xymove(tfl_cache,40);
                        fun_xymove(tfl_turn,tur_r90);
                    }else{
                        ;
                    }
                    continue;
                }
                if(par_y<str_now.y){//如果要去的Y值比现在的小,向下走
                    if(str_zbfl.xy[str_now.x][str_now.y].endown==tf_ture){
                        fun_xymove(tfl_cache,40);
                        fun_xymove(tfl_turn,tur_l90);
                    }else{
                        ;
                    }
                    continue;
                }
                if(par_x==str_now.x&&par_y==str_now.y){//需要在原地转个弯
                    fun_xymove(tfl_cache,40);
                    switch(par_ctfx){
                        case dir_right:
                            if(str_zbfl.xy[str_now.x][str_now.y].endown==tf_ture){
                                fun_xymove(tfl_turn,tur_l180);
                            }
                            break;
                        case dir_down:
                            if(str_zbfl.xy[str_now.x][str_now.y].endown==tf_ture){
                                fun_xymove(tfl_turn,tur_l90);
                            }else{
                                ;
                            }
                            break;
                        case dir_up:
                            if(str_zbfl.xy[str_now.x][str_now.y].enup==tf_ture){
                                fun_xymove(tfl_turn,tur_r90);
                            }else{
                                ;
                            }
                            break;
                        default:
                            break;
                    }
                    continue;
                }
                break;
            default:
                break;
        }
    }
    fun_xymove(tfl_line,1);//进入工位台
    fun_xymove(tfl_cache,40);//前冲
    str_tfl.run+=2;//指针指向下一组数组
    (*str_tfl.run)=def_end;//存入步骤

    str_tfl.online=tf_false;//不在线
    str_tfl.run=str_tfl.step;//指针指向第一个数组
    str_tfl.gospeed=par_gospeed;//默认速度
    str_tfl.turnspeed=par_turnspeed;//拐弯速度
    str_tfl.cachespeed=par_cachespeed;//前冲速度
    str_tfl.doing=tf_ture;//开始做
}//定时器坐标巡线步骤生成




void fun_record(char par_x,char par_y,enum varENU_dir par_ctfx,char par_gospeed,char par_turnspeed,char par_cachespeed){
    //          需要到的X ,需要到的y ,需要的车头方向          ,巡线的速度      ,转弯速度          ,前冲速度
    /*
        优先左右走,其次考虑车头方向,再次考虑工件台的位置
    */
    str_tfl.run=str_tfl.step;//指针指向第一个步骤
    while((str_now.x!=par_x)||(str_now.y!=par_y)||(str_now.ctfx!=par_ctfx)){//如果xy轴到达了,车头方向一致了
        switch(str_now.ctfx){//判断当前车头方向
            case dir_up://现在车头朝上
                if(par_x>str_now.x){//如果要去的x值比现在的大,向右走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_r90);
                    str_now.ctfx=dir_right;
                    continue;
                }
                if(par_x<str_now.x){//如果要去的x值比现在的小,向左走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_l90);
                    str_now.ctfx=dir_left;
                    continue;
                }
                if(par_y>str_now.y){//如果要去的Y值比现在的大,向上走
                    fun_xymove(tfl_line,1);
                    str_now.y+=1;
                    continue;
                }
                if(par_y<str_now.y){//如果要去的Y值比现在的小,向下走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_r180);
                    str_now.ctfx=dir_down;
                    continue;
                }
                if(par_x==str_now.x&&par_y==str_now.y){//需要在原地转个弯
                    fun_xymove(tfl_cache,40);
                    switch(par_ctfx){
                        case dir_left:
                            fun_xymove(tfl_turn,tur_l90);
                            break;
                        case dir_right:
                            fun_xymove(tfl_turn,tur_r90);
                            break;
                        case dir_down:
                            fun_xymove(tfl_turn,tur_l180);
                            break;
                        default:
                            break;
                    }
                    str_now.ctfx=par_ctfx;
                    continue;
                }
                break;
            case dir_down://现在车头朝下
                if(par_x>str_now.x){//如果要去的x值比现在的大//向右走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_l90);
                    str_now.ctfx=dir_right;
                    continue;
                }
                if(par_x<str_now.x){//如果要去的x值比现在的小//向左走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_r90);
                    str_now.ctfx=dir_left;
                    continue;
                }
                if(par_y<str_now.y){//如果要去的Y值比现在的小//向下走
                    fun_xymove(tfl_line,1);
                    str_now.y-=1;
                    continue;
                }
                if(par_y>str_now.y){//如果要去的Y值比现在的大//向上走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_r180);
                    str_now.ctfx=dir_up;
                    continue;
                }
                if(par_x==str_now.x&&par_y==str_now.y){//需要在原地转个弯
                    fun_xymove(tfl_cache,40);
                    switch(par_ctfx){
                        case dir_left:
                            fun_xymove(tfl_turn,tur_r90);
                            break;
                        case dir_right:
                            fun_xymove(tfl_turn,tur_l90);
                            break;
                        case dir_up:
                            fun_xymove(tfl_turn,tur_l180);
                            break;
                        default:
                            break;
                    }
                    str_now.ctfx=par_ctfx;
                    continue;
                }
                break;
            case dir_right://现在车头朝右
                if(par_x>str_now.x){//如果要去的x值比现在的大,向右走
                    fun_xymove(tfl_line,1);
                    str_now.x+=1;
                    continue;
                }
                if(par_x<str_now.x){//如果要去的x值比现在的小,向左走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_l180);
                    str_now.ctfx=dir_left;
                    continue;
                }
                if(par_y>str_now.y){//如果要去的Y值比现在的大,向上走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_l90);
                    str_now.ctfx=dir_up;
                    continue;
                }
                if(par_y<str_now.y){//如果要去的Y值比现在的小,向下走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_r90);
                    str_now.ctfx=dir_down;
                    continue;
                }
                if(par_x==str_now.x&&par_y==str_now.y){//需要在原地转个弯
                    fun_xymove(tfl_cache,40);
                    switch(par_ctfx){
                        case dir_left:
                            fun_xymove(tfl_turn,tur_l180);
                            break;
                        case dir_down:
                            fun_xymove(tfl_turn,tur_r90);
                            break;
                        case dir_up:
                            fun_xymove(tfl_turn,tur_l90);
                            break;
                        default:
                            break;
                    }
                    str_now.ctfx=par_ctfx;
                    continue;
                }
                break;
            case dir_left://现在车头朝左
                if(par_x<str_now.x){//如果要去的x值比现在的小,向左走
                    fun_xymove(tfl_line,1);
                    str_now.x-=1;
                    continue;
                }
                if(par_x>str_now.x){//如果要去的x值比现在的大,向右走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_l180);
                    str_now.ctfx=dir_right;
                    continue;
                }
                if(par_y>str_now.y){//如果要去的Y值比现在的大,向上走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_r90);
                    str_now.ctfx=dir_up;
                    continue;
                }
                if(par_y<str_now.y){//如果要去的Y值比现在的小,向下走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_l90);
                    str_now.ctfx=dir_down;
                    continue;
                }
                if(par_x==str_now.x&&par_y==str_now.y){//需要在原地转个弯
                    fun_xymove(tfl_cache,40);
                    switch(par_ctfx){
                        case dir_right:
                            fun_xymove(tfl_turn,tur_l180);
                            break;
                        case dir_down:
                            fun_xymove(tfl_turn,tur_l90);
                            break;
                        case dir_up:
                            fun_xymove(tfl_turn,tur_r90);
                            break;
                        default:
                            break;
                    }
                    str_now.ctfx=par_ctfx;
                    continue;
                }
                break;
            default:
                break;
        }
    }
    fun_xymove(tfl_line,1);//进入工位台
    fun_xymove(tfl_cache,40);//前冲
    str_tfl.run+=2;//指针指向下一组数组
    (*str_tfl.run)=def_end;//存入步骤

    str_tfl.online=tf_false;//不在线
    str_tfl.run=str_tfl.step;//指针指向第一个数组
    str_tfl.gospeed=par_gospeed;//默认速度
    str_tfl.turnspeed=par_turnspeed;//拐弯速度
    str_tfl.cachespeed=par_cachespeed;//前冲速度
    str_tfl.doing=tf_ture;//开始做
}//定时器坐标巡线步骤生成









void fun_setxy(uc par_1x,uc par_1y,uc par_1value,enum varENU_dir par_1fx,enum varENU_dir par_1gw,
    par_2x,uc par_2y,uc par_2value,enum varENU_dir par_2fx,enum varENU_dir par_2gw,
    par_3x,uc par_3y,uc par_3value,enum varENU_dir par_3fx,enum varENU_dir par_3gw,
    par_4x,uc par_4y,uc par_4value,enum varENU_dir par_4fx,enum varENU_dir par_4gw,
    uc par_5value,uc par_5fx){
    //x为x轴坐标,y为y轴坐标,value为工位号,fx为到达此坐标时需要的朝向,gw为工位在小车的哪一侧
    uc loc_con;

    //设置坐标的value
    str_zbfl.xy[par_1x][par_1y].value=par_1value;
    str_zbfl.xy[par_2x][par_2y].value=par_2value;
    str_zbfl.xy[par_3x][par_3y].value=par_3value;
    str_zbfl.xy[par_4x][par_4y].value=par_4value;
    str_zbfl.top.value=par_5value;

    //设置坐标的方向
    str_zbfl.xy[par_1x][par_1y].fx=par_1fx;
    str_zbfl.xy[par_2x][par_2y].fx=par_2fx;
    str_zbfl.xy[par_3x][par_3y].fx=par_3fx;
    str_zbfl.xy[par_4x][par_4y].fx=par_4fx;
    str_zbfl.top.fx=par_5fx;

    //屏蔽工件台相关坐标
    fun_pbxy(par_1x,par_1y,par_1fx,par_1gw);
    fun_pbxy(par_2x,par_2y,par_2fx,par_2gw);
    fun_pbxy(par_3x,par_3y,par_3fx,par_3gw);
    fun_pbxy(par_4x,par_4y,par_4fx,par_4gw);

    //屏蔽必须屏蔽的边界坐标
    for(loc_con=0;loc_con<=13;loc_con++){//屏蔽左右两侧分别向左右走的坐标
        str_zbfl.xy[0][loc_con].enleft=tf_false;
        str_zbfl.xy[4][loc_con].enright=tf_false;
    }
    for(loc_con=0;loc_con<=4;loc_con++){//屏蔽上下两侧分别向上下走的坐标
        str_zbfl.xy[loc_con][0].endown=tf_false;
        str_zbfl.xy[loc_con][13].enup=tf_false;//可以到达13但在13不能向上走
    }

    //Y=12轴中间
    str_zbfl.xy[1][12].enup=tf_false;
    str_zbfl.xy[2][12].enup=tf_false;
    str_zbfl.xy[3][12].enup=tf_false;
    
    //两个边儿上的虚拟坐标禁止转弯
    str_zbfl.xy[0][13].enright=tf_false;
    str_zbfl.xy[4][13].enleft=tf_false;

    //三个中间位虚拟坐标禁止一切运动
    str_zbfl.xy[1][13].enright=tf_false;
    str_zbfl.xy[1][13].enleft=tf_false;
    str_zbfl.xy[1][13].endown=tf_false;
    str_zbfl.xy[2][13].enright=tf_false;
    str_zbfl.xy[2][13].enleft=tf_false;
    str_zbfl.xy[2][13].endown=tf_false;
    str_zbfl.xy[3][13].enright=tf_false;
    str_zbfl.xy[3][13].enleft=tf_false;
    str_zbfl.xy[3][13].endown=tf_false;

    //中间一条没线的禁止一切运动
    str_zbfl.xy[2][12].enright=tf_false;
    str_zbfl.xy[2][12].enleft=tf_false;
    str_zbfl.xy[2][12].endown=tf_false;

    //禁止到达中间一条没线的
    str_zbfl.xy[1][12].enright=tf_false;
    str_zbfl.xy[3][12].enleft=tf_false;
    str_zbfl.xy[2][11].enup=tf_false;

    //禁止到达抓件台周围
    str_zbfl.xy[1][0].enright=tf_false;
    str_zbfl.xy[1][1].enright=tf_false;
    str_zbfl.xy[3][1].enright=tf_false;
    str_zbfl.xy[4][0].enleft=tf_false;
    str_zbfl.xy[4][1].enleft=tf_false;

    //禁止达抓件台周围坐标的一切运动
    str_zbfl.xy[2][1].enup=tf_false;
    str_zbfl.xy[2][1].endown=tf_false;
    str_zbfl.xy[2][1].enleft=tf_false;
    str_zbfl.xy[2][1].enright=tf_false;
    str_zbfl.xy[2][0].enup=tf_false;
    str_zbfl.xy[2][0].endown=tf_false;
    str_zbfl.xy[2][0].enleft=tf_false;
    str_zbfl.xy[2][0].enright=tf_false;
    str_zbfl.xy[3][1].enup=tf_false;
    str_zbfl.xy[3][1].endown=tf_false;
    str_zbfl.xy[3][1].enleft=tf_false;
    str_zbfl.xy[3][1].enright=tf_false;
    str_zbfl.xy[3][0].enup=tf_false;
    str_zbfl.xy[3][0].endown=tf_false;
    str_zbfl.xy[3][0].enleft=tf_false;
    str_zbfl.xy[3][0].enright=tf_false;

    //禁止达抓件台周围坐标的部分运动
    str_zbfl.xy[2][2].enright=tf_false;
    str_zbfl.xy[2][2].endown=tf_false;
    str_zbfl.xy[3][2].enleft=tf_false;
    str_zbfl.xy[3][2].endown=tf_false;
}//设置初始坐标
void fun_pbxy(uc par_x,uc par_y,enum varENU_dir par_fx,enum varENU_dir par_gw){
    /*
        屏蔽某一个坐标是指可以到达此坐标,但位于此坐标不允许相应的运动.
    */
    if(par_fx==dir_down){//如果需要向下停
        if(par_gw==dir_left){//如果工位在小车左边
            if(par_x==0){
                str_zbfl.xy[par_x][par_y].enright=tf_false;
                str_zbfl.xy[par_x+1][par_y].enleft=tf_false;
                str_zbfl.xy[par_x+2][par_y].enleft=tf_false;
                str_zbfl.xy[par_x][par_y-1].enright=tf_false;
                str_zbfl.xy[par_x+1][par_y-1].enleft=tf_false;
                str_zbfl.xy[par_x+2][par_y-1].enleft=tf_false;
            }else if(par_x==3){
                str_zbfl.xy[par_x-1][par_y].enright=tf_false;
                str_zbfl.xy[par_x][par_y].enright=tf_false;
                str_zbfl.xy[par_x+1][par_y].enleft=tf_false;
                str_zbfl.xy[par_x-1][par_y-1].enright=tf_false;
                str_zbfl.xy[par_x][par_y-1].enright=tf_false;
                str_zbfl.xy[par_x+1][par_y-1].enleft=tf_false;
            }else{
                str_zbfl.xy[par_x-1][par_y].enright=tf_false;
                str_zbfl.xy[par_x][par_y].enright=tf_false;
                str_zbfl.xy[par_x+1][par_y].enleft=tf_false;
                str_zbfl.xy[par_x+2][par_y].enleft=tf_false;
                str_zbfl.xy[par_x-1][par_y-1].enright=tf_false;
                str_zbfl.xy[par_x][par_y-1].enright=tf_false;
                str_zbfl.xy[par_x+1][par_y-1].enleft=tf_false;
                str_zbfl.xy[par_x+2][par_y-1].enleft=tf_false;
            }
        }
        else if(par_gw==dir_right){//如果工位在小车右边
            if(par_x==1){
                str_zbfl.xy[par_x-1][par_y].enright=tf_false;
                str_zbfl.xy[par_x][par_y].enleft=tf_false;
                str_zbfl.xy[par_x+1][par_y].enleft=tf_false;
                str_zbfl.xy[par_x-1][par_y-1].enright=tf_false;
                str_zbfl.xy[par_x][par_y-1].enleft=tf_false;
                str_zbfl.xy[par_x+1][par_y-1].enleft=tf_false;
            }else if(par_x==4){
                str_zbfl.xy[par_x-2][par_y].enright=tf_false;
                str_zbfl.xy[par_x-1][par_y].enright=tf_false;
                str_zbfl.xy[par_x][par_y].enleft=tf_false;
                str_zbfl.xy[par_x-2][par_y-1].enright=tf_false;
                str_zbfl.xy[par_x-1][par_y-1].enright=tf_false;
                str_zbfl.xy[par_x][par_y-1].enleft=tf_false;
            }else{
                str_zbfl.xy[par_x-2][par_y].enright=tf_false;
                str_zbfl.xy[par_x-1][par_y].enright=tf_false;
                str_zbfl.xy[par_x][par_y].enleft=tf_false;
                str_zbfl.xy[par_x+1][par_y].enleft=tf_false;
                str_zbfl.xy[par_x-2][par_y-1].enright=tf_false;
                str_zbfl.xy[par_x-1][par_y-1].enright=tf_false;
                str_zbfl.xy[par_x][par_y-1].enleft=tf_false;
                str_zbfl.xy[par_x+1][par_y-1].enleft=tf_false;
            }
        }
    }else if(par_fx==dir_up){//如果需要向上停
        if(par_gw==dir_left){//如果工位在小车左边
            if(par_x==1){
                str_zbfl.xy[par_x-1][par_y].enright=tf_false;
                str_zbfl.xy[par_x][par_y].enleft=tf_false;
                str_zbfl.xy[par_x+1][par_y].enleft=tf_false;
                str_zbfl.xy[par_x-1][par_y+1].enright=tf_false;
                str_zbfl.xy[par_x][par_y+1].enleft=tf_false;
                str_zbfl.xy[par_x+1][par_y+1].enleft=tf_false;
            }else if(par_x==4){
                str_zbfl.xy[par_x-2][par_y].enright=tf_false;
                str_zbfl.xy[par_x-1][par_y].enright=tf_false;
                str_zbfl.xy[par_x][par_y].enleft=tf_false;
                str_zbfl.xy[par_x-2][par_y+1].enright=tf_false;
                str_zbfl.xy[par_x-1][par_y+1].enright=tf_false;
                str_zbfl.xy[par_x][par_y+1].enleft=tf_false;
            }else{
                str_zbfl.xy[par_x-2][par_y].enright=tf_false;
                str_zbfl.xy[par_x-1][par_y].enright=tf_false;
                str_zbfl.xy[par_x][par_y].enleft=tf_false;
                str_zbfl.xy[par_x+1][par_y].enleft=tf_false;
                str_zbfl.xy[par_x-2][par_y+1].enright=tf_false;
                str_zbfl.xy[par_x-1][par_y+1].enright=tf_false;
                str_zbfl.xy[par_x][par_y+1].enleft=tf_false;
                str_zbfl.xy[par_x+1][par_y+1].enleft=tf_false;
            }
        }
        else if(par_gw==dir_right){//如果工位在小车右边
            if(par_x==0){
                str_zbfl.xy[par_x][par_y].enright=tf_false;
                str_zbfl.xy[par_x+1][par_y].enleft=tf_false;
                str_zbfl.xy[par_x+2][par_y].enleft=tf_false;
                str_zbfl.xy[par_x][par_y+1].enright=tf_false;
                str_zbfl.xy[par_x+1][par_y+1].enleft=tf_false;
                str_zbfl.xy[par_x+2][par_y+1].enleft=tf_false;
            }else if(par_x==3){
                str_zbfl.xy[par_x-1][par_y].enright=tf_false;
                str_zbfl.xy[par_x][par_y].enright=tf_false;
                str_zbfl.xy[par_x+1][par_y].enleft=tf_false;
                str_zbfl.xy[par_x-1][par_y+1].enright=tf_false;
                str_zbfl.xy[par_x][par_y+1].enright=tf_false;
                str_zbfl.xy[par_x+1][par_y+1].enleft=tf_false;
            }else{
                str_zbfl.xy[par_x-1][par_y].enright=tf_false;
                str_zbfl.xy[par_x][par_y].enright=tf_false;
                str_zbfl.xy[par_x+1][par_y].enleft=tf_false;
                str_zbfl.xy[par_x+2][par_y].enleft=tf_false;
                str_zbfl.xy[par_x-1][par_y+1].enright=tf_false;
                str_zbfl.xy[par_x][par_y+1].enright=tf_false;
                str_zbfl.xy[par_x+1][par_y+1].enleft=tf_false;
                str_zbfl.xy[par_x+2][par_y+1].enleft=tf_false;
            }
        }
    }
}//通过工件的朝向和小车的车头方向屏蔽坐标
void fun_getxy(char par_value){
    uc loc_xhx,loc_xhy;//两个循环变量
    str_now.x=str_begin.x;//当前的x轴坐标等于起始的x轴坐标
    str_now.y=str_begin.y;//当前的y轴坐标等于起始的y轴坐标
    str_now.ctfx=str_begin.ctfx;//当前的车头方向等于起始的车头方向
    if(par_value==str_zbfl.top.value){//如果是去最顶上的工位台
        if(str_zbfl.top.fx==dir_right){
            str_next.x=0;//x轴坐标赋值为0
            str_next.y=12;//y轴坐标赋值为12
            str_next.ctfx=dir_right;//车头方向赋值为dir_right
        }else if(str_zbfl.top.fx==dir_left){
            str_next.x=4;//x轴坐标赋值为4
            str_next.y=12;//y轴坐标赋值为12
            str_next.ctfx=dir_left;//车头方向赋值为dir_left
        }
    }else{
        for(loc_xhx=0;loc_xhx<=4;loc_xhx++){//X轴循环,0-5
            for(loc_xhy=0;loc_xhy<=12;loc_xhy++){//y轴循环,0-12
                if(str_zbfl.xy[loc_xhx][loc_xhy].value==par_value){//如果找到了这个件
                    str_next.x=loc_xhx;//x轴坐标赋值给str_next.x
                    str_next.y=loc_xhy;//y轴坐标赋值给str_next.y
                    str_next.ctfx=str_zbfl.xy[loc_xhx][loc_xhy].fx;//车头方向赋值给str_next.ctfx
                    return;//退出函数
                }
            }
        }
    }
}//通过想要去的工位号获得XY坐标并储存在str_next结构体中,把现在的工位号存储再str_now结构体中
void fun_xymove(enum varENU_tfl par_model,char par_value){
    if(*str_tfl.run==0){//如果当前步骤没被编辑过
        if(par_model==tfl_cache){//如果第一个是前冲
            return;//不允许是前冲
        }
        (*str_tfl.run)=par_model;//那就等于现在的模式
    }else if(*str_tfl.run!=par_model){//如果当前步骤和传入的步骤不一样
        str_tfl.run+=2;//指针指向下一组数组
        (*str_tfl.run)=par_model;//存入步骤
    }
    switch(*str_tfl.run){//选择正在编辑的步骤
        case tfl_line://如果正在编辑巡线
            *(str_tfl.run+1)+=par_value;//巡线步骤的参数加上需要增加的参数(据说可以减去)
            switch(str_now.ctfx){
                case dir_up:
                    str_now.y+=par_value;
                    break;
                case dir_down:
                    str_now.y-=par_value;
                    break;
                case dir_left:
                    str_now.x-=par_value;
                    break;
                case dir_right:
                    str_now.x+=par_value;
                    break;
                default:
                    break;
            }
            break;
        case tfl_turn://如果正在编辑转弯
            *(str_tfl.run+1)=par_value;//参数传入
            switch(str_now.ctfx){
                case dir_up:
                    switch(par_value){
                        case tur_l90:
                            str_now.ctfx=dir_left;
                            break;
                        case tur_r90:
                            str_now.ctfx=dir_right;
                            break;
                        case tur_l180:
                            str_now.ctfx=dir_down;
                            break;
                        case tur_r180:
                            str_now.ctfx=dir_down;
                            break;
                        default:
                            break;
                    }
                    break;
                case dir_down:
                    switch(par_value){
                        case tur_l90:
                            str_now.ctfx=dir_right;
                            break;
                        case tur_r90:
                            str_now.ctfx=dir_left;
                            break;
                        case tur_l180:
                            str_now.ctfx=dir_up;
                            break;
                        case tur_r180:
                            str_now.ctfx=dir_up;
                            break;
                        default:
                            break;
                    }
                    break;
                case dir_left:
                    switch(par_value){
                        case tur_l90:
                            str_now.ctfx=dir_down;
                            break;
                        case tur_r90:
                            str_now.ctfx=dir_up;
                            break;
                        case tur_l180:
                            str_now.ctfx=dir_right;
                            break;
                        case tur_r180:
                            str_now.ctfx=dir_right;
                            break;
                        default:
                            break;
                    }
                    break;
                case dir_right:
                    switch(par_value){
                        case tur_l90:
                            str_now.ctfx=dir_up;
                            break;
                        case tur_r90:
                            str_now.ctfx=dir_left;
                            break;
                        case tur_l180:
                            str_now.ctfx=dir_left;
                            break;
                        case tur_r180:
                            str_now.ctfx=dir_left;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;
        case tfl_cache://如果正在编辑前冲
            *(str_tfl.run+1)+=par_value;
            break;
        default:
            break;
    }
}//坐标巡线单步累计步骤生成
char fun_getpublicy(char par_xnow,char par_ynow,char par_xnext,char par_ynext,enum varENU_dir par_gwfx){
    //返回值为整数为公共的Y,-1为顶端坐标,-2为在同X轴,-3为错误
    uc loc_xhx,loc_xhy,loc_flag=0,loc_con=0;
    uc loc_data[12];
    memset(loc_data,def_end,sizeof(loc_data));//清空数组
    if(par_xnext>par_xnow){//往右走
        for(loc_xhy=0;loc_xhy<=12;loc_xhy++){//循环扫描所有可能性的Y
            for(loc_xhx=par_xnow;loc_xhx<=par_xnext;loc_xhx++){//循环扫描两点之间的X
                if(str_zbfl.xy[loc_xhx][loc_xhy].enright==tf_ture){//如果允许右行
                    loc_flag++;//标志位+1
                }
            }
            if(loc_flag==par_xnext-par_xnow+1){//如果可以走的线就是一共需要走的线
                loc_data[loc_con++]=loc_xhy;//将Y轴数据记录至数组
            }
            loc_flag=0;//标志位清零
        }
    }else if(par_xnext<par_xnow){//往左走
        for(loc_xhy=0;loc_xhy<=12;loc_xhy++){//循环扫描所有可能性的Y
            for(loc_xhx=par_xnow;loc_xhx>=par_xnext;loc_xhx--){//循环扫描两点之间的X 
                if(str_zbfl.xy[loc_xhx][loc_xhy].enleft==tf_ture){//如果允许左行
                    loc_flag++;//标志位+1
                }
            }
            if(loc_flag==par_xnow-par_xnext+1){//如果可以走的线就是一共需要走的线
                loc_data[loc_con++]=loc_xhy;//将Y轴数据记录至数组
            }
            loc_flag=0;//标志位清零
        }
    }else{//不往左不往右
        return (par_ynext);
    }
    #ifdef Debug
        printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",(int)loc_data[0],
            (int)loc_data[1],
            (int)loc_data[2],
            (int)loc_data[3],
            (int)loc_data[4],
            (int)loc_data[5],
            (int)loc_data[6],
            (int)loc_data[7],
            (int)loc_data[8],
            (int)loc_data[9],
            (int)loc_data[10],
            (int)loc_data[11]);
    #endif
    if(par_ynext>par_ynow){//要往上走
        if(par_gwfx==dir_up){//工位要求向上停
            for(loc_con=0;loc_data[loc_con]!=def_end;loc_con++){//循环已经赋值过的数组
                if(loc_data[loc_con]>=par_ynow && loc_data[loc_con]<par_ynext){//如果比现在的大,比要去的小
                    return (loc_data[loc_con]);//返回值
                }
            }
            for(loc_con=0;loc_data[loc_con]!=def_end;loc_con++){//循环已经赋值过的数组
                if(loc_data[loc_con]<par_ynow){//如果比现在的小
                    return (loc_data[loc_con]);//返回值
                }
            }
            for(loc_con=0;loc_data[loc_con]!=def_end;loc_con++){//循环已经赋值过的数组
                if(loc_data[loc_con]>par_ynext){//如果比要去的大
                    return (loc_data[loc_con]);//返回值
                }
            }
        }else if(par_gwfx==dir_down){//工位要求向下停
            for(loc_con=0;loc_data[loc_con]!=def_end;loc_con++){//循环已经赋值过的数组
                if(loc_data[loc_con]>par_ynext){//如果比要去的大
                    return (loc_data[loc_con]);//返回值
                }
                if(loc_data[loc_con]<par_ynext){//如果比要去的小
                    return (loc_data[loc_con]);//返回值
                }
            }
        }else{
            return (-1);
        }
    }else if(par_ynext<par_ynow){//往下走
        if(par_gwfx==dir_up){//工位要求向上停
            for(loc_con=0;loc_data[loc_con]!=def_end;loc_con++){//循环已经赋值过的数组
                if(loc_data[loc_con]<par_ynext){//如果比要去的小
                    return (loc_data[loc_con]);//返回值
                }
            }
            for(loc_con=0;loc_data[loc_con]!=def_end;loc_con++){//循环已经赋值过的数组
                if(loc_data[loc_con]>par_ynext){//如果比要去的大
                    return (loc_data[loc_con]);//返回值
                }
            }
        }else if(par_gwfx==dir_down){//如果工位要求朝下停
            for(loc_con=0;loc_data[loc_con]!=def_end;loc_con++){//循环已经赋值过的数组
                if(loc_data[loc_con]<=par_ynow && loc_data[loc_con]>par_ynext){//如果比现在的小,比要去的大
                    return (loc_data[loc_con]);//返回值
                }
            }
            for(loc_con=0;loc_data[loc_con]!=def_end;loc_con++){//循环已经赋值过的数组
                if(loc_data[loc_con]>par_ynow){//如果比现在的大
                    return (loc_data[loc_con]);//返回值
                }
            }
            for(loc_con=0;loc_data[loc_con]!=def_end;loc_con++){//循环已经赋值过的数组
                if(loc_data[loc_con]<par_ynext){//如果比要去的小
                    return (loc_data[loc_con]);//返回值
                }
            }
        }else{
            return (-1);
        }
    }else{
        return (-2);
    }
    return (-3);
}//获取共有Y轴
void fun_record(char par_xnow,char par_ynow,enum varENU_dir par_ctfxnow,char par_xnext,char par_ynext,enum varENU_dir par_ctfxnext){
    //          需要到的X ,需要到的y ,需要的车头方向
    /*
        优先左右走,其次考虑车头方向,再次考虑工件台的位置
    */
    char loc_xnow=par_xnow,loc_ynow=par_ynow,loc_ctfxnow=par_ctfxnow;//局部变量用于计算时的中间值
    while((par_xnow!=par_xnext)||(par_ynow!=par_ynext)||(par_ctfxnow!=par_ctfxnext)){//如果xy轴到达了,车头方向一致了
        switch(par_ctfxnow){//判断当前车头方向
            case dir_up://现在车头朝上
                if(par_xnext>par_xnow){//如果要去的x值比现在的大,向右走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_r90);
                    par_ctfxnow=dir_right;
                    continue;
                }
                if(par_xnext<par_xnow){//如果要去的x值比现在的小,向左走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_l90);
                    par_ctfxnow=dir_left;
                    continue;
                }
                if(par_ynext>par_ynow){//如果要去的Y值比现在的大,向上走
                    fun_xymove(tfl_line,1);
                    par_ynow+=1;
                    continue;
                }
                if(par_ynext<par_ynow){//如果要去的Y值比现在的小,向下走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_r180);
                    par_ctfxnow=dir_down;
                    continue;
                }
                if(par_xnext==par_xnow&&par_ynext==par_ynow){//需要在原地转个弯
                    fun_xymove(tfl_cache,40);
                    switch(par_ctfxnext){
                        case dir_left:
                            fun_xymove(tfl_turn,tur_l90);
                            break;
                        case dir_right:
                            fun_xymove(tfl_turn,tur_r90);
                            break;
                        case dir_down:
                            fun_xymove(tfl_turn,tur_l180);
                            break;
                        default:
                            break;
                    }
                    par_ctfxnow=par_ctfxnext;
                    continue;
                }
                break;
            case dir_down://现在车头朝下
                if(par_xnext>par_xnow){//如果要去的x值比现在的大//向右走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_l90);
                    par_ctfxnow=dir_right;
                    continue;
                }
                if(par_xnext<par_xnow){//如果要去的x值比现在的小//向左走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_r90);
                    par_ctfxnow=dir_left;
                    continue;
                }
                if(par_ynext<par_ynow){//如果要去的Y值比现在的小//向下走
                    fun_xymove(tfl_line,1);
                    par_ynow-=1;
                    continue;
                }
                if(par_ynext>par_ynow){//如果要去的Y值比现在的大//向上走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_r180);
                    par_ctfxnow=dir_up;
                    continue;
                }
                if(par_xnext==par_xnow&&par_ynext==par_ynow){//需要在原地转个弯
                    fun_xymove(tfl_cache,40);
                    switch(par_ctfxnext){
                        case dir_left:
                            fun_xymove(tfl_turn,tur_r90);
                            break;
                        case dir_right:
                            fun_xymove(tfl_turn,tur_l90);
                            break;
                        case dir_up:
                            fun_xymove(tfl_turn,tur_l180);
                            break;
                        default:
                            break;
                    }
                    par_ctfxnow=par_ctfxnext;
                    continue;
                }
                break;
            case dir_right://现在车头朝右
                if(par_xnext>par_xnow){//如果要去的x值比现在的大,向右走
                    fun_xymove(tfl_line,1);
                    par_xnow+=1;
                    continue;
                }
                if(par_xnext<par_xnow){//如果要去的x值比现在的小,向左走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_l180);
                    par_ctfxnow=dir_left;
                    continue;
                }
                if(par_ynext>par_ynow){//如果要去的Y值比现在的大,向上走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_l90);
                    par_ctfxnow=dir_up;
                    continue;
                }
                if(par_ynext<par_ynow){//如果要去的Y值比现在的小,向下走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_r90);
                    par_ctfxnow=dir_down;
                    continue;
                }
                if(par_xnext==par_xnow&&par_ynext==par_ynow){//需要在原地转个弯
                    fun_xymove(tfl_cache,40);
                    switch(par_ctfxnext){
                        case dir_left:
                            fun_xymove(tfl_turn,tur_l180);
                            break;
                        case dir_down:
                            fun_xymove(tfl_turn,tur_r90);
                            break;
                        case dir_up:
                            fun_xymove(tfl_turn,tur_l90);
                            break;
                        default:
                            break;
                    }
                    par_ctfxnow=par_ctfxnext;
                    continue;
                }
                break;
            case dir_left://现在车头朝左
                if(par_xnext<par_xnow){//如果要去的x值比现在的小,向左走
                    fun_xymove(tfl_line,1);
                    par_xnow-=1;
                    continue;
                }
                if(par_xnext>par_xnow){//如果要去的x值比现在的大,向右走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_l180);
                    par_ctfxnow=dir_right;
                    continue;
                }
                if(par_ynext>par_ynow){//如果要去的Y值比现在的大,向上走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_r90);
                    par_ctfxnow=dir_up;
                    continue;
                }
                if(par_ynext<par_ynow){//如果要去的Y值比现在的小,向下走
                    fun_xymove(tfl_cache,40);
                    fun_xymove(tfl_turn,tur_l90);
                    par_ctfxnow=dir_down;
                    continue;
                }
                if(par_xnext==par_xnow&&par_ynext==par_ynow){//需要在原地转个弯
                    fun_xymove(tfl_cache,40);
                    switch(par_ctfxnext){
                        case dir_right:
                            fun_xymove(tfl_turn,tur_l180);
                            break;
                        case dir_down:
                            fun_xymove(tfl_turn,tur_l90);
                            break;
                        case dir_up:
                            fun_xymove(tfl_turn,tur_r90);
                            break;
                        default:
                            break;
                    }
                    par_ctfxnow=par_ctfxnext;
                    continue;
                }
                break;
            default:
                break;
        }
    }
}//定时器坐标巡线步骤生成
void fun_coordinate(char par_gospeed,char par_turnspeed,char par_cachespeed){
    char loc_y=fun_getpublicy(str_now.x,str_now.y,str_next.x,str_next.y,str_next.ctfx);
    fun_delay(50,del_ms);
    str_tfl.run=str_tfl.step;//指针指向第一个步骤
    if(str_next.x==str_now.x){
        if(str_next.ctfx==dir_up){
            fun_record(str_now.x,str_now.y,str_now.ctfx,str_now.x,str_next.y-1,str_next.ctfx);
        }else if(str_next.ctfx==dir_down){
            fun_record(str_now.x,str_now.y,str_now.ctfx,str_now.x,str_next.y+1,str_next.ctfx);
        }else{
            fun_record(str_now.x,str_now.y,str_now.ctfx,str_now.x,str_next.y,dir_up);
        }
    }else if(str_next.y==str_now.y){
        ;
    }else{
        //第一步:沿Y轴走
        if(str_next.x>str_now.x){
            fun_record(str_now.x,str_now.y,str_now.ctfx,str_now.x,loc_y,dir_right);
            str_now.ctfx=dir_right;
        }else if(str_next.x<str_now.x){
            fun_record(str_now.x,str_now.y,str_now.ctfx,str_now.x,loc_y,dir_left);
            str_now.ctfx=dir_left;
        }else{
            fun_record(str_now.x,str_now.y,str_now.ctfx,str_now.x,loc_y,str_next.ctfx);
        }
        str_now.y=loc_y;
        //第二步:沿X轴走
        if(str_next.y>str_now.y){
            fun_record(str_now.x,str_now.y,str_now.ctfx,str_next.x,str_now.y,dir_up);
            str_now.ctfx=dir_up;
        }else if(str_next.y<str_now.y){
            fun_record(str_now.x,str_now.y,str_now.ctfx,str_next.x,str_now.y,dir_down);
            str_now.ctfx=dir_down;
        }else{
            fun_record(str_now.x,str_now.y,str_now.ctfx,str_next.x,str_now.y,str_next.ctfx);
            str_now.ctfx=str_next.ctfx;
        }
        str_now.x=str_next.x;
        //第三步:沿Y轴走
        if(str_next.ctfx==dir_up){
            fun_record(str_now.x,str_now.y,str_now.ctfx,str_now.x,str_next.y-1,str_next.ctfx);
        }else if(str_next.ctfx==dir_down){
            fun_record(str_now.x,str_now.y,str_now.ctfx,str_now.x,str_next.y+1,str_next.ctfx);
        }else{
            fun_record(str_now.x,str_now.y,str_now.ctfx,str_now.x,str_next.y,dir_up);
        }
    }

    fun_xymove(tfl_line,1);//进入工位台
    fun_xymove(tfl_cache,40);//前冲
    str_tfl.run+=2;//指针指向下一组数组
    (*str_tfl.run)=def_end;//存入步骤
    printf("%d\n",(int)loc_y);

    str_tfl.online=tf_false;//不在线
    str_tfl.run=str_tfl.step;//指针指向第一个数组
    str_tfl.gospeed=par_gospeed;//默认速度
    str_tfl.turnspeed=par_turnspeed;//拐弯速度
    str_tfl.cachespeed=par_cachespeed;//前冲速度
    str_tfl.doing=tf_ture;//开始做
}//自动巡线之坐标
void fun_go(enum varENU_go par_model){
    if(par_model>=115){
        ;
    }else{
        fun_getxy(par_model-109);//通过工位号获取xy坐标
        if(str_next.ctfx==dir_up){//如果去的地方要车头向上
            //fun_record(str_next.x,str_next.y-1,str_next.ctfx,56,45,50);//少向上一个
            fun_coordinate(56,45,50);
            str_now.x=str_next.x;
            str_now.y=str_next.y;
            str_now.ctfx=str_next.ctfx;
        }else if(str_next.ctfx==dir_down){//如果去的地方要车头向下
            //fun_record(str_next.x,str_next.y+1,str_next.ctfx,56,45,50);//少向下一个
            fun_coordinate(56,45,50);
            str_now.x=str_next.x;
            str_now.y=str_next.y;
            str_now.ctfx=str_next.ctfx;
        }else{//最顶上工位的情况
            //fun_record(str_next.x,str_next.y,dir_up,56,45,50);//不多上不多下,但设置车头方向为向前
            fun_coordinate(56,45,50);
            if(str_next.x==0){//从左边的来
                str_now.x=4;
                str_now.y=13;
                str_now.ctfx=dir_down;
            }else if(str_next.x==4){//从右边的来
                str_now.x=0;
                str_now.y=13;
                str_now.ctfx=dir_down;
            }
        }
    }
}//定时器坐标巡线最终调用形式