#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"
#include "Blessed_Champion.h"

Blessed_Champion::Blessed_Champion(BattleField * field, int cost, string name, int power)
	:Magic(field, 5, "축복받은 용사", 0, false)
{
	strDescribeSkillDetail = "\n하수인의 공격력을 2배 증가시킵니다.";
}

bool Blessed_Champion::FirstSkill()
{
	Creature * target = SelectCreatureOfAllField();
	if (target == nullptr)
	{
		return false;
	}
	else
	{
		target->SetPlusSkillDetail(strDescribeSkillDetail);
		target->SetPower(target->GetPower());
	}
}

void Blessed_Champion::detail()
{
	Magic::detail();
	cout << strDescribeSkillDetail << endl;
}
