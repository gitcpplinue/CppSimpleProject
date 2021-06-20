/*
* һ���ճ���ƻ�ѡ����Ϸ
* ��n����ѡ���ճ����Ϊѡ���ͷ�ڸ���ѡ�������������������ֹͣѭ�����������ɵĽ�ͼѡ���ţ�
* 
* �º�����
*   GetStdHandle����ȡ���롢����������׼�ļ����
*   SetConsoleCursorPosition�����ù���ڿ���̨�е�λ��
* 
* �ջ񣺿���̨�������ƺͽṹ
*   ��1��������������ĺ���
*   ˢ�º���������ù��λ�õĺ��������н������ϸ���޸�
*   system("cls")�����ɽ���������̨��գ�ͨ���ͻ��ƽ���ĺ������ʹ��
*/



#include <iostream>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <vector>
#include <conio.h>

using namespace std;

class RandomChoice
{
private:
    vector<string> option;
    size_t size;
    HANDLE handle_out;
    COORD crd;
    int arrow; // ���浱ǰ��ͷָ��ѡ����±�
    int delay;

public:
    RandomChoice(vector<string> strs)
    {
        size = strs.size();
        arrow = 0;

        for (string str : strs)
            option.push_back(str);

        // GetStdHandle:���ָ����׼�豸�ľ������׼���롢��������� OUTPUT��INTPUT��ERROR��
        handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
        crd.X = 8;  // ��ͷ��->���Ŀ�ʼλ��
        crd.Y = 4 + (arrow << 1);  // ��һ��ѡ����кţ���5��

    }

    void Start()
    {
        printf("\n������Ļ������ʲô��������ѡ��ɡ�\n\n\n");
        for (int i = 0; i < size; ++i)
            printf("\t  %s\n\n", option[i].c_str());
    }

    void Refresh()
    {
        // ������һ������ļ�ͷ��->��
        SetConsoleCursorPosition(handle_out, crd); 
        cout << "  ";

        // ����Y���꣬���»���ͷ
        arrow = (arrow + 1) % size;
        crd.Y = 4 + (arrow << 1); // ÿ��ѡ����1�У��кŲ�Ϊ2��y=4+2x
        SetConsoleCursorPosition(handle_out, crd);
        cout << "->";
    }

    // ˢ�µ���ʱʱ��
    int SetDelay(int var) { return delay = var; }
    void Wait() { Sleep(delay); }

    int Play()
    {
        while (!_kbhit()) // ����û��Ƿ��¼��̣�������
        {
            Refresh();
            Wait();
        }
        return arrow;
    }

    void ShowResult()
    {
        crd.Y = 18; // ���·�������Զ�ĵط�������
        SetConsoleCursorPosition(handle_out, crd);
        cout << option[arrow] << endl;
    }

};

int main()
{
    RandomChoice rc({ "����Ӱ", "д����", "�乫԰", "�ʹ���̫̫Լ��", "˯����" });

    rc.SetDelay(20);

    char choice;
    do
    {
        system("cls"); // �����ϴ�����Ľ��
        rc.Start(); // ���»��ƽ���

        rc.Play();
        rc.ShowResult();
        _getch(); // �̵�ʹPlay()����ֹͣ���ַ�����ֹӰ��while���ж�
        cout << "try again?" << endl;
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}
