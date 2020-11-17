#pragma once
#include "Card.h"

class Creature;
class Hero;

class Magic :
	public Card
{
protected:
	int nPower;
	int nPowerBonus;
	bool isDamageMagic;
public:
	Magic();
	Magic(
		BattleField * field,
		int cost,
		string name,
		int power,
		bool damage
	);
	virtual ~Magic();

	virtual int GetPower()
	{
		if (nPower + nPowerBonus < 0) return 0;
		else return nPower + nPowerBonus;
	}
	virtual int GetPowerBonus() { return nPowerBonus; }
	virtual void SetPowerBonus(int val) { nPowerBonus = val; }

	virtual bool GetIsDamageMagic() { return isDamageMagic; }

	virtual void Use() override;
	virtual bool FirstSkill();
	virtual void Info() override;
	virtual void detail() override;

	virtual Creature * SelectCreatureOfAllField();	// ��� ���� �ϼ��� �� �ϳ� ����
	virtual Hero * SelectHeroOfUser(); // ���� �� ����
	virtual Card * SelectCardOfFieldAndHero(); // ������ �ϼ��� �� ����

};

