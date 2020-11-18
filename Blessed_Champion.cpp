#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"
#include "Blessed_Champion.h"

Blessed_Champion::Blessed_Champion(BattleField * field, int cost, string name, int power)
	:Magic(field, 5, "�ູ���� ���", 0, false)
{
	strDescribeSkillDetail = "\n�ϼ����� ���ݷ��� 2�� ������ŵ�ϴ�.";
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
