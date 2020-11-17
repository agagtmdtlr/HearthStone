#pragma once
#include "stdafx.h"
#include "Creature.h"
#include "Hand_Of_Protection.h"

Hand_Of_Protection::Hand_Of_Protection(BattleField * field, int cost, string name, int power)
	:Magic(field, 1, "겸손", 0,false)
{
}

void Hand_Of_Protection::FirstSkill()
{
	Creature * creature = SelectCreatureOfAllField();
	creature->SetHolyShield(true);
}

void Hand_Of_Protection::detail()
{
	Magic::detail();
	cout << "하수인에게 [천상의 보호막]을 부여합니다."
}
