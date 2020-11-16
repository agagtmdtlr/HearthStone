#pragma once
#include "stdafx.h"
#include "Tirion_Fordring.h"
#include "BattleField.h"
#include "Weapon.h"
#include "Hero.h"

Tirion_Fordring::Tirion_Fordring()
{	
}

Tirion_Fordring::Tirion_Fordring(BattleField * field)
	:Creature(field, 7, "Ƽ���� ���帵", 6, 6, 1, true, true, false)
{
}


Tirion_Fordring::~Tirion_Fordring()
{	
}


void Tirion_Fordring::detail()
{
	Creature::detail();
	cout << "õ���� ��ȣ��,����," << endl
		<< "������ �޾Ƹ� : 5/3 �ĸ��� �ε��ڸ� ��ȯ�մϴ�" << endl;
}

void Tirion_Fordring::SetDelete(bool val)
{
	cout << "delete" << endl;
	system("pause");
	Card::SetDelete(val);
	cout << "5/3 �ĸ��� �ε��ڸ� �����մϴ�." << endl;
	Sleep(1500);
	/*battleFieldOfCard->cardsOfField[nThisCardUserNumber].push_back(
		new Creature(
			battleFieldOfCard, 2, "�ĸ��� �ε���", 5, 3, 1, false, false, false));*/
	
	Hero * hero = (Hero *)battleFieldOfCard->User[nThisCardUserNumber];
	hero->SetWeapon(
		new Weapon(
			nThisCardUserNumber,
			battleFieldOfCard, 2, "�ĸ��� �ε���", 5, 3, 1)
	);
	
	cout << "end" << endl;
	system("pause");
}
