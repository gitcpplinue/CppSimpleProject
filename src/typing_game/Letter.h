#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <deque>
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
	deque<Letter> m_letters[26]; // ÿ����ĸ1������
	int m_delay; // ��ĸ���µ��ٶ�
	int m_score;

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

	// ��ʾ�������Ѷ�
	void Level(int select);

	// ��ʾ��ǰ����
	void ShowScore();

	// ��Ϸ��ʼ
	// ����ִ��Fall����������ĸ�������䣬��׽�û��İ�����������Ӧ����ĸ
	// return 0 һ����Ϸ������return 1 ������ͣ���档
	int Rain();
};

extern LetterShower ls;