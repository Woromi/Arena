#include "knihovna.hpp"

#include <iostream> // cout
#include <iomanip> // setw
#include <random>

std::default_random_engine generator; // TODO: Nahoda neni zatim nahodna
std::uniform_int_distribution<cislo> distribution(0, 100);

void report(const std::string & spell_name, const std::string & caster_name, const std::string & target_name) { // TODO: inline?
	std::cout << caster_name << " pouziva " << spell_name << " na " << target_name << std::endl;
}

cislo Spell::calculate_damage(Mage & caster, Mage & target, spell_families f) const {
	target.get_resist().resize(f + 1); // TODO: Tohle se mi nelibi, je to proto, ze z maga nedokazu zjistit pocet elementu, ktere jsem v knihovne
	return (cislo)(damage_ * (1 + (double)caster.get_spell_power() / 100) * ((1 - target.get_resist()[f] / 100)));
}

void Spell::show_spell() const {
	std::cout
		<< std::setw(30) << name_
		<< std::setw(15) << damage_
		<< std::setw(15) << cost_
		<< std::setw(15) << casting_time_;
	switch (single_target_)
	{
	case true:
		std::cout << std::setw(15) << "Single enemy" << std::endl;
		break;
	case false:
		std::cout << std::setw(15) << "All enemies" << std::endl;
		break;
	}
}

Spell * Knihovna::get_spell(std::string spell) const { 
	if (spells.find(spell) != spells.end())
		return spells.at(spell).get();
	else
		std::cout << "Kouzlo s nazvem >>" << spell << "<< nebylo nalezeno" << std::endl;
	return nullptr;
}

void Knihovna::show_spells() const {
	std::cout
		<< std::setw(30) << "Name:"
		<< std::setw(15) << "Damage:"
		<< std::setw(15) << "Mana cost:"
		<< std::setw(15) << "Casting time:"
		<< std::setw(15) << "Target"
		<< std::endl;
	for (auto && spell : spells)
	{
		spell.second->show_spell();
	}
}





// Ohniva magie
void Fire_magic::elemental_passive_(Mage & caster) {
	if (distribution(generator) < 25) {// 25% sance, ze se mag sam zapali a da si desetinu dmg
		caster.set_burn(3);
		std::cout << caster.get_name() << " podpalil sam sebe." << std::endl;
	}
}; 

void Fireball::cast_( Mage & caster, Mage & target) {
	report(name_, caster.get_name(), target.get_name());
	target.get_health() -= calculate_damage(caster, target, spell_families::fire);
	elemental_passive(caster);
}






// Ledova magie
void Ice_magic::elemental_passive_(Mage & caster) {
	if (distribution(generator) < 50) {
		caster.set_frozen();
		std::cout << caster.get_name() << " se zmrazil a pristi kouzlo vykouzli o jedno kolo pozdeji." << std::endl;
	}
}

void Ice_lance::cast_( Mage & caster, Mage & target) {
	report(name_, caster.get_name(), target.get_name());
	target.get_health() -= calculate_damage(caster, target, spell_families::ice);
	elemental_passive(caster);
}