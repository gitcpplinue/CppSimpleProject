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

void Level(int select, LetterShower& ls);

int main()
{
	srand(time(0)); // 产生随机种子

	// 先显示欢迎界面，待用户按下任意键后进入选项界面
	menu.Welcome();
	_getch();

	char choice; // 用户的选项
	LetterShower ls;
	int level; // 用户选择的难度登记

	do
	{
		level = menu.ShowMenu();

		// 清除ShowMenu()生成的界面
		system("cls");
		// 清空上次ls运行的状态
		ls.ClearAll();
		vty.GetHeal();

		// 显示选取的难度
		Level(level, ls);
		// 显示地面
		menu.DrawGround();
		// 显示生命值
		vty.ShowVitality();
		// 显示得分（0）
		ls.ShowScore();

		// 游戏开始运行
		ls.Rain();

		// 游戏结束，询问用户是否重新开始
		menu.SetCursor(10, GROUND + 2);
		cout << "Try again?(y/n)";
		cin >> choice;
	}while (choice == 'Y' || choice == 'y');

}


void Level(int select, LetterShower& ls)
{

	menu.SetCursor(0, 0);
	switch (select)
	{
	case 0:
		printf("Level: EASY ");
		ls.SetDelay(300);
		break;
	case 1:
		printf("Level: INTERMEDIATE ");
		ls.SetDelay(200);
		break;
	case 2:
		printf("Level: HARD ");
		ls.SetDelay(100);
		break;
	default:
		printf("Level: EASY ");
		ls.SetDelay(300);
		break;
	}
}


