#include "stdafx.h"
#include "Bot.h"


Bot::Bot()
{
	validTarget = false;
	inRange = false;
	gotExp = false;
}

bool Bot::getValidTarget()
{
	return validTarget;
}

bool Bot::getInRange()
{
	return inRange;
}

bool Bot::getGotExp()
{
	return gotExp;
}

bool Bot::getLowMana()
{
	return lowMana;
}

void Bot::setValidTarget(bool input)
{
	validTarget = input;
}

void Bot::setInRange(bool input)
{
	inRange = input;
}

void Bot::setGotExp(bool input)
{
	gotExp = input;
}

void Bot::setLowMana(bool input)
{
	lowMana = input;
}

void Bot::falseAllBools()
{
	validTarget = false;
	gotExp = false;
	inRange = false;
	lowMana = false;
}
