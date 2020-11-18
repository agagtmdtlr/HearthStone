#pragma once
#include "stdafx.h"
#include "Bronze_Broodmother.h"
#include "BattleField.h"


Bronze_Broodmother::Bronze_Broodmother()
{
}

Bronze_Broodmother::Bronze_Broodmother(BattleField * field)
	:Creature(field, 4, "û���뱺�� �������", 5, 5, 1, false, false, false)
{
	
	int turn = battleFieldOfCard->nPlayerTurn % 2;
	cout << turn << endl;
	system("pause");
	battleFieldOfCard->AddObserver(turn, this);
}


Bronze_Broodmother::~Bronze_Broodmother()
{
}

void Bronze_Broodmother::detail()
{
	Creature::detail();
	cout << "�� ī�带 ���� ��," << endl
		<< "1/1 ���� �������� ��ȯ�մϴ�." << endl;
}

void Bronze_Broodmother::onNotify(const Card & card, EVENT event)
{
	

	if (&card == this && event == EVENT::DRAW && isSilence == false)
	{
		int turn = battleFieldOfCard->nPlayerTurn % 2;
		cout << "1/1 ���� �������� ��ȯ�մϴ�." << endl;
		Sleep(1000);
		battleFieldOfCard->cardsOfField[turn].push_back(new Creature(battleFieldOfCard, 0, "���� ������", 1, 1, 1, false, false, false));
		for (int i = 0; i < battleFieldOfCard->observers[turn].size(); i++)
		{
			if (this == battleFieldOfCard->observers[turn][i])
			{
				battleFieldOfCard->observers[turn].erase(battleFieldOfCard->observers[turn].begin() + i);
			}			
		}
	}
		
}

void Bronze_Broodmother::onNotify(const Card * card, EVENT event)
{
	int turn = battleFieldOfCard->nPlayerTurn % 2;
	if (card == this && event == EVENT::DRAW)	
	{
		
		cout << "1/1 ���� �������� ��ȯ�մϴ�." << endl;
		Sleep(1000);
		battleFieldOfCard->cardsOfField->push_back(new Creature(battleFieldOfCard, 1, "���� ������", 1, 1, 1, false, false, false));
		for (int i = 0; i < battleFieldOfCard->observers[turn].size(); i++)
		{
			if (this == battleFieldOfCard->observers[turn][i])
			{
				battleFieldOfCard->observers[turn].erase(battleFieldOfCard->observers[turn].begin() + i);
			}
		}
	}
}
