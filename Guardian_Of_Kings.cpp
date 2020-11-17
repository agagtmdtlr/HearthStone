#pragma once
#include "stdafx.h"
#include "Guardian_Of_Kings.h"
#include "BattleField.h"



Guardian_Of_Kings::Guardian_Of_Kings()
{
}

Guardian_Of_Kings::Guardian_Of_Kings(BattleField * field)
	:Creature(field, 6, "���� ��ȣ��", 5, 6, 1, false, false, false)
{
}

Guardian_Of_Kings::~Guardian_Of_Kings()
{
}

void Guardian_Of_Kings::FirstSkill()
{
	int turn = nThisCardUserNumber;
	Creature * user = dynamic_cast<Creature *>(battleFieldOfCard->User[turn]);
	user->SetShield(6);
}

void Guardian_Of_Kings::detail()
{
	Creature::detail();
	cout << "�� ������ ������� 6 ȸ�� ��ŵ�ϴ�." << endl;
}
