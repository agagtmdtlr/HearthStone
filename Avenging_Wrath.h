#pragma once
#include "Magic.h"
class Avenging_Wrath :
	public Magic
{
public:
	Avenging_Wrath() {}
	Avenging_Wrath(
		BattleField * field		
	);
	virtual ~Avenging_Wrath() {}
	virtual bool FirstSkill() override;
	virtual void detail() override;
};

