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
}

Character::~Character()
{
	delete ip;
	ip = NULL;
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

//	Launch actions based on the lastLineRead from the log file
void Character::CharacterActions()
{
	Console::WriteLine(lastLineRead);
}

void Character::PressESC()
{
	ip->type = INPUT_KEYBOARD;
	ip->ki.dwExtraInfo = GetMessageExtraInfo();
	ip->ki.wScan = static_cast<WORD>(MapVirtualKey(VK_ESCAPE, MAPVK_VK_TO_VSC));
	ip->ki.time = 0;

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	ip->ki.dwFlags = 0;	//	0 for keypress
	SendInput(1, ip, sizeof(INPUT));
	ip->ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, ip, sizeof(INPUT));
}

void Character::PressEnter()
{
	ip->type = INPUT_KEYBOARD;
	ip->ki.dwExtraInfo = GetMessageExtraInfo();
	ip->ki.wScan = static_cast<WORD>(MapVirtualKey(VK_RETURN, MAPVK_VK_TO_VSC));
	ip->ki.time = 0;

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	ip->ki.dwFlags = 0;	//	0 for keypress
	SendInput(1, ip, sizeof(INPUT));
	ip->ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, ip, sizeof(INPUT));
	Sleep(100);
}

void Character::PressTab()
{
	ip->type = INPUT_KEYBOARD;
	ip->ki.dwExtraInfo = GetMessageExtraInfo();
	ip->ki.wScan = static_cast<WORD>(MapVirtualKey(VK_TAB, MAPVK_VK_TO_VSC));
	ip->ki.time = 0;

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	ip->ki.dwFlags = 0;	//	0 for keypress
	SendInput(1, ip, sizeof(INPUT));
	ip->ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, ip, sizeof(INPUT));
}

void Character::PressF1()
{
	ip->type = INPUT_KEYBOARD;
	ip->ki.dwExtraInfo = GetMessageExtraInfo();
	ip->ki.wScan = static_cast<WORD>(MapVirtualKey(VK_F1, MAPVK_VK_TO_VSC));
	ip->ki.time = 0;

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	ip->ki.dwFlags = 0;	//	0 for keypress
	SendInput(1, ip, sizeof(INPUT));
	ip->ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, ip, sizeof(INPUT));
}

void Character::Press1()
{
	ip->type = INPUT_KEYBOARD;
	ip->ki.dwExtraInfo = GetMessageExtraInfo();
	ip->ki.wScan = static_cast<WORD>(MapVirtualKey(VK_NUMPAD1, MAPVK_VK_TO_VSC));
	ip->ki.time = 0;

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	ip->ki.dwFlags = 0;	//	0 for keypress
	SendInput(1, ip, sizeof(INPUT));
	ip->ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, ip, sizeof(INPUT));
}

void Character::Press2()
{
	ip->type = INPUT_KEYBOARD;
	ip->ki.dwExtraInfo = GetMessageExtraInfo();
	ip->ki.wScan = static_cast<WORD>(MapVirtualKey(VK_NUMPAD2, MAPVK_VK_TO_VSC));
	ip->ki.time = 0;

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	ip->ki.dwFlags = 0;	//	0 for keypress
	SendInput(1, ip, sizeof(INPUT));
	ip->ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, ip, sizeof(INPUT));
}

void Character::Press3()
{
	ip->type = INPUT_KEYBOARD;
	ip->ki.dwExtraInfo = GetMessageExtraInfo();
	ip->ki.wScan = static_cast<WORD>(MapVirtualKey(VK_NUMPAD3, MAPVK_VK_TO_VSC));
	ip->ki.time = 0;

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	ip->ki.dwFlags = 0;	//	0 for keypress
	SendInput(1, ip, sizeof(INPUT));
	ip->ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, ip, sizeof(INPUT));
}

void Character::Press4()
{
	ip->type = INPUT_KEYBOARD;
	ip->ki.dwExtraInfo = GetMessageExtraInfo();
	ip->ki.wScan = static_cast<WORD>(MapVirtualKey(VK_NUMPAD4, MAPVK_VK_TO_VSC));
	ip->ki.time = 0;

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	ip->ki.dwFlags = 0;	//	0 for keypress
	SendInput(1, ip, sizeof(INPUT));
	ip->ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, ip, sizeof(INPUT));
}

void Character::Press5()
{
	ip->type = INPUT_KEYBOARD;
	ip->ki.dwExtraInfo = GetMessageExtraInfo();
	ip->ki.wScan = static_cast<WORD>(MapVirtualKey(VK_NUMPAD5, MAPVK_VK_TO_VSC));
	ip->ki.time = 0;

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	ip->ki.dwFlags = 0;	//	0 for keypress
	SendInput(1, ip, sizeof(INPUT));
	ip->ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, ip, sizeof(INPUT));
}

void Character::Press6()
{
	ip->type = INPUT_KEYBOARD;
	ip->ki.dwExtraInfo = GetMessageExtraInfo();
	ip->ki.wScan = static_cast<WORD>(MapVirtualKey(0x36, MAPVK_VK_TO_VSC));
	ip->ki.time = 0;

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	ip->ki.dwFlags = 0;	//	0 for keypress
	SendInput(1, ip, sizeof(INPUT));
	ip->ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, ip, sizeof(INPUT));
}

void Character::Press7()
{
	ip->type = INPUT_KEYBOARD;
	ip->ki.dwExtraInfo = GetMessageExtraInfo();
	ip->ki.wScan = static_cast<WORD>(MapVirtualKey(VK_NUMPAD7, MAPVK_VK_TO_VSC));
	ip->ki.time = 0;

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	ip->ki.dwFlags = 0;	//	0 for keypress
	SendInput(1, ip, sizeof(INPUT));
	ip->ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, ip, sizeof(INPUT));
}

void Character::Press8()
{
	ip->type = INPUT_KEYBOARD;
	ip->ki.dwExtraInfo = GetMessageExtraInfo();
	ip->ki.wScan = static_cast<WORD>(MapVirtualKey(VK_NUMPAD8, MAPVK_VK_TO_VSC));
	ip->ki.time = 0;

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	ip->ki.dwFlags = 0;	//	0 for keypress
	SendInput(1, ip, sizeof(INPUT));
	ip->ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, ip, sizeof(INPUT));
}

void Character::Press9()
{
	ip->type = INPUT_KEYBOARD;
	ip->ki.dwExtraInfo = GetMessageExtraInfo();
	ip->ki.wScan = static_cast<WORD>(MapVirtualKey(VK_NUMPAD9, MAPVK_VK_TO_VSC));
	ip->ki.time = 0;

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	ip->ki.dwFlags = 0;	//	0 for keypress
	SendInput(1, ip, sizeof(INPUT));
	ip->ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, ip, sizeof(INPUT));
}

void Character::Press0()
{
	ip->type = INPUT_KEYBOARD;
	ip->ki.dwExtraInfo = GetMessageExtraInfo();
	ip->ki.wScan = static_cast<WORD>(MapVirtualKey(VK_NUMPAD0, MAPVK_VK_TO_VSC));
	ip->ki.time = 0;

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	ip->ki.dwFlags = 0;	//	0 for keypress
	SendInput(1, ip, sizeof(INPUT));
	ip->ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, ip, sizeof(INPUT));
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