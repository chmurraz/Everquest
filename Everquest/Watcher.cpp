#include "stdafx.h"
#include "Watcher.h"


Watcher::Watcher()
{
	watcher = gcnew FileSystemWatcher;
	//newLine = "";

	//	Set the path
	watcher->Path = "C:\\Users\\Public\\Daybreak Game Company\\Installed Games\\EverQuest\\Logs";

	//	Filter to only watch text files
	watcher->Filter = "*.txt";
}

void Watcher::OnChange(Object ^, FileSystemEventArgs ^ e)
{
	/*
	sr = File::OpenText("C:\\Users\\Public\\Daybreak Game Company\\Installed Games\\EverQuest\\Logs\\eqlog_Xahul_phinigel.txt");
	newLine = sr->ReadLine();
	while ((newLine = sr->ReadLine()) != nullptr)
	{
		newLine = sr->ReadLine();
	}
	//System::Windows::Forms::MessageBox(newLine);
	sr->Close();
	*/

	std::string line;
	std::ifstream inFile;
	inFile.open("C:\\Users\\Public\\Daybreak Game Company\\Installed Games\\EverQuest\\Logs\\eqlog_Xahul_phinigel.txt");


	//	Scan through the log and extract the last lines.  Send them through log flag filter routine

	//	Extract the last line read by the character object and convert to System::String^
	System::String^ currentLine;
	bool foundLastLineReadInLog = false;
	while (inFile >> std::ws && std::getline(inFile, line))
	{
		//	Convert the line of the log being read to a System::String^
		currentLine = gcnew String(line.c_str());

		//	If the lastLineRead is empty, make this line the lastLineRead and send it to Flags routine
		if (character->getLastLineRead() == "")
		{
			character->setLastLineRead(currentLine);
			character->LogFlags(currentLine);
		}

		//	Otherwise, the lastLineRead is nonempty.  Set a flag and only send lines encountered after that
		else
		{
			if (currentLine == character->getLastLineRead())
				foundLastLineReadInLog = true;
			if (foundLastLineReadInLog && (currentLine != character->getLastLineRead()))
				character->LogFlags(currentLine);
		}

	};
	character->setLastLineRead(currentLine);
	inFile.close();
}

void Watcher::ScanLog()
{
	//	Add event handlers
	watcher->Changed += gcnew FileSystemEventHandler(Watcher::OnChange);
	watcher->EnableRaisingEvents = true;
}

void Watcher::setCharacter(Character ^ val)
{
	character = val;
}
