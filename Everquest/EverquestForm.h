#ifndef EVERQUESTFORM_H
#define EVERQUESTFORM_H

#include "Character.h"
//#include "LogWatcher.h"
#include "Watcher.h"
//#using <System.Drawing.dll>
//#using <System.Windows.Forms.dll>
//#using <System.dll>
//#include <cstdio>

public ref class EverquestForm : public System::Windows::Forms::Form
{
private:
	bool consoleShowing;
	HWND thisHandle;
	void button1_Click(Object^ sender, EventArgs^ e);
	void button2_Click(Object^ sender, EventArgs^ e);
public:
	EverquestForm();

};

#endif