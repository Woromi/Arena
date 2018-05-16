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

	// Kopie tymu, aby bylo momzne souboj zopakovat
	team_container team1_f{ team1_ };
	team_container team2_f{ team2_ };

	bool konec = false;
	while (!konec) {
		out << std::endl << time_ << ". kolo" << std::endl; // Vypis casu

		for (auto it = team1_f.begin(); it != team1_f.end(); ++it) { // TODO: Kdybych chtel delat kouzla, co zerou manu, byl by druhy tym znevyhodnen
			(*it->second).akce( team2_f);
		}
		for (auto it = team2_f.begin(); it != team2_f.end(); ++it) {
			(*it->second).akce( team1_f);
		}

		for (auto it = team1_f.begin(); it != team1_f.end(); ++it) {
			if (aktualizuj_hp(out, team1_f, it)) it = team1_f.begin(); // Po zmene zacni odznova (hloupe, ale nenapadlo me nic lepsiho a team nebude nikdy tak velky, aby mi to vadilo)
			if (it == team1_f.end()) break;
		}
		for (auto it = team2_f.begin(); it != team2_f.end(); ++it) {
			if (aktualizuj_hp(out, team2_f, it)) it = team2_f.begin(); // Po zmene zacni odznova (hloupe, ale nenapadlo me nic lepsiho a team nebude nikdy tak velky, aby mi to vadilo)
			if (it == team2_f.end()) break;
		}

		// Ukoncujici podminka
		if (team1_f.size() == 0 && team2_f.size() == 0) {
			out << "Vsichni umreli. Je to nerozhodne. " << std::endl;
			konec = true;
		}
		else if (team1_f.size() == 0) {
			out << "Vyhrava tym 2" << std::endl;
			konec = true;
		}
		else if (team2_f.size() == 0) {
			out << "Vyhrava tym 1" << std::endl;
			konec = true;
		}

		++time_;
	}

	for (auto it = team1_.begin(); it != team1_.end(); ++it) {
		(*it->second).revive(); // Zacne ukazovat na konec seznamu naucenych kouzel
	}
	for (auto it = team2_.begin(); it != team2_.end(); ++it) {
		(*it->second).revive();
	}
}