// Everquest.cpp : Defines the entry point for the console application.


//	REMOVE ALL REFERENCES TO LOGWATCHER CLASS ONCE WATCHER CLASS IS WORKING

#include "stdafx.h"
#include "EverquestForm.h"

//using namespace System;
//using namespace System::Runtime::InteropServices;
//using namespace System::Drawing;
//using namespace System::Windows::Forms;
//using namespace System::Threading;

EverquestForm::EverquestForm()
{
		// The ^ hat symbol here is a garbage collection thing from Microsoft https://msdn.microsoft.com/en-us/library/yk97tc08.aspx
		// gcnew (or garbage collection new) is also a Microsoft thing https://msdn.microsoft.com/en-us/library/te3ecsc8.aspx
		// These require CLR compiler option
		Text = "Everquest Botter Thingy!";

		//	Set GUI options
		consoleShowing = false;
		thisHandle = FindWindowA(NULL, "Everquest Botter Thingy!");
		Size = System::Drawing::Size(500, 500);

		Button^ button1 = gcnew Button();
		Button^ button2 = gcnew Button();
		TextBox^ textBox1 = gcnew TextBox();
		Label^ label1 = gcnew Label();
		button1->Location = System::Drawing::Point(10, 10);
		button2->Location = System::Drawing::Point(10, 40);
		textBox1->Location = System::Drawing::Point(300, 10);
		label1->Location = System::Drawing::Point(200, 10);

		//	This will be the "zeroth" button when pressing tab to cycle between them
		button1->TabIndex = 0;
		button2->TabIndex = 1;
		textBox1->TabIndex = 2;
		button1->Text = "Click to automate EQ";
		button2->Text = "Show/Hide Console Window";
		textBox1->Text = "Enter Character Name Here";
		label1->Text = "Character Name:";
		button1->AutoSize = true;
		button2->AutoSize = true;
		textBox1->AutoSize = true;
		button1->Click += gcnew EventHandler(this, &EverquestForm::button1_Click);
		button2->Click += gcnew EventHandler(this, &EverquestForm::button2_Click);
		this->Controls->Add(button1);
		this->Controls->Add(button2);
		this->Controls->Add(textBox1);
		this->Controls->Add(label1);
}

void EverquestForm::button1_Click(Object ^ sender, EventArgs ^ e)
{
	Character^ Necro = gcnew Character;

	//	Move all watcher stuff into the Character class
	Watcher^ logWatcher = gcnew Watcher;
	Necro->MoveEQToFront();
	logWatcher->ScanLog();
	logWatcher->setCharacter(Necro);
	Necro->NecroRoutine();
}
void EverquestForm::button2_Click(Object ^ sender, EventArgs ^ e)
{
	consoleShowing = !consoleShowing;
	if (consoleShowing)
		ShowWindow(GetConsoleWindow(), 1);
	if (!consoleShowing)
		ShowWindow(GetConsoleWindow(), 0);
}