#pragma once
#include "Magic.h"
class Hand_Of_Protection :
	public Magic
{
public:
	Hand_Of_Protection(){}
	Hand_Of_Protection(
		BattleField * field
	);
	virtual ~Hand_Of_Protection(){}
	virtual bool FirstSkill() override;
	virtual void detail() override;


};

