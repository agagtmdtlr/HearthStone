#pragma once
#include "Magic.h"
class Hand_Of_Protection :
	public Magic
{
public:
	Hand_Of_Protection(){}
	Hand_Of_Protection(
		BattleField * field,
		int cost,
		string name,
		int power
	);
	virtual ~Hand_Of_Protection(){}
	virtual void FirstSkill() override;
	virtual void detail() override;
};

