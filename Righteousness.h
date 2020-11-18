#pragma once
#include "Magic.h"
class Righteousness :
	public Magic
{
public:
	Righteousness() {}
	Righteousness(
		BattleField * field
	);
	virtual ~Righteousness() {}
	virtual bool FirstSkill() override;
	virtual void detail() override;
};

