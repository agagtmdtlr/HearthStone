#pragma once
#include "Creature.h"


class Weapon;
class Secret;

class Hero :
	public Creature
{
private :
	Weapon * weapon;
	vector<Secret *> secretCards;
public:
	Hero();
	Hero(
		BattleField * field,
		int cost, string name,
		int power, int shield,
		int attcount,
		bool agro, bool holy,
		bool hide, Weapon * weapon = nullptr
	);
	virtual ~Hero();

	virtual void Use() override;
	virtual void FirstSkill() override;

	
	virtual int GetPower() override; // ������ ���� ���� ���

	virtual int GetAttackCount() override;
	virtual void SetAttackCount(int val) override;	

	virtual vector<Secret *> * GetSecret() { return &secretCards; }
	virtual int GetSecretSize() { return (int)secretCards.size(); }
	virtual void SetSecretCard(Secret * secretCard) { secretCards.push_back(secretCard); }
		
	virtual Weapon * GetWeapon() { return weapon; }
	virtual void SetWeapon(Weapon * val);

	virtual void ReleaseWeapon()
	{
		// ���� �ı��� ���� ����Ƚ�� �ʱ�ȭ
		// 2 cnt weapon destroy when use 1cnt
		// hero org cnt 1 but we att 1
		// 2 - 1 - 1 = 0;
		// 2 cnt weapon destroy when use 2cnt
		// hero org cnt 1 but we att 2
		// 2 - 2 - 1  = - 1		
		nAttackCount -= nAttackCount - nAttackCountOrigin;
		nAttackCountTurn = nAttackCountOrigin;
	}	

	virtual void Info();
	virtual void InfoAboutWeapon();
	virtual void InfoAboutSecrets();
};

