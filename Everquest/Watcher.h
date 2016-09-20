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

public ref class Watcher
{
private:
	static void OnChange(Object^, FileSystemEventArgs^ e);
	FileSystemWatcher^ fileWatcher;
	Character^ character;
	System::String^ newLine;
	System::String^ fileName;
	StreamReader^ sr;

public:
	//[PermissionSet(SecurityAction::Demand,Name="FullTrust")]

	Watcher(Character^ character);
};