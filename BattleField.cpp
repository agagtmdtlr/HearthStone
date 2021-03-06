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

	
	// 선택된 하수인이 공격할 수 있는지 판별한다. ( 공격횟수 부족이나 빙결이면 공격 불가 )
	if (arrFight[turn]->GetPower() <= 0)
	{
		//cout << "power" << endl;
		cout << arrFight[turn]->GetPower() << endl;
		//system("pause");
		return; // 공격력이 0이면 공격불가.
	}
		
	if (arrFight[turn]->GetAttackCount() <= 0 || arrFight[turn]->GetIced() == true)
	{
		cout << "이번 턴에 더 이상 공격할 수 없습니다." << endl;
		Sleep(1000);
		return;
	}

	//cout << "checkiscanAttack" << endl;
	//system("pause");
	//  필드에 도발이 존재하면 도발을 우선으로 공격해야 한다.
	//  현재 상대를 공격할 수 있는지 판별한다
	if (CheckIsCanAttack(turn, arrFight[1 - turn]) == true)
	{
		// 공격 이벤트 발생
		arrFight[turn]->ExcuteObserver(EVENT::ATTACK);		
		
		//cout << "canAttack" << endl;
		//system("pause");
		// 공격을 한 하수인은 공격 횟수가 차감되고 서로의 전투효과와 데미지를 처리한다.
		arrFight[turn]->SetAttackCount(-1); // 공격 횟수 차감

		if (arrFight[1 - turn] != User[1 - turn]) // 영웅을 공격할때는 피해를 입지 않습니다.
			arrFight[turn]->SetShield(-(arrFight[1 - turn]->GetPower()));
		arrFight[1 - turn]->SetShield(-(arrFight[turn]->GetPower()));
		
		// 공격을 수행한 카드 전투 스킬발동
		if (arrFight[turn]->GetSilence() == false)
			arrFight[turn]->AttackSkill(arrFight[1 - turn]);
		// 공격을 받은 카드 전투 스킬 발동
		if (arrFight[1 - turn]->GetSilence() == false)
			arrFight[1 - turn]->AttackSkill(arrFight[turn]);
	}
	else
	{
		cout << "해당 하수인을 공격할 수가 없습니다." << endl;
		Sleep(1000);
	}	
}

bool BattleField::CheckIsCanAttack(int turn, Creature * target)
{
	if (target->GetInvincibility() == true) return false; // 무적이면 공격 불가
	if (target->GetAttackTargeted() == false) return false; // 타켓팅 가능한지 확인하기

	int enemyTurn = 1 - turn;
	for (int i = 0; i < cardsOfField[enemyTurn].size(); i++)
	{
		// 필드에는 하수인 밖에 없으므로 RTTI 로 인한 오버헤드르 방지한다.
		Creature * enemy =
			(Creature *)(cardsOfField[enemyTurn][i]);
		// 상대 필드에 어그로가 있고 공격 대상 하수인이 어그로면 공격 가능
		if (enemy->GetAgro() == true) 
			return target->GetAgro();
	}

	return true;
}


void BattleField::Draw(int turn)
{
	// 덱이 비었을 경우
	if (cardsOfDeck[turn].empty())
	{
		cout << "남아 있는 카드가 없어 드로우를 못합니다" << endl;
		Sleep(1000);
		return;
	}

	// 덱이 비지 않았을 경우
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
		cout << "보유할 수 있는 카드가 한계입니다." << endl
			<< "드로우한 카드를 삭제합니다." << endl;
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

	cout << "사용할 카드를 선택하시오 : ";
	inputNum = InputVariable<int>(inputNum); // input
	SelectNum = inputNum;

	if (SelectNum >= cardsOfHand[turn].size())
		return false;
	cout << "===========================" << endl;
	cout << "======   카드 설명 :  ======" << endl;
	cout << "===========================" << endl;
	cardsOfHand[turn][SelectNum]->detail();
	cout << "정말 사용하시겠습니까(Yes.1 No.0) : ";
	inputNum = InputVariable<int>(inputNum); // input

	if (inputNum == 1)
	{
		Card * card = cardsOfHand[turn][SelectNum];		
		cardsOfHand[turn][SelectNum]->Use();		
		// 패에서 제거
		cardsOfHand[turn].erase(cardsOfHand[turn].begin() + SelectNum);
		return true;
	}
	else if (inputNum == 0)
		return false;
	else
	{
		cout << "잘못 입력하셨습니다." << endl;
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
	cout << "\t\t상대 영웅: ";
	enemyPlayerBody->Info();
	cout << endl;
	enemyPlayerBody->InfoAboutWeapon();
	cout << endl;
	enemyPlayerBody->InfoAboutSecrets();
	cout << endl;
	cout << "현재 상대의 덱에 남은 카드 수 : " 
		<< cardsOfDeck[e_turn].size() << endl;
	cout << "상대 패 : ";
	for (int i = 0; i < cardsOfHand[e_turn].size(); i++)
		cout << " ■ ";
	cout << endl;
	cout << "상대 필드 : ";
	for (int i = 0; i < cardsOfField[e_turn].size(); i++)
	{
		cout << "(" << i << ")" << "[ ";
		cardsOfField[e_turn][i]->Info();
		cout << " ]";
		cout << "  ";
	}
	cout << "\n================================================" << endl;
	
	cout << "내 필드 : ";
	for (int i = 0; i < cardsOfField[turn].size(); i++)
	{
		cout << "(" << i << ")" << "[ ";
		cardsOfField[turn][i]->Info();
		cout << " ]";
		cout << "  ";
	}
	cout << "\n================================================" << endl;
	cout << "내 패 : ";
	for (int i = 0; i < cardsOfHand[turn].size(); i++)
	{
		cout << "(" << i  << ")" << "[ ";
		cardsOfHand[turn][i]->Info();
		cout << " ]";
		cout << "  ";
	}
	cout << endl;
	cout << "현재 나의 덱에 남은 카드 수 : "
		<< cardsOfDeck[turn].size() << endl;
	cout << "\t\t나의 영웅 : ";
	myPlayerBody->Info();
	cout << endl;
	myPlayerBody->InfoAboutWeapon();
	cout << endl;
	myPlayerBody->InfoAboutSecrets();
	cout << endl;
	cout << "남은 코스트 : " << cost[turn];
		
}

void BattleField::InitGame()
{
	nPlayerTurn = 0;
	// 유저 정보 초기화
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

	// 안에 자료 비우기
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
		//cout << "카드 생성" << endl;
		if (i == 0)
		{
			cardSpawner.SpawnCards(&cardlist, this);
			cardsOfField[i].push_back(new Creature(this, 0, "연습 봇", 999, 99999, 9999, false, false, false));
		}			
		else if (i == 1)
		{
			cardsOfField[i].push_back(new Tirion_Fordring(this));
			cardsOfField[i].push_back(new Creature(this, 0, "연습 봇", 999, 99999, 9999, false, false, false));
			cardsOfField[i].push_back(new Creature(this, 0, "연습 봇", 999, 99999, 9999, false, false, false));
			cardsOfField[i].push_back(new Creature(this, 0, "연습 봇", 999, 99999, 9999, false, false, false));
			
		}
		//cout << "카드 생성 완료" << endl;
		//system("pause");
	}	
	nPlayerTurn = 0;	
}

void BattleField::InitTurn()
{
	int turn = nPlayerTurn % 2;
	int attackCount;
	// 영웅 턴 초기화
	Hero * hero = (Hero *)User[turn];
	attackCount = hero->GetAttackCountTurn() - hero->GetAttackCount();
	hero->SetAttackTargeted(true);
	// 필드 내 하수인 턴 초기화
	for (int i = 0; i < cardsOfField[turn].size(); i++)
	{
		Creature * card = dynamic_cast<Creature *>(cardsOfField[turn][i]);
		// 충전해줘야 할 공격 횟수 = 이번턴에 부여할 횟수 - 남아잇는 공격 횟수
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
			cout << "아니! 이럴수가!" << endl;
			Sleep(1000);
			cout << "PLAYER" << (i + 1) % 2 << "의 승리입니다 축하합니다!!!" << endl;
			Sleep(500);
			cout << "게임을 종료합니다" << endl;
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
