#pragma once
#include "Magic.h"
class Blessing_Of_Might :
	public Magic
{
private:
	string strDescribeSkillDetail;
public:
	Blessing_Of_Might() {}
	Blessing_Of_Might(
		BattleField * field,
		int cost,
		string name,
		int power
	);
	virtual ~Blessing_Of_Might() {}
	virtual bool FirstSkill() override;
	virtual void detail() override;
};

