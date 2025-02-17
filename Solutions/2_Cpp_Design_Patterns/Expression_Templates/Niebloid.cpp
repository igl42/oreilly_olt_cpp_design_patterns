/**************************************************************************************************
*
* \file Niebloid.cpp
* \brief C++ Training - Programming Task for C++20 Niebloids
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Consider the use of 'swap()' in the following example. Implement an an ADL-resistant
*       version of the 'swap()' algorithm in the standard namespace. See
*       http://ericniebler.com/2014/10/21/customization-point-design-in-c11-and-beyond/ for
*       an inspiration.
*
**************************************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <utility>


//---- <utility> ----------------------------------------------------------------------------------

namespace standard {

namespace detail {

template< typename T >
constexpr void swap( T& lhs, T& rhs )
{
   std::puts( "standard::swap(T&,T&)" );
   T tmp( std::move(lhs) );
   lhs = std::move(rhs);
   rhs = std::move(tmp);
}

} // namespace detail

struct Swap
{
   template< typename T >
   constexpr void operator()( T& lhs, T& rhs ) const
   {
      std::puts( "Swap::operator()(T&,T&)" );
      using standard::detail::swap;
      swap( lhs, rhs );
   }
};

inline constexpr Swap swap{};

} // namespace standard


//---- <jan/Int.h> --------------------------------------------------------------------------------

namespace jan {  // Just Another Namespace = jan

struct Int
{
   int i;
};

void swap( Int& lhs, Int& rhs )
{
   std::puts( "jan::swap(Int&,Int&)" );
   using standard::swap;
   swap( lhs.i, rhs.i );
}

} // namespace jan


//---- <Main.cpp> ---------------------------------------------------------------------------------

template< typename T >
void performSwap( T& lhs, T& rhs )
{
   standard::swap( lhs, rhs );
}


int main()
{
   {
      std::puts( "\n---- Swapping two 'int'----" );

      int i{ 42 }, j{ 99 };
      performSwap( i, j );
   }
   {
      std::puts( "\n---- Swapping two 'jan::Int'----" );

      jan::Int i{ 42 }, j{ 99 };
      performSwap( i, j );
   }

   return EXIT_SUCCESS;
}
