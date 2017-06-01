#include "stdafx.h"
#include "Subject.h"
#include <algorithm>

void Subject::Attach(Command^ command)
{
	//list.push_back(shop);
	list->Add(command);
}
void Subject::Detach(Command^ command)
{
	//list.erase(std::remove(list.begin(), list.end(), shop), list.end());
	list->Remove(command);
}

void Subject::Notify(Command^ command)
{
	//list->ForEach(character->CharacterCommands);
	list->ForEach(command->Update);
}
