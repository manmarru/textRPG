#include <iostream>
#define ���� "================================"
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif

using namespace std;

struct player
{
	char myName[20] = "";
	int iHP, iMana, iAtt;
	int myHp = 0, myMana = 0, myAtt = 0;

	void status()
	{
		cout << ���� << endl;
		cout << myName << endl;
		cout << "ü�� :" << myHp << " ���� :" << myMana << " ���ݷ� :" << myAtt << endl;
 		cout << ���� << endl;
	}
};

player* me = new player; //YOU!
int* pstg = new int; //��������
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	strcpy_s(me->myName, sizeof(me->myName), "�ڹ�");
	me->status();


	delete me, pstg;
	me = nullptr;
	pstg = nullptr;
	return 0;
}