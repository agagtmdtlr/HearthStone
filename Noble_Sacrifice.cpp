#pragma once
#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"
#include "Noble_Sacrifice.h"

Noble_Sacrifice::Noble_Sacrifice(BattleField * field)
	:Secret(field, 1, "고귀한 희생", 0)
{
}

void Noble_Sacrifice::FirstSkill()
{
	// 상대 관찰자 리스트에 추가하기
	battleFieldOfCard->observers[1 - nThisCardUserNumber].push_back(this);
}

void Noble_Sacrifice::onNotify(Card & card, EVENT event)
{
	if (event == EVENT::ATTACK && card.GetThisCardUser() == 1 - nThisCardUserNumber)
	{
		Creature * creature = new Creature(battleFieldOfCard, 1,
			"수호자", 2, 1, 1, false, false, false);
		// 필드에 하수인 추가
		battleFieldOfCard->cardsOfField[nThisCardUserNumber].push_back(creature);
		// 피공격자에 생성한 하수인 추가하기
		battleFieldOfCard->arrFight[nThisCardUserNumber] = creature;

		auto & observerList = battleFieldOfCard->observers[1-nThisCardUserNumber];
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

void Noble_Sacrifice::onNotify(Card * card, EVENT event)
{
	if (card == nullptr) return;
	if (event == EVENT::ATTACK && card->GetThisCardUser() == 1 - nThisCardUserNumber)
	{
		Creature * creature = new Creature(battleFieldOfCard, 1,
			"수호자", 2, 1, 1, false, false, false);
		// 필드에 하수인 추가
		battleFieldOfCard->cardsOfField[nThisCardUserNumber].push_back(creature);
		// 피공격자에 생성한 하수인 추가하기
		battleFieldOfCard->arrFight[nThisCardUserNumber] = creature;

		auto & observerList = battleFieldOfCard->observers[1 - nThisCardUserNumber];
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
