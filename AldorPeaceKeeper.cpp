#pragma once
#include "stdafx.h"
#include "BattleField.h"
#include "AldorPeaceKeeper.h"


AldorPeaceKeeper::AldorPeaceKeeper(BattleField * field)
	:Creature(field,2,"�˵��� ��ȭ���ô�",3,3,1,false,false,false)
{	
}

void AldorPeaceKeeper::Attack(Card * target)
{
}

void AldorPeaceKeeper::FirstSkill()
{
	int e_turn = 1 - nThisCardUserNumber;
	// ��� �ʵ忡 ī�尡 ������ ȿ�� �̹ߵ�
	
	// �ʵ尡 ��� ����
	if (battleFieldOfCard->cardsOfField[e_turn].size() <= 0) return;

	vector<Card *> selectList;
	selectList.reserve(FieldMax);

	// ������ Ÿ���� ������ �ϼ����� �����ϴ��� Ȯ���ϱ�
	for (int i = 0; i < battleFieldOfCard->cardsOfField[e_turn].size(); i++)
	{
		Creature * creature = (Creature *)battleFieldOfCard->cardsOfField[e_turn][i];
		if (creature->GetMagicTargeted() == true && creature->GetInvincibility() == false)
			selectList.push_back(creature);
	}
	if (selectList.size() <= 0) return;

	cout << "���� �ϼ��� �ʵ�" << endl;		
	int selectNum = SelectCard(&selectList); // ī�� ����
	
	Creature * enemy = dynamic_cast<Creature *>(selectList[selectNum]);
	enemy->SetPower(-(enemy->GetPower()-1));
}

void AldorPeaceKeeper::Use()
{
	Creature::Use();
}

void AldorPeaceKeeper::Info()
{
	Creature::Info();
}

void AldorPeaceKeeper::detail()
{
	Creature::detail();
	cout << "������ �Լ� : " << endl;
	cout << "������ ���� ���ݷ��� 1�� ����ϴ�." << endl;
}
