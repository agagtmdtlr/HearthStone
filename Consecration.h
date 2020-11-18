#pragma once
#include "Magic.h"
class Consecration :
	public Magic
{
public:
	Consecration() {}
	Consecration(
		BattleField * field
	);
	virtual ~Consecration() {}
	virtual bool FirstSkill() override;
	virtual void detail() override;

	

};

