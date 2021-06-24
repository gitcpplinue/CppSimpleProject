#include "Menu.h"

Menu menu;
Vitality vty;


// ------------------- Menu -------------------

Menu::Menu()
{
	system("mode con cols=60 lines=31"); // ���ÿ���̨���ڴ�С
	m_handle = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ��׼����ľ��
}

// ���ù��λ��
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

// ��ʽ��ӭ����
void Menu::Welcome()
{
	SetCursor(17, 10);
	printf("Welcomt To Type Game!");

	SetCursor(17, 12);
	printf("Press any key to continue...");
}

// ��ʽ�Ѷ�ѡ��˵�
int Menu::ShowMenu()
{
	system("cls"); // ���֮ǰ�Ļ�ӭ����

	SetCursor(10, 10);
	printf("Which level do you want to try?");
	int result = 0;
	char ch = 0;

	do
	{
		// ʵ�ְ������ҷ�����л�ѡ��
		// Ĭ��ѡ�е�1��
		if (ch == 75)
			result = (result + 2) % 3; // +2 = -1 + 3
		if (ch == 77)
			result = (result + 1) % 3;

		// �����3��ѡ��...
		SetCursor(10, 12);
		printf(" EASY ");
		SetCursor(20, 12);
		printf(" INTERMEDIATE ");
		SetCursor(38, 12);
		printf(" HARD ");

		// ...�ٸ���result��ֵ�жϵ�ǰ��ѡ���ɫ�����������ѡ��
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

		ch = _getch(); // �������ҷ����
		//if (ch == 0)ch = _getch(); ��Ƶ��˵������µ��Ƿ��������1��_getch()���û��޷���ȡ�������ֵ��
	} while (ch != VK_RETURN); // ���»س�����

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

// ��ʾѪ��
void Vitality::ShowVitality()
{
	menu.SetCursor(SCR_WIDTH * 0.6, 0);
	menu.SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "HP: ";
	for (int i = 0; i < HEALTH; ++i)
	{
		cout << (i < m_health ? "��" : "��");
	}
	menu.SetTextColor(TextDefault);
}

// ����Ѫ��
int Vitality::GetWound(int n)
{
	m_health -= n;
	ShowVitality();
	return m_health;
}

// �ظ�Ѫ��
int Vitality::GetHeal()
{
	m_health = HEALTH;
	ShowVitality();
	return m_health;
}



