#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"
#include "Blessing_Of_Aeons.h"

Blessing_Of_Aeons::Blessing_Of_Aeons(BattleField * field, int cost, string name, int power)
	:Magic(field, 1, "영겁의 축복", 1, false)
{
	strDescribeSkillDetail = "\n하수인에게\n\"내 턴이 끝날 때, +1/+1을 얻음\"능력을 부여합니다.";
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
		// 해당 하수인 적일 경우 상대방 관찰자 리스트에도 삽입(하수인이 죽거나 침묵걸릴
		// 경우 해제하기 해제 하기 위함)
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
	// 내 턴이 끝날떄(해당 마법카드를 사용한 유저의 턴)
	if (event == EVENT::END &&
		nThisCardUserNumber == battleFieldOfCard->nPlayerTurn % 2)
	{
		target->SetPower(nPower);
		target->SetMaxShield(nPower);
	}

	// 대상 카드가 죽거나 침묵에 걸렸을 경우
	if (&card == target && ( event == EVENT::SILENCE || event == EVENT::DIE ))
	{
		EraseObserverFromObserverList(nThisCardUserNumber);
		if (target->GetThisCardUser() != nThisCardUserNumber)
			EraseObserverFromObserverList(1- nThisCardUserNumber);
	}
}

void Blessing_Of_Aeons::onNotify(Card * card, EVENT event)
{
	// 내 턴이 끝날떄(해당 마법카드를 사용한 유저의 턴)
	if (event == EVENT::END &&
		nThisCardUserNumber == battleFieldOfCard->nPlayerTurn % 2)
	{
		target->SetPower(nPower);
		target->SetMaxShield(nPower);
	}

	// 대상 카드가 죽거나 침묵에 걸렸을 경우
	if (card == target && (event == EVENT::SILENCE || event == EVENT::DIE))
	{
		EraseObserverFromObserverList(nThisCardUserNumber);
		if (target->GetThisCardUser() != nThisCardUserNumber)
			EraseObserverFromObserverList(1 - nThisCardUserNumber);
	}
}
