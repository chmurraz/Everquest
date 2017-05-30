#pragma once
#include "Observer.h"
#include "Bot.h"
ref class Command : Observer
{
private:
	bool validTarget;
	bool inRange;
	bool gotExp;
public:
	Command();
	void Update(Bot ^botData);
};

