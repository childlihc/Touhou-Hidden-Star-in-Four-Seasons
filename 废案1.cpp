#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
/*
选项可能移动的非常快，暂时还想不到最满意的方法
*/
//定义全局变量
int screen_x = 1000, screen_y = 600;
const int number_choose = 10;//一个界面内一共有几个选项
int frist_order_x = 100, frist_order_y = 300;//第一个选项的坐标，其他选项坐标也与它俩有关
double control_choose_move = 1;//使选项移动起来（动态效果）
wchar_t menu[number_choose][5] = { L"开始游戏" , L"ex难度" ,L"练习模式",L"符卡练习",L"播放录像",L"玩家成绩" , L"音乐播放",L"游戏设置",L"游戏介绍" ,L"退出游戏" };
wchar_t title_word[5][2] = { L"东" ,L"方",L"天",L"空",L"璋" };

//定义文字格式
LOGFONT title_style =//标题文字格式
{
	title_style.lfHeight = 130,//高度
	title_style.lfWeight = 0,
	title_style.lfQuality = ANTIALIASED_QUALITY
};
LOGFONT normal;//正常的文字格式

volatile void delay(double count)//volatile可防止被编译器优化，函数作用是暂停一段时间程序（说实话这个函数在这里没啥大用）
{
	int i;
	for (i = 1; i <= count * 3000; i++);
}
void printf_game_menu()//打印初始界面的文字
{
	for (int i = 0; i < number_choose; i++)//打印选项
	{
		outtextxy(frist_order_x + 20 + 5 * i + 10 * sin(control_choose_move), frist_order_y + 25 * i, menu[i]);
	}
	control_choose_move += 0.01;//使选项移动起来 
	delay(1000);
	outtextxy(400, 550, L"@2017 ZUN ALL right reserved");
	settextstyle(&title_style);//设置标题文字样式
	for (int i = 0; i < 5; i++)
	{
		if (i == 2)//"天"字
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
	settextstyle(&normal);//恢复初始文字输出样式
}
int main()
{
	initgraph(screen_x, screen_y);
	BeginBatchDraw();//头文件函数，开始绘制画面
	while (1)
	{
		printf_game_menu();
		FlushBatchDraw();//头文件函数，绘制画面
		cleardevice();//头文件函数，清屏 
	}
	return 0;
}
