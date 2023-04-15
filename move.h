
extern move;



double xy_to_theta(double x, double y, double* theta_name)//直角坐标转极坐标,输入极角的变量名，返回极径
{
	*theta_name = atan2(y, x);
	return sqrt(pow(x, 2) + pow(y, 2));
}

double theta_to_x(double theta, double r)
{
	return r * cos(theta);
}
double theta_to_y(double theta, double r)//这里我懒得转换坐标系了
{
	return -(r * sin(theta));
}



class move_class
{
public:
	static int normal(enemy_class *enemy,char changed_direction)
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
}move_class;

class move_function   //这里记录一切运动轨迹函数
	//直角坐标系
{
public:


};

class graphics_all  //节省存储，直接只用代码绘制图案
{
	void heart(int x,int y)
	{
		setorigin(x, y);
		//pow((x_ * x_ + y_ * y_ - 1),3) - pow(x,2) * pow(y,3) == 0
	}
};

double get_x(double time_exist, enemy_class::bullet who)//算法相同，所以合并了
{
	switch (who.move_x)
	{
	case move::move_normal://匀速直线
		return who.r_created * cos(who.move_theta) * time_exist;
	}
}
double get_y(double time_exist, enemy_class::bullet who)
{
	switch (who.move_y)
	{
	case move::move_normal:
		return who.r_created * sin(who.move_theta) * time_exist;
	}


}



