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


//---- <Addable.h> --------------------------------------------------------------------------------

template< typename Derived >
struct Addable
{
   friend constexpr Derived& operator+=( Derived& lhs, const Derived& rhs ) {
      lhs.get() += rhs.get();
      return lhs;
   }

   friend constexpr Derived operator+( const Derived& lhs, const Derived& rhs ) {
      return Derived{ lhs.get() + rhs.get() };
   }
};


//---- <Subtractable.h> ---------------------------------------------------------------------------

template< typename Derived >
struct Subtractable
{
   friend constexpr Derived& operator-=( Derived& lhs, const Derived& rhs ) {
      lhs.get() -= rhs.get();
      return lhs;
   }

   friend constexpr Derived operator-( const Derived& lhs, const Derived& rhs ) {
      return Derived{ lhs.get() - rhs.get() };
   }
};


//---- <IntegralArithmetic.h> ---------------------------------------------------------------------

template< typename Derived >
struct IntegralArithmetic
   : public Addable<Derived>
   , public Subtractable<Derived>
{};


//---- <Printable.h> ------------------------------------------------------------------------------

#include <iosfwd>

template< typename Derived >
struct Printable
{
   friend std::ostream& operator<<( std::ostream& os, Derived const& d )
   {
      os << d.get();
      return os;
   }
};


//---- <EqualityComparable.h> ---------------------------------------------------------------------

template< typename Derived >
struct EqualityComparable
{
   friend constexpr bool operator==( Derived const& lhs, Derived const& rhs )
   {
      return lhs.get() == rhs.get();
   }

   // No longer required in C++20
   friend constexpr bool operator!=( Derived const& lhs, Derived const& rhs )
   {
      return !( lhs == rhs );
   }
};


//---- <StrongType.h> -----------------------------------------------------------------------------

#include <utility>

template< typename T, typename Tag, template<typename> class... Skills >
class StrongType
   : public Skills< StrongType<T,Tag,Skills...> >...
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

template< typename T, typename Tag, template<typename> class... Skills >
constexpr void swap( StrongType<T,Tag,Skills...>& a, StrongType<T,Tag,Skills...>& b )
{
   a.swap( b );
}


//---- <Meter.h> ----------------------------------------------------------------------------------

template< typename T >
using Meter = StrongType<T,struct MeterTag,Addable,Subtractable,Printable,EqualityComparable>;


//---- <Main.cpp> ---------------------------------------------------------------------------------

#include <cstdlib>
#include <iostream>

int main()
{
   auto const m1 = Meter<long>{ 100L };
   auto const m2 = Meter<long>{  50L };

   auto m3 = m1 + m2;       // Addition of two 'Meter' objects
   m3 -= Meter<long>{108L};  // Subtraction assignment

   std::cout << "\n m3  = " << m3 << "m\n\n";

   static_assert( Meter<long>{100L} + Meter<long>{50L} == Meter<long>{150L} );
   static_assert( Meter<long>{100L} - Meter<long>{50L} != Meter<long>{150L} );

   return EXIT_SUCCESS;
}
