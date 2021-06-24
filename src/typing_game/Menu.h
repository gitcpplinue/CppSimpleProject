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
class Menu
{
private:
	HANDLE m_handle;
	COORD m_crd;

public:
	Menu();

	// ���ù��λ��
	void SetCursor(int x, int y);

	// ����������ɫ��ֻ��ʡ����SetConsoleTextAttribute�ĵ�1������
	void SetTextColor(WORD wAttributes);

	// ��ʽ��ӭ����
	void Welcome();

	// ��ʽ�Ѷ�ѡ��˵�
	int ShowMenu(); 

	// ���Ƶ���
	void DrawGround();
};


// ����Ѫ������ʽ�����١��ָ�
class Vitality
{
private:
	int m_health; // ʣ��Ѫ��

public:
	Vitality();

	// ��ʾѪ��
	void ShowVitality();

	// ����Ѫ��
	int GetWound(int n = 1);

	// �ظ�Ѫ��
	int GetHeal();
};

extern Menu menu;
extern Vitality vty;


