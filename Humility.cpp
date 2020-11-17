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

void Humility::FirstSkill()
{
	Creature * creature = SelectCreatureOfAllField();
	creature->SetPower(-(creature->GetPower() - 1));
}

void Humility::detail()
{
	Magic::detail();
	cout << "�ϼ����� ���ݷ��� 1�� ����ϴ�." << endl;	
}
