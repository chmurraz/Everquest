#include "stdafx.h"
#include "Command.h"


Command::Command()
{
	validTarget = false;
	inRange = false;
	gotExp = false;
}

void Command::Update()
{
	validTarget = botData->getValidTarget();
	inRange = botData->getInRange();
	gotExp = botData->getGotExp();
}
