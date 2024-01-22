#include <iostream>
#include <cstring>
#define 라인 "================================"

using namespace std;

struct player
{
    char myName[21];
    int iHp = 0, iMp = 0, iAtt = 0;
    int myHp, myMp, myAtt;
    char sound[20];
    void position(int i)
    {
        switch (i)
        {
        case 1: //수인
            iHp = 100;
            iMp = 50;
            iAtt = 10;
            strcpy_s(sound, "크앙!");
            break;
        case 2: //요정
            iHp = 70;
            iMp = 100;
            iAtt = 15;
            strcpy_s(sound, "...");
            break;
        case 3: //유령
            iHp = 50;
            iMp = 80;
            iAtt = 15;
            strcpy_s(sound, "히히!");
            break;
        default: //테스트용
            iHp = 10;
            iMp = 10;
            iAtt = 10;
            strcpy_s(sound, "//////");
            break;
        }
    }
    void status()
    { 
        cout << myName << '\n' << "체력 :" << myHp << " 마나 :" << myMp << " 공격력 :" << myAtt;
        cout << "\n" << 라인 << "\n";
    }
    void revive()
    {
        myHp = iHp;
        myMp = iMp;
        myAtt = iAtt;
    }
};

struct party
{
    player* slot[3];
    void status()
    {
        cout << "\n" << 라인 << "\n";
        for (int i = 0; i < 3; ++i)
        {
            (*slot[i]).status();
        }
    }
    void revive()
    {
        for (int i = 0; i < 3; ++i)
            (*slot[i]).revive();
    }
    void changePosition()
    {
        int iSlotNum(1), iPos(1);
        while (iPos != 0 && iSlotNum != 0)
        {
            system("cls");
            status();
            cout << "캐릭터 슬롯을 선택하세요" << endl;
            cin >> iSlotNum;
            if (iSlotNum != 1 && iSlotNum != 2 && iSlotNum != 3 && iSlotNum != 0)
                continue;
            if (iSlotNum == 0)
                break;
            cout << "직업!\n" << "1. 전사  2. 마법사  3. 도적  4. 취소 :" << endl;
            cin >> iPos;
            if (iPos != 1 && iPos != 2 && iPos != 3 && iPos != 4)
                continue;
            if (iPos == 4)
                continue;
            (*slot[iSlotNum-1]).position(iPos);
            (*slot[iSlotNum-1]).revive();
        }
    }
    int isalive()
    {
        for (int i = 0; i < 3; ++i)
        {
            if ((*slot[i]).myHp >= 0)
                continue;
            return i;
        }
        return 0;
    }
};

bool playstage(int* _stage, party* _me);
void battle(int diff, party* _me);

int main()
{
#pragma region 정의와 캐릭터 생성

    int stage(0);
    char cName[21];
    player tPlayer1;
    player tPlayer2;
    player tPlayer3;
    party squad = { {&tPlayer1, &tPlayer2, &tPlayer3} };
    for (int i = 0; i < 3; ++i)
    {
        cout << i+1 << "번 플레이어 이름 :\n";
        cin >> cName;
        strcpy_s(squad.slot[i] -> myName, sizeof(squad.slot[i] -> myName), cName);
    }
    squad.revive();
    squad.changePosition(); // 캐릭터 생성 완료
    stage = 1;
#pragma endregion

    do
    {
        system("cls");
//        squad.status();
    } while (playstage(&stage, &squad));

    return 0;
}

int map(int stage, int choice)
{
    switch (stage)
    {
    case 0: //포지션 변경
    case 1: //마을광장
        if (choice == 1)
            return 2;
        else if (choice == 2)
            return 1;
        break;
    case 2: //사냥터
        break;
    default:
        break;
    }
}

bool playstage(int* _stage, party* _me)
{
    int iChoice; 
//    (*_me).status();
    switch (*_stage)
    {
    case 0:
        cin >> iChoice;
        (*_me).changePosition();
        break;
    case 1:
        cout << "마을 광장\n" << "1. 사냥터  2. 포지션 바꾸기 :";
        cin >> iChoice;
        *_stage = map(*_stage, iChoice);
        break;
    case 2:
        cout << "1. 초급  2. 중급  3. 상급 :";
        cin >> iChoice;
        battle(iChoice, _me);
        cout << "돌아간다.";
        *_stage = 1;
        break;
    default:
        break;
    }
    return 1;
}

void battle(int diff, party* _me)
{
    int iChoice, turn(0);
    system("cls");
    player enemy = { "티그", 30 * diff, 10 * diff, 5 * diff };
    enemy.revive();
    while (enemy.myHp >= 0 && _me->isalive() != 4)
    {
        turn = 0;
        while (turn < 3)
        {
            system("cls");
            (*_me).status();
            enemy.status();
            cout << "1. 공격 2. 회복  3. 도망! :";
            cin >> iChoice;
            switch (iChoice)
            {
            case 1:
                enemy.myHp -= (*_me).slot[turn]->myAtt;
                break;
            case 2:
                (*_me).revive();
                break;
            case 3:
                return;
            default:
                break;
            }
            if ((*_me).isalive() == 4 || enemy.myHp <= 0)
                break;
            ++turn;
        }
        (*_me).slot[(*_me).isalive()]->myHp -= enemy.myAtt;
    }
    "전투종료";
    system("pause");
};