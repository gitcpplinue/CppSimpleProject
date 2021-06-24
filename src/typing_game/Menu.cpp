#include "Menu.h"

Menu menu;
Vitality vty;


// ------------------- Menu -------------------

Menu::Menu()
{
	system("mode con cols=60 lines=31"); // 设置控制台窗口大小
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

// 显式欢迎界面
void Menu::Welcome()
{
	SetCursor(17, 10);
	printf("Welcomt To Type Game!");

	SetCursor(17, 12);
	printf("Press any key to continue...");
}

// 显式难度选择菜单
int Menu::ShowMenu()
{
	system("cls"); // 清除之前的欢迎界面

	SetCursor(10, 10);
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
		SetCursor(10, 12);
		printf(" EASY ");
		SetCursor(20, 12);
		printf(" INTERMEDIATE ");
		SetCursor(38, 12);
		printf(" HARD ");

		// ...再根据result的值判断当前所选项，换色后重新输出该选项
		switch (result)
		{
		case 0:
			SetTextColor(TextSelect);
			SetCursor(10, 12);
			printf(" EASY ");
			break;
		case 1:
			SetTextColor(TextSelect);
			SetCursor(20, 12);
			printf(" INTERMEDIATE ");
			break;
		case 2:
			SetTextColor(TextSelect);
			SetCursor(38, 12);
			printf(" HARD ");
			break;
		default:

			break;
		}
		SetTextColor(TextDefault);

		ch = _getch(); // 捕获左右方向键
		//if (ch == 0)ch = _getch(); 视频中说如果按下的是方向键，仅1次_getch()调用还无法获取方向键的值。
	} while (ch != VK_RETURN); // 按下回车结束

	return result;
}

void Menu::DrawGround()
{
	SetCursor(0, GROUND + 1);

	for (int i = 0; i < SCR_WIDTH; ++i)
		cout << '=';
}




// ------------------- Vitality -------------------

Vitality::Vitality()
{
	m_health = HEALTH;
}

// 显示血量
void Vitality::ShowVitality()
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

// 减少血量
int Vitality::GetWound(int n)
{
	m_health -= n;
	ShowVitality();
	return m_health;
}

// 回复血量
int Vitality::GetHeal()
{
	m_health = HEALTH;
	ShowVitality();
	return m_health;
}



