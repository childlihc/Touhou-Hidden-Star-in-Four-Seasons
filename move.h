
extern move;



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

class move_function   //�����¼һ���˶��켣����
	//ֱ������ϵ
{
public:


};

class graphics_all  //��ʡ�洢��ֱ��ֻ�ô������ͼ��
{
	void heart(int x,int y)
	{
		setorigin(x, y);
		//pow((x_ * x_ + y_ * y_ - 1),3) - pow(x,2) * pow(y,3) == 0
	}
};

double get_x(double time_exist, enemy_class::bullet who)//�㷨��ͬ�����Ժϲ���
{
	switch (who.move_x)
	{
	case move::move_normal://����ֱ��
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



