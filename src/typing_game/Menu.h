#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <queue>
#include <time.h>

using namespace std;


// 被选中的选项颜色
#define TextSelect BACKGROUND_GREEN
// 默认的文字样式
#define TextDefault FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

const int GROUND = 27;
const int SCR_WIDTH = 60;
const int HEALTH = 5;

// 管理界面绘制
class Menu
{
private:
	HANDLE m_handle;
	COORD m_crd;

public:
	Menu();

	// 设置光标位置
	void SetCursor(int x, int y);

	// 设置文字颜色，只是省略了SetConsoleTextAttribute的第1个参数
	void SetTextColor(WORD wAttributes);

	// 显式欢迎界面
	void Welcome();

	// 显式难度选择菜单
	int ShowMenu(); 

	// 绘制地面
	void DrawGround();
};


// 管理血量的显式、减少、恢复
class Vitality
{
private:
	int m_health; // 剩余血量

public:
	Vitality();

	// 显示血量
	void ShowVitality();

	// 减少血量
	int GetWound(int n = 1);

	// 回复血量
	int GetHeal();
};

extern Menu menu;
extern Vitality vty;


