#include "knihovna.hpp"
#include "arena.hpp"
#include <iomanip> // setw


void report(std::ostream & out, const std::string & spell_name, const std::string & caster_name, const std::string & target_name, cislo calculaded_dmg) {
	out << caster_name << " pouziva " << spell_name << " na " << target_name << " a ubira mu " << calculaded_dmg << " zivotu. " << std::endl;
}

cislo Spell::calculate_damage(Mage & caster, Mage & target, spell_families f) const {
	return (cislo)(damage_ * (1 + (double)caster.get_spell_power() / 100) * (1 - (double)target.get_resist(f) / 100)); // TODO: Vymyslet nejakou lepsi rovnici, tohle je dost provizorni
}

void Spell::show_spell() const {
	arena_.out
		<< std::setw(30) << name_
		<< std::setw(15) << damage_
		<< std::setw(15) << cost_
		<< std::setw(15) << casting_time_;
	switch (single_target_)
	{
	case true:
		arena_.out << std::setw(15) << "Single enemy" << std::endl;
		break;
	case false:
		arena_.out << std::setw(15) << "All enemies" << std::endl;
		break;
	}
}

Spell * Knihovna::get_spell( std::string spell) const { 
	if (spells.find(spell) != spells.end())
		return spells.at(spell).get();
	else
		arena_.out << "Kouzlo s nazvem >>" << spell << "<< nebylo nalezeno" << std::endl;
	return nullptr;
}

void Knihovna::show_spells_header() const {
	arena_.out
		<< std::setw(30) << "Name:"
		<< std::setw(15) << "Damage:"
		<< std::setw(15) << "Mana cost:"
		<< std::setw(15) << "Casting time:"
		<< std::setw(15) << "Target"
		<< std::endl;
}

void Knihovna::show_spells() const {
	show_spells_header();
	for (auto && spell : spells)
	{
		spell.second->show_spell();
	}
	arena_.out << std::endl;
}





// Ohniva magie
void Fire_magic::elemental_passive_( Mage & caster, Mage & target) const {
	if (arena_.distribution(arena_.generator) < 25) {// 25% sance, ze se mag sam zapali a da si desetinu dmg
		caster.set_burn(3);
		arena_.out << caster.get_name() << " podpalil sam sebe." << std::endl;
	}
	if (arena_.distribution(arena_.generator) < 25) {// 25% sance, ze bude podpalen protivnik da si desetinu dmg
		target.set_burn(3);
		arena_.out << target.get_name() << " byl podpalen. " << std::endl;
	}
}; 

void Fire_magic::cast_( Mage & caster, Mage & target) const { 
	cislo calculated_dmg = calculate_damage(caster, target, spell_families::fire);
	report(arena_.out, name_, caster.get_name(), target.get_name(), calculated_dmg);
	target.add_health(-calculated_dmg);
	elemental_passive( caster, target);
}





// Ledova magie
void Ice_magic::elemental_passive_( Mage & caster, Mage & target) const {
	if (arena_.distribution(arena_.generator) < 50) {
		caster.set_frozen();
		arena_.out << caster.get_name() << " se zmrazil a pristi kouzlo vykouzli o jedno kolo pozdeji." << std::endl;
	}
	if (arena_.distribution(arena_.generator) < 50) {
		target.set_frozen();
		arena_.out << target.get_name() << " byl zmrazen a pristi kouzlo vykouzli o jedno kolo pozdeji." << std::endl;
	}
}

void Ice_magic::cast_( Mage & caster, Mage & target) const {
	cislo calculated_damage = calculate_damage(caster, target, spell_families::ice);
	report(arena_.out, name_, caster.get_name(), target.get_name(), calculated_damage);
	target.add_health(-calculated_damage);
	elemental_passive( caster, target);
}