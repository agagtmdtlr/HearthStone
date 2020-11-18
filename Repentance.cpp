#pragma once
#include "stdafx.h"
#include "BattleField.h"
#include "Hero.h"
#include "Repentance.h"

Repentance::Repentance(BattleField * field)
	:Secret(field,1,"��ȸ",0)
{
}

void Repentance::FirstSkill()
{
	battleFieldOfCard->observers[1 - nThisCardUserNumber].push_back(this);
}

void Repentance::detail()
{
	cout << "[���]" << endl
		<< "������� �ϼ����� �� �Ŀ�, �� �ϼ����� ������� 1�� �����մϴ�." << endl;
}

void Repentance::onNotify(Card & card, EVENT event)
{
	if (event == EVENT::FIELD)
	{
		Creature * target = (Creature *)&card;
		// ������� 1�� �����մϴ�.
		target->SetMaxShield(-(target->GetMaxShield() - 1));

		EraseObserverFromObserverList(1 - nThisCardUserNumber);

		isDelete = true;
	}
}

void Repentance::onNotify(Card * card, EVENT event)
{
	
	if (event == EVENT::FIELD)
	{
		Creature * target = (Creature *)card;
		target->SetMaxShield(-(target->GetMaxShield() - 1));

		EraseObserverFromObserverList(1 - nThisCardUserNumber);

		isDelete = true;
	}
}
