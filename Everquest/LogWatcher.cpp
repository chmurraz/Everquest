#include "stdafx.h"
#include "LogWatcher.h"

void LogWatcher::ScanLog()
{
	do
	{
		oldLine = character->getLastLine();
		do
		{
			newLine = character->getLastLine();

		} while (newLine->Equals(oldLine) && !newLine->Contains("say to your guild"));

		//	Update character member variables based on new line activity

		//	Experience
		if (newLine->Contains("You gain experience"))
			character->setExp(true);

		//	Buffs
		if (newLine->Contains("You do not sense any enchantments"))
			character->setShielding(false);
		if (newLine->Contains("Minor Shielding"))
			character->setShielding(true);
		if (newLine->Contains("You feel armored"))
			character->setShielding(true);
		if (newLine->Contains("Your shielding fades away"))
			character->setShielding(false);

		//	Target
		if (newLine->Contains("looks kind of risky"))
			character->setValidTarget(true);
		if (newLine->Contains("no longer have a target") ||
			newLine->Contains("must first select a target for this spell") ||
			newLine->Contains("can't drain yourself") ||
			(character->getPetAlive() && newLine->Contains(character->getPetName())) ||
			newLine->Contains("target is out of range"))
			character->setValidTarget(false);
		if (newLine->Contains("cannot see your target"))
			character->setValidTarget(false);
		if (newLine->Contains("a skunk"))
			character->setValidTarget(false);

		//	Pet Alive or Dead or In Combat
		if (newLine->Contains("Changing position") || 
			newLine->Contains("Targeting your pet") ||
			newLine->Contains("cannot have more than one pet at a time"))
			character->setPetAlive(true);
		if (newLine->Contains("don't have a pet to command"))
			character->setPetAlive(false);
		if (newLine->Contains("tells you, 'Attacking") && newLine->Contains("Master"))
			character->setPetInCombat(true);

		//	Casting spells
		if (newLine->Contains("our spell fizzles"))
		{
			character->setFizzled(true);
			character->setCastingSpell(false);
		}
		if (newLine->Contains("ou begin casting") || 
			newLine->Contains("use that command while casting") || 
			newLine->Contains("ou haven't recovered yet") ||
			newLine->Contains("our spell is interrupted"))
		{
			character->setCastingSpell(true);
			character->setFizzled(false);
		}
		
		//	Combat
		if (newLine->Contains("YOU for") || newLine->Contains("YOU, but misses"))
			character->setBeingHit(true);

	} while (!character->getRoutineStop());
}