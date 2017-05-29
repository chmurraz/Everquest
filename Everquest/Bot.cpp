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

void Bot::falseAllBools()
{
	validTarget = false;
	gotExp = false;
	inRange = false;
}
