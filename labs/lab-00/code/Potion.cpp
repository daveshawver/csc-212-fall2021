#include "Potion.hpp"

Potion::Potion() : Item("Potion") {
	this->amount = 20;
}

void Potion::activate(Entity* target) {
	target->heal(this->amount);
}
