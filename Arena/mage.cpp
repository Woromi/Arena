#include "mage.hpp"

#include <iostream>
#include <iomanip> // setw


void Mage::learn( Spell * spell) { 
	if (spell != nullptr) {
		kouzla_.emplace_back(spell);
		std::cout << name_ << " se naucil pouzivat " << spell->get_name() << std::endl;
	}
}

void Mage::show_stats() {
	std::cout
		<< name_ << std::endl
		// Spells
		<< std::setw(20) << "Spells:" << std::endl;
	for (auto && k : kouzla_) k->show_spell();
	// Items
	std::cout
		<< std::setw(20) << "Items:" << std::endl
		<< std::setw(25) << "Weapon: ";
	if (weapon_ != nullptr)weapon_->show_stats();
	else std::cout << "No weapon" << std::endl;
	std::cout
		<< std::setw(25) << "Robe: ";
	if (robe_ != nullptr) robe_->show_stats();
	else std::cout << "No robe" << std::endl;
	// Stats
	std::cout // TODO: Predelat staty do pole indexovaneho enum
		<< "Health: " << health_ << std::endl
		<< "Health regen: " << health_regen_ << std::endl
		<< "Mana: " << mana_ << std::endl
		<< "Mana regen: " << mana_regen_ << std::endl
		<< "Spell power: " << spell_power_ << std::endl;
}

void Mage::akce( team_container & enemy_team) {
	// Regenerace
	health_ += health_regen_;
	if (health_ > max_health_) health_ = max_health_;
	mana_ += mana_regen_;
	if (mana_ > max_mana_) mana_ = max_mana_;

	// Burn
	if (burn_ > 0) {
		health_ -= 5;
		--burn_;
	}

	if (pristi_kouzlo_ == kouzla_.end()) // Je zacatek a jeste zadne kouzlo nemas vybrane, nebo jsi hloupy a neumis pouzivat zadne kouzlo (pokud jsi se ho zapomel naucit)
		pristi_kouzlo_ = kouzla_.begin();
	else // Pristi kouzlo je nejake kouzlo
	{
		// Postup v kouzleni (pokud mas dostatek many, zacni)
		if (mana_ >= (**pristi_kouzlo_).get_cost())
			if (!frozen_) ++casting_time_;
			else frozen_ = false;
		else // Kdyby jsi nahodou ztratil potrebnou manu, musis zacit odzacatku
			casting_time_ = 0; 

		// Pokud uz se pripravujes dostatecne dlouho, sesli kouzlo
		if (casting_time_ >= (**pristi_kouzlo_).get_casting_time())
		{
			// Pokud ma kouzlo jen jeden cil, pouzij ho na nejslabsiho maga
			if ((**pristi_kouzlo_).single_target()) {
				team_iterator target = enemy_team.begin();
				(**pristi_kouzlo_).calculate_damage(*this, *(target->second), spell_families::fire);
				(**pristi_kouzlo_).cast(*this, *(target->second));
			}
			// Jinak ho pouzij na vsechny
			else { 
				for (auto it = enemy_team.begin(); it != enemy_team.end(); ++it) {
					(**pristi_kouzlo_).cast(*this, *(it->second));
				}
			}

			// Priprav si dalsi kouzlo
			++pristi_kouzlo_;
			if (pristi_kouzlo_ == kouzla_.end()) pristi_kouzlo_ = kouzla_.begin();
			casting_time_ = 0;
		}
	}
}


// Nakupovani a prodavani predmetu
void Mage::buy_weapon(weapon * new_weapon) {
	if (new_weapon != nullptr && weapon_ == nullptr && new_weapon->buy(*this)) // Pokud nemam zadnou zbran a muzu si to dovolit, zmen mu vlastnosti, a ...
	{
		weapon_ = new_weapon;	// Zapis si, ze si koupil tuhle zbran
		std::cout << this->name_ << " si koupil " << weapon_->get_name() << std::endl;
	}
}

void Mage::sell_weapon() {
	if (weapon_ != nullptr) // Pokud ma nejakou zbran, prodej ji
	{
		weapon_->sell(*this);
		std::cout << this->name_ << " prodal " << weapon_->get_name() << std::endl;
		weapon_ = nullptr;
	}
}

void Mage::buy_robe(robe * new_robe) {
	if (new_robe != nullptr && robe_ == nullptr && new_robe->buy(*this)) // Kopirovani je castym zdrojem chyb
	{
		robe_ = new_robe;
		std::cout << this->name_ << " si koupil " << robe_->get_name() << std::endl;
	}
}

void Mage::sell_robe() {
	if (robe_ != nullptr)
	{
		robe_->sell(*this);
		std::cout << this->name_ << " prodal " << robe_->get_name() << std::endl;		
		robe_ = nullptr;
	}
}