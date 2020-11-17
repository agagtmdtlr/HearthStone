#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"
#include "Holy_Wrath.h"

Holy_Wrath::Holy_Wrath(BattleField * field, int cost, string name, int power)
	:Magic(field, 5, "신의 격노", 0, true)
{
	battleFieldOfCard->observers[nThisCardUserNumber].push_back(this);
}

bool Holy_Wrath::FirstSkill()
{
	Card * card = SelectCardOfFieldAndHero();
	if (card == nullptr)
	{
		return false;
	}
	else
	{
		target = (Creature *)card;
		battleFieldOfCard->Draw(nThisCardUserNumber);
	}
	
}

void Holy_Wrath::detail()
{
	Magic::detail();
	cout << "카드를 뽑고 그 카드의 비용만큼 피해를 줍니다." << endl;
}

void Holy_Wrath::onNotify(Card & card, EVENT event)
{
	if (card.GetThisCardUser() == nThisCardUserNumber && event == EVENT::DRAW)
	{
		target->SetShield(-card.GetCost());
	}
	EraseObserverFromObserverList(nThisCardUserNumber);
}

void Holy_Wrath::onNotify(Card * card, EVENT event)
{
	if (card->GetThisCardUser() == nThisCardUserNumber && event == EVENT::DRAW)
	{
		target->SetShield(-card->GetCost());
	}
	EraseObserverFromObserverList(nThisCardUserNumber);
}
