#pragma once
#include "Magic.h"
class Blessing_Of_Wisdorn :
	public Magic
{
private:
	Creature * target;
	string strDescribeSkillDetail;
public:
	Blessing_Of_Wisdorn() {}
	Blessing_Of_Wisdorn(
		BattleField * field
	);
	virtual ~Blessing_Of_Wisdorn() {}
	virtual bool FirstSkill() override;
	virtual void detail() override;

	virtual void onNotify(Card& card, EVENT event) override;
	virtual void onNotify(Card* card, EVENT event) override;
};

