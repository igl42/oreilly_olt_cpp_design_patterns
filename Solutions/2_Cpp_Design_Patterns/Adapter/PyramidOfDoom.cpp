/**************************************************************************************************
*
* \file PyramidOfDoom.cpp
* \brief C++ Training - Example for the Adapter Design Pattern
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Refactor the given 'doSomeWork()' function to avoid the "Pyramid of Doom". For that
*       purpose, implement an adapter to seamlessly connect the three functions 'doSomething()',
*       'doSomethingElse()' and 'doAThirdThing()'.
*
**************************************************************************************************/

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <optional>


//---- <Map.h> ------------------------------------------------------------------------------------

template< typename Fn >
std::optional<double> map( Fn fn, std::optional<double> maybe_value )
{
   if( maybe_value.has_value() ) {
      return fn( *maybe_value );
   }
   else
      return std::nullopt;
}

template< typename Fn >
std::optional<double> operator|( std::optional<double> maybe_value, Fn fn )
{
   return map( fn, maybe_value );
}


//---- <DoSomeWork.h> -----------------------------------------------------------------------------

std::optional<double> doSomething( double d )
{
   if( d >= 0.0 ) {
      return std::sqrt( d );
   }
   else {
      return std::nullopt;
   }
}

std::optional<double> doSomethingElse( double d )
{
   if( d > 0.0 && d < 10.0 ) {
      return d * 2.0;
   }
   else {
      return std::nullopt;
   }
}

std::optional<double> doAThirdThing( double d )
{
   if( d > 2.0 ) {
      return d / 4.0;
   }
   else {
      return std::nullopt;
   }
}

std::optional<double> doAnAlternative()
{
   return std::make_optional( 1.0 );
}

std::optional<double> doSomeWork( double d )
{
   // The original code
   /*
   auto const r1 = doSomething( d );
   if( r1.has_value() ) {
      auto const r2 = doSomethingElse( *r1 );
      if( r2.has_value() ) {
         auto const r3 = doAThirdThing( *r2 );
         if( r3.has_value() ) {
            return *r3;
         }
         else {
            return std::nullopt;
         }
      }
      else {
         return std::nullopt;
      }
   }
   else {
      return std::nullopt;
   }
   */

   // C++17 solution with map() function
   /*
   return
      map( doAThirdThing,
         map( doSomethingElse,
            map( doSomething, std::make_optional(d) ) ) );
   */

   // C++17 solution with overloading of operator|()
   return std::make_optional(d)
        | doSomething
        | doSomethingElse
        | doAThirdThing;

   // C++23 solution with std::optional
   /*
   return std::make_optional(d)
      .and_then( doSomething )
      .and_then( doSomethingElse )
      .and_then( doAThirdThing );
   */
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   // Success
   {
      auto const result = doSomeWork( 64.0 );

      if( result.has_value() ) {
         std::cout << "\n result = " << *result << "\n\n";
      }
      else {
         std::cout << "\n No result!\n\n";
      }
   }

   // Failure
   {
      auto const result = doSomeWork( 1.0 );

      if( result.has_value() ) {
         std::cout << "\n result = " << *result << "\n\n";
      }
      else {
         std::cout << "\n No result!\n\n";
      }
   }

   return EXIT_SUCCESS;
}

