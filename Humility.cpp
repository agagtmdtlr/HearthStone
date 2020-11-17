#pragma once
#include "stdafx.h"
#include "BattleField.h"
#include "Humility.h"

Humility::Humility()	
{
}

Humility::Humility(BattleField * field)
	:Magic(field, 1, "겸손", 0,false)
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
	cout << "하수인의 공격력을 1로 만듭니다." << endl;	
}
