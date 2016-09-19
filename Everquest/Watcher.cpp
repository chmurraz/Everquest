#include "stdafx.h"
#include "Watcher.h"
#include "EverquestForm.h"


Watcher::Watcher(Character^ val1, System::String^ cName, System::String^ sName)
{
	fileWatcher = gcnew FileSystemWatcher;

	//	Set the path
	fileWatcher->Path = "C:\\Users\\Public\\Daybreak Game Company\\Installed Games\\EverQuest\\Logs";

	//	Filter to only watch text files
	fileWatcher->Filter = "*.txt";

	//	Add event handlers
	fileWatcher->Changed += gcnew FileSystemEventHandler(Watcher::OnChange);
	fileWatcher->EnableRaisingEvents = true;

	character = val1;
	charName = cName;
	serverName = sName;
	fileName = "C:\\Users\\Public\\Daybreak Game Company\\Installed Games\\EverQuest\\Logs\\eqlog_";
	fileName += charName + "_" + serverName + ".txt";

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
				LaunchCharStateUpdateThread(newLine);
			}

			//	If it is non empty, then compare the currently read line in the log to the last line read by the character
			else
			{
				if (newLine == character->getLastLineRead())
					foundLastLineReadInLog = true;
				if (foundLastLineReadInLog && (newLine != character->getLastLineRead()))
					LaunchCharStateUpdateThread(newLine);
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

void Watcher::LaunchCharStateUpdateThread(System::String ^ newLine)
{
	character->setLastLineRead(newLine);
	CharacterStateUpdater^ charState = gcnew CharacterStateUpdater(character, newLine);
	ThreadStart^ threadDelegate = gcnew ThreadStart(charState, &CharacterStateUpdater::ThreadUpdate);
	Thread^ logThread = gcnew Thread(threadDelegate);
	logThread->Start();
}

void Watcher::setCharacter(Character ^ val)
{
	character = val;
}

Character ^ Watcher::getCharacter()
{
	return character;
}

CharacterStateUpdater::CharacterStateUpdater(Character ^ val1, String ^ val2)
{
	character = val1;
	newLine = val2;
}

void CharacterStateUpdater::ThreadUpdate()
{
	//	Update character member variables based on new line activity

	//	Experience
	if (newLine->Contains("You gain experience"))
	{
		character->setExp(true);
		Console::WriteLine("Experience gained");
	}

	//	Buffs
	if (newLine->Contains("You do not sense any enchantments"))
	{
		character->setShielding(false);
		Console::WriteLine("No buffs");
	}	
	if (newLine->Contains("Minor Shielding"))
	{
		character->setShielding(true);
		Console::WriteLine("Minor Shielding buff found");
	}
	if (newLine->Contains("You feel armored"))
	{
		character->setShielding(true);
		Console::WriteLine("Minor Shielding sucessfully cast");
	}
	if (newLine->Contains("Your shielding fades away"))
	{
		character->setShielding(false);
		Console::WriteLine("Shielding buff fades away");
	}

	//	Target
	if (newLine->Contains("looks kind of risky"))
	{
		character->setValidTarget(true);
		Console::WriteLine("Valid target... blue");
	}

	if (newLine->Contains("looks like an even fight"))
	{
		character->setValidTarget(true);
		Console::WriteLine("Valid target... even con");
	}

	if (newLine->Contains("must first select a target for this spell"))
	{
		character->setValidTarget(false);
		Console::WriteLine("Invalid target:  NO TARGET");
	}

	if (newLine->Contains("no longer have a target"))
	{
		character->setValidTarget(false);
		Console::WriteLine("Invalid target:  NO TARGET... pressed ESC");
	}

	if (newLine->Contains("can't drain yourself"))
	{
		character->setValidTarget(false);
		Console::WriteLine("Invalid target:  attempting to lifespike self");
	}

	if (newLine->Contains("target is out of range"))
	{
		character->setValidTarget(false);
		Console::WriteLine("Invalid target:  out of range");
	}

	if (newLine->Contains("cannot see your target"))
	{
		character->setValidTarget(false);
		Console::WriteLine("Invalid target:  can't see");
	}

	if (newLine->Contains("a skunk"))
	{
		character->setValidTarget(false);
		Console::WriteLine("Invalid target:  skunk");
	}

	if (newLine->Contains("this corpse will decay in"))
	{
		character->setValidTarget(false);
		Console::WriteLine("Invalid target:  corpse");
	}

	//	Pet Alive or Dead or In Combat
	if (newLine->Contains("Changing position") ||
		newLine->Contains("Targeting your pet") ||
		newLine->Contains("cannot have more than one pet at a time"))
	{
		character->setPetAlive(true);
		Console::WriteLine("Pet is alive");
	}
	if (newLine->Contains("don't have a pet to command"))
	{
		character->setPetAlive(false);
		Console::WriteLine("No pet found");
	}
	if (newLine->Contains("tells you, 'Attacking") && newLine->Contains("Master"))
	{
		character->setPetInCombat(true);
		Console::WriteLine("Pet is in combat");
	}

	//	Casting spells
	if (newLine->Contains("Your spell fizzles"))
	{
		character->setFizzled(true);
		character->setCastingSpell(false);
		Console::WriteLine("Spell fizzled");
	}
	if (newLine->Contains("You begin casting") ||
		newLine->Contains("Yuse that command while casting") ||
		newLine->Contains("You haven't recovered yet") ||
		newLine->Contains("Your spell is interrupted"))
	{
		character->setCastingSpell(true);
		character->setFizzled(false);
		Console::WriteLine("Spell sucessful");
	}

	//	Combat
	if (newLine->Contains("YOU for") || newLine->Contains("YOU, but misses"))
	{
		character->setBeingHit(true);
		Console::WriteLine("Character being hit");
	}

	//	Low Mana
	if (newLine->Contains("Insufficient Mana to cast this spell!"))
	{
		character->setLowMana(true);
		Console::WriteLine("Low mana");
	}		
}