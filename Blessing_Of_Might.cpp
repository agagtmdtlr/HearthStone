#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"
#include "Blessing_Of_Might.h"

Blessing_Of_Might::Blessing_Of_Might(BattleField * field)
	:Magic(field, 1, "���� �ູ", 3, false)
{
	strDescribeSkillDetail = "\n�ϼ��ο��� ���ݷ��� +3 �ο��մϴ�.";
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
		return true;
	}
}

void Blessing_Of_Might::detail()
{
	Magic::detail();
	cout << strDescribeSkillDetail << endl;
}
