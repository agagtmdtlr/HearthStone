#pragma once
#include "stdafx.h"
#include "Argent_Protecter.h"
#include "BattleField.h"



Argent_Protecter::Argent_Protecter()
{
}

Argent_Protecter::Argent_Protecter(BattleField * field)
	:Creature(field, 1, "����ȸ �ļ���", 2, 2, 1, false, false, false)
{
}


Argent_Protecter::~Argent_Protecter()
{
}

void Argent_Protecter::FirstSkill()
{
	int turn = nThisCardUserNumber;
	// �Ʊ� �ʵ忡 ī�尡 ������ ȿ�� �̹ߵ�
	if (battleFieldOfCard->cardsOfField[turn].size() == 0) return;
	int inputNum = 0;
	while (1)
	{
		cout << "�Ʊ��� �����Ͻÿ� : ";
		inputNum = InputVariable<int>(inputNum);

		if (inputNum >= battleFieldOfCard->cardsOfField[turn].size())
		{
			cout << "�ٽ� �Է��Ͻÿ�" << endl;
		}
		else
		{
			break;
		}
	}
	Creature * card = dynamic_cast<Creature *>(battleFieldOfCard->cardsOfField[turn][inputNum]);

	card->SetHolyShield(true);
}

void Argent_Protecter::detail()
{
	Creature::detail();
	if (isSilence)
	{
		cout << "������ �Լ� : " << endl;
		cout << "�Ʊ� �ϼ��ο��� õ���� ��ȣ���� �ο��մϴ�." << endl;
	}
}
