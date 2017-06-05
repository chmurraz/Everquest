#include "stdafx.h"
#include "Character.h"

Character::Character()
{

	lastLineRead = "";
	name = "";
	serverName = "";
	logFile = "";
	CharacterWindowHandle = NULL;
	botData = gcnew Bot;
	command = gcnew Command;
	eventList = gcnew List<EventBlob^>();

	//	Build events list
	EventBuilder();
}

void Character::EventBuilder()
{
	EventBlob ^considerWhom = gcnew EventBlob("Consider whom", true,"", false);
	EventBlob ^looksRisky = gcnew EventBlob("looks kind of risky", true, "validTarget", true);
	EventBlob ^tombstone = gcnew EventBlob("what would you like your tombstone to say", true, "validTarget", false);
	EventBlob ^cantSee = gcnew EventBlob("You cannot see your target", true, "validTarget", false);
	EventBlob ^talkingSelf = gcnew EventBlob("Talking to yourself", true, "", false);
	EventBlob ^gotExp = gcnew EventBlob("You gain experience", true, "gotExp", true);
	EventBlob ^outRange = gcnew EventBlob("out of range", true, "validTarget", false);
	EventBlob ^inRange = gcnew EventBlob("You begin casting", botData->getValidTarget(), "inRange", true);
	EventBlob ^spellHit = gcnew EventBlob("of non-melee damage", true, "", false);

	eventList->Add(considerWhom);
	eventList->Add(looksRisky);
	eventList->Add(cantSee);
	eventList->Add(talkingSelf);
	eventList->Add(gotExp);
	eventList->Add(outRange);
	eventList->Add(inRange);
	eventList->Add(spellHit);
}

void Character::eventRaised(System::String^ eventText)
{
	//	Hook the handler to the event
	E += gcnew BotDataChanged(command, &Command::Handler);

	//	Call the event
	fire(eventText, botData->getValidTarget(), botData->getInRange(), botData->getGotExp());

	//	Unhook the handler from the event
	E -= gcnew BotDataChanged(command, &Command::Handler);
}



System::String ^ Character::getLastLine()
{
	/*
	std::string line;
	std::ifstream inFile;
	inFile.open("C:\\Users\\Public\\Daybreak Game Company\\Installed Games\\EverQuest\\Logs\\eqlog_Xahul_phinigel.txt");

	while (inFile >> std::ws && std::getline(inFile, line))
	{
	};
	System::String^ line2 = gcnew String(line.c_str());
	inFile.close();
	return line2;
	*/
	return lastLineRead;
}

void Character::setLastLineRead(System::String ^ val)
{
	lastLineRead = val;
}

System::String ^ Character::getLastLineRead()
{
	return lastLineRead;
}

System::String ^ Character::getName()
{
	return name;
}

System::String ^ Character::getServerName()
{
	return serverName;
}

System::String ^ Character::getLogFile()
{
	return logFile;
}

HWND Character::getCharacterWindowHandle()
{
	return CharacterWindowHandle;
}

void Character::setName(System::String ^ nameVal)
{
	name = nameVal;
	if (serverName != "")
	{
		logFile = "C:\\Users\\Public\\Daybreak Game Company\\Installed Games\\EverQuest\\Logs\\eqlog_";
		logFile += name + "_" + serverName + ".txt";
		CharacterWindowHandle = FindWindow("_EverQuestwndclass", "EverQuest");
		//SetWindowText(CharacterWindowHandle, name->);

		//	Erase the old log files
		File::Delete(logFile);
	}

}

void Character::setServer(System::String ^ serverVal)
{
	serverName = serverVal;
	if (name != "")
	{
		logFile = "C:\\Users\\Public\\Daybreak Game Company\\Installed Games\\EverQuest\\Logs\\eqlog_";
		logFile += name + "_" + serverName + ".txt";
		CharacterWindowHandle = FindWindow("_EverQuestwndclass", "EverQuest");
		//SetWindowText(CharacterWindowHandle, name->);

		//	Erase the old log files
		File::Delete(logFile);
	}
}

Bot^ Character::getBotData()
{
	return botData;
}

/*
void Character::setAttributes(System::String ^ nameVal, System::String ^ serverVal)
{
	name = nameVal;
	serverName = serverVal;
	logFile = "C:\\Users\\Public\\Daybreak Game Company\\Installed Games\\EverQuest\\Logs\\eqlog_";
	logFile += name + "_" + serverName + ".txt";
	CharacterWindowHandle = FindWindow("_EverQuestwndclass", "EverQuest");
	//SetWindowText(CharacterWindowHandle, name->);

	//	Erase the old log files
	File::Delete(logFile);
}
*/

//	Launch commands based on the lastLineRead from the log file
void Character::PrintNewLine()
{
	Console::WriteLine(lastLineRead);
	// DELETE THIS LINE?? Old deprecated crap?? Notify(botData);
}

void Character::DelegateMethod(int number)
{
	throw gcnew System::NotImplementedException();
}

void Character::BringWindowToFront()
{
	SetForegroundWindow(CharacterWindowHandle);
	Sleep(150);
}



void Character::ProcessCommands(System::String ^ newLine)
{
	/* WORK ON KHAED RAVEK STUFF BELOW*/
	/*
	if (character->getName() == "Khaed")
	{
	if (newLine->Contains("Assist me Khaed!"))
	{
	character->BringWindowToFront();
	character->PressKeys("/assist izzuum", true);
	character1->BringWindowToFront();
	}
	if (newLine->Contains("Khaed, play your group buffs please"))
	{
	character->BringWindowToFront();
	character->PressKeys("/stopsong", true);
	character->PressKeys("/melody 3 5 8 9 1 3 5 8 9 1 3 5 8 9 1 4", true);
	character->PressKeys("/g ", false);
	character->HoldShift();
	character->PressKeys("i ", false);
	character->ReleaseShift();
	character->PressKeys("have started singing my buff songs", true);
	//character->Press6();
	character1->BringWindowToFront();
	}
	if (newLine->Contains("Khaed, stop singing"))
	{
	character->BringWindowToFront();
	character->PressKeys("/stopsong", true);
	character->PressKeys("/g ", false);
	character->HoldShift();
	character->PressKeys("i ", false);
	character->ReleaseShift();
	character->PressKeys("have stopped singing", true);
	character1->BringWindowToFront();
	}
	if (newLine->Contains("Khaed, mesmerize my target"))
	{
	character->BringWindowToFront();
	character->PressKeys("/stopsong", true);
	character->PressKeys("/assist Izzuum", true);
	character->PressKeys("/attackoff", true);
	character->PressKeys("/melody 11", true);
	character->PressKeys("/g ", false);
	character->HoldShift();
	character->PressKeys("i ", false);
	character->ReleaseShift();
	character->PressKeys("am mesmerizing it", true);
	character1->BringWindowToFront();
	}
	if (newLine->Contains("Khaed, slow them down"))
	{
	character->BringWindowToFront();
	character->PressKeys("/stopsong", true);
	character->PressKeys("/melody 2 1 3 8 9", true);
	character->PressKeys("/g ", false);
	character->HoldShift();
	character->PressKeys("i ", false);
	character->ReleaseShift();
	character->PressKeys("am slowing them", true);
	character1->BringWindowToFront();
	}
	if (newLine->Contains("Khaed, AoE mez and assist"))
	{
	character->BringWindowToFront();
	character->PressKeys("/stopsong", true);
	character->PressKeys("/assist Izzuum", true);
	character->PressKeys("/melody 10 2 12 8 3 5 12 8 3 5 12", true);
	character->PressKeys("/g ", false);
	character->HoldShift();
	character->PressKeys("i ", false);
	character->ReleaseShift();
	character->PressKeys("am slowing them", true);
	character1->BringWindowToFront();
	}
	}
	if (character->getName() == "Ravek")
	{
	if (newLine->Contains("Assist me Ravek!"))
	{
	character->BringWindowToFront();
	character->PressKeys("/assist izzuum", true);
	character->PressKeys("/pet attack", true);
	character1->BringWindowToFront();
	}
	if (newLine->Contains("Ravek, flameskin please"))
	{
	character->BringWindowToFront();
	character->PressKeys("/cast 11", true);
	character->PressKeys("/g ", false);
	character->HoldShift();
	character->PressKeys("t", false);
	character->ReleaseShift();
	character->PressKeys("he group has been immolated", true);
	character1->BringWindowToFront();
	}
	}
	*/
	if (name == "Xuurak")
	{
		//	Find valid target
		//	Attempt to nuke
		//	If out of range
		//	If can't see
		//	If damaged, keep in combat
		//	Check for exp gain
		//	Remove valid target
		//	Remove from combat
		//	Sit
		for each(EventBlob^ eventBlob in eventList)
		{
			if (newLine->Contains(eventBlob->getEventText()) && eventBlob->getLogic())
				eventRaised(eventBlob->getEventText());
			if (eventBlob->getBotDataType() == "validTarget")
				botData->setValidTarget(eventBlob->getBotDataValue());
			if (eventBlob->getBotDataType() == "inRange")
				botData->setInRange(eventBlob->getBotDataValue());
			if (eventBlob->getBotDataType() == "gotExp")
				botData->setGotExp(eventBlob->getBotDataValue());
		}
	}
}

EventBlob::EventBlob(System::String ^eventtext, bool logic, System::String ^botType, bool botValue)
{
	eventText = eventtext;
	additionalLogic = logic;
	botDataType = botType;
	botDataValue = botValue;
}

System::String ^ EventBlob::getEventText()
{
	return eventText;
}

bool EventBlob::getLogic()
{
	return additionalLogic;
}

System::String ^ EventBlob::getBotDataType()
{
	return botDataType;
}

bool EventBlob::getBotDataValue()
{
	return botDataValue;
}
