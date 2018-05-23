#include "mage.hpp"
#include "arena.hpp"

#include <iostream>
#include <iomanip> // setw


void Mage::revive() {
	health_ = max_health_;
	mana_ = max_mana_;
}

void Mage::learn( const Spell * spell) { 
	if (spell != nullptr) {
		kouzla_.emplace_back(spell);
		arena_.out << name_ << " se naucil pouzivat " << spell->get_name() << std::endl;
	}
}

void Mage::show_stats() {
	arena_.out << name_ << std::endl;
	// Spells
	
	arena_.out << std::setw(odsazeni::o1) << "" << "Spells:" << std::endl;
	if (kouzla_.size() > 0)
		for (auto && k : kouzla_) k->show_spell(odsazeni::o2);
	else
		arena_.out << std::setw(odsazeni::o2) << "" << name_ << " can't cast any spells." << std::endl;
	// Items
	arena_.out << std::setw(odsazeni::o1) << "" << "Items:" << std::endl
		<< std::setw(odsazeni::o2) << "" << "Weapon: ";
	if (weapon_ != nullptr)weapon_->show_stats(0);
	else arena_.out << "No weapon" << std::endl;
	arena_.out << std::setw(odsazeni::o2) << "" << "Robe: ";
	if (robe_ != nullptr) robe_->show_stats(0);
	else arena_.out << "No robe" << std::endl;
	// Stats
	arena_.out 
		<< std::setw(odsazeni::o1) << "" << "Health: " << health_ << std::endl
		<< std::setw(odsazeni::o1) << "" << "Health regen: " << health_regen_ << std::endl
		<< std::setw(odsazeni::o1) << "" << "Mana: " << mana_ << std::endl
		<< std::setw(odsazeni::o1) << "" << "Mana regen: " << mana_regen_ << std::endl
		<< std::setw(odsazeni::o1) << "" << "Spell power: " << spell_power_ << std::endl;
	arena_.out << std::endl;
}

void Mage::akce( team_container & enemy_team) {
	// Regenerace
	health_ += health_regen_;
	if (health_ > max_health_) health_ = max_health_;
	mana_ += mana_regen_;
	if (mana_ > max_mana_) mana_ = max_mana_;

	// Burn
	if (efekty_[effects::burn] > 0) {
		health_ -= 5;
		--efekty_[effects::burn];
	}

	if (pristi_kouzlo_ == kouzla_.end()) {// Je zacatek a jeste zadne kouzlo nemas vybrane, nebo jsi hloupy a neumis pouzivat zadne kouzlo (pokud jsi se ho zapomel naucit)
		pristi_kouzlo_ = kouzla_.begin();
		// Pokud mag neumi zadne kouzlo, basic attack
		if (pristi_kouzlo_ == kouzla_.end())
		{
			team_iterator target = enemy_team.begin();
			arena_.out << std::setw(odsazeni::o2) << "" << name_ << " neumi zadne kouzlo a proto se pokusil protivnika alespon bouchnout." << std::endl;
			target->second->add_health(-10);
		}
	}
	else // Pristi kouzlo je nejake kouzlo
	{
		// Postup v kouzleni (pokud mas dostatek many, zacni)
		if (mana_ >= (**pristi_kouzlo_).get_cost())
			if (!efekty_[effects::freeze]) ++casting_time_;
			else efekty_[effects::freeze] = false;
		else // Kdyby jsi nahodou ztratil potrebnou manu, musis zacit odzacatku
			casting_time_ = 0; 

		// Pokud uz se pripravujes dostatecne dlouho, sesli kouzlo
		if (casting_time_ >= (**pristi_kouzlo_).get_casting_time())
		{
			// Pokud ma kouzlo jen jeden cil, pouzij ho na nejslabsiho maga
			if ((**pristi_kouzlo_).single_target()) {
				team_iterator target = enemy_team.begin();
				(**pristi_kouzlo_).cast( *this, *(target->second));
			}
			// Jinak ho pouzij na vsechny
			else { 
				for (auto it = enemy_team.begin(); it != enemy_team.end(); ++it) {
					(**pristi_kouzlo_).cast( *this, *(it->second));
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
void Mage::buy_weapon( const weapon * new_weapon) {
	// Pokud nemam zadnou zbran a muzu si to dovolit, zmen mu vlastnosti, a ...
	if (new_weapon != nullptr) { 
		if (weapon_ != nullptr) {
			sell_weapon();
		}
		if (new_weapon->buy(*this)) {
			weapon_ = new_weapon;	// Zapis si, ze si koupil tuhle zbran
		}
	}
}

void Mage::sell_weapon() {
	if (weapon_ != nullptr) // Pokud ma nejakou zbran, prodej ji
	{
		weapon_->sell(*this);
		weapon_ = nullptr;
	}
}

void Mage::buy_robe(const robe * new_robe) {
	if (new_robe != nullptr) { // Kopirovani je castym zdrojem chyb
		if (robe_ != nullptr)
			sell_robe();
		if (new_robe->buy(*this)) {
			robe_ = new_robe;
		}
	}
}

void Mage::sell_robe() {
	if (robe_ != nullptr)
	{
		robe_->sell(*this);
		robe_ = nullptr;
	}
}