#include "arena.hpp"

#include <iostream>

void Arena::souboj() {
	time_ = 0;

	for (auto it = team1_.begin(); it != team1_.end(); ++it) {
		it->second.naplanuj_kouzlo();
	}
	for (auto it = team2_.begin(); it != team2_.end(); ++it) {
		it->second.naplanuj_kouzlo();
	}

	bool konec = false;
	while (!konec) {
		std::cout << std::endl << time_ << std::endl; // Vypis casu

		for (auto it = team1_.begin(); it != team1_.end(); ++it) {
			it->second.Akce(team2_);
		}
		for (auto it = team2_.begin(); it != team2_.end(); ++it) {
			it->second.Akce(team1_);
		}

		// Ukoncujici podminka
		if (team1_.size() == 0) {
			std::cout << "Vyhrava tym 2" << std::endl;
			konec = true;
		}
		if (team2_.size() == 0) {
			std::cout << "Vyhrava tym 1" << std::endl;
			konec = true;
		}

		++time_;
	}
}