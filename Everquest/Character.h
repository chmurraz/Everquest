#pragma once

#include <windows.h>
#include "winuser.h"
#include <iostream>
#include <fstream>
#include <string>
#using <System.dll>
#using <System.Windows.Forms.dll>
#include "Bot.h"

using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Security::Permissions;
using namespace System::Runtime::InteropServices;

ref class Character : public Subject
{
private:
	INPUT* ip;
	DWORD rest;
	DWORD typeSpeed;
	System::String^ lastLineRead;
	System::String^ name;
	System::String^ serverName;
	System::String^ logFile;
	HWND CharacterWindowHandle;
	Bot ^botData;
	
public:
	Character();
	~Character();
	
	//	Keyboard Sim
	void PressKeys(System::String^ keys, System::Boolean enterBool);
	void HoldShift();
	void ReleaseShift();
	void PressESC();
	void PressEnter();
	void PressTab();
	void PressF1();
	void Press1();
	void Press2();
	void Press3();
	void Press4();
	void Press5();
	void Press6();
	void Press7();
	void Press8();
	void Press9();
	void Press0();
	void ProcessActions(System::String ^ newLine);

	//	Windows functions
	void BringWindowToFront();

	//	Logic function
	void CharacterActions();

	//	Mutators and Accessors
	System::String^ getLastLine();
	void setLastLineRead(System::String^ val);
	System::String^ getLastLineRead();
	System::String^ getName();
	System::String^ getServerName();
	System::String^ getLogFile();
	HWND getCharacterWindowHandle();
	void setName(System::String^ name);
	void setServer(System::String^ server);
	Bot^ getBotData();
	//void setAttributes(System::String^ name, System::String^ server);
	
	//[DllImport("user32.dll", CharSet = CharSet::Auto)]
	//static void SetWindowText(HWND charHWND, System::String^ winName);

};