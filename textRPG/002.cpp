#include <iostream>
#include <cstring>
#include<ctime>
#define 라인 "================================"

using namespace std;

struct player
{
	char myName[20];
	int myHp, myMp, myAtt;
	int iHp, iMp, iAtt;
	int myMoney = 0;
	char myPos[20];
	char PosList[3][20] = {"전사", "마법사", "암살자"};
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
		case 1://전사
			iHp = 100; iMp = 10; iAtt = 10;	break;
		case 2: //법사
			iHp = 70; iMp = 30; iAtt = 10; break;
		case 3: //암살자
			iHp = 50; iMp = 30; iAtt = 15; break;
		default:
			break;
		}
		revive();
	}
	void stat()
	{
		cout << 라인 << '\n' << myName << " 소지금 :" << myMoney << '\n' << "체력 :" << myHp << " 마나 :" << myMp << " 공격력 :" << myAtt << '\n' << 라인 << '\n';
	}
};

int map(player* _me);
void battle(player* _me, int diff);
void making_money(player* _me);

int* pstage = new int;
int main()
{
#pragma region 캐릭터 생성
	player tP1;
	char cName[20];
	*pstage = 0;
	cout << "버터 이름은 뭐에요? :";
	cin >> cName;
	strcpy_s(tP1.myName, sizeof(tP1.myName), cName);
	*pstage = map(&tP1);
	tP1.stat();
	cout << "산책하러 가요!\n";
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
	case 0://포지션선택
		cout << "1. 전사  2. 마법사  3. 암살자" << endl;
		cin >> iChoice;
		(*_me).changePos(iChoice);
		*pstage = 1;
		break;
	case 1: //마을
		cout << "1. 사냥터  2.돈벌기  3. 포지션 변경" << endl;
		cin >> iChoice;
		if (iChoice == 1)
			*pstage = 2;
		if (iChoice == 2)
			*pstage = 3;
		if (iChoice == 3)
			*pstage = 0;
		break;
	case 2://사냥터 선택
		cout << "난이도를 선택하세용! (1. 뒤로가기):";
		cin >> iChoice;
		if (iChoice == 1)
		{
			*pstage = 1;
			break;
		}
		battle(_me, iChoice);
		*pstage = 1;
		//전투함수
		break;
	case 3: //돈벌기
		//돈벌기함수
		making_money(_me);
		*pstage = 1;
		iChoice = 1; //true
		break;
	case 4: // 스텟강화
		
		break;
	default:
		break;
	}
	return (bool)iChoice;
}

void battle(player* _me, int diff)
{
	player enemy = {"티그", 10 * diff, 0, 5*diff};
	int choice(0);
	while (_me->myHp > 0 && enemy.myHp > 0)
	{
		system("cls");
		_me->stat();
		enemy.stat();
		while (choice != 1 && choice != 2 && choice != 3)
		{
			cout << "1. 공격  2. 스킬  3. 탈출! :";
			cin >> choice;
		}
		switch (choice)
		{
		case 1:
			enemy.myHp -= _me->myAtt;
			_me->myHp -= enemy.myAtt;
			continue;
		case 2://스킬은 Mp계수로 때리고 한턴 쉼
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
		cout << "패배..\n";
		_me->revive();
	}
	else if (enemy.myHp <= 0)
	{
		cout << "승리!\n";
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
		cout << "2. 상  3. 하  1. 좌  4. 우  5.그만둘래요! :";
		cin >> choice;
		if (choice == 5)
			return;
		switch (choice)
		{
		case 2://상
			if (iY == 0)
			{
				cout << "쿵! (천장)" << endl;
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
		case 3://하
			if (iY == 4)
			{
				cout << "철푸덕! (바닥)" << endl;
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
		case 1://좌
			if (iX == 0)
			{
				cout << "쿵! (왼쪽벽)" << endl;
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
		case 4://우
			if (iX == 4)
			{
				cout << "쿵! (오른쪽벽)" << endl;
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
