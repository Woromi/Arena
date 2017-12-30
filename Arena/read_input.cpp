#include "read_input.hpp"

#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>

// https://stackoverflow.com/questions/23943728/case-insensitive-standard-string-comparison-in-c
bool icompare_pred(unsigned char a, unsigned char b)
{
	return std::tolower(a) == std::tolower(b);
}

bool icompare(std::string const& a, std::string const& b)
{
	if (a.length() == b.length()) {
		return std::equal(b.begin(), b.end(),
			a.begin(), icompare_pred);
	}
	else {
		return false;
	}
}

void write_help() { // TODO: Zarovnat text doleva
	std::cout
		<< std::setw(40) << "Mage name "<<"- zacne vytvaret noveho maga se jmenem 'name'"	<< std::endl	// Mage name
		<< std::setw(40) << "School "<<"- vypise seznam kouzel, ktere se mag muze naucit"	<< std::endl	// School
		<< std::setw(40) << "Learn 'name' "<<"\t- nauci maga kouzlo se jmenem 'name'"		<< std::endl	// Learn spell_name
		<< std::setw(40) << "Shop "<<"- vypise seznam veci, ktere si mag muze koupit"		<< std::endl	// Shop
		<< std::setw(40) << "Buy weapon|robe|... 'name' "<<"\t- mag si koupi predmet se jmenem 'name'"		<< std::endl	// Buy item_name
		<< std::setw(40) << "Show "<<"- vypise aktualni vlastnost maga"					<< std::endl	// Show
		<< std::setw(40) << "Team [12] "<<"- ukonceni procesu vytvareni postavy a zarazeni maga do tymu [12]" << std::endl	// Team
		<< std::setw(40) << "Fight "<<"- zahaji souboj s vytvorenymi magy"					<< std::endl;	// Fight
}

void write_items(const Shop & shop) {
	shop.show_weapons();
	shop.show_robes();
	// TODO: Pridat dalsi druhy vybaveni
}

void team(Arena & arena, Mage mage, int i) { // Tady predavam hodnotou, budu presouvat vytvoreneho maga
	switch (i)
	{
	case 1:
		std::cout << mage.get_name() << " byl zarazen do tymu 1" << std::endl;
		arena.team1_add(std::move(mage));
		break;
	case 2:
		std::cout << mage.get_name() << " byl zarazen do tymu 2" << std::endl;
		arena.team2_add(std::move(mage));
		break;
	default:
		break;
	}
}

//void show_mage_stats(const Mage & mage);

void my_getline(std::istream & is, std::string & vstup) { // Potrebuju, aby na zacatku preskocil mezery a aby prvni pismeno bylo velke a ostatni male
	std::getline(is, vstup);
	while (vstup[0] == ' ')
		vstup.erase(0, 1);
	for (auto && ch : vstup)
		ch = tolower(ch);
	vstup[0] = toupper(vstup[0]);
}

Arena read_input( Knihovna & knihovna, Shop & shop)
{
	Arena arena;
	std::string vstup;
	std::cin >> vstup; // TODO: Ukonci to cteni na konci radky?
	while (vstup != "Fight") {
		if		(icompare(vstup, "help")) write_help();
		else if (icompare(vstup, "School")) knihovna.show_spells();
		else if (icompare(vstup, "Shop")) write_items(shop);
		else if (icompare(vstup, "Mage")) {					// Vytvor maga
			std::cin >> vstup; 
			Mage mage{ vstup };
			std::cout << mage.get_name() << " muze nyni navstivit knihovnu nebo obchod." << std::endl;
			std::cin >> vstup;
			while (!icompare(vstup, "Team")) {				// A dokud ho nezaradis do tymy, muzes ho upravovat
				if		(icompare(vstup, "help")) write_help();
				//else if (icompare(vstup, "Show")) show_mage_stats(mage);
				else if (icompare(vstup, "School")) knihovna.show_spells();
				else if (icompare(vstup, "Learn")) { my_getline(std::cin, vstup); mage.learn(knihovna.get_spell(vstup)); }
				else if (icompare(vstup, "Shop")) write_items(shop);
				else if (icompare(vstup, "Buy")) { 
					std::cin >> vstup; 
					if		(icompare(vstup, "weapon")) { my_getline(std::cin, vstup); mage.buy_weapon(shop.get_weapon(vstup)); } // TODO: Vyjimky, pokud spatne napisu jmeno (kouzla + vsechny predmety)
					else if (icompare(vstup, "robe")) { 
						my_getline(std::cin, vstup); 
						mage.buy_robe(shop.get_robe(vstup));
					}
					else std::cout << "Neznamy typ predmetu: >>" << vstup << "<<" << std::endl;
				}
				else std::cout << "Neznamy prikaz: >>" << vstup << "<<" << std::endl;
				std::cin >> vstup;
			}
			std::cin >> vstup;
			while (vstup != "1" && vstup != "2") {
				std::cout << "Napis cislo tymu: ";
				std::cin >> vstup;
			}
			team(arena, std::move(mage), std::stoi(vstup));
		}
		else std::cout << "Neznamy prikaz: >>" << vstup << "<<" << std::endl;
		std::cin >> vstup;
	}
	return arena;
}