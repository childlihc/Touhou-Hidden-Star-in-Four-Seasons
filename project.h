#pragma once
#define _CRT_SECURE_NO_WARNINGS

/*��֪bug
* �����ڵ��Ի��ӵ�û���˺�
* ��Ҫͬʱ�����¼���Ҳ��Ҫͬʱ�����Ҽ��������Ի��ᾲֹ��shift��ʧ��
* ����ͨ����x���˳���Ϸ
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



//#include "c����.cpp"

#define pi 3.14159265
//#define  judge_time_second per_time_set[5] <= time_game_running && time_game_running <= per_time_set[6]
#define _v_x 6//�Ի��ƶ��ٶ�
#define _v_y 6//�Ի��ƶ��ٶ�

//�Ի����
enum { ���� = 0, ħ��ɳ, ����˿ };


//�л��˶��켣���
enum {
    move_null = 0, //  �켣���ϼ����˶�
    move_sin, // ���Ҳ�
    move_x_a, // x��a���ݣ�a�ǳ�����
    move_a_x  //a��x����
};
//�л��ӵ����



int r_enemy = 12;//�л��뾶���ݶ���
double length_move_x = 600, length_move_y = 560, tang_x = 50, tang_y = 20;//���Χ
int r_player = 5;//�ж���뾶
int x_player = tang_x + length_move_x / 2, y_player = length_move_y - (tang_y + 2 * r_player);//��ҳ�ʼλ��
int order_bullet = 1;//��n��������ӵ���
int v_bullet_player_y = 2 * r_player + 2 * r_enemy - 1;  //�Ի��ӵ����ٶ�
int bullet_player_r = 9;//�Ի��ӵ��뾶
int distance_player_bullet = r_player - bullet_player_r;//�Ի���Բ�����꣩�����һ�ŷ����ӵ�(������)�ľ���
double v_player_x = _v_x, v_player_y = _v_y;//�Ի��ƶ��ٶ�
double shift_v_player_x = v_player_x / 2, shift_v_player_y = v_player_y / 2;//����״̬���Ի��ƶ��ٶ�
int time_game_running = 0;//��Ϸ����ʱ��
int number_enemy = 0, number_enemy_max = 255;//���ɵ�nֻ�л������256
int number_bullet_enemy = 0;//�л��ĵ�n���ӵ�
//int number_bullet_player = 0;//�Ի��ĵ�n���ӵ�
int bullet_hurt = 25;//�Ի��ӵ����˺�
//constexpr int per_time_set[] = { 20,50,80,110,140,200,300,320,340,360,380};

//���ѷ�����int tem_per_time_set[][300];//�����ۼӣ���200�ӵ�250��  //��һ����һ���˶��켣Ϊ���Ҳ��ĵл�����50����ࣩ��

enum { �� = 100 };

int tem_number_second = 1;//���ڵڶ������ɵл�����

struct bullet_enemy
{
    double x =0, y=0, r = 2;
    int isexisted = 0;//�ӵ��Ƿ��ڳ���
    int size = 1; //�ӵ��Ĵ�С��1����С����2��3��4���������

} bullet_enemy_small[256];

struct bullet_player
{
    double x =0, y = 0, r = bullet_player_r;
    int isexisted = 0;
    //int number_hurt = bullet_hurt; //�ӵ��˺�(�Ѿ���ȫ�ֱ�����)
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
void player::shoot(int x_player, int y_player)//�����Ի�������ӵ�
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

void player::move(int* x_player, int* y_player)//�Ի��ƶ�
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