#include "Record.h"

Record rec;

string Record::getDate()
{
	SYSTEMTIME lt;
	GetLocalTime(&lt);
	char date[50] = { 0 };

	sprintf_s(date, "%d/%02d/%02d %02d:%02d:%02d",
		lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond);

	string str = date;
	return str;
}

Record::Record()
{
	m_score = 0;
	m_level = 0;
	memset(m_date, 0, sizeof(m_date));
}

void Record::WriteRecord()
{
	if (m_score == 0)
		return;

	ofstream ofs("..\\.type_game_record", ios::app | ios::binary);
	if (!ofs)
	{
		perror("open file");
		return;
	}
	string str = getDate(); 
	memcpy_s(m_date, sizeof(m_date), str.c_str(), str.length());

	ofs.write((char*)this, sizeof(Record));
	//ofs.write((char*)this, sizeof(*this));
	ofs.close();
}

void Record::ReadRecord(vector<vector<Record>>& records)
{
	ifstream ifs("..\\.type_game_record", ios::in | ios::binary);
	Record temp;
	int level;

	if (!ifs)
	{
		perror("open file");
		return;
	}

	while (1)
	{
		ifs.read((char*)&temp, sizeof(Record));
		if (ifs.eof())
			break;

		level = temp.GetLevel();
		switch (level)
		{
		case 0:
			records[0].push_back(temp);
			break;
		case 1:
			records[1].push_back(temp);
			break;
		case 2:
			records[2].push_back(temp);
			break;
		default:
			break;
		}
	}

	ifs.close();
}
