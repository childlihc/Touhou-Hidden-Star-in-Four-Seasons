
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






double get_x(double time_exist, enemy_class::bullet who)//�㷨��ͬ�����Ժϲ���
{
	switch (who.move_x)
	{
	case 0://����ֱ��
		return who.r_created * cos(who.move_theta) * time_exist;
	}
}
double get_y(double time_exist, enemy_class::bullet who)
{
	switch (who.move_y)
	{
	case 0:
		return who.r_created * sin(who.move_theta) * time_exist;
	}


}



