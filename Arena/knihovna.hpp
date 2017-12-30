#ifndef knihovna_hpp
#define knihovna_hpp

#include "mage.hpp" // Je spravne includovat dva soubory navzajem? 

#include <map>
#include <string>
#include <memory>

class Mage;

using cislo = int;

enum spell_families { fire, ice, size };

class Spell { // Primarne je mysleno jako kouzlo, ale je mozne pridat napr. tridu kouzel "jaderna fyzika" a jeji potomek napr. "neutronovy kanon"
public:
	virtual ~Spell() {};
	Spell(std::string name, cislo damage, cislo cost, cislo casting_time, bool single_target) : name_{ name }, damage_{ damage }, cost_{ cost }, casting_time_{ casting_time }, single_target_{single_target} {};
	void cast( Mage & caster, Mage & target) { cast_( caster, target); } // Chci menit maga -> nekonstantni reference
	void elemental_passive(Mage & caster) { elemental_passive_(caster); };
	cislo calculate_damage(Mage & caster, Mage & target, spell_families) const;
	void show_spell() const;
	// get a set
	std::string get_name() const { return name_; }
	cislo get_damage() const { return damage_; }
	cislo get_cost() const { return cost_; }
	cislo get_casting_time() const { return casting_time_; }
	bool single_target() const { return single_target_; }
protected:
	std::string name_;
	cislo damage_;
	cislo cost_;
	cislo casting_time_;
	bool single_target_;
private:
	virtual void cast_( Mage & caster, Mage & target) {} // Chci menit maga -> nekonstantni reference
	virtual void elemental_passive_(Mage & caster) {};
};

// Ohniva magie
class Fire_magic : public Spell {
public:
	using Spell::Spell; // Konstruktor zdedeny od predka
private:
	virtual void elemental_passive_(Mage & caster) override;
};

class Fireball : public Fire_magic {
public:
	using Fire_magic::Fire_magic;
private:
	virtual void cast_( Mage & caster, Mage & target) override;
};

// Ledova magie
class Ice_magic : public Spell {
public:
	using Spell::Spell;
private:
	virtual void elemental_passive_(Mage & caster) override;
};

class Ice_lance : public Ice_magic {
public:
	using Ice_magic::Ice_magic;
private:
	virtual void cast_( Mage & caster, Mage & target) override;
};







using PtrSpell = std::unique_ptr<Spell>;
using MapKnihovna = std::map<std::string, PtrSpell>;

// Knihovna - jsou v ni ulozeny vsechny spelly. Hrac, ktery se nauci kouzlo se nauci jenom odkaz do teto knihovny
struct Knihovna {
	Knihovna() {										//	Name			Damage	Cost	Casting_time	Single_target
		spells["Fireball"] = std::make_unique<Fireball>(	"Fireball",		100,	90,		5,				true);
		spells["Ice lance"] = std::make_unique<Ice_lance>(	"Ice lance",	30,		40,		1,				true);
	}
	Spell * get_spell(std::string spell) const;
	void show_spells() const;
	//const MapKnihovna & get_spells() const { return Spells; }
private:
	MapKnihovna spells;
};


#endif // !knihovna_hpp