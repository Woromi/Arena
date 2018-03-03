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
		//Woromi.learn(knihovna.get_spell("Ice lance"));
		//Modrozub.learn(knihovna.get_spell("Fireball"));
		Plosnak.learn(knihovna.get_spell("Flamestrike"));
		Plosnak2.learn(knihovna.get_spell("Flamestrike"));
		//Dummy1.learn(knihovna.get_spell("Ice lance"));
		Dummy2.learn(knihovna.get_spell("Ice lance"));

		//Woromi.buy_weapon(shop.get_weapon("Wooden staff"));
		//Woromi.buy_robe(shop.get_robe("Heavy armored robe"));
		//Modrozub.buy_robe(shop.get_robe("Robe"));
		//Modrozub.buy_weapon(shop.get_weapon("Wooden staff of flames"));
		Plosnak.buy_weapon(shop.get_weapon("Wooden staff of flames"));
		Plosnak.buy_robe(shop.get_robe("Heavy armored robe"));
		Dummy1.buy_robe(shop.get_robe("Robe of fire resistance"));

		//arena.team1_add(std::move(Woromi));
		arena.team1_add(Plosnak);
		arena.team1_add(Plosnak2);
		//arena.team2_add(Modrozub);
		arena.team2_add(Dummy1);
		arena.team2_add(Dummy2);
	}//*/

	arena.souboj();
}