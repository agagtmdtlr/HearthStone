#pragma once
#include "IObserver.h"

class BattleField;

class Card
	: public IObserver
{
protected:
	int nThisCardUserNumber;
	int nCost;	
	int nCostOrigin;
	
	string strName;
	string strPlusSkillDetail;
	
	// 카드 효과 발생시 필드를 직접 제어
	BattleField * battleFieldOfCard;	
	// 관찰자 목록
	bool isDelete;
public:
	Card() {};	
	Card(int cost, string name, BattleField * field);
	virtual ~Card() {}

	virtual void InitStat()	{ nCost = nCostOrigin; }

	virtual int GetCost() { return nCost; }		
	virtual void SetCost(const int val) 
	{ 		
		nCost += val; 
		if (nCost < 0) nCost = 0;
	}

	virtual string GetName() { return strName; }
	virtual bool GetDelete() { return isDelete; }

	virtual void SetDelete(bool val);
	
	virtual void SetPlusSkillDetail(string detail) { strPlusSkillDetail += detail; }

	virtual void Use();
	
	virtual void Info(){}
	virtual void detail(){}

	virtual void onNotify(Card& card, EVENT event) override {}
	virtual void onNotify(Card* card, EVENT event) override {}
	virtual void onNotify(EVENT event) override {}
	virtual void ExcuteObserver(EVENT event) final;
	

	virtual int GetThisCardUser() { return nThisCardUserNumber; }

	virtual int SelectCard(vector<Card*> *pCardCategory);

	virtual void EraseObserverFromObserverList(int turn);
	
};

