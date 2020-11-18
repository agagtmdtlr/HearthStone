#pragma once
#include "stdafx.h"
#include "BattleField.h"
#include "Hero.h"
#include "Repentance.h"

Repentance::Repentance(BattleField * field)
	:Secret(field,1,"참회",0)
{
}

void Repentance::FirstSkill()
{
	battleFieldOfCard->observers[1 - nThisCardUserNumber].push_back(this);
}

void Repentance::detail()
{
	cout << "[비밀]" << endl
		<< "상대편이 하수인을 낸 후에, 그 하수인의 생명력이 1로 감소합니다." << endl;
}

void Repentance::onNotify(Card & card, EVENT event)
{
	if (event == EVENT::FIELD)
	{
		Creature * target = (Creature *)&card;
		// 생명력이 1로 감소합니다.
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
