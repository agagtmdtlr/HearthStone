#pragma once
#include "Magic.h"
class Holy_Wrath :
	public Magic
{
private:
	Creature * target;
public:
	Holy_Wrath() {}
	Holy_Wrath(
		BattleField * field
	);
	virtual ~Holy_Wrath() {}
	virtual bool FirstSkill() override;
	virtual void detail() override;

	virtual void onNotify(Card& card, EVENT event) override;
	virtual void onNotify(Card* card, EVENT event) override;
};

