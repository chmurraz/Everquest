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
	static void OnChange1(Object^ source, FileSystemEventArgs^ e);
	static void OnChange2(Object^ source, FileSystemEventArgs^ e);
	static void OnChange3(Object^ source, FileSystemEventArgs^ e);
	static FileSystemWatcher^ fileWatcher1;
	static FileSystemWatcher^ fileWatcher2;
	static FileSystemWatcher^ fileWatcher3;

	static Character^ character1;
	static Character^ character2;
	static Character^ character3;

	static StreamReader^ sr1;
	static StreamReader^ sr2;
	static StreamReader^ sr3;

	static void ScanLines(FileSystemWatcher^ fileWatcher, Character^ character, StreamReader^ sr);

public:
	//[PermissionSet(SecurityAction::Demand,Name="FullTrust")]

	Watcher(Character^ character1, Character^ character2, Character^ character3);
};