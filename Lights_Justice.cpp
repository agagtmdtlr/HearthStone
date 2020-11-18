#include "stdafx.h"
#include "Lights_Justice.h"

Lights_Justice::Lights_Justice(BattleField * field, int cost, string name, int power, int durability, int attcount)
	:Weapon(field,1,"ºûÀÇ Á¤ÀÇ",1,4,1)
{
}

Lights_Justice::Lights_Justice(int userNumber, BattleField * field, int cost, string name, int power, int durability, int attcount)
	: Weapon(userNumber,field, 1, "ºûÀÇ Á¤ÀÇ", 1, 4, 1)
{
}
