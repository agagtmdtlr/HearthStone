#pragma once
#include "Magic.h"
class Consecration :
	public Magic
{
public:
	Consecration() {}
	Consecration(
		BattleField * field,
		int cost,
		string name,
		int power
	);
	virtual ~Consecration() {}
	virtual bool FirstSkill() override;
	virtual void detail() override;

	

};

