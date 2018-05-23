#ifndef equipement_hpp
#define equipement_hpp

#include "mage.hpp" // Vybaveni pri nakupu umi menit vlastnosti maga
#include "using_deklarace.hpp"

#include <string>
#include <map>
#include <vector>
#include <fstream>

class Mage;
class Arena;

class item {
public:
	virtual ~item() {};
	item(const Arena & arena, std::istream & ifs, std::string & name);
	bool buy( Mage & mage) const;
	void sell(Mage & mage) const;
	void show_stats(cislo odsazeni) const;
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
	const Arena & arena_;
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
};

class robe: public item {
	using item::item;
};

class hat : public item {
	using item::item;
};


struct Shop {
public:
	Shop( const Arena & arena, const std::string & file_name);

	// Zakaz kopirovani a move
	Shop(const Shop &) = delete;
	Shop(Shop &&) = default;
	Shop & operator=(const Shop &) = delete;
	Shop & operator=(Shop &&) = default;
	~Shop() = default;

	weapon * get_weapon(const std::string & name);
	robe * get_robe(const std::string & name);
	hat * get_hat(const std::string & name);

	// Vypis zbozi urciteho druhu
	template<typename item_type>
	void show_items(std::string type_name, std::map<std::string, item_type> shop) const {
		arena_.out << std::setw(odsazeni::o1) << "" << type_name << ":" << std::endl;
		show_headline(arena_.out);
		for (auto && item : shop) {
			item.second.show_stats(odsazeni::o2);
		}
		arena_.out << std::endl;
	}

	auto get_weapons() const { return weapon_shop_; }
	auto get_robes() const { return robes_shop_; }
	auto get_hats() const { return hats_shop_; }
private:
	void show_headline(std::ostream & out) const;

	const Arena & arena_;
	std::map<std::string, weapon> weapon_shop_;
	std::map<std::string, robe> robes_shop_;
	std::map<std::string, hat> hats_shop_;
};

#endif // !equipement_hpp