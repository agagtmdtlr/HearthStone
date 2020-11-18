#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"
#include "Blessing_Of_Kings.h"

Blessing_Of_Kings::Blessing_Of_Kings(BattleField * field)
	:Magic(field, 4, "왕의 축복", 4, false)
{
	strDescribeSkillDetail = "\n하수인에게 +4/+4를 부여합니다.";
}

bool Blessing_Of_Kings::FirstSkill()
{
	Creature * creature = SelectCreatureOfAllField();
	if (creature == nullptr)
	{
		return false;
	}
	else
	{
		creature->SetPlusSkillDetail(strDescribeSkillDetail);
		creature->SetPower(nPower);
		creature->SetMaxShield(nPower);
		return true;
	}
}

void Blessing_Of_Kings::detail()
{
	Magic::detail();
	cout << strDescribeSkillDetail << endl;
}
