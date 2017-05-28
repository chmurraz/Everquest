#include "stdafx.h"
#include "Actions.h"


Actions::Actions()
{
}

void Actions::ProcessActions(Character^ character, System::String ^ newLine)
{
	/* WORK ON KHAED RAVEK STUFF BELOW*/
	/*
	if (character->getName() == "Khaed")
	{
		if (newLine->Contains("Assist me Khaed!"))
		{
			character->BringWindowToFront();
			character->PressKeys("/assist izzuum", true);
			character1->BringWindowToFront();
		}
		if (newLine->Contains("Khaed, play your group buffs please"))
		{
			character->BringWindowToFront();
			character->PressKeys("/stopsong", true);
			character->PressKeys("/melody 3 5 8 9 1 3 5 8 9 1 3 5 8 9 1 4", true);
			character->PressKeys("/g ", false);
			character->HoldShift();
			character->PressKeys("i ", false);
			character->ReleaseShift();
			character->PressKeys("have started singing my buff songs", true);
			//character->Press6();
			character1->BringWindowToFront();
		}
		if (newLine->Contains("Khaed, stop singing"))
		{
			character->BringWindowToFront();
			character->PressKeys("/stopsong", true);
			character->PressKeys("/g ", false);
			character->HoldShift();
			character->PressKeys("i ", false);
			character->ReleaseShift();
			character->PressKeys("have stopped singing", true);
			character1->BringWindowToFront();
		}
		if (newLine->Contains("Khaed, mesmerize my target"))
		{
			character->BringWindowToFront();
			character->PressKeys("/stopsong", true);
			character->PressKeys("/assist Izzuum", true);
			character->PressKeys("/attackoff", true);
			character->PressKeys("/melody 11", true);
			character->PressKeys("/g ", false);
			character->HoldShift();
			character->PressKeys("i ", false);
			character->ReleaseShift();
			character->PressKeys("am mesmerizing it", true);
			character1->BringWindowToFront();
		}
		if (newLine->Contains("Khaed, slow them down"))
		{
			character->BringWindowToFront();
			character->PressKeys("/stopsong", true);
			character->PressKeys("/melody 2 1 3 8 9", true);
			character->PressKeys("/g ", false);
			character->HoldShift();
			character->PressKeys("i ", false);
			character->ReleaseShift();
			character->PressKeys("am slowing them", true);
			character1->BringWindowToFront();
		}
		if (newLine->Contains("Khaed, AoE mez and assist"))
		{
			character->BringWindowToFront();
			character->PressKeys("/stopsong", true);
			character->PressKeys("/assist Izzuum", true);
			character->PressKeys("/melody 10 2 12 8 3 5 12 8 3 5 12", true);
			character->PressKeys("/g ", false);
			character->HoldShift();
			character->PressKeys("i ", false);
			character->ReleaseShift();
			character->PressKeys("am slowing them", true);
			character1->BringWindowToFront();
		}
	}
	if (character->getName() == "Ravek")
	{
		if (newLine->Contains("Assist me Ravek!"))
		{
			character->BringWindowToFront();
			character->PressKeys("/assist izzuum", true);
			character->PressKeys("/pet attack", true);
			character1->BringWindowToFront();
		}
		if (newLine->Contains("Ravek, flameskin please"))
		{
			character->BringWindowToFront();
			character->PressKeys("/cast 11", true);
			character->PressKeys("/g ", false);
			character->HoldShift();
			character->PressKeys("t", false);
			character->ReleaseShift();
			character->PressKeys("he group has been immolated", true);
			character1->BringWindowToFront();
		}
	}
	*/
	if (character->getName() == "Xuurak")
	{
		if (newLine->Contains("Consider whom"))
		{
			character->BringWindowToFront();
			character->PressTab();
			character->PressKeys("/consider", true);
		}
		if (newLine->Contains("looks kind of risky"))
		{
			character->getBotData()->setValidTarget(true);
			character->PressKeys("/say valid", true);
			int count = 0;
			do
			{
				character->PressKeys("/cast 5", true);
				count++;
			} while (count < 6);
			character->PressKeys("/sit", true);
			Sleep(30000);
		}
		if (newLine->Contains("Talking to yourself"))
		{
			character->PressESC();
			character->PressKeys("/consider", true);
		}
	}
}
