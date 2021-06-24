#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <queue>
#include <time.h>
#include "Menu.h"
using namespace std;

// ��ĸ��������
struct Letter
{
	char letter;
	int x;
	int y;
};

// ������ĸ�����ɡ�����
class LetterShower
{
private:
	vector<Letter> m_letters[26]; // ÿ����ĸ1������
	int m_score; // ����
	int m_delay; // ��ĸ���µ��ٶ�

	// �ж���ĸ�Ƿ��䵽�˵���
	bool Ground(Letter l) { return l.y >= GROUND; }

public:
	LetterShower();

	// ������ĸ�ĵ����ٶ�
	void SetDelay(int d);
	void Wait();

	// ����һ����ĸ������������
	void GenerateLetter();
	
	// ��ĸ���䣬����"-1"��ζ����Ϸ����
	int Fall();

	// �������
	void ClearAll();

	// ��ʾ����
	void ShowScore();

	// ��Ϸ��ʼ
	// ����ִ��Fall����������ĸ�������䣬��׽�û��İ�����������Ӧ����ĸ
	void Rain();
};

