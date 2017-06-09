#pragma once

#include <windows.h>
#include "winuser.h"
#include <iostream>
#include <fstream>
#include <string>
#using <System.dll>
#using <System.Windows.Forms.dll>
#include "Bot.h"
//#include "Subject.h"
#include "Command.h"

using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Security::Permissions;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;

//	CHANGE THE NAME OF THIS DELEGATE.  EVENTS ARE RAISED BASED ON STRING MATCHES NOW, NOT BOTDATA
public delegate void BotDataChanged(System::String^, Bot^, System::String^);

//	interface that has an event and a function to invoke the event
interface struct I
{
public:
	event BotDataChanged ^E;
	void fire(System::String^, Bot^);
};

ref class EventBlob
{
private:
	System::String^ eventText;
	bool additionalLogic;
	System::String^ botDataType;
	bool botDataValue;
public:
	EventBlob(System::String^, bool, System::String^, bool);
	System::String^ getEventText();
	bool getLogic();
	System::String^ getBotDataType();
	bool getBotDataValue();
};

//ref class Character : public Subject
ref class Character: public I
{
private:

	System::String^ lastLineRead;
	System::String^ name;
	System::String^ serverName;
	System::String^ logFile;
	HWND CharacterWindowHandle;
	Bot ^botData;
	Command ^command;
	List<EventBlob^>^ eventList;
	
public:
	Character();

	//	Events
	virtual event BotDataChanged ^E;
	virtual void fire(System::String^ t, Bot^ botData)
	{
		E(t, botData, logFile);
	}
	void eventRaised(System::String^ t);
	void EventBuilder();

	//	Windows functions
	void BringWindowToFront();

	//	Logic function
	void PrintNewLine();
	void ProcessCommands(System::String ^ newLine);

	//	Delegate functions
	void DelegateMethod(int number);

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