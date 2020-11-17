#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"
#include "Lay_On_Hands.h"

Lay_On_Hands::Lay_On_Hands(BattleField * field, int cost, string name, int power)
	:Magic(field, 8, "���� �ູ", 8, false)
{
}

bool Lay_On_Hands::FirstSkill()
{
	Card * card = SelectCardOfFieldAndHero();
	if (card == nullptr)
	{
		return false;
	}
	else
	{
		Creature * target = (Creature *)card;
		target->SetShield(nPower);
		for (int i = 0; i < 3; i++)
			battleFieldOfCard->Draw(nThisCardUserNumber);
		return true;
	}	
}

void Lay_On_Hands::detail()
{
	Magic::detail();
	cout << "������� 8ȸ����ŵ�ϴ�." << endl;
	cout << "ī�带 3�� �̽��ϴ�." << endl;
}
