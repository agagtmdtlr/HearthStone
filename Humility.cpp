#pragma once
#include "stdafx.h"
#include "BattleField.h"
#include "Humility.h"

Humility::Humility()	
{
}

Humility::Humility(BattleField * field)
	:Magic(field, 1, "���", 0)
{
}

void Humility::Info()
{
	cout << strName << "|" << nCost;
}

void Humility::FirstSkill()
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

			if(creature->GetThisCardUser() != nThisCardUserNumber)
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
	if (targetSum[0] + targetSum[1] <= 0) return;

	// �ʵ忡 �ϼ����� �����ϹǷ� ������ �����Ѵ�.
	int selectNum;
	int fieldNum = 0;
	if (selectList[0].size() > 0 && selectList[1].size() > 0)
	{
		cout << "�ʵ带 �����Ͻÿ�(0.�� �ʵ�  1.��� �ʵ�)" << endl;
		fieldNum = InputVariable<int>(fieldNum);
		fieldNum = (fieldNum + nThisCardUserNumber) % 2;
		selectNum = SelectCard(&selectList[fieldNum]);
	}
	else
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
	}
	Creature * enemy = dynamic_cast<Creature *>(selectList[fieldNum][selectNum]);
	enemy->SetPower(-(enemy->GetPower() - 1));
}
