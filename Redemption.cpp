#pragma once
#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"
#include "Redemption.h"

Redemption::Redemption(BattleField * field)
	:Secret(field, 1, "����", 0)
{
}

void Redemption::FirstSkill()
{
	// ��� ������ ����Ʈ�� �߰��ϱ�
	battleFieldOfCard->observers[nThisCardUserNumber].push_back(this);
}

void Redemption::onNotify(Card & card, EVENT event)
{
	// �Ʊ� �ϼ����� ������
	if (event == EVENT::DIE && card.GetThisCardUser() == nThisCardUserNumber)
	{
		Creature * creature = (Creature *)&card;
		Creature * newCreature = new Creature(*creature);
		newCreature->InitStat();
		newCreature->ChangeShieldOrigin(1);
		newCreature->ChangeShield(1);
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

void Redemption::onNotify(Card * card, EVENT event)
{
	if (card != nullptr)
	{
		if (event == EVENT::DIE && card->GetThisCardUser() == nThisCardUserNumber)
		{
			Creature * creature = (Creature *)card;
			Creature * newCreature = new Creature(*creature);
			newCreature->InitStat();
			newCreature->ChangeShieldOrigin(1);
			newCreature->ChangeShield(1);
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
}

