#ifndef arena_hpp
#define arena_hpp

#include "mage.hpp"

#include <map>

using team_container = std::multimap<cislo, Mage>;
using team_iterator = team_container::iterator;

class Arena {
public:
	void team1_add(Mage m) { team1_.emplace(m.get_health(), m); }
	void team2_add(Mage m) { team2_.emplace(m.get_health(), m); }
	void souboj();
private:
	cislo time_;
	team_container team1_;
	team_container team2_;
};

#endif // ! arena_hpp
