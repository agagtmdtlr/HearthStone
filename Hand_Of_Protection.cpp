#pragma once
#include "stdafx.h"
#include "Creature.h"
#include "Hand_Of_Protection.h"

Hand_Of_Protection::Hand_Of_Protection(BattleField * field, int cost, string name, int power)
	:Magic(field, 1, "���", 0,false)
{
}

bool Hand_Of_Protection::FirstSkill()
{
	Creature * creature = SelectCreatureOfAllField();
	if (creature != nullptr)
	{
		creature->SetHolyShield(true);
		return true;
	}
	else
	{
		return false;
	}
	
}

void Hand_Of_Protection::detail()
{
	Magic::detail();
	cout << "�ϼ��ο��� [õ���� ��ȣ��]�� �ο��մϴ�." << endl;
}
