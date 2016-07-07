// Everquest.cpp : Defines the entry point for the console application.


//	REMOVE ALL REFERENCES TO LOGWATCHER CLASS ONCE WATCHER CLASS IS WORKING

#include "stdafx.h"
#include "Character.h"
//#include "LogWatcher.h"
#include "Watcher.h"
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>
#using <System.dll>
#include <cstdio>
#include "Everquest.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Threading;

namespace SimulateKeyPress
{
	public ref class Form1 : public Form
	{
	public:
		Form1()
		{
			// The ^ hat symbol here is a garbage collection thing from Microsoft https://msdn.microsoft.com/en-us/library/yk97tc08.aspx
			// gcnew (or garbage collection new) is also a Microsoft thing https://msdn.microsoft.com/en-us/library/te3ecsc8.aspx
			// These require CLR compiler option
			Text = "Everquest Botter Thingy!";

			Button^ button1 = gcnew Button();
			Button^ button2 = gcnew Button();
			button1->Location = Point(10, 10);
			button2->Location = Point(10, 40);

			//	This will be the "zeroth" button when pressing tab to cycle between them
			button1->TabIndex = 0;
			button2->TabIndex = 1;
			button1->Text = "Click to automate EQ";
			button2->Text = "Do something else";
			button1->AutoSize = true;
			button2->AutoSize = true;
			button1->Click += gcnew EventHandler(this, &Form1::button1_Click);
			button2->Click += gcnew EventHandler(this, &Form1::button2_Click);
			this->Controls->Add(button1);
			this->Controls->Add(button2);
		}

	// Execute commands when button is pressed.
	private:
		void button1_Click(Object^ sender, EventArgs^ e);
		void button2_Click(Object^ sender, EventArgs^ e);
	};
	inline void Form1::button1_Click(Object ^ sender, EventArgs ^ e)
	{
		Character^ Necro = gcnew Character;

		//	Move all watcher stuff into the Character class
		Watcher^ logWatcher = gcnew Watcher;
		Necro->MoveEQToFront();
		logWatcher->ScanLog();
		logWatcher->setCharacter(Necro);
		Necro->NecroRoutine();
	}
	void Form1::button2_Click(Object ^ sender, EventArgs ^ e)
	{
		MessageBox::Show("Ouch!");
	}
}

[STAThread]
int main()
{
	Console::WriteLine("testing (in Everquest.cpp:main) 1 2 3... this is a write line to console");
	Application::EnableVisualStyles();
	Application::Run(gcnew SimulateKeyPress::Form1());
}