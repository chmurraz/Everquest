#pragma once

public delegate void BotDataChanged(int, float);

//	interface that has an event and a function to invoke the event
interface struct I
{
public:
	event BotDataChanged ^E;
	void fire(int, float);
};

ref class Bot: public I
{

private:
	bool validTarget;
	bool inRange;
	bool gotExp;
public:

	//	Events
	virtual event BotDataChanged ^E;
	virtual void fire(int i, float f)
	{
		E(i, f);
	}
	Bot();
	bool getValidTarget();
	bool getInRange();
	bool getGotExp();
	void setValidTarget(bool input);
	void setInRange(bool input);
	void setGotExp(bool input);
	void falseAllBools();
};

