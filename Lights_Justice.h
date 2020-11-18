#pragma once
#include "Weapon.h"
class Lights_Justice :
	public Weapon
{
public:
	Lights_Justice() {};
	Lights_Justice(
		BattleField * field
	);

	Lights_Justice(
		int userNumber,
		BattleField * field
	);
};

