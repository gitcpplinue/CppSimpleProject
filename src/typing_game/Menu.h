#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <queue>
#include <time.h>

using namespace std;


// ��ѡ�е�ѡ����ɫ
#define TextSelect BACKGROUND_GREEN
// Ĭ�ϵ�������ʽ
#define TextDefault FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

const int GROUND = 27;
const int SCR_WIDTH = 60;
const int HEALTH = 5;




// ����������
// ӵ��һ��ȫ�ֱ�������������Ҫ���ù��λ�ö�Ҫͨ��Menu���Ա��������ȡ
class Menu
{
private:
	HANDLE m_handle; // ��ȡ����̨��׼����ľ��
	COORD m_crd; // ����̨�������

public:
	Menu();

	// ���ù��λ��
	void SetCursor(int x, int y);

	// ����������ɫ��ֻ��ʡ����SetConsoleTextAttribute�ĵ�1������
	void SetTextColor(WORD wAttributes);
};

// ����Ѫ������ʽ�����١��ָ�
class Health
{
private:
	int m_health; // ʣ��Ѫ��

public:
	Health();

	// ��ʾѪ��
	void ShowHealth();

	// ����Ѫ����Ĭ���˺�Ϊ1
	int GetWound(int n = 1);

	// �ظ�Ѫ����i=0��Ѫ��������i=1ֻ��1��Ѫ
	int GetHeal(int i);
};



extern Menu menu;
extern Health health;

