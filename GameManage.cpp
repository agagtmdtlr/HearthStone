#pragma once
#include "stdafx.h"
#include "Card.h"
#include "BattleField.h"
#include "GameManage.h"



void GameManage::PlayGaming()
{
	field = new BattleField;
	
	isQuitGame = false;	
	while (!isQuitGame)
	{		
		field->InitGame();
		isEndGame = false;
		while (!isEndGame)
		{
			system("cls");
			// ���� ���۽� ȿ�� �ߵ�
			int turn = field->nPlayerTurn % 2;
			field->CallObservers(turn,nullptr, EVENT::BEGIN);
			field->DeleteCards();
			// ���� ���� Ƚ���� �ʱ�ȭ
			field->InitTurn();
			// ���� ���۽� ȿ�� �ߵ�
			// �� ����
			isEndTurn = false;
			// �ڽ�Ʈ �ο�
			int thisTurnCost = field->nPlayerTurn / 2 + 10;
			if (thisTurnCost > field->maXCost)
				field->cost[field->nPlayerTurn % 2] = field->maXCost;
			else
				field->cost[field->nPlayerTurn % 2] = thisTurnCost;
			// ��ο�
			field->Draw(turn);
			
			while (!isEndTurn)
			{
				system("cls");				
				field->ShowField();
				// if Active changed the field refresh field output
				isChangeField = SelectAction();
				if (isChangeField)
				{
					system("cls");
					field->ShowField();
				}					
				// if exhausted of user hp end the game
				if (field->CheckEnd())
				{
					isEndGame = true;
					isEndTurn = true;
				}
					
				// to delete died creature or used cards 
				field->DeleteCards();
			}
			// �� ������ ȿ���ߵ� ( ex) Ÿ�츴�� ȿ�� : �� ����� �п� ��� �ִ� ī���� �ڽ�Ʈ�� 1 �����մϴ�. )
			field->CallObservers(field->nPlayerTurn % 2, nullptr, EVENT::END);
			// ���� ������ ������ �ѱ��.
			field->nPlayerTurn += 1;
		}		
	}

	delete field;
}

bool GameManage::SelectAction()
{
	int inputNum=0;
	unsigned int myCreatureIndex = 0;
	unsigned int enemyCreatureIndex = 0;
	int selectNum = 0;
	int turn = field->nPlayerTurn % 2;
	E_ACTION myAction;
	cout << "\n�׼��� �����ϼ���(0.�ϼ��� ���� 1.�� ī�� ��� 2.���� ��ģ�� 3.�׺��Ѵ�)\n : ";
	inputNum = InputVariable<int>(inputNum);

	myAction = (E_ACTION)inputNum;


	switch (myAction)
	{
	case E_ACTION::ATTACK:
		

		cout << "������ ���� �ϼ����� �����ϼ��� : ";
		myCreatureIndex = InputVariable<unsigned int>(myCreatureIndex); // input test
		if (myCreatureIndex >= field->cardsOfField[turn].size())
			return false;
		field->cardsOfField[turn][myCreatureIndex]->detail();
		cout << "--------------------------------------------------" << endl;
		cout << "�� �ϼ���?(0)��� ����?(1) : ";
		enemyCreatureIndex = InputVariable<unsigned int>(enemyCreatureIndex);
		if (enemyCreatureIndex == 1)
		{
			field->Attack(
				turn,
				field->cardsOfField[turn][myCreatureIndex],
				field->User[1-turn]
			);
		}
		else
		{
			cout << "������ ���� �ϼ����� �����ϼ��� : ";
			enemyCreatureIndex = InputVariable<unsigned int>(enemyCreatureIndex);
			if (myCreatureIndex >= field->cardsOfField[abs(turn - 1)].size())
				return false;
			//��ī���� �ο�
			field->Attack(
				turn,
				field->cardsOfField[turn][myCreatureIndex],
				field->cardsOfField[1-turn][enemyCreatureIndex]
			);
		}
		
		return true;		
		break;
	case E_ACTION::USE:		
		return field->Choice();
		break;
	case E_ACTION::END:
		isEndTurn = true;
		return false;
		break;
	case E_ACTION::SURRENDER:
		field->User[turn]->SetDelete(true);
		cout << "PLAYER" << turn << "�� �׺��߽��ϴ�." << endl;
		cout << "���� �ºο���." << endl;
		Sleep(2000);
		return false;
		break;
	default:
		return false;
		break;		
	}
	


}
