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
			WatcherThreadWithState^ wtws = gcnew WatcherThreadWithState(character, currentLine);
			Thread^ logThread = gcnew Thread(gcnew ThreadStart(wtws, &WatcherThreadWithState::ThreadProc));
			logThread->Start();
			//character->LogFlags(currentLine);
		}

		//	Otherwise, the lastLineRead is nonempty.  Set a flag and only send lines encountered after that
		else
		{
			if (currentLine == character->getLastLineRead())
				foundLastLineReadInLog = true;
			if (foundLastLineReadInLog && (currentLine != character->getLastLineRead()))
			{
				WatcherThreadWithState^ wtws = gcnew WatcherThreadWithState(character, currentLine);
				Thread^ logThread = gcnew Thread(gcnew ThreadStart(wtws, &WatcherThreadWithState::ThreadProc));
				logThread->Start();
				//character->LogFlags(currentLine);
			}
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

WatcherThreadWithState::WatcherThreadWithState(Character^ val1, String^ val2)
{
	threadCharacter = val1;
	threadLine = val2;
}

void WatcherThreadWithState::ThreadProc()
{

	//	Update character member variables based on new line activity

	//	Experience
	if (threadLine->Contains("You gain experience"))
		threadCharacter->setExp(true);

	//	Buffs
	if (threadLine->Contains("You do not sense any enchantments"))
		threadCharacter->setShielding(false);
	if (threadLine->Contains("Minor Shielding"))
		threadCharacter->setShielding(true);
	if (threadLine->Contains("You feel armored"))
		threadCharacter->setShielding(true);
	if (threadLine->Contains("Your shielding fades away"))
		threadCharacter->setShielding(false);

	//	Target
	if (threadLine->Contains("looks kind of risky") ||
		threadLine->Contains("looks like an even fight"))
	{
		threadCharacter->setValidTarget(true);
		Console::WriteLine("Setting valid target to TRUE");
	}

	if (threadLine->Contains("must first select a target for this spell"))
	{
		threadCharacter->setValidTarget(false);
		Console::WriteLine("Invalid target:  NO TARGET");
	}

	if (threadLine->Contains("no longer have a target"))
	{
		threadCharacter->setValidTarget(false);
		Console::WriteLine("Invalid target:  NO TARGET... pressed ESC");
	}

	if (threadLine->Contains("can't drain yourself"))
	{
		threadCharacter->setValidTarget(false);
		Console::WriteLine("Invalid target:  attempting to lifespike self");
	}

	if (threadLine->Contains("target is out of range"))
	{
		threadCharacter->setValidTarget(false);
		Console::WriteLine("Invalid target:  out of range");
	}

	if (threadLine->Contains("cannot see your target"))
	{
		threadCharacter->setValidTarget(false);
		Console::WriteLine("Invalid target:  can't see");
	}

	if (threadLine->Contains("a skunk"))
	{
		threadCharacter->setValidTarget(false);
		Console::WriteLine("Invalid target:  skunk");
	}

	if (threadLine->Contains("this corpse will decay in"))
	{
		threadCharacter->setValidTarget(false);
		Console::WriteLine("Invalid target:  corpse");
	}


		

	//	Pet Alive or Dead or In Combat
	if (threadLine->Contains("Changing position") ||
		threadLine->Contains("Targeting your pet") ||
		threadLine->Contains("cannot have more than one pet at a time"))
		threadCharacter->setPetAlive(true);
	if (threadLine->Contains("don't have a pet to command"))
		threadCharacter->setPetAlive(false);
	if (threadLine->Contains("tells you, 'Attacking") && threadLine->Contains("Master"))
		threadCharacter->setPetInCombat(true);

	//	Casting spells
	if (threadLine->Contains("Your spell fizzles"))
	{
		threadCharacter->setFizzled(true);
		threadCharacter->setCastingSpell(false);
	}
	if (threadLine->Contains("You begin casting") ||
		threadLine->Contains("Yuse that command while casting") ||
		threadLine->Contains("You haven't recovered yet") ||
		threadLine->Contains("Your spell is interrupted"))
	{
		threadCharacter->setCastingSpell(true);
		threadCharacter->setFizzled(false);
	}

	//	Combat
	if (threadLine->Contains("YOU for") || threadLine->Contains("YOU, but misses"))
		threadCharacter->setBeingHit(true);

}
