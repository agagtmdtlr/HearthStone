#pragma once
#include "Magic.h"
class Hammer_Of_Wrath :
	public Magic
{
public:
	Hammer_Of_Wrath() {}
	Hammer_Of_Wrath(
		BattleField * field,
		int cost,
		string name,
		int power
	);
	virtual ~Hammer_Of_Wrath() {}
	virtual bool FirstSkill() override;
	virtual void detail() override;

	
};

