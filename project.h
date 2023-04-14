#pragma once
#define _CRT_SECURE_NO_WARNINGS

/*已知bug
* 发弹口的自机子弹没有伤害
* 不要同时按上下键，也不要同时按左右键，否则自机会静止，shift键失灵
* 不能通过按x键退出游戏
* 

*/
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>



//#include "c测试.cpp"

#define pi 3.14159265
//#define  judge_time_second per_time_set[5] <= time_game_running && time_game_running <= per_time_set[6]
#define _v_x 6//自机移动速度
#define _v_y 6//自机移动速度

//自机相关
enum { 灵梦 = 0, 魔理沙, 爱丽丝 };


//敌机运动轨迹相关
enum {
    move_null = 0, //  轨迹符合加速运动
    move_sin, // 正弦波
    move_x_a, // x的a次幂（a是常数）
    move_a_x  //a的x次幂
};
//敌机子弹相关



int r_enemy = 12;//敌机半径（暂定）
double length_move_x = 600, length_move_y = 560, tang_x = 50, tang_y = 20;//活动范围
int r_player = 5;//判定点半径
int x_player = tang_x + length_move_x / 2, y_player = length_move_y - (tang_y + 2 * r_player);//玩家初始位置
int order_bullet = 1;//第n个射出的子弹。
int v_bullet_player_y = 2 * r_player + 2 * r_enemy - 1;  //自机子弹的速度
int bullet_player_r = 9;//自机子弹半径
int distance_player_bullet = r_player - bullet_player_r;//自机（圆心坐标）离最近一颗发出子弹(发弹口)的距离
double v_player_x = _v_x, v_player_y = _v_y;//自机移动速度
double shift_v_player_x = v_player_x / 2, shift_v_player_y = v_player_y / 2;//低速状态下自机移动速度
int time_game_running = 0;//游戏运行时间
int number_enemy = 0, number_enemy_max = 255;//生成第n只敌机，最大256
int number_bullet_enemy = 0;//敌机的第n颗子弹
//int number_bullet_player = 0;//自机的第n颗子弹
int bullet_hurt = 25;//自机子弹的伤害
//constexpr int per_time_set[] = { 20,50,80,110,140,200,300,320,340,360,380};

//（已废弃）int tem_per_time_set[][300];//用于累加（如200加到250）  //第一组是一波运动轨迹为正弦波的敌机，共50（左侧）个

enum { 少 = 100 };

int tem_number_second = 1;//用于第二波生成敌机计数

struct bullet_enemy
{
    double x =0, y=0, r = 2;
    int isexisted = 0;//子弹是否在场内
    int size = 1; //子弹的大小，1（最小）、2、3、4……（最大）

} bullet_enemy_small[256];

struct bullet_player
{
    double x =0, y = 0, r = bullet_player_r;
    int isexisted = 0;
    //int number_hurt = bullet_hurt; //子弹伤害(已经有全局变量了)
    struct bullet_player* next_bullet;
}bullet_player[256];



/*
class enemy
{
public:




};
*/






class player {
private:
    
    


public:
    player(*player_information);
    static void shoot(int x_player, int y_player);
    static void move(int* x_player, int* y_player);
    static void boom_player();

    
};

/*
void test_1(player_information & reimu,int x,int y)//如不改变结构体内容，可以加上const
{
    reimu.v_x;
    reimu.x;
    

}
*/
struct player_information //玩家的信息
{
    int name;
    int x = x_player, y = y_player;
    int v_x = v_player_x, v_y = v_player_y;
    int bullet_hurt;

};
void player::shoot(int x_player, int y_player)//生成自机射出的子弹
{
    for (int i = 0; i < 2; i++)
    {
        bullet_player[order_bullet].isexisted = 1;
        bullet_player[order_bullet].y = (y_player + distance_player_bullet);
        bullet_player[order_bullet].x = x_player + pow(-1, i) * (bullet_player_r + 2);
        order_bullet++;
    }
    if (order_bullet > 256 - 2)//可能是内存溢出吧，不减二的话子弹到达256颗的时候自机和子弹都会消失
    {
        order_bullet = 1;
    }
}

void player::move(int* x_player, int* y_player)//自机移动
{
    //(废弃)int inter_move = _getch();


    if (GetKeyState(38) < 0)//上        
    {
        *y_player -= v_player_y;
    }

    if (GetKeyState(40) < 0)//下          
    {
        *y_player += v_player_y;
    }


    if (GetKeyState(37) < 0)//左
    {
        *x_player -= v_player_x;
    }

    if (GetKeyState(39) < 0)//右           
    {
        *x_player += v_player_x;
    }

    //防止出界
    if (*x_player - r_player < tang_x)     //左   右
    {
        *x_player = tang_x + r_player;
    }
    if (*x_player + r_player > tang_x + length_move_x)
    {
        *x_player = tang_x + length_move_x - r_player;
    }
    if (*y_player - r_player < tang_y)     //上   下
    {
        *y_player = tang_y + r_player;
    }
    if (*y_player + r_player > tang_y + length_move_y)
    {
        *y_player = tang_y + length_move_y - r_player;
    }
}
void player::boom_player()//放B
{


}