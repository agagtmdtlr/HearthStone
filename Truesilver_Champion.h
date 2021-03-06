#pragma once
#include "Weapon.h"
class Truesilver_Champion :
	public Weapon
{
public:
	Truesilver_Champion() {};
	Truesilver_Champion(
		BattleField * field
	);

	Truesilver_Champion(
		int userNumber,
		BattleField * field
	);

	virtual void FirstSkill() override;

	virtual void SetDelete(bool val) override;

	virtual void onNotify(Card& card, EVENT event) override;
	virtual void onNotify(Card* card, EVENT event) override;

	virtual void detail() override;
};

