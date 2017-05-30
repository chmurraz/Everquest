#include "stdafx.h"
#include "Command.h"


Command::Command()
{
	validTarget = false;
	inRange = false;
	gotExp = false;
}

void Command::Update(Bot ^botData)
{
	validTarget = botData->getValidTarget();
	inRange = botData->getInRange();
	gotExp = botData->getGotExp();
}
