#pragma once
#include "Magic.h"
class Blessing_Of_Aeons :
	public Magic
{
private:
	Creature * target;
	string strDescribeSkillDetail;
public:
	Blessing_Of_Aeons() {}
	Blessing_Of_Aeons(
		BattleField * field	
	);
	virtual ~Blessing_Of_Aeons() {}
	virtual bool FirstSkill() override;
	virtual void detail() override;

	virtual void onNotify(Card& card, EVENT event) override;
	virtual void onNotify(Card* card, EVENT event) override;
};

