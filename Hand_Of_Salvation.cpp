#pragma once
#include "stdafx.h"
#include "BattleField.h"
#include "Hand_Of_Salvation.h"

Hand_Of_Salvation::Hand_Of_Salvation(BattleField * field, int cost, string name, int power)
	:Secret(field, 1, "구원의 손길", 0),nDeathCount(0)
{
}

void Hand_Of_Salvation::FirstSkill()
{
	battleFieldOfCard->observers[nThisCardUserNumber].push_back(this);
}

void Hand_Of_Salvation::onNotify(Card & card, EVENT event)
{
	if (event == EVENT::END) nDeathCount = 0;
	// 아군 하수인이 죽으면
	if (event == EVENT::DIE && card.GetThisCardUser() == nThisCardUserNumber)
	{
		nDeathCount++;
	}
	// 2번째 죽으면
	if (nDeathCount == 2)
	{
		Creature * creature = (Creature *)&card;
		Creature * newCreature = new Creature(*creature);
		newCreature->InitStat();
		battleFieldOfCard->cardsOfField[nThisCardUserNumber].push_back(newCreature);

		auto & observerList = battleFieldOfCard->observers[nThisCardUserNumber];
		for (int i = 0; i < observerList.size();)
		{
			if (observerList[i] == this)
				observerList.erase(observerList.begin() + i);
			else
				i++;
		}

		isDelete = true;
	}
}

void Hand_Of_Salvation::onNotify(Card * card, EVENT event)
{
	if (event == EVENT::END) nDeathCount = 0;
	// 아군 하수인이 죽으면
	if (event == EVENT::DIE && card->GetThisCardUser() == nThisCardUserNumber)
	{
		nDeathCount++;
	}
	// 2번째 죽으면
	if (nDeathCount >= 2)
	{
		Creature * creature = (Creature *)&card;
		Creature * newCreature = new Creature(*creature);
		newCreature->InitStat();
		battleFieldOfCard->cardsOfField[nThisCardUserNumber].push_back(newCreature);

		auto & observerList = battleFieldOfCard->observers[nThisCardUserNumber];
		for (int i = 0; i < observerList.size();)
		{
			if (observerList[i] == this)
				observerList.erase(observerList.begin() + i);
			else
				i++;
		}

		isDelete = true;
	}
}
