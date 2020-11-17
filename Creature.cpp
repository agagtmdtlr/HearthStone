#pragma once
#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"


Creature::Creature(
	BattleField * field,
	int cost, string name,
	int power, int shield,
	int attcount, 
	bool agro, bool holy,
	bool invincibility
)
	:Card(cost, name,field),
	nPower(power), nShield(shield), nPreviouShield(shield), nMaxShield(shield),
	nPowerOrigin(power), nShieldOrigin(shield),
	nAttackCount(0),nAttackCountTurn(attcount), nAttackCountOrigin(attcount),	
	isAgro(agro),isAgroOrigin(agro),
	isHolyShiled(holy), isHolyShiledOrigin(holy),
	isSilence(false), 
	isInvincibility(invincibility),
	isAttackTargeted(true), isAttackTargetedOrigin(true),
	isMagicTargeted(true), isMagicTargetedOrigin(true), 
	isIced(false), isIcedOrigin(false)	
{}

void Creature::SilenceStat()
{
	Card::InitStat();
	// 3 cur / 7 max/ 2 origin
	// max = orgin = 2
	// if cur > max : cur = max
	// 체력 초기화
	nMaxShield = nShieldOrigin;
	if(nShield > nMaxShield) // 체력이 기본 체력보다 높으면 최대체력으로 낮추기
		nShield = nMaxShield;
	// 파워 초기화
	if(nPower > nPowerOrigin)
		nPower = nPowerOrigin;
	// 공격횟수 초기화
	nAttackCountTurn = nAttackCountOrigin;
	if (nAttackCount > nAttackCountTurn)
		nAttackCount = nAttackCountTurn;
	isAgro = false;
	isHolyShiled = false;
	isIced = false;
	isAttackTargeted = true;
	isMagicTargeted = true;
}

void Creature::InitStat()
{
	Card::InitStat();
	isDelete = false;
	nMaxShield = nShieldOrigin;
	nShield = nShieldOrigin;	
	nPower = nPowerOrigin;
	nAttackCountTurn = nAttackCountOrigin;
	nAttackCount = 0;
	isAgro = isAgroOrigin;
	isHolyShiled = isHolyShiledOrigin;
	isIced = isIcedOrigin;
	isAttackTargeted = isAttackTargetedOrigin;
	isMagicTargeted = isMagicTargetedOrigin;
	isSilence = false;
	isInvincibility = false;
	strPlusSkillDetail = "";
}

void Creature::SetShield(int val)
{
	if (isInvincibility == true) // 무적은 피해 안받음
		return;
	if (isHolyShiled && val < 0)
	{
		isHolyShiled = false;
		return;
	}
	// 이전 체력을 변경.
	nPreviouShield = nShield;
	// 체력 증감 계산
	int result = nShield + val;
	// 회복은 최대 체력을 넘어갈수 가 없다. ( 회복과 체력 증가는 다르다 )
	if (result > nMaxShield) result = nMaxShield;
	
	if (result != nShield) // 체력의 변화가 있는가
	{
		EVENT event;
		// 기존 체력 보다 내려가야 피해입음으로 판정된다.
		if (result < nShield)
			event = EVENT::DAMAGE;
		// 기존 체력 보다 올라가야 회복으로 판정된다.
		else if (result > nShield)
			event = EVENT::HEAL;		
		// 현재 체력을 변경
		nShield = result;
		ExcuteObserver(event);
	}

	if (nShield <= 0) // 카드 소멸 판단
	{
		ExcuteObserver(EVENT::DIE);
		isDelete = true;
	}		
}

void Creature::Use()
{
	int turn = nThisCardUserNumber;

	if (battleFieldOfCard->cardsOfField[turn].size() >= FieldMax)
	{
		cout << "=================================" << endl;
		cout << "==      필드가 꽉 찼습니다.     ==" << endl;
		cout << "=================================" << endl;
		Sleep(1000);
		return;
	}

	if (battleFieldOfCard->cost[turn] >= nCost)
	{
		battleFieldOfCard->cost[turn] -= nCost; // 코스트 소모
		if (isSilence == false)
			FirstSkill();
		SummonCreature(turn);
		Card::Use();
	}
	else
	{
		cout << "=================================" << endl;
		cout << "==가지고 있는 코스트가 부족합니다.==" << endl;
		cout << "=================================" << endl;
	}
	Sleep(1000);
}

void Creature::SummonCreature(int turn)
{
	cout << "=================================" << endl;
	cout << "==" << strName << "를(을) 소환합니다==" << endl;
	cout << "=================================" << endl;	
	battleFieldOfCard->cardsOfField[turn].push_back(this);	
	ExcuteObserver(EVENT::FIELD);
	
}



void Creature::SetSilence(bool val)
{
	isSilence = val;
	
	if (isSilence == true)
	{
		ExcuteObserver(EVENT::SILENCE);
		InitStat();
	}
		
}
void Creature::AttackSkill(Card * target)
{
	return;
}

void Creature::FirstSkill()
{
	return;
}

void Creature::Info() // 요약 정보
{
	cout << strName << "|" << nCost << "|" << nPower << "|" << nShield;
	if (isAgro) cout << "|★";
	else cout << "|X";
	if (isHolyShiled) cout << "|♥";
	else cout << "|X";
}

void Creature::detail() // 세부 정보
{
	cout << "이름 : " << strName << endl
		<< "코스트 : " << nCost << endl
		<< "파워 : " << nPower << endl
		<< "체력 : " << nShield << endl;
	cout << "어그로 : ";
	if (isAgro) cout << "보유" << endl;
	else cout << "없음" << endl;
	cout << "천상의 보호막 : ";
	if (isHolyShiled) cout << "보유" << endl;
	else cout << "없음" << endl;
	cout << strPlusSkillDetail << endl;
}








