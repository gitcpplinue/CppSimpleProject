#include "Letter.h"

#pragma comment(lib, "winmm.lib") // Ϊ��ʹ��PlaySound����������Ч

LetterShower ls;

LetterShower::LetterShower()
{
	m_delay = 300;
	m_score = 0;
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
		// �������ڽ�������ʾ����ĸ�½�һλ
		for (auto it = m_letters[i].begin(); it != m_letters[i].end(); )
		{
			// ��������д���Ԫ�أ��ڽ�������ʾ�����ͽ����ԭ����λ�ò���������һ�����»���
			menu.SetCursor(it->x, it->y);
			cout << ' ';

			if (Ground(*it)) // �����ĸ��أ���Ѫ
			{
				int iret = health.GetWound();
				if (iret <= 0) // ���Ѫ����Ϊ0������
				{
					menu.SetCursor(25, GROUND / 2);
					menu.SetTextColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
					cout << "Game Over!";
					menu.SetTextColor(TextDefault);

					PlaySound(L"..\\sound\\over.wav", NULL, SND_ASYNC | SND_FILENAME);
					return -1; // ��ʾ��Ϸ����
				}

				// ��һ���������ж��Ԫ�أ�������صĿ϶��Ƕ���Ԫ��
				m_letters[i].pop_front();
				// ����pop_front()ʱit��ָ�����Ԫ�أ��ᵼ�µ�����ʧЧ�������¸�ֵ
				it = m_letters[i].begin();
				PlaySound(L"..\\sound\\wound.wav", NULL, SND_ASYNC | SND_FILENAME);
				continue;
			}

			// ����ĸ����һ��
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
	char ch = 0; // �����û�����
	Letter letter;
	while (1)
	{
		// ���û���δ���°���ʱ�����ϳ���������ĸ
		while (!_kbhit())
		{
			if (Fall() == -1)
				return 0; // һ����Ϸ����

			Wait();
			// ��ÿ��ѭ����1/3�ĸ��ʵ�������ĸ
			if (rand() % 3 == 0)
				GenerateLetter();
		}

		// �û����°����󣬽����жϣ�������Ӧ����ĸ
		// ����������ж��Ԫ�أ�ɾ����ͷԪ�أ���������һ����ĸ���ֶ�Σ��������·�����ĸ��
		ch = _getch();
		if (ch >= 'a' && ch <= 'z')
		{
			if (!m_letters[ch - 'a'].empty())
			{
				// ���ݼ��̰��µ���ĸ������Ӧ��deque�����Ķ��״���Ļ�����
				letter = m_letters[ch - 'a'].front();
				menu.SetCursor(letter.x, letter.y);
				cout << ' ';

				m_letters[ch - 'a'].pop_front(); // ɾ��ͷԪ��
				PlaySound(L"..\\sound\\m_score.wav", NULL, SND_ASYNC | SND_FILENAME);

				m_score++;
				ShowScore();
			}
		}
		else if (ch == VK_ESCAPE) // ���¡�esc��������ͣ����
			return 1; 
	}
	return 0;
}

