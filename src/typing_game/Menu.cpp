#include "Menu.h"
#include "Letter.h"


Menu menu;
Health health;


// ------------------- Menu -------------------

Menu::Menu()
{
	system("mode con cols=60 lines=32"); // 设置控制台窗口大小 cols-x lines-y
	m_handle = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出的句柄
}

// 设置光标位置
void Menu::SetCursor(int x, int y)
{
	m_crd.X = x; 
	m_crd.Y = y;
	SetConsoleCursorPosition(m_handle, m_crd);
}

void Menu::SetTextColor(WORD wAttributes)
{
	SetConsoleTextAttribute(m_handle, wAttributes);
}






// ------------------- Health -------------------

Health::Health()
{
	m_health = HEALTH;
}

// 显示血量
void Health::ShowHealth()
{
	menu.SetCursor(SCR_WIDTH * 0.6, 0);
	menu.SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "HP: ";
	for (int i = 0; i < HEALTH; ++i)
	{
		cout << (i < m_health ? "■" : "□");
	}
	menu.SetTextColor(TextDefault);
}

// 减少血量，默认值为1
int Health::GetWound(int n)
{
	m_health -= n;
	ShowHealth();
	return m_health;
}

// 回复血量
int Health::GetHeal(int i)
{
	if (i == 0)
		m_health = HEALTH;
	else
		m_health = (m_health < HEALTH) ? (m_health + 1) : HEALTH;
	ShowHealth();
	return m_health;
}






