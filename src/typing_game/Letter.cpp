#include "Letter.h"

#pragma comment(lib, "winmm.lib") // Ϊ��ʹ��PlaySound����������Ч


LetterShower::LetterShower()
{
	m_score = 0;
	m_delay = 300;
}

// ������ĸ�ĵ����ٶ�
void LetterShower::SetDelay(int d)
{
	m_delay = d;
}

void LetterShower::Wait()
{
	Sleep(m_delay);
}

// ����һ����ĸ������������
void LetterShower::GenerateLetter()
{
	// ���������ĸ�����x����
	Letter l = { 'A' + rand() % 26, rand() % SCR_WIDTH, 1 };
	m_letters[l.letter - 'A'].push_back(l);
}

// ��ĸ����
int LetterShower::Fall()
{
	// ���������������Ԫ��
	for (int i = 0; i < 26; ++i)
	{
		for (auto it = m_letters[i].begin(); it != m_letters[i].end(); )
		{
			// ��������д���Ԫ�أ��ͽ����ԭ����λ�ò���������һ�����»���
			menu.SetCursor(it->x, it->y);
			cout << ' ';

			if (Ground(*it)) // �����ĸ��أ���Ѫ
			{
				if (vty.GetWound() <= 0) // ���Ѫ����Ϊ0
				{
					menu.SetCursor(25, GROUND / 2);
					menu.SetTextColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
					cout << "Game Over!";
					menu.SetTextColor(TextDefault);

					PlaySound(L"..\\sound\\over.wav", NULL, SND_ASYNC | SND_FILENAME);
					return -1; // ��ʾ��Ϸ����
				}

				// ����ص���ĸ���������Ƴ����Ƴ���it���Զ�ָ����һ��Ԫ�أ����Բ���Ҫit++
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
	char ch = 0; // �����û�����
	vector<Letter>::iterator it;
	while (1)
	{
		// ���û���δ���°���ʱ�����ϳ���������ĸ
		while (!_kbhit())
		{
			if (Fall() == -1)
				return; // while(1)��Ψһ����

			Wait();
			// ��ÿ��ѭ����1/3�ĸ��ʵ�������ĸ
			if (rand() % 3 == 0)
				GenerateLetter();
		}

		// �û����°����󣬽����жϣ�������Ӧ����ĸ
		ch = _getch();
		if (ch >= 'a' && ch <= 'z')
		{
			if (!m_letters[ch - 'a'].empty())
			{
				it = m_letters[ch - 'a'].begin();

				menu.SetCursor(it->x, it->y);
				cout << ' ';

				m_letters[ch - 'a'].erase(it); // ɾ��ͷԪ�أ�Ӧ��ʹ��deque����
				PlaySound(L"..\\sound\\m_score.wav", NULL, SND_ASYNC | SND_FILENAME);
				m_score++;

				ShowScore();
			}
		}
	}
}
