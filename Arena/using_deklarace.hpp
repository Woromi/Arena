#ifndef using_deklarace_hpp
#define using_deklarace_hpp

#include <map>
#include <vector>
#include <memory>

// Vsude
using cislo = int;

// Arena + Mage
class Mage;
using team_container = std::multimap<cislo, std::shared_ptr<Mage>>; // Shared_ptr, abych mohl vytvorit kopii a z ni mazat mrtve magy
using team_iterator = team_container::iterator;

// Knihovna
enum spell_families { fire, ice, size }; // TODO: Opravit chyby z doby, kdy jsem neumel dat tohle do hlavickoveho souboru

// Mage
class Spell; // Kvuli seznamu kouzel
class Mage; // Kvuli team_containeru
class weapon; // Kvuli nakupu predmetu
class robe;

using kouzla_container = std::vector< const Spell *>;
using kouzla_const_iterator = kouzla_container::const_iterator;

#endif // !using_deklarace_hpp
