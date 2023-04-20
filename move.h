
#ifndef _move_h_
#define _move_h_
extern move;


namespace switch_class
{

	double xy_to_theta(double x, double y, double* theta_name);
	double theta_to_x(double theta, double r);
	double theta_to_y(double theta, double r);
};

double switch_class::xy_to_theta(double x, double y, double* theta_name)//直角坐标转极坐标,输入极角的变量名，返回极径
{
	*theta_name = atan2(y, x);
	return sqrt(pow(x, 2) + pow(y, 2));
}

double switch_class::theta_to_x(double theta, double r)
{
	return r * cos(theta);
}
double switch_class::theta_to_y(double theta, double r)//这里我懒得转换坐标系了
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

class move_function   //这里记录一切运动轨迹函数
	//直角坐标系
{
public:


};

class _graphics_all  //节省存储，直接只用代码绘制图案
{
private:
	 const int detha_y = 15;
	 POINT heart_point[22] = { {0,-100 - detha_y},//下顶点
			{38,-70 - detha_y},{(int)82.985,-27 - detha_y},
			{100,0 - detha_y},//x轴右顶点
			{110,26 - detha_y},{(int)113.9025,54 - detha_y}/*最右顶点*/,{110,(int)80.46 - detha_y},
			{100,100 - detha_y},//右上顶点
			{80,(int)116.958 - detha_y},{52,(int)123.665 - detha_y}/*最上顶点*/,{20,(int)116.56 - detha_y},
			{0,100 - detha_y},//y轴上顶点                   //对称
			{-20,(int)116.56 - detha_y},{-52,(int)123.665 - detha_y}/*最上顶点*/,{-80,(int)116.958 - detha_y},
			{-100,100 - detha_y},//左上顶点
			{-110,(int)80.46 - detha_y},{-(int)113.9025,54 - detha_y}/*最左顶点*/,{-110,26 - detha_y},
			{-100,0 - detha_y},//x轴左顶点
			{-(int)82.985,-27 - detha_y},{-38,-70 - detha_y},
		//结束
	};

public:
	 double heart(double x, double y, COLORREF color = GREEN)//返回判定点的半径
	{
		setorigin(x, y);
		setfillcolor(color);
		solidpolygon(heart_point, 22);
		setorigin(0, 0);
		return 0.9;//判断圆面积的半径
		//pow((x_ * x_ + y_ * y_ - 1),3) - pow(x,2) * pow(y,3) == 0
	}
};
class _graphics_all graphics_all;
namespace get_class
{
	double get_x(double time_exist, enemy_class::bullet who);
	double get_y(double time_exist, enemy_class::bullet who);
};

double get_class::get_x(double time_exist, enemy_class::bullet who)//算法相同，所以合并了
{
	switch (who.move_x)
	{
	case move::move_normal://匀速直线
		return who.r_created * cos(who.move_theta) * time_exist;
	}
}
double get_class::get_y(double time_exist, enemy_class::bullet who)
{
	switch (who.move_y)
	{
	case move::move_normal:
		return who.r_created * sin(who.move_theta) * time_exist;
	}


}



#endif // !_move_h_