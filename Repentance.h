#pragma once
#include "Secret.h"
class Repentance :
	public Secret
{
public:
	Repentance() {}
	Repentance(
		BattleField * field,
		int cost,
		string name,
		int power
	);
	virtual void FirstSkill() override;
	virtual void detail() override;
	virtual void onNotify(Card& card, EVENT event) override;
	virtual void onNotify(Card* card, EVENT event) override;
};

