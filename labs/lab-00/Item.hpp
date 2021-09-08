#pragma once
#include "Entity.hpp"

class Item
{
private:
	std::string name;

public:
	Item(std::string name);
	std::string getName();
	static Item* generateItem(std::string name);
	static Item* generateRandomItem();
	virtual void activate(Entity* target) = 0;
};