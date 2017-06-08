#include "stdafx.h"
#include "Watcher.h"
#include "EverquestForm.h"


Watcher::Watcher(Character^ char1, Character^ char2, Character^ char3)
{
	fileWatcher1 = gcnew FileSystemWatcher;
	//fileWatcher2 = gcnew FileSystemWatcher;
	//fileWatcher3 = gcnew FileSystemWatcher;

	//lineQ = gcnew System::Collections::Queue;

	character1 = char1;
	character2 = char2;
	character3 = char3;

	q = gcnew CommandQueue<String^>();

	//	Set the path
	fileWatcher1->Path = "C:\\Users\\Public\\Daybreak Game Company\\Installed Games\\EverQuest\\Logs";
	//fileWatcher2->Path = "C:\\Users\\Public\\Daybreak Game Company\\Installed Games\\EverQuest\\Logs";
	//fileWatcher3->Path = "C:\\Users\\Public\\Daybreak Game Company\\Installed Games\\EverQuest\\Logs";

	//	Add event handlers
	fileWatcher1->Changed += gcnew FileSystemEventHandler(Watcher::OnChange1);
	fileWatcher1->EnableRaisingEvents = false;

	//fileWatcher2->Changed += gcnew FileSystemEventHandler(Watcher::OnChange2);
	//fileWatcher2->EnableRaisingEvents = false;

	//fileWatcher3->Changed += gcnew FileSystemEventHandler(Watcher::OnChange3);
	//fileWatcher3->EnableRaisingEvents = false;
}

void Watcher::ToggleEvents()
{
	if (fileWatcher1->EnableRaisingEvents)
	{
		fileWatcher1->EnableRaisingEvents = false;
		//fileWatcher2->EnableRaisingEvents = false;
		//fileWatcher3->EnableRaisingEvents = false;
	}
	else
	{
		fileWatcher1->EnableRaisingEvents = true;
		//fileWatcher2->EnableRaisingEvents = true;
		//fileWatcher3->EnableRaisingEvents = true;
	}
}

FileSystemWatcher ^ Watcher::getFileWatcher1()
{
	return fileWatcher1;
}

//FileSystemWatcher ^ Watcher::getFileWatcher2()
//{
//	return fileWatcher2;
//}

//FileSystemWatcher ^ Watcher::getFileWatcher3()
//{
//	return fileWatcher3;
//}

void Watcher::ScanLines(Character^ character)
{
	System::String^ newLine;
	StreamReader^ sr;
	try
	{
		sr = File::OpenText(character->getLogFile());
		bool foundLastLineReadInLog = false;
		while (!sr->EndOfStream)
		{
			newLine = sr->ReadLine();

			//	Check if last line read by character is empty
			if (character->getLastLineRead() == "")
			{
				foundLastLineReadInLog = true;
				character->setLastLineRead(newLine);

				//	PrintNewLine is deprecated.  Clean this up/remove
				character->PrintNewLine();
			}

			//	If it is non empty, then compare the currently read line to the last line read by the character
			else
			{
				if (newLine == character->getLastLineRead())
					foundLastLineReadInLog = true;
				if (foundLastLineReadInLog && (newLine != character->getLastLineRead()))
				{
					character->setLastLineRead(newLine);
					character->PrintNewLine();
					
					//	Add this line to the CommandQueue 'q'
					q->TryEnqueue(newLine,10);

				}
			}
		}

		//	Close the stream reader
		sr->Close();

		//	Process the Queue
		while (q->Count()>0)
		{
			newLine = q->Dequeue();
			character->ProcessCommands(newLine);
			Console::WriteLine(System::String::Concat("PROCESSED -------->: ", newLine));
		}
	}
	catch (Exception^ ioex)
	{
		throw gcnew Exception("\nAn error occured when opening the log file.  It is likely you have an incorrect character or server name.  The first letter of a character names must be capitalized.  Server names are NOT capitalized (all letters are lower case).", ioex);
	}
}

//	Scan each line in the batch of lines added to the eqlog.txt file
//	Compare each line to the last line read by the character object
//	If a line is newer than the last line read by the character object, then launch a character state updater thread
//	Repeat until end of stream

void Watcher::OnChange1(Object^ source, FileSystemEventArgs^ e)
{
	//FileSystemWatcher^ filewatcher = fileWatcher1;
	Character^ character = character1;
	ScanLines(character);
}

//void Watcher::OnChange2(Object ^ source, FileSystemEventArgs ^ e)
//{
//	FileSystemWatcher^ filewatcher = fileWatcher2;
//	Character^ character = character2;
//	StreamReader^ sr = sr2;
//
//	ScanLines(filewatcher, character, sr);
//}

//void Watcher::OnChange3(Object ^ source, FileSystemEventArgs ^ e)
//{
//	FileSystemWatcher^ filewatcher = fileWatcher3;
//	Character^ character = character3;
//	StreamReader^ sr = sr3;
//
//	ScanLines(filewatcher, character, sr);
//}