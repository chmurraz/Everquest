#include "stdafx.h"
#include "Command.h"


Command::Command()
{

}

void Command::Delegate1(int number)
{
	//	Do stuff
}

void Command::Delegate2(int number)
{
	//	Do other stuff
}

void Command::Handler(bool validTarget, bool inRange, bool gotExp)
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
