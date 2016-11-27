#include "stdafx.h"
#include "EverquestForm.h"

using namespace System::Drawing;
using namespace System::Windows::Forms;

[STAThread]
void EverquestForm::Launch()
{
	ShowWindow(GetConsoleWindow(), 0);
	Application::Run(gcnew EverquestForm());
}

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

//	This uses a typedef for a function pointer.  This is declared in EverquestForm.h
void EverquestForm::ButtonBuilder(Button^ button, int locx, int locy, int tabIndx, System::String^ text, System::String^ color)
{
	button->Location = Point(locx, locy);
	button->TabIndex = tabIndx;
	button->Text = text;
	button->AutoSize = true;
	button->Click += gcnew EventHandler(this, &EverquestForm::GUI_Click);
	if (color == "Red")
	{
		button->BackColor = System::Drawing::Color::Red;
	}
	if (color == "LightGreen")
	{
		button->BackColor = System::Drawing::Color::LightGreen;
	}

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
	button3 = gcnew Button();
	button4 = gcnew Button();
	textBox1 = gcnew TextBox();
	textBox2 = gcnew TextBox();
	textBox3 = gcnew TextBox();
	textBox4 = gcnew TextBox();
	textBox5 = gcnew TextBox();
	textBox6 = gcnew TextBox();
	textBox7 = gcnew TextBox();
	label1 = gcnew Label();
	label2 = gcnew Label();
	label3 = gcnew Label();
	label4 = gcnew Label();
	label5 = gcnew Label();
	label6 = gcnew Label();
	label7 = gcnew Label();

	ButtonBuilder(button1, 10, 10, 0, "Click to Start EQ Bot", "LightGreen");
	ButtonBuilder(button2, 10, 40, 1, "Show/Hide Console Window", "");
	ButtonBuilder(button3, 10, 70, 2, "Find EQ Character Window", "");
	ButtonBuilder(button4, 10, 100, 3, "Reset EQ Windows", "");

	LabelBuilder(label1, 200, 10, 9, "Character One ----->:");
	LabelBuilder(label2, 200, 40, 10, "Character Two ----->:");
	LabelBuilder(label3, 200, 70, 11, "Character Three --->:");
	LabelBuilder(label4, 200, 110, 12, "Server Name --->:");

	TextBoxBuilder(textBox1, 325, 10, 2, "Izzuum");
	TextBoxBuilder(textBox2, 325, 40, 3, "Khaed");
	TextBoxBuilder(textBox3, 325, 70, 4, "Ravek");
	TextBoxBuilder(textBox4, 325, 110, 5, "firiona");

	LabelBuilder(label5, 600, 10, 9, "HWND:");
	LabelBuilder(label6, 600, 40, 10, "HWND:");
	LabelBuilder(label7, 600, 70, 11, "HWND:");

	TextBoxBuilder(textBox5, 650, 10, 6, "unknown");
	TextBoxBuilder(textBox6, 650, 40, 7, "unknown");
	TextBoxBuilder(textBox7, 650, 70, 8, "unknown");
}

void EverquestForm::BuildPrivate()
{
	Text = "EQ Botter Thingy v2!";
	consoleShowing = false;
	Size = System::Drawing::Size(1200, 200);
	charAndServerLocked = false;

	character1 = gcnew Character();
	character2 = gcnew Character();
	character3 = gcnew Character();

	watcher = gcnew Watcher(character1, character2, character3);

	//	Note change Properties > General > Character Set to "Use Multi-Byte Character Set" so that FindWindow() works properly.
}

void EverquestForm::GUI_Click(Object ^ sender, EventArgs ^ e)
{
	//System::Windows::Forms::Button^ senderAsButton = (System::Windows::Forms::Button^)sender;
	if (sender == button1 && button1->Text)
	{
		if (button1->Text == "Click to Start EQ Bot")
		{
			button1->BackColor = System::Drawing::Color::Red;
			button1->Text = "Click to Stop EQ Bot";
			this->Refresh();

			//character1->setAttributes(textBox1->Text, textBox4->Text);
			//character2->setAttributes(textBox2->Text, textBox4->Text);
			//character3->setAttributes(textBox3->Text, textBox4->Text);

			//	Add filters to the filewatchers
			//watcher->getFileWatcher1()->Filter = character1->getLogFile();
			//watcher->getFileWatcher2()->Filter = character2->getLogFile();
			//watcher->getFileWatcher3()->Filter = character3->getLogFile();

			watcher->getFileWatcher1()->Filter = "eqlog_" + character1->getName() + "_" + character1->getServerName() + ".txt";
			//watcher->getFileWatcher2()->Filter = "eqlog_" + character2->getName() + "_" + character2->getServerName() + ".txt";
			//watcher->getFileWatcher3()->Filter = "eqlog_" + character3->getName() + "_" + character3->getServerName() + ".txt";

			//	Char and watcher is a wrapper class that holds the char, the watcher and any buttons it GUI objects
			//	Used to create a thread delegate object

			//ThreadStart^ threadDelegate = gcnew ThreadStart(charAndWatcher, &CharAndWatcher::RoutineLaunch);
			//Thread^ routineThread = gcnew Thread(threadDelegate);
			//routineThread->Start();
		}
		else if (button1->Text == "Click to Stop EQ Bot")
		{
			button1->BackColor = System::Drawing::Color::Green;
			button1->Text = "Click to Start EQ Bot";
			this->Refresh();
		}
		watcher->ToggleEvents();
	}

	if (sender == button2)
	{
		consoleShowing = !consoleShowing;
		if (consoleShowing)
			ShowWindow(GetConsoleWindow(), 1);
		if (!consoleShowing)
			ShowWindow(GetConsoleWindow(), 0);
	}

	if (sender == button3)
	{
		if (textBox5->Text == "unknown" && FindWindow("_EverQuestwndclass", "EverQuest") != NULL)
		{
			character1->setAttributes(textBox1->Text, textBox4->Text);
			textBox5->Text = character1->getName();
			SetWindowText(character1->getCharacterWindowHandle(), "Izzuum");
		}

		if (textBox6->Text == "unknown" && FindWindow("_EverQuestwndclass", "EverQuest") != NULL)
		{
			character2->setAttributes(textBox2->Text, textBox4->Text);
			textBox6->Text = character2->getName();
			SetWindowText(character2->getCharacterWindowHandle(), "Khaed");
		}

		if (textBox7->Text == "unknown" && FindWindow("_EverQuestwndclass", "EverQuest") != NULL)
		{
			character3->setAttributes(textBox3->Text, textBox4->Text);
			textBox7->Text = character3->getName();
			SetWindowText(character3->getCharacterWindowHandle(), "Ravek");
		}
		
	}

	if (sender == button4)
	{
		HWND one, two, three;
		one = FindWindow("_EverQuestwndclass", "Izzuum");
		two = FindWindow("_EverQuestwndclass", "Khaed");
		three = FindWindow("_EverQuestwndclass", "Ravek");
		if (one != NULL)
			SetWindowText(one, "EverQuest");
		if (two != NULL)
			SetWindowText(two, "EverQuest");
		if (three != NULL)
			SetWindowText(three, "EverQuest");
		textBox5->Text = "unknown";
		textBox6->Text = "unknown";
		textBox7->Text = "unknown";
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
		//charName = textBox1->Text;
	}

	if (sender == textBox2)
	{
		//serverName = textBox2->Text;
	}
	//charNameLabel->Text = "Character Name Set to: " + textBox1->Text;
	//serverNameLabel->Text = "Server Name Set to: " + textBox2->Text;
	this->Refresh();
}