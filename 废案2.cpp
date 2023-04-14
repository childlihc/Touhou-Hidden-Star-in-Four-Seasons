#include "project.h"



int screen_x = 1000, screen_y = 600;
int order = 1;//光标选择第几个
const int number_choose = 10;//一个界面内一共有几个选项
int frist_order_x = 100, frist_order_y = 300;//控制光标
int order_level = 1;//选择的第几个难度(决定难度)
int time_game = 1;//游戏运行时间刻
int player_live = 8, player_live_splinter = 0, player_bomb = 3, player_bomb_splinter = 0;//生命碎片和bomb碎片
int generate_enemy_number = 1;//这是生成的第几只敌机


wchar_t menu[number_choose][5] = { L"开始游戏" , L"ex难度" ,L"练习模式",L"符卡练习",L"播放录像",L"玩家成绩" , L"音乐播放",L"游戏设置",L"游戏介绍" ,L"退出游戏" };
double control_choose_move = 1;
wchar_t title_word[5][2] = { L"东" ,L"方",L"天",L"空",L"璋" };
wchar_t title_word_english[5][8] = { L"Hidden",L"Star",L"in",L"Four",L"Seasons" };
LOGFONT title_style =//标题文字格式
{
	title_style.lfHeight = 130,//高度
	title_style.lfWeight = 0,
	title_style.lfQuality = ANTIALIASED_QUALITY
};
LOGFONT normal; //正常的文字格式
LOGFONT mode_english//难度英文的文字格式
{
	mode_english.lfHeight = 100
};
LOGFONT mode_description//难度描述的文字格式
;
typedef struct enemy  //小怪
{
	int number = generate_enemy_number;//这是第几个生成的敌机（用于链表删除）
	double x = 0, y = 0;
	double frist_x, frist_y;//最开始生成的位置   //(其实应该是定值)
	int Hp = 少;//血量
	int number_of_Hp = 少;//控制血量，其实应该是定值//好吧，是变量，毕竟要被覆盖
	int isexisted = 0;//是否生成
	double v_x = 6, v_y = 6;//敌机速度
	double a_x = 0, a_y = 0;//敌机加速度
	int wait = 0; //敌机从生成到移动的时间段  (为0则生成)
	int name; //敌机种类（暂时还没想好）
	int time_exist = 0;//（非必要，敌机已生成的时间，用于控制运动轨迹）
	//int mark_move_line = move_null; //标记运动路线（默认符合加速运动）
	struct enemy* next_enemy = NULL;
} set_enemy;
enemy* tem_next_enemy;
//为了全局变量
struct enemy* frist_enemy = new set_enemy;
struct enemy* true_frist_enemy = frist_enemy;//
volatile void delay(double count)//防止被编译器优化
{
	int i;
	for (i = 1; i <= count * 3000; i++);
}
int initialize(void)//初始化信息
{
	//初始化文字格式
	gettextstyle(&normal);


	return 1;
}
char choose_move(int* order)  //开始界面，用光标选择    (输入选择的是第几个)
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
	if (tem_inter == 'x' || tem_inter == 'X')
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
void generate_enemy(int frist_x, int frist_y)//生成敌机位置（不绘制，不移动）
{
	frist_enemy->frist_x = frist_x;//生成敌机（不绘制）
	frist_enemy->frist_y = frist_y;
	frist_enemy->x = frist_enemy->frist_x;
	frist_enemy->y = frist_enemy->frist_y;
	frist_enemy->isexisted = 1;
	frist_enemy->number = generate_enemy_number;
	generate_enemy_number++;//下一个生成敌机的编号（第n+1个敌机生成）
	tem_next_enemy = new set_enemy;
	frist_enemy->next_enemy = tem_next_enemy;//实现链表
	frist_enemy = tem_next_enemy;
}
void draw_enemy()//绘制敌机
{
	setfillcolor(RED);//敌机颜色
	frist_enemy = true_frist_enemy;
	while (1)
	{
		fillcircle(frist_enemy->x, frist_enemy->y, r_enemy);
		frist_enemy = frist_enemy->next_enemy;
		if (frist_enemy->next_enemy == NULL)
		{
			break;
		}
	}
}
void free_enemy(struct enemy* delete_enemy)//删除敌机（未完成）
{
	(*(delete_enemy - 1)).next_enemy = (*delete_enemy).next_enemy;//从链表中删除
	free(delete_enemy);

}
int delete_enemy(set_enemy** tem_enemy, int number_enemy_delete)//输入地址的地址
{
	return 1;
}

int stage_1()//这里只负责在初坐标生成敌机，移动在别的函数上
{
	cleardevice();
	while (1)
	{
		time_game++;
		draw_game_picture();
		switch (time_game)//生成敌机（只生成不移动）
		{
		case 2:
		{
			int j = 0;
			int tem_y;
			for (int i = 0; i < 20; i++)
			{
				j = 0;
				
				do
				{

					//generate_enemy( tem_x,tem_y );
					j++;
				} while (j < 3);
			}
			break;
		}
		case 300:
			break;
		}
		if (time_game > 20)
		{
			draw_enemy();
		}
		FlushBatchDraw();
		Sleep(1000.0 / 60);
	}
	return 1;//通关
}
int stage_2()
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
		outtextxy(frist_order_x, 2.0 * screen_y / 6, level_1[order_level - 1]);
		outtextxy(400, 3.0 * screen_y / 6, level_1[order_level]);
		outtextxy(920, 4.0 * screen_y / 6, level_1[order_level + 1]);
		if (_kbhit())
		{
			char tem_inter = _getch();
			if (tem_inter == -32)
			{
				char inter = _getch();
				if (inter == 72 || inter == 75)//up&left
				{
					order_level--;

				}
				if (inter == 80 || inter == 77)
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
			if (tem_inter == 'x' || tem_inter == 'X')//x
			{
				return 1;
			}
			else if (tem_inter == 'z' || tem_inter == 'Z')//z
			{
				break;
			}

		}
		FlushBatchDraw();
		cleardevice();
	}
	int order_choose_character = 1;
	int number_character = 5;
	wchar_t character_name[5][6] = { L"",L"" ,L"",L"",L"" };
	while (1)//选择人物
	{
		cleardevice();
		outtextxy(200, 200, L"灵梦");
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
			if (inter == 'x' || inter == 'X')//x
			{
				game_start();
				return 1;
			}
			else if (inter == 'z' || inter == 'Z')//z
			{
				int next = stage_1();
				if (next)
				{
					next = stage_2();
					if (next)
					{

					}
				}
			}
		}
		FlushBatchDraw();
	}
}
void practice()
{
}
int choose_tp()//选择选项（游戏未开始界面）
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
	return 0;
}
int judge_ex()//判断ex难度是否解锁
{
	return 0;
}
void printf_game_menu()
{
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
}
int main()
{
	initgraph(screen_x, screen_y);
	BeginBatchDraw();
	initialize();//初始化
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
			choose_tp();
		}
		FlushBatchDraw();
		cleardevice();
	}
	return 0;
}