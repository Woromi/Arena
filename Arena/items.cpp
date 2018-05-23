#include "items.hpp"
#include "arena.hpp"

#include <fstream> // ifstream
#include <iostream>
#include <iomanip> // setw
#include <array>
#include <string>

bool item::buy( Mage & mage) const {
	if (mage.spend_money(price_)) {
		
		mage.add_health(health_);
		mage.set_max_health(mage.get_health());
		mage.add_health_regen(health_regen_);
		
		mage.add_mana(mana_);
		mage.set_max_mana(mage.get_mana());
		mage.add_mana_regen(mana_regen_);

		for (std::uint16_t i = 0; i < resistance_.size(); ++i)
			mage.add_resist(i, resistance_[i]);

		mage.add_spell_power(spell_power_);

		arena_.out << mage.get_name() << " si koupil " << name_ << std::endl
			<< "Zustatek: " << mage.get_money() << std::endl << std::endl;
		return true;
	}
	else {
		arena_.out << mage.get_name() << " je moc chudy na to, aby si mohl koupit " << this->name_ << std::endl
			       << "Zustatek: " << mage.get_money() << "(" << name_ << " stoji " << price_ << ")" << std::endl << std::endl;
		return false;
	}
}

void item::sell(Mage & mage) const { // Predpokladam, ze to bude volat pouze mag, ktery ten predmet vlastni (kontroluje se to v Mage.sell_item())
	mage.spend_money(-price_ / 2);

	mage.set_max_health(mage.get_max_health() - health_);
	mage.add_health_regen(-health_regen_);

	mage.set_max_mana(mage.get_max_mana() - mana_);
	mage.add_mana_regen(-mana_regen_);

	for (std::uint16_t i = 0; i < resistance_.size(); ++i)
		mage.add_resist(i, -resistance_[i]);

	mage.add_spell_power(-spell_power_);

	arena_.out << mage.get_name() << " prodal " << name_ << std::endl
		       << "Zustatek: " << mage.get_money() << std::endl << std::endl;
}

// Cteni vlastnosti vybaveni ze souboru
item::item( const Arena & arena, std::istream & ifs, std::string & name) : arena_{arena}, name_ { name }, health_{ 0 }, health_regen_{ 0 },
														mana_{ 0 }, mana_regen_{ 0 },
														spell_power_{ 0 } {
	resistance_.resize(spell_families::size, 0);
	std::string attribute;
	std::string value;
	std::getline(ifs, attribute, '=');
	std::getline(ifs, value);
	while (attribute != "") {
			 if (attribute == "price") price_ = std::stoi(value);
		else if (attribute == "health") health_ = std::stoi(value);
		else if (attribute == "health_regen") health_regen_ = std::stoi(value);
		else if (attribute == "mana") mana_ = std::stoi(value);
		else if (attribute == "mana_regen") mana_regen_ = std::stoi(value);
		else if (attribute == "fire_resistance") resistance_[spell_families::fire] = std::stoi(value);
		else if (attribute == "ice_resistance") resistance_[spell_families::ice] = std::stoi(value);
		else if (attribute == "spell_power") spell_power_ = std::stoi(value);
		else { throw std::exception("Takova vlastnost neexistuje."); }
		std::getline(ifs, attribute, '=');
		std::getline(ifs, value);
		}
}

// Nacti svoje zbozi ze souboru
Shop::Shop(const Arena & arena, const std::string & file_name) : arena_{arena} {
	std::ifstream ifs{ file_name };
	std::string line;
	while (ifs.good())
	{
		getline(ifs, line);
		
		// Zbrane
		if (line == "weapons") {
			getline(ifs, line);
			while (line != "") { // Dokud nenarazis na prazdnou radku
				std::string name = line;
				weapon_shop_.emplace(name, weapon{ arena_, ifs, name }); // Precte vsechny radky s vlastnostma a jeden prazdny potom (aby vedel kdy ma skoncit)
				getline(ifs, line);
			}
		}
		else if (line == "robes") {
			getline(ifs, line);
			while (line != "") { // Dokud nenarazis na prazdnou radku
				std::string name = line;
				robes_shop_.emplace(name, robe{ arena_, ifs, name });
				getline(ifs, line);
			}
		}
		else if (line == "hats") {
			getline(ifs, line);
			while (line != "") { // Dokud nenarazis na prazdnou radku
				std::string name = line;
				hats_shop_.emplace(name, hat{ arena_, ifs, name });
				getline(ifs, line);
			}
		}
	}
}



// Vypis zbozi obchodu
void item::show_stats(cislo odsazeni) const {
	arena_.out
		<< std::setw(odsazeni) << ""
		<< std::setw(30) << name_
		<< std::setw(10) << price_
		<< std::setw(10) << health_
		<< std::setw(10) << health_regen_
		<< std::setw(10) << mana_
		<< std::setw(10) << mana_regen_;
	for (std::uint16_t i = 0; i < resistance_.size(); ++i)
		arena_.out << std::setw(15) << resistance_[i];
	arena_.out << std::setw(15) << spell_power_
		<< std::endl;
}

void Shop::show_headline(std::ostream & out) const {
	std::array<std::string, spell_families::size + 1> elements{ "Fire", "Ice", "Dodefinuj me" };
	out << std::setw(odsazeni::o2) << ""
		<< std::setw(30) << "Name"
		<< std::setw(10) << "Price"
		<< std::setw(10) << "Health"
		<< std::setw(10) << "H regen"
		<< std::setw(10) << "Mana"
		<< std::setw(10) << "M regen";
	for (std::uint16_t i = 0; i < spell_families::size; ++i) {
		out << std::setw(8)
			<< elements[i] << " resist";
	}
	out << std::setw(15) << "Spell power"
		<< std::endl;
}

weapon * Shop::get_weapon( const std::string & name) { 
	if (weapon_shop_.find(name) != weapon_shop_.end())
		return &weapon_shop_.at(name);
	else 
		arena_.out << "Zbran s nazvem >>" << name << "<< nebyla nalezena" << std::endl;
	return nullptr;
}


robe * Shop::get_robe(const std::string & name) { 
	if (robes_shop_.find(name) != robes_shop_.end())
		return &robes_shop_.at(name);
	else
		arena_.out << "Roba s nazvem >>" << name << "<< nebyla nalezena" << std::endl;
	return nullptr;
}


hat * Shop::get_hat(const std::string & name) {
	if (hats_shop_.find(name) != hats_shop_.end())
		return &hats_shop_.at(name);
	else
		arena_.out << "Klobouk s nazvem >>" << name << "<< nebyl nalezena" << std::endl;
	return nullptr;
}