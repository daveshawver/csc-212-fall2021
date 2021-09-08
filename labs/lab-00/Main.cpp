#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Entity.hpp"
#include "Potion.hpp"

int main(){
	srand((unsigned int)time(NULL));

    Entity hero = Entity("Hero", 20, 5);

	std::vector<Entity*> enemies;
	enemies.push_back(new Entity("Enemy 1", 10, 2));
	enemies.push_back(new Entity("Enemy 2", 10, 2));
	enemies.push_back(new Entity("Enemy 3", 25, 5));

	int turnCounter = 1;

	while (hero.getHealth() > 0 && enemies.size() > 0) {
		std::cout << "Turn " << turnCounter << "\n---------------------------------------\n";
		hero.getInfo();
		hero.displayInventory();

		if (hero.getInventorySize() > 0) {
			hero.useItem(0, &hero);
		}

		Item* temp = hero.attack(enemies.at(0));
		if (temp) {
			hero.addItem(temp);
			enemies.erase(enemies.begin());
		}
		// Signed: -2^(31) - 1 through 2^31
		// Unsigned: 2^(32) - 1
		for (unsigned int i = 0; i < enemies.size(); i++) {
			enemies.at(i)->getInfo();
			enemies.at(i)->attack(&hero);
		}
		turnCounter++;
	}

	if (hero.getHealth() > 0) {
		std::cout << "You Win!\n";
	}
	else {
		std::cout << "You Lose!\n";
	}

}