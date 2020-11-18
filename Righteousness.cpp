#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"
#include "Righteousness.h"

Righteousness::Righteousness(BattleField * field)
	:Magic(field, 5, "����", 0, false)
{
}

bool Righteousness::FirstSkill()
{
	auto & fieldList = battleFieldOfCard->cardsOfField[nThisCardUserNumber];
	for (auto iter : fieldList)
	{
		Creature * target = (Creature *)iter;
		target->SetHolyShield(true);		
	}
	return true;
}

void Righteousness::detail()
{
	Magic::detail();
	cout << "�� �ϼ��ε鿡�� [õ���� ��ȣ��]�� �ο��մϴ�." << endl;
}
