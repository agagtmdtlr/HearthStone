#include "stdafx.h"
#include "Creature.h"
#include "BattleField.h"
#include "Avenging_Wrath.h"

Avenging_Wrath::Avenging_Wrath(BattleField * field)
	:Magic(field, 6, "응징의 격노", 8, true)
{
}

bool Avenging_Wrath::FirstSkill()
{
	int damage = nPower + nPowerBonus;

	vector<Creature *> targetList;
	targetList.reserve(FieldMax + 1);
	// 상대 영웅을 첫번째로 넣는다 인덱스는 0이다.
	targetList.push_back((Creature *)battleFieldOfCard->User[1 - nThisCardUserNumber]);
	// 나머지 필드위의 상대 하수인을 넣어 준다.
	auto & fieldList = battleFieldOfCard->cardsOfField[1 - nThisCardUserNumber];
	for (int i = 0; i < fieldList.size();)
	{
		targetList.push_back((Creature *)fieldList[i]);
	}	
	size_t ListSize = targetList.size(); // 최종 완성된 리스트의 크기

	int randNumber;
	srand((unsigned int)(time(NULL)));
	rand();

	// 주문의 피해력 만큼 상대를 무작위로 1씩 때린다.
	for (int i = 0; i < damage; i++)
	{
		randNumber = rand() % ListSize;
		// 이미 죽은 하수인은 더이상 타겟이 되지 않는다.(영웅은 죽어도 더 때린다^^)
		if (randNumber != 0 && targetList[randNumber]->GetShield() <= 0)
		{
			i--;
			continue;
		}
		else
		{
			targetList[randNumber]->SetShield(-1);
			cout << targetList[randNumber]->GetName() << "에게 피해를 1줍니다." << endl;
		}
	}
	Sleep(1000);
	return true;
}

void Avenging_Wrath::detail()
{
	Magic::detail();
	cout << "모든 적에게 " << nPower + nPowerBonus << "의 피해를" << endl
		<< "무작위로 나누어 입힙니다." << endl;
}
