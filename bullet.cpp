#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <math.h>
#include <time.h>
#include <assert.h>

#define Pi 3.14159265358979
struct test
{
	int number = 1;
	int age = 12;
	int color = 1;
	test* next_test = NULL;

};
test* tem_next;
test* test_head = new test;
test* all_test = new test;


void generate_enemy(int color[], int which[], int number_judged) //改变颜色，后面三个分别是设置要显示的颜色、设置改变颜色的条件（第几个生成的要改变成什么样的颜色，是一一对应的）、被判断是否要改颜色的敌机是第number_judjed个生成的
//还是设置一个全局变量的数组吧。
{
	int number = sizeof  which / sizeof which[0];//判断条件的总个数
	printf("???%d", number);
	for (int i = 0; i < number; i++)
	{
		if (number_judged == which[i])
		{
			//frist_test->color = color[i];
		}
	}
}

class enemy_class
{
public:
	double x, y;//敌机实时坐标
	double frist_x, frist_y; //敌机生成时的坐标
	struct bullet 
	{
		//int number = 0;
		double move_theta = 0;//运动角度（正常坐标系）
		double delta_theta = 0;//运动过程中角度改变量
		//double x = -1, y = -1;//如果子弹“必须”要用直角坐标系表示，就用这个，否则不用//舍弃这个，用enemy的运动函数
		double v_absolute = 15.0 / 3;//慢  速度大小
		//double v_direction = 
		double frist_direction_about_orgin = 20;//发弹口离原点（敌机中心s）的距离
		double  r_created = 0;//生成时原点的坐标和生成点离该店的距离
		int isexist = 0;//是否绘制
		bullet* next_bullet = NULL;
		COLORREF color = BLUE;
	}bullet_enemy;

};

#define bullet_of_enemy enemy_class::bullet
enemy_class::bullet *bullet_enemy_head = new bullet_of_enemy;
enemy_class::bullet* all_bullet_enemy = new bullet_of_enemy;
enemy_class::bullet* next_bullet_enemy = new bullet_of_enemy;


double xy_to_theta(double x,double y,double *theta_name)//直角坐标转极坐标,输入极角的变量名，返回极径
{
	*theta_name = atan2(y , x);
	return sqrt(pow(x, 2) + pow(y, 2));
}

double theta_to_x(double theta,double r)
{
	return r  * cos(theta);
}
double theta_to_y(double theta,double r)//这里我懒得转换坐标系了
{
	return -(r * sin(theta));
}


void draw_bullet(double x,double y,bullet_of_enemy * bullet_druw,COLORREF color = BLUE)//生成并绘制弹幕
{
	setorigin(x, y);//设置原点坐标
	setfillcolor(color);
	
	/*
	frist_bullet_enemy->move_theta = theta;//i;
	frist_bullet_enemy->frist_direction_about_orgin = l;//2 * r_boss;
	frist_bullet_enemy->r_created = frist_bullet_enemy->frist_direction_about_orgin;
	*/
	fillcircle(theta_to_x(bullet_druw->move_theta, bullet_druw->r_created)
		, theta_to_y(bullet_druw->move_theta, bullet_druw->r_created), 5);
	setorigin(0, 0);
}



int delete_bullet(bullet_of_enemy *bullet_deleted,bullet_of_enemy* head)
{
	bullet_of_enemy* tem_head = new bullet_of_enemy;
	bullet_of_enemy* tem_judged = new bullet_of_enemy;//临时，用于判断是否是被删除的子弹
	assert(tem_head);
	*tem_head = *head;//复制一下所有子弹
	tem_judged = bullet_deleted;
	assert(tem_judged);
	if (tem_head == NULL || tem_judged == NULL)
	{
		outtextxy(500, 300, L"hhhh");
		FlushBatchDraw();
		_getch();
	}
	while (head->next_bullet != NULL)
	{
		tem_judged = tem_head;
		if (tem_head->next_bullet == bullet_deleted)
		{
			tem_head->next_bullet = bullet_deleted->next_bullet;
			//head = 
			/*outtextxy(500, 300, L"hhhh");
			FlushBatchDraw();
			_getch();*/
			//delete(tem_head);
			

			return 1;
		}
		
		tem_head = tem_head->next_bullet;
		if (tem_head == NULL)
		{
			break;
		}
	}
	return 0;
}
bullet_of_enemy* generated_bullet(double theta,double direction_orgin,COLORREF color, double v = 5,double delta_theta = 0)//生成并赋值
{
	bullet_of_enemy *bullet = new bullet_of_enemy;
	bullet->move_theta = theta;
	bullet->frist_direction_about_orgin = direction_orgin;
	bullet->r_created = direction_orgin;
	bullet->isexist = 1;
	bullet->color = color;
	bullet->v_absolute = v;
	bullet->delta_theta = delta_theta;
	return bullet;
}

int main()

{
	srand(time(0));
	int boss_x = 500, boss_y = 300, r_boss = 20;
	bullet_enemy_head->frist_direction_about_orgin = 2 * r_boss;//链表
	bullet_enemy_head->r_created = bullet_enemy_head->frist_direction_about_orgin;
	bullet_enemy_head->move_theta = 0;
	bullet_enemy_head->v_absolute = 0;//防止被删除（虽然没什么大用）
	all_bullet_enemy = bullet_enemy_head;
	initgraph(1000, 600);
	setfillcolor(RED);
	fillcircle(boss_x, boss_y, r_boss);
	//_getch();
	//设计弹幕
	enemy_class *alice = new enemy_class;
	alice->x = boss_x;
	alice->y = boss_y;
	BeginBatchDraw();
	cleardevice();
	int time_game = 0;
	double theta_change = 0;
	double theta_change_2 = 2;
	int tem_theta_change_1 = 1; 
	int tem_geneater_enemy;
	bullet_of_enemy* tem_head;
	unsigned int number_of_bullet = 1;
	while (1)//动画主体
	{
		
		//生成
		tem_geneater_enemy = time_game % 5;
		switch(tem_geneater_enemy)
		{
		case 2:
			
			//for (double i = 0; i < 6; i += 0.75)
			for (double i = 0; i < 12; i ++)
			{
				next_bullet_enemy = generated_bullet((i * (Pi / 6) ) + theta_change *(Pi / theta_change_2),r_boss,BLUE);
				/*
				if (0)
				{	new bullet_of_enemy;
				//next_bullet_enemy->number = number_of_bullet;
				//next_bullet_enemy->move_theta = (i * (Pi / 6) / * / (1.0 / 3)* /) + theta_change *  /* * (theta_change + i)*/ /* * 10 * i* / ((Pi /* + theta_change* /) / theta_change_2/*不定值*//*4*//*2*/ /* + theta_change */ /* + 12 * (((int)theta_change % 16) * (Pi / 8))* /);
				next_bullet_enemy->frist_direction_about_orgin = r_boss;
				next_bullet_enemy->isexist = 1;
				}*/
				all_bullet_enemy->next_bullet = next_bullet_enemy;
				all_bullet_enemy = next_bullet_enemy;
				number_of_bullet++;
			}
			theta_change++;
			//theta_change_2 = 6.0 * tan(theta_change) ;// *sin(theta_change);
			theta_change_2 = 18;
			/*
			switch (rand() % 4)
			{
			case 1:
				theta_change_2 = 6;
				break;
			case 2:
				theta_change_2 = 18;
				break;
			case 3:
				theta_change_2 = 12;
				break;
			}
			*/
			//theta_change += 24 * sin(theta_change_2)  * (Pi / 24);
			//theta_change_2 *= 2;

			break;
		case 3:
			if (time_game > 80)
			{
				for (double i = 0; i < 9; i++)
				{
					next_bullet_enemy = generated_bullet((Pi / 9) + (i + 1) * (2 * Pi / 8) - (tem_theta_change_1 * Pi / 32) , r_boss, RED, 10);
					all_bullet_enemy->next_bullet = next_bullet_enemy;
					all_bullet_enemy = next_bullet_enemy;
					number_of_bullet++;
					tem_theta_change_1++;
				}
			}
			/*待修正
			if (time_game > 20)//* 30)
			{
				
				double tem_bullet_x[30] , tem_bullet_theta[30];
				for (int i = 0; i < 30; i++)
				{
					tem_bullet_x[i] = (rand() % ((int)alice->x - 100) + (int)alice->x + 100) / 10.0;
					do {
						tem_bullet_theta[i] = (sin(rand()) * Pi / 24) + (Pi / 2);
					} while (!tem_bullet_theta[i]);//防止为0
					next_bullet_enemy = new bullet_of_enemy;
					next_bullet_enemy->frist_direction_about_orgin = tem_bullet_x[i] / sin(tem_bullet_theta[i]);
					next_bullet_enemy->r_created = next_bullet_enemy->frist_direction_about_orgin;
					next_bullet_enemy->move_theta = atan(sqrt((alice->y - (next_bullet_enemy->r_created * sin(tem_bullet_theta[i])))));
					next_bullet_enemy->color = GREEN;
					next_bullet_enemy->v_absolute *= 3;
					next_bullet_enemy->isexist = 1;
					all_bullet_enemy->next_bullet = next_bullet_enemy;
					all_bullet_enemy = next_bullet_enemy;
					number_of_bullet++;
				}
				
			}
			*/
			if (time_game > 40 && time_game < 80)//* 30)
			{
				
				for (double i = 0; i < 8; i++)
				{
					next_bullet_enemy = generated_bullet((Pi / 9) + (i + 1) * (2 * Pi / 8), r_boss, RED, 10);
					all_bullet_enemy->next_bullet = next_bullet_enemy;
					all_bullet_enemy = next_bullet_enemy;
					number_of_bullet++;
				}

			}
			break;
		}
		all_bullet_enemy->next_bullet = NULL;
		//改值（距离原点的距离）
		
		//判断是否越界
		tem_head = bullet_enemy_head;
		while (1)
		{
			
				tem_head->r_created += tem_head->v_absolute;
			
			//  尚未完成
			
			/*if (tem_head != NULL && ((theta_to_x(alice->x + tem_head->frist_direction_about_orgin, 0) > 600 || theta_to_x(alice->x - tem_head->frist_direction_about_orgin, 0)< 0) &&
				(theta_to_y(alice->y + tem_head->frist_direction_about_orgin,0) > 400 || theta_to_y (alice->y - tem_head->frist_direction_about_orgin,0) < 0)))
			*/

			//if (tem_head != NULL && ((theta_to_x(tem_head->move_theta,alice->x +  tem_head->r_created) > 400 || theta_to_x(tem_head->move_theta, alice->x+ tem_head->r_created) < -400) &&
			//	(theta_to_y(tem_head->move_theta,alice->y + tem_head->r_created) > 400 || theta_to_y(tem_head->move_theta, alice->y + tem_head->r_created) < -400)))
			if (tem_head != NULL)
			{
				if (((theta_to_x(tem_head->move_theta, tem_head->r_created) > alice->x - 50 || theta_to_x(tem_head->move_theta, tem_head->r_created) < alice->x - 950) ||
					(theta_to_y(tem_head->move_theta, tem_head->r_created) > alice->y - 50 || theta_to_y(tem_head->move_theta, tem_head->r_created) < alice->y - 550)))//我不知道100和500是怎么来的，但是它们确实有用，可以修改它们的值并查看效果，以此来推断过程
					{
						delete_bullet(tem_head, bullet_enemy_head);
						tem_head = tem_head->next_bullet;//我是大傻逼
						//outtextxy(20, 20, L"20");
					}
			}
			/*else
			{
				if ((tem_head->x > alice->x - 50 || tem_head->x < -950) && (tem_head->y > alice->y - 50 || tem_head->y < alice->y - 550))
				{
					delete_bullet(tem_head, bullet_enemy_head);
					tem_head = tem_head->next_bullet;
				}
			}
			*/
			tem_head = tem_head->next_bullet;
			if (tem_head == NULL)
			{
				cleardevice();
				break;
			}

		}
		//bullet_enemy_head = tem_head;
		delete(tem_head);
		
		//绘制
		
		tem_head = bullet_enemy_head;
		//cleardevice();
		while (1)
		{
			
			setfillcolor(RED);
			fillcircle(boss_x, boss_y, r_boss);
			
			if (tem_head->isexist == 1)
			{
				//setorigin(alice->x, alice->y);
				//if (tem_head->next_bullet != NULL && ((alice->x + tem_head->next_bullet->frist_direction_about_orgin > 600 || alice->x - tem_head->next_bullet->frist_direction_about_orgin < 0) &&
				//	(alice->y + tem_head->next_bullet->frist_direction_about_orgin > 400 || alice->y - tem_head->next_bullet->frist_direction_about_orgin < 0)))
				//if (tem_head != NULL && ((theta_to_x(tem_head->move_theta,  tem_head->r_created) > 950 || theta_to_x(tem_head->move_theta, alice->x + tem_head->frist_direction_about_orgin) < -700) ||
				//	(theta_to_y(tem_head->move_theta,  tem_head->r_created) > 400 || theta_to_y(tem_head->move_theta,alice->y + tem_head->frist_direction_about_orgin) < -550)))
				if (tem_head != NULL && ((theta_to_x(tem_head->move_theta, tem_head->r_created) > alice->x - 50 || theta_to_x(tem_head->move_theta, tem_head->r_created) < alice->x - 950)||
					(theta_to_y(tem_head->move_theta, tem_head->r_created) > alice->y - 50 || theta_to_y(tem_head->move_theta,tem_head->r_created) < alice->y - 550)))//我不知道100和500是怎么来的，但是它们确实有用，可以修改它们的值并查看效果，以此来推断过程
				{
					//tem_head->isexist = 0;
					draw_bullet(boss_x, boss_y, tem_head, GREEN);
					
				}
				else if(tem_head != NULL)
				{
					draw_bullet(boss_x, boss_y, tem_head,tem_head->color);
				}/*
				//!!!
				if (tem_head != NULL && ((theta_to_x(tem_head->move_theta,2 * r_boss + tem_head->frist_direction_about_orgin) > 800 || theta_to_x(tem_head->move_theta, 2 * r_boss + tem_head->frist_direction_about_orgin) < -800)))
				{
					//draw_bullet(boss_x, boss_y, tem_head, BLACK);
				}
				if (tem_head != NULL && ((theta_to_x(tem_head->move_theta, 2 * r_boss + tem_head->frist_direction_about_orgin) > 800 || theta_to_x(tem_head->move_theta, 2 * r_boss + tem_head->frist_direction_about_orgin) < -800) &&
					(theta_to_y(tem_head->move_theta, alice->y + tem_head->frist_direction_about_orgin) > 400 || theta_to_y(tem_head->move_theta, alice->y + tem_head->frist_direction_about_orgin) < -400)))
				{
					//tem_head->isexist = 0;
					//draw_bullet(boss_x, boss_y, tem_head, RED);
				}
				*/
				//FlushBatchDraw();
				//Sleep(50);
			}
			
			//FlushBatchDraw();
			
			tem_head = tem_head->next_bullet;
			if (tem_head == NULL)
			{
				break;
			}
		}
		delete (tem_head);
		time_game++;
		FlushBatchDraw();
		Sleep(1000.0/60);
	}


	/*链表
	while (1)//创建链表
	{
		//test* frist_test = new test;//(struct test*)malloc(sizeof test);(md，重定义了居然不报错)
		test* true_frist_test = frist_test;
		for (int i = 0; i < 6; i++)
		{

			frist_test->age = i * 10;
			tem_next = new test;//(struct test*)malloc(sizeof test);
			frist_test->next_test = tem_next;
			frist_test = tem_next;
			
			//free(tem_next);//加上这行代码有随机效果（其实在于frist_test = tem_next）
		}
		
		//frist_test = NULL;
		//frist_test->next_test = NULL;
		////delete(tem_next);
		//不知道为什么 ，true_frist_test 才是链表
		
		*tem_frist_test = *true_frist_test;//有没有星号似乎没有影响
		//frist_test = true_frist_test;//生成循环链表（大概）
		while (1)//验证链表
		{
			if (tem_frist_test->next_test == NULL)//内存溢出   //去掉->next就会多输出一个，不知道为什么
			//if ()
			{
				break;
			}
			printf("%d\n", tem_frist_test->age);

			tem_frist_test = tem_frist_test->next_test;
			
		}
		break;
	}
	
	int judge_number[7] = { 10,20,30,40,50 };
	int color[7] = { 2,3,2,2,4 };
	
	printf(";;;");
		generate_enemy(color,  judge_number, frist_test->number);
		
		*/
	

	
	
	/*
	char a = _getch();
	int b = _getch();
	printf("%d", b);
	*/
	return 0;
}


/*什么鸡巴玩意，看不懂
int tem_theta_add = 0;
	bullet_of_enemy* bullet_alice = new bullet_of_enemy;

	while (1)//第一波弹幕
	{

		setorigin(0, 0);
		setfillcolor(RED);
		fillcircle(alice->x, alice->y, r_boss);

		//for (int i = 0;i <19;i++)

		true_frist_bullet_enemy = bullet_alice;
		for (int i = 0; i < 18; i++)
		{//包装成函数

			bullet_alice->move_theta = i;
			bullet_alice->r_created = 2 * r_boss;
			draw_bullet(alice->x, alice->y, bullet_alice->move_theta + tem_theta_add, bullet_alice->r_created);
			bullet_of_enemy* tem_bullet_alice = new bullet_of_enemy;
			bullet_alice->next_bullet = tem_bullet_alice;
			bullet_alice = tem_bullet_alice;
			Sleep(50);
			FlushBatchDraw();
		}

		bullet_alice->next_bullet = NULL;//可能不会爆内存
		//Sleep(1000);
		break;
	}

	while (1)
	{
		bullet_of_enemy* tem_bullet = new bullet_of_enemy;
		bullet_alice->next_bullet = tem_bullet;
		tem_theta_add++;
		while (1)
		{

			setorigin(0, 0);
			setfillcolor(RED);
			fillcircle(alice->x, alice->y, r_boss);

			//for (int i = 0;i <19;i++)

			true_frist_bullet_enemy = bullet_alice;
			for (int i = 0; i < 18; i++)
			{//包装成函数

				tem_bullet->move_theta = i;
				tem_bullet->r_created = 2 * r_boss;
				draw_bullet(alice->x, alice->y, tem_bullet->move_theta + tem_theta_add, tem_bullet->r_created);
				bullet_of_enemy* tem_bullet_alice= new bullet_of_enemy;
				tem_bullet->next_bullet = tem_bullet_alice;
				tem_bullet= tem_bullet_alice;
				Sleep(50);
				FlushBatchDraw();
			}

			tem_bullet_enemy->next_bullet = NULL;//可能不会爆内存
			//Sleep(1000);
			break;
		}

		Sleep(500);

		//子弹运动
		//frist_bullet_enemy = true_frist_bullet_enemy;
		int tem_add = 0;//一会你就知道它是干嘛用的了
		int other_add = 0;




		setorigin(alice->x, alice->y);
		cleardevice();
		//*all_bullet_alice = *true_frist_bullet_enemy;
		int tem_number = 0;
		while (1)
		{
			tem_number++;
			tem_add += other_add;
			//有用，但是用不上
			if (true_frist_bullet_enemy->next_bullet == NULL)//(tem_number % 18 == 0)
			{
				Sleep(1000.0/30 );
				//cleardevice();
				break;
			}

			setfillcolor(RED);

			fillcircle(0, 0, r_boss);

			true_frist_bullet_enemy->r_created += true_frist_bullet_enemy->v_absolute;//沿theta方向移动
			//true_frist_bullet_enemy->r_created = all_bullet_alice->r_created;
			setfillcolor(GREEN);
			//cleardevice();
			fillcircle(theta_to_x(true_frist_bullet_enemy->move_theta + tem_add, true_frist_bullet_enemy->r_created)
				, theta_to_y(true_frist_bullet_enemy->move_theta + tem_add, true_frist_bullet_enemy->r_created), 5);
			//fillcircle(theta_to_x(frist_bullet_enemy->move_theta, frist_bullet_enemy->frist_direction_about_orgin), theta_to_y(frist_bullet_enemy->move_theta, frist_bullet_enemy->frist_direction_about_orgin), 5);
			true_frist_bullet_enemy = true_frist_bullet_enemy->next_bullet;
			FlushBatchDraw();
			//cleardevice();
			if (true_frist_bullet_enemy->next_bullet == true_frist_bullet_enemy)
			{
				cleardevice();
				outtextxy(400, 200, L"!!!");
				FlushBatchDraw();
				_getch();
				break;
			}


		}

		FlushBatchDraw();
		//Sleep(1000);
	}
	outtextxy(200, 400,L"结束了");
	_getch();
*/

