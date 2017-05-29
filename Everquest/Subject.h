#pragma once
#include <vector>
#include <list>
#include "shop.h"

ref class Subject
{
	//Lets keep a track of all the shops we have observing
	std::vector<Shop*> list;

public:
	void Attach(Shop *product);
	void Detach(Shop *product);
	void Notify(float price);
};

