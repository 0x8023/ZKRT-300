void fun_xymove(enum varENU_tfl par_model,char par_value){
    if((*str_tfl.run)==0){//如果当前步骤没被编辑过
        (*str_tfl.run)=par_model;//那就等于现在的模式
    }else if(*str_tfl.run!=par_model){//如果当前步骤和传入的步骤不一样
        (*str_tfl.run)+=2;//指针指向下一组数组
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