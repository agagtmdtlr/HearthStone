#pragma once
#include "Secret.h"
class Noble_Sacrifice :
	public Secret
{
public:
	Noble_Sacrifice() {}
	Noble_Sacrifice(
		BattleField * field
	);
	virtual void FirstSkill() override;
	virtual void onNotify(Card& card, EVENT event) override;
	virtual void onNotify(Card* card, EVENT event) override;
};



