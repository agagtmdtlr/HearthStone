#pragma once
#include "Magic.h"
class Equality :
	public Magic
{
public:
	Equality() {}
	Equality(
		BattleField * field
	);
	virtual ~Equality() {}
	virtual bool FirstSkill() override;
	virtual void detail() override;
};

