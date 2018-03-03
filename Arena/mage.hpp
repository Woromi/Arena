#ifndef mage_hpp
#define mage_hpp

#include "knihovna.hpp"
#include "items.hpp"

#include <string>
#include <vector>
#include <map> // Jenom kvuli team_containeru

// TODO: Potrebuju tam ty deklarace, kdyz jsem presunul using do samostatne hlavicky?
// Dopredne deklarace
class Spell; 
class weapon;
class robe;

// Mage
class Mage {
public:
	Mage(std::string name) : name_{ name }, money_{ 1000 }, max_health_{ 500 }, health_regen_{ 5 }, max_mana_{ 500 }, mana_regen_{ 10 } {
		resistance_.resize(spell_families::size);
		health_ = max_health_;
		mana_ = max_mana_;
	};

	// Zakaz kopirovani a move
	Mage(const Mage &) = delete;
	Mage(Mage &&) = default;
	Mage & operator=(const Mage &) = delete;
	Mage & operator=(Mage &&) = default;
	~Mage() = default;

	void learn(Spell * spell);
	void akce(team_container & enemy_team);
	void naplanuj_kouzlo() { pristi_kouzlo_ = kouzla_.end(); } // Je nutne mit na to funkci, protoze kdybych to udelal v konstruktoru, vadilo by mu move (ukazoval by pak na spatny container)
	void show_stats();

	// get a set
	// Health
	void add_health(cislo value) { health_ += value; }
	cislo get_health() const { return health_; }
	// Max health
	void set_max_health(cislo value) { if (value > 0) { if (value >= health_) max_health_ = value; else { max_health_ = value; health_ = value; } } }
	cislo get_max_health() { return max_health_; }
	// Health regen
	void add_health_regen(cislo value) { if (health_regen_ + value >= 0) health_regen_ += value; }
	cislo get_health_regen() const { return health_regen_; }
	// Mana
	void add_mana(cislo value) { if (mana_ + value > 0) mana_ += value; }
	cislo get_mana() const { return mana_; }
	// Max mana
	void set_max_mana(cislo value) { if (value > 0) { if (value >= mana_) max_mana_ = value; else { max_mana_ = value; mana_ = value; } } }
	cislo get_max_mana() const { return max_mana_; }
	// Mana regen
	void add_mana_regen(cislo value) { if (mana_regen_ + value >= 0) mana_regen_ += value; }
	cislo get_mana_regen() const { return mana_regen_; }
	// Money
	bool spend_money(cislo price) { if (money_ - price >= 0) { money_ -= price; return true; } else return false; }
	// Spell power
	void add_spell_power(cislo value) { if (spell_power_ + value >= 0) spell_power_ += value; }
	cislo get_spell_power() const { return spell_power_; }
	// resistance
	void add_resist(cislo index, cislo value) { if (resistance_[index] + value >= 0) resistance_[index] += value; }
	cislo get_resist(cislo index) const { return resistance_[index]; }
	
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
