#pragma once

#include "Item.hpp"

class Potion : public Item
{
public:
	Potion();
	void activate(Entity* target);
private:
	// Note: This will not work prior to C++11!
	// This assignment would need to be done in the constructor.
	int amount;
};

