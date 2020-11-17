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
	// ī�� ȿ�� �߻��� �ʵ带 ���� ����
	BattleField * battleFieldOfCard;	
	// ������ ���
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
	virtual bool GetDelete() { return isDelete; }

	virtual void SetDelete(bool val);
	

	virtual void Use();
	
	virtual void Info(){}
	virtual void detail(){}

	virtual void onNotify(Card& card, EVENT event) {}
	virtual void onNotify(Card* card, EVENT event) {}

	virtual void ExcuteObserver(EVENT event) final;
	

	virtual int GetThisCardUser() { return nThisCardUserNumber; }

	virtual int SelectCard(vector<Card*> *pCardCategory);
	
};

