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
using namespace System::Runtime::InteropServices;

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
	Character();
	~Character();
	
	//	Keyboard Sim
	void PressKeys(System::String^ keys);
	void HoldShift();
	void ReleaseShift();
	void PressESC();
	void PressTab();
	void PressF1();

	//	Logic function
	void CharacterActions();

	//	Mutators and Accessors
	System::String^ getLastLine();
	void setLastLineRead(System::String^ val);
	System::String^ getLastLineRead();
	System::String^ getName();
	System::String^ getServerName();
	System::String^ getLogFile();
	void setAttributes(System::String^ name, System::String^ server);
	
	[DllImport("user32.dll", CharSet = CharSet::Auto)]
	static void SetWindowText(HWND charHWND, System::String^ winName);

};