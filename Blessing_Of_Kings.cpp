#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"
#include "Blessing_Of_Kings.h"

Blessing_Of_Kings::Blessing_Of_Kings(BattleField * field)
	:Magic(field, 4, "���� �ູ", 4, false)
{
	strDescribeSkillDetail = "\n�ϼ��ο��� +4/+4�� �ο��մϴ�.";
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
