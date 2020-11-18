#pragma once
#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"
#include "Noble_Sacrifice.h"

Noble_Sacrifice::Noble_Sacrifice(BattleField * field)
	:Secret(field, 1, "����� ���", 0)
{
}

void Noble_Sacrifice::FirstSkill()
{
	// ��� ������ ����Ʈ�� �߰��ϱ�
	battleFieldOfCard->observers[1 - nThisCardUserNumber].push_back(this);
}

void Noble_Sacrifice::onNotify(Card & card, EVENT event)
{
	if (event == EVENT::ATTACK && card.GetThisCardUser() == 1 - nThisCardUserNumber)
	{
		Creature * creature = new Creature(battleFieldOfCard, 1,
			"��ȣ��", 2, 1, 1, false, false, false);
		// �ʵ忡 �ϼ��� �߰�
		battleFieldOfCard->cardsOfField[nThisCardUserNumber].push_back(creature);
		// �ǰ����ڿ� ������ �ϼ��� �߰��ϱ�
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
			"��ȣ��", 2, 1, 1, false, false, false);
		// �ʵ忡 �ϼ��� �߰�
		battleFieldOfCard->cardsOfField[nThisCardUserNumber].push_back(creature);
		// �ǰ����ڿ� ������ �ϼ��� �߰��ϱ�
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
