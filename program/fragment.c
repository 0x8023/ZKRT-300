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