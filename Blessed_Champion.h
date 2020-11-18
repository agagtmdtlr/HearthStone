#pragma once
#include "Magic.h"
class Blessed_Champion :
	public Magic
{
private:
	string strDescribeSkillDetail;
public:
	Blessed_Champion() {}
	Blessed_Champion(
		BattleField * field,
		int cost,
		string name,
		int power
	);
	virtual ~Blessed_Champion() {}
	virtual bool FirstSkill() override;
	virtual void detail() override;
};


