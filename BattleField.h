#pragma once

class Card;
class Creature;
class IObserver;

class BattleField
{
public:
	Card * User[2];
	// total = 10
	vector<Card *> cardsOfDeck[2];
	// limit = 5
	vector<Card *> cardsOfHand[2];
	// limit = 3
	vector<Card *> cardsOfField[2];
	// ������ ����Ʈ�� ����ϴ�.
	vector<Card *> observers[2];
	// ���Ǿ��� ī�� ����Ʈ
	vector<Card *> garbageCollector[2];

	Creature * arrFight[2];

	int nPlayerTurn = 0;

	int cost[2]; // ��� ������ �ڽ�Ʈ
	int maXCost = 11; // �����Ҽ� �ִ� �ڽ�Ʈ �Ѱ�	

	BattleField();	

	virtual void Attack(int turn, Card * myCard, Card * yourCard);	

	virtual bool CheckIsCanAttack(int turn, Creature * target);

	virtual void Draw(int turn);	

	virtual bool Choice();

	virtual void DeleteCards();

	virtual void ShowField();

	virtual void InitGame();
	
	virtual void InitTurn();

	virtual bool CheckEnd();	


	virtual void AddObserver(int turn,const Card * observer = nullptr);
	virtual void DeleteObserver(int turn,const Card * observer = nullptr);

	virtual void CallObservers(int turn, Card& card, EVENT event);
	virtual void CallObservers(int turn, Card* card, EVENT event);
};


