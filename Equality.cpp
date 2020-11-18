#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"
#include "Equality.h"

Equality::Equality(BattleField * field, int cost, string name, int power)
	:Magic(field, 4, "평등", 0, false)
{
}

bool Equality::FirstSkill()
{
	for (int i = 0; i < 2; i++)
	{
		auto & targetList = battleFieldOfCard->cardsOfField[i];
		for (int j = 0; j < targetList.size(); j++)
		{
			auto target = (Creature *)targetList[j];
			// 생명력을 1로 바꿉니다.
			target->SetMaxShield(-(target->GetMaxShield() - 1));
		}		
	}
	return true;
}

void Equality::detail()
{
	Magic::detail();
	cout << "모든 하수인의 생명력을 1로 바꿉니다." << endl;
}
