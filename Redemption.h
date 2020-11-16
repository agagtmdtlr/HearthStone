#pragma once
#include "Secret.h"
class Redemption :
	public Secret
{
public:
	Redemption() {}
	Redemption(
		BattleField * field,
		int cost,
		string name,
		int power
	);
	virtual void FirstSkill() override;
	virtual void onNotify(Card& card, EVENT event) override;
	virtual void onNotify(Card* card, EVENT event) override;
};

