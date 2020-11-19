#include "stdafx.h"
#include "Hero.h"
#include "BattleField.h"
#include "Truesilver_Champion.h"

Truesilver_Champion::Truesilver_Champion(BattleField * field)
	:Weapon(field, 4, "용사의 진은검", 4, 2, 1)
{
}

Truesilver_Champion::Truesilver_Champion(int userNumber, BattleField * field)
	: Weapon(userNumber, field, 4, "용사의 진은검", 4, 2, 1)
{
}

void Truesilver_Champion::FirstSkill()
{
	battleFieldOfCard->observers[nThisCardUserNumber].push_back(this);
}

void Truesilver_Champion::SetDelete(bool val)
{
	Weapon::SetDelete(val);
	// 무기 파괴시 카드 관찰자 제거
	if (isDelete == true)
		EraseObserverFromObserverList(nThisCardUserNumber);
}

void Truesilver_Champion::onNotify(Card & card, EVENT event)
{
	Hero * hero = (Hero *)battleFieldOfCard->User[nThisCardUserNumber];
	if (event == EVENT::ATTACK && &card == hero)
		hero->SetShield(nPower);		
}

void Truesilver_Champion::onNotify(Card * card, EVENT event)
{
	if (card == nullptr) return;
	Hero * hero = (Hero *)battleFieldOfCard->User[nThisCardUserNumber];
	if (event == EVENT::ATTACK && card == hero)
		hero->SetShield(nPower);
}

void Truesilver_Champion::detail()
{
	Weapon::detail();
	cout << "내 영웅이 공격할 때마다 생명력을 [2]회복합니다." << endl;
}


