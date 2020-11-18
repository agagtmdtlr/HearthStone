#pragma once
#include "Weapon.h"
class Truesilver_Champion :
	public Weapon
{
public:
	Truesilver_Champion() {};
	Truesilver_Champion(
		BattleField * field,
		int cost, string name,
		int power, int durability,
		int attcount
	);

	Truesilver_Champion(
		int userNumber,
		BattleField * field,
		int cost, string name,
		int power, int durability,
		int attcount
	);

	virtual void FirstSkill() override;
};

