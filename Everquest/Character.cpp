#include "stdafx.h"
#include "Character.h"

Character::Character()
{
	// Change Visual Studio Properties > General > Character Set to "Use Multi-Byte Character Set" so the arguments in FindWindow() work okay
	EQHandle = FindWindowA(NULL, "Everquest");

	// Verify that Everquest is a running process.
	if (EQHandle == NULL)
	{
		MessageBox::Show("Everquest is not running.");
		return;
	}

	ip = new INPUT;
	keys = "";
	rest = 0;
	fizzled = false;
	beingHit = false;
	lowMana = false;
	petInCombat = false;
	experience = false;
	validTarget = false;
	petAlive = false;
	typeSpeed = 30;
	routineStop = false;
	petName = "";
	targetingCorpse = false;
	lastLineRead = "";

	//	Debugging member variables
	DEBUGMODE = false;
	talkFlag = false;
	shielding =false;
}

Character::~Character()
{
	delete ip;
	ip = NULL;
}

void Character::PressKeys(INPUT* ip, System::String^ keys, DWORD rest)
{
	if (DEBUGMODE)
	{
		MoveEQToFront();
		Sleep(2000);
	}

	for (unsigned i = 0; i < keys->Length; i++)
	{
		ip->type = INPUT_KEYBOARD;
		ip->ki.dwExtraInfo = GetMessageExtraInfo();
		//	would use char ch = keys->at(i); for a C++ std:string
		char ch = keys[i];
		ip->ki.wScan = static_cast<WORD>(MapVirtualKeyEx(VkKeyScanA(ch), MAPVK_VK_TO_VSC, GetKeyboardLayout(0)));
		ip->ki.time = 0;

		//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

		ip->ki.dwFlags = 0;	//	0 for keypress
		SendInput(1, ip, sizeof(INPUT));
		ip->ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, ip, sizeof(INPUT));
		// Use this sleep line to debug each character one at a time in EQ
		Sleep(typeSpeed);
	}
	Sleep(rest);
}

bool Character::SearchLog(std::string text)
{
	bool boolValue = false;

	std::ifstream inFile;
	inFile.open("C:\\Users\\Public\\Daybreak Game Company\\Installed Games\\EverQuest\\Logs\\eqlog_Xahul_phinigel.txt");

	std::size_t found;
	std::string line;
	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			getline(inFile, line);
			if ((found = line.find(text, 0)) != std::string::npos)
			{
				boolValue = true;
			}
		}
		inFile.close();
	}

	return boolValue;
}

void Character::PetAssist()
{
	PressKeys(ip, "/pet assist\r", typeSpeed);
}

void Character::InspectBuffs()
{
	Console::WriteLine("Inspecting buffs");
	PressF1();
	PressKeys(ip,"/inspectbuffs\r",typeSpeed);
	Sleep(3000);
}

void Character::TargetSelf()
{
	PressF1();
}

void Character::setPetInCombat(bool val)
{
	petInCombat=val;
}

bool Character::getPetInCombat()
{
	return petInCombat;
}

bool Character::LowMana()
{
	lowMana = SearchLog("Insufficient Mana to cast this spell!");
	if (lowMana)
		this->Talk(true, "my mana is low");
	return lowMana;
}

void Character::EraseLog()
{
	remove("C:\\Users\\Public\\Daybreak Game Company\\Installed Games\\EverQuest\\Logs\\eqlog_Xahul_phinigel.txt");
	this->Talk(true, "erasing log");
}

bool Character::InRange()
{
	return !(SearchLog("Your target is out of range, get closer!"));
}

bool Character::BeingHit()
{
	beingHit = SearchLog("YOU for") || SearchLog("YOU, but misses!");
	if (beingHit)
	{
		this->Talk(true, "am being hit");
		PressESC();
	}
		
	else
		this->Talk(true, "am not being hit");
	return beingHit;
}

bool Character::Died()
{
	return SearchLog("You have been slain by");
}

void Character::FindValidTarget()
{
	Console::WriteLine("Finding a valid target");
	validTarget = false;
	std::string target;
	do
	{
		this->Talk(true, "finding a valid target");
		MoveEQToFront();
		PressTab();
		VerifyTarget();
		Sleep(1000);

	} while (!validTarget);
}

void Character::VerifyTarget()
{
	if (talkFlag)
	{
		PressKeys(ip, "/gu verifying ", typeSpeed);
		HoldShift();
		PressKeys(ip, "5", typeSpeed);
		ReleaseShift();
		PressKeys(ip, "t is valid\r", typeSpeed);
	}

	this->Talk(true, "verifying");
	Consider();

	this->Talk(validTarget, "my target is valid");
	this->Talk(!validTarget, "invalid target");
}

/*
void Character::OnLogChange(Object ^, FileSystemEventArgs ^ e)
{
	//	Get the last line of the log
	//	Can't just use "getLastLine()" because OnLogChange is static

	//std::string line;
	//std::ifstream inFile;
	//inFile.open("C:\\Users\\Public\\Daybreak Game Company\\Installed Games\\EverQuest\\Logs\\eqlog_Xahul_phinigel.txt");

	//while (inFile >> std::ws && std::getline(inFile, line))
	//{
	//};
	//System::String^ newLine = gcnew String(line.c_str());
	//inFile.close();

	//System::Windows::Forms::MessageBox(newLine);
}
*/

void Character::LogFlags(System::String^ newLine)
{
	//	REMOVE THIS FUNCTION FROM CHARACTER.H/CPP IF IT IS SUCESSFULLY INCLUDED IN WATCHER THREAD CLASS

	//	Update character member variables based on new line activity

	//	Experience
	if (newLine->Contains("You gain experience"))
		experience = true;

	//	Buffs
	if (newLine->Contains("You do not sense any enchantments"))
		shielding = false;
	if (newLine->Contains("Minor Shielding"))
		shielding = true;
	if (newLine->Contains("You feel armored"))
		shielding = true;
	if (newLine->Contains("Your shielding fades away"))
		shielding = false;

	//	Target
	if (newLine->Contains("looks kind of risky") ||
		newLine->Contains("looks like an even fight"))
	{
		targetingCorpse = false;
		validTarget = true;
	}
	if (newLine->Contains("no longer have a target") ||
		newLine->Contains("must first select a target for this spell") ||
		newLine->Contains("can't drain yourself") ||
		(petAlive && newLine->Contains(petName)) ||
		newLine->Contains("target is out of range") ||
		newLine->Contains("cannot see your target") ||
		newLine->Contains("a skunk") ||
		newLine->Contains("This corpse will decay in"))
		validTarget = false;

	//	Pet Alive or Dead or In Combat
	if (newLine->Contains("Changing position") ||
		newLine->Contains("Targeting your pet") ||
		newLine->Contains("cannot have more than one pet at a time"))
		petAlive = true;
	if (newLine->Contains("don't have a pet to command"))
		petAlive = false;
	if (newLine->Contains("tells you, 'Attacking") && newLine->Contains("Master"))
		petInCombat = true;

	//	Casting spells
	if (newLine->Contains("Your spell fizzles"))
	{
		fizzled = true;
		castingSpell = false;
	}
	if (newLine->Contains("You begin casting") ||
		newLine->Contains("Yuse that command while casting") ||
		newLine->Contains("You haven't recovered yet") ||
		newLine->Contains("Your spell is interrupted"))
	{
		castingSpell = true;
		fizzled = false;
	}

	//	Combat
	if (newLine->Contains("YOU for") || newLine->Contains("YOU, but misses"))
		beingHit = true;
}

void Character::NecroRoutine()
{
	MoveEQToFront();
	EraseLog();
	LogOn();

	for (int i = 0; i < 500; i++)
	{
		Console::WriteLine("Current loop iteration is " + i);
		MoveEQToFront();
		experience = false;
		beingHit = false;
		petInCombat = false;
		MoveEQToFront();

		HideCorpses();
		PressESC();
		MoveEQToFront();
		TargetPet();
		MoveEQToFront();
		PetSit();
		MoveEQToFront();
		InspectBuffs();
		if (!shielding)
		{
			Shielding();
			Sleep(4000);
			Sit();
		}
		if (!petAlive)
			SummonPet();
		setPetName();
		FindValidTarget();

		// Main combat loop
		do
		{
			do
			{
				MoveEQToFront();
				//Consider();
				MoveEQToFront();
				PetAttack();
				LifeSpike();
				if (!validTarget)
				{
					MoveEQToFront();
					PetBackOff();
				}
				AssistPet();
				VerifyTarget();
			} while (!experience && validTarget && !beingHit);

			if (beingHit)
			{
				// Press SHIFT + TAB to target nearest NPC
				HoldShift();
				PressTab();
				ReleaseShift();
				PetAttack();
			}

			if (experience)
			{
				PressESC();
				PetBackOff();
				beingHit = false;
				petInCombat = false;
			}
		} while (beingHit);

		MoveEQToFront();
		Sleep(1000);
		Sit();
		Sleep(3000);
		PetSit();
		Sleep(1000);
		PressESC();
		if (lowMana & !beingHit)
		{
			Sleep(35000);
		}

	}
	routineStop = true;
	Talk(true, "routine finished");
}

System::String ^ Character::getLastLine()
{
	std::string line;
	std::ifstream inFile;
	inFile.open("C:\\Users\\Public\\Daybreak Game Company\\Installed Games\\EverQuest\\Logs\\eqlog_Xahul_phinigel.txt");

	while (inFile >> std::ws && std::getline(inFile, line))
	{
	};
	System::String^ line2 = gcnew String(line.c_str());
	inFile.close();
	return line2;
}

void Character::setLastLineRead(System::String ^ val)
{
	lastLineRead = val;
}

System::String ^ Character::getLastLineRead()
{
	return lastLineRead;
}

void Character::setRoutineStop(bool val)
{
	routineStop = val;
}

bool Character::getRoutineStop()
{
	return routineStop;;
}

void Character::setValidTarget(bool val)
{
	validTarget = val;
}

void Character::setPetAlive(bool val)
{
	petAlive = val;
}

bool Character::getPetAlive()
{
	return petAlive;
}

void Character::setCastingSpell(bool val)
{
	castingSpell = val;
}

bool Character::getCastingSpell()
{
	return castingSpell;
}

void Character::Consider()
{
	this->Talk(true, "conning target");
	PressKeys(ip, "/con\r", 50);
}

void Character::MoveEQToFront()
{
	SetForegroundWindow(EQHandle);
	Sleep(2000);
}

void Character::LogOn()
{
	PressKeys(ip, "/log on\r", 1000);
	this->Talk(true,"turning log on");
}

void Character::HideCorpses()
{
	Console::WriteLine("Hiding corpses");
	this->Talk(true, "hiding corpses");
	PressKeys(ip, "/hidecorpse all\r", 1000);
}

void Character::PressESC()
{
	this->Talk(true, "releasing target");
	ip->type = INPUT_KEYBOARD;
	ip->ki.dwExtraInfo = GetMessageExtraInfo();
	ip->ki.wScan = static_cast<WORD>(MapVirtualKey(VK_ESCAPE, MAPVK_VK_TO_VSC));
	ip->ki.time = 0;

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	ip->ki.dwFlags = 0;	//	0 for keypress
	SendInput(1, ip, sizeof(INPUT));
	ip->ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, ip, sizeof(INPUT));
}

void Character::PressTab()
{
	ip->type = INPUT_KEYBOARD;
	ip->ki.dwExtraInfo = GetMessageExtraInfo();
	ip->ki.wScan = static_cast<WORD>(MapVirtualKey(VK_TAB, MAPVK_VK_TO_VSC));
	ip->ki.time = 0;

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	ip->ki.dwFlags = 0;	//	0 for keypress
	SendInput(1, ip, sizeof(INPUT));
	ip->ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, ip, sizeof(INPUT));
}

void Character::PressF1()
{
	ip->type = INPUT_KEYBOARD;
	ip->ki.dwExtraInfo = GetMessageExtraInfo();
	ip->ki.wScan = static_cast<WORD>(MapVirtualKey(VK_F1, MAPVK_VK_TO_VSC));
	ip->ki.time = 0;

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	ip->ki.dwFlags = 0;	//	0 for keypress
	SendInput(1, ip, sizeof(INPUT));
	ip->ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, ip, sizeof(INPUT));
}

void Character::HoldShift()
{
	ip->type = INPUT_KEYBOARD;
	ip->ki.dwExtraInfo = GetMessageExtraInfo();
	ip->ki.wScan = static_cast<WORD>(MapVirtualKey(VK_SHIFT, MAPVK_VK_TO_VSC));
	ip->ki.time = 0;

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	ip->ki.dwFlags = 0;	//	0 for keypress
	SendInput(1, ip, sizeof(INPUT));
}

void Character::ReleaseShift()
{
	ip->type = INPUT_KEYBOARD;
	ip->ki.dwExtraInfo = GetMessageExtraInfo();
	ip->ki.wScan = static_cast<WORD>(MapVirtualKey(VK_SHIFT, MAPVK_VK_TO_VSC));
	ip->ki.time = 0;

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

	ip->ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, ip, sizeof(INPUT));
}

void Character::SummonPet()
{
	do
	{
		PressKeys(ip, "/cast 3\r", 500);
	} while (!castingSpell);

	Sleep(10000);

	Sit();
}

bool Character::SpellFizzle()
{
	fizzled = SearchLog("Your spell fizzles!");
	return fizzled;
}

void Character::PetSit()
{
	Console::WriteLine("Telling pet to sit");
	PressKeys(ip, "/pet sit\r",250);
}

void Character::Sit()
{
	Console::WriteLine("Sitting");
	if (!beingHit)
		PressKeys(ip, "/sit\r", 250);
}

void Character::PetAttack()
{
	Console::WriteLine("Pet attacking");
	PressKeys(ip, "/pet attack\r", 0);
}

void Character::AssistPet()
{
	Console::WriteLine("Assisting pet");
	PressKeys(ip, "/assist " + getPetName() + " \r", typeSpeed);
}

void Character::Shielding()
{
	Console::WriteLine("Casting shielding");
	do
	{
		PressKeys(ip, "/cast 1\r", 500);
	} while (fizzled);
}

void Character::LifeSpike()
{
	Console::WriteLine("Casting Lifespike");
	do
	{
		PressKeys(ip, "/cast 2\r", 500);
	} while (fizzled);
	if (!beingHit)
		Sleep(2000);
}

void Character::Snare()
{
}

bool Character::CannotSeeTarget()
{
	return SearchLog("You cannot see your target");
}

bool Character::TargetOutOfRange()
{
	return SearchLog("Your target is out of range, get closer!");
}

void Character::setFizzled(bool val)
{
	fizzled = val;
}

bool Character::getFizzled()
{
	return fizzled;
}

void Character::setBeingHit(bool val)
{
	beingHit = val;
}

bool Character::getBeingHit()
{
	return beingHit;
}

void Character::setLowMana(bool val)
{
	lowMana = val;
}

bool Character::getLowMana()
{
	return lowMana;
}

void Character::setShielding(bool val)
{
	shielding = val;
}

bool Character::getShielding()
{
	return shielding;
}

System::String ^ Character::getPetName()
{
	return petName;
}

void Character::PetBackOff()
{
	this->Talk(true, "backing pet off");
	PressKeys(ip, "/pet back off\r", 3000);
}

void Character::setPetName()
{
	Console::WriteLine("Setting pet name");
	//	Target pet and say his name to guildchat
	TargetPet();
	//PressKeys(ip, "/hail\r", typeSpeed);

	PressKeys(ip, "/gu ", typeSpeed);
	HoldShift();
	PressKeys(ip, "5", typeSpeed);
	ReleaseShift();
	PressKeys(ip, "t\r", typeSpeed);

	//	While the newLine doesn't contain "You say", loop
	do
	{
		petName = this->getLastLine();
	} while (!(petName->Contains("You say")));

	//	Trim the last single quote character and everything up to and including the first one
	//int nameStart = petName->IndexOf("Hail, ");
	int nameStart = petName->IndexOf("guild, ");
	int nameEnd = petName->LastIndexOf("'");
	petName = petName->Remove(nameEnd, 1);
	petName = petName->Substring(nameStart + 8);
	if (petName == "Target")
	{
		petAlive = false;
		petName = "";
	}
	PressESC();
}

void Character::TargetPet()
{
	Console::WriteLine("Targeting Pet");
	PressKeys(ip, "/pet target\r", 500);
}

bool Character::getExp()
{
	return experience;
}

void Character::setExp(bool val)
{
	experience = val;
}

bool Character::getValidTarget()
{
	return validTarget;
}

void Character::Talk(bool criteria, System::String^ text)
{
	if (criteria && talkFlag)
	{
		PressKeys(ip, "/gu "+ text +"\r", typeSpeed);
	}	
}