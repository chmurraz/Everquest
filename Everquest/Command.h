#pragma once
//#include "Observer.h"
#include "Bot.h"

public delegate void MyDelegate(int number);

//ref class Command : Observer
ref class Command
{
private:
	bool validTarget;
	bool inRange;
	bool gotExp;
	Bot ^botData;
public:
	Command();
	//void Update() override;
	void Delegate1(int number);
	void Delegate2(int number);
	void Handler(int i, float f);
};

