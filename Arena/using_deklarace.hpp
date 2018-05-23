#ifndef using_deklarace_hpp
#define using_deklarace_hpp

#include <map>
#include <vector>
#include <memory>

// Vsude
using cislo = int;

// Vypis (globalni promenne - potrebuju je z vice mist a chci, aby byly vsude stejne)
static struct odsazeni {
	static const cislo o1 = 3;
	static const cislo o2 = 6;
	static const cislo o3 = 9;
};

// Arena + Mage
class Mage;
using team_container = std::multimap<cislo, std::shared_ptr<Mage>>; // Shared_ptr, abych mohl vytvorit kopii (a tedy hrat se stejnymi magy vice her) a z ni mazat mrtve magy
using team_iterator = team_container::iterator;

// Knihovna
enum spell_families { fire, ice, size };

// Mage
class Spell; // Kvuli seznamu kouzel
class Mage; // Kvuli team_containeru
class weapon; // Kvuli nakupu predmetu
class robe;
enum effects {	burn,	// Ubira 5 zivotu kazde kolo
				freeze, // Oddali kouzlo o 1 kolo
				count_of_effects };

using kouzla_container = std::vector< const Spell *>;
using kouzla_const_iterator = kouzla_container::const_iterator;

#endif // !using_deklarace_hpp
