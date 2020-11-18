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
		BattleField * field
	);
	virtual ~Blessed_Champion() {}
	virtual bool FirstSkill() override;
	virtual void detail() override;
};


