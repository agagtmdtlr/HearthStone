#pragma once
#include "Card.h"
class Magic :
	public Card
{
protected:
	int nPower;
	int nPowerBonus;
public:
	Magic();
	Magic(
		BattleField * field,
		int cost,
		string name,
		int power
	);
	virtual ~Magic();

	virtual int GetPower()
	{
		if (nPower + nPowerBonus < 0) return 0;
		else return nPower + nPowerBonus;
	}
	virtual int GetPowerBonus() { return nPowerBonus; }
	virtual void SetPowerBonus(int val) { nPowerBonus = val; }
	
	virtual void Use() override;
	virtual void FirstSkill();
	virtual void Info() override;
	virtual void detail() override;
};

