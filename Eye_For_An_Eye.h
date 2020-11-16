#pragma once
#include "Secret.h"
class Eye_For_An_Eye :
	public Secret
{
private:
	int nDeathCount;
public:
	Eye_For_An_Eye() {}
	Eye_For_An_Eye(
		BattleField * field,
		int cost,
		string name,
		int power
	);
	virtual void FirstSkill() override;
	virtual void onNotify(Card& card, EVENT event) override;
	virtual void onNotify(Card* card, EVENT event) override;
};

