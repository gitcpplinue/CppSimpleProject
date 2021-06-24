#include "Letter.h"

#pragma comment(lib, "winmm.lib") // 为了使用PlaySound函数播放音效


LetterShower::LetterShower()
{
	m_score = 0;
	m_delay = 300;
}

// 设置字母的掉落速度
void LetterShower::SetDelay(int d)
{
	m_delay = d;
}

void LetterShower::Wait()
{
	Sleep(m_delay);
}

// 生成一个字母，存入容器中
void LetterShower::GenerateLetter()
{
	// 产生随机字母，随机x坐标
	Letter l = { 'A' + rand() % 26, rand() % SCR_WIDTH, 1 };
	m_letters[l.letter - 'A'].push_back(l);
}

// 字母下落
int LetterShower::Fall()
{
	// 遍历各个容器检查元素
	for (int i = 0; i < 26; ++i)
	{
		for (auto it = m_letters[i].begin(); it != m_letters[i].end(); )
		{
			// 如果容器中存在元素，就将其从原来的位置擦除，在下一行重新绘制
			menu.SetCursor(it->x, it->y);
			cout << ' ';

			if (Ground(*it)) // 如果字母落地，扣血
			{
				if (vty.GetWound() <= 0) // 如果血量减为0
				{
					menu.SetCursor(25, GROUND / 2);
					menu.SetTextColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
					cout << "Game Over!";
					menu.SetTextColor(TextDefault);

					PlaySound(L"..\\sound\\over.wav", NULL, SND_ASYNC | SND_FILENAME);
					return -1; // 表示游戏结束
				}

				// 将落地的字母从容器中移除。移除后it会自动指向下一个元素，所以不需要it++
				it = m_letters[i].erase(it);
				PlaySound(L"..\\sound\\wound.wav", NULL, SND_ASYNC | SND_FILENAME);
				continue;
			}
			it->y++;
			menu.SetCursor(it->x, it->y);
			cout << it->letter;
			it++;
		}
	}
	return 0;
}

void LetterShower::ClearAll()
{
	for (int i = 0; i < 26; ++i)
		if (!m_letters[i].empty())
			m_letters[i].clear();
	m_score = 0;
}

void LetterShower::ShowScore()
{
	menu.SetCursor(0, GROUND + 2);
	cout << "Score: " << m_score << "   ";
}

void LetterShower::Rain()
{
	char ch = 0; // 保存用户按键
	vector<Letter>::iterator it;
	while (1)
	{
		// 当用户还未按下按键时，不断尝试生成字母
		while (!_kbhit())
		{
			if (Fall() == -1)
				return; // while(1)的唯一出口

			Wait();
			// 让每次循环有1/3的概率掉落新字母
			if (rand() % 3 == 0)
				GenerateLetter();
		}

		// 用户按下按键后，进行判断，消除对应的字母
		ch = _getch();
		if (ch >= 'a' && ch <= 'z')
		{
			if (!m_letters[ch - 'a'].empty())
			{
				it = m_letters[ch - 'a'].begin();

				menu.SetCursor(it->x, it->y);
				cout << ' ';

				m_letters[ch - 'a'].erase(it); // 删除头元素，应该使用deque容器
				PlaySound(L"..\\sound\\m_score.wav", NULL, SND_ASYNC | SND_FILENAME);
				m_score++;

				ShowScore();
			}
		}
	}
}

