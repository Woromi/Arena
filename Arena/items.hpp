#ifndef equipement_hpp
#define equipement_hpp

#include "mage.hpp" // Vybaveni pri nakupu umi menit vlastnosti maga
#include "using_deklarace.hpp"

#include <string>
#include <map>
#include <vector>
#include <fstream>

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






struct Shop {
public:
	Shop(const std::string & file_name);

	// Zakaz kopirovani a move
	Shop(const Shop &) = delete;
	Shop(Shop &&) = default;
	Shop & operator=(const Shop &) = delete;
	Shop & operator=(Shop &&) = default;
	~Shop() = default;

	weapon * get_weapon(const std::string & name);
	robe * get_robe(const std::string & name);
	// Vypis zbozi na cout
	void show_weapons() const;
	void show_robes() const;
private:
	std::map<std::string, weapon> weapon_shop_;
	std::map<std::string, robe> robes_shop_;
};

#endif // !equipement_hpp