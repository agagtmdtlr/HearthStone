#pragma once
#include "stdafx.h"
#include "BattleField.h"
#include "Hero.h"
#include "Eye_For_An_Eye.h"


Eye_For_An_Eye::Eye_For_An_Eye(BattleField * field, int cost, string name, int power)
{
}

void Eye_For_An_Eye::FirstSkill()
{
	battleFieldOfCard->observers[nThisCardUserNumber].push_back(this);
}

void Eye_For_An_Eye::detail()
{
	Secret::detail();
	cout << "[���]" << endl
		<< "�� ������ ���ظ� ������, ���������Ե� ���� ���ظ� �ݴϴ�." << endl;
}

void Eye_For_An_Eye::onNotify(Card & card, EVENT event)
{
	if (event == EVENT::DAMAGE && &card == battleFieldOfCard->User[nThisCardUserNumber])
	{
		Hero * hero = (Hero *)battleFieldOfCard->User[nThisCardUserNumber];
		int attackDamage = hero->GetPreviousShield() - hero->GetShield();
		// ���� ���ظ� ��� �������Ե� ������.
		Hero * enemy = (Hero *)battleFieldOfCard->User[1 - nThisCardUserNumber];
		enemy->SetShield(-attackDamage);

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

void Eye_For_An_Eye::onNotify(Card * card, EVENT event)
{
	if (event == EVENT::DAMAGE && card == battleFieldOfCard->User[nThisCardUserNumber])
	{
		Hero * hero = (Hero *)battleFieldOfCard->User[nThisCardUserNumber];
		int attackDamage = hero->GetPreviousShield() - hero->GetShield();
		// ���� ���ظ� ��� �������Ե� ������.
		Hero * enemy = (Hero *)battleFieldOfCard->User[1 - nThisCardUserNumber];
		enemy->SetShield(-attackDamage);

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
