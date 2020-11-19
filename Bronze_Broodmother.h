#pragma once
#include "Creature.h"
class Bronze_Broodmother :
	public Creature
{
public:
	Bronze_Broodmother();
	Bronze_Broodmother(BattleField * field);

	~Bronze_Broodmother();
	virtual void detail() override;
	virtual void onNotify(Card& card, EVENT event) override;
	virtual void onNotify(Card* card, EVENT event) override;
};

