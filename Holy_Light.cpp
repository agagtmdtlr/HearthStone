#pragma once
#include "stdafx.h"
#include "Hero.h"
#include "Creature.h"
#include "Holy_Light.h"

Holy_Light::Holy_Light(BattleField * field, int cost, string name, int power)
	:Magic(field, 2, "성스러운 빛", 6, false)
{
}

bool Holy_Light::FirstSkill()
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
		return true;
	}
}



void Holy_Light::detail()
{
	Magic::detail();
	cout << "생명력을 6회복시킵니다" << endl;
}