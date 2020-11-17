#pragma once
#include "stdafx.h"
#include "BattleField.h"
#include "Humility.h"

Humility::Humility()	
{
}

Humility::Humility(BattleField * field)
	:Magic(field, 1, "���", 0,false)
{
}

bool Humility::FirstSkill()
{
	Creature * creature = SelectCreatureOfAllField();
	if (creature != nullptr)
	{
		creature->SetPower(-(creature->GetPower() - 1));
		return true;
	}
	else
	{
		return false;
	}
	
}

void Humility::detail()
{
	Magic::detail();
	cout << "�ϼ����� ���ݷ��� 1�� ����ϴ�." << endl;	
}
