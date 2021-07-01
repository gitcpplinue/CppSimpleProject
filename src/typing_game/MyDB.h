#pragma once
#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include "..\include\mysql.h"
#include "Record.h" 


using namespace std;

class Record;

class MyDB
{
private:
	MYSQL mySql;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

public:
	MyDB();
	~MyDB();

	void Init();

	// ���һ����¼
	void AddRecord(int score, int level);

	// ��ȡ������Ϣ
	// ��������������
	void GetRecordByScoreAsc(vector<Record> vec, int level);
	// ��������������
	void GetRecordByScoreDesc(vector<Record> vec, int level);
	// ��������������
	void GetRecordByDateAsc(vector<Record> vec, int level);
	// �����ڽ�������
	void GetRecordByDateDesc(vector<Record> vec, int level);

	void Clean();
};

