/**************************************************************************************************
*
* \file StrongType_CRTP.cpp
* \brief C++ Training - Advanced example for the CRTP Design Pattern
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Extend the 'StrongType' class template by a CRTP-based mechanism to enable the
*       customization of a specific strong type with user-defined operations. For instance,
*       the 'Meter' type should support addition and subtraction, it should be printable and
*       equality comparable.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <utility>


//---- <Addable.h> --------------------------------------------------------------------------------

// TODO


//---- <Subtractable.h> ---------------------------------------------------------------------------

// TODO


//---- <Printable.h> ------------------------------------------------------------------------------

// TODO


//---- <EqualityComparable.h> ---------------------------------------------------------------------

// TODO


//---- <StrongType.h> -----------------------------------------------------------------------------

template< typename T, typename Tag >
class StrongType
{
 public:
   using value_type = T;

   explicit constexpr StrongType( const T& value ) : value_( value ) {}

   constexpr StrongType& operator=( const T& value ) { value_ = value; return *this; }

   [[nodiscard]] constexpr T&        get()       &  noexcept { return value_; }
   [[nodiscard]] constexpr T const&  get() const &  noexcept { return value_; }
   [[nodiscard]] constexpr T&&       get()       && noexcept { return std::move(value_); }
   [[nodiscard]] constexpr T const&& get() const && noexcept { return std::move(value_); }

   constexpr void swap( StrongType& other ) noexcept( std::is_nothrow_swappable_v<T> )
   {
      using std::swap;
      swap( value_, other.value_ );

      // One-line alternative in C++20: std::ranges::swap( value_, other.value_ );
   }

 private:
   T value_;
};

template< typename T, typename Tag >
std::ostream& operator<<( std::ostream& os, const StrongType<T,Tag>& nt )
{
   os << nt.get();
   return os;
}

template< typename T, typename Tag >
constexpr void swap( StrongType<T,Tag>& a, StrongType<T,Tag>& b )
{
   a.swap( b );
}


//---- <Meter.h> ----------------------------------------------------------------------------------

template< typename T >
using Meter = StrongType<T,struct MeterTag>;


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   /*
   auto const m1 = Meter<long>{ 100L };
   auto const m2 = Meter<long>{  50L };

   auto m3 = m1 + m2;       // Addition of two 'Meter' objects
   m3 -= Meter<long>{108L};  // Subtraction assignment

   std::cout << "\n m3  = " << m3 << "m\n\n";
   */

   /*
   static_assert( Meter<long>{100L} + Meter<long>{50L} == Meter<long>{150L} );
   static_assert( Meter<long>{100L} - Meter<long>{50L} != Meter<long>{150L} );
   */

   return EXIT_SUCCESS;
}
