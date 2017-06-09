#include "stdafx.h"
#include "Command.h"


Command::Command()
{
	ip = new INPUT;
	rest = 0;
	typeSpeed = 45;
}

Command::~Command()
{
	delete ip;
	ip = NULL;
}

void Command::Delegate1(int number)
{
	//	Do stuff
}

void Command::Delegate2(int number)
{
	//	Do other stuff
}

void Command::Handler(System::String^ eventText, Bot^ botData, System::String^ logFile)
{
	System::IO::StreamWriter ^sw = gcnew System::IO::StreamWriter(logFile);
	System::Console::WriteLine("EventTriggered");
	if (eventText == "Talking to yourself")
	{
		PressTab();
		PressKeys("/consider", true);
	}
	if (eventText == "what would you like your tombstone to say")
	{
		PressTab();
		PressKeys("/consider", true);
	}
	if (eventText == "practice skills" && !botData->getLowMana())
	{

		PressF1();
		PressKeys("/cast 1", true);
		Sleep(4000);
		//sw->WriteLine("practice skills");
		//sw->Close();
		//PressKeys("/cast 2", true);
		//Sleep(4000);
		//PressKeys("/cast 3", true);
		//Sleep(4000);
		//PressKeys("/cast 4", true);
		//Sleep(5000);
		//PressKeys("/autoinv", true);
		//PressKeys("/cast 5", true);
		//Sleep(4000); 
		PressKeys("practice skills", true);
	}
	if (eventText == "Insufficient Mana to cast this spell")
	{
		PressKeys("/sit", true);
		Sleep(60000);
		botData->setLowMana(false);
		PressKeys("/1 practice skills", true);
	}

	if (eventText == "Go swim")
	{
		PressKeyTest(0x57, false);
		PressKeyTest(0x44, false);
	}
}

void Command::PressKeys(System::String^ keys, System::Boolean enterBool)
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

void Command::PressKeyTest(UINT key)
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

void Command::PressKeyTest(UINT key, bool hold)
{
	ip->type = INPUT_KEYBOARD;
	ip->ki.dwExtraInfo = GetMessageExtraInfo();
	ip->ki.wScan = static_cast<WORD>(MapVirtualKey(key, MAPVK_VK_TO_VSC));
	ip->ki.time = 0;

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	ip->ki.dwFlags = 0;	//	0 for keypress
	SendInput(1, ip, sizeof(INPUT));

	if (!hold)
	{
		ip->ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, ip, sizeof(INPUT));
	}
}

void Command::PressESC()
{
	PressKeyTest(VK_ESCAPE);
}

void Command::PressEnter()
{
	PressKeyTest(VK_RETURN);
	Sleep(100);
}

void Command::PressTab()
{
	PressKeyTest(VK_TAB);
}

void Command::PressF1()
{
	PressKeyTest(VK_F1);
}

void Command::Press1()
{
	PressKeyTest(VK_NUMPAD1);
}

void Command::Press2()
{
	PressKeyTest(VK_NUMPAD2);
}

void Command::Press3()
{
	PressKeyTest(VK_NUMPAD3);
}

void Command::Press4()
{
	PressKeyTest(VK_NUMPAD4);
}

void Command::Press5()
{
	PressKeyTest(VK_NUMPAD5);
}

void Command::Press6()
{
	PressKeyTest(VK_NUMPAD6);
}

void Command::Press7()
{
	PressKeyTest(VK_NUMPAD7);
}

void Command::Press8()
{
	PressKeyTest(VK_NUMPAD8);
}

void Command::Press9()
{
	PressKeyTest(VK_NUMPAD9);
}

void Command::Press0()
{
	PressKeyTest(VK_NUMPAD0);
}

void Command::PressUp()
{
	PressKeyTest(VK_UP);
}

void Command::PressW()
{
	PressKeyTest(0x57);
}

void Command::PressD()
{
	PressKeyTest(0x44);
}

void Command::PressRight()
{
	PressKeyTest(VK_RIGHT);
}

void Command::HoldShift()
{
	PressKeyTest(VK_SHIFT, true);
}

void Command::ReleaseShift()
{
	PressKeyTest(VK_SHIFT);
}
