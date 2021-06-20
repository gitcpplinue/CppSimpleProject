/*
* 一个日常活动计划选择游戏
* 有n个可选的日常活动作为选项，箭头在各个选项中往复，按下任意键停止循环（类似贴吧的截图选老婆）
* 
* 新函数：
*   GetStdHandle：获取输入、输出、错误标准文件句柄
*   SetConsoleCursorPosition：设置光标在控制台中的位置
* 
* 收获：控制台界面的设计和结构
*   有1个绘制整个界面的函数
*   刷新函数配合设置光标位置的函数对已有界面进行细节修改
*   system("cls")函数可将整个控制台清空，通常和绘制界面的函数配合使用
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
    int arrow; // 保存当前箭头指向选项的下标
    int delay;

public:
    RandomChoice(vector<string> strs)
    {
        size = strs.size();
        arrow = 0;

        for (string str : strs)
            option.push_back(str);

        // GetStdHandle:获得指定标准设备的句柄（标准输入、输出、错误 OUTPUT、INTPUT、ERROR）
        handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
        crd.X = 8;  // 箭头“->”的开始位置
        crd.Y = 4 + (arrow << 1);  // 第一个选项的行号，第5行

    }

    void Start()
    {
        printf("\n您今天的活动安排是什么？来做个选择吧。\n\n\n");
        for (int i = 0; i < size; ++i)
            printf("\t  %s\n\n", option[i].c_str());
    }

    void Refresh()
    {
        // 擦掉上一次输出的箭头“->”
        SetConsoleCursorPosition(handle_out, crd); 
        cout << "  ";

        // 更新Y坐标，重新画箭头
        arrow = (arrow + 1) % size;
        crd.Y = 4 + (arrow << 1); // 每个选项间隔1行，行号差为2。y=4+2x
        SetConsoleCursorPosition(handle_out, crd);
        cout << "->";
    }

    // 刷新的延时时间
    int SetDelay(int var) { return delay = var; }
    void Wait() { Sleep(delay); }

    int Play()
    {
        while (!_kbhit()) // 检测用户是否按下键盘，不阻塞
        {
            Refresh();
            Wait();
        }
        return arrow;
    }

    void ShowResult()
    {
        crd.Y = 18; // 在下方离界面较远的地方输出结果
        SetConsoleCursorPosition(handle_out, crd);
        cout << option[arrow] << endl;
    }

};

int main()
{
    RandomChoice rc({ "看电影", "写代码", "逛公园", "和春田太太约会", "睡懒觉" });

    rc.SetDelay(20);

    char choice;
    do
    {
        system("cls"); // 清理上次输出的结果
        rc.Start(); // 重新绘制界面

        rc.Play();
        rc.ShowResult();
        _getch(); // 吞掉使Play()函数停止的字符，防止影响while的判断
        cout << "try again?" << endl;
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}
