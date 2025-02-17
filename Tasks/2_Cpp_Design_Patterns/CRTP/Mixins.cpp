/**************************************************************************************************
*
* \file Mixins.cpp
* \brief C++ Training - Example for Mixins (CRTP vs. Explicit Object Parameters)
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Understand the classic form of Mixin (Implementation) CRTP, before switching to the
*       C++23 form using explicit object parameters (aka "Deducing This").
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>


//---- <Sensitivity.h> (C++20 and before)----------------------------------------------------------

template< typename Derived >
struct NumericalFunctions
{
   void scale( double multiplicator )
   {
      Derived& underlying = static_cast<Derived&>(*this);
      underlying.setValue( underlying.getValue() * multiplicator );
   }
};

struct Sensitivity : public NumericalFunctions<Sensitivity>
{
   explicit Sensitivity( double value ) : value_{value} {}

   double getValue() const { return value_; }
   void setValue( double value ) { value_ = value; }

   double value_;
};


//---- <Sensitivity.h> (C++23, using explicit object parameters, aka "Deducing This")--------------
/*
struct NumericalFunctions
{
   void scale( this auto&& self, double multiplicator )
   {
      self.setValue( self.getValue() * multiplicator );
   }
};

struct Sensitivity : public NumericalFunctions
{
   explicit Sensitivity( double value ) : value_{value} {}

   double getValue() const { return value_; }
   void setValue( double value ) { value_ = value; }

   double value_;
};
*/


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <Sensitivity.h>

int main()
{
   Sensitivity s{ 1.2 };

   s.scale( 2.0 );

   std::cout << "\n s.getValue() = " << s.getValue() << "\n\n";

   return EXIT_SUCCESS;
}

