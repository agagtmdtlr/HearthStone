#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"
#include "Righteousness.h"

Righteousness::Righteousness(BattleField * field)
	:Magic(field, 5, "정의", 0, false)
{
}

bool Righteousness::FirstSkill()
{
	auto & fieldList = battleFieldOfCard->cardsOfField[nThisCardUserNumber];
	for (auto iter : fieldList)
	{
		Creature * target = (Creature *)iter;
		target->SetHolyShield(true);		
	}
	return true;
}

void Righteousness::detail()
{
	Magic::detail();
	cout << "내 하수인들에게 [천상의 보호막]을 부여합니다." << endl;
}
