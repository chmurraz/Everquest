#include "stdafx.h"
#include "Command.h"


Command::Command()
{
	validTarget = false;
	inRange = false;
	gotExp = false;
}

void Command::Delegate1(int number)
{
	//	Do stuff
}

void Command::Delegate2(int number)
{
	//	Do other stuff
}

void Command::Handler(int i, float f)
{
	System::Console::WriteLine("EventTriggered");
}

/*
void Command::Update()
{
	validTarget = botData->getValidTarget();
	inRange = botData->getInRange();
	gotExp = botData->getGotExp();
}
*/
