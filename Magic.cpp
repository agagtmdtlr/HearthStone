#pragma once
#include "stdafx.h"
#include "BattleField.h"
#include "Creature.h"
#include "Hero.h"
#include "Magic.h"

Magic::Magic()
{
}

Magic::Magic(BattleField * field, int cost, string name, int power, bool damage)
	:Card(cost, name, field), nPower(power), nPowerBonus(0), isDamageMagic(damage)
{
}

Magic::~Magic()
{
}

Creature * Magic::SelectCreatureOfAllField()
{
	// ������ Ÿ���� ������ �ϼ����� �����ϴ��� Ȯ���ϱ�
	vector<Card *> selectList[2];
	int targetSum[2] = { 0,0 };
	for (int i = 0; i < 2; i++)
	{
		selectList[i].reserve(FieldMax);
		for (int j = 0; j < battleFieldOfCard->cardsOfField[i].size(); j++)
		{
			Creature * creature = (Creature *)battleFieldOfCard->cardsOfField[i][j];

			if (creature->GetThisCardUser() != nThisCardUserNumber)
			{
				if (creature->GetMagicTargeted() == true &&
					creature->GetInvincibility() == false)
				{
					selectList[i].push_back(creature);
					targetSum[i]++;
				}
			}
			else
			{
				selectList[i].push_back(creature);
				targetSum[i]++;
			}
		}
	}
	if (targetSum[0] + targetSum[1] <= 0) return nullptr;

	// �ʵ忡 �ϼ����� �����ϹǷ� ������ �����Ѵ�.
	int selectNum;
	int fieldNum = 0;
	int endNum = 0;
	if (selectList[0].size() > 0 && selectList[1].size() > 0)
	{
		while (1)
		{
			cout << "�ʵ带 �����Ͻÿ�(0.�� �ʵ�  1.��� �ʵ�)" << endl;
			fieldNum = InputVariable<int>(fieldNum);
			fieldNum = (fieldNum + nThisCardUserNumber) % 2;
			selectNum = SelectCard(&selectList[fieldNum]);

			cout << "���� ������ �Ϸ��Ͻðڽ��ϱ�? (0.�ƴϿ� 1.��)" << endl;
			endNum = InputVariable<int>(endNum);
			if (endNum != 0) break;
		}

	}
	else
	{
		while (1)
		{
			if (targetSum[nThisCardUserNumber] > 0) // ���ʵ忡�� ����
			{
				fieldNum = nThisCardUserNumber;
				selectNum = SelectCard(&selectList[fieldNum]);

			}
			else // �� �ʵ忡�� ����
			{
				fieldNum = 1 - nThisCardUserNumber;
				selectNum = SelectCard(&selectList[fieldNum]);
			}

			cout << "���� ������ �Ϸ��Ͻðڽ��ϱ�? (0.�ƴϿ� 1.��)" << endl;
			endNum = InputVariable<int>(endNum);
			if (endNum != 0) break;
		}

	}
	Creature * creature = dynamic_cast<Creature *>(selectList[fieldNum][selectNum]);
	return creature;
}

Hero * Magic::SelectHeroOfUser()
{
	vector<Card *> selectList;

	int targetSum[2] = { 0,0 };
	for (int i = 0; i < 2; i++)
	{

		Creature * creature = (Creature *)battleFieldOfCard->User[i];
		if (i == nThisCardUserNumber)
			selectList.push_back(creature);
		// ��� ����
		if (creature->GetMagicTargeted() == true &&
			creature->GetInvincibility() == false &&
			i != nThisCardUserNumber)
		{
			selectList.push_back(creature);
			targetSum[i]++;
		}
	}
	if (selectList.size() == 1)
		return (Hero *)selectList[0];
	int selectNum = SelectCard(&selectList);
	Hero * hero = (Hero*)selectList[selectNum];
	return hero;
}

Card * Magic::SelectCardOfFieldAndHero()
{
	int inputNum = 0;
	bool quitLoop = true;
	do
	{
		cout << "������ ���� �Ͻðڽ��ϱ�?(0.���� 1.�ϼ��� 2.���)" << endl;
		inputNum = InputVariable<int>(inputNum);
		Hero * hero = nullptr;
		Creature * creature = nullptr;
		switch (inputNum)
		{
		case 0:
			
			hero = SelectHeroOfUser();
			return hero;
			
		case 1:
			
			creature = SelectCreatureOfAllField();
			if (creature != nullptr)
			{
				return creature;				
			}
			else
			{
				quitLoop = false;
				break;
			}
		case 2:
			return nullptr;
		default:
			quitLoop = false;
			break;
		}
	} while (!quitLoop);
	return nullptr;
}

void Magic::Use()
{
	int turn = nThisCardUserNumber;
	if (battleFieldOfCard->cost[turn] >= nCost)
	{
		if (this->FirstSkill() == false)
		{
			cout << "ī�带 ����� �� �����ϴ�" << endl;
			Sleep(500);
		}
		cout << "=================================" << endl;
		cout << "==" << strName << "��(��) ����մϴ�==" << endl;
		cout << "=================================" << endl;
		battleFieldOfCard->cost[turn] -= nCost; // �ڽ�Ʈ �Ҹ�		
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

bool Magic::FirstSkill()
{
	return true;
}

void Magic::Info()
{
	cout << strName << "|" << nCost;
	if (isDamageMagic) cout << "|" << nPower + nPowerBonus;
	else cout << "|" << nPower;

}

void Magic::detail()
{
	cout << "�̸� : " << strName << endl
		<< "�ڽ�Ʈ : " << nCost << endl
		<< "�Ŀ� : " << nPower << endl;
}
