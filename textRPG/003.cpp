#include <iostream>
#define 라인 "================================"
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
		cout << 라인 << endl;
		cout << myName << endl;
		cout << "체력 :" << myHp << " 마나 :" << myMana << " 공격력 :" << myAtt << endl;
 		cout << 라인 << endl;
	}
};

player* me = new player; //YOU!
int* pstg = new int; //스테이지
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	strcpy_s(me->myName, sizeof(me->myName), "코미");
	me->status();


	delete me, pstg;
	me = nullptr;
	pstg = nullptr;
	return 0;
}