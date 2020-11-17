#pragma once
#include "Card.h"

class BattleField;

class Creature :
	public Card
{
protected:
	int nPower;
	int nPowerOrigin;	

	int nShield;
	int nPreviouShield;
	int nMaxShield;
	int nShieldOrigin;	

	int nAttackCount; // ���� ���� ���� Ƚ��
	int nAttackCountTurn; // �ϸ��� �־����� ����Ƚ��
	int nAttackCountOrigin;	 // �ʱ� ���� ����Ƚ��

	bool isAgro; // ���� ������ �� ����� �켱���� �����ؾ� ��
	bool isAgroOrigin;
	/*
	��׷δ� ��� �����ϸ� ��׷ΰ� �ƴ� ��븦 �������� ���ϰ� ���� ��
	�������?
	*/
	bool isHolyShiled; // õ���� ��ȣ�� �ѹ��� ������ �����ϴ�.
	bool isHolyShiledOrigin;

	bool isSilence; // ħ��

	bool isInvincibility; // ����
	
	bool isIced;
	bool isIcedOrigin;

	bool isAttackTargeted;
	bool isAttackTargetedOrigin;

	bool isMagicTargeted;
	bool isMagicTargetedOrigin;

public:
	Creature(){}
	Creature(
		BattleField * field,
		int cost, string name,
		int power, int shield,
		int attcount,
		bool agro, bool holy,
		bool invincibility
		);
	virtual ~Creature(){}

	virtual void SilenceStat();	
	virtual void InitStat() override;

	virtual int GetPower() { return nPower; }
	virtual void SetPower(int val) 
	{		
		nPower += val; 
		if (nPower < 0) nPower = 0;		
	}

	virtual int GetPowerOrigin() { return nPowerOrigin; }
	virtual void SetPowerOrigin(int val) 
	{
		nPowerOrigin += val; 
		if (nPowerOrigin < 0) nPowerOrigin = 0;
	}

	virtual void SetDelete(bool val)
	{
		Card::SetDelete(val);
	}

	virtual int GetShield() { return nShield; }
	virtual void SetShield(int val);	
	virtual void ChangeShield(int val)
	{
		nShield = val;
		if (nShield < 1) nShield = 1;
	}

	virtual int GetPreviousShield() { return nShield; }

	virtual int GetMaxShield() { return nMaxShield; }
	
	virtual void SetMaxShield(int val)// �ִ� ü�� ����
	{ 
		nMaxShield += val;
		// 3 / 5 -> 3 / 5-3=2 
		// 2-3=-1 -> 3+(-1) = 2;
		nShield += val;
		if (nShield < 1) nShield = 1;
	}	

	virtual int GetShieldOrigin() { return nShieldOrigin; }	
	virtual void ChangeShieldOrigin(int val) { nShieldOrigin = val; }

	virtual int GetAttackCount() { return nAttackCount; }
	virtual void SetAttackCount(int val) { nAttackCount += val; }

	virtual int GetAttackCountTurn() { return nAttackCountTurn; }
	virtual void SetAttackCountTurn(int val) { nAttackCountTurn += val;	}

	virtual int GetAttackCountOrigin() { return nAttackCountOrigin; }
	virtual void SetAttackCountOrigin(int val) { nAttackCountOrigin += val; }
		
	virtual bool GetHolyShiled() { return isHolyShiled; }
	virtual void SetHolyShield(bool val) { isHolyShiled = val; }

	virtual bool GetAgro() { return isAgro; }	
	
	virtual bool GetSilence() { return isSilence; }
	virtual void SetSilence(bool val);
	
	virtual bool GetAttackTargeted() { return isAttackTargeted; }
	virtual void SetAttackTargeted(bool val) { isAttackTargeted = val; }
	
	virtual bool GetMagicTargeted() { return isMagicTargeted; }
	virtual void SetMagicTargeted(bool val) { isMagicTargeted = val; }

	virtual bool GetInvincibility() { return isInvincibility; }
	virtual void SetInvincibility(bool val) { isInvincibility = val; }

	virtual bool GetIced() { return isIced; }
	virtual void SetIced(bool val) { isIced = val; }

	virtual void AttackSkill(Card * target);
	virtual void FirstSkill();
	virtual void Use() override;
	virtual void SummonCreature(int turn);
	virtual void Info() override;
	virtual void detail() override;	
	
};

