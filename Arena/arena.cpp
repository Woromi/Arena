#include "arena.hpp"

#include <iostream>


bool aktualizuj_hp(std::ostream & out, team_container & team, team_iterator & target) {
	cislo old_health = target->first;
	cislo new_health = (*target->second).get_health();
	bool zmena = new_health != old_health;
	if (zmena) { // TODO: Vymyslet to lepe - ted ma vyhodu zacinajici tym
		auto mag = std::move(target->second);
		team.erase(target);
		if (new_health > 0) // Pokud mag stale jeste zije
			team.emplace(new_health, std::move(mag));
		else
			out << (*mag).get_name() << " umrel" << std::endl;
	}
	return zmena;
}


void Arena::souboj() {
	time_ = 0;

	for (auto it = team1_.begin(); it != team1_.end(); ++it) {
		(*it->second).naplanuj_kouzlo(); // Zacne ukazovat na konec seznamu naucenych kouzel
	}
	for (auto it = team2_.begin(); it != team2_.end(); ++it) {
		(*it->second).naplanuj_kouzlo();
	}

	bool konec = false;
	while (!konec) {
		out << std::endl << time_ << ". kolo" << std::endl; // Vypis casu

		for (auto it = team1_.begin(); it != team1_.end(); ++it) { // TODO: Kdybych chtel delat kouzla, co zerou manu, byl by druhy tym znevyhodnen
			(*it->second).akce( team2_);
		}
		for (auto it = team2_.begin(); it != team2_.end(); ++it) {
			(*it->second).akce( team1_);
		}

		for (auto it = team1_.begin(); it != team1_.end(); ++it) {
			if (aktualizuj_hp(out, team1_, it)) it = team1_.begin(); // Po zmene zacni odznova (hloupe, ale nenapadlo me nic lepsiho a team nebude nikdy tak velky, aby mi to vadilo)
			if (it == team1_.end()) break;
		}
		for (auto it = team2_.begin(); it != team2_.end(); ++it) {
			if (aktualizuj_hp(out, team2_, it)) it = team2_.begin(); // Po zmene zacni odznova (hloupe, ale nenapadlo me nic lepsiho a team nebude nikdy tak velky, aby mi to vadilo)
			if (it == team2_.end()) break;
		}

		// Ukoncujici podminka
		if (team1_.size() == 0 && team2_.size() == 0) {
			out << "Vsichni umreli. Je to nerozhodne. " << std::endl;
			konec = true;
		}
		else if (team1_.size() == 0) {
			out << "Vyhrava tym 2" << std::endl;
			konec = true;
		}
		else if (team2_.size() == 0) {
			out << "Vyhrava tym 1" << std::endl;
			konec = true;
		}

		++time_;
	}
}