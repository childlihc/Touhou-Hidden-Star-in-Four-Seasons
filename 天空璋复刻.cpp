#include "project.h"
#include "move.h"


#define defalut_generate_enemy_x_left (tang_x - r_enemy) //默认生成敌机初坐标
#define defalut_generate_enemy_x_right (tang_x + lenght_move_x + r_enemy)
#define defalut_generate_enemy_y_up (tang_y - r_enemy)
#define defalut_generate_enemy_y_down (tang_x + lenght_move_y + r_enemy)
#define Pi 3.14159265358979



int r_boss = 30;//临时的，等定义好全部boss，就删掉

int screen_x = 1000, screen_y = 600;
int order = 1;//光标选择第几个
const int number_choose = 10;//一个界面内一共有几个选项
int frist_order_x = 100, frist_order_y = 300;//控制光标
int order_level = 1;//选择的第几个难度(决定难度)
int time_game = 1;//游戏运行时间刻
int player_live = 8, player_live_splinter = 0,player_bomb = 3,player_bomb_splinter = 0;//生命碎片和bomb碎片
int generate_enemy_number = 1;//这是生成的第几只敌机
int choose_character = 1;//选择的自机
double r_graze = r_player * 3;//擦弹范围，同时也是碰撞检查的范围半径（圆形）

wchar_t menu[number_choose][5] = { L"开始游戏" , L"ex难度" ,L"练习模式",L"符卡练习",L"播放录像",L"玩家成绩" , L"音乐播放",L"游戏设置",L"游戏介绍" ,L"退出游戏" };
double control_choose_move = 1;
wchar_t title_word[5][2] = { L"东" ,L"方",L"天",L"空",L"璋" };
wchar_t title_word_english[5][8] = { L"Hidden",L"Star",L"in",L"Four",L"Seasons" };

std::vector<set_enemy> stage_1_youkai = { {100,100,少,0,YELLOW},{150,100,少,0,GREEN},{200,100,少,0,BLACK},{250,100,少,0,BROWN},{300,100,少,0,WHITE},{350,100,少,0,BLUE}};//在这里赋好值再运行
std::vector<set_enemy> stage_2_youkai = { {},{},{} };//动态数组，像他妈数组一样


enum move_move {匀直 = 0,变直,匀圆周,};

enum character_name
{_冴月麟 = 0, _灵梦,_琪露诺,_文,_魔理沙,_爱丽丝};//夹了一点私货 


union present_boss//当前关卡的boss（包括道中）
{
	boss name = alice;
}present_boss;

LOGFONT title_style =//标题文字格式
{
	title_style.lfHeight = 130,//高度
	title_style.lfWeight = 0,
	title_style.lfQuality = ANTIALIASED_QUALITY
};
LOGFONT normal; //正常的文字格式
LOGFONT mode_english//难度英文的文字格式
{
	mode_english.lfHeight =100

};
LOGFONT mode_description//难度描述的文字格式
{

};
//typedef struct enemy _enemy ;

enemy_class *tem_next_enemy;

//为了全局变量
enemy_class* frist_enemy = new enemy_class;//相对与每个stage而言
enemy_class* true_frist_enemy = frist_enemy;//

volatile void delay(double count)//防止被编译器优化
{
	
	int i;
	for (i = 1; i <= count * 3000; i++)
		;
}

// (废弃了，类里面有)void init_enemy(enemy_class* class_e)//(只能单个，多个（链表）不太好写，摆了)初始化敌机信息（包括位置、初始血量等）

/*//因为只使用类链表和弹幕动态数组，所以用不上了
void init_bullet_head()//为敌机子弹的头赋值并跳过，防止头被删除
{
	bullet_enemy_head->frist_direction_about_orgin = 0;
	bullet_enemy_head->v_absolute = 0;
	bullet_enemy_head->r_bullet = 1;
	bullet_enemy_head->next_bullet = all_bullet_enemy;
}
*/



int initialize(void)//初始化信息
{
	srand(time(0));
	initgraph(screen_x, screen_y);
	BeginBatchDraw();
	//初始化文字格式
	gettextstyle(&normal);
	                                                          //init_bullet_head();//用不上了
	
	return 1;
}



//生成一个类，将敌机与弹幕联系起来
enemy_class* _stdcall information_enemy(_Inout_ std::vector<set_enemy> *enemy_inf)//把这个类里面的信息转换成链表的形式（虽然我也不知道为啥要这样）
//（用不着）搜索SAL，祥见https://learn.microsoft.com/zh-cn/cpp/code-quality/annotating-function-parameters-and-return-values?view=msvc-170
//输入值一看就知道                      //输入值是敌机信息（struct enemy）
//返回值是链表(对象，类)////////波数（输入游戏刻的个数（模仿scanf））
{

	static enemy_class* head = new enemy_class;//链表头
	//static set_enemy* one_by_one = new set_enemy;
	static enemy_class *present_enemy = new enemy_class;
	head = present_enemy;
	static enemy_class* tem_enemy = new enemy_class;
	
	/*
	present_enemy->name_enemy = *enemy_inf->begin();//某个类的头地址
	//head->name_enemy = present_enemy->name_enemy;//创建链表
	present_enemy->initialize();//第一个
	head = present_enemy;//创建链表
	head->next = present_enemy;
	*/
	//head = present_enemy;
	//head->next = present_enemy;//后面已经有了
	//static enemy_class* tem_next;
	
	//va_list begin;//初始化(为链表做准备)///TMD，不是可变参数函数用不了va_list
	//va_start(begin, &present_enemy);//不知道可不可以，不行的话就得改一下”set_enemy present_enemy = *enemy_inf->begin();//某个类的头地址“了
	//意思是从传入参数的第一个开始为链表赋值

	//for (int tem = 0; tem < enemy_inf->size(); tem++)
	//for (;bool operator != (present_enemy & *enemy_inf->end()&);resent_enemy )

	//std::_Vector_iterator<std::_Vector_val<std::_Simple_types<set_enemy>>>* tem = new std::_Vector_iterator<std::_Vector_val<std::_Simple_types<set_enemy>>>;
	//*tem = enemy_inf->begin();//因为begin（）是右值，没法用&取地址,所以临时整一个代替品

	for (int i = 0; i < enemy_inf->size(); i++)
	{
		tem_enemy = new enemy_class;
		tem_enemy->name_enemy = (*enemy_inf)[i] ;//我他妈像疯了一样
		//居然可以，真离谱
		tem_enemy->initialize();//初始化赋值 （详见注释）
		//present_enemy->name_enemy.next_enemy = &(tem_next->name_enemy);
		
		present_enemy->next = tem_enemy;//换下一个类
		present_enemy = tem_enemy;//???
		//present_enemy = tem_next;//换下一个类
	}
	tem_enemy->next = NULL;
	////present_enemy->name_enemy.next_enemy = NULL;//结束
	//delete(tem);//或许用不着delete
	//tem_next = NULL;//结束
	return head;
}

char choose_move(int *order)  //开始界面，用光标选择    (输入选择的是第几个)
{
	char tem_inter = _getch();
	
	if (tem_inter == -32)
	{
		int move_choose = _getch();
		switch (move_choose)
		{
		case 80://up
			if (*order == number_choose)
			{
				*order = 1;
			}
			else
			{
				*order += 1;
			}
			break;
		case 72://down
			if (*order == 1)
			{
				*order = number_choose;
			}
			else
			{
				*order -= 1;
			}
			break;
		}
	}
	if (tem_inter == 'x'||tem_inter == 'X')
	{
		*order = number_choose;
	}

	return tem_inter;
}

int tem_number = 25;//保证选项平均分布
void printf_choose(int order)//显示光标,（x坐标固定（200），y在300到600之间，一共5个）
{
	int choose_word_x = frist_order_x + order * 5 - 20, choose_word_y = frist_order_y + (order - 1) * tem_number;
	wchar_t choose[] = L"->";
	outtextxy(choose_word_x, choose_word_y, choose);
}

int turn_to_setting()//转到设置界面后的画面
{
	cleardevice();
	const int word_x = 200, word_y = 100, word_distance = 50, number_word = 2;
	wchar_t impertant[] = L"按z键显示下一行，按x键退出";
	wchar_t word[number_word][256] = { L"还没有想好",L"真的还没有想好" };
	cleardevice();
	outtextxy(100, 50, impertant);
	for (int i = 0; i < number_word; i++)
	{

		outtextxy(word_x, word_y + i * word_distance, word[i]);
		FlushBatchDraw();
		int tem_inter = _getch(), jump_out = 1;
		while (jump_out)
		{
			switch (tem_inter)
			{
			case 90://Z
			case 122://z
				jump_out = 0;
				break;
			case 88://X
			case 120://x
				return 0;
			default:
				tem_inter = _getch();

			}
		}
	}
		int tem_inter;
		do {
			tem_inter = _getch();
		} while (!(tem_inter == 88 || tem_inter == 120));

		return 0;
	
}


void draw_game_picture()//绘制游戏开始时的画面
{
	setbkcolor(0xFF1493);//背景颜色
	cleardevice();
	setfillcolor(BLUE);
	fillrectangle(tang_x, tang_y, length_move_x, length_move_y);//绘制底板
}
void draw_enemy(enemy_class* head_of_enemy = NULL)//(COLORREF color_enemy)//绘制敌机
//输入链表头（如果有的话）
{
	//setfillcolor(color_enemy);//敌机颜色
	enemy_class* tem_enemy = new enemy_class;
	*tem_enemy = (head_of_enemy == NULL ? *true_frist_enemy : *head_of_enemy);//我不记得true_frist_enemy是不是链表头了
	//建立临时类链表头
	while (tem_enemy!= NULL)
	{
		setfillcolor(tem_enemy->name_enemy.color);
		fillcircle(tem_enemy->name_enemy.x, tem_enemy->name_enemy.y, r_enemy);
		tem_enemy = tem_enemy->next;
	}
	delete(tem_enemy);
	tem_enemy = nullptr;
}

enemy_class* delete_enemy(enemy_class* head,enemy_class* enemy_deleted)//输入地址的地址
{
	enemy_class *tem_enemy;
	tem_enemy = head;
	enemy_class* new_head = new enemy_class;
	new_head = tem_enemy;
	while (tem_enemy != nullptr)
	{
		/*稍等
		if (tem_enemy->next == enemy_deleted)
		{
			tem_enemy->next = enemy_deleted->next;

			
			delete enemy_deleted;
			enemy_deleted = nullptr;
			return ;
		}
		*/
		tem_enemy = tem_enemy->next;
	}
	delete new_head;
	new_head = nullptr;
	return head;
}

bullet_of_enemy* generated_bullet(double theta, double direction_orgin, COLORREF color, double v = 5, double delta_theta = 0)//生成弹幕并赋值
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

int stage_1()//这里只负责在初坐标生成敌机，移动在别的函数上
{
	present_boss.name = alice;
	
	cleardevice();
	//准备敌机内存
	//std::vector::clear();
	
	enemy_class* all_enemy = new enemy_class;
	
	all_enemy = information_enemy(&stage_1_youkai);//在这里赋好值再运行
	enemy_class* tem_enemy = new enemy_class;
	*tem_enemy = *all_enemy;
	
	while (1)//只用类链表
	{
		true_frist_enemy = all_enemy;//???为了以后
		time_game++;
		draw_game_picture();
		while(1)
		{
			if (time_game == tem_enemy->name_enemy.time_born )//这里好像也得改
			{
				tem_enemy->name_enemy.isexisted = 1;
			}
			break;
		}

		//绘制敌机（包装成函数）
		if (1)
		{
			draw_enemy(true_frist_enemy);
		}
		//敌机移动（改变位置，不绘制）
		//使用move_class的函数
		enemy_class* tem_head = new enemy_class;//不这样的话tem_head == NULL，无法赋值（包括指针)
		*tem_head = *all_enemy;
		while (tem_head != NULL)
		{
			switch (tem_head->name_enemy.move_line_x)
			{
			case move_null:
				break;
			case move_normal:
				move_class::normal(tem_head,'x');
				break;
			}
			switch (tem_head->name_enemy.move_line_y)
			{
			case move_null:
				break;
			case move_normal:
				move_class::normal(tem_head, 'y');
			}
			tem_head = tem_head->next;
		}

		//生成子弹（做好心理准备，这段可能要重写，甚至用不上）
		
		/*
		double theta_change = 0;
		double theta_change_2 = 2;
		int tem_theta_change_1 = 1;
		int tem_geneater_enemy;
		//bullet_of_enemy* tem_head = new bullet_of_enemy;
		bullet_of_enemy *t_head = new bullet_of_enemy;//子弹，不是敌机,仅用于生成子弹，之后就放在类里面了
		unsigned int number_of_bullet = 1;
		tem_geneater_enemy = time_game % 5;
		switch (tem_geneater_enemy)
		{
		case 2:
			for (double i = 0; i < 12; i++)
			{
				next_bullet_enemy = bullet_class::generated_bullet((i * (Pi / 6)) + theta_change * (Pi / theta_change_2), r_boss, BLUE);
				all_bullet_enemy->next_bullet = next_bullet_enemy;
				all_bullet_enemy = next_bullet_enemy;
				number_of_bullet++;
			}
			theta_change++;
			theta_change_2 = 18;
			break;
		case 3:
			if (time_game > 80)
			{
				for (double i = 0; i < 9; i++)
				{
					next_bullet_enemy = bullet_class::generated_bullet((Pi / 9) + (i + 1) * (2 * Pi / 8) - (tem_theta_change_1 * Pi / 32), r_boss, RED, 10);
					all_bullet_enemy->next_bullet = next_bullet_enemy;
					all_bullet_enemy = next_bullet_enemy;
					number_of_bullet++;
					tem_theta_change_1++;
				}
			}
			if (time_game > 40 && time_game < 80)//* 30)
			{

				for (double i = 0; i < 8; i++)
				{
					next_bullet_enemy = bullet_class::generated_bullet((Pi / 9) + (i + 1) * (2 * Pi / 8), r_boss, RED, 10);
					all_bullet_enemy->next_bullet = next_bullet_enemy;
					all_bullet_enemy = next_bullet_enemy;
					number_of_bullet++;
				}

			}
			break;
		}
		all_bullet_enemy->next_bullet = NULL;
		
		*/

		//绘制子弹
		tem_head = new enemy_class;//不这样的话tem_head == NULL，无法赋值（包括指针)
		*tem_head = *all_enemy;
		while (tem_head != NULL)
		{
			for (int i = 0; i < tem_head->number_of_bullet; i++)
			{
				draw_bullet(tem_head->name_enemy.frist_x, tem_head->name_enemy.frist_x, &(tem_head->frist_bullet[i]));
			}
			
			tem_head = tem_head->next;
		}

		//碰撞检测
		/*
		tem_head = new bullet_of_enemy;
		*tem_head = *bullet_enemy_head;
		double tem_x_bullet ,tem_y_bullet;
		while (1)
		{

			tem_head->bullet_enemy.r_created += tem_head->bullet_enemy.v_absolute;
			tem_x_bullet = theta_to_x(tem_head->bullet_enemy.move_theta, tem_head->bullet_enemy.r_created);
			tem_y_bullet = theta_to_y(tem_head->bullet_enemy.move_theta, tem_head->bullet_enemy.r_created);
			setorigin(0, 0);
			if (tem_head != NULL && pow(tem_x_bullet - x_player, 2) + pow(tem_y_bullet - y_player, 2) < pow(r_graze, 2))//剔除离自机远的子弹（不在擦弹范围内的）
			{
				tem_head->bullet_enemy.isjudge = 1;
			}
			if (tem_head != NULL && tem_head->bullet_enemy.isjudge && pow(tem_x_bullet - x_player, 2) + pow(tem_y_bullet - y_player, 2) < pow(r_player, 2))//检测自机是否碰到子弹
			{
				//player_live--;
			}
			tem_head = tem_head->bullet_enemy.next_bullet;
			if (tem_head == NULL)
			{
				break;
			}
		}//这里结束的时候，tem_head == NULL
		
		//delete(tem_head);//所以没有必要
		*/
		//清除越界的子弹
		/*
		tem_head = new bullet_of_enemy;//不这样的话tem_head == NULL，无法赋值（包括指针)
		*tem_head = *bullet_enemy_head;
		while (1)
		{
			//_getch();
			if (tem_head == NULL)
			{
				break;
			}
			if (tem_head != NULL)
			{
				if (((theta_to_x(tem_head->move_theta, tem_head->r_created) > tem_head->enemy_x - tang_x || theta_to_x(tem_head->move_theta, tem_head->r_created) < tem_head->enemy_x - tang_x - length_move_x) ||
					(theta_to_y(tem_head->move_theta, tem_head->r_created) > tem_head->enemy_y - tang_y || theta_to_y(tem_head->move_theta, tem_head->r_created) < tem_head->enemy_y - tang_x - length_move_y)))//我不知道100和500是怎么来的，但是它们确实有用，可以修改它们的值并查看效果，以此来推断过程
				{
					delete_bullet(tem_head, bullet_enemy_head);
					tem_head = tem_head->next_bullet;
				}
			}
			
			tem_head = tem_head->next_bullet;
			/*
			tem_head = tem_head->next_bullet;
			if (tem_head == NULL)
			{
				break;
			}*

		}*/
		//delete(tem_head);
		
		//绘制掉落物

		//回收敌机（包装成函数）

		//第一关结束
		//{return 0; }//残0不续关
		


		FlushBatchDraw();
		Sleep(1000.0 / 60);
	}
	
	//对话完成
	//结算最终得分

	//初始化敌机链表
	delete(true_frist_enemy);//???
	true_frist_enemy = new enemy_class;

	return 1;//通关
}
int stage_2(boss boss_name)
{

	return 1;
}
int game_start()//选择“游戏开始”后的画面
{
	
	wchar_t level_1[][14] = { L"  " ,L"easy mode",  L"normal mode",  L"hard mode",  L"laughten mode",L"  " };
	wchar_t level_2[][5] = { L"春之小雨",L"夏之阵雨",L"秋之台风",L"蛰居之冬" };
	wchar_t level_3[][3] = { L"",L" ",L" ",L" " };
	int frist_order_x = 20, second_order_x = 400, thrid_order_x = 920;//动态移动
	while (1)//选择难度
	{
		//ex 恶心级的难度，为恶心丸们准备   我忘记了
		//settextstyle(&mode_english);
		outtextxy(frist_order_x, 2.0 * screen_y / 6, level_1[order_level - 1]);
		outtextxy(400, 3.0 * screen_y / 6, level_1[order_level]);
		outtextxy(920, 4.0 * screen_y / 6, level_1[order_level + 1]);
		if (_kbhit())
		{
			char tem_inter = _getch();
			if (tem_inter == -32)
			{
				char inter = _getch();
				if (inter == 72||inter == 75)//up&left
				{
					order_level--;

				}
				if (inter == 80||inter == 77)
				{
					order_level++;

				}
			}
			if (order_level < 1)//限制范围
			{
				order_level = 1;
			}
			else if (order_level > 4)
			{
				order_level = 4;
			}
			if (tem_inter == 'x'||tem_inter =='X')//x
			{
				return 1;
			}
			else if (tem_inter == 'z'||tem_inter =='Z')//z
			{
				break;
			}

		}
		FlushBatchDraw();
		cleardevice();
	}
	int order_choose_character = 1;
	int number_character = 5;
	wchar_t character_name[5][6] = { L"",L"" ,L"",L"",L""};
	//delay(10000);
	while (1)//选择人物
	{
		cleardevice();
		outtextxy(200,200,L"默认");
		
		
		/*
			长夏中永恒不变的人偶使
			天气变得潮湿酷热，阴阳平稳的季节
			是 阴雨连绵，湿热交织，气的升降平衡，气机平和的季节
		*/

		if (order_choose_character > number_character)
		{
			order_choose_character = 1;
		}
		else if (order_choose_character < 1)
		{
			order_choose_character = number_character;
		}
		if (_kbhit())
		{
			char inter = _getch();
			if (inter == 'x'||inter == 'X')//x
			{
				game_start();
				return 1;
			}
			else if (inter == 'z'||inter == 'Z')//z
			{
				//这里有大箭头型代码的倾向
				if (stage_1())
				{
					if (stage_2(alice))
					{
						//通关（各结局函数）
					}
				}
				else//game over函数
				{

				}
			}
			else
			{

			}
		}
		FlushBatchDraw();
		//_getch();
	}

}

void practice()
{


}

int choose_tp( )//选择选项（游戏未开始界面）
{
	if (GetKeyState(0x5A) < 0)
	{
		switch (order)
		{
		case 1:
			game_start();
			//return 1;
			break;
		case 2:
			cleardevice();
			for (int i = 0; i < 100; i++)
			{
				outtextxy(200 + 30, 150, L"制作中");
			}
			FlushBatchDraw();
			_getch();
			break;
		case 3:
			practice();
			break;
		case 4:
			outtextxy(200 + 30, 150, L"4");
			break;
		case 5:
			outtextxy(200 + 30, 150, L"5");
			break;
		case 6:
			outtextxy(200 + 30, 150, L"6");
			return 6;
		case 7:
			break;
		case 8:
			turn_to_setting();

		}
	}
	/*int tem_inter;
	do {
		tem_inter = _getch();
	} while (!(tem_inter == 88 || tem_inter == 120));
	*/return 0;
}

int judge_ex()//判断ex难度是否解锁
{

	return 0;
}

void printf_game_menu()
{
	graphics_all.heart(200, 200);
	for (int i = 0; i < number_choose; i++)
	{
		outtextxy(frist_order_x + 20 + 5 * i + 10 * sin(control_choose_move), frist_order_y + 25 * i, menu[i]);
		
	}
	control_choose_move += 0.01;
	delay(1000);
	outtextxy(400, 550, L"@2017 ZUN ALL right reserved");
	settextstyle(&title_style);//打印标题
	for (int i = 0; i < 5; i++)
	{
		if (i == 2)//天
		{
			title_style.lfHeight += 80;
			settextstyle(&title_style);
			outtextxy(165 + 120 * i, 50 + 25 * (sin((i * 2 - 1) * 3.141592653 / 4 + 0.5)), title_word[i]);
		}
		else
		{
			title_style.lfHeight = 110;
			settextstyle(&title_style);
			outtextxy(200 + 120 * i, 100 + 20 * (sin((i * 2 - 1) * 3.141592653 / 4 + 0.5)), title_word[i]);
		}
	}
	settextstyle(&normal);
	//outtextxy();
	//delay(8000.0/6);

	
}

int for_main()
{
	int exit = 2;//确保第二次按下x键时才退出游戏
	char tem_inter = 0;
	while (1)
	{
		printf_game_menu();
		printf_choose(order);
		if (_kbhit())
		{
			tem_inter = choose_move(&order);
			if (((order == number_choose) && (tem_inter == 'z' || tem_inter == 'Z')))
			{
				return 0;
			}
			/*
			if ((order == number_choose) && (tem_inter == 'x' || tem_inter == 'X'))
			{
				char other_inter = _getch();
				if (tem_inter == 'x' || tem_inter == 'X')
				{
					return 0;
				}
			}*/
			/*else
			{
				delay(10000);
				if ((GetKeyState(0x58) < 0)&&(order == number_choose))
				{
					return 0;
				}
			}*/
			choose_tp();
		}
		FlushBatchDraw();
		cleardevice();
	}
}

int main()
{
	initialize();//初始化
	return for_main();
}/*论如何用两行指令写一个游戏(滑稽)*/
