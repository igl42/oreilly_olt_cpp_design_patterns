/**************************************************************************************************
*
* \file OptionalRefactoring_1.cpp
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

std::optional<int> to_int( std::string_view sv )
{
   int i{};
   auto [ptr, ec]{ std::from_chars( sv.data(), sv.data() + sv.size(), i ) };
   if( ec == std::errc() )
      return i;
   else
      return std::nullopt;
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <ToInt.h>
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
         "1234", "15 foo", "bar", "42", "5000000000", " 5", std::nullopt, "-43"
      };

   // Manual, imperative style
   for( auto&& x : v )
   {
      if( x )
      {
         std::cout << std::left << std::setw(13)
                   << std::quoted(*x) << " -> ";

         std::optional<int> i = to_int(*x);

         if( i ) {
            *i += 1;
            std::cout << std::to_string(*i) << '\n';
         }
         else {
            std::cout << "NaN\n";
         }
      }
      else {
         std::cout << std::left << std::setw(13)
                   << std::quoted("nullopt") << " -> NaN\n";
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

