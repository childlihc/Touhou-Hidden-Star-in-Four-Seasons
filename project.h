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
#include <assert.h>
#include <initializer_list>
#include <vector>

extern int time_game;
extern double xy_to_theta(double x, double y, double* theta_name);
extern double theta_to_x(double theta, double r);
double theta_to_y(double theta, double r);
extern int screen_x, screen_y;
extern class move_class;

//#include "c测试.cpp"

#define pi 3.14159265
//#define  judge_time_second per_time_set[5] <= time_game_running && time_game_running <= per_time_set[6]
#define _v_x 6//自机移动速度
#define _v_y 6//自机移动速度

//自机相关
enum { 灵梦 = 0, 魔理沙, 爱丽丝 };


//敌机运动轨迹相关
enum move{
    move_null = 0, //  轨迹符合匀速运动
    move_add, //匀加速运动
    move_add_add, //变加速运动 
    move_sin, // 正弦波
    move_x_a, // x的a次幂（a是常数）
    move_a_x  //a的x次幂
};
//敌机子弹相关



int r_enemy = 20;//敌机半径（暂定）
double length_move_x = 600, length_move_y = 560, tang_x = 50, tang_y = 20;//活动范围
int r_player = 5;//判定点半径
double x_player = tang_x + length_move_x / 2, y_player = length_move_y - (tang_y + 2 * r_player);//玩家初始位置
int order_bullet = 1;//第n个射出的子弹。
int v_bullet_player_y = 2 * r_player + 2 * r_enemy - 1;  //自机子弹的速度
int bullet_player_r = 9;//自机子弹半径
double distance_player_bullet = r_player - bullet_player_r;//自机（圆心坐标）离最近一颗发出子弹(发弹口)的距离
double v_player_x = _v_x, v_player_y = _v_y;//自机移动速度
double shift_v_player_x = v_player_x / 2, shift_v_player_y = v_player_y / 2;//低速状态下自机移动速度
int time_game_running = 0;//游戏运行时间
int number_enemy = 0, number_enemy_max = 255;//生成第n只敌机，最大256
int number_bullet_enemy = 0;//敌机的第n颗子弹
//int number_bullet_player = 0;//自机的第n颗子弹
int bullet_hurt = 25;//自机子弹的伤害
//constexpr int per_time_set[] = { 20,50,80,110,140,200,300,320,340,360,380};

//（已废弃）int tem_per_time_set[][300];//用于累加（如200加到250）  //第一组是一波运动轨迹为正弦波的敌机，共50（左侧）个

enum enemy_life { 少 = 100 };
enum bullet_size { 米弹 = 3, 鳞弹 = 5 , 大玉 = 40 };

int tem_number_second = 1;//用于第二波生成敌机计数
/*
struct bullet_enemy
{
    double x =0, y=0, r = 2;
    int isexisted = 0;//子弹是否在场内
    int size = 1; //子弹的大小，1（最小）、2、3、4……（最大）

} bullet_enemy_small[256];
*/
struct bullet_player
{
    double x =0, y = 0, r = bullet_player_r;
    short isexisted = 0;
    //int number_hurt = bullet_hurt; //子弹伤害(已经有全局变量了)
    struct bullet_player* next_bullet = NULL;
}bullet_player[256];



class enemy_class //父类
{
private:
    
   

public:
    double life_max = 10000;//生命值上限
    double life = life_max;//剩下的生命值
    int r = r_enemy;//敌机半径
    //double x = screen_x/2.0, y = screen_y / 4;//敌机实时坐标
    //double frist_x = screen_x / 2.0,  frist_y = screen_y / 4; //敌机生成时的坐标
    enemy_class *next = NULL;//链表
    struct enemy  //小怪
    {

        //int number = generate_enemy_number;//这是第几个生成的敌机（用于链表删除）
        double frist_x = 0, frist_y = 0;//最开始生成的位置   //(其实应该是定值)
        int Hp = 少;//血量上限
        int name = 0; //敌机种类（暂时还没想好）
        COLORREF color = RED;//未来会改成图片地址
        short wait = 0; //敌机从生成到移动的时间段  (为0则生成)
        double v_x = 6, v_y = 6;//敌机速度
        double a_x = 0, a_y = 0;//敌机加速度
        int mark_move_line = move_null; //标记运动路线（默认符合加速运动）
        short isexisted = 0;//是否生成   可能直接delete就行了???
        short time_born = -1;//用于if判断 是否到了生成的时刻
        int time_exist = 0;//（非必要，敌机已生成的时间，用于控制运动轨迹）

        double x = 0, y = 0;//初始化的时候把frist里的值赋上
        int number_of_Hp = 少;//控制血量，其实应该是定值//好吧，是变量，毕竟要被覆盖     (可能是目前的？同样在初始化时赋值)

        //struct enemy* next_enemy = NULL;//只要类链表
    }name_enemy;

    //enemy_class()
    //{

    //};
    
    //enemy sample_enemy;//为了可以引用结构体里的变量（主要是为了frist_x与frist_y）

    struct bullet
    {
        //int number = 0;
        double enemy_x = 0, enemy_y = 0;;//子弹生成时的坐标原点坐标    值是frist_x 与frist_y，初始化的时候再赋值吧，写一个初始化函数
        double move_theta = 0;//运动角度（正常坐标系）
        double delta_theta = 0;//运动过程中角度改变量
        double v_absolute = 15;//慢  速度大小
        //double v_direction = 
        double frist_direction_about_orgin = 20;//发弹口离原点（敌机中心s）的距离
        double  r_created = 0;//生成时原点的坐标和生成点离该点的距离
        double r_bullet = 米弹; //子弹半径
        short isexist = 0;//是否绘制
        short isjudge = 0;//是否进行碰撞检测
        int move_x = 0;//x方向移动方式
        int move_y = 0;
        COLORREF color = BLUE;//子弹颜色
        //bullet* next_bullet = NULL;  //只用类链表
    }bullet_enemy;
    
    
    //tmd all_bullet不是类型名    
    
    //void move();//好像在move.h里面
    //void shoot();//不知道在哪

    int number_of_bullet = 1;
    enemy_class::bullet *frist_bullet;//便于引用弹幕数组，我总不能调用一次输入一次所有弹幕，执行下一个函数的时候的时候自动赋初值
    enemy_class::bullet*  bullet_vector(enemy_class::bullet frist_bullet ...)// 生成弹幕数组,返回数组首地址
    {//未完待续
        std::vector<enemy_class::bullet> all_bullet(3);//所有弹幕的数组  因为vector是给类，所以“只能”在一个函数里初始化
        va_list frist;
        va_start(frist, frist_bullet);
        for (int i = 0;0; i++)//结束条件没想好
        {
            //all_bullet[i] = va_arg(frist_bullet,enemy_class::bullet);

        }
        this->number_of_bullet = all_bullet.size();
        this->frist_bullet = &all_bullet[0];
        return this->frist_bullet;
    }
    
    int initialize()//初始化name_enemy信息
    {
        
        this->name_enemy.x = this->name_enemy.frist_x;
        this->name_enemy.y = this->name_enemy.frist_y;
        this->name_enemy.number_of_Hp = this->name_enemy.Hp;
        return 1;
    }
    void change_theta(double (*get_x) (double , enemy_class ), double (*get_y)(double , enemy_class))//更新子弹位置
    {
        this->bullet_enemy.move_theta = sqrt(pow(get_x(time_game,*this), 2) + pow(get_y(time_game,*this), 2));
    }
    void change_r_created(double (*get_x) (double, enemy_class), double (*get_y)(double, enemy_class))
    {
        this->bullet_enemy.r_created = atan(get_y(time_game, *this) / get_x(time_game, *this));
    }

};
#define bullet_of_enemy enemy_class::bullet
enemy_class::bullet* bullet_enemy_head = new bullet_of_enemy;//这三个不与boss绑定，作为单独的部分//（还是算了，类外不能赋值（初始化））(不对，这个不影响)
enemy_class::bullet* all_bullet_enemy = new bullet_of_enemy;
enemy_class::bullet* next_bullet_enemy = new bullet_of_enemy;

//typedef  enemy set_enemy;
typedef enemy_class::enemy set_enemy;

class boss : public enemy_class
{
     int number_card = 5;//符卡数 
     int number_uncard = 5;//非符数
    double* left_time = new double[number_card + number_uncard]; //符卡倒计时

};
boss alice;

class youkai : public enemy_class
{


};


/*

int delete_bullet(enemy_class::bullet *deleted_vector, enemy_class* head)//删除弹幕
//输入：被删除的弹幕在动态数组的哪个位置，被删除的弹幕所在的类
{
    //enemy_class* tem_head = new enemy_class;
    //assert(tem_head);
    bullet_of_enemy* tem_judged = new enemy_class::bullet;//临时，用于判断是否是被删除的子弹
    assert(tem_judged);
    tem_judged = deleted_vector;
    //在类中数组中删除此弹幕
    //while (head->next != NULL)
    for (int i = 1;i < head->number_of_bullet;i++)
    {
        
        if (head->frist_bullet[i] == tem_judged)
        {
            head->frist_bullet[i - 1] = ;//这是数组
            return 1;
        }
        if (tem_head == NULL)
        {
            break;
        }
    }
    //在数组中删除此弹幕 
    //这是数组
    return 0;
}

*/



void draw_bullet(double enemy_x, double enemy_y, bullet_of_enemy* bullet_druw, COLORREF color = BLUE)//绘制弹幕
{
    setorigin(enemy_x, enemy_y);//设置原点坐标
    setfillcolor(color);
    fillcircle(theta_to_x(bullet_druw->move_theta, bullet_druw->r_created)
        , theta_to_y(bullet_druw->move_theta, bullet_druw->r_created), 5);
    setorigin(0, 0);
}


class player {
private:
    
    


public:
    player(*player_information);
    static void shoot(double x_player, double y_player);
    static void move(double* x_player, double* y_player);
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
void player::shoot(double x_player, double y_player)//生成自机射出的子弹
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

void player::move(double* x_player, double* y_player)//自机移动
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

class bullet_class
{
public:
    static bullet_of_enemy* generated_bullet(double theta, double direction_orgin, COLORREF color, double v , double delta_theta);//生成并赋值
    void draw_bullet(bullet_of_enemy* bullet_druw, COLORREF color);//绘制弹幕
};

bullet_of_enemy* bullet_class::generated_bullet(double theta, double direction_orgin, COLORREF color, double v = 5, double delta_theta = 0)//生成并赋值
{
    bullet_of_enemy* bullet = new bullet_of_enemy;
    bullet->move_theta = theta;
    bullet->frist_direction_about_orgin = direction_orgin;
    bullet->r_created = direction_orgin;
    bullet->isexist = 1;
    bullet->color = color;
    bullet->v_absolute = v;
    bullet->delta_theta = delta_theta;
    return bullet;
}

void bullet_class::draw_bullet(bullet_of_enemy* bullet_druw, COLORREF color = BLUE)//生成并绘制弹幕
{
    setorigin(bullet_druw->enemy_x, bullet_druw->enemy_y);//设置原点坐标
    setfillcolor(color);
    fillcircle(theta_to_x(bullet_druw->move_theta, bullet_druw->r_created)
        , theta_to_y(bullet_druw->move_theta, bullet_druw->r_created), 5);
    setorigin(0, 0);
}