#include "stdafx.h"
#include "BattleField.h"
#include "Sword_Of_Justice.h"

Sword_Of_Justice::Sword_Of_Justice(BattleField * field)
	:Weapon(field, 3, "������ Į��", 1, 5, 1)
{
}

Sword_Of_Justice::Sword_Of_Justice(int userNumber, BattleField * field)
	: Weapon(userNumber, field, 3, "������ Į��", 1, 5, 1)
{
}

void Sword_Of_Justice::FirstSkill()
{
	battleFieldOfCard->observers[nThisCardUserNumber].push_back(this);
}

void Sword_Of_Justice::SetDelete(bool val)
{
	Weapon::SetDelete(val);
	// ���� �ı��� ī�� ������ ����
	if (isDelete == true)
		EraseObserverFromObserverList(nThisCardUserNumber);
}

void Sword_Of_Justice::onNotify(Card & card, EVENT event)
{

	if (event == EVENT::FIELD && card.GetThisCardUser() == nThisCardUserNumber)
	{
		Creature * target = (Creature *)&card;
		target->SetPower(1);
		target->SetMaxShield(1);
		SetDurability(-1);
	}
}

void Sword_Of_Justice::onNotify(Card * card, EVENT event)
{
	if (card == nullptr) return;
	if (event == EVENT::FIELD && card->GetThisCardUser() == nThisCardUserNumber)
	{
		Creature * target = (Creature *)card;
		target->SetPower(1);
		target->SetMaxShield(1);
		SetDurability(-1);
	}
}

void Sword_Of_Justice::detail()
{
	Weapon::detail();
	cout << "�� �ϼ����� ��ȯ�� �Ŀ�," <<
		"\n�� �ϼ��ο��� +1/+1�� �ο��ϰ� �������� 1�ҽ��ϴ�." << endl;
}
