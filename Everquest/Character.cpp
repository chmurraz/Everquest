#include "stdafx.h"
#include "Character.h"

Character::Character()
{
	ip = new INPUT;
	rest = 0;
	typeSpeed = 45;
	lastLineRead = "";
	name = "";
	serverName = "";
	logFile = "";
	CharacterWindowHandle = NULL;
	botData = gcnew Bot;
	command = gcnew Command;
}

Character::~Character()
{
	delete ip;
	ip = NULL;
}

void Character::eventRaised()
{
	//	Hook the handler to the event
	E += gcnew BotDataChanged(command, &Command::Handler);

	//	Call the event
	fire(botData->getValidTarget(), botData->getInRange(), botData->getGotExp());

	//	Unhook the handler from the event
	E -= gcnew BotDataChanged(command, &Command::Handler);
}

void Character::PressKeys(System::String^ keys, System::Boolean enterBool)
{
	for (unsigned i = 0; i < keys->Length; i++)
	{
		ip->type = INPUT_KEYBOARD;
		ip->ki.dwExtraInfo = GetMessageExtraInfo();

		//	would use char ch = keys->at(i); for a C++ std:string
		char ch = keys[i];

		ip->ki.wScan = static_cast<WORD>(MapVirtualKeyEx(VkKeyScanA(ch), MAPVK_VK_TO_VSC, GetKeyboardLayout(0)));
		ip->ki.time = 0;

		//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

		ip->ki.dwFlags = 0;	//	0 for keypress
		SendInput(1, ip, sizeof(INPUT));
		ip->ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, ip, sizeof(INPUT));
		// Use this sleep line to debug each character one at a time in EQ
		Sleep(typeSpeed);
	}
	if (enterBool)
		PressEnter();
	Sleep(rest);
}

void Character::PressKeyTest(UINT key)
{
	ip->type = INPUT_KEYBOARD;
	ip->ki.dwExtraInfo = GetMessageExtraInfo();
	ip->ki.wScan = static_cast<WORD>(MapVirtualKey(key, MAPVK_VK_TO_VSC));
	ip->ki.time = 0;

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	ip->ki.dwFlags = 0;	//	0 for keypress
	SendInput(1, ip, sizeof(INPUT));
	ip->ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, ip, sizeof(INPUT));
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
void Character::CharacterCommands()
{
	Console::WriteLine(lastLineRead);
	// DELETE THIS LINE?? Notify(botData);
}

void Character::DelegateMethod(int number)
{
	throw gcnew System::NotImplementedException();
}

void Character::PressESC()
{
	PressKeyTest(VK_ESCAPE);
}

void Character::PressEnter()
{
	PressKeyTest(VK_RETURN);
	Sleep(100);
}

void Character::PressTab()
{
	PressKeyTest(VK_TAB);
}

void Character::PressF1()
{
	PressKeyTest(VK_F1);
}

void Character::Press1()
{
	PressKeyTest(VK_NUMPAD1);
}

void Character::Press2()
{
	PressKeyTest(VK_NUMPAD2);
}

void Character::Press3()
{
	PressKeyTest(VK_NUMPAD3);
}

void Character::Press4()
{
	PressKeyTest(VK_NUMPAD4);
}

void Character::Press5()
{
	PressKeyTest(VK_NUMPAD5);
}

void Character::Press6()
{
	PressKeyTest(VK_NUMPAD6);
}

void Character::Press7()
{
	PressKeyTest(VK_NUMPAD7);
}

void Character::Press8()
{
	PressKeyTest(VK_NUMPAD8);
}

void Character::Press9()
{
	PressKeyTest(VK_NUMPAD9);
}

void Character::Press0()
{
	PressKeyTest(VK_NUMPAD0);
}

void Character::BringWindowToFront()
{
	SetForegroundWindow(CharacterWindowHandle);
	Sleep(150);
}

void Character::HoldShift()
{
	ip->type = INPUT_KEYBOARD;
	ip->ki.dwExtraInfo = GetMessageExtraInfo();
	ip->ki.wScan = static_cast<WORD>(MapVirtualKey(VK_SHIFT, MAPVK_VK_TO_VSC));
	ip->ki.time = 0;

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	ip->ki.dwFlags = 0;	//	0 for keypress
	SendInput(1, ip, sizeof(INPUT));
}

void Character::ReleaseShift()
{
	ip->type = INPUT_KEYBOARD;
	ip->ki.dwExtraInfo = GetMessageExtraInfo();
	ip->ki.wScan = static_cast<WORD>(MapVirtualKey(VK_SHIFT, MAPVK_VK_TO_VSC));
	ip->ki.time = 0;

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	ip->ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, ip, sizeof(INPUT));
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
		if (newLine->Contains("Consider whom"))
		{
			PressTab();
			PressKeys("/consider", true);
		}
		if (newLine->Contains("looks kind of risky"))
			botData->setValidTarget(true);
		if (newLine->Contains("You cannot see your target"))
			botData->setValidTarget(false);
		if (newLine->Contains("Talking to yourself"))
		{
			PressESC();
			PressKeys("/consider", true);
			botData->setValidTarget(false);
		}
		if (newLine->Contains("You gain experience"))
			botData->setGotExp(true);
		if (newLine->Contains("out of range"))
			botData->setInRange(false);
		if (newLine->Contains("You begin casting") && botData->getValidTarget())
			botData->setInRange(true);
		if ((newLine->Contains("Xuurak hit") && newLine->Contains("of non-melee damage")) || newLine->Contains("resist"))
		{
			int count = 0;
			do
			{
				PressKeys("/cast 5", true);
				Sleep(4000);
				count++;
			} while (count < 7);
			PressKeys("/sit", true);
			botData->falseAllBools();
		}
		if (getBotData()->getValidTarget() && getBotData()->getInRange())
			PressKeys("/cast 5", true);
	}
	eventRaised();
}
