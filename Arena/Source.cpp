#include "arena.hpp"
#include "read_input.hpp"
#include "items.hpp"
#include "knihovna.hpp"
#include <string>

int main(int argc, char * * argv) {
	Arena arena;
	Knihovna knihovna{arena};
	Shop shop{ arena, "items.txt" }; // Nacti vybaveni ze souboru

	// read_input(arena, knihovna, shop);

	// Vytvareni tymu bez cteni vstupu (jen pro testovani souboje)
	{	
		Mage Plosnak{ "Plosnak", arena };
		Mage Plosnak2{ "Plosnak2", arena };
		Mage Dummy1{ "Dummy1", arena };
		Mage Dummy2{ "Dummy2", arena };
		Plosnak.learn(knihovna.get_spell("Flamestrike"));
		Plosnak2.learn(knihovna.get_spell("Flamestrike"));
		Dummy2.learn(knihovna.get_spell("Ice lance"));

		Plosnak.buy_weapon(shop.get_weapon("Wooden staff of flames"));
		Plosnak.buy_robe(shop.get_robe("Heavy armored robe"));
		Dummy1.buy_robe(shop.get_robe("Robe of fire resistance"));

		arena.team1_add(std::move(Plosnak));
		arena.team1_add(std::move(Plosnak2));
		arena.team2_add(std::move(Dummy1));
		arena.team2_add(std::move(Dummy2));
	}//*/

	arena.souboj();
 }