#pragma once
#include "stdafx.h"
#include "BattleField.h"
#include "Weapon.h"




Weapon::Weapon(BattleField * field, int cost, string name, int power, int durability, int attcount)
	: Card(cost, name, field),
	nPower(power), nPowerOrigin(power),
	nDurability(durability), nDurabilityOrigin(durability),
	nAttackCount(attcount)
{
}

Weapon::Weapon(int userNumber, BattleField * field, int cost, string name, int power, int durability, int attcount)
	: Card(cost,name,field),
	nPower(power), nPowerOrigin(power),
	nDurability(durability), nDurabilityOrigin(durability),
	nAttackCount(attcount)
{
	nThisCardUserNumber = userNumber;
}

Weapon::~Weapon()
{
}

void Weapon::SetDelete(bool val)
{
	Card::SetDelete(val);

	if (isDelete == true)
	{
		// �ش� ���⸦ �����ϰ� �ִ� ������ ���ݰ���(Ƚ��) �ʱ�ȭ ���ش�.
		Hero * hero = (Hero *)battleFieldOfCard->User[nThisCardUserNumber];
		hero->ReleaseWeapon();
	}
}

void Weapon::Use()
{
	int turn = battleFieldOfCard->nPlayerTurn % 2;

	if (battleFieldOfCard->cost[turn] >= nCost)
	{
		battleFieldOfCard->cost[turn] -= nCost; // �ڽ�Ʈ �Ҹ�
		cout << "=================================" << endl;
		cout << "== ���� : " << strName << "��(��) �����մϴ�==" << endl;
		cout << "=================================" << endl;
		FirstSkill();
		Hero * hero = (Hero*)battleFieldOfCard->User[turn];		
		hero->SetWeapon(this); // �������� ���� ����	
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


