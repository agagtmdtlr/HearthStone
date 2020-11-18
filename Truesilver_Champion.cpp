#include "stdafx.h"
#include "BattleField.h"
#include "Truesilver_Champion.h"

Truesilver_Champion::Truesilver_Champion(BattleField * field, int cost, string name, int power, int durability, int attcount)
	:Weapon(field, 1, "용사의 진은검", 4, 2, 1)
{
}

Truesilver_Champion::Truesilver_Champion(int userNumber, BattleField * field, int cost, string name, int power, int durability, int attcount)
	: Weapon(userNumber, field, 1, "용사의 진은검", 4, 2, 1)
{
}

void Truesilver_Champion::FirstSkill()
{
	battleFieldOfCard->observers[nThisCardUserNumber].push_back(this);
}
