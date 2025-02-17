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

class Weapon
{
 public:
   virtual ~Weapon() = default;

   virtual Attack attack() const = 0;
};


//---- <Armor.h> ----------------------------------------------------------------------------------

//#include <Stats.h>

class Armor
{
 public:
   virtual ~Armor() = default;

   virtual Defense defense() const = 0;
};


//---- <Gear.h> -----------------------------------------------------------------------------------

//#include <Stats.h>

class Gear
{
 public:
   virtual ~Gear() = default;

   virtual Speed speed() const = 0;
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

   Attack  attack () const { return weapon_ ? weapon_->attack() : Attack{0}; }
   Defense defense() const { return armor_ ? armor_->defense() : Defense{0}; }
   Speed   speed  () const { return gear_ ? gear_->speed() : Speed{0}; }

   void equip( std::unique_ptr<Weapon>&& weapon ) { weapon_ = std::move(weapon); }
   void equip( std::unique_ptr<Armor>&& armor ) { armor_ = std::move(armor); }
   void equip( std::unique_ptr<Gear>&& gear ) { gear_ = std::move(gear); }

 private:
   std::string name_;
   std::unique_ptr<Weapon> weapon_;
   std::unique_ptr<Armor> armor_;
   std::unique_ptr<Gear> gear_;
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

//#include <Weapon.h>

class Sword : public Weapon
{
 public:
   Attack attack() const override { return Attack{2}; }
};


//---- <Shield.h> ---------------------------------------------------------------------------------

//#include <Armor.h>

class Shield : public Armor
{
 public:
   Defense defense() const override { return Defense{2}; }
};


//---- <LeatherBoots.h> ---------------------------------------------------------------------------

//#include <Gear.h>

class LeatherBoots : public Gear
{
 public:
   Speed speed() const override { return Speed{2}; }
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

class DragonFire : public Weapon
{
 public:
   Attack attack() const override { return Attack{6}; }
};


//---- <DragonScales.h> ---------------------------------------------------------------------------

//#include <Armor.h>

class DragonScales : public Armor
{
 public:
   Defense defense() const override { return Defense{4}; }
};


//---- <DragonSpeed.h> ----------------------------------------------------------------------------

//#include <Gear.h>

class DragonSpeed : public Gear
{
 public:
   Speed speed() const override { return Speed{3}; }
};


//---- <WeaponModifier.h> -------------------------------------------------------------------------

//#include <Weapon.h>
#include <memory>

class WeaponModifier : public Weapon
{
 public:
   explicit WeaponModifier( std::unique_ptr<Weapon>&& weapon )
      : weapon_{ std::move(weapon) }
   {}

   Attack attack() const override { return weapon_->attack(); }

 private:
   std::unique_ptr<Weapon> weapon_;
};


//---- <IceEnchantment.h> -------------------------------------------------------------------------

//#include <WeaponModifier.h>

class IceEnchantment : public WeaponModifier
{
 public:
   using WeaponModifier::WeaponModifier;

   Attack attack() const override { return WeaponModifier::attack() + Attack{3}; }
};


//---- <ArmorModifier.h> --------------------------------------------------------------------------

//#include <Armor.h>
#include <memory>

class ArmorModifier : public Armor
{
 public:
   explicit ArmorModifier( std::unique_ptr<Armor>&& armor )
      : armor_{ std::move(armor) }
   {}

   Defense defense() const override { return armor_->defense(); }

 private:
   std::unique_ptr<Armor> armor_;
};


//---- <MagicShield.h> ----------------------------------------------------------------------------

//#include <ArmorModifier.h>

class MagicShield : public ArmorModifier
{
 public:
   using ArmorModifier::ArmorModifier;

   Defense defense() const override { return ArmorModifier::defense() + Defense{2}; }
};


//---- <ShoesOfAgility.h> -------------------------------------------------------------------------

//#include <Gear.h>

class ShoesOfAgility : public Gear
{
 public:
   explicit ShoesOfAgility()
   {}

   Speed speed() const override { return Speed{4}; }
};


//---- <GearModifier.h> ---------------------------------------------------------------------------

//#include <Gear.h>
#include <memory>

class GearModifier : public Gear
{
 public:
   explicit GearModifier( std::unique_ptr<Gear>&& gear )
      : gear_{ std::move(gear) }
   {}

   Speed speed() const override { return gear_->speed(); }

 private:
   std::unique_ptr<Gear> gear_;
};


//---- <MagicShackles.h> --------------------------------------------------------------------------

//#include <GearModifier.h>

class MagicShackles : public GearModifier
{
 public:
   using GearModifier::GearModifier;

   Speed speed() const override { return Speed{0}; }
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
   std::unique_ptr<Weapon> knightWeapon =
      std::make_unique<IceEnchantment>( std::make_unique<Sword>() );

   std::unique_ptr<Armor> knightArmor =
      std::make_unique<MagicShield>( std::make_unique<Shield>() );

   std::unique_ptr<Gear> knightGear = std::make_unique<ShoesOfAgility>();

   WhiteKnight knight{ "Roland" };
   knight.equip( std::move(knightWeapon) );
   knight.equip( std::move(knightArmor) );
   knight.equip( std::move(knightGear) );

   // Creating the dragon 'Darksmoke'
   std::unique_ptr<Weapon> dragonWeapon = std::make_unique<DragonFire>();

   std::unique_ptr<Armor> dragonArmor = std::make_unique<DragonScales>();

   std::unique_ptr<Gear> dragonGear =
      std::make_unique<MagicShackles>( std::make_unique<DragonSpeed>() );

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

