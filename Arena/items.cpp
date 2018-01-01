#include "items.hpp"

#include <fstream> // ifstream
#include <iostream> // cout
#include <iomanip> // setw
#include <array>
#include <string>

bool item::buy(Mage & mage) {
	if (mage.get_money() >= price_) {
		mage.get_money() -= price_;

		mage.get_health() += health_;
		mage.get_max_health() += health_;
		mage.get_health_regen() += health_regen_;
		
		mage.get_mana() += mana_;
		mage.get_max_mana() += mana_;
		mage.get_mana_regen() += mana_regen_;

		auto & mage_resist = mage.get_resist();
		mage_resist.resize(resistance_.size(), 0);
		for (std::uint16_t i = 0; i < resistance_.size(); ++i)
			mage_resist[i] += resistance_[i];

		mage.get_spell_power() += spell_power_;
		return true;
	}
	else {
		std::cout << mage.get_name() << " je moc chudy na to, aby si mohl koupit " << this->name_ << std::endl;
		return false;
	}
}

void item::sell(Mage & mage) { // Predpokladam, ze to bude volat pouze mag, ktery ten predmet vlastni (kontroluje se to v Mage.sell_item())
	mage.get_money() += price_ / 2;

	mage.get_health() -= health_;
	mage.get_max_health() -= health_;
	mage.get_health_regen() -= health_regen_;

	mage.get_mana() -= mana_;
	mage.get_max_mana() -= mana_;
	mage.get_mana_regen() -= mana_regen_;

	auto & mage_resist = mage.get_resist();
	for (std::uint16_t i = 0; i < resistance_.size(); ++i)
		mage_resist[i] -= resistance_[i];

	mage.get_spell_power() -= spell_power_;

}

// Cteni vlastnosti vybaveni ze souboru
item::item(std::ifstream & ifs, std::string & name) : name_{ name }, health_{ 0 }, health_regen_{ 0 },
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
Shop::Shop(const std::string & file_name) {
	std::ifstream ifs{ file_name };
	std::string line;
	while (ifs.good()) // TODO: Vymyslet sem lepsi podminku
	{
		getline(ifs, line);
		
		// Zbrane
		if (line == "weapons") {
			getline(ifs, line);
			while (line != "") { // Dokud nenarazis na prazdnou radku
				std::string name = line;
				weapon_shop_.emplace(name, weapon{ ifs, name }); // Precte vsechny radky s vlastnostma a jeden prazdny potom (aby vedel kdy ma skoncit)
				getline(ifs, line);
			}
		}
		else if (line == "robes") {
			getline(ifs, line);
			while (line != "") { // Dokud nenarazis na prazdnou radku
				std::string name = line;
				robes_shop_.emplace(name, robe{ ifs, name });
				getline(ifs, line);
			}
		}
	}
}



// Vypis zbozi obchodu
void item::show_stats() const {
	std::cout
		<< std::setw(30) << name_
		<< std::setw(15) << health_
		<< std::setw(15) << health_regen_
		<< std::setw(15) << mana_
		<< std::setw(15) << mana_regen_;
	for (std::uint16_t i = 0; i < resistance_.size(); ++i)
		std::cout << std::setw(15) << resistance_[i];
	std::cout
		<< std::setw(15) << spell_power_
		<< std::setw(20) << price_
		<< std::endl;
}

void show_headline() {
	std::array<std::string, spell_families::size + 1> elements{ "Fire", "Ice", "Dodefinuj me v equipement.cpp" };
	std::cout
		<< std::setw(30) << "Name"
		<< std::setw(15) << "Health"
		<< std::setw(15) << "Health regen"
		<< std::setw(15) << "Mana"
		<< std::setw(15) << "Mana regen";
	for (std::uint16_t i = 0; i < spell_families::size; ++i) {
		std::cout << std::setw(8)
			<< elements[i] << " resist";
	}
	std::cout
		<< std::setw(15) << "Spell power"
		<< std::setw(20) << "Price"
		<< std::endl;
}

void Shop::show_weapons() const {
	std::cout << "Weapons:" << std::endl;
	show_headline();
	for (auto && item : weapon_shop_) {
		item.second.show_stats();
	}
}

void Shop::show_robes() const {
	std::cout << "Robes:" << std::endl;
	show_headline();
	for (auto && item : robes_shop_) {
		item.second.show_stats();
	}
}

weapon * Shop::get_weapon(const std::string & name) { 
	if (weapon_shop_.find(name) != weapon_shop_.end())
		return &weapon_shop_.at(name);
	else 
		std::cout << "Zbran s nazvem >>" << name << "<< nebyla nalezena" << std::endl;
	return nullptr;
}


robe * Shop::get_robe(const std::string & name) { 
	if (robes_shop_.find(name) != robes_shop_.end())
		return &robes_shop_.at(name);
	else
		std::cout << "Roba s nazvem >>" << name << "<< nebyla nalezena" << std::endl;
	return nullptr;
}