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

void Level(int select, LetterShower& ls);

int main()
{
	srand(time(0)); // �����������

	// ����ʾ��ӭ���棬���û���������������ѡ�����
	menu.Welcome();
	_getch();

	char choice; // �û���ѡ��
	LetterShower ls;
	int level; // �û�ѡ����ѶȵǼ�

	do
	{
		level = menu.ShowMenu();

		// ���ShowMenu()���ɵĽ���
		system("cls");
		// ����ϴ�ls���е�״̬
		ls.ClearAll();
		vty.GetHeal();

		// ��ʾѡȡ���Ѷ�
		Level(level, ls);
		// ��ʾ����
		menu.DrawGround();
		// ��ʾ����ֵ
		vty.ShowVitality();
		// ��ʾ�÷֣�0��
		ls.ShowScore();

		// ��Ϸ��ʼ����
		ls.Rain();

		// ��Ϸ������ѯ���û��Ƿ����¿�ʼ
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


