/**************************************************************************************************
*
* \file OptionalRefactoring_2.cpp
* \brief C++ Training - Example for the Adapter Design Pattern
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Refactor the given 'main()' function from a declarative style to an imperative
*       (functional/monadic) style by means of the following four member functions:
*         - 'std::optional::value_or()'
*         - 'std::optional::and_then()'
*         - 'std::optional::or_else()'
*         - 'std::optional::transform()'
*
* Inspired by cppreference.com: https://en.cppreference.com/w/cpp/utility/optional/and_then
*
**************************************************************************************************/


//---- <ToInt.h> ----------------------------------------------------------------------------------

#include <charconv>
#include <optional>
#include <system_error>

std::optional<float> to_float( std::string_view sv )
{
   float f{};
   auto [ptr, ec]{ std::from_chars( sv.data(), sv.data() + sv.size(), f ) };
   if( ec == std::errc() )
      return f;
   else
      return std::nullopt;
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <ToInt.h>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>
using namespace std::literals;

int main()
{
   std::vector<std::optional<std::string>> const v
      {
         "1.23", "-4.56 foo", "5E-2", "inf", "INF", "nan", "NaN", "bar", "5E300", " 5.0"
      };


   // Manual, imperative style
   for( auto&& x : v )
   {
      if( x )
      {
         std::cout << std::left << std::setw(13)
                   << std::quoted(*x) << " -> ";

         std::optional<float> f = to_float(*x);

         if( f )
         {
            if( std::isfinite(*f) )
            {
               *f *= -1.0F;
            }

            std::cout << std::to_string(*f) << '\n';
         }
         else {
            std::cout << "Invalid\n";
         }
      }
      else {
         std::cout << std::left << std::setw(13)
                   << std::quoted("nullopt") << " -> Invalid\n";
      }
   }


   // C++23 declarative (functional/monadic) style
   // Refactor the given 'main()' function from an imperative style to a declarative
   // (functional/monadic) style by means of the following four member functions:
   //    - 'std::optional::value_or()'
   //    - 'std::optional::and_then()'
   //    - 'std::optional::or_else()'
   //    - 'std::optional::transform()'


   return EXIT_SUCCESS;
}

