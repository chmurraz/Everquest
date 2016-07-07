#include "stdafx.h"
#include "EverquestForm.h"

[STAThread]
int main()
{
	Console::WriteLine("Drag this console window aside to show the GUI window");
	
	//	Enable fancy themes if user's OS has them turned on
	Application::EnableVisualStyles();

	ShowWindow(GetConsoleWindow(), 0);

	//	Run the GUI
	EverquestForm^ EQform = gcnew EverquestForm();
	Application::Run(EQform);
	

	// *** ATTEMPTS TO MOVE/RESIZE CONSOLE WINDOW *** //

	//EQform->StartPosition = FormStartPosition::CenterScreen;
	//EQform->Dock = DockStyle::Left;
	//MoveWindow(GetConsoleWindow(), 100, 100, Console::WindowWidth, Console::WindowHeight, TRUE);
	//FreeConsole();
	//ShowWindow(GetConsoleWindow(), SW_RESTORE);
	//HWND consoleWindow = GetConsoleWindow();
	//SetWindowPos(consoleWindow, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	//System::Console::SetWindowPosition(50, 50);
}