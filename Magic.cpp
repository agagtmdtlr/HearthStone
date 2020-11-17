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
	// 실제로 타케팅 가능한 하수인이 존재하는지 확인하기
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

	// 필드에 하수인이 존재하므로 선택을 수행한다.
	int selectNum;
	int fieldNum = 0;
	int endNum = 0;
	if (selectList[0].size() > 0 && selectList[1].size() > 0)
	{
		while (1)
		{
			cout << "필드를 선택하시오(0.내 필드  1.상대 필드)" << endl;
			fieldNum = InputVariable<int>(fieldNum);
			fieldNum = (fieldNum + nThisCardUserNumber) % 2;
			selectNum = SelectCard(&selectList[fieldNum]);

			cout << "최종 선택을 완료하시겠습니까? (0.아니오 1.네)" << endl;
			endNum = InputVariable<int>(endNum);
			if (endNum != 0) break;
		}

	}
	else
	{
		while (1)
		{
			if (targetSum[nThisCardUserNumber] > 0) // 내필드에서 선택
			{
				fieldNum = nThisCardUserNumber;
				selectNum = SelectCard(&selectList[fieldNum]);

			}
			else // 적 필드에서 선택
			{
				fieldNum = 1 - nThisCardUserNumber;
				selectNum = SelectCard(&selectList[fieldNum]);
			}

			cout << "최종 선택을 완료하시겠습니까? (0.아니오 1.네)" << endl;
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
		// 상대 영웅
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
		cout << "누구를 선택 하시겠습니까?(0.영웅 1.하수인 2.취소)" << endl;
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
			cout << "카드를 사용할 수 없습니다" << endl;
			Sleep(500);
		}
		cout << "=================================" << endl;
		cout << "==" << strName << "를(을) 사용합니다==" << endl;
		cout << "=================================" << endl;
		battleFieldOfCard->cost[turn] -= nCost; // 코스트 소모		
		Card::Use();
		isDelete = true;
	}
	else
	{
		cout << "=================================" << endl;
		cout << "==가지고 있는 코스트가 부족합니다.==" << endl;
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
	cout << "이름 : " << strName << endl
		<< "코스트 : " << nCost << endl
		<< "파워 : " << nPower << endl;
}
