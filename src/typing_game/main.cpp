#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <queue>
#include <time.h>
#include "Menu.h"
#include "Letter.h"



using namespace std;

#pragma comment(lib, "winmm.lib") // Ϊ��ʹ��PlaySound����������Ч


// --------------------------- ���ڻ��ƽ����ȫ�ֺ��� ---------------------------
void Welcome(); // ��ӭ����
int ShowMenu(); // �Ѷ�ѡ��˵�
void ShowPlayGround(int level); // ��Ϸ���еĽ��棬����1��int���Ͳ��������ж���ǰ���Ѷ�
int GameStart(int level); // ��Ϸ��ʼ���С�����ֵ��0-����������1-������Ϸ��2-�ؿ���Ϸ��3-������Ϸ
int Pause(); // ��ͣ����
void ShowRank(); // ��������



int main()
{
	srand(time(0)); // �����������



	// ����ʾ��ӭ���棬���û���������������ѡ�����
	Welcome();
	_getch();

	char choice = 'y'; // �û���ѡ��
	int level; // �û�ѡ����ѶȵǼ�
	int gret = -1;

	do
	{
		level = ShowMenu();

		// ���ShowMenu()���ɵĽ���
		system("cls");
		// ����ϴ�ls���е�״̬
		ls.ClearAll();
		health.GetHeal(0);

		ShowPlayGround(level);

		while (1)
		{
			gret = GameStart(level);

			if (gret == 0)
			{
				// ��Ϸ������ѯ���û��Ƿ����¿�ʼ
				menu.SetCursor(10, GROUND + 2);
				cout << "Try again?(y/n)";
				cin >> choice;
			}
			else if (gret == 1)
				continue; // ������Ϸ
			else if (gret == 2)
				break; // ����������Ϸ
			else if (gret == 3)
				return 0; // �˳���Ϸ
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



// --------------------------- ���ڻ��ƽ����ȫ�ֺ��� ---------------------------

void Welcome()
{
	menu.SetCursor(17, 10);
	printf("Welcomt To Type Game!");

	menu.SetCursor(17, 12);
	printf("Press any key to continue...");
}

int ShowMenu()
{
	system("cls"); // ���֮ǰ�Ļ�ӭ����

	menu.SetCursor(10, 10);
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
		menu.SetCursor(10, 12);
		printf(" EASY ");
		menu.SetCursor(20, 12);
		printf(" INTERMEDIATE ");
		menu.SetCursor(38, 12);
		printf(" HARD ");

		// ...�ٸ���result��ֵ�жϵ�ǰ��ѡ���ɫ�����������ѡ��
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

		ch = _getch(); // �������ҷ����
		//if (ch == 0)ch = _getch(); ��Ƶ��˵������µ��Ƿ��������1��_getch()���û��޷���ȡ�������ֵ��
	} while (ch != VK_RETURN); // ���»س�����

	return result;
}

void ShowPlayGround(int difficulty)
{
	// ���Ͻ���ʾ��ѡ�Ѷ�
	ls.Level(difficulty);

	// ���Ͻ���ʾѪ��
	health.ShowHealth();

	// �ײ����Ƶ���
	menu.SetCursor(0, GROUND + 1);
	for (int i = 0; i < SCR_WIDTH; ++i)
		cout << '=';

	// �����·���ʾ����
	ls.ShowScore();

	// �ڷ����·���ʾ��ͣ��ʾ
	menu.SetCursor(0, GROUND + 3);
	cout << "( Press \"esc\" To Pause )";
}

int GameStart(int level)
{
	int pret = -1;
	// ��Ϸ��ʼ����
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

	// �·�����ṹ��ShowMenu������ͬ��ͬ�����г�3����ѡ��
	int choice = 0;
	char ch = 0;
	do
	{
		// ʵ�ְ������·�����л�ѡ��
		// Ĭ��ѡ�е�1��
		if (ch == 72)
			choice = (choice + 2) % 3; // +2 = -1 + 3
		if (ch == 80)
			choice = (choice + 1) % 3;

		// �����3��ѡ��...
		menu.SetCursor(25, GROUND / 2 - 2);
		printf(" CONTINUE ");
		menu.SetCursor(25, GROUND / 2);
		printf(" RESTART ");
		menu.SetCursor(25, GROUND / 2 + 2);
		printf(" EXIT ");

		// ...�ٸ���choice��ֵ�жϵ�ǰ��ѡ���ɫ�����������ѡ��
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

		ch = _getch(); // �������·����
	} while (ch != VK_RETURN); // ���»س�����

	return choice;
}

void ShowRank()
{
}