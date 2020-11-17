#pragma once
#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"


Creature::Creature(
	BattleField * field,
	int cost, string name,
	int power, int shield,
	int attcount, 
	bool agro, bool holy,
	bool invincibility
)
	:Card(cost, name,field),
	nPower(power), nShield(shield), nPreviouShield(shield), nMaxShield(shield),
	nPowerOrigin(power), nShieldOrigin(shield),
	nAttackCount(0),nAttackCountTurn(attcount), nAttackCountOrigin(attcount),	
	isAgro(agro),isAgroOrigin(agro),
	isHolyShiled(holy), isHolyShiledOrigin(holy),
	isSilence(false), 
	isInvincibility(invincibility),
	isAttackTargeted(true), isAttackTargetedOrigin(true),
	isMagicTargeted(true), isMagicTargetedOrigin(true), 
	isIced(false), isIcedOrigin(false)	
{}

void Creature::SilenceStat()
{
	Card::InitStat();
	// 3 cur / 7 max/ 2 origin
	// max = orgin = 2
	// if cur > max : cur = max
	// ü�� �ʱ�ȭ
	nMaxShield = nShieldOrigin;
	if(nShield > nMaxShield) // ü���� �⺻ ü�º��� ������ �ִ�ü������ ���߱�
		nShield = nMaxShield;
	// �Ŀ� �ʱ�ȭ
	if(nPower > nPowerOrigin)
		nPower = nPowerOrigin;
	// ����Ƚ�� �ʱ�ȭ
	nAttackCountTurn = nAttackCountOrigin;
	if (nAttackCount > nAttackCountTurn)
		nAttackCount = nAttackCountTurn;
	isAgro = false;
	isHolyShiled = false;
	isIced = false;
	isAttackTargeted = true;
	isMagicTargeted = true;
}

void Creature::InitStat()
{
	Card::InitStat();
	isDelete = false;
	nMaxShield = nShieldOrigin;
	nShield = nShieldOrigin;	
	nPower = nPowerOrigin;
	nAttackCountTurn = nAttackCountOrigin;
	nAttackCount = 0;
	isAgro = isAgroOrigin;
	isHolyShiled = isHolyShiledOrigin;
	isIced = isIcedOrigin;
	isAttackTargeted = isAttackTargetedOrigin;
	isMagicTargeted = isMagicTargetedOrigin;
	isSilence = false;
	isInvincibility = false;
	strPlusSkillDetail = "";
}

void Creature::SetShield(int val)
{
	if (isInvincibility == true) // ������ ���� �ȹ���
		return;
	if (isHolyShiled && val < 0)
	{
		isHolyShiled = false;
		return;
	}
	// ���� ü���� ����.
	nPreviouShield = nShield;
	// ü�� ���� ���
	int result = nShield + val;
	// ȸ���� �ִ� ü���� �Ѿ�� �� ����. ( ȸ���� ü�� ������ �ٸ��� )
	if (result > nMaxShield) result = nMaxShield;
	
	if (result != nShield) // ü���� ��ȭ�� �ִ°�
	{
		EVENT event;
		// ���� ü�� ���� �������� ������������ �����ȴ�.
		if (result < nShield)
			event = EVENT::DAMAGE;
		// ���� ü�� ���� �ö󰡾� ȸ������ �����ȴ�.
		else if (result > nShield)
			event = EVENT::HEAL;		
		// ���� ü���� ����
		nShield = result;
		ExcuteObserver(event);
	}

	if (nShield <= 0) // ī�� �Ҹ� �Ǵ�
	{
		ExcuteObserver(EVENT::DIE);
		isDelete = true;
	}		
}

void Creature::Use()
{
	int turn = nThisCardUserNumber;

	if (battleFieldOfCard->cardsOfField[turn].size() >= FieldMax)
	{
		cout << "=================================" << endl;
		cout << "==      �ʵ尡 �� á���ϴ�.     ==" << endl;
		cout << "=================================" << endl;
		Sleep(1000);
		return;
	}

	if (battleFieldOfCard->cost[turn] >= nCost)
	{
		battleFieldOfCard->cost[turn] -= nCost; // �ڽ�Ʈ �Ҹ�
		if (isSilence == false)
			FirstSkill();
		SummonCreature(turn);
		Card::Use();
	}
	else
	{
		cout << "=================================" << endl;
		cout << "==������ �ִ� �ڽ�Ʈ�� �����մϴ�.==" << endl;
		cout << "=================================" << endl;
	}
	Sleep(1000);
}

void Creature::SummonCreature(int turn)
{
	cout << "=================================" << endl;
	cout << "==" << strName << "��(��) ��ȯ�մϴ�==" << endl;
	cout << "=================================" << endl;	
	battleFieldOfCard->cardsOfField[turn].push_back(this);	
	ExcuteObserver(EVENT::FIELD);
	
}



void Creature::SetSilence(bool val)
{
	isSilence = val;
	
	if (isSilence == true)
	{
		ExcuteObserver(EVENT::SILENCE);
		InitStat();
	}
		
}
void Creature::AttackSkill(Card * target)
{
	return;
}

void Creature::FirstSkill()
{
	return;
}

void Creature::Info() // ��� ����
{
	cout << strName << "|" << nCost << "|" << nPower << "|" << nShield;
	if (isAgro) cout << "|��";
	else cout << "|X";
	if (isHolyShiled) cout << "|��";
	else cout << "|X";
}

void Creature::detail() // ���� ����
{
	cout << "�̸� : " << strName << endl
		<< "�ڽ�Ʈ : " << nCost << endl
		<< "�Ŀ� : " << nPower << endl
		<< "ü�� : " << nShield << endl;
	cout << "��׷� : ";
	if (isAgro) cout << "����" << endl;
	else cout << "����" << endl;
	cout << "õ���� ��ȣ�� : ";
	if (isHolyShiled) cout << "����" << endl;
	else cout << "����" << endl;
	cout << strPlusSkillDetail << endl;
}








