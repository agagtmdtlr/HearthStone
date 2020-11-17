#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"
#include "Blessing_Of_Aeons.h"

Blessing_Of_Aeons::Blessing_Of_Aeons(BattleField * field, int cost, string name, int power)
	:Magic(field, 1, "������ �ູ", 1, false)
{
	strDescribeSkillDetail = "\n�ϼ��ο���\n\"�� ���� ���� ��, +1/+1�� ����\"�ɷ��� �ο��մϴ�.";
}

bool Blessing_Of_Aeons::FirstSkill()
{
	Creature * creature = SelectCreatureOfAllField();
	if (creature == nullptr)
	{
		return false;
	}
	else
	{
		target = creature;
		target->SetPlusSkillDetail(strDescribeSkillDetail);
		battleFieldOfCard->observers[nThisCardUserNumber].push_back(this);
		// �ش� �ϼ��� ���� ��� ���� ������ ����Ʈ���� ����(�ϼ����� �װų� ħ���ɸ�
		// ��� �����ϱ� ���� �ϱ� ����)
		if(target->GetThisCardUser() != nThisCardUserNumber)
			battleFieldOfCard->observers[1 - nThisCardUserNumber].push_back(this);
		return true;
	}	
}

void Blessing_Of_Aeons::detail()
{
	Magic::detail();
	cout << strDescribeSkillDetail << endl;
}

void Blessing_Of_Aeons::onNotify(Card & card, EVENT event)
{
	// �� ���� ������(�ش� ����ī�带 ����� ������ ��)
	if (event == EVENT::END &&
		nThisCardUserNumber == battleFieldOfCard->nPlayerTurn % 2)
	{
		target->SetPower(nPower);
		target->SetMaxShield(nPower);
	}

	// ��� ī�尡 �װų� ħ���� �ɷ��� ���
	if (&card == target && ( event == EVENT::SILENCE || event == EVENT::DIE ))
	{
		EraseObserverFromObserverList(nThisCardUserNumber);
		if (target->GetThisCardUser() != nThisCardUserNumber)
			EraseObserverFromObserverList(1- nThisCardUserNumber);
	}
}

void Blessing_Of_Aeons::onNotify(Card * card, EVENT event)
{
	// �� ���� ������(�ش� ����ī�带 ����� ������ ��)
	if (event == EVENT::END &&
		nThisCardUserNumber == battleFieldOfCard->nPlayerTurn % 2)
	{
		target->SetPower(nPower);
		target->SetMaxShield(nPower);
	}

	// ��� ī�尡 �װų� ħ���� �ɷ��� ���
	if (card == target && (event == EVENT::SILENCE || event == EVENT::DIE))
	{
		EraseObserverFromObserverList(nThisCardUserNumber);
		if (target->GetThisCardUser() != nThisCardUserNumber)
			EraseObserverFromObserverList(1 - nThisCardUserNumber);
	}
}
