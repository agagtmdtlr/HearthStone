#pragma once
#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"
#include "Consecration.h"

Consecration::Consecration(BattleField * field)
	:Magic(field, 4, "신성화", 2, true)
{
}

bool Consecration::FirstSkill()
{
	int turn = nThisCardUserNumber;
	int damage = nPower + nPowerBonus;
	Creature * enemyHero = (Creature*)battleFieldOfCard->User[1 - turn];
	enemyHero->SetShield(-damage);
	for (auto card : battleFieldOfCard->cardsOfField[1 - turn])
	{
		Creature * creature = (Creature *)card;
		creature->SetShield(-damage);
	}
	return true;
}

void Consecration::detail()
{
	Magic::detail();
	cout << "모든 적에게 피해를 " << nPower + nPowerBonus << " 줍니다." << endl;
}

