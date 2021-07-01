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

	// 添加一条记录
	void AddRecord(int score, int level);

	// 获取排名信息
	// 按分数升序排序
	void GetRecordByScoreAsc(vector<Record> vec, int level);
	// 按分数降序排序
	void GetRecordByScoreDesc(vector<Record> vec, int level);
	// 按日期升序排序
	void GetRecordByDateAsc(vector<Record> vec, int level);
	// 按日期降序排序
	void GetRecordByDateDesc(vector<Record> vec, int level);

	void Clean();
};

