#pragma once
#include "Observer.h"
#include "Bot.h"
ref class Command : Observer
{
private:
	bool validTarget;
	bool inRange;
	bool gotExp;
	Bot ^botData;
public:
	Command();
	//void Update() override;
	void Update() override;
};

