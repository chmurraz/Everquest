#include "stdafx.h"
#include "Character.h"

Character::Character()
{
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

/*	DEPRECATED... MAY REMOVE THIS LATER
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
*/

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

void Character::FindValidTarget()
{
	Console::WriteLine("Finding a valid target...");
	Console::WriteLine("Setting Target invalid");
	validTarget = false;
	do
	{
		PressTab();
		Consider();
		Sleep(1000);

	} while (!validTarget);
}

void Character::NecroStartUp()
{
	LogOn();
	experience = false;
	beingHit = false;
	petInCombat = false;
	HideCorpses();
	PressESC();
	TargetPet();
	PetSit();
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
}

void Character::NecroNuke()
{
	//	Loop while current target is alive
	do
	{
		PetAttack();
		LifeSpike();
		if (!validTarget)
		{
			PetBackOff();
		}
		AssistPet();
		Consider();
	} while (!experience && validTarget && !beingHit);
}

void Character::NecroBeingHit()
{
	// Press SHIFT + TAB to target nearest NPC
	HoldShift();
	PressTab();
	ReleaseShift();
	PetAttack();
}

void Character::NecroGotExp()
{
	PressESC();
	PetBackOff();
	beingHit = false;
	petInCombat = false;
}

void Character::NecroCleanUp()
{
	Sleep(1000);
	Sit();
	Sleep(3000);
	PetSit();
	Sleep(1000);
	PressESC();
	if (lowMana & !beingHit)
	{
		NecroMedBreak();
	}

	//	Reset experience or the routine will just fall through the main combat loop at next execution
	experience = false;
	routineStop = true;
}

void Character::NecroMedBreak()
{
	Sit();
	int i = 60;
	do
	{
		Console::WriteLine("Med break with " + i + " seconds remaining");
		Sleep(1000);
		i--;
	} while (!beingHit);
	lowMana = false;
}

void Character::ClericHealSkillUp()
{
	PressKeys(ip, "/cast 2\r", 1000);
}


void Character::NecroMain()
{

	FindValidTarget();

	// Main combat loop ... do this as long as the character is being hit
	do
	{
		NecroNuke();
		if (beingHit)
			NecroBeingHit();

		if (experience)
			NecroGotExp();

	} while (beingHit);

	NecroCleanUp();
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
	PressKeys(ip, "/con\r", 50);
}

void Character::LogOn()
{
	PressKeys(ip, "/log on\r", 1000);
}

void Character::HideCorpses()
{
	Console::WriteLine("Hiding corpses");
	PressKeys(ip, "/hidecorpse all\r", 1000);
}

void Character::PressESC()
{
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

void Character::PetSit()
{
	Console::WriteLine("Telling pet to sit");
	PressKeys(ip, "/pet sit\r",250);
}

void Character::Sit()
{
	Console::WriteLine("Sitting");
	PressKeys(ip, "/stand\r", 250);
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