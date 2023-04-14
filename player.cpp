// c测试.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include "project.h"

void player_z_x_c_s()
{

    if (GetKeyState(160) < 0)//左shift
    {

        v_player_x = shift_v_player_x;
        v_player_y = shift_v_player_y;
        setfillcolor(WHITE);
        solidcircle(x_player, y_player, r_player - 2);

    }//放后面其实也可以（滑稽）
    else {
        v_player_x = _v_x;
        v_player_y = _v_y;//暂时想不出其他方法了
    }

    player::move(&x_player, &y_player);
    if (GetKeyState(90) < 0)//Z
    {
        player::shoot(x_player, y_player);
    }
    if (GetKeyState(88) < 0)//X
    {
        player::boom_player();
    }
    if (GetKeyState(67) < 0)//C
    {

    }
    



}

int enemy_move_sin(int tem_number_enemy,int tem_v_x,int control_distance,int control_place,int max_hight)//用于控制敌机速度进而控制敌机运动轨迹（正弦波）(横向)
//输入这是第几个敌机，临时的横向速度，用于控制相位大小，用于控制波形位置,用于控制振幅
{
    enemy[tem_number_enemy].x += tem_v_x;
    //enemy[tem_number_enemy].y = tang_y + enemy[tem_number_enemy].frist_y + 50 *  sin(((double)enemy[number_enemy].time_exist)*((double)pi / 2));
    enemy[tem_number_enemy].y = tang_y + enemy[tem_number_enemy].frist_y + max_hight * sin(((float)enemy[tem_number_enemy].time_exist / control_distance) + control_place);
    enemy[tem_number_enemy].time_exist++;
    
    return 0;
}

void perpare_sin(int x,int y,int hight)//当敌机按正弦波运动时要做的准备（用于生成敌机不显示）
//输入生成时离最顶端的高度（y坐标）(高度偏移量)
{
    enemy[number_enemy].frist_x = x;
    enemy[number_enemy].frist_y = y + hight;
    enemy[number_enemy].x = x;
    enemy[number_enemy].y = y + hight;
    enemy[number_enemy].a_x = 0;
    enemy[number_enemy].a_y = 0;
    enemy[number_enemy].isexisted = 1;
    enemy[number_enemy].mark_move_line = move_sin;
    number_enemy++;
}

void perpare_pow(int x,int y)//当敌机按指数函数运动时
//输入底数
{
    enemy[number_enemy].frist_x = x;
    enemy[number_enemy].frist_y = y;
    enemy[number_enemy].x = x;
    enemy[number_enemy].y = y;
    enemy[number_enemy].a_x = 0;
    enemy[number_enemy].a_y = 0;
    enemy[number_enemy].isexisted = 1;
    enemy[number_enemy].mark_move_line = move_x_a;
    number_enemy++;

}
void enemy_move_pow(int tem_number,int tem_v_x,double left,int sign_x = 1,int sign_y = 1)
//left是指数,x是敌机横坐标,sign_y控制向上还是向下
{
    
    enemy[tem_number].x = enemy[tem_number].frist_x - (  (sign_x * (enemy[tem_number].time_exist) * tem_v_x));//坐标系原点平移
    enemy[tem_number].y = -sign_y * pow((long double)( enemy[tem_number].time_exist), (long double)left) + enemy[tem_number].frist_y;
    //enemy[tem_number].y =  enemy[tem_number].time_exist  + enemy[tem_number].frist_y;
    enemy[tem_number].time_exist++;    
}

void add_enemy_normal(int x,int y,int v_x,int v_y,int a_x,int a_y,int wait)//生成运动符合加速运动的敌机
//输入的分别是  
{

    //enemy[number_enemy - 1].next_enemy = (next_enemy*)malloc(sizeof(enemy[number_enemy]));//动态链表
    enemy[number_enemy].x = x;//初始位置
    enemy[number_enemy].y = y;//初始位置

    enemy[number_enemy].v_x = v_x;
    enemy[number_enemy].v_y = v_y;
    enemy[number_enemy].a_x = a_x;
    enemy[number_enemy].a_y = a_y;
    enemy[number_enemy].isexisted = 1;
    enemy[number_enemy].wait = wait;//等待wait游戏刻后按预定轨迹运动（否则做匀速直线运动）   //单独封装成一个函数
    number_enemy++;
}

int judge_enemy_ifhitten(int number)//判断敌机是否中弹 输入的是敌机的编号
{
    if (enemy[number].isexisted)
    {
        for (int a = 0; a < 256; a++)//a代表子弹的编号
        {
            bool distence = (pow(enemy[number].x - bullet_player[a].x, 2) + pow(enemy[number].y - bullet_player[a].y, 2)) <= pow(r_enemy + bullet_player_r,2);
            if (bullet_player[a].isexisted && distence)
            {
                bullet_player[a].isexisted = 0;//子弹不能穿透
                return 1;
            }

        }
    }
    return 0;
}



int main()
{
    initgraph(length_screen_x,length_screen_y);

    //预处理


    BeginBatchDraw();
    while (1)
    {
        setfillcolor(GREEN);//背景色
        solidrectangle(tang_x, tang_y, tang_x + length_move_x, tang_y + length_move_y);
        setfillcolor(RED);//自机判定点色
        solidcircle(x_player, y_player, r_player);
       
        //自机相关
        
        player_z_x_c_s();


        //{
            //(废弃)if (inter == 224)//自机移动
            //{
                //move_player(&x_player,&y_player);
            //}
            
            //{
            
                
                //shoot_player(x_player,y_player);
            //}
        //}


        //游戏进行，生成敌机（不显示）

        
        //int tem_time = 2;//间隔2帧生成敌机


        if (number_enemy > number_enemy_max)
        {
            number_enemy = 0;//初始化
        }

            switch (time_game_running)//时刻判断
            {
            case per_time_set[0]://第一波
            case per_time_set[1]:
            case per_time_set[2]:
            case per_time_set[3]:
            case per_time_set[4]:
                 
                for (int i = 1; i < 3; i++)
                {
                    add_enemy_normal(i * ((tang_x + length_move_x) / 3), tang_y, - enemy[number_enemy].v_x * pow(-1, i), enemy[number_enemy].v_y, - 1 / 4, -0.125 / 2, 20);//生成敌机信息  
                }
                
            break;
            case per_time_set[7]:
            case per_time_set[8]:
            case per_time_set[9]:
            case per_time_set[10]:
                //perpare_pow(enemy[number_enemy].x, enemy[number_enemy].y);
                perpare_pow(tang_x + length_move_x, tang_y + (length_move_y / 2));
                break;
            }
            //break;
             bool  judge_time_second = per_time_set[5] <= time_game_running && time_game_running <= per_time_set[6];//判断时间是否到达第二波。

             
             if (judge_time_second)//时间段判断
             {
                 //case (judge_time_second) ://第二波
                     //(废案)if (tem_number_second <= 50)
                 
                 perpare_sin(tang_x,tang_y,(4 * r_enemy * (tem_number_second % 5)));
                     
                     //enemy_move_sin(number_enemy);
                     //enemy[number_enemy].time_exist++;//已经有了
                     
                     tem_number_second++;

                 
             }
            



        
        //生成敌机的子弹（不显示）



        //显示敌机（绘制）
             
        for (int i = 0; i <= 256; i++)
        {
            
            if (enemy[i].isexisted)
            {
                setfillcolor(BLUE);//敌机机身颜色
                solidcircle(enemy[i].x, enemy[i].y, r_enemy);
                
                bool judge_x = (enemy[i].x +  r_enemy < tang_x) || (enemy[i].x -  r_enemy > tang_x + length_move_x);
                bool judge_y = (enemy[i].y +  r_enemy < tang_y) || (enemy[i].y -  r_enemy > tang_y + length_move_y);
                if (judge_x||judge_y)//回收敌机
                {
                    enemy[i].isexisted = 0;
                }
            }


        }


        //显示敌机子弹（绘制）


         //使自机射出的子弹移动起来
        for (int i = 0; i <= 256; i++) 
        {
            if (bullet_player[i].isexisted)//子弹移动
            {
                
                setfillcolor(BLACK);//自机子弹颜色
                solidcircle(bullet_player[i].x, bullet_player[i].y, bullet_player_r);
                bullet_player[i].y -= v_bullet_player_y;
                
            }
            if (bullet_player[i].y < 0) //回收子弹
            {
                bullet_player[i].isexisted = 0;
            }

        }

        //判断敌机是否中弹
        for (int i = 0; i < number_enemy_max; i++)
        {
            if (judge_enemy_ifhitten(i))
            {
                
                //enemy[i - 1].next_enemy = enemy[i].next_enemy; //链表（还不完善）
                enemy[i].Hp -= bullet_hurt;
                if (enemy[i].Hp <= 0)
                {
                    enemy[i].isexisted = 0;
                    enemy[i].Hp = enemy[i].number_of_Hp;
                }
                //free();
            }
        }



        //判断自机是否中弹

        

        //回收中弹和离开画面的敌机，(初始化信息 ???) //直接覆盖应该就可以了
        /*
        while(!isexisted) //???
        {
        
        }



        */

        


        //敌机移动
        for (int i = 0; i <= 256; i++)
        {
            if (enemy[i].wait != 0)//延时
            {
                enemy[i].wait--;
                enemy[i].y += enemy[i].v_y;
            }
            else
            {
                switch (enemy[i].mark_move_line)
                {
                case move_sin:
                    enemy_move_sin(i, enemy[i].v_x, 4, 0, 50);
                    break;
                case move_x_a:
                    enemy_move_pow(i,enemy[i].v_x ,1.5);
                    break;
                default:

                    if ((enemy[i].isexisted) && (enemy[i].wait == 0))
                    {
                        enemy[i].x += enemy[i].v_x;
                        enemy[i].y += enemy[i].v_y;
                        enemy[i].v_x += enemy[i].a_x;
                        enemy[i].v_y += enemy[i].a_y;

                    }
                }
            }
        }

        //绘制游戏区外画面

        //显示状态（生命值，boom、得分等）

        FlushBatchDraw();
        cleardevice();
        Sleep(1000 / 60);
        time_game_running++;
    }


    return 0;
}

