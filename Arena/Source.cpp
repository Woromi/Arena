#include "arena.hpp"

#include <iostream>

int main(int argc, char * * argv) {
	Knihovna knihovna;
	Weapons weapons; // TODO: weapons
	Mage Woromi{ "Woromi" };
	Mage Modrozub{ "Modrozub" };
	Woromi.learn(knihovna.get_spell("Ice lance"));
	Modrozub.learn(knihovna.get_spell("Fireball"));

	Modrozub.buy(*weapons.get_weapon("Wooden staff"));

	Arena arena;

	arena.team1_add(Woromi);
	arena.team2_add(Modrozub);

	arena.souboj();
}