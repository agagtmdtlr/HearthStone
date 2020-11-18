#pragma once
#include "Secret.h"
class Hand_Of_Salvation :
	public Secret
{
private:
	int nDeathCount;
public:
	Hand_Of_Salvation() {}
	Hand_Of_Salvation(
		BattleField * field
	);
	virtual void FirstSkill() override;
	virtual void onNotify(Card& card, EVENT event) override;
	virtual void onNotify(Card* card, EVENT event) override;
};

