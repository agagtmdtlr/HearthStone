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
	virtual ~Humility() {}
	virtual bool FirstSkill() override;
	virtual void detail() override;
};

