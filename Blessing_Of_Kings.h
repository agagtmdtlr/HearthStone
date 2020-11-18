#pragma once
#include "Magic.h"
class Blessing_Of_Kings :
	public Magic
{
private:
	string strDescribeSkillDetail;
public:
	Blessing_Of_Kings() {}
	Blessing_Of_Kings(
		BattleField * field		
	);
	virtual ~Blessing_Of_Kings() {}
	virtual bool FirstSkill() override;
	virtual void detail() override;

	
};

