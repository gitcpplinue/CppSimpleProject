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

#pragma comment(lib, "winmm.lib") // Ϊ��ʹ��PlaySound����������Ч


// --------------------------- ���ڻ��ƽ����ȫ�ֺ��� ---------------------------
void Welcome(); // ��ӭ����
int ShowMenu(); // �Ѷ�ѡ��˵�
void ShowPlayGround(int level); // ��Ϸ���еĽ��棬����1��int���Ͳ��������ж���ǰ���Ѷ�
int GameStart(int level); // ��Ϸ��ʼ���С�����ֵ��0-����������1-������Ϸ��2-�ؿ���Ϸ��3-������Ϸ
int Pause(); // ��ͣ����
void ShowRank(); // ��������

/*
int main()
{
	char choice = 'y'; // �û���ѡ��
	int level; // �û�ѡ����Ѷ�
	int gret = -1;
	


	srand(time(0)); // �����������

	// ����ʾ��ӭ���棬���û���������������ѡ�����
	Welcome();
	_getch();

	do
	{
		level = ShowMenu();

		// ���ShowMenu()���ɵĽ���
		system("cls");
		// ����ϴ�ls���е�״̬
		ls.ClearAll();
		health.GetHeal(0);

		ShowPlayGround(level);
		rec.SetLevel(level);

		bool flag = 0; // ����������Ϸ������ֹ(flag == 1)����ͨ����ͣ�������¿�ʼ(flag == 0)
		while (1)
		{
			gret = GameStart(level);

			if (gret == 0) // ��Ϸ�����������˳��ڲ�whileѭ��
			{
				flag = 1;
				rec.SetScore(ls.GetScore());
				rec.WriteRecord();
				break;
			}
			else if (gret == 1) // ��ͣ-������Ϸ
				continue; 
			else if (gret == 2) // ��ͣ-����������Ϸ���˳��ڲ�whileѭ��
			{
				// ��¼������Ϸ��Ϣ
				rec.SetScore(ls.GetScore());
				rec.WriteRecord();
				flag = 0;
				break; 
			}
			else if (gret == 3) // ��ͣ-�˳���Ϸ
			{
				// ��¼������Ϸ��Ϣ
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
	menu.SetCursor(10, 14);
	printf("��/��: select difficulty");
	menu.SetCursor(10, 15);
	printf("r: show ranks");
	menu.SetCursor(10, 16);
	printf("e: exit");

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
		if (ch == 'r')
			ShowRank();
		if (ch == 'e')
			exit(0);

		// ����ʾ3��ѡ��...
		menu.SetCursor(10, 12);
		printf(" EASY ");
		menu.SetCursor(20, 12);
		printf(" INTERMEDIATE ");
		menu.SetCursor(38, 12);
		printf(" HARD ");

		// ...�ٸ���result��ֵ�жϵ�ǰ��ѡ���ɫ��������ʾ��ѡ��
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
	vector<vector<Record>> records(3);
	char ch = 0;
	int level = 0;
	int max = 0;
	rec.ReadRecord(records);

	do
	{
		system("cls"); 

		menu.SetCursor(0, 1);
		printf("��/��: switch page    q: back to menu");


		// �ָ���
		menu.SetCursor(0, 2);
		for (int i = 0; i < SCR_WIDTH; ++i)
			cout << '=';

		menu.SetCursor(SCR_WIDTH / 5, 3);
		printf("Score");
		menu.SetCursor(SCR_WIDTH / 5 * 2, 3);
		printf("Date");

		// ʵ�ְ������ҷ�����л���ʾ���Ѷȼ�¼
		// Ĭ����ʾ���Ѷ��µļ�¼
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

		ch = _getch(); // �������ҷ����
	} while (ch != 'q' && ch != 'Q'); // ����q�ص��Ѷ�ѡ�����

	// �˳����ص��Ѷ�ѡ������Ҫ���»��ƽ���
	system("cls");
	menu.SetCursor(10, 10);
	printf("Which level do you want to try?");
	menu.SetCursor(10, 14);
	printf("��/��: select difficulty");
	menu.SetCursor(10, 15);
	printf("r: show ranks");
}
