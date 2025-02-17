/**************************************************************************************************
*
* \file Decorator_Static.cpp
* \brief C++ Training - Programming Task for the Decorator Design Pattern
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Discuss the advantages and disadvantages of the given compile-time decorator.
*
**************************************************************************************************/


//---- <Money.h> --------------------------------------------------------------------------------

//#include <concepts>
#include <cstdint>
#include <ostream>
#include <type_traits>

template< typename T >
using enable_if_is_int64_convertible =
   std::enable_if_t< std::is_convertible_v<T,std::int64_t>, bool >;

template< typename T >
using enable_if_is_arithmetic =
   std::enable_if_t< std::is_arithmetic_v<T>, bool >;

class Money
{
 public:
   Money() = default;

   template< typename T, enable_if_is_int64_convertible<T> = true >
   //template< typename T > requires std::is_convertible_v<T,std::int64_t>  // C++20 constraint
   constexpr explicit Money( T v )
      : value_{static_cast<std::int64_t>(v*100)}
   {}

   double value() const { return static_cast<double>(value_)/100.0; }

 private:
   std::int64_t value_{};

   template< typename T, enable_if_is_arithmetic<T> = true >
   //template< typename T > requires std::is_arithmetic_v<T>  // C++20 constraint
   friend constexpr Money operator*( Money money, T factor )
   {
      money.value_ *= factor;
      return money;
   }

   template< typename T, enable_if_is_arithmetic<T> = true >
   //template< typename T > requires std::is_arithmetic_v<T>  // C++20 constraint
   friend constexpr Money operator*( T factor, Money money )
   {
      money.value_ *= factor;
      return money;
   }

   friend constexpr Money operator+( Money lhs, Money rhs )
   {
      lhs.value_ += rhs.value_;
      return lhs;
   }

   friend constexpr Money operator-( Money lhs, Money rhs )
   {
      lhs.value_ -= rhs.value_;
      return lhs;
   }

   friend constexpr bool operator==( Money lhs, Money rhs )
   {
      return lhs.value_ == rhs.value_;
   }

   friend constexpr bool operator!=( Money lhs, Money rhs )
   {
      return !( lhs == rhs );
   }

   friend constexpr bool operator<( Money lhs, Money rhs )
   {
      return lhs.value_ < rhs.value_;
   }

   friend constexpr bool operator>( Money lhs, Money rhs )
   {
      return rhs < lhs;
   }

   friend std::ostream& operator<<( std::ostream& os, Money money )
   {
      return os << money.value();
   }
};

static_assert( Money{120}*0.5 == Money{60} );
static_assert( 0.5*Money{120} != Money{50} );
static_assert( Money{120}+Money{60} < Money{200} );
static_assert( Money{120}-Money{60} > Money{40} );


//---- <PricedItem.h> -----------------------------------------------------------------------------

#include <concepts>

template< typename T >
concept PricedItem =
   requires ( const T item ) {
      { item.price() } -> std::same_as<Money>;
   };


//---- <Discount.h> -------------------------------------------------------------------------------

//#include <PricedItem.h>
#include <concepts>
#include <utility>

template< double discount, PricedItem Item >
class Discount
{
 public:
   template< typename... Args >
      requires std::constructible_from<Item,Args...>
   explicit constexpr Discount( Args&&... args )
      : item_{ std::forward<Args>(args)... }
   {}

   constexpr Money price() const {
      return item_.price() * ( 1.0 - discount );
   }

 private:
   Item item_;
};

template< double discount, PricedItem Item >
constexpr Discount<discount,Item> applyDiscount( Item item )
{
   return Discount<discount,Item>{ item };
}


//---- <Tax.h> ------------------------------------------------------------------------------------

//#include <PricedItem.h>
#include <concepts>
#include <utility>

template< double tax, PricedItem Item >
class Tax : private Item
{
 public:
   template< typename... Args >
      requires std::constructible_from<Item,Args...>
   explicit constexpr Tax( Args&&... args )
      : Item{ std::forward<Args>(args)... }
   {}

   constexpr Money price() const {
      return Item::price() * ( 1.0 + tax );
   }
};

template< double tax, PricedItem Item >
constexpr Tax<tax,Item> applyTax( Item item )
{
   return Tax<tax,Item>{ item };
}


//---- <ConferenceTicket.h> -----------------------------------------------------------------------

//#include <Money.h>
#include <string>
#include <utility>

class ConferenceTicket
{
 public:
   constexpr ConferenceTicket( std::string name, Money price )
      : name_{ std::move(name) }
      , price_{ price }
   {}

   constexpr const std::string& name() const noexcept { return name_; }
   constexpr Money price() const noexcept { return price_; }

 private:
   std::string name_{};
   Money price_{};
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <ConferenceTicket.h>
//#include <Discount.h>
//#include <Money.h>
//#include <Tax.h>
#include <cstdlib>
#include <iostream>

int main()
{
   using ItemType = Tax<0.1,Discount<0.2,ConferenceTicket>>;

   auto item = applyTax<0.1>( applyDiscount<0.2>( ConferenceTicket{ "CppCon", Money{1200.0F} } ) );

   static_assert( std::same_as<decltype(item),ItemType> );

   std::cout << "item.price() = " << item.price() << "\n";

   //static_assert( Tax<0.1,Discount<0.2,ConferenceTicket>>{ "CppCon", Money{1200.0F} }.price() == Money{1056} );

   return EXIT_SUCCESS;
}

