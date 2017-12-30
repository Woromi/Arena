#include "arena.hpp"
#include "read_input.hpp"

int main(int argc, char * * argv) {
	Knihovna knihovna;
	Shop shop{ "equipement.txt" }; // Nacti vybaveni ze souboru

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
	}

	shop.show_weapons();

	arena.souboj();
}