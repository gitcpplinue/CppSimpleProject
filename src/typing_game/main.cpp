#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <queue>
#include <time.h>
#include "Menu.h"
#include "Letter.h"
#include <fstream>
#include "Record.h"
#include "MyDB.h"


using namespace std;

#pragma comment(lib, "winmm.lib") // 为了使用PlaySound函数播放音效


// --------------------------- 用于绘制界面的全局函数 ---------------------------
void Welcome(); // 欢迎界面
int ShowMenu(); // 难度选择菜单
void ShowPlayGround(int level); // 游戏运行的界面，接收1个int类型参数用于判定当前的难度
int GameStart(int level); // 游戏开始运行。返回值：0-正常结束、1-继续游戏、2-重开游戏、3-结束游戏
int Pause(); // 暂停界面
void ShowRank(); // 排名界面

/*
int main()
{
	char choice = 'y'; // 用户的选项
	int level; // 用户选择的难度
	int gret = -1;
	


	srand(time(0)); // 产生随机种子

	// 先显示欢迎界面，待用户按下任意键后进入选项界面
	Welcome();
	_getch();

	do
	{
		level = ShowMenu();

		// 清除ShowMenu()生成的界面
		system("cls");
		// 清空上次ls运行的状态
		ls.ClearAll();
		health.GetHeal(0);

		ShowPlayGround(level);
		rec.SetLevel(level);

		bool flag = 0; // 用于区分游戏正常终止(flag == 1)还是通过暂停界面重新开始(flag == 0)
		while (1)
		{
			gret = GameStart(level);

			if (gret == 0) // 游戏正常结束，退出内层while循环
			{
				flag = 1;
				rec.SetScore(ls.GetScore());
				rec.WriteRecord();
				break;
			}
			else if (gret == 1) // 暂停-继续游戏
				continue; 
			else if (gret == 2) // 暂停-结束此轮游戏，退出内层while循环
			{
				// 记录此轮游戏信息
				rec.SetScore(ls.GetScore());
				rec.WriteRecord();
				flag = 0;
				break; 
			}
			else if (gret == 3) // 暂停-退出游戏
			{
				// 记录此轮游戏信息
				rec.SetScore(ls.GetScore());
				rec.WriteRecord();
				return 0; 
			}
		}

		if (flag) 
		{
			menu.SetCursor(10, GROUND + 2);
			cout << "Try again?(y/n)";
			cin >> choice;
		}
	}while (choice == 'Y' || choice == 'y');

}
*/

int main()
{
	MyDB db;
	db.Init();

	vector<Record> vec;
	int level;
	db.GetRecordByScoreAsc(vec, 0);
	db.AddRecord(777,0);
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
	menu.SetCursor(10, 14);
	printf("←/→: select difficulty");
	menu.SetCursor(10, 15);
	printf("r: show ranks");
	menu.SetCursor(10, 16);
	printf("e: exit");

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
		if (ch == 'r')
			ShowRank();
		if (ch == 'e')
			exit(0);

		// 先显示3个选项...
		menu.SetCursor(10, 12);
		printf(" EASY ");
		menu.SetCursor(20, 12);
		printf(" INTERMEDIATE ");
		menu.SetCursor(38, 12);
		printf(" HARD ");

		// ...再根据result的值判断当前所选项，换色后重新显示该选项
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
	vector<vector<Record>> records(3);
	char ch = 0;
	int level = 0;
	int max = 0;
	rec.ReadRecord(records);

	do
	{
		system("cls"); 

		menu.SetCursor(0, 1);
		printf("←/→: switch page    q: back to menu");


		// 分割线
		menu.SetCursor(0, 2);
		for (int i = 0; i < SCR_WIDTH; ++i)
			cout << '=';

		menu.SetCursor(SCR_WIDTH / 5, 3);
		printf("Score");
		menu.SetCursor(SCR_WIDTH / 5 * 2, 3);
		printf("Date");

		// 实现按下左右方向键切换显示的难度记录
		// 默认显示简单难度下的记录
		if (ch == 75)
			level = (level + 2) % 3; // +2 = -1 + 3
		if (ch == 77)
			level = (level + 1) % 3;

		menu.SetCursor(0, 0);
		switch (level)
		{
		case 0:
			printf("Level: EASY ");
			break;
		case 1:
			printf("Level: INTERMEDIATE ");
			break;
		case 2:
			printf("Level: HARD ");
			break;
		}

		max = 0;
		for(int i = 0; i < records[level].size(); ++i)
		{
			int record = records[level][i].GetScore();
			menu.SetCursor(SCR_WIDTH / 5, 5 + i * 2);
			printf("%d", record);
			menu.SetCursor(SCR_WIDTH / 5 * 2, 5 + i * 2);
			printf("%s", records[level][i].GetDate());

			max = (record > max ? record : max);
		}

		if (max != 0)
		{
			menu.SetCursor(SCR_WIDTH * 0.7, 0);
			printf("Highest score : %d", max);
		}

		ch = _getch(); // 捕获左右方向键
	} while (ch != 'q' && ch != 'Q'); // 按下q回到难度选择界面

	// 退出，回到难度选择界面后要重新绘制界面
	system("cls");
	menu.SetCursor(10, 10);
	printf("Which level do you want to try?");
	menu.SetCursor(10, 14);
	printf("←/→: select difficulty");
	menu.SetCursor(10, 15);
	printf("r: show ranks");
}
