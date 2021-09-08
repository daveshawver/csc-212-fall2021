#include "MegaPotion.hpp"

MegaPotion::MegaPotion() : Item("Mega Potion") {
	this->amount = 50;
}

void MegaPotion::activate(Entity* target) {
	target->heal(this->amount);
}