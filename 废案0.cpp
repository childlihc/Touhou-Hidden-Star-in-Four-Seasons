#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <string.h>
#include <stdlib.h>

wchar_t game_star[] = L"开始游戏", ex_start[] = L"ex难度",exercise[] = L"练习模式",something[] = L"游戏介绍", setting[] = L"设置", end_game[] = L"结束游戏";

int screen_x = 1000, screen_y = 600;

int order = 1;//光标选择第几个
int number_choose = 6;//一个界面内一共有几个选项


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

void printf_choose(int order)//显示光标,（x坐标固定（200），y在300到600之间，一共5个）
{
	int tem_number = 50;//保证选项平均分布
	int choose_word_x = 200, choose_word_y = 250 + order * tem_number;
	wchar_t choose[] = L"->";
	outtextxy(choose_word_x, choose_word_y, choose);


}

int turn_to_setting()//转到设置界面后的画面
{
	cleardevice();
	const int word_x = 200, word_y = 100, word_distance = 50,number_word = 2;
	wchar_t impertant[] = L"按z键显示下一行，按x键退出";
	wchar_t word[number_word][256] = { L"  还没有想好",L"真的还没有想好" };
	cleardevice();
	outtextxy(100, 50, impertant);
	for (int i = 0; i < number_word; i++)
	{
		
		outtextxy(word_x, word_y + i * word_distance,word[i]);
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

int choose_tp(int order,char inter)//选择选项（游戏未开始界面）
{
	if (inter == 'z'||inter == 'Z')
	{
		switch (order)
		{
		case 1:
			return 1;
			
		case 2:
			cleardevice();
			outtextxy(screen_x / 2, screen_y / 2,L"想啥呢，普通难度我都没做完");
			FlushBatchDraw();
			Sleep(2000);

			break;
		case 3:
			break;
		case 4:
			turn_to_setting();
			break;
		case 5:
			break;
		case 6:
			return 6;

		}
	}
	return 0;
}

int main()
{
	
	
	//_getch();
	initgraph(screen_x, screen_y);

	outtextxy(screen_x/3, screen_y/2, L"资源加载中……");



	//Sleep(1000);
	cleardevice();
	outtextxy(screen_x / 3, screen_y / 2, L"加载完成");
	//Sleep(1000);
	cleardevice();



	BeginBatchDraw();
	while (1)
	{
		//roundrect(screen_x / 4, 5 * screen_y / 8, 3 * screen_x / 4, 6 * screen_y / 8, 3 * screen_x / 60, screen_y / 40);
		outtextxy(200 + 20, 300, game_star);
		outtextxy(200 + 20, 350, ex_start);
		outtextxy(200 + 20, 400, exercise);
		outtextxy(200 + 20, 450, something);
		outtextxy(200 + 20, 500, setting);
		outtextxy(200 + 20, 550, end_game);

		printf_choose(order);
		if (_kbhit())
		{
			char inter_player = choose_move(&order);
			int if_begin = choose_tp(order,inter_player);
			if (if_begin == 1)
			{
				break;
			}
			else if (if_begin == 6)
			{
				return 0;
			}
			
		}
		FlushBatchDraw();
		cleardevice();
		
	}
	while (1)//选择难度
	{
		wchar_t e_1[] = L"easy", n_1[] = L"normal", h_1[] = L"hard", l_1[] = L"laughten";
		wchar_t e_2[] = L"入门级的难度，为初次尝试者准备", n_2[] = L"进阶级的难度，为非常熟悉者准备", h_2[] = L"噩梦级的难度，为一切大触准备", L_2[] = L"闹玩级的难度，为三岁小孩准备";
		//ex 恶心级的难度，为恶心丸们准备   我忘记了
		int distance_1 = 100, distance_2 = 50;



		cleardevice();
		FlushBatchDraw();
	}







	return 0;
}
