#include "MyDB.h"

MyDB::MyDB()
{
}

MyDB::~MyDB()
{
    if (sql_result != NULL)
        mysql_free_result(sql_result);
    mysql_close(&mySql);
}

// ����������ȡDB����
void MyDB::Connect()
{
    const char user[] = "root";
    const char pswd[] = "123456";
    const char host[] = "localhost";
    const char database[] = "db_test";
    unsigned int port = 3306;
    int ret;

    mysql_init(&mySql);
    if (mysql_real_connect(&mySql, host, user, pswd, database, port, 0, 0) == NULL)
    {
        cout << "connect failed!" << endl;
        fprintf(stderr, "Failed to connect to database: Error: %s\n",
            mysql_error(&mySql));
    }
}

void MyDB::AddRecord(int score, int level)
{
    int ret;
    char sql_add[100] = { 0 };
    sprintf_s(sql_add, "INSERT INTO records (score, level, date_t) \
        VALUES \
        (%d, %d, now())", score, level);
    
    ret = mysql_query(&mySql, sql_add);  // sql���
    if (ret) 
    {
        cout << "query sql failed!" << endl;
        fprintf(stderr, "Failed to connect to database: Error: %s\n",
            mysql_error(&mySql));
    }
}

void MyDB::GetRecordByScoreAsc(vector<Record>& vec, int level)
{
    int ret;
    char sql_select_sa[150] = { 0 };
    sprintf_s(sql_select_sa, "SELECT score,level,date_t \
        FROM records \
        WHERE level=%d \
        ORDER BY score \
        ASC", level);

    ret = mysql_query(&mySql, sql_select_sa);  // sql���
    if (!ret) // ���Ϊ0��ʾ�ɹ�
    {
        sql_result = mysql_store_result(&mySql); // ��ò�ѯ���
        if (sql_result)
        {
            // ���vec����
            vec.clear();
            while (sql_row = mysql_fetch_row(sql_result)) // �Ӳ�ѯ��������л�ȡ����
            {
                // ʹ��ÿһ�е���������һ��Record���󣬲���vec������
                vec.push_back({ atoi(sql_row[0]), atoi(sql_row[1]), sql_row[2] });
            }
        }
    }
    else
    {
        cout << "query sql failed!" << endl;
        fprintf(stderr, "Failed to connect to database: Error: %s\n",
            mysql_error(&mySql));
    }
}

void MyDB::GetRecordByScoreDesc(vector<Record>& vec, int level)
{
    int ret;
    char sql_select_sd[150] = { 0 };
    sprintf_s(sql_select_sd, "SELECT score,level,date_t \
        FROM records \
        WHERE level=%d \
        ORDER BY score \
        DESC", level);

    ret = mysql_query(&mySql, sql_select_sd);  // sql���
    if (!ret) // ���Ϊ0��ʾ�ɹ�
    {
        sql_result = mysql_store_result(&mySql); // ��ò�ѯ���
        if (sql_result)
        {
            // ���vec����
            vec.clear();
            while (sql_row = mysql_fetch_row(sql_result)) // �Ӳ�ѯ��������л�ȡ����
            {
                // ʹ��ÿһ�е���������һ��Record���󣬲���vec������
                vec.push_back({ atoi(sql_row[0]), atoi(sql_row[1]), sql_row[2] });
            }
        }
    }
    else
    {
        cout << "query sql failed!" << endl;
        fprintf(stderr, "Failed to connect to database: Error: %s\n",
            mysql_error(&mySql));
    }
}

void MyDB::GetRecordByDateAsc(vector<Record>& vec, int level)
{
    int ret;
    char sql_select_da[150] = { 0 };
    sprintf_s(sql_select_da, "SELECT score,level,date_t \
        FROM records \
        WHERE level=%d \
        ORDER BY date_t  \
        ASC", level);

    ret = mysql_query(&mySql, sql_select_da);  // sql���
    if (!ret) // ���Ϊ0��ʾ�ɹ�
    {
        sql_result = mysql_store_result(&mySql); // ��ò�ѯ���
        if (sql_result)
        {
            // ���vec����
            vec.clear();
            while (sql_row = mysql_fetch_row(sql_result)) // �Ӳ�ѯ��������л�ȡ����
            {
                // ʹ��ÿһ�е���������һ��Record���󣬲���vec������
                vec.push_back({ atoi(sql_row[0]), atoi(sql_row[1]), sql_row[2] });
            }
        }
    }
    else
    {
        cout << "query sql failed!" << endl;
        fprintf(stderr, "Failed to connect to database: Error: %s\n",
            mysql_error(&mySql));
    }
}

void MyDB::GetRecordByDateDesc(vector<Record>& vec, int level)
{
    int ret;
    char sql_select_dd[150] = { 0 };
    sprintf_s(sql_select_dd, "SELECT score,level,date_t \
        FROM records \
        WHERE level=%d \
        ORDER BY date_t \
        DESC", level);

    ret = mysql_query(&mySql, sql_select_dd);  // sql���
    if (!ret) // ���Ϊ0��ʾ�ɹ�
    {
        sql_result = mysql_store_result(&mySql); // ��ò�ѯ���
        if (sql_result)
        {
            // ���vec����
            vec.clear();
            while (sql_row = mysql_fetch_row(sql_result)) // �Ӳ�ѯ��������л�ȡ����
            {
                // ʹ��ÿһ�е���������һ��Record���󣬲���vec������
                vec.push_back({ atoi(sql_row[0]), atoi(sql_row[1]), sql_row[2] });
            }
        }
    }
    else
    {
        cout << "query sql failed!" << endl;
        fprintf(stderr, "Failed to connect to database: Error: %s\n",
            mysql_error(&mySql));
    }
}

void MyDB::Clean()
{
    int ret;
    char sql_clean[30] = { 0 };
    sprintf_s(sql_clean, "DELETE FROM records ");

    ret = mysql_query(&mySql, sql_clean);  // sql���
    if (ret)
    {
        cout << "query sql failed!" << endl;
        fprintf(stderr, "Failed to connect to database: Error: %s\n",
            mysql_error(&mySql));
    }
}
