#include "arena.hpp"

#include <iostream>

int main(int argc, char * * argv) {
	Knihovna knihovna;
	Mage Woromi{ "Woromi" };
	Mage Modrozub{ "Modrozub" };
	Woromi.learn(knihovna.get_spell("Fireball"));
	//Woromi.learn(knihovna.get_spell("Ice lance"));
	Modrozub.learn(knihovna.get_spell("Fireball"));
	Modrozub.learn(knihovna.get_spell("Ice lance"));

	Arena arena;

	arena.team1_add(Woromi);
	arena.team2_add(Modrozub);

	arena.souboj();
}