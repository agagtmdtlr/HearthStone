#pragma once
#include "Creature.h"
#include "Magic.h"


class Humility :
	public Magic
{
public:
	Humility();
	Humility(
		BattleField * field		
	);
	virtual void FirstSkill() override;
	virtual void detail() override;
};

