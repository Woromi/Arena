#include "mage.hpp"
#include "arena.hpp" // TODO: Je dobre includovat v cpp souborech?

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
	int odsazeni1 = 3, odsazeni2 = 6;
	arena_.out << name_ << std::endl;
	// Spells
	
	arena_.out << std::setw(odsazeni1) << "" << "Spells:" << std::endl;
	for (auto && k : kouzla_) k->show_spell();
	// Items
	arena_.out << std::setw(odsazeni1) << "" << "Items:" << std::endl
		<< std::setw(odsazeni2) << "" << "Weapon: ";
	if (weapon_ != nullptr)weapon_->show_stats();
	else arena_.out << "No weapon" << std::endl;
	arena_.out << std::setw(odsazeni2) << "" << "Robe: ";
	if (robe_ != nullptr) robe_->show_stats();
	else arena_.out << "No robe" << std::endl;
	// Stats
	arena_.out // TODO: Predelat staty do pole indexovaneho enum
		<< std::setw(odsazeni1) << "" << "Health: " << health_ << std::endl
		<< std::setw(odsazeni1) << "" << "Health regen: " << health_regen_ << std::endl
		<< std::setw(odsazeni1) << "" << "Mana: " << mana_ << std::endl
		<< std::setw(odsazeni1) << "" << "Mana regen: " << mana_regen_ << std::endl
		<< std::setw(odsazeni1) << "" << "Spell power: " << spell_power_ << std::endl;
	arena_.out << std::endl;
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

	if (pristi_kouzlo_ == kouzla_.end()) {// Je zacatek a jeste zadne kouzlo nemas vybrane, nebo jsi hloupy a neumis pouzivat zadne kouzlo (pokud jsi se ho zapomel naucit)
		pristi_kouzlo_ = kouzla_.begin();
		// Pokud mag neumi zadne kouzlo, basic attack
		if (pristi_kouzlo_ == kouzla_.end())
		{
			team_iterator target = enemy_team.begin();
			arena_.out << name_ << " neumi zadne kouzlo a proto se pokusil protivnika alespon bouchnout." << std::endl;
			target->second->add_health(-10);
		}
	}
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
	if (new_weapon != nullptr && weapon_ == nullptr && new_weapon->buy( *this)) // Pokud nemam zadnou zbran a muzu si to dovolit, zmen mu vlastnosti, a ...
	{
		weapon_ = new_weapon;	// Zapis si, ze si koupil tuhle zbran
		arena_.out << this->name_ << " si koupil " << weapon_->get_name() << std::endl;
	}
}

void Mage::sell_weapon() {
	if (weapon_ != nullptr) // Pokud ma nejakou zbran, prodej ji
	{
		weapon_->sell(*this);
		arena_.out << this->name_ << " prodal " << weapon_->get_name() << std::endl;
		weapon_ = nullptr;
	}
}

void Mage::buy_robe(const robe * new_robe) {
	if (new_robe != nullptr && robe_ == nullptr && new_robe->buy( *this)) // Kopirovani je castym zdrojem chyb
	{
		robe_ = new_robe;
		arena_.out << this->name_ << " si koupil " << robe_->get_name() << std::endl;
	}
}

void Mage::sell_robe() {
	if (robe_ != nullptr)
	{
		robe_->sell(*this);
		arena_.out << this->name_ << " prodal " << robe_->get_name() << std::endl;
		robe_ = nullptr;
	}
}