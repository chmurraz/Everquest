// Everquest.cpp : Defines the entry point for the console application.


//	REMOVE ALL REFERENCES TO LOGWATCHER CLASS ONCE WATCHER CLASS IS WORKING

#include "stdafx.h"
#include "EverquestForm.h"

//using namespace System;
//using namespace System::Runtime::InteropServices;
using namespace System::Drawing;
using namespace System::Windows::Forms;
//using namespace System::Threading;

EverquestForm::EverquestForm()
{
		// The ^ hat symbol here is a garbage collection thing from Microsoft https://msdn.microsoft.com/en-us/library/yk97tc08.aspx
		// gcnew (or garbage collection new) is also a Microsoft thing https://msdn.microsoft.com/en-us/library/te3ecsc8.aspx
		// These require CLR compiler option

		//	Build the private member variables and other options for the Form
		BuildPrivate();

		//	Declare and Build GUI Objects such as buttons, text fields, etc
		BuildGUIObjects();
}

[STAThread]
void EverquestForm::Main()
{
	ShowWindow(GetConsoleWindow(), 0);
	Application::Run(gcnew EverquestForm());
}

//	This uses a typedef for a function pointer.  This is declared in EverquestForm.h
void EverquestForm::ButtonBuilder(Button^ button, int locx, int locy, int tabIndx, System::String^ text)
{
	button->Location = Point(locx, locy);
	button->TabIndex = tabIndx;
	button->Text = text;
	button->AutoSize = true;
	button->Click += gcnew EventHandler(this, &EverquestForm::GUI_Click);
	this->Controls->Add(button);
}

void EverquestForm::TextBoxBuilder(TextBox ^ box, int locx, int locy, int tabIndx, System::String ^ text)
{
	box->Location = Point(locx, locy);
	box->TabIndex = tabIndx;
	box->Text = text;
	box->AutoSize = true;
	box->Width = 200;
	box->TextChanged += gcnew EventHandler(this, &EverquestForm::GUI_TextChanged);
	box->Click += gcnew EventHandler(this, &EverquestForm::GUI_Click);
	this->Controls->Add(box);
}

void EverquestForm::LabelBuilder(Label ^ label, int locx, int locy, int tabIndx, System::String ^ text)
{
	label->Location = Point(locx, locy);
	label->TabIndex = tabIndx;
	label->Text = text;
	label->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
	label->AutoSize = true;
	this->Controls->Add(label);
}

void EverquestForm::BuildGUIObjects()
{
	button1 = gcnew Button();
	button2 = gcnew Button();
	textBox1 = gcnew TextBox();
	textBox2 = gcnew TextBox();
	label1 = gcnew Label();
	label2 = gcnew Label();
	charNameLabel = gcnew Label();
	serverNameLabel = gcnew Label();

	ButtonBuilder(button1, 10, 10, 0, "Click to Start EQ Bot");
	ButtonBuilder(button2, 10, 40, 1, "Show/Hide Console Window");
	TextBoxBuilder(textBox1, 325, 10, 2, "Type Here...");
	TextBoxBuilder(textBox2, 325, 40, 3, "Type Here...");
	LabelBuilder(label1, 200, 10, 4, "Character Name -->:");
	LabelBuilder(label2, 200, 40, 5, "Server Name ----->:");
	LabelBuilder(charNameLabel, 600, 10, 6, "Character Name Set to: N/A");
	LabelBuilder(serverNameLabel, 600, 40, 7, "Character Name Set to: N/A");
}

void EverquestForm::BuildPrivate()
{
	Text = "Everquest Botter Thingy!";
	consoleShowing = false;
	Size = System::Drawing::Size(1000, 500);
	charName = "";
	serverName = "";

	//	Note change Properties > General > Character Set to "Use Multi-Byte Character Set" so that FindWindow() works properly.
	EQHandle = FindWindowA(NULL, "Everquest");
}

void EverquestForm::GUI_Click(Object ^ sender, EventArgs ^ e)
{
	//System::Windows::Forms::Button^ senderAsButton = (System::Windows::Forms::Button^)sender;
	if (sender == button1)
	{
		// Verify that Everquest is a running process.
		if (EQHandle == NULL)
		{
			MessageBox::Show("Everquest is not running.");
		}
		else
		{
			Character^ Necro = gcnew Character;

			//	Move all watcher stuff into the Character class
			Watcher^ logWatcher = gcnew Watcher;
			Necro->MoveEQToFront();
			logWatcher->ScanLog();
			logWatcher->setCharacter(Necro);
			Necro->NecroRoutine();
		}
	}

	if (sender == button2)
	{
		consoleShowing = !consoleShowing;
		if (consoleShowing)
			ShowWindow(GetConsoleWindow(), 1);
		if (!consoleShowing)
			ShowWindow(GetConsoleWindow(), 0);
	}
	if (sender == textBox1 )
	{
		textBox1->Text = "";
	}

	if (sender == textBox2)
	{
		textBox2->Text ="";
	}
}

void EverquestForm::GUI_TextChanged(Object ^ sender, EventArgs ^ e)
{
	if (sender == textBox1)
	{
		charName = textBox1->Text;
	}

	if (sender == textBox2)
	{
		serverName = textBox2->Text;
	}
	charNameLabel->Text = "Character Name Set to: " + textBox1->Text;
	serverNameLabel->Text = "Server Name Set to: " + textBox2->Text;
	this->Refresh();
}
