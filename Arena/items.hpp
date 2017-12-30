#ifndef equipement_hpp
#define equipement_hpp

#include  "mage.hpp" // Vybaveni pri nakupu umi menit vlastnosti maga

#include <string>
#include <map>
#include <vector>
#include <fstream>

using cislo = int;

class Mage;

class item {
public:
	virtual ~item() {};
	item(std::ifstream & ifs, std::string & name);
	bool buy(Mage & mage);
	void sell(Mage & mage);
	void show_stats() const;
	// get
	const std::string & get_name() const { return name_; }
	cislo get_price() const { return price_; }
	cislo get_health() const { return health_; }
	cislo get_health_regen() const { return health_regen_; }
	cislo get_mana() const { return mana_; }
	cislo get_mana_regen() const { return mana_regen_; }
	const std::vector<cislo> & get_resistance() const { return resistance_; }
	cislo get_spell_power() const { return spell_power_; }
protected:
	std::string name_;
	cislo price_;

	cislo health_;
	cislo health_regen_;
	cislo mana_;
	cislo mana_regen_;

	std::vector<cislo> resistance_;

	cislo spell_power_;
};

class weapon : public item {
	using item::item;
}; // TODO: Ma vytvoreni "zbytecneho" potomka nejake nevyhody?

class robe: public item {
	using item::item;
};






struct Weapons {
public:
	friend struct Shop;
	weapon * get_weapon(const std::string & name) { return &weapons_.at(name); }
	void show_weapons() const;
private:
	std::map<std::string, weapon> weapons_; // TODO: Je spravne to delat pres unique_ptr?
};

struct Robes {
public:
	friend struct Shop;
	robe * get_robe(const std::string & name) { return &robes_.at(name); }
	void show_robes() const;
private:
	std::map<std::string, robe> robes_;
};

struct Shop {
public:
	Shop(const std::string & file_name);
	weapon * get_weapon(const std::string & name) { return weapon_shop_.get_weapon(name); }
	robe * get_robe(const std::string & name) { return robes_shop_.get_robe(name); }
	// Vypis zbozi na cout
	void show_weapons() const { weapon_shop_.show_weapons(); }
	void show_robes() const { robes_shop_.show_robes(); }
private:
	Weapons weapon_shop_;
	Robes robes_shop_;
};

#endif // !equipement_hpp