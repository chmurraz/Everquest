#pragma once
#include "Command.h"
#include "Bot.h"
using namespace System::Collections::Generic;

ref class Subject
{
private:

	//Lets keep a track of all the shops we have observing
	List<Command^>^ list;
	//List<String^>^ dinosaurs = gcnew List<String^>();

public:
	void Attach(Command ^command);
	void Detach(Command ^command);
	void Notify(Bot ^botData);
};

