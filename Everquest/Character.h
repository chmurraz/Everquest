#pragma once

#include <windows.h>
#include "winuser.h"
#include <iostream>
#include <fstream>
#include <string>
#using <System.dll>
#using <System.Windows.Forms.dll>
using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Security::Permissions;

ref class Character
{
private:
	INPUT* ip;
	//FileSystemWatcher^ watcher;
	System::String^ keys;
	DWORD rest;
	bool fizzled;
	bool beingHit;
	bool lowMana;
	bool petInCombat;
	bool experience;
	bool talkFlag;
	bool validTarget;
	bool petAlive;
	bool castingSpell;
	DWORD typeSpeed;
	bool routineStop;
	bool DEBUGMODE;
	//	Buffs
	bool shielding;
	bool targetingCorpse;

	System::String^ petName;
	System::String^ lastLineRead;
	

public:
	Character();
	~Character();
	
	//bool SearchLog(std::string text);			//	deprecated, may remove eventually... commenting out for now

	//	Keyboard Sim
	void PressKeys(INPUT* ip, System::String^ keys, DWORD rest);
	void HoldShift();
	void ReleaseShift();
	void PressESC();
	void PressTab();
	void PressF1();

	//	Cast Spells
	void Shielding();
	void LifeSpike();
	void Snare();

	// Everquest Functions
	void PetAssist();
	void InspectBuffs();
	void TargetSelf();

	//	Mutators and Accessors
	void setPetInCombat(bool val);
	bool getPetInCombat();
	void setExp(bool val);
	bool getExp();
	bool getValidTarget();
	void setValidTarget(bool val);
	void setRoutineStop(bool val);
	bool getRoutineStop();
	void setPetAlive(bool val);
	bool getPetAlive();
	void setCastingSpell(bool val);
	bool getCastingSpell();
	void setFizzled(bool val);
	bool getFizzled();
	void setBeingHit(bool val);
	bool getBeingHit();
	void setLowMana(bool val);
	bool getLowMana();
	void setShielding(bool val);
	bool getShielding();
	System::String^ getPetName();
	void setPetName();
	System::String^ getLastLine();
	void setLastLineRead(System::String^ val);
	System::String^ getLastLineRead();

	// TBD
	void FindValidTarget();
	void Consider();
	void LogOn();
	void HideCorpses();
	
	void SummonPet();
	void PetSit();
	void Sit();
	void PetAttack();
	void AssistPet();

	void PetBackOff();
	void TargetPet();

	void VerifyTarget();

	//	Log stuff
	//static void OnLogChange(Object ^ obj, FileSystemEventArgs^ e);
	//void LogFlags(System::String^ newLine);					//	This is the new log text file logic routine
	void NecroRoutine();
	
};

