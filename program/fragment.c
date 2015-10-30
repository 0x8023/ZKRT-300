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




void fun_gety(char par_xnow,char par_xnext,char par_){

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
