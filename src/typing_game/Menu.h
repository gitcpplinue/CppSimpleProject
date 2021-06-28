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
// 拥有一个全局变量，其它的类要设置光标位置都要通过Menu类成员函数来获取
class Menu
{
private:
	HANDLE m_handle; // 获取控制台标准输出的句柄
	COORD m_crd; // 控制台光标坐标

public:
	Menu();

	// 设置光标位置
	void SetCursor(int x, int y);

	// 设置文字颜色，只是省略了SetConsoleTextAttribute的第1个参数
	void SetTextColor(WORD wAttributes);
};

// 管理血量的显式、减少、恢复
class Health
{
private:
	int m_health; // 剩余血量

public:
	Health();

	// 显示血量
	void ShowHealth();

	// 减少血量，默认伤害为1
	int GetWound(int n = 1);

	// 回复血量，i=0将血量回满，i=1只回1格血
	int GetHeal(int i);
};



extern Menu menu;
extern Health health;

