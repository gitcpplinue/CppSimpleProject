// 引入MyDB类后，Record类用于保存游戏进行时的分数状态，不再负责数据的读写

#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <deque>
#include <time.h>
#include <fstream>
#include "Menu.h"


using namespace std;

class Record
{
private:
	int m_score;
	int m_level;
	char m_date[20];

	string getDate();
public:
	Record();
	Record(int score, int level, string date);

	void SetScore(int i) { m_score = i; }
	void SetLevel(int i) { m_level = i; }

	int GetScore() { return m_score; }
	int GetLevel() { return m_level; }
	const char* GetDate() { return m_date; }


	void WriteRecord();

	void ReadRecord(vector<vector<Record>>& records);

};

