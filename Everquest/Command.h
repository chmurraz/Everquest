#pragma once
//#include "Observer.h"
#include <windows.h>
#include "Bot.h"

//	I DON"T THINK THIS DELEGATE IS NEEDED???  CLEAN UP
public delegate void MyDelegate(int number);

//ref class Command : Observer
ref class Command
{
private:
	INPUT* ip;
	DWORD rest;
	DWORD typeSpeed;
	//System::IO::StreamWriter ^sw;

public:
	Command();
	~Command();
	void Delegate1(int number);
	void Delegate2(int number);
	void Handler(System::String^ eventText, Bot^ botData, System::String^ logFile);

	//	Keyboard Sim
	void PressKeys(System::String^ keys, System::Boolean enterBool);
	void PressKeyTest(UINT key);
	void PressKeyTest(UINT key, bool hold);
	void HoldShift();
	void ReleaseShift();
	void PressESC();
	void PressEnter();
	void PressTab();
	void PressF1();
	void Press1();
	void Press2();
	void Press3();
	void Press4();
	void Press5();
	void Press6();
	void Press7();
	void Press8();
	void Press9();
	void Press0();
	void PressRight();
	void PressUp();
	void PressW();
	void PressD();

};

