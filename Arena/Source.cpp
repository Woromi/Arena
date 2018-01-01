#include "arena.hpp"
#include "read_input.hpp"

#include <string>

int main(int argc, char * * argv) {
	Knihovna knihovna;
	Shop shop{ "items.txt" }; // Nacti vybaveni ze souboru

	//Arena arena = read_input(knihovna, shop);

		Arena arena;
	// Docasne vytvareni tymu
	{	
		Mage Woromi{ "Woromi" };
		Mage Modrozub{ "Modrozub" };
		Woromi.learn(knihovna.get_spell("Ice lance"));
		Modrozub.learn(knihovna.get_spell("Fireball"));

		Woromi.buy_weapon(shop.get_weapon("Wooden staff"));
		Woromi.buy_robe(shop.get_robe("Heavy armored robe"));
		Modrozub.buy_robe(shop.get_robe("Robe"));
		Modrozub.buy_weapon(shop.get_weapon("Wooden staff of flames"));

		arena.team1_add(Woromi);
		arena.team2_add(Modrozub);
	}//*/

	arena.souboj();
}