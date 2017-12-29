#include "mage.hpp"

void aktualizuj_hp(team_container & enemy_team, team_iterator & target) {
	cislo old_health = target->first;
	cislo new_health = target->second.get_health();
	if (new_health != old_health) { // TODO: Vymyslet to lepe - ted ma vyhodu zacinajici tym
		auto mag = std::move(target->second);
		enemy_team.erase(target);
		if (new_health > 0) // Pokud mag stale jeste zije
			enemy_team.emplace(new_health, std::move(mag));
	}
}

void Mage::Akce(team_container & enemy_team) {
	// Regenerace
	health_ += health_regen_;
	if (health_ > max_health_) health_ = max_health_;
	mana_ += mana_regen_;
	if (mana_ > max_mana_) mana_ = max_mana_;


	if (pristi_kouzlo_ == kouzla_.end()) // Je zacatek a jeste zadne kouzlo nemas vybrane
		pristi_kouzlo_ = kouzla_.begin();
	else // Pristi kouzlo je nejake kouzlo
	{
		// Postup v kouzleni (pokud mas dostatek many, zacni)
		if (mana_ >= (**pristi_kouzlo_).get_cost())
			++casting_time_;
		else // Kdyby jsi nahodou ztratil potrebnou manu, musis zacit odzacatku
			casting_time_ = 0; 

		// Pokud uz se pripravujes dostatecne dlouho, sesli kouzlo
		if (casting_time_ >= (**pristi_kouzlo_).get_casting_time())
		{
			// Pokud ma kouzlo jen jeden cil, pouzij ho na nejslabsiho maga
			if ((**pristi_kouzlo_).single_target()) { 
				team_iterator target = enemy_team.begin();
				(**pristi_kouzlo_).cast(*this, target->second);
				aktualizuj_hp(enemy_team, target);
			}
			// Jinak ho pouzij na vsechny
			else { 
				for (auto it = enemy_team.begin(); it != enemy_team.end(); ++it) {
					(**pristi_kouzlo_).cast(*this, it->second);
					aktualizuj_hp(enemy_team, it);
				}
			}

			// Priprav si dalsi kouzlo
			++pristi_kouzlo_;
			if (pristi_kouzlo_ == kouzla_.end()) pristi_kouzlo_ = kouzla_.begin();
			casting_time_ = 0;
		}
	}
	// TODO: Po utoku na maga se musim postarat o jeho presunuti v containeru
}