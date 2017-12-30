#include "read_input.hpp"

#include <iostream>
#include <string>
#include <cctype>

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

void write_help() {
	std::cout
		<< "Mage name \t- zacne vytvaret noveho maga se jmenem 'name'"	// Mage name
		<< "School \t- vypise seznam kouzel, ktere se mag muze naucit"	// School
		<< "\tLearn 'name' \t nauci maga kouzlo se jmenem 'name'"		// Learn spell_name
		<< "Shop \t- vypise seznam veci, ktere si mag muze koupit"		// Shop
		<< "\tBuy 'name' \t- mag si koupi predmet se jmenem 'name'";	// Buy item_name
}

void write_spells() {}

void write_items() {}

void read_input()
{
	std::string vstup;
	std::cin >> vstup;
	if (icompare(vstup, "help")) {
		write_help();
	}
	else if (icompare(vstup, "School")) {
		write_spells();
	}
	else if (icompare(vstup, "Shop")) {
		write_items();
	}
}