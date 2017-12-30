#include "mage.hpp"

#include <iostream>


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

	if (pristi_kouzlo_ == kouzla_.end()) // Je zacatek a jeste zadne kouzlo nemas vybrane
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
				(**pristi_kouzlo_).cast(*this, target->second);
			}
			// Jinak ho pouzij na vsechny
			else { 
				for (auto it = enemy_team.begin(); it != enemy_team.end(); ++it) {
					(**pristi_kouzlo_).cast(*this, it->second);
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
	if (new_weapon->buy(*this))
	{
		weapon_ = new_weapon;
		std::cout << this->name_ << " si koupil " << weapon_->get_name() << std::endl;
	}
}

void Mage::sell_weapon() {
	if (weapon_ != nullptr)
	{
		weapon_->sell(*this);
		std::cout << this->name_ << " prodal " << weapon_->get_name() << std::endl;
		weapon_ = nullptr;
	}
}

void Mage::buy_robe(robe * new_robe) {
	if (new_robe->buy(*this))
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