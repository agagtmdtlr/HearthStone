#pragma once
#include "Creature.h"

class Tirion_Fordring :
	public Creature
{
public:
	Tirion_Fordring();
	Tirion_Fordring(BattleField * field);
	virtual ~Tirion_Fordring();

	virtual void detail() override;
	virtual void SetDelete(bool val) override;

};

