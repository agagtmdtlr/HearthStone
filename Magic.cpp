#pragma once
#include "stdafx.h"
#include "BattleField.h"
#include "Magic.h"

Magic::Magic()
{
}

Magic::Magic(BattleField * field, int cost, string name, int power)
	:Card(cost,name,field),nPower(power)
{
}

Magic::~Magic()
{
}

void Magic::Use()
{
	int turn = battleFieldOfCard->nPlayerTurn % 2;
	if (battleFieldOfCard->cost[turn] >= nCost)
	{
		battleFieldOfCard->cost[turn] -= nCost; // �ڽ�Ʈ �Ҹ�
		cout << "=================================" << endl;
		cout << "==" << strName << "��(��) ����մϴ�==" << endl;
		cout << "=================================" << endl;
		this->FirstSkill();
		Card::Use();
		isDelete = true;
	}
	else
	{
		cout << "=================================" << endl;
		cout << "==������ �ִ� �ڽ�Ʈ�� �����մϴ�.==" << endl;
		cout << "=================================" << endl;
	}
	Sleep(1000);
}

void Magic::FirstSkill()
{
}

void Magic::Info()
{
	cout << strName << "|" << nCost << "|" << nPower;
}

void Magic::detail()
{
	cout << "�̸� : " << strName << endl
		<< "�ڽ�Ʈ : " << nCost << endl
		<< "�Ŀ� : " << nPower << endl;
}
