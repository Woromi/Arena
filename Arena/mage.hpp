#ifndef mage_hpp
#define mage_hpp

#include "knihovna.hpp"
#include "items.hpp"

#include <string>
#include <vector>
#include <map> // Jenom kvuli team_containeru

// TODO: Potrebuju tam ty deklarace, kdyz jsem presunul using do samostatne hlavicky?
// Dopredne deklarace
class Spell; // Kvuli seznamu kouzel
class Mage; // Kvuli team_containeru
class weapon; // Kvuli nakupu predmetu
class robe;

// Mage
class Mage {
public:
	Mage(std::string name) : name_{ name }, money_{ 1000 }, max_health_{ 500 }, health_regen_{ 5 }, max_mana_{ 500 }, mana_regen_{ 10 } {
		health_ = max_health_;
		mana_ = max_mana_;
	};

	void learn( Spell * spell);
	void akce(team_container & enemy_team);
	void naplanuj_kouzlo() { pristi_kouzlo_ = kouzla_.end(); } // Je nutne mit na to funkci, protoze kdybych to udelal v konstruktoru, vadilo by mu move (ukazoval by pak na spatny container)
	void show_stats();

	// get a set
	cislo & get_health() { return health_; }
	cislo & get_max_health() { return max_health_; }
	cislo & get_health_regen() { return health_regen_; }
	cislo & get_mana() { return mana_; }
	cislo & get_max_mana() { return max_mana_; }
	cislo & get_mana_regen() { return mana_regen_; }
	cislo & get_money() { return money_; }
 	cislo & get_spell_power() { return spell_power_; }
	std::vector<cislo> & get_resist() { return resistance_; } 
	const std::string & get_name() const { return name_; }
	void set_frozen() { frozen_ = true; }
	void set_burn(cislo pocet_kol) { burn_ = pocet_kol; }

	// buy a sell
	void buy_weapon(weapon * new_weapon);
	void sell_weapon();
	void buy_robe(robe * new_robe);
	void sell_robe();

	// Pouze na prohlizeni
	weapon * get_weapon() const { return weapon_; }
	robe * get_robe() const { return robe_; }
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
	weapon * weapon_;
	robe * robe_;
};

#endif // !mage_hpp
