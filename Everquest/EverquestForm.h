#ifndef EVERQUESTFORM_H
#define EVERQUESTFORM_H

#include "Character.h"
//#include "LogWatcher.h"
#include "Watcher.h"
//#using <System.Drawing.dll>
//#using <System.Windows.Forms.dll>
//#using <System.dll>
//#include <cstdio>

using namespace System::Windows::Forms;

//	This is a wrapper class to contain the Character and Watcher objects
public ref class CharAndWatcher
{
private:
	Character^ character;
	Watcher^ logWatcher;
public:
	CharAndWatcher(System::String^ cName, System::String^ sName);
	void RoutineLaunch();
};

public ref class EverquestForm : public System::Windows::Forms::Form
{
private:
	bool consoleShowing;
	bool charAndServerLocked;
	static System::String^ charName;
	static System::String^ serverName;

	Button^ button1;
	Button^ button2;

	TextBox^ textBox1;
	TextBox^ textBox2;

	Label^ label1;
	Label^ label2;
	Label^ charNameLabel;
	Label^ serverNameLabel;
	HWND EQHandle;

	void GUI_Click(Object^ sender, EventArgs^ e);
	void GUI_TextChanged(Object^ sender, EventArgs^ e);
	void MoveEQToFront();

public:
	EverquestForm();
	void BuildGUIObjects();
	void BuildPrivate();
	void ButtonBuilder(Button^ button, int locx, int locy, int tabIndx, System::String^ text);
	void TextBoxBuilder(TextBox^ box, int locx, int locy, int tabIndx, System::String^ text);
	void LabelBuilder(Label^ label, int locx, int locy, int tabIndx, System::String^ text);
	static System::String^ getCharName();
	static System::String^ getServerName();

	static void Launch();
};

#endif