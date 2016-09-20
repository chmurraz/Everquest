#pragma once

#include <windows.h>
#include "winuser.h"
#include <iostream>
#include <fstream>
#include <string>
#using <System.dll>
#using <System.Windows.Forms.dll>
using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Security::Permissions;

ref class Character
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

	
public:
	Character(System::String^ name, System::String^ serverName);
	~Character();
	
	//	Keyboard Sim
	void PressKeys(System::String^ keys);
	void HoldShift();
	void ReleaseShift();
	void PressESC();
	void PressTab();
	void PressF1();

	//	Mutators and Accessors
	System::String^ getLastLine();
	void setLastLineRead(System::String^ val);
	System::String^ getLastLineRead();
	System::String^ getName();
	System::String^ getServerName();
	System::String^ getLogFile();
	void CharacterActions();
};