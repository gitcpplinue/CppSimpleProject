#include "Letter.h"

#pragma comment(lib, "winmm.lib") // 为了使用PlaySound函数播放音效

LetterShower ls;

LetterShower::LetterShower()
{
	m_delay = 300;
	m_score = 0;
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
		// 让所有在界面中显示的字母下降一位
		for (auto it = m_letters[i].begin(); it != m_letters[i].end(); )
		{
			// 如果容器中存在元素（在界面中显示），就将其从原来的位置擦除，在下一行重新绘制
			menu.SetCursor(it->x, it->y);
			cout << ' ';

			if (Ground(*it)) // 如果字母落地，扣血
			{
				int iret = health.GetWound();
				if (iret <= 0) // 如果血量减为0，结束
				{
					menu.SetCursor(25, GROUND / 2);
					menu.SetTextColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
					cout << "Game Over!";
					menu.SetTextColor(TextDefault);

					PlaySound(L"..\\sound\\over.wav", NULL, SND_ASYNC | SND_FILENAME);
					return -1; // 表示游戏结束
				}

				// 若一个容器中有多个元素，首先落地的肯定是队首元素
				m_letters[i].pop_front();
				// 调用pop_front()时it还指向队首元素，会导致迭代器失效，得重新赋值
				it = m_letters[i].begin();
				PlaySound(L"..\\sound\\wound.wav", NULL, SND_ASYNC | SND_FILENAME);
				continue;
			}

			// 将字母下移一行
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

void LetterShower::Level(int select)
{

	menu.SetCursor(0, 0);
	switch (select)
	{
	case 0:
		printf("Level: EASY ");
		SetDelay(300);
		break;
	case 1:
		printf("Level: INTERMEDIATE ");
		SetDelay(200);
		break;
	case 2:
		printf("Level: HARD ");
		SetDelay(100);
		break;
	default:
		printf("Level: EASY ");
		SetDelay(300);
		break;
	}
}

void LetterShower::ShowScore()
{
	menu.SetCursor(0, GROUND + 2);
	cout << "Score: " << m_score << "   ";
}

int LetterShower::Rain()
{
	char ch = 0; // 保存用户按键
	Letter letter;
	while (1)
	{
		// 当用户还未按下按键时，不断尝试生成字母
		while (!_kbhit())
		{
			if (Fall() == -1)
				return 0; // 一轮游戏结束

			Wait();
			// 让每次循环有1/3的概率掉落新字母
			if (rand() % 3 == 0)
				GenerateLetter();
		}

		// 用户按下按键后，进行判断，消除对应的字母
		// 如果容器中有多个元素，删除队头元素（若界面中一个字母出现多次，消除最下方的字母）
		ch = _getch();
		if (ch >= 'a' && ch <= 'z')
		{
			if (!m_letters[ch - 'a'].empty())
			{
				// 根据键盘按下的字母，将对应的deque容器的队首从屏幕中清除
				letter = m_letters[ch - 'a'].front();
				menu.SetCursor(letter.x, letter.y);
				cout << ' ';

				m_letters[ch - 'a'].pop_front(); // 删除头元素
				PlaySound(L"..\\sound\\m_score.wav", NULL, SND_ASYNC | SND_FILENAME);

				m_score++;
				ShowScore();
			}
		}
		else if (ch == VK_ESCAPE) // 按下“esc”进入暂停界面
			return 1; 
	}
	return 0;
}

