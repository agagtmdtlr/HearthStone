#pragma once
#include "stdafx.h"
#include "BattleField.h"

#include "Hero.h"
#include "Weapon.h"
#include "Secret.h"
#include "AldorPeaceKeeper.h"
#include "Argent_Protecter.h"
#include "Bronze_Broodmother.h"
#include "Tirion_Fordring.h"



BattleField::BattleField()	
{
	for (int i = 0; i < 2; i++)
		User[i] = new Creature(this, 0, "Player" + i, 0, 5, 0, false, false, false);
	cardsOfDeck->reserve(DeckSetting);
	cardsOfField->reserve(FieldMax);
	cardsOfHand->reserve(HandMax);
}

void BattleField::Attack(int turn ,Card * myCard, Card * yourCard)
{		
	arrFight[turn] = dynamic_cast<Creature *>(myCard);
	arrFight[1-turn] = dynamic_cast<Creature *>(yourCard);

	
	// ���õ� �ϼ����� ������ �� �ִ��� �Ǻ��Ѵ�. ( ����Ƚ�� �����̳� �����̸� ���� �Ұ� )
	if (arrFight[turn]->GetPower() <= 0) return; // ���ݷ��� 0�̸� ���ݺҰ�.
	if (arrFight[turn]->GetAttackCount() <= 0 || arrFight[turn]->GetIced() == true)
	{
		cout << "�̹� �Ͽ� �� �̻� ������ �� �����ϴ�." << endl;
		Sleep(1000);
		return;
	}

	//  �ʵ忡 ������ �����ϸ� ������ �켱���� �����ؾ� �Ѵ�.
	//  ���� ��븦 ������ �� �ִ��� �Ǻ��Ѵ�
	if (CheckIsCanAttack(turn, arrFight[1 - turn]) == true)
	{
		// ���� �̺�Ʈ �߻�
		arrFight[turn]->ExcuteObserver(EVENT::ATTACK);		
		
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

	bool isAgroOnField = false;
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
		observers[turn][i]->onNotify(*card, EVENT::DRAW);
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
	Creature * myPlayerBody =dynamic_cast<Creature *>(User[turn]);
	Creature * enemyPlayerBody = dynamic_cast<Creature *>(User[e_turn]);

	cout << "PLAYER" << turn << " TURN" << endl;
	cout << "\t\t��� ü�� : " << enemyPlayerBody->GetShield() << endl;
	cout << "���� ����� ���� ���� ī�� �� : " 
		<< cardsOfDeck[e_turn].size() << endl;
	cout << "��� �� : ";
	for (int i = 0; i < cardsOfHand[e_turn].size(); i++)
		cout << " �� ";
	cout << endl;
	cout << "��� �ʵ� : ";
	for (int i = 0; i < cardsOfField[e_turn].size(); i++)
	{
		cardsOfField[e_turn][i]->Info();
		cout << "\t";
	}
	cout << "\n================================================" << endl;
	
	cout << "�� �ʵ� : ";
	for (int i = 0; i < cardsOfField[turn].size(); i++)
	{
		cardsOfField[turn][i]->Info();
		cout << "\t";
	}
	cout << endl;
	cout << "�� �� : ";
	for (int i = 0; i < cardsOfHand[turn].size(); i++)
	{
		cardsOfHand[turn][i]->Info();
		cout << "\t";
	}
	cout << endl;
	cout << "���� ���� ���� ���� ī�� �� : "
		<< cardsOfDeck[turn].size() << endl;
	cout << "\t\t���� ü�� : " << myPlayerBody->GetShield() << endl;
	cout << "���� �ڽ�Ʈ : " << cost[turn];
		
}

void BattleField::InitGame()
{
	nPlayerTurn = 0;
	// ���� ���� �ʱ�ȭ
	for (int i = 0; i < 2; i++)
	{
		cost[i] = 0;
		delete User[i];
		User[i] = new Hero(this, 0, "Player" + i, 0, 5, 0, false, false, false);
	}

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
	}	

	for (nPlayerTurn = 0; nPlayerTurn < 2; nPlayerTurn++)
	{
		cardsOfDeck[nPlayerTurn].push_back(new Argent_Protecter(this));
		cardsOfDeck[nPlayerTurn].push_back(new AldorPeaceKeeper(this));
		//cardsOfDeck[nPlayerTurn].push_back(new Bronze_Broodmother(this));
		cardsOfDeck[nPlayerTurn].push_back(new Tirion_Fordring(this));
	}
	nPlayerTurn = 0;
}

void BattleField::InitTurn()
{
	int turn = nPlayerTurn % 2;
	for (int i = 0; i < cardsOfField[turn].size(); i++)
	{
		Creature * card = dynamic_cast<Creature *>(cardsOfField[turn][i]);
		// ��������� �� ���� Ƚ�� = �̹��Ͽ� �ο��� Ƚ�� - �����մ� ���� Ƚ��
		int attackCount = card->GetAttackCountTurn() - card->GetAttackCount();
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
		observers[turn][i]->onNotify(card, event);
}
