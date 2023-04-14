
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






double get_x(double time_exist, enemy_class::bullet who)//算法相同，所以合并了
{
	switch (who.move_x)
	{
	case 0://匀速直线
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



