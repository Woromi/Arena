#ifndef mage_hpp
#define mage_hpp

#include "knihovna.hpp"

#include <string>
#include <vector>
#include <map> // Jenom kvuli team_containeru

class Spell; // Kvuli seznamu kouzel
class Mage; // Kvuli team_containeru
using cislo = int;
using team_container = std::multimap<cislo, Mage>;
using team_iterator = team_container::iterator;
using kouzla_container = std::vector<Spell *>;
using kouzla_const_iterator = kouzla_container::const_iterator;


class Mage {
public:
	Mage(std::string name) : name_{ name }, max_health_{ 500 }, health_regen_{ 5 }, max_mana_{ 500 }, mana_regen_{ 10 } {
		health_ = max_health_;
		mana_ = max_mana_;
	};

	void learn(Spell * spell) { kouzla_.emplace_back(spell); }
	void Akce(team_container & enemy_team);
	void naplanuj_kouzlo() { pristi_kouzlo_ = kouzla_.end(); } // Je nutne mit na to funkci, protoze kdybych to udelal v konstruktoru, vadilo by mu move (ukazoval by pak na spatny container)

	cislo & get_health() { return health_; }
	const std::string & get_name() const { return name_; }
private:
	std::string name_;
	cislo health_;
	cislo max_health_;
	cislo health_regen_;
	cislo mana_;
	cislo max_mana_;
	cislo mana_regen_;
	cislo casting_time_;
	kouzla_container kouzla_;
	kouzla_const_iterator pristi_kouzlo_;
};

#endif // !mage_hpp
