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

public ref class EverquestForm : public System::Windows::Forms::Form
{
private:
	bool consoleShowing;
	bool charAndServerLocked;

	Button^ button1;
	Button^ button2;

	TextBox^ textBox1;
	TextBox^ textBox2;
	TextBox^ textBox3;
	TextBox^ textBox4;
	TextBox^ textBox5;
	TextBox^ textBox6;
	TextBox^ textBox7;

	Label^ label1;
	Label^ label2;
	Label^ label3;
	Label^ label4;
	Label^ label5;
	Label^ label6;
	Label^ label7;

	Character^ character1;
	Character^ character2;
	Character^ character3;

	Watcher^ watcher;

	void GUI_Click(Object^ sender, EventArgs^ e);
	void GUI_TextChanged(Object^ sender, EventArgs^ e);

public:
	EverquestForm();
	void BuildGUIObjects();
	void BuildPrivate();
	void ButtonBuilder(Button^ button, int locx, int locy, int tabIndx, System::String^ text);
	void TextBoxBuilder(TextBox^ box, int locx, int locy, int tabIndx, System::String^ text);
	void LabelBuilder(Label^ label, int locx, int locy, int tabIndx, System::String^ text);

	static void Launch();
};

#endif