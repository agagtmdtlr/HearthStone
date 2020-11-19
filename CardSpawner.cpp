#pragma once
#include "stdafx.h"
#include "BattleField.h"

#include "AldorPeaceKeeper.h"
#include "Argent_Protecter.h"
#include "Bronze_Broodmother.h"
#include "Guardian_Of_Kings.h"
#include "Tirion_Fordring.h"

#include "Avenging_Wrath.h"
#include "Blessing_Of_Aeons.h"
#include "Blessing_Of_Kings.h"
#include "Blessing_Of_Wisdorn.h"
#include "Blessing_Of_Might.h"
#include "Blessed_Champion.h"
#include "Consecration.h"
#include "Hand_Of_Protection.h"
#include "Holy_Light.h"
#include "Holy_Wrath.h"
#include "Humility.h"
#include "Lay_On_Hands.h"
#include "Righteousness.h"
#include "Equality.h"
#include "Hammer_Of_Wrath.h"

#include "Eye_For_An_Eye.h"
#include "Hand_Of_Salvation.h"
#include "Noble_Sacrifice.h"
#include "Redemption.h"
#include "Repentance.h"

#include "Lights_Justice.h"
#include "Sword_Of_Justice.h"
#include "Truesilver_Champion.h"

#include "CardSpawner.h"

void CardSpawner::SpawnCards(vector<CardName>* cardList ,BattleField * field)
{
	for (int i = 0; i < cardList->size();i++)
	{
		CardName card = cardList->at(i);

		auto & deck = field->cardsOfDeck[field->nPlayerTurn % 2];
		switch (card)
		{
			// CREATURE
		case CardName::ALDOR_PEACE_KEEPER:
			deck.push_back(new AldorPeaceKeeper(field));
			break;
		case CardName::ARGENT_PROTECTER:
			deck.push_back(new Argent_Protecter(field));
			break;
		case CardName::BRONZE_BROODMOTHER:
			deck.push_back(new Bronze_Broodmother(field));
			break;
		case CardName::GUARDIAN_OF_KINGS:
			deck.push_back(new Guardian_Of_Kings(field));
			break;
		case CardName::TIRION_FORDRING:
			deck.push_back(new Tirion_Fordring(field));
			break;
			// MAGIC
		case CardName::AVENGING_WRATH:
			deck.push_back(new Avenging_Wrath(field));
			break;
		case CardName::BLESSING_OF_AEONS:
			deck.push_back(new Blessing_Of_Aeons(field));
			break;
		case CardName::BLESSING_OF_KINGS:
			deck.push_back(new Blessing_Of_Kings(field));
			break;
		case CardName::BLESSING_OF_WISDORN:
			deck.push_back(new Blessing_Of_Wisdorn(field));
			break;
		case CardName::BLESSING_OF_MIGHT:
			deck.push_back(new Blessing_Of_Might(field));
			break;
		case CardName::BLESSED_CHAMPION:
			deck.push_back(new Blessed_Champion(field));
			break;
		case CardName::CONSECRATION:
			deck.push_back(new Consecration(field));
			break;
		case CardName::HAND_OF_PROTECTION:
			deck.push_back(new Hand_Of_Protection(field));
			break;
		case CardName::HOLY_LIGHT:
			deck.push_back(new Holy_Light(field));
			break;
		case CardName::HOLY_WRATH:
			deck.push_back(new Holy_Wrath(field));
			break;
		case CardName::HUMILITY:
			deck.push_back(new Humility(field));
			break;
		case CardName::LAY_ON_HANDS:
			deck.push_back(new Lay_On_Hands(field));
			break;
		case CardName::RIGHTEOUSNESS:
			deck.push_back(new Righteousness(field));
			break;
		case CardName::EQUALITY:
			deck.push_back(new Equality(field));
			break;
		case CardName::HAMMER_OF_WRATH:
			deck.push_back(new Hammer_Of_Wrath(field));
			break;
			// SECRET
		case CardName::EYE_FOR_AN_EYE:
			deck.push_back(new Eye_For_An_Eye(field));
			break;
		case CardName::HAND_OF_SALVATION:
			deck.push_back(new Hand_Of_Salvation(field));
			break;
		case CardName::NOBLE_SACRIFICE:
			deck.push_back(new Noble_Sacrifice(field));
			break;
		case CardName::REDEMPTION:
			deck.push_back(new Redemption(field));
			break;
		case CardName::REPENTANCE:
			deck.push_back(new Repentance(field));
			break;
			// WEAPON
		case CardName::LIGHTS_JUSTICE:
			deck.push_back(new Lights_Justice(field));
			break;
		case CardName::SWORD_OF_JUSTICE:
			deck.push_back(new Sword_Of_Justice(field));
			break;
		case CardName::TRUESILVER_CHAMPION:
			deck.push_back(new Truesilver_Champion(field));
			break;
		default:
			break;
		}
	}
}
