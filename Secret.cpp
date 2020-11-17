#pragma once
#include "stdafx.h"
#include "BattleField.h"
#include "Hero.h"
#include "Secret.h"


Secret::Secret(BattleField * field, int cost, string name, int power)
	:Card(cost, name, field),
	nPower(power),nPowerOrigin(power)
{
}

void Secret::Use()
{
	int turn = battleFieldOfCard->nPlayerTurn % 2;	

	if (battleFieldOfCard->cost[turn] >= nCost)
	{
		Hero * hero = (Hero*)battleFieldOfCard->User[turn];
		if (hero->GetSecretSize() < 3)
			hero->SetSecretCard(this);
		else
		{
			cout << "====================================" << endl;
			cout << "== ���ī�带 �� ������ �� �����ϴ� .==" << endl;
			cout << "====================================" << endl;
			Sleep(1000);
			return;
		}			

		battleFieldOfCard->cost[turn] -= nCost; // �ڽ�Ʈ �Ҹ�
		cout << "=================================" << endl;
		cout << "== ���ī�� : " << strName << "��(��) �����մϴ�==" << endl;
		cout << "=================================" << endl;
		FirstSkill();		
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

void Secret::Info()
{
	cout << strName << "|" << nCost;
}

void Secret::detail()
{
	cout << "�̸� : " << strName << endl
		<< "�ڽ�Ʈ : " << nCost << endl;		
}

void Secret::FirstSkill()
{
}
