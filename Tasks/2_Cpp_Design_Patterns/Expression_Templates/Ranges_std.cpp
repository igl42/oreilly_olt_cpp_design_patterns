/**************************************************************************************************
*
* \file Ranges_std.cpp
* \brief C++ Training - Example for the C++20 ranges library
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Modify the given example of the C++20 ranges library to compute the first four squares
*       of odd numbers.
*
**************************************************************************************************/

#include <algorithm>
#include <concepts>
#include <cstdlib>
#include <iostream>
#include <ranges>
#include <vector>


void print( std::ranges::input_range auto&& range )
{
   std::cout << "\n (";

   for( auto const& item : range ) {
      std::cout << ' ' << item;
   }

   // Note: Alternatively, the for loop can be replaced by a range algorithm.
   // std::ranges::for_each( range, []( const auto& value ){ std::cout << ' ' << value; } );

   std::cout << " )\n\n";
}


int main()
{
   // Note: std::views is a standard shortcut for std::ranges::views

   std::vector<int> numbers{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

   auto scaledEvenNumbers = numbers
                          | std::views::filter([](int n){ return n%2 == 0; })
                          | std::views::transform([](int n) { return n*2; })
                          | std::views::take( 3UL );

   print( scaledEvenNumbers );

   return EXIT_SUCCESS;
}
