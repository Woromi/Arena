#include "arena.hpp"
#include "read_input.hpp"
#include "items.hpp"
#include "knihovna.hpp"

#include <string>

int main(int argc, char * * argv) {
	Knihovna knihovna;
	Shop shop{ "items.txt" }; // Nacti vybaveni ze souboru

	//Arena arena = read_input(knihovna, shop);

	// Vytvareni tymu bez cteni vstupu (jen pro testovani souboje)
	Arena arena;
	{	
		//Mage Woromi{ "Woromi" };
		//Mage Modrozub{ "Modrozub" };
		Mage Plosnak{ "Plosnak" };
		Mage Plosnak2{ "Plosnak2" };
		Mage Dummy1{ "Dummy1" };
		Mage Dummy2{ "Dummy2" };
		//Woromi.learn(arena.out, knihovna.get_spell(arena.out, "Ice lance"));
		//Modrozub.learn(arena.out, knihovna.get_spell(arena.out, "Fireball"));
		Plosnak.learn(arena.out, knihovna.get_spell(arena.out, "Flamestrike"));
		Plosnak2.learn(arena.out, knihovna.get_spell(arena.out, "Flamestrike"));
		//Dummy1.learn(arena.out, knihovna.get_spell(arena.out, "Ice lance"));
		Dummy2.learn(arena.out, knihovna.get_spell(arena.out, "Ice lance"));

		//Woromi.buy_weapon(arena.out, shop.get_weapon(arena.out, "Wooden staff"));
		//Woromi.buy_robe(arena.out, shop.get_robe(arena.out, "Heavy armored robe"));
		//Modrozub.buy_robe(arena.out, shop.get_robe(arena.out, "Robe"));
		//Modrozub.buy_weapon(arena.out, shop.get_weapon(arena.out, "Wooden staff of flames"));
		Plosnak.buy_weapon(arena.out, shop.get_weapon(arena.out, "Wooden staff of flames"));
		Plosnak.buy_robe(arena.out, shop.get_robe(arena.out, "Heavy armored robe"));
		Dummy1.buy_robe(arena.out, shop.get_robe(arena.out, "Robe of fire resistance"));

		//arena.team1_add(std::move(Woromi));
		arena.team1_add(std::move(Plosnak));
		arena.team1_add(std::move(Plosnak2));
		//arena.team2_add(Modrozub);
		arena.team2_add(std::move(Dummy1));
		arena.team2_add(std::move(Dummy2));
	}//*/

	arena.souboj();
}