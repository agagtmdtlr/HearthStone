#pragma once
#include "Magic.h"
class Lay_On_Hands :
	public Magic
{
public:
	Lay_On_Hands() {}
	Lay_On_Hands(
		BattleField * field
	);
	virtual ~Lay_On_Hands() {}
	virtual bool FirstSkill() override;
	virtual void detail() override;
};

