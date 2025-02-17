/**************************************************************************************************
*
* \file StaticInterfaces.cpp
* \brief C++ Training - Example for Static Interface (CRTP vs. Explicit Object Paramters)
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Understand the classic form of Interface CRTP, before switching to the C++23 form
*       using explicit object parameters (aka "Deducing This").
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>


//---- <Animal.h> (C++20 and before)---------------------------------------------------------------

template< typename Derived >
class Animal
{
 protected:
   ~Animal() = default;

 public:
   Derived&       derived()       { return static_cast<Derived&>(*this); }
   Derived const& derived() const { return static_cast<Derived const&>(*this); }

   //template< typename Self >
   //auto&& derived( this Self&& self ) { return self; }

   void make_sound() const { derived().make_sound_impl(); }
};


class Dog : public Animal<Dog>
{
 public:
   void make_sound_impl() const { std::cout << "bark!\n"; }
};


class Cat : public Animal<Cat>
{
 public:
   void make_sound_impl() const { std::cout << "meow!\n"; }
};


class Sheep : public Animal<Sheep>
{
 public:
   void make_sound_impl() const { std::cout << "baa!\n"; }
};


//---- <Animal.h> (C++23, using explicit object parameters, aka "Deducing This")-------------------
/*
class Animal
{
 protected:
   ~Animal() = default;

 public:
   template< typename Self >
   auto&& derived( this Self&& self ) { return self; }

   void make_sound() const { derived().make_sound_impl(); }
};


class Dog : public Animal
{
 public:
   void make_sound_impl() const { std::cout << "bark!\n"; }
};


class Cat : public Animal
{
 public:
   void make_sound_impl() const { std::cout << "meow!\n"; }
};


class Sheep : public Animal
{
 public:
   void make_sound_impl() const { std::cout << "baa!\n"; }
};
*/


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <Animal.h>

template< typename Derived >
void make_sound( Animal<Derived> const& animal )
{
   animal.make_sound();
}


int main()
{
   Dog dog;
   Cat cat;
   Sheep sheep;

   make_sound( dog );
   make_sound( cat );
   make_sound( sheep );

   return EXIT_SUCCESS;
}

