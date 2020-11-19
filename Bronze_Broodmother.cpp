#pragma once
#include "stdafx.h"
#include "Bronze_Broodmother.h"
#include "BattleField.h"


Bronze_Broodmother::Bronze_Broodmother()
{
}

Bronze_Broodmother::Bronze_Broodmother(BattleField * field)
	:Creature(field, 4, "청동용군단 무리어미", 5, 5, 1, false, false, false)
{
	
	int turn = nThisCardUserNumber;
	battleFieldOfCard->AddObserver(turn, this);
}


Bronze_Broodmother::~Bronze_Broodmother()
{
}

void Bronze_Broodmother::detail()
{
	Creature::detail();
	cout << "이 카드를 뽑을 때," << endl
		<< "1/1 작은 새끼용을 소환합니다." << endl;
}

void Bronze_Broodmother::onNotify(Card & card, EVENT event)
{
	
	int turn = nThisCardUserNumber;

	if (&card == nullptr) return;
	if (&card == this && event == EVENT::DRAW)
	{		
		cout << "1/1 작은 새끼용을 소환합니다." << endl;
		Sleep(1000);
		battleFieldOfCard->cardsOfField[nThisCardUserNumber].push_back(new Creature(battleFieldOfCard, 1, "작은 새끼용", 1, 1, 1, false, false, false));
		for (int i = 0; i < battleFieldOfCard->observers[turn].size(); i++)
		{
			if (this == battleFieldOfCard->observers[turn][i])
			{
				battleFieldOfCard->observers[turn].erase(battleFieldOfCard->observers[turn].begin() + i);
			}			
		}
	}
		
}

void Bronze_Broodmother::onNotify(Card * card, EVENT event)
{
	int turn = nThisCardUserNumber;
	
	
	if (card == nullptr) return;
	if (card == this && event == EVENT::DRAW)	
	{		
		cout << "1/1 작은 새끼용을 소환합니다." << endl;
		Sleep(1000);
		battleFieldOfCard->cardsOfField[nThisCardUserNumber].push_back(new Creature(battleFieldOfCard, 1, "작은 새끼용", 1, 1, 1, false, false, false));
		for (int i = 0; i < battleFieldOfCard->observers[turn].size(); i++)
		{
			if (this == battleFieldOfCard->observers[turn][i])
			{
				battleFieldOfCard->observers[turn].erase(battleFieldOfCard->observers[turn].begin() + i);
			}
		}
	}
}
