#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <queue>
#include <time.h>
#include "Menu.h"
#include "Letter.h"



using namespace std;

#pragma comment(lib, "winmm.lib") // 为了使用PlaySound函数播放音效


// --------------------------- 用于绘制界面的全局函数 ---------------------------
void Welcome(); // 欢迎界面
int ShowMenu(); // 难度选择菜单
void ShowPlayGround(int level); // 游戏运行的界面，接收1个int类型参数用于判定当前的难度
int GameStart(int level); // 游戏开始运行。返回值：0-正常结束、1-继续游戏、2-重开游戏、3-结束游戏
int Pause(); // 暂停界面
void ShowRank(); // 排名界面



int main()
{
	srand(time(0)); // 产生随机种子



	// 先显示欢迎界面，待用户按下任意键后进入选项界面
	Welcome();
	_getch();

	char choice = 'y'; // 用户的选项
	int level; // 用户选择的难度登记
	int gret = -1;

	do
	{
		level = ShowMenu();

		// 清除ShowMenu()生成的界面
		system("cls");
		// 清空上次ls运行的状态
		ls.ClearAll();
		health.GetHeal(0);

		ShowPlayGround(level);

		while (1)
		{
			gret = GameStart(level);

			if (gret == 0)
			{
				// 游戏结束，询问用户是否重新开始
				menu.SetCursor(10, GROUND + 2);
				cout << "Try again?(y/n)";
				cin >> choice;
			}
			else if (gret == 1)
				continue; // 继续游戏
			else if (gret == 2)
				break; // 结束此轮游戏
			else if (gret == 3)
				return 0; // 退出游戏
		}
		
	}while (choice == 'Y' || choice == 'y');

}

void showDate()
{
	SYSTEMTIME lt;
	GetLocalTime(&lt);
	printf("date: %d/%02d/%02d %02d:%02d:%02d\n",
		lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond);
}



// --------------------------- 用于绘制界面的全局函数 ---------------------------

void Welcome()
{
	menu.SetCursor(17, 10);
	printf("Welcomt To Type Game!");

	menu.SetCursor(17, 12);
	printf("Press any key to continue...");
}

int ShowMenu()
{
	system("cls"); // 清除之前的欢迎界面

	menu.SetCursor(10, 10);
	printf("Which level do you want to try?");
	int result = 0;
	char ch = 0;

	do
	{
		// 实现按下左右方向键切换选项
		// 默认选中第1项
		if (ch == 75)
			result = (result + 2) % 3; // +2 = -1 + 3
		if (ch == 77)
			result = (result + 1) % 3;

		// 先输出3个选项...
		menu.SetCursor(10, 12);
		printf(" EASY ");
		menu.SetCursor(20, 12);
		printf(" INTERMEDIATE ");
		menu.SetCursor(38, 12);
		printf(" HARD ");

		// ...再根据result的值判断当前所选项，换色后重新输出该选项
		switch (result)
		{
		case 0:
			menu.SetTextColor(TextSelect);
			menu.SetCursor(10, 12);
			printf(" EASY ");
			break;
		case 1:
			menu.SetTextColor(TextSelect);
			menu.SetCursor(20, 12);
			printf(" INTERMEDIATE ");
			break;
		case 2:
			menu.SetTextColor(TextSelect);
			menu.SetCursor(38, 12);
			printf(" HARD ");
			break;
		default:

			break;
		}
		menu.SetTextColor(TextDefault);

		ch = _getch(); // 捕获左右方向键
		//if (ch == 0)ch = _getch(); 视频中说如果按下的是方向键，仅1次_getch()调用还无法获取方向键的值。
	} while (ch != VK_RETURN); // 按下回车结束

	return result;
}

void ShowPlayGround(int difficulty)
{
	// 左上角显示所选难度
	ls.Level(difficulty);

	// 右上角显示血量
	health.ShowHealth();

	// 底部绘制地面
	menu.SetCursor(0, GROUND + 1);
	for (int i = 0; i < SCR_WIDTH; ++i)
		cout << '=';

	// 地面下方显示分数
	ls.ShowScore();

	// 在分数下方显示暂停提示
	menu.SetCursor(0, GROUND + 3);
	cout << "( Press \"esc\" To Pause )";
}

int GameStart(int level)
{
	int pret = -1;
	// 游戏开始运行
	if (ls.Rain() == 1)
		pret = Pause();

	switch (pret)
	{
	case 0:
		system("cls");
		ShowPlayGround(level);
		return 1;
	case 1:
		return 2;
	case 2:
		return 3;
	default:
		return 0;
	}
}

int Pause()
{
	menu.SetCursor(25, GROUND / 2 - 4);
	menu.SetTextColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << "   Pause   ";
	menu.SetTextColor(TextDefault);

	// 下方代码结构与ShowMenu函数相同，同样是列出3个可选项
	int choice = 0;
	char ch = 0;
	do
	{
		// 实现按下上下方向键切换选项
		// 默认选中第1项
		if (ch == 72)
			choice = (choice + 2) % 3; // +2 = -1 + 3
		if (ch == 80)
			choice = (choice + 1) % 3;

		// 先输出3个选项...
		menu.SetCursor(25, GROUND / 2 - 2);
		printf(" CONTINUE ");
		menu.SetCursor(25, GROUND / 2);
		printf(" RESTART ");
		menu.SetCursor(25, GROUND / 2 + 2);
		printf(" EXIT ");

		// ...再根据choice的值判断当前所选项，换色后重新输出该选项
		switch (choice)
		{
		case 0:
			menu.SetTextColor(TextSelect);
			menu.SetCursor(25, GROUND / 2 - 2);
			printf(" CONTINUE ");
			break;
		case 1:
			menu.SetTextColor(TextSelect);
			menu.SetCursor(25, GROUND / 2);
			printf(" RESTART ");
			break;
		case 2:
			menu.SetTextColor(TextSelect);
			menu.SetCursor(25, GROUND / 2 + 2);
			printf(" EXIT ");
			break;
		default:
			break;
		}
		menu.SetTextColor(TextDefault);

		ch = _getch(); // 捕获上下方向键
	} while (ch != VK_RETURN); // 按下回车结束

	return choice;
}

void ShowRank()
{
}