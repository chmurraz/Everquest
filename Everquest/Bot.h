#pragma once
ref class Bot
{

private:
	bool validTarget;
	bool inRange;
	bool gotExp;
public:
	Bot();
	bool getValidTarget();
	bool getInRange();
	bool getGotExp();
	void setValidTarget(bool input);
	void setInRange(bool input);
	void setGotExp(bool input);
};

