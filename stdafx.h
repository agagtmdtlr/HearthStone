#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <Windows.h>
#include <vector>

using namespace std;

#define DeckSetting 40
#define HandMax 5
#define FieldMax 5
#define SecretMax 3

enum class EVENT
{
	BEGIN,
	DRAW,
	USE,
	FIELD,
	ATTACK,
	SILENCE,
	DAMAGE,
	HEAL,
	NONE,
	DESTROY,
	DIE,
	END
};

enum class CardName
{
	// CREATURE
	ALDOR_PEACE_KEEPER,
	ARGENT_PROTECTER,
	BRONZE_BROODMOTHER,
	GUARDIAN_OF_KINGS,
	TIRION_FORDRING,
	// MAGIC
	AVENGING_WRATH,
	BLESSING_OF_AEONS,
	BLESSING_OF_KINGS,
	BLESSING_OF_WISDORN,
	BLESSING_OF_MIGHT,
	BLESSED_CHAMPION,	
	CONSECRATION,
	HAND_OF_PROTECTION,
	HOLY_LIGHT,
	HOLY_WRATH,
	HUMILITY,
	LAY_ON_HANDS,
	RIGHTEOUSNESS,
	EQUALITY,
	HAMMER_OF_WRATH,
	// SECRET
	EYE_FOR_AN_EYE,
	HAND_OF_SALVATION,
	NOBLE_SACRIFICE,
	REDEMPTION,
	REPENTANCE,
	// WEAPON
	LIGHTS_JUSTICE,
	SWORD_OF_JUSTICE,
	TRUESILVER_CHAMPION
};

template <typename T>
T InputVariable(T val)
{
	while (1)
	{
		cin >> val;
		if (cin.fail())
		{
			cout << "error input type please retry : ";
			cin.clear();
			cin.ignore(10, '\n');
		}
		else return val;
	}
	
}

