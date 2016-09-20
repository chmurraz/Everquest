#include "stdafx.h"
#include "Watcher.h"
#include "EverquestForm.h"


Watcher::Watcher(Character^ character)
{
	fileWatcher = gcnew FileSystemWatcher;

	//	Set the path
	fileWatcher->Path = "C:\\Users\\Public\\Daybreak Game Company\\Installed Games\\EverQuest\\Logs";

	//	Filter to only watch text files
	fileWatcher->Filter = "*.txt";

	//	Add event handlers
	fileWatcher->Changed += gcnew FileSystemEventHandler(Watcher::OnChange);
	fileWatcher->EnableRaisingEvents = true;

	fileName = "C:\\Users\\Public\\Daybreak Game Company\\Installed Games\\EverQuest\\Logs\\eqlog_";
	fileName += character->getName() + "_" + character->getServerName() + ".txt";

	//	Erase the old log files
	File::Delete(fileName);
}

void Watcher::OnChange(Object ^, FileSystemEventArgs ^ e)
{
	//	Scan each line in the batch of lines added to the eqlog.txt file
	//	Compare each line to the last line read by the character object
	//	If a line is newer than the last line read by the character object, then launch a character state updater thread
	//	Repeat until end of stream

	try
	{
		sr = File::OpenText(fileName);
		bool foundLastLineReadInLog = false;
		while (!sr->EndOfStream)
		{
			newLine = sr->ReadLine();

			//	Check if last line read by character object is empty
			if (character->getLastLineRead() == "")
			{
				foundLastLineReadInLog = true;
				character->setLastLineRead(newLine);
				character->CharacterActions();
			}

			//	If it is non empty, then compare the currently read line in the log to the last line read by the character
			else
			{
				if (newLine == character->getLastLineRead())
					foundLastLineReadInLog = true;
				if (foundLastLineReadInLog && (newLine != character->getLastLineRead()))
				{
					character->setLastLineRead(newLine);
					character->CharacterActions();
				}
			}
		}

		//	Close the stream reader
		sr->Close();
	}
	catch (Exception^ ioex)
	{
		throw gcnew Exception("\nAn error occured when opening the log file.  It is likely you have an incorrect character or server name.  The first letter of a character names must be capitalized.  Server names are NOT capitalized (all letters are lower case).", ioex);
	}

}