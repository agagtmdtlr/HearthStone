#pragma once
#include "stdafx.h"
#include "BattleField.h"
#include "Card.h"

Card::Card(int cost, string name, BattleField * field)
	:nCost(cost), nCostOrigin(cost), strName(name),battleFieldOfCard(field),isDelete(false),
	strPlusSkillDetail("")
{
	nThisCardUserNumber = field->nPlayerTurn % 2;
}

void Card::SetDelete(bool val)
{
	isDelete = val;
	if (isDelete == true)
	{
		ExcuteObserver(EVENT::DESTROY);
	}
}

void Card::Use() { ExcuteObserver(EVENT::USE); }
void Card::ExcuteObserver(EVENT event)
{
	int turn = battleFieldOfCard->nPlayerTurn % 2;
	for (int i = 0; i < battleFieldOfCard->observers[turn].size(); i++)
		battleFieldOfCard->observers[turn][i]->
		onNotify(this, event);
}

int Card::SelectCard(vector<Card*> *pCardCategory)
{	
	int inputNum = 0;
	for (int i = 0; i < pCardCategory->size(); i++)
	{
		cout << i << " : ";
		(*pCardCategory)[i]->Info();
		cout << "\t";
	}
	cout << endl;
		
	while (1)
	{
		cout << "대상을 선택하시오 : ";
		inputNum = InputVariable<int>(inputNum);

		if (inputNum >= pCardCategory->size())
		{
			cout << "다시 입력하시오" << endl;
		}
		else
		{
			return inputNum;
		}
	}
}

void Card::EraseObserverFromObserverList(int turn)
{
	auto & observerList = battleFieldOfCard->observers[turn];
	for (int i = 0; i < observerList.size();)
	{
		if (observerList[i] == this)
		{
			observerList.erase(observerList.begin() + i);
			break;
		}
	}
}











