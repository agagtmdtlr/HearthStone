#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"
#include "Blessing_Of_Wisdorn.h"

Blessing_Of_Wisdorn::Blessing_Of_Wisdorn(BattleField * field, int cost, string name, int power)
	:Magic(field, 1, "지혜의 축복", 0, false)
{
	strDescribeSkillDetail = "\n하수인을 선택합니다.\n그 하수인 공격할 때마다 카드를 뽑습니다.";
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
		// 해당 하수인 적일 경우 상대방 관찰자 리스트에도 삽입(하수인이 죽거나 침묵걸릴
		// 경우 해제하기 해제 하기 위함)
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
	// 내 턴이 끝날떄(해당 마법카드를 사용한 유저의 턴)
	if (event == EVENT::ATTACK && &card == target)
	{
		battleFieldOfCard->Draw(nThisCardUserNumber);
	}

	// 대상 카드가 죽거나 침묵에 걸렸을 경우
	if (&card == target && (event == EVENT::SILENCE || event == EVENT::DIE))
	{
		EraseObserverFromObserverList(nThisCardUserNumber);
		if (target->GetThisCardUser() != nThisCardUserNumber)
			EraseObserverFromObserverList(1 - nThisCardUserNumber);
	}
}

void Blessing_Of_Wisdorn::onNotify(Card * card, EVENT event)
{
	// 내 턴이 끝날떄(해당 마법카드를 사용한 유저의 턴)
	if (event == EVENT::ATTACK && card == target)
	{
		battleFieldOfCard->Draw(nThisCardUserNumber);
	}

	// 대상 카드가 죽거나 침묵에 걸렸을 경우
	if (card == target && (event == EVENT::SILENCE || event == EVENT::DIE))
	{
		EraseObserverFromObserverList(nThisCardUserNumber);
		if (target->GetThisCardUser() != nThisCardUserNumber)
			EraseObserverFromObserverList(1 - nThisCardUserNumber);
	}
}
