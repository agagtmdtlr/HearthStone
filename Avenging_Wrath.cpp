#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"
#include "Avenging_Wrath.h"

Avenging_Wrath::Avenging_Wrath(BattleField * field)
	:Magic(field, 6, "��¡�� �ݳ�", 8, true)
{
}

bool Avenging_Wrath::FirstSkill()
{
	int damage = nPower + nPowerBonus;

	vector<Creature *> targetList;
	targetList.reserve(FieldMax + 1);
	// ��� ������ ù��°�� �ִ´� �ε����� 0�̴�.
	targetList.push_back((Creature *)battleFieldOfCard->User[1 - nThisCardUserNumber]);
	// ������ �ʵ����� ��� �ϼ����� �־� �ش�.
	auto & fieldList = battleFieldOfCard->cardsOfField[1 - nThisCardUserNumber];
	for (int i = 0; i < fieldList.size();)
	{
		targetList.push_back((Creature *)fieldList[i]);
	}	
	size_t ListSize = targetList.size(); // ���� �ϼ��� ����Ʈ�� ũ��

	int randNumber;
	srand((unsigned int)(time(NULL)));
	rand();

	// �ֹ��� ���ط� ��ŭ ��븦 �������� 1�� ������.
	for (int i = 0; i < damage; i++)
	{
		randNumber = rand() % ListSize;
		// �̹� ���� �ϼ����� ���̻� Ÿ���� ���� �ʴ´�.(������ �׾ �� ������^^)
		if (randNumber != 0 && targetList[randNumber]->GetShield() <= 0)
		{
			i--;
			continue;
		}
		else
		{
			targetList[randNumber]->SetShield(-1);
			cout << targetList[randNumber]->GetName() << "���� ���ظ� 1�ݴϴ�." << endl;
		}
	}
	Sleep(1000);
	return true;
}

void Avenging_Wrath::detail()
{
	Magic::detail();
	cout << "��� ������ " << nPower + nPowerBonus << "�� ���ظ�" << endl
		<< "�������� ������ �����ϴ�." << endl;
}
