#include "knihovna.hpp"

#include <iostream>

inline void report(const std::string & spell_name, const std::string & caster_name, const std::string & target_name) {
	std::cout << caster_name << " pouziva " << spell_name << " na " << target_name << std::endl;
}

// Ohniva magie
void Fire_magic::elemental_passive_() { std::cout << "Pouziva se ohniva passivka" << std::endl; }; // TODO: implementovat ohnivou passivku

void Fireball::cast_( Mage & caster, Mage & target) {
	report(name_, caster.get_name(), target.get_name());
	target.get_health() -= damage_;
	elemental_passive();
}

// Ledova magie
void Ice_magic::elemental_passive_() { std::cout << "Pouziva se ledova passivka" << std::endl; }

void Ice_lance::cast_( Mage & caster, Mage & target) {
	report(name_, caster.get_name(), target.get_name());
	target.get_health() -= damage_;
	elemental_passive();
}
