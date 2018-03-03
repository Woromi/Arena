#include "read_input.hpp"

#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>

// Funkce pro porovnani stringu bez ohledu na velikost pismen prevzata z https://stackoverflow.com/questions/23943728/case-insensitive-standard-string-comparison-in-c
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

void write_help(std::ostream & out) { // TODO: Zarovnat text doleva
	out << std::setw(40) << "Mage name "<<"- zacne vytvaret noveho maga se jmenem 'name'"	<< std::endl	// Mage name
		<< std::setw(40) << "Library "<<"- vypise seznam kouzel, ktere se mag muze naucit"	<< std::endl	// School
		<< std::setw(40) << "Learn 'name' "<<"\t- nauci maga kouzlo se jmenem 'name'"		<< std::endl	// Learn spell_name
		<< std::setw(40) << "Shop "<<"- vypise seznam veci, ktere si mag muze koupit"		<< std::endl	// Shop
		<< std::setw(40) << "Buy weapon|robe|... 'name' "<<"\t- mag si koupi predmet se jmenem 'name'"		<< std::endl	// Buy item_name
		<< std::setw(40) << "Show "<<"- vypise aktualni vlastnost maga"					<< std::endl	// Show
		<< std::setw(40) << "Team [12] "<<"- ukonceni procesu vytvareni postavy a zarazeni maga do tymu [12]" << std::endl	// Team
		<< std::setw(40) << "Fight "<<"- zahaji souboj s vytvorenymi magy"					<< std::endl;	// Fight
}

void write_items(std::ostream & out, const Shop & shop) {
	shop.show_weapons(out);
	shop.show_robes(out);
	// TODO: Pridat dalsi druhy vybaveni
}

void team(Arena & arena, Mage mage, int i) { // Tady predavam hodnotou, budu presouvat vytvoreneho maga
	switch (i)
	{
	case 1:
		arena.out << mage.get_name() << " byl zarazen do tymu 1" << std::endl;
		arena.team1_add(std::move(mage));
		break;
	case 2:
		arena.out << mage.get_name() << " byl zarazen do tymu 2" << std::endl;
		arena.team2_add(std::move(mage));
		break;
	default:
		break;
	}
}

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
	arena.out << "Vytvorit noveho maga je mozne napsanim prikazu Mage 'jmeno'. Pro dalsi napovedu napis help. Na velikosti pismen nezalezi. " << std::endl;
	std::string vstup;
	arena.in >> vstup; // TODO: Ukonci to cteni na konci radky?
	while (!icompare(vstup, "Fight")) {
		if		(icompare(vstup, "help")) write_help(arena.out);
		else if (icompare(vstup, "Library")) knihovna.show_spells(arena.out);
		else if (icompare(vstup, "Shop")) write_items(arena.out, shop);
		else if (icompare(vstup, "Mage")) {					// Vytvor maga
			arena.in >> vstup; 
			Mage mage{ vstup };
			arena.out << mage.get_name() << " muze nyni navstivit knihovnu nebo obchod." << std::endl;
			arena.in >> vstup;
			while (!icompare(vstup, "Team")) {				// A dokud ho nezaradis do tymu, muzes ho upravovat
				if		(icompare(vstup, "help")) write_help(arena.out);
				else if (icompare(vstup, "Show")) mage.show_stats(arena.out);
				else if (icompare(vstup, "Library")) knihovna.show_spells(arena.out);
				else if (icompare(vstup, "Learn")) { my_getline(arena.in, vstup); mage.learn(arena.out, knihovna.get_spell(arena.out, vstup)); mage.show_stats(arena.out); }
				else if (icompare(vstup, "Shop")) write_items(arena.out, shop);
				else if (icompare(vstup, "Buy")) { 
					arena.in >> vstup; 
					if		(icompare(vstup, "weapon")) { my_getline(std::cin, vstup); mage.buy_weapon(arena.out, shop.get_weapon(arena.out, vstup)); } // TODO: Vyjimky, pokud spatne napisu jmeno (kouzla + vsechny predmety)
					else if (icompare(vstup, "robe")) { 
						my_getline(std::cin, vstup); 
						mage.buy_robe(arena.out, shop.get_robe(arena.out, vstup));
					}
					else arena.out << "Neznamy typ predmetu: >>" << vstup << "<<" << std::endl;
					mage.show_stats(arena.out);
				}
				else arena.out << "Neznamy prikaz: >>" << vstup << "<<" << std::endl;
				arena.in >> vstup;
			}
			arena.in >> vstup;
			while (vstup != "1" && vstup != "2") {
				arena.out << "Napis cislo tymu: ";
				arena.in >> vstup;
			}
			team(arena, std::move(mage), std::stoi(vstup));
		}
		else arena.out << "Neznamy prikaz: >>" << vstup << "<<" << std::endl;
		arena.in >> vstup;
	}
	return arena;
}