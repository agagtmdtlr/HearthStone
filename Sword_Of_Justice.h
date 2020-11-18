#pragma once
#include "Weapon.h"
class Sword_Of_Justice :
	public Weapon
{
public:
	Sword_Of_Justice() {};
	Sword_Of_Justice(
		BattleField * field
	);

	Sword_Of_Justice(
		int userNumber,
		BattleField * field
	);

	virtual void FirstSkill() override;

	virtual void SetDelete(bool val) override;

	virtual void onNotify(Card& card, EVENT event) override;
	virtual void onNotify(Card* card, EVENT event) override;

	virtual void detail() override;
};

