#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"
#include "Blessing_Of_Might.h"

Blessing_Of_Might::Blessing_Of_Might(BattleField * field, int cost, string name, int power)
	:Magic(field, 1, "흠의 축복", 3, false)
{
	strDescribeSkillDetail = "\n하수인에게 공격력을 +3 부여합니다.";
}

bool Blessing_Of_Might::FirstSkill()
{
	Creature * target = SelectCreatureOfAllField();
	if (target == nullptr)
	{
		return false;
	}
	else
	{
		target->SetPlusSkillDetail(strDescribeSkillDetail);
		target->SetPower(3);
	}
}

void Blessing_Of_Might::detail()
{
	Magic::detail();
	cout << strDescribeSkillDetail << endl;
}
