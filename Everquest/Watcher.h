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

public ref class CharacterStateUpdater
{
private:
	Character^ character;
	String^ newLine;

public:
	CharacterStateUpdater(Character^ val1, String^ val2);
	void ThreadUpdate();
};

public ref class Watcher
{
private:
	static void OnChange(Object^, FileSystemEventArgs^ e);
	static void LaunchCharStateUpdateThread(System::String^ newLine);
	FileSystemWatcher^ fileWatcher;
	static Character^ character;
	static System::String^ serverName;
	static System::String^ charName;
	static System::String^ newLine;
	static System::String^ fileName;
	static StreamReader^ sr;

public:
	//[PermissionSet(SecurityAction::Demand,Name="FullTrust")]

	Watcher(Character^ val1, System::String^ charName, System::String^ serverName);
	void setCharacter(Character^ val);
	Character^ getCharacter();
};