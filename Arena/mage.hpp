#ifndef mage_hpp
#define mage_hpp

#include "knihovna.hpp"
#include "equipement.hpp"

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
	Mage(std::string name) : name_{ name }, money_{ 1000 }, max_health_{ 500 }, health_regen_{ 5 }, max_mana_{ 500 }, mana_regen_{ 10 } {
		health_ = max_health_;
		mana_ = max_mana_;
	};

	void learn(Spell * spell) { kouzla_.emplace_back(spell); }
	void akce(team_container & enemy_team);
	void naplanuj_kouzlo() { pristi_kouzlo_ = kouzla_.end(); } // Je nutne mit na to funkci, protoze kdybych to udelal v konstruktoru, vadilo by mu move (ukazoval by pak na spatny container)

	// get a set
	cislo & get_health() { return health_; }
	const cislo & get_spell_power() const { return spell_power_; }
	std::vector<cislo> & get_resist() { return resistance_; } 
	const std::string & get_name() const { return name_; }
	void set_frozen() { frozen_ = true; }
	void set_burn(cislo pocet_kol) { burn_ = pocet_kol; }

	// buy and sell
	void buy(const vybaveni & v);
private:
	// Jmeno
	std::string name_;
	cislo money_;
	// Health a mana
	cislo health_;
	cislo max_health_;
	cislo health_regen_;
	cislo mana_;
	cislo max_mana_;
	cislo mana_regen_;
	// Resistance
	std::vector<cislo> resistance_;
	// Efekty
	bool frozen_ = false; // Zmrazeny zpomali casteni o jedno kolo
	cislo burn_ = 0; // Kazde kolo ubere 5 HP
	// Kouzleni
	cislo casting_time_;
	cislo spell_power_;
	// Kouzla
	kouzla_container kouzla_;
	kouzla_const_iterator pristi_kouzlo_;
	// Equipement
	vybaveni * weapon;
};

#endif // !mage_hpp