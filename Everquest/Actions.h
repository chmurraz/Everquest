#pragma once
#include "Character.h"
ref class Actions
{
public:
	Actions();
	void ProcessActions(Character^ character, System::String ^newLine);
};

