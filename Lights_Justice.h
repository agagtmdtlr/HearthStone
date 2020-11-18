#pragma once
#include "Weapon.h"
class Lights_Justice :
	public Weapon
{
public:
	Lights_Justice() {};
	Lights_Justice(
		BattleField * field,
		int cost, string name,
		int power, int durability,
		int attcount
	);

	Lights_Justice(
		int userNumber,
		BattleField * field,
		int cost, string name,
		int power, int durability,
		int attcount
	);
};

