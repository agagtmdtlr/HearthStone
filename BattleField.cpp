#pragma once
#include "stdafx.h"
#include "Card.h"
#include "Creature.h"
#include "Hero.h"
#include "Weapon.h"
#include "Secret.h"
#include "CardSpawner.h"

#include "BattleField.h"

#include "Tirion_Fordring.h"


BattleField::BattleField()	
{	
	User[0] = nullptr;
	User[1] = nullptr;
	cardsOfDeck->reserve(DeckSetting);
	cardsOfField->reserve(FieldMax);
	cardsOfHand->reserve(HandMax);
}

void BattleField::Attack(int turn ,Card * myCard, Card * yourCard)
{		
	arrFight[turn] = dynamic_cast<Creature *>(myCard);
	arrFight[1-turn] = dynamic_cast<Creature *>(yourCard);

	
	// ���õ� �ϼ����� ������ �� �ִ��� �Ǻ��Ѵ�. ( ����Ƚ�� �����̳� �����̸� ���� �Ұ� )
	if (arrFight[turn]->GetPower() <= 0)
	{
		//cout << "power" << endl;
		cout << arrFight[turn]->GetPower() << endl;
		//system("pause");
		return; // ���ݷ��� 0�̸� ���ݺҰ�.
	}
		
	if (arrFight[turn]->GetAttackCount() <= 0 || arrFight[turn]->GetIced() == true)
	{
		cout << "�̹� �Ͽ� �� �̻� ������ �� �����ϴ�." << endl;
		Sleep(1000);
		return;
	}

	//cout << "checkiscanAttack" << endl;
	//system("pause");
	//  �ʵ忡 ������ �����ϸ� ������ �켱���� �����ؾ� �Ѵ�.
	//  ���� ��븦 ������ �� �ִ��� �Ǻ��Ѵ�
	if (CheckIsCanAttack(turn, arrFight[1 - turn]) == true)
	{
		// ���� �̺�Ʈ �߻�
		arrFight[turn]->ExcuteObserver(EVENT::ATTACK);		
		
		//cout << "canAttack" << endl;
		//system("pause");
		// ������ �� �ϼ����� ���� Ƚ���� �����ǰ� ������ ����ȿ���� �������� ó���Ѵ�.
		arrFight[turn]->SetAttackCount(-1); // ���� Ƚ�� ����

		if (arrFight[1 - turn] != User[1 - turn]) // ������ �����Ҷ��� ���ظ� ���� �ʽ��ϴ�.
			arrFight[turn]->SetShield(-(arrFight[1 - turn]->GetPower()));
		arrFight[1 - turn]->SetShield(-(arrFight[turn]->GetPower()));
		
		// ������ ������ ī�� ���� ��ų�ߵ�
		if (arrFight[turn]->GetSilence() == false)
			arrFight[turn]->AttackSkill(arrFight[1 - turn]);
		// ������ ���� ī�� ���� ��ų �ߵ�
		if (arrFight[1 - turn]->GetSilence() == false)
			arrFight[1 - turn]->AttackSkill(arrFight[turn]);
	}
	else
	{
		cout << "�ش� �ϼ����� ������ ���� �����ϴ�." << endl;
		Sleep(1000);
	}	
}

bool BattleField::CheckIsCanAttack(int turn, Creature * target)
{
	if (target->GetInvincibility() == true) return false; // �����̸� ���� �Ұ�
	if (target->GetAttackTargeted() == false) return false; // Ÿ���� �������� Ȯ���ϱ�

	int enemyTurn = 1 - turn;
	for (int i = 0; i < cardsOfField[enemyTurn].size(); i++)
	{
		// �ʵ忡�� �ϼ��� �ۿ� �����Ƿ� RTTI �� ���� ������帣 �����Ѵ�.
		Creature * enemy =
			(Creature *)(cardsOfField[enemyTurn][i]);
		// ��� �ʵ忡 ��׷ΰ� �ְ� ���� ��� �ϼ����� ��׷θ� ���� ����
		if (enemy->GetAgro() == true) 
			return target->GetAgro();
	}

	return true;
}


void BattleField::Draw(int turn)
{
	// ���� ����� ���
	if (cardsOfDeck[turn].empty())
	{
		cout << "���� �ִ� ī�尡 ���� ��ο츦 ���մϴ�" << endl;
		Sleep(1000);
		return;
	}

	// ���� ���� �ʾ��� ���
	Card* card = cardsOfDeck[turn].back();	
	for (int i = 0; i < observers[turn].size(); i++)
	{		
		/*cout << "call observer for draw" << endl;
		cout << observers[turn][i]->GetName() << endl;
		cout << observers[turn][i] << endl;
		system("pause");*/
		
		observers[turn][i]->onNotify(card, EVENT::DRAW);
	}
	
	cardsOfDeck[turn].pop_back();	
	if (cardsOfHand[turn].size() >= HandMax)
	{
		garbageCollector->push_back(card);
		cout << "������ �� �ִ� ī�尡 �Ѱ��Դϴ�." << endl
			<< "��ο��� ī�带 �����մϴ�." << endl;
	}
	else
		cardsOfHand[turn].push_back(card);
	Sleep(500);
}

bool BattleField::Choice()
{
	
	int turn = nPlayerTurn % 2;
	int inputNum = 0;
	int SelectNum;

	cout << "����� ī�带 �����Ͻÿ� : ";
	inputNum = InputVariable<int>(inputNum); // input
	SelectNum = inputNum;

	if (SelectNum >= cardsOfHand[turn].size())
		return false;
	cout << "===========================" << endl;
	cout << "======   ī�� ���� :  ======" << endl;
	cout << "===========================" << endl;
	cardsOfHand[turn][SelectNum]->detail();
	cout << "���� ����Ͻðڽ��ϱ�(Yes.1 No.0) : ";
	inputNum = InputVariable<int>(inputNum); // input

	if (inputNum == 1)
	{
		Card * card = cardsOfHand[turn][SelectNum];		
		cardsOfHand[turn][SelectNum]->Use();		
		// �п��� ����
		cardsOfHand[turn].erase(cardsOfHand[turn].begin() + SelectNum);
		return true;
	}
	else if (inputNum == 0)
		return false;
	else
	{
		cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
		return false;
	}
		
	
}

void BattleField::DeleteCards()
{
	int i = 0;
	for (int turn = 0; turn < 2; turn++)
	{


		Hero * hero = (Hero *)User[turn];
		Weapon * weapon = hero->GetWeapon();
		if (weapon != nullptr)
		{
			if (weapon->GetDelete() == true)
			{
				garbageCollector[turn].push_back(weapon);
			}
			
		}

		
		
		vector<Secret *> * secretCards = hero->GetSecret();
		while (1)
		{
			if (i >= secretCards->size())
				break;
			else
			{
				secretCards->at(i);
				if (secretCards->at(i)->GetDelete() == true)
				{
					garbageCollector[turn].push_back(secretCards->at(i));
					secretCards->erase(secretCards->begin() + i);
				}
				else
				{
					i++;
				}
			}			
		}			
		
		i = 0;
		while (1)
		{
			if (i >= cardsOfDeck[turn].size())
				break;
			if (cardsOfDeck[turn][i]->GetDelete() == true)
			{
				garbageCollector[turn].push_back(cardsOfDeck[turn][i]);
				cardsOfDeck[turn].erase(cardsOfDeck[turn].begin() + i);
			}
			else
			{
				i++;
			}
		}

		i = 0;
		while (1)
		{
			if (i >= cardsOfHand[turn].size())
				break;
			if (cardsOfHand[turn][i]->GetDelete() == true)
			{
				garbageCollector[turn].push_back(cardsOfHand[turn][i]);
				cardsOfHand[turn].erase(cardsOfHand[turn].begin() + i);
			}
			else
			{
				i++;
			}
		}

		i = 0;
		while (1)
		{
			if (i >= cardsOfField[turn].size())
				break;
			if (cardsOfField[turn][i]->GetDelete() == true)
			{
				garbageCollector[turn].push_back(cardsOfField[turn][i]);
				cardsOfField[turn].erase(cardsOfField[turn].begin() + i);
			}
			else
			{
				i++;
			}
		}
	}
	
}

void BattleField::ShowField()
{
	int turn = nPlayerTurn % 2;
	int e_turn = 1 - turn;
	Hero * myPlayerBody =dynamic_cast<Hero *>(User[turn]);
	Hero * enemyPlayerBody = dynamic_cast<Hero *>(User[e_turn]);

	cout << "PLAYER" << turn << " TURN" << endl;
	cout << "\t\t��� ����: ";
	enemyPlayerBody->Info();
	cout << endl;
	enemyPlayerBody->InfoAboutWeapon();
	cout << endl;
	enemyPlayerBody->InfoAboutSecrets();
	cout << endl;
	cout << "���� ����� ���� ���� ī�� �� : " 
		<< cardsOfDeck[e_turn].size() << endl;
	cout << "��� �� : ";
	for (int i = 0; i < cardsOfHand[e_turn].size(); i++)
		cout << " �� ";
	cout << endl;
	cout << "��� �ʵ� : ";
	for (int i = 0; i < cardsOfField[e_turn].size(); i++)
	{
		cout << "(" << i << ")" << "[ ";
		cardsOfField[e_turn][i]->Info();
		cout << " ]";
		cout << "  ";
	}
	cout << "\n================================================" << endl;
	
	cout << "�� �ʵ� : ";
	for (int i = 0; i < cardsOfField[turn].size(); i++)
	{
		cout << "(" << i << ")" << "[ ";
		cardsOfField[turn][i]->Info();
		cout << " ]";
		cout << "  ";
	}
	cout << "\n================================================" << endl;
	cout << "�� �� : ";
	for (int i = 0; i < cardsOfHand[turn].size(); i++)
	{
		cout << "(" << i  << ")" << "[ ";
		cardsOfHand[turn][i]->Info();
		cout << " ]";
		cout << "  ";
	}
	cout << endl;
	cout << "���� ���� ���� ���� ī�� �� : "
		<< cardsOfDeck[turn].size() << endl;
	cout << "\t\t���� ���� : ";
	myPlayerBody->Info();
	cout << endl;
	myPlayerBody->InfoAboutWeapon();
	cout << endl;
	myPlayerBody->InfoAboutSecrets();
	cout << endl;
	cout << "���� �ڽ�Ʈ : " << cost[turn];
		
}

void BattleField::InitGame()
{
	nPlayerTurn = 0;
	// ���� ���� �ʱ�ȭ
	for (int i = 0; i < 2; i++)
	{
		cost[i] = 0;	
		if (User[i] != nullptr)
		{
			delete User[i];
			nPlayerTurn = i;
			User[i] = new Hero(this, 0, "Player" + i, 0, 600, 1, false, false, false);
		}					
		else
		{
			nPlayerTurn = i;
			User[i] = new Hero(this, 0, "Player" + i, 0, 600, 1, false, false, false);
		}	

		observers[i].clear();
	}
	nPlayerTurn = 0;

	// �ȿ� �ڷ� ����
	for (int i = 0; i < 2; i++)
	{		
		for (int j = 0; j < cardsOfField[i].size(); j++)
		{
			delete cardsOfField[i][j];
		}
		cardsOfField[i].clear();

		for (int j = 0; j < cardsOfDeck[i].size(); j++)
		{
			delete cardsOfDeck[i][j];
		}
		cardsOfDeck[i].clear();

		for (int j = 0; j < cardsOfHand[i].size(); j++)
		{
			delete cardsOfHand[i][j];
		}
		cardsOfHand[i].clear();		

		for (int j = 0; j < garbageCollector[i].size(); j++)
		{
			delete garbageCollector[i][j];
		}
		garbageCollector[i].clear();

		nPlayerTurn = i;

		vector<CardName> cardlist =
		{
				
				CardName::AVENGING_WRATH,
				CardName::BLESSING_OF_AEONS,
				CardName::BLESSING_OF_KINGS,
				CardName::BLESSING_OF_WISDORN,
				CardName::BLESSING_OF_MIGHT,
				CardName::BLESSED_CHAMPION,
				CardName::CONSECRATION,
				CardName::HAND_OF_PROTECTION,
				CardName::HOLY_LIGHT,
				CardName::HOLY_WRATH,
				CardName::HUMILITY,
				CardName::LAY_ON_HANDS,
				CardName::RIGHTEOUSNESS,
				CardName::EQUALITY,
				CardName::HAMMER_OF_WRATH,
				CardName::EYE_FOR_AN_EYE,

				CardName::HAND_OF_SALVATION,

				CardName::NOBLE_SACRIFICE,
				CardName::REDEMPTION,
				CardName::REPENTANCE,
				CardName::LIGHTS_JUSTICE,
				CardName::SWORD_OF_JUSTICE,
				CardName::TRUESILVER_CHAMPION,

				CardName::ALDOR_PEACE_KEEPER,
				CardName::ARGENT_PROTECTER,
				
				CardName::BRONZE_BROODMOTHER,
				CardName::GUARDIAN_OF_KINGS,
				CardName::TIRION_FORDRING
		};

		CardSpawner cardSpawner;
		//cout << "ī�� ����" << endl;
		if (i == 0)
		{
			cardSpawner.SpawnCards(&cardlist, this);
			cardsOfField[i].push_back(new Creature(this, 0, "���� ��", 999, 99999, 9999, false, false, false));
		}			
		else if (i == 1)
		{
			cardsOfField[i].push_back(new Tirion_Fordring(this));
			cardsOfField[i].push_back(new Creature(this, 0, "���� ��", 999, 99999, 9999, false, false, false));
			cardsOfField[i].push_back(new Creature(this, 0, "���� ��", 999, 99999, 9999, false, false, false));
			cardsOfField[i].push_back(new Creature(this, 0, "���� ��", 999, 99999, 9999, false, false, false));
			
		}
		//cout << "ī�� ���� �Ϸ�" << endl;
		//system("pause");
	}	
	nPlayerTurn = 0;	
}

void BattleField::InitTurn()
{
	int turn = nPlayerTurn % 2;
	int attackCount;
	// ���� �� �ʱ�ȭ
	Hero * hero = (Hero *)User[turn];
	attackCount = hero->GetAttackCountTurn() - hero->GetAttackCount();
	hero->SetAttackTargeted(true);
	// �ʵ� �� �ϼ��� �� �ʱ�ȭ
	for (int i = 0; i < cardsOfField[turn].size(); i++)
	{
		Creature * card = dynamic_cast<Creature *>(cardsOfField[turn][i]);
		// ��������� �� ���� Ƚ�� = �̹��Ͽ� �ο��� Ƚ�� - �����մ� ���� Ƚ��
		attackCount = card->GetAttackCountTurn() - card->GetAttackCount();
		card->SetAttackCount(attackCount);
		card->SetAttackTargeted(true);
	}
}

bool BattleField::CheckEnd()
{
	for (int i = 0; i < 2; i++)
	{
		if (User[i]->GetDelete() == true)
		{
			system("cls");
			Sleep(1000);
			cout << "�ƴ�! �̷�����!" << endl;
			Sleep(1000);
			cout << "PLAYER" << (i + 1) % 2 << "�� �¸��Դϴ� �����մϴ�!!!" << endl;
			Sleep(500);
			cout << "������ �����մϴ�" << endl;
			return true;
		}
	}
	return false;
}



void BattleField::AddObserver(int turn,const Card * observer)
{
	if(observer != nullptr)
		observers[turn].push_back(const_cast<Card *>(observer));
}

void BattleField::DeleteObserver( int turn,const Card * observer)
{
	for (int i = 0; i < observers[turn].size(); i++)
	{
		if (observers[turn][i] == observer)
		{
			delete observers[turn][i];
			observers[turn].erase(observers[turn].begin() + i);
			return;
		}
	}
}

void BattleField::CallObservers(int turn ,Card & card, EVENT event)
{
	for (int i = 0; i < observers[turn].size(); i++)
		observers[turn][i]->onNotify(card, event);
}

void BattleField::CallObservers(int turn, Card * card, EVENT event)
{
	for (int i = 0; i < observers[turn].size(); i++)
	{
		cout << i << endl;
		Card * card = (Card *)observers[turn][i];
		cout << card->GetName() << endl;
		observers[turn][i]->onNotify(card, event);		
	}
		
}
