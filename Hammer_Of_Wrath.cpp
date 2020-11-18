#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"
#include "Hammer_Of_Wrath.h"

Hammer_Of_Wrath::Hammer_Of_Wrath(BattleField * field)
	:Magic(field, 4, "õ���� ��ġ", 3, true)
{
}

bool Hammer_Of_Wrath::FirstSkill()
{
	Card * card = SelectCardOfFieldAndHero();
	if (card == nullptr)
	{
		return false;
	}
	else
	{
		Creature * target = (Creature *)card;
		target->SetShield(-(nPower + nPowerBonus));
		battleFieldOfCard->Draw(nThisCardUserNumber);
		return true;
	}
}

void Hammer_Of_Wrath::detail()
{
	Magic::detail();
	cout << "���ظ� " << nPower + nPowerBonus << "�� �ݴϴ�" << endl
		<< "ī�带 �̽��ϴ�." << endl;	
}
