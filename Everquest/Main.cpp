#include "stdafx.h"
#include "EverquestForm.h"

int main()
{
	Console::WriteLine("Drag this console window aside to show the GUI window");
	
	//	Enable fancy themes if user's OS has them turned on
	Application::EnableVisualStyles();

	//	Run the GUI
	EverquestForm::Launch();

}