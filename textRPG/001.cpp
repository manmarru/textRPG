#include <iostream>
#include <cstring>
#define ���� "================================"

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
        case 1: //����
            iHp = 100;
            iMp = 50;
            iAtt = 10;
            strcpy_s(sound, "ũ��!");
            break;
        case 2: //����
            iHp = 70;
            iMp = 100;
            iAtt = 15;
            strcpy_s(sound, "...");
            break;
        case 3: //����
            iHp = 50;
            iMp = 80;
            iAtt = 15;
            strcpy_s(sound, "����!");
            break;
        default: //�׽�Ʈ��
            iHp = 10;
            iMp = 10;
            iAtt = 10;
            strcpy_s(sound, "//////");
            break;
        }
    }
    void status()
    { 
        cout << myName << '\n' << "ü�� :" << myHp << " ���� :" << myMp << " ���ݷ� :" << myAtt;
        cout << "\n" << ���� << "\n";
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
        cout << "\n" << ���� << "\n";
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
            cout << "ĳ���� ������ �����ϼ���" << endl;
            cin >> iSlotNum;
            if (iSlotNum != 1 && iSlotNum != 2 && iSlotNum != 3 && iSlotNum != 0)
                continue;
            if (iSlotNum == 0)
                break;
            cout << "����!\n" << "1. ����  2. ������  3. ����  4. ��� :" << endl;
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
#pragma region ���ǿ� ĳ���� ����

    int stage(0);
    char cName[21];
    player tPlayer1;
    player tPlayer2;
    player tPlayer3;
    party squad = { {&tPlayer1, &tPlayer2, &tPlayer3} };
    for (int i = 0; i < 3; ++i)
    {
        cout << i+1 << "�� �÷��̾� �̸� :\n";
        cin >> cName;
        strcpy_s(squad.slot[i] -> myName, sizeof(squad.slot[i] -> myName), cName);
    }
    squad.revive();
    squad.changePosition(); // ĳ���� ���� �Ϸ�
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
    case 0: //������ ����
    case 1: //��������
        if (choice == 1)
            return 2;
        else if (choice == 2)
            return 1;
        break;
    case 2: //�����
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
        cout << "���� ����\n" << "1. �����  2. ������ �ٲٱ� :";
        cin >> iChoice;
        *_stage = map(*_stage, iChoice);
        break;
    case 2:
        cout << "1. �ʱ�  2. �߱�  3. ��� :";
        cin >> iChoice;
        battle(iChoice, _me);
        cout << "���ư���.";
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
    player enemy = { "Ƽ��", 30 * diff, 10 * diff, 5 * diff };
    enemy.revive();
    while (enemy.myHp >= 0 && _me->isalive() != 4)
    {
        turn = 0;
        while (turn < 3)
        {
            system("cls");
            (*_me).status();
            enemy.status();
            cout << "1. ���� 2. ȸ��  3. ����! :";
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
    "��������";
    system("pause");
};