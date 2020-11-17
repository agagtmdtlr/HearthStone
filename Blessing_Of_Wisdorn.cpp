#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"
#include "Blessing_Of_Wisdorn.h"

Blessing_Of_Wisdorn::Blessing_Of_Wisdorn(BattleField * field, int cost, string name, int power)
	:Magic(field, 1, "������ �ູ", 0, false)
{
	strDescribeSkillDetail = "\n�ϼ����� �����մϴ�.\n�� �ϼ��� ������ ������ ī�带 �̽��ϴ�.";
}

bool Blessing_Of_Wisdorn::FirstSkill()
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
		if (target->GetThisCardUser() != nThisCardUserNumber)
			battleFieldOfCard->observers[1 - nThisCardUserNumber].push_back(this);
		return true;
	}
	return false;
}

void Blessing_Of_Wisdorn::detail()
{
	Magic::detail();
	cout << strDescribeSkillDetail << endl;
}

void Blessing_Of_Wisdorn::onNotify(Card & card, EVENT event)
{
	// �� ���� ������(�ش� ����ī�带 ����� ������ ��)
	if (event == EVENT::ATTACK && &card == target)
	{
		battleFieldOfCard->Draw(nThisCardUserNumber);
	}

	// ��� ī�尡 �װų� ħ���� �ɷ��� ���
	if (&card == target && (event == EVENT::SILENCE || event == EVENT::DIE))
	{
		EraseObserverFromObserverList(nThisCardUserNumber);
		if (target->GetThisCardUser() != nThisCardUserNumber)
			EraseObserverFromObserverList(1 - nThisCardUserNumber);
	}
}

void Blessing_Of_Wisdorn::onNotify(Card * card, EVENT event)
{
	// �� ���� ������(�ش� ����ī�带 ����� ������ ��)
	if (event == EVENT::ATTACK && card == target)
	{
		battleFieldOfCard->Draw(nThisCardUserNumber);
	}

	// ��� ī�尡 �װų� ħ���� �ɷ��� ���
	if (card == target && (event == EVENT::SILENCE || event == EVENT::DIE))
	{
		EraseObserverFromObserverList(nThisCardUserNumber);
		if (target->GetThisCardUser() != nThisCardUserNumber)
			EraseObserverFromObserverList(1 - nThisCardUserNumber);
	}
}
