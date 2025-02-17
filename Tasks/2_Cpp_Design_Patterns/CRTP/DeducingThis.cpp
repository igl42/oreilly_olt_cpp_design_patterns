/**************************************************************************************************
*
* \file DeducingThis.cpp
* \brief C++ Training - Example for Explicit Object Parameters (aka "Deducing This")
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Explore the explicit object parameters in the three member functions 'S::f()',
*       'S::g()' and 'S::h()'.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <type_traits>


#ifdef __cpp_explicit_this_parameter

struct S
{
   S() = default;

   // Explicit object parameters cannot be used in constructors and assignment operators
   //S( this auto&& self ) { std::cout << "Copy/move constructor!\n"; }
   //S& operator=( this auto&& self ) { std::cout << "Copy/move assignment operator!\n"; }

   // Explicit object parameter 'self'
   // Note that the function is not const, but 'self' is a reference-to-const
   void f( [[maybe_unused]] this S const& self )
   {
      std::cout << "Calling f()\n";
   }

   // Explicit object parameter 'self'
   // Note that 'T&&' is a forwarding reference, i.e. the function can be called on
   // const and non-const objects.
   template< typename T >
   void g( [[maybe_unused]] this T&& self )
   {
      using U = std::remove_reference_t<T>;
      std::cout << "Calling g()\n"
                << "std::is_reference_v<T> = " << std::is_reference_v<T> << "\n"
                << "std::is_reference_v<U> = " << std::is_reference_v<U> << "\n"
                << "std::is_const_v<U>     = " << std::is_const_v<U> << "\n"
                << "\n";
   }

   // Explicit object parameter 'self'
   // Note that 'auto&&' is a forwarding reference, i.e. the function can be called on
   // const and non-const objects.
   void h( [[maybe_unused]] this auto&& self )
   {
      using T = decltype(self);
      using U = std::remove_reference_t<T>;
      std::cout << "Calling h()\n"
                << "std::is_reference_v<T> = " << std::is_reference_v<T> << "\n"
                << "std::is_reference_v<U> = " << std::is_reference_v<U> << "\n"
                << "std::is_const_v<U>     = " << std::is_const_v<U> << "\n"
                << "\n";
   }
};


int main()
{
   S s{};
   S const cs;

   s.f();
   s.g();
   s.h();

   cs.f();
   cs.g();
   cs.h();

   return EXIT_SUCCESS;
}

#else

int main()
{}

#endif

