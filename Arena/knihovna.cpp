#include "knihovna.hpp"

#include <iostream>
#include <random>

std::default_random_engine generator;
std::uniform_int_distribution<cislo> distribution(0, 100);

void report(const std::string & spell_name, const std::string & caster_name, const std::string & target_name) { // TODO: inline?
	std::cout << caster_name << " pouziva " << spell_name << " na " << target_name << std::endl;
}

// Ohniva magie
void Fire_magic::elemental_passive_(Mage & caster) {
	if (distribution(generator) < 25) {// 25% sance, ze se mag sam zapali a da si desetinu dmg
		caster.set_burn(3);
		std::cout << caster.get_name() << " podpalil sam sebe." << std::endl;
	}
}; // TODO: implementovat ohnivou passivku

cislo Fire_magic::calculate_damage_(Mage & caster, Mage & target) const {
	return (cislo)(damage_ * (1 + (double)caster.get_spell_power()/100) - (target.get_fire_resist() * damage_ / 100));
}

void Fireball::cast_( Mage & caster, Mage & target) {
	report(name_, caster.get_name(), target.get_name());
	target.get_health() -= calculate_damage(caster, target);
	elemental_passive(caster);
}

// Ledova magie
void Ice_magic::elemental_passive_(Mage & caster) {
	if (distribution(generator) < 50) {
		caster.set_frozen();
		std::cout << caster.get_name() << " se zmrazil a pristi kouzlo vykouzli o jedno kolo pozdeji." << std::endl;
	}
}

cislo Ice_magic::calculate_damage_(Mage & caster, Mage & target) const {
	return (cislo)(damage_ * (1 + (double)caster.get_spell_power() / 100) - (target.get_ice_resist() * damage_ / 100));
}

void Ice_lance::cast_( Mage & caster, Mage & target) {
	report(name_, caster.get_name(), target.get_name());
	target.get_health() -= calculate_damage(caster, target);
	elemental_passive(caster);
}
