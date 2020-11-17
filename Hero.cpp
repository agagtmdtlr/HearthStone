#pragma once
#include "stdafx.h"
#include "BattleField.h"
#include "Weapon.h"
#include "Secret.h"
#include "Hero.h"

Hero::Hero()
{
}

Hero::Hero(BattleField * field, int cost, string name, int power, int shield, int attcount, bool agro, bool holy, bool hide, Weapon * weapon_)
	: Creature(field, cost, name, power, shield, attcount, agro, holy, hide)
{
	if (weapon_ != nullptr)
		weapon = weapon_;
	else
		weapon = nullptr;
}


Hero::~Hero()
{
}

void Hero::Use()
{
	int turn = battleFieldOfCard->nPlayerTurn % 2;
	
	if (battleFieldOfCard->cost[turn] >= nCost)
	{
		battleFieldOfCard->cost[turn] -= nCost; // �ڽ�Ʈ �Ҹ�
		cout << "=================================" << endl;
		cout << "==" << strName << "��(��) ��ȯ�մϴ�==" << endl;
		cout << "=================================" << endl;
		
		if (isSilence == false)
			FirstSkill();

		Card * beforeHero = battleFieldOfCard->User[turn];
		battleFieldOfCard->User[turn] = this;
		delete beforeHero;
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

void Hero::FirstSkill()
{
	int turn = battleFieldOfCard->nPlayerTurn % 2;
	Hero * beforeHero = (Hero *)battleFieldOfCard->User[turn];	
	// ���� ������ ������ ���⸦ ��������
	weapon = beforeHero->GetWeapon();
	// ���� ���� ���� ����
	beforeHero->SetWeapon(nullptr);
	
}

int Hero::GetPower()
{
	int nTotalPower = nPower;
	if (weapon != nullptr)
		nTotalPower += weapon->GetPower();
	return nTotalPower;
}

int Hero::GetAttackCount()
{
	return Creature::GetAttackCount();
}

void Hero::SetAttackCount(int val)
{
	nAttackCount += val;
	if (weapon != nullptr) // ���ݽ� ���� ���� �������� ������
		weapon->SetDurability(val);	
}

void Hero::SetWeapon(Weapon * val)
{
	if (weapon != nullptr)// ���� �����ϱ����� �̹� ���Ǿ� �ִٸ� �ٲ� ����.
	{
		weapon->SetDelete(true); // �������⸦ �����ϰ� ������������ ������.
		battleFieldOfCard->garbageCollector[nThisCardUserNumber].push_back(weapon);
		weapon = nullptr;
	}
	weapon = val;
	// ���Ⱑ ���� �����Ƿ� ������ ����Ƚ���� ���⿡ �����.
	if (weapon != nullptr)
	{
		nAttackCountTurn = weapon->GetAttackCount();
		nAttackCount = nAttackCountTurn;
	}
}
