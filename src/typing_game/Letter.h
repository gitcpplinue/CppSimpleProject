#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <queue>
#include <time.h>
#include "Menu.h"
using namespace std;

// 字母及其坐标
struct Letter
{
	char letter;
	int x;
	int y;
};

// 管理字母的生成、下落
class LetterShower
{
private:
	vector<Letter> m_letters[26]; // 每个字母1个容器
	int m_score; // 分数
	int m_delay; // 字母落下的速度

	// 判断字母是否落到了地面
	bool Ground(Letter l) { return l.y >= GROUND; }

public:
	LetterShower();

	// 设置字母的掉落速度
	void SetDelay(int d);
	void Wait();

	// 生成一个字母，存入容器中
	void GenerateLetter();
	
	// 字母下落，返回"-1"意味着游戏结束
	int Fall();

	// 清空容器
	void ClearAll();

	// 显示分数
	void ShowScore();

	// 游戏开始
	// 反复执行Fall函数，让字母持续下落，捕捉用户的按键，消除对应的字母
	void Rain();
};

