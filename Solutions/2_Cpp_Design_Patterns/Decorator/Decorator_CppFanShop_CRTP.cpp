/**************************************************************************************************
*
* \file Decorator_CppFanShop_CRTP.cpp
* \brief C++ Training - Programming Task for the Decorator Design Pattern
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Introduce a quantity discount and a shopping cart (2 items: 10%, 3 items: 15%,
*         4 items: 20%, more than four items: 25%).
*
* Step 2: Refactor the classic Decorator solution by a value semantics based solution. Note that
*         the general behavior should remain unchanged.
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


//---- <Color.h> ----------------------------------------------------------------------------------

enum class Color
{
   red   = 0xFF0000,
   green = 0x00FF00,
   blue  = 0x0000FF
};


//---- <Item.h> -----------------------------------------------------------------------------------

//#include <Money.h>

template< typename Derived >
class Item
{
 protected:
   ~Item() = default;

 public:
   Money price() const { return derived().price(); }

   Derived&       derived()       { return static_cast<Derived&>(*this); }
   Derived const& derived() const { return static_cast<Derived const&>(*this); }
};


//---- <ConferenceTicket.h> --------------------------------------------------------------------------

//#include <Money.h>
#include <string>

class ConferenceTicket : public Item<ConferenceTicket>
{
 public:
   ConferenceTicket( std::string name, Money price )
      : name_{ std::move(name) }
      , price_{ price }
   {}

   std::string const& name() const {
      return name_;
   }

   Money price() const {
      return price_;
   }

 private:
   std::string name_{};
   Money price_{};
};


//---- <CppBook.h> --------------------------------------------------------------------------------

//#include <Money.h>
#include <string>

class CppBook : public Item<CppBook>
{
 public:
   CppBook( std::string title, Money price )
      : title_{ std::move(title) }
      , price_{ price }
   {}

   std::string const& title() const {
      return title_;
   }

   Money price() const {
      return price_;
   }

 private:
   std::string title_{};
   Money price_{};
};


//---- <CppShirt.h> -------------------------------------------------------------------------------

//#include <Color.h>
//#include <Money.h>

class CppShirt : public Item<CppShirt>
{
 public:
   CppShirt( Color color, Money price )
      : color_{ color }
      , price_{ price }
   {}

   Color color() const {
      return color_;
   }

   Money price() const {
      return price_;
   }

 private:
   Color color_{};
   Money price_{};
};


//---- <Discount.h> -------------------------------------------------------------------------------

//#include <Item.h>
#include <cmath>
#include <stdexcept>
#include <utility>

template< typename ItemT >
class Discount : public Item<Discount<ItemT>>
{
 public:
   template< typename... Args >
   Discount( double discount, Args&&... args )
      : item_( std::forward<Args>(args)... )
      , factor_( 1.0 - discount )
   {
      if( !std::isfinite(discount) || discount < 0.0 || discount > 1.0 ) {
         throw std::invalid_argument( "Invalid discount value" );
      }
   }

   Money price() const {
      return item_.price() * factor_;
   }

 private:
   ItemT item_;
   double factor_{};
};


//---- <Tax.h> ------------------------------------------------------------------------------------

//#include <DecoratedItem.h>
#include <cmath>
#include <stdexcept>
#include <utility>

template< typename ItemT >
class Tax : public Item<Tax<ItemT>>
{
 public:
   template< typename... Args >
   Tax( double tax, Args&&... args )
      : item_( std::forward<Args>(args)... )
      , factor_( 1.0 + tax )
   {
      if( tax < 0.0 ) {
         throw std::invalid_argument( "Invalid tax value" );
      }
   }

   Money price() const {
      return item_.price() * factor_;
   }

 private:
   ItemT item_;
   double factor_{};
};


//---- <QuantityDiscount.h> -----------------------------------------------------------------------

//#include <Item.h>
#include <cstddef>
#include <utility>

template< typename ItemT >
class QuantityDiscount : public Item<QuantityDiscount<ItemT>>
{
 public:
   template< typename... Args >
   QuantityDiscount( size_t count, Args&&... args )
      : item_{ std::forward<Args>(args)... }
      , count_{ count }
   {}

   Money price() const {
      return item_.price() * count_ * ( 1.0-discount() );
   }

 private:
   double discount() const
   {
      if     ( count_ >  4U ) return 0.25;
      else if( count_ == 4U ) return 0.2;
      else if( count_ == 3U ) return 0.15;
      else if( count_ == 2U ) return 0.1;
      else                    return 0.0;
   }

   ItemT item_;
   size_t count_{};
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <ConferenceTicket.h>
//#include <CppBook.h>
//#include <CppShirt.h>
//#include <Discount.h>
//#include <QuantityDiscount.h>
//#include <Tax.h>
#include <cstdlib>
#include <iostream>

int main()
{
   Tax<Discount<ConferenceTicket>> item1( 0.19, 0.2, "CppCon", Money{999.0F} );

   Tax<QuantityDiscount<CppBook>> item2( 0.07, 3, "Effective C++", Money{19.0F} );

   Tax<CppShirt> item3( 0.19, Color::red, Money{15.0F} );

   std::cout << "\n"
             << " Total price of item1 = " << item1.price() << "\n"
             << " Total price of item2 = " << item2.price() << "\n"
             << " Total price of item3 = " << item3.price() << "\n"
             << "\n";

   return EXIT_SUCCESS;
}

