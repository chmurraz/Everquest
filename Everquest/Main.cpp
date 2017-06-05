#include "stdafx.h"
#include "EverquestForm.h"

int main()
{
	Console::WriteLine("Drag this console window aside to show the GUI window");
	
	//	Enable fancy themes if user's OS has them turned on
	Application::EnableVisualStyles();

	//	Run the GUI
	EverquestForm::Launch();

	//	Testing Event/Delegates/Queues
	
	/*		FROM PDF
	Command ^test = gcnew Command;
	MyDelegate ^delegate_test = gcnew MyDelegate(test, &Command::Delegate1);

	if (delegate_test)
		delegate_test(12345);

	delegate_test += gcnew MyDelegate(test, &Command::Delegate2);
	delegate_test -= gcnew MyDelegate(test, &Command::Delegate1);

	Character ^testChar = gcnew Character;
	test->

	*/

	/*
	/////	From MSDN
	//https://msdn.microsoft.com/en-us/library/58cwt3zh.aspx

	//	Declare a new character (event source)
	Character ^character = gcnew Character();
	
	//	Declare a new command (event listener)
	Command^ command = gcnew Command();

	//	Hook the handler to the event
	character->getBotData()->E += gcnew BotDataChanged(command, &Command::Handler);

	//	Call the event
	character->getBotData()->fire(1, 3.14);

	//	Unhook the handler from the event
	character->getBotData()->E -= gcnew BotDataChanged(command, &Command::Handler);
	*/

	//CommandQueue<String^>^ test = gcnew CommandQueue<String^>();


}