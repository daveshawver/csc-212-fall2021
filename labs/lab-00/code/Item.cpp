#include "Item.hpp"
#include "Potion.hpp"
#include "MegaPotion.hpp"

Item::Item(std::string name) {
	this->name = name;
}

std::string Item::getName() {
	return this->name;
}

Item* Item::generateItem(std::string name) {
	if (name == "Potion") {
		return new Potion();
	}
	else if (name == "Mega Potion") {
		return new MegaPotion();
	}
	// An invalid item was requested.
	std::cout << "That item does not exist!\n";
	return nullptr;
}

Item* Item::generateRandomItem() {
	int choice = rand() % 2;

	if (choice == 0) {
		return new Potion();
	}
	else if (choice == 1) {
		return new MegaPotion();
	}
	// Make sure the # being modded is the count of items.
	std::cout << "Error in modulo for generateRandomItem()!\n";
	return nullptr;
}
