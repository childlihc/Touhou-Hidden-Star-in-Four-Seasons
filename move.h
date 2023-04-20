#pragma once
#include "project.h"
#ifndef _move_h_
#define _move_h_
extern move;

/*
namespace switch_class
{
	double xy_to_theta(double x, double y, double* theta_name);
	double theta_to_x(double theta, double r);
	double theta_to_y(double theta, double r);
};
*/
double xy_to_theta(double x, double y, double* theta_name)//ֱ������ת������,���뼫�ǵı����������ؼ���
{
	*theta_name = atan2(y, x);
	return sqrt(pow(x, 2) + pow(y, 2));
}

double theta_to_x(double theta, double r)
{
	return r * cos(theta);
}
double theta_to_y(double theta, double r)//����������ת������ϵ��
{
	return -(r * sin(theta));
}



namespace move_class
{
	int normal(enemy_class *enemy,char changed_direction)
	{
		switch (changed_direction)
		{
		case 'x':
			enemy->name_enemy.x += enemy->name_enemy.v_x;
			enemy->name_enemy.v_x += enemy->name_enemy.a_x;
			break;
		case 'y':
			enemy->name_enemy.y += enemy->name_enemy.v_y;
			enemy->name_enemy.v_y += enemy->name_enemy.a_y;
			break;
		default:
			return 0;
		}
		return 1;
	}
};

class move_function   //�����¼һ���˶��켣����
	//ֱ������ϵ
{
public:


};

class _graphics_all  //��ʡ�洢��ֱ��ֻ�ô������ͼ��
{
private:
	 const int detha_y = 15;
	 POINT heart_point[22] = { {0,-100 - detha_y},//�¶���
			{38,-70 - detha_y},{(int)82.985,-27 - detha_y},
			{100,0 - detha_y},//x���Ҷ���
			{110,26 - detha_y},{(int)113.9025,54 - detha_y}/*���Ҷ���*/,{110,(int)80.46 - detha_y},
			{100,100 - detha_y},//���϶���
			{80,(int)116.958 - detha_y},{52,(int)123.665 - detha_y}/*���϶���*/,{20,(int)116.56 - detha_y},
			{0,100 - detha_y},//y���϶���                   //�Գ�
			{-20,(int)116.56 - detha_y},{-52,(int)123.665 - detha_y}/*���϶���*/,{-80,(int)116.958 - detha_y},
			{-100,100 - detha_y},//���϶���
			{-110,(int)80.46 - detha_y},{-(int)113.9025,54 - detha_y}/*���󶥵�*/,{-110,26 - detha_y},
			{-100,0 - detha_y},//x���󶥵�
			{-(int)82.985,-27 - detha_y},{-38,-70 - detha_y},
		//����
	};

public:
	 double heart(double x, double y, COLORREF color = GREEN)//�����ж���İ뾶
	{
		setorigin(x, y);
		setfillcolor(color);
		solidpolygon(heart_point, 22);
		setorigin(0, 0);
		return 0.9;//�ж�Բ����İ뾶
		//pow((x_ * x_ + y_ * y_ - 1),3) - pow(x,2) * pow(y,3) == 0
	}
};
class _graphics_all graphics_all;
namespace get_class
{
	double get_x(double time_exist, enemy_class::bullet who, double sth);
	double get_y(double time_exist, enemy_class::bullet who, double sth);
};

double get_class::get_x(double time_exist, enemy_class::bullet who,double sth = 0)//�㷨��ͬ�����Ժϲ���
//sth�����Ŀǰ����֪��Ӧ�ô���ʲô
{
	switch (who.move_x)
	{
	case move::move_normal://����ֱ��
		return who.r_created * cos(who.move_theta) * time_exist;
		break;
	case move::move_step_by_step:
		return 0.0;
		break;

	}
}
double get_class::get_y(double time_exist, enemy_class::bullet who,double sth = 0)
{
	switch (who.move_y)
	{
	case move::move_normal:
		return who.r_created * sin(who.move_theta) * time_exist;
	}


}



#endif // !_move_h_