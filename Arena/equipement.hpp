#ifndef equipement_hpp
#define equipement_hpp

#include <string>
#include <map>
#include <vector>

using cislo = int;

struct vybaveni {
	vybaveni() {}; // TODO: Proc to po me chce default construktor???
	vybaveni(std::string name, cislo price, cislo health, cislo health_regen, cislo mana, cislo mana_regen, cislo fire_resist, cislo ice_resist, cislo spell_power) :
		name_{ name }, price_{ price }, // Item 
		health_{ health }, health_regen_{ health_regen }, // Health
		mana_{ mana }, mana_regen_{ mana_regen }, // Mana
		resistance_{fire_resist, ice_resist}, // Resist
		spell_power_{ spell_power } {}; // Spell power
	const std::string & get_name() const { return name_; }
	cislo get_price() const { return price_; }
	cislo get_health() const { return health_; }
	cislo get_health_regen() const { return health_regen_; }
	cislo get_mana() const { return mana_; }
	cislo get_mana_regen() const { return mana_regen_; }
	const std::vector<cislo> & get_resistance() const { return resistance_; }
	cislo get_spell_power() const { return spell_power_; }
private:
	std::string name_;
	cislo price_;

	cislo health_;
	cislo health_regen_;
	cislo mana_;
	cislo mana_regen_;
	
	std::vector<cislo> resistance_;

	cislo spell_power_;
};

struct Weapons {
public:
	Weapons() {
		zbrane_["Wooden staff"] = vybaveni{ "Wooden staff", 50, 0, 0, 0, 5, 0, 0, 10 };
		zbrane_["Wooden staff of fire"] = vybaveni{ "Wooden staff of fire", 100, 0, 0, 0, 5, 10, 0, 10 };
		zbrane_["Wooden staff of ice"] = vybaveni{ "Wooden staff of ice", 100, 0, 0, 0, 5, 0, 10, 10 };
	}
	const vybaveni * get_weapon(std::string name) { return &zbrane_.at(name); }
	//const std::map<std::string, vybaveni> & get_zbrane() { return zbrane_; }
private:
	std::map<std::string, vybaveni> zbrane_;
};

#endif // !equipement_hpp