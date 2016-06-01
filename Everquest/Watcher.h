#pragma once

#using <System.dll>
#using <System.Windows.Forms.dll>
#include "Character.h"
using namespace System;
using namespace System::IO;
using namespace System::Security::Permissions;
using namespace System::Threading;

//	Based off of the following website:
//	https://msdn.microsoft.com/en-us/library/system.io.filesystemwatcher.changed(v=vs.90).aspx

public ref class WatcherThreadWithState
{
private:
	Character^ threadCharacter;
	String^ threadLine;

public:
	WatcherThreadWithState(Character^ val1, String^ val2);
	void ThreadProc();
};


public ref class Watcher
{
private:
	static void OnChange(Object^, FileSystemEventArgs^ e);
	FileSystemWatcher^ watcher;
	static Character^ character;
	static System::String^ newLine;
	static StreamReader^ sr;

public:
	//[PermissionSet(SecurityAction::Demand,Name="FullTrust")]

	Watcher();
	void ScanLog();
	void setCharacter(Character^ val);
};

