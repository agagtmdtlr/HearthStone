#pragma once
#include "Magic.h"
class Holy_Light :
	public Magic
{
public:
	Holy_Light() {}
	Holy_Light(
		BattleField * field,
		int cost,
		string name,
		int power
	);
	virtual ~Holy_Light() {}
	virtual bool FirstSkill() override;
	virtual void detail() override;

};
