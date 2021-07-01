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

MyDB g_db;
Record g_rec;
LetterShower g_ls;

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
		g_ls.ClearAll();
		health.GetHeal(0);

		ShowPlayGround(level);
		g_rec.SetLevel(level);

		bool flag = 0; // ����������Ϸ������ֹ(flag == 1)����ͨ����ͣ�������¿�ʼ(flag == 0)
		while (1)
		{
			gret = GameStart(level);
			

			if (gret == 0) // ��Ϸ�����������˳��ڲ�whileѭ��
			{
				flag = 1;
				g_rec.SetScore(g_ls.GetScore());
				g_db.Connect();
				g_db.AddRecord(g_rec.GetScore(), g_rec.GetLevel());
				g_db.Close();
				//rec.WriteRecord();
				break;
			}
			else if (gret == 1) // ��ͣ-������Ϸ
				continue; 
			else if (gret == 2) // ��ͣ-����������Ϸ���˳��ڲ�whileѭ��
			{
				// ��¼������Ϸ��Ϣ
				g_rec.SetScore(g_ls.GetScore());
				g_db.Connect();
				g_db.AddRecord(g_rec.GetScore(), g_rec.GetLevel());
				g_db.Close();
				//rec.WriteRecord();
				flag = 0;
				break; 
			}
			else if (gret == 3) // ��ͣ-�˳���Ϸ
			{
				// ��¼������Ϸ��Ϣ
				g_rec.SetScore(g_ls.GetScore());
				g_db.Connect();
				g_db.AddRecord(g_rec.GetScore(), g_rec.GetLevel());
				g_db.Close();
				//rec.WriteRecord();

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
	g_ls.Level(difficulty);

	// ���Ͻ���ʾѪ��
	health.ShowHealth();

	// �ײ����Ƶ���
	menu.SetCursor(0, GROUND + 1);
	for (int i = 0; i < SCR_WIDTH; ++i)
		cout << '=';

	// �����·���ʾ����
	g_ls.ShowScore();

	// �ڷ����·���ʾ��ͣ��ʾ
	menu.SetCursor(0, GROUND + 3);
	cout << "( Press \"esc\" To Pause )";
}

int GameStart(int level)
{
	int pret = -1; // Pause()�����ķ���ֵ

	// ��Ϸ��ʼ����
	if (g_ls.Rain() == 1)
		pret = Pause();

	switch (pret)
	{
	case 0: // ������Ϸ
		system("cls");
		ShowPlayGround(level);
		return 1;
	case 1: // �ؿ�
		return 2;
	case 2: // �˳�
		return 3;
	default: // ��Ϸ��������
		return 0;
	}
}

// ����ֵ��0����������1�����ؿ���2�����˳�
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

// ���Ż�����base = 0;�������˰��¡��͡����⣬�������е�ѡ�ѡ�ж�Ҫ��base���㡣
void ShowRank()
{
	vector<vector<Record>> records(3);

	char ch = 0; // ��ȡ����

	int level = 0; // �Ѷȣ�0�����򵥡�1�����еȡ�2��������

	bool arsc = false; // Ĭ�Ͻ�������
	bool order_by_s = true; // Ĭ�ϰ���������

	char state1; // ��ʾ��ǰ���������
	char state2;

	int max = 0; // ��ǰ��¼�е����ֵ

	int base = 0; // ����ʵ�ַ�ҳ����
	const int a_page = 13; // һ�������ʾ13����¼
	int pages = 1; // ��ǰ�ļ�¼����Ҫ��Ϊ����ҳ

	//rec.ReadRecord(records);

	g_db.Connect();
	do
	{
		system("cls"); 

		// ������ʾ
		menu.SetCursor(0, 1);
		printf("��/��: change level    ��/��: previous/next page\n");
		printf("r/d: change order    s/t: order by score/time    q: quit");

		// �ָ���
		menu.SetCursor(0, 3);
		for (int i = 0; i < SCR_WIDTH; ++i)
			cout << '=';

		// ������
		menu.SetCursor(SCR_WIDTH / 5, 4);
		printf("Score");
		menu.SetCursor(SCR_WIDTH / 5 * 2, 4);
		printf("Date");


		// ʵ�ְ������ҷ�����л���ʾ���Ѷȼ�¼
		// Ĭ����ʾ���Ѷ��µļ�¼
		if (ch == 75)
		{
			level = (level + 2) % 3; // +2 = -1 + 3
			base = 0; 
		}
		if (ch == 77)
		{
			level = (level + 1) % 3;
			base = 0;
		}
		// ��ѡ����Ѷ���ʾ�����Ͻ�
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

		// �л����ݵ����й���: ���ݷ���/���� ��/�������С�
		if (ch == 'r')
		{
			arsc = true;
			base = 0;
		}
		else if (ch == 'd')
		{
			arsc = false;
			base = 0;
		}

		if (ch == 's')
		{
			order_by_s = true;
			base = 0;
		}
		else if (ch == 't')
		{
			order_by_s = false;
			base = 0;
		}
		// ��ʾ�������
		state1 = (order_by_s ? 's' : 't');
		state2 = (arsc ? 'r' : 'd');
		menu.SetCursor(SCR_WIDTH * 0.8, 4);
		printf("(%c/%c)", state1, state2);

		// �����ݿ��ȡ����
		if (order_by_s)
		{
			if (!arsc)
				g_db.GetRecordByScoreDesc(records[level], level);
			else
				g_db.GetRecordByScoreAsc(records[level], level);
		}
		else
		{
			if (!arsc)
				g_db.GetRecordByDateDesc(records[level], level);
			else
				g_db.GetRecordByDateAsc(records[level], level);
		}


		pages = records[level].size() / 13 + 1;
		if (ch == 72) // ��
			base = (base - 1 + pages) % pages;
		if (ch == 80) // ��
			base = (base + 1) % pages;

		max = 0;
		// �������е�������ʾ����Ļ��
		for (int i = base * a_page, j = 0; i < records[level].size() && i < base * a_page + a_page; ++i, ++j)
		{
			int record = records[level][i].GetScore();
			menu.SetCursor(SCR_WIDTH / 5, 6 + j * 2);
			printf("%d", record);
			menu.SetCursor(SCR_WIDTH / 5 * 2, 6 + j * 2);
			printf("%s", records[level][i].GetDate());

			max = (record > max ? record : max);
		}

		// ��ʾ��ǰ�Ѷȵ���߷�
		if (max != 0)
		{
			menu.SetCursor(SCR_WIDTH * 0.65, 0);
			printf("Highest score : %d", max);
		}

		ch = _getch(); // �������ҷ����
	} while (ch != 'q' && ch != 'Q'); // ����q�ص��Ѷ�ѡ�����
	g_db.Close();

	// �˳��������棬�ص��Ѷ�ѡ������Ҫ���»��ƽ���
	system("cls");
	menu.SetCursor(10, 10);
	printf("Which level do you want to try?");
	menu.SetCursor(10, 14);
	printf("��/��: select difficulty");
	menu.SetCursor(10, 15);
	printf("r: show ranks");
	menu.SetCursor(10, 16);
	printf("e: exit");
}
