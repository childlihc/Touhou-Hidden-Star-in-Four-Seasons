#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef _project_h_
#define _project_h_


/*��֪bug
* �����ڵ��Ի��ӵ�û���˺�
* ��Ҫͬʱ�����¼���Ҳ��Ҫͬʱ�����Ҽ��������Ի��ᾲֹ��shift��ʧ��
* ����ͨ����x���˳���Ϸ
* ��Ļ���Ͻǻ���һ������ʼ���ĵл�
* 
* 
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
//extern double switch_class::xy_to_theta(double x, double y, double* theta_name);
//extern double switch_class::theta_to_x(double theta, double r);
//double theta_to_y(double theta, double r);
extern int screen_x, screen_y;
using namespace switch_class;
//#include "c����.cpp"

#define pi 3.14159265
//#define  judge_time_second per_time_set[5] <= time_game_running && time_game_running <= per_time_set[6]
#define _v_x 6//�Ի��ƶ��ٶ�
#define _v_y 6//�Ի��ƶ��ٶ�

//�Ի����
enum { ���� = 0, ħ��ɳ, ����˿ };


//�л��˶��켣���
enum move{
    move_null = 0, //���˶������겻�ı䣩
    move_normal, //  �켣���������˶�
    move_function, //�˶��켣�����ú������ʽ������
    move_add, //�ȼ����˶�
    move_add_add, //������˶� 
    move_sin, // ���Ҳ�
    move_x_a, // x��a���ݣ�a�ǳ�����
    move_a_x  //a��x����
};
//�л��ӵ����



int r_enemy = 20;//�л��뾶���ݶ���
double length_move_x = 600, length_move_y = 560, tang_x = 50, tang_y = 20;//���Χ
int r_player = 5;//�ж���뾶
double x_player = tang_x + length_move_x / 2, y_player = length_move_y - (tang_y + 2 * r_player);//��ҳ�ʼλ��
int order_bullet = 1;//��n��������ӵ���
int v_bullet_player_y = 2 * r_player + 2 * r_enemy - 1;  //�Ի��ӵ����ٶ�
int bullet_player_r = 9;//�Ի��ӵ��뾶
double distance_player_bullet = r_player - bullet_player_r;//�Ի���Բ�����꣩�����һ�ŷ����ӵ�(������)�ľ���
double v_player_x = _v_x, v_player_y = _v_y;//�Ի��ƶ��ٶ�
double shift_v_player_x = v_player_x / 2, shift_v_player_y = v_player_y / 2;//����״̬���Ի��ƶ��ٶ�
int time_game_running = 0;//��Ϸ����ʱ��
int number_enemy = 0, number_enemy_max = 255;//���ɵ�nֻ�л������256
int number_bullet_enemy = 0;//�л��ĵ�n���ӵ�
//int number_bullet_player = 0;//�Ի��ĵ�n���ӵ�
int bullet_hurt = 25;//�Ի��ӵ����˺�
//constexpr int per_time_set[] = { 20,50,80,110,140,200,300,320,340,360,380};

//���ѷ�����int tem_per_time_set[][300];//�����ۼӣ���200�ӵ�250��  //��һ����һ���˶��켣Ϊ���Ҳ��ĵл�����50����ࣩ��

enum enemy_life { �� = 100 };
enum bullet_size { �׵� = 3, �۵� = 5 , ���� = 40 };

int tem_number_second = 1;//���ڵڶ������ɵл�����
/*
struct bullet_enemy
{
    double x =0, y=0, r = 2;
    int isexisted = 0;//�ӵ��Ƿ��ڳ���
    int size = 1; //�ӵ��Ĵ�С��1����С����2��3��4���������

} bullet_enemy_small[256];
*/
struct bullet_player
{
    double x =0, y = 0, r = bullet_player_r;
    short isexisted = 0;
    //int number_hurt = bullet_hurt; //�ӵ��˺�(�Ѿ���ȫ�ֱ�����)
    struct bullet_player* next_bullet = NULL;
}bullet_player[256];



class enemy_class //����
{
private:
    
   

public:
    double life_max = 10000;//����ֵ����
    double life = life_max;//ʣ�µ�����ֵ
    int r = r_enemy;//�л��뾶
    //double x = screen_x/2.0, y = screen_y / 4;//�л�ʵʱ����
    //double frist_x = screen_x / 2.0,  frist_y = screen_y / 4; //�л�����ʱ������
    enemy_class *next = NULL;//����
    struct enemy  //С��
    {

        //int number = generate_enemy_number;//���ǵڼ������ɵĵл�����������ɾ����
        double frist_x = 0, frist_y = 0;//�ʼ���ɵ�λ��   //(��ʵӦ���Ƕ�ֵ)
        int Hp = ��;//Ѫ������
        int name = 0; //�л����ࣨ��ʱ��û��ã�
        COLORREF color = RED;//δ����ĳ�ͼƬ��ַ
        short wait = 0; //�л������ɵ��ƶ���ʱ���  (Ϊ0������)
        double v_x = 6, v_y = 6;//�л��ٶ�
        double a_x = 0, a_y = 0;//�л����ٶ�
        int move_line_x = move_null; //����˶�·�ߣ�Ĭ�Ϸ��ϼ����˶���
        int move_line_y = move_normal;
        short isexisted = 0;//�Ƿ�����   ����ֱ��delete������???
        short time_born = -1;//����if�ж� �Ƿ������ɵ�ʱ��
        int time_exist = 0;//���Ǳ�Ҫ���л������ɵ�ʱ�䣬���ڿ����˶��켣��

        double x = 0, y = 0;//��ʼ����ʱ���frist���ֵ����
        int number_of_Hp = ��;//����Ѫ������ʵӦ���Ƕ�ֵ//�ðɣ��Ǳ������Ͼ�Ҫ������     (������Ŀǰ�ģ�ͬ���ڳ�ʼ��ʱ��ֵ)

        //struct enemy* next_enemy = NULL;//ֻҪ������
    }name_enemy;

    //enemy_class()
    //{

    //};
    
    //enemy sample_enemy;//Ϊ�˿������ýṹ����ı�������Ҫ��Ϊ��frist_x��frist_y��

    struct bullet
    {
        //int number = 0;
        double enemy_x = 0, enemy_y = 0;;//�ӵ�����ʱ������ԭ������    ֵ��frist_x ��frist_y����ʼ����ʱ���ٸ�ֵ�ɣ�дһ����ʼ������
        double move_theta = 0;//�˶��Ƕȣ���������ϵ��
        double delta_theta = 0;//�˶������нǶȸı���
        double v_absolute = 15;//��  �ٶȴ�С
        //double v_direction = 
        double frist_direction_about_orgin = 20;//��������ԭ�㣨�л�����s���ľ���
        double  r_created = 0;//����ʱԭ�����������ɵ���õ�ľ���
        double r_bullet = �׵�; //�ӵ��뾶
        short isexist = 0;//�Ƿ����
        short isjudge = 0;//�Ƿ������ײ���
        int move_x = 0;//x�����ƶ���ʽ
        int move_y = 0;
        COLORREF color = BLUE;//�ӵ���ɫ
        //bullet* next_bullet = NULL;  //ֻ��������
    }bullet_enemy;
    
    
    //tmd all_bullet����������    
    
    //void move();//������move.h����
    //void shoot();//��֪������

    int number_of_bullet = 1;
    enemy_class::bullet *frist_bullet;//�������õ�Ļ���飬���ܲ��ܵ���һ������һ�����е�Ļ��ִ����һ��������ʱ���ʱ���Զ�����ֵ
    enemy_class::bullet*  bullet_vector(enemy_class::bullet frist_bullet ...)// ���ɵ�Ļ����,���������׵�ַ
    {//δ�����
        std::vector<enemy_class::bullet> all_bullet(3);//���е�Ļ������  ��Ϊvector�Ǹ��࣬���ԡ�ֻ�ܡ���һ���������ʼ��
        va_list frist;
        va_start(frist, frist_bullet);
        for (int i = 0;0; i++)//��������û���
        {
            //all_bullet[i] = va_arg(frist_bullet,enemy_class::bullet);

        }
        this->number_of_bullet = all_bullet.size();
        this->frist_bullet = &all_bullet[0];
        return this->frist_bullet;
    }
    
    int initialize()//��ʼ��name_enemy��Ϣ
    {
        
        this->name_enemy.x = this->name_enemy.frist_x;
        this->name_enemy.y = this->name_enemy.frist_y;
        this->name_enemy.number_of_Hp = this->name_enemy.Hp;
        return 1;
    }
    void change_theta(double (*get_x) (double , enemy_class ), double (*get_y)(double , enemy_class))//�����ӵ�λ��
    {
        this->bullet_enemy.move_theta = sqrt(pow(get_x(time_game,*this), 2) + pow(get_y(time_game,*this), 2));
    }
    void change_r_created(double (*get_x) (double, enemy_class), double (*get_y)(double, enemy_class))
    {
        this->bullet_enemy.r_created = atan(get_y(time_game, *this) / get_x(time_game, *this));
    }

};
#define bullet_of_enemy enemy_class::bullet
enemy_class::bullet* bullet_enemy_head = new bullet_of_enemy;//����������boss�󶨣���Ϊ�����Ĳ���//���������ˣ����ⲻ�ܸ�ֵ����ʼ������(���ԣ������Ӱ��)
enemy_class::bullet* all_bullet_enemy = new bullet_of_enemy;
enemy_class::bullet* next_bullet_enemy = new bullet_of_enemy;

//typedef  enemy set_enemy;
typedef enemy_class::enemy set_enemy;

class boss : public enemy_class
{
     int number_card = 5;//������ 
     int number_uncard = 5;//�Ƿ���
    double* left_time = new double[number_card + number_uncard]; //��������ʱ

};
boss alice;

class youkai : public enemy_class
{


};


/*

int delete_bullet(enemy_class::bullet *deleted_vector, enemy_class* head)//ɾ����Ļ
//���룺��ɾ���ĵ�Ļ�ڶ�̬������ĸ�λ�ã���ɾ���ĵ�Ļ���ڵ���
{
    //enemy_class* tem_head = new enemy_class;
    //assert(tem_head);
    bullet_of_enemy* tem_judged = new enemy_class::bullet;//��ʱ�������ж��Ƿ��Ǳ�ɾ�����ӵ�
    assert(tem_judged);
    tem_judged = deleted_vector;
    //������������ɾ���˵�Ļ
    //while (head->next != NULL)
    for (int i = 1;i < head->number_of_bullet;i++)
    {
        
        if (head->frist_bullet[i] == tem_judged)
        {
            head->frist_bullet[i - 1] = ;//��������
            return 1;
        }
        if (tem_head == NULL)
        {
            break;
        }
    }
    //��������ɾ���˵�Ļ 
    //��������
    return 0;
}

*/



void draw_bullet(double enemy_x, double enemy_y, bullet_of_enemy* bullet_druw, COLORREF color = BLUE)//���Ƶ�Ļ
{
    setorigin(enemy_x, enemy_y);//����ԭ������
    setfillcolor(color);
    fillcircle(switch_class::theta_to_x(bullet_druw->move_theta, bullet_druw->r_created)
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
void test_1(player_information & reimu,int x,int y)//�粻�ı�ṹ�����ݣ����Լ���const
{
    reimu.v_x;
    reimu.x;
    

}
*/
struct player_information //��ҵ���Ϣ
{
    int name;
    int x = x_player, y = y_player;
    int v_x = v_player_x, v_y = v_player_y;
    int bullet_hurt;

};
void player::shoot(double x_player, double y_player)//�����Ի�������ӵ�
{
    for (int i = 0; i < 2; i++)
    {
        bullet_player[order_bullet].isexisted = 1;
        bullet_player[order_bullet].y = (y_player + distance_player_bullet);
        bullet_player[order_bullet].x = x_player + pow(-1, i) * (bullet_player_r + 2);
        order_bullet++;
    }
    if (order_bullet > 256 - 2)//�������ڴ�����ɣ��������Ļ��ӵ�����256�ŵ�ʱ���Ի����ӵ�������ʧ
    {
        order_bullet = 1;
    }
}

void player::move(double* x_player, double* y_player)//�Ի��ƶ�
{
    //(����)int inter_move = _getch();


    if (GetKeyState(38) < 0)//��        
    {
        *y_player -= v_player_y;
    }

    if (GetKeyState(40) < 0)//��          
    {
        *y_player += v_player_y;
    }


    if (GetKeyState(37) < 0)//��
    {
        *x_player -= v_player_x;
    }

    if (GetKeyState(39) < 0)//��           
    {
        *x_player += v_player_x;
    }

    //��ֹ����
    if (*x_player - r_player < tang_x)     //��   ��
    {
        *x_player = tang_x + r_player;
    }
    if (*x_player + r_player > tang_x + length_move_x)
    {
        *x_player = tang_x + length_move_x - r_player;
    }
    if (*y_player - r_player < tang_y)     //��   ��
    {
        *y_player = tang_y + r_player;
    }
    if (*y_player + r_player > tang_y + length_move_y)
    {
        *y_player = tang_y + length_move_y - r_player;
    }
}
void player::boom_player()//��B
{


}

class bullet_class
{
public:
    static bullet_of_enemy* generated_bullet(double theta, double direction_orgin, COLORREF color, double v , double delta_theta);//���ɲ���ֵ
    void draw_bullet(bullet_of_enemy* bullet_druw, COLORREF color);//���Ƶ�Ļ
};

bullet_of_enemy* bullet_class::generated_bullet(double theta, double direction_orgin, COLORREF color, double v = 5, double delta_theta = 0)//���ɲ���ֵ
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

void bullet_class::draw_bullet(bullet_of_enemy* bullet_druw, COLORREF color = BLUE)//���ɲ����Ƶ�Ļ
{
    setorigin(bullet_druw->enemy_x, bullet_druw->enemy_y);//����ԭ������
    setfillcolor(color);
    fillcircle(switch_class::theta_to_x(bullet_druw->move_theta, bullet_druw->r_created)
        , switch_class::theta_to_y(bullet_druw->move_theta, bullet_druw->r_created), 5);
    setorigin(0, 0);
}

bool operator== (enemy_class frist, enemy_class second)
{
    return (frist.frist_bullet == second.frist_bullet && frist.name_enemy.frist_x == second.name_enemy.frist_x);
}

#endif // !_project_h_