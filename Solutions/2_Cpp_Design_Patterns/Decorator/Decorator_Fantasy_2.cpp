/**************************************************************************************************
*
* \file Decorator_Fantasy.cpp
* \brief C++ Training - Programming Task for the Decorator Design Pattern
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Help the knight "Roland" to win against the dragon "Darksmoke" by conjuring helpful
*         magical equipment (e.g. 'IceEnchantment', 'StrengthEnchantment', 'MagicShield',
*         'ShoesOfAgility', or 'MagicShackles'). Note that you are only allowed to add new
*         code, but not to modify existing code.
*
* Step 2: Refactor the classic Decorator solution by a value semantics based solution. Note that
*         the general behavior should remain unchanged.
*
* Step 3: Discuss the interface segregation of the 'Weapon', 'Armor', and 'Gear' classes: what
*         are the benefits and drawbacks of separating the 'attack()', 'defense()', and 'speed()'
*         functions?
*
**************************************************************************************************/


//---- <Stats.h> ----------------------------------------------------------------------------------

#include <ostream>

struct Attack
{
   int value;

   operator int() const { return value; }

   friend Attack operator+( Attack lhs, Attack rhs )
   {
      return Attack{ lhs.value + rhs.value };
   }

   friend Attack operator-( Attack lhs, Attack rhs )
   {
      return Attack{ lhs.value - rhs.value };
   }

   friend std::ostream& operator<<( std::ostream& os, Attack attack )
   {
      return os << attack.value;
   }
};


struct Defense
{
   int value;

   operator int() const { return value; }

   friend Defense operator+( Defense lhs, Defense rhs )
   {
      return Defense{ lhs.value + rhs.value };
   }

   friend Defense operator-( Defense lhs, Defense rhs )
   {
      return Defense{ lhs.value - rhs.value };
   }

   friend std::ostream& operator<<( std::ostream& os, Defense defense )
   {
      return os << defense.value;
   }
};


struct Speed
{
   int value;

   operator int() const { return value; }

   friend Speed operator+( Speed lhs, Speed rhs )
   {
      return Speed{ lhs.value + rhs.value };
   }

   friend Speed operator-( Speed lhs, Speed rhs )
   {
      return Speed{ lhs.value - rhs.value };
   }

   friend std::ostream& operator<<( std::ostream& os, Speed speed )
   {
      return os << speed.value;
   }
};


//---- <Weapon.h> ---------------------------------------------------------------------------------

//#include <Stats.h>
#include <memory>

class Weapon
{
 public:
   Weapon() = default;

   template< typename WeaponT >
   Weapon( WeaponT weapon )
      : pimpl_{ std::make_unique<Model<WeaponT>>( std::move(weapon) ) }
   {}

   Attack attack() const { return pimpl_ ? pimpl_->attack() : Attack{0}; }

 private:
   struct Concept
   {
      virtual ~Concept() = default;
      virtual Attack attack() const = 0;
   };

   template< typename WeaponT >
   struct Model : public Concept
   {
      explicit Model( WeaponT weapon ) : weapon_{std::move(weapon)} {}
      Attack attack() const override { return weapon_.attack(); }
      WeaponT weapon_;
   };

   std::unique_ptr<Concept> pimpl_;
};


//---- <Armor.h> ----------------------------------------------------------------------------------

//#include <Stats.h>
#include <memory>

class Armor
{
 public:
   Armor() = default;

   template< typename ArmorT >
   Armor( ArmorT armor )
      : pimpl_{ std::make_unique<Model<ArmorT>>( std::move(armor) ) }
   {}

   Defense defense() const { return pimpl_ ? pimpl_->defense() : Defense{0}; }

 private:
   struct Concept
   {
      virtual ~Concept() = default;
      virtual Defense defense() const = 0;
   };

   template< typename ArmorT >
   struct Model : public Concept
   {
      explicit Model( ArmorT armor ) : armor_{std::move(armor)} {}
      Defense defense() const override { return armor_.defense(); }
      ArmorT armor_;
   };

   std::unique_ptr<Concept> pimpl_;
};


//---- <Gear.h> -----------------------------------------------------------------------------------

//#include <Stats.h>
#include <memory>

class Gear
{
 public:
   Gear() = default;

   template< typename GearT >
   Gear( GearT gear )
      : pimpl_{ std::make_unique<Model<GearT>>( std::move(gear) ) }
   {}

   Speed speed() const { return pimpl_ ? pimpl_->speed() : Speed{0}; }

 private:
   struct Concept
   {
      virtual ~Concept() = default;
      virtual Speed speed() const = 0;
   };

   template< typename GearT >
   struct Model : public Concept
   {
      explicit Model( GearT gear ) : gear_{std::move(gear)} {}
      Speed speed() const override { return gear_.speed(); }
      GearT gear_;
   };

   std::unique_ptr<Concept> pimpl_;
};


//---- <Creature.h> -------------------------------------------------------------------------------

//#include <Armor.h>
//#include <Gear.h>
//#include <Weapon.h>
#include <memory>
#include <string>
#include <string_view>
#include <utility>

class Creature
{
 public:
   explicit Creature( std::string name ) : name_{ std::move(name) } {}

   virtual ~Creature() = default;

   std::string_view name() const { return name_; }

   Attack  attack () const { return weapon_.attack(); }
   Defense defense() const { return armor_.defense(); }
   Speed   speed  () const { return gear_.speed(); }

   void equip( Weapon weapon ) { weapon_ = std::move(weapon); }
   void equip( Armor armor ) { armor_ = std::move(armor); }
   void equip( Gear gear ) { gear_ = std::move(gear); }

 private:
   std::string name_;
   Weapon weapon_;
   Armor armor_;
   Gear gear_;
};

std::ostream& operator<<( std::ostream& os, Creature const& creature );


//---- <Creature.cpp> -----------------------------------------------------------------------------

//#include <Creature.h>

std::ostream& operator<<( std::ostream& os, Creature const& creature )
{
   return os << creature.name()
             << " (attack: " << creature.attack()
             << ", defense: " << creature.defense()
             << ", speed: " << creature.speed()
             << ')';
}


//---- <WhiteKnight.h> ----------------------------------------------------------------------------

//#include <Creature.h>

class WhiteKnight : public Creature
{
 public:
   explicit WhiteKnight( std::string name )
      : Creature{ std::move(name) }
   {}
};


//---- <Sword.h> ----------------------------------------------------------------------------------

class Sword
{
 public:
   Attack attack() const { return Attack{2}; }
};


//---- <Shield.h> ---------------------------------------------------------------------------------

class Shield
{
 public:
   Defense defense() const { return Defense{2}; }
};


//---- <LeatherBoots.h> ---------------------------------------------------------------------------

class LeatherBoots
{
 public:
   Speed speed() const { return Speed{1}; }
};


//---- <Dragon.h> ---------------------------------------------------------------------------------

//#include <Creature.h>

class Dragon : public Creature
{
 public:
   explicit Dragon( std::string name )
      : Creature{ std::move(name) }
   {}
};


//---- <DragonFire.h> -----------------------------------------------------------------------------

//#include <Weapon.h>

class DragonFire
{
 public:
   Attack attack() const { return Attack{6}; }
};


//---- <DragonScales.h> ---------------------------------------------------------------------------

//#include <Armor.h>

class DragonScales
{
 public:
   Defense defense() const { return Defense{4}; }
};


//---- <DragonSpeed.h> ----------------------------------------------------------------------------

//#include <Gear.h>

class DragonSpeed
{
 public:
   Speed speed() const { return Speed{3}; }
};


//---- <IceEnchantment.h> -------------------------------------------------------------------------

//#include <Weapon.h>

class IceEnchantment
{
 public:
   explicit IceEnchantment( Weapon weapon )
      : weapon_{ std::move(weapon) }
   {}

   Attack attack() const { return weapon_.attack() + Attack{3}; }

 private:
   Weapon weapon_;
};


//---- <MagicShield.h> ----------------------------------------------------------------------------

//#include <Armor.h>

class MagicShield
{
 public:
   explicit MagicShield( Armor armor )
      : armor_{ std::move(armor) }
   {}

   Defense defense() const { return armor_.defense() + Defense{2}; }

 private:
   Armor armor_;
};


//---- <ShoesOfAgility.h> -------------------------------------------------------------------------

//#include <Gear.h>

class ShoesOfAgility
{
 public:
   explicit ShoesOfAgility()
   {}

   Speed speed() const { return Speed{4}; }
};


//---- <MagicShackles.h> --------------------------------------------------------------------------

//#include <Gear.h>

class MagicShackles
{
 public:
   explicit MagicShackles( Gear gear )
      : gear_{ std::move(gear) }
   {}

   Speed speed() const { return Speed{0}; }

 private:
   Gear gear_;
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <WhiteKnight.h>
//#include <Sword.h>
//#include <Shield.h>
//#include <Dragon.h>
//#include <DragonFire.h>
//#include <DragonScales.h>
//#include <IceEnchantment.h>
//#include <MagicShield.h>
//#include <MagicShackles.h>
//#include <ShoesOfAgility.h>
#include <cstdlib>
#include <iostream>

void attacks( Creature const& attacker, Creature const& defender )
{
   // Attack rules:
   // - 'attacker' attacks first;
   // - If the attack value of 'attacker' is higher than the defense of 'defender', 'attacker' wins;
   // - 'defender' attacks second;
   // - If the attack value of 'defender' is higher than the defense of 'attacker', 'defender' wins;

   if( attacker.attack() > defender.defense() ) {
      std::cout << attacker.name() << " wins against " << defender.name() << '\n';
   }
   else if( defender.attack() > attacker.defense() ) {
      std::cout << defender.name() << " wins against " << attacker.name() << '\n';
   }
   else {
      std::cout << "No winner in " << attacker.name() << " against " << defender.name() << '\n';
   }
}

void fight( Creature const& creature1, Creature const& creature2 )
{
   // Fighting rules:
   // - The creature with the higher speed attacks first;
   // - If both creates have the same speed, the creature with the higher attack value attacks first;

   if( creature1.speed() > creature2.speed() )
   {
      attacks( creature1, creature2 );
   }
   else if( creature2.speed() > creature1.speed() )
   {
      attacks( creature2, creature1 );
   }
   else if( creature1.attack() > creature2.attack() )
   {
      attacks( creature1, creature2 );
   }
   else if( creature2.attack() > creature1.attack() )
   {
      attacks( creature2, creature1 );
   }
   else {
      std::cout << "No winner in " << creature1.name() << " against " << creature2.name() << '\n';
   }
}

int main()
{
   // Creating the white knight 'Roland'
   Weapon knightWeapon = IceEnchantment{ Sword{} };

   Armor knightArmor = MagicShield{ Shield{} };

   Gear knightGear = ShoesOfAgility{};

   WhiteKnight knight{ "Roland" };
   knight.equip( std::move(knightWeapon) );
   knight.equip( std::move(knightArmor) );
   knight.equip( std::move(knightGear) );

   // Creating the dragon 'Darksmoke'
   Weapon dragonWeapon = DragonFire{};

   Armor dragonArmor = DragonScales{};

   Gear dragonGear = MagicShackles{ DragonSpeed{} };

   Dragon dragon{ "DarkSmoke" };
   dragon.equip( std::move(dragonWeapon) );
   dragon.equip( std::move(dragonArmor) );
   dragon.equip( std::move(dragonGear) );

   // Printing the two combatants
   std::cout << '\n'
             << knight << '\n'
             << dragon << '\n'
             << '\n';

   // Starting the epic fight
   fight( knight, dragon );

   return EXIT_SUCCESS;
}

