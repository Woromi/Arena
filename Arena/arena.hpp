#ifndef arena_hpp
#define arena_hpp

#include "mage.hpp"
#include "using_deklarace.hpp"

#include <map>
#include <memory>
#include <random>
#include <iostream>

class Mage;

class Arena {
public:
	void team1_add(std::unique_ptr<Mage> m) { team1_.insert(std::make_pair(m->get_health(), std::move(m))); }
	void team2_add(std::unique_ptr<Mage> m) { team2_.insert(std::make_pair(m->get_health(), std::move(m))); }
	void souboj();

	std::default_random_engine generator; // TODO: Nahoda neni zatim nahodna
	std::uniform_int_distribution<cislo> distribution{ 0, 100 };
	std::ostream & out = std::cout;
	std::istream & in = std::cin;
private:
	cislo time_;
	team_container team1_;
	team_container team2_;
};

#endif // ! arena_hpp
