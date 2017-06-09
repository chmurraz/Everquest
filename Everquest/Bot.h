#pragma once

ref class Bot
{

private:
	bool validTarget;
	bool inRange;
	bool gotExp;
	bool lowMana;

public:


	Bot();
	bool getValidTarget();
	bool getInRange();
	bool getGotExp();
	bool getLowMana();
	void setValidTarget(bool input);
	void setInRange(bool input);
	void setGotExp(bool input);
	void setLowMana(bool input);
	void falseAllBools();

};

