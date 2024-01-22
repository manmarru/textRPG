#include <iostream>
#include <cstring>
#include<ctime>
#define ���� "================================"

using namespace std;

struct player
{
	char myName[20];
	int myHp, myMp, myAtt;
	int iHp, iMp, iAtt;
	int myMoney = 0;
	char myPos[20];
	char PosList[3][20] = {"����", "������", "�ϻ���"};
	void revive()
	{
		myHp = iHp;
		myMp = iMp;
		myAtt = iAtt;
	}
	void changePos(int i)
	{
		strcpy_s(myPos, sizeof(myPos), PosList[i-1]);
		switch (i)
		{
		case 1://����
			iHp = 100; iMp = 10; iAtt = 10;	break;
		case 2: //����
			iHp = 70; iMp = 30; iAtt = 10; break;
		case 3: //�ϻ���
			iHp = 50; iMp = 30; iAtt = 15; break;
		default:
			break;
		}
		revive();
	}
	void stat()
	{
		cout << ���� << '\n' << myName << " ������ :" << myMoney << '\n' << "ü�� :" << myHp << " ���� :" << myMp << " ���ݷ� :" << myAtt << '\n' << ���� << '\n';
	}
};

int map(player* _me);
void battle(player* _me, int diff);
void making_money(player* _me);

int* pstage = new int;
int main()
{
#pragma region ĳ���� ����
	player tP1;
	char cName[20];
	*pstage = 0;
	cout << "���� �̸��� ������? :";
	cin >> cName;
	strcpy_s(tP1.myName, sizeof(tP1.myName), cName);
	*pstage = map(&tP1);
	tP1.stat();
	cout << "��å�Ϸ� ����!\n";
	system("pause");
#pragma endregion

	do
	{
		system("cls");
		tP1.stat();

	} while (map(&tP1));

	delete pstage;
	pstage = nullptr;
	return 0;
}

int map(player* _me)
{
	int iChoice = 0;
	switch (*pstage)
	{
	case 0://�����Ǽ���
		cout << "1. ����  2. ������  3. �ϻ���" << endl;
		cin >> iChoice;
		(*_me).changePos(iChoice);
		*pstage = 1;
		break;
	case 1: //����
		cout << "1. �����  2.������  3. ������ ����" << endl;
		cin >> iChoice;
		if (iChoice == 1)
			*pstage = 2;
		if (iChoice == 2)
			*pstage = 3;
		if (iChoice == 3)
			*pstage = 0;
		break;
	case 2://����� ����
		cout << "���̵��� �����ϼ���! (1. �ڷΰ���):";
		cin >> iChoice;
		if (iChoice == 1)
		{
			*pstage = 1;
			break;
		}
		battle(_me, iChoice);
		*pstage = 1;
		//�����Լ�
		break;
	case 3: //������
		//�������Լ�
		making_money(_me);
		*pstage = 1;
		iChoice = 1; //true
		break;
	case 4: // ���ݰ�ȭ
		
		break;
	default:
		break;
	}
	return (bool)iChoice;
}

void battle(player* _me, int diff)
{
	player enemy = {"Ƽ��", 10 * diff, 0, 5*diff};
	int choice(0);
	while (_me->myHp > 0 && enemy.myHp > 0)
	{
		system("cls");
		_me->stat();
		enemy.stat();
		while (choice != 1 && choice != 2 && choice != 3)
		{
			cout << "1. ����  2. ��ų  3. Ż��! :";
			cin >> choice;
		}
		switch (choice)
		{
		case 1:
			enemy.myHp -= _me->myAtt;
			_me->myHp -= enemy.myAtt;
			continue;
		case 2://��ų�� Mp����� ������ ���� ��
			enemy.myHp -= _me->myMp;
			_me->myHp -= enemy.myAtt * 2;
			continue;
		case 3:
			return;
		default:
			break;
		}
	}
	if (_me->myHp <= 0)
	{
		cout << "�й�..\n";
		_me->revive();
	}
	else if (enemy.myHp <= 0)
	{
		cout << "�¸�!\n";
	}
	system("pause");
}

void making_money(player* _me)
{
	int iX(0), iY(0);
	int choice(1);
	int ground[5][5] = {0};
	ground[0][0] -= 1;
	srand(time(NULL));
	ground[rand() % 4 + 1][rand() % 4 + 1] = rand() % 100;
	while (choice != 0)
	{
		system("cls");
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (ground[i][j] == -1)
				{
					cout << "ME\t";
					continue;
				}
				cout << ground[i][j] << '\t';
			}
			cout << '\n';
		}
		cout << "2. ��  3. ��  1. ��  4. ��  5.�׸��ѷ���! :";
		cin >> choice;
		if (choice == 5)
			return;
		switch (choice)
		{
		case 2://��
			if (iY == 0)
			{
				cout << "��! (õ��)" << endl;
				break;
			}
			if (ground[iY - 1][iX] != 0)
			{
				(*_me).myMoney += ground[iY - 1][iX];
				return;
			}
			swap(ground[iY][iX], ground[iY - 1][iX]);
			--iY;
			break;
		case 3://��
			if (iY == 4)
			{
				cout << "öǪ��! (�ٴ�)" << endl;
				break;
			}
			if (ground[iY + 1][iX] != 0)
			{
				(*_me).myMoney += ground[iY + 1][iX];
				return;
			}
			swap(ground[iY][iX], ground[iY + 1][iX]);
			++iY;
			break;
		case 1://��
			if (iX == 0)
			{
				cout << "��! (���ʺ�)" << endl;
				break;
			}
			if (ground[iY][iX - 1] != 0)
			{
				(*_me).myMoney += ground[iY][iX - 1];
				return;
			}
			swap(ground[iY][iX], ground[iY][iX - 1]);
			--iX;
			break;
		case 4://��
			if (iX == 4)
			{
				cout << "��! (�����ʺ�)" << endl;
				break;
			}
			if (ground[iY][iX + 1] != 0)
			{
				(*_me).myMoney += ground[iY][iX + 1];
				return;
			}
			swap(ground[iY][iX], ground[iY][iX + 1]);
			++iX;
			break;
		default:
			break;
		}
	}
}
