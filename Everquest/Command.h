#pragma once
//#include "Observer.h"

public delegate void MyDelegate(int number);

//ref class Command : Observer
ref class Command
{
private:

public:
	Command();
	//void Update() override;
	void Delegate1(int number);
	void Delegate2(int number);
	void Handler(bool, bool, bool);
};

