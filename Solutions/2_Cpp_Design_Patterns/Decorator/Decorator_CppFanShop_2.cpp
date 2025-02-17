/**************************************************************************************************
*
* \file Decorator_CppFanShop_2.cpp
* \brief C++ Training - Programming Task for the Decorator Design Pattern
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* You are hired to rework the pricing system of the "C++ Fan Shop":
*
* Step 1: Implement a 'DecoratedItem', which enables the Decorator design pattern for
*         the items of the "C++ Fan Shop". Based on this, implement a 'Discount'
*         decorator, a 'Coupon' decorator, and a 'Tax' decorator.
*
* Step 2: Introduce a quantity discount and a shopping cart (2 items: 10%, 3 items: 15%,
*         4 items: 20%, more than four items: 25%).
*
* Step 3: Refactor the classic Decorator solution by a value semantics based solution. Note that
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

class Item
{
 public:
   virtual ~Item() = default;
   virtual Money price() const = 0;
};


//---- <ConferenceTicket.h> --------------------------------------------------------------------------

//#include <Money.h>
#include <string>

class ConferenceTicket : public Item
{
 public:
   ConferenceTicket( std::string name, Money price )
      : name_{ std::move(name) }
      , price_{ price }
   {}

   std::string const& name() const {
      return name_;
   }

   Money price() const override {
      return price_;
   }

 private:
   std::string name_{};
   Money price_{};
};


//---- <CppBook.h> --------------------------------------------------------------------------------

//#include <Money.h>
#include <string>

class CppBook : public Item
{
 public:
   CppBook( std::string title, Money price )
      : title_{ std::move(title) }
      , price_{ price }
   {}

   std::string const& title() const {
      return title_;
   }

   Money price() const override {
      return price_;
   }

 private:
   std::string title_{};
   Money price_{};
};


//---- <CppStandard.h> -----------------------------------------------------------------------------

//#include <Money.h>
#include <string>

class CppStandard : public Item
{
 public:
   // The C++ standard can be purchased here: https://www.iso.org/standard/79358.html

   CppStandard( std::string title, Money price )
      : title_{ std::move(title) }
      , price_{ price }
   {}

   std::string const& title() const {
      return title_;
   }

   Money price() const override {
      return price_;
   }

 private:
   std::string title_{};
   Money price_{};
};


//---- <CppShirt.h> -------------------------------------------------------------------------------

//#include <Color.h>
//#include <Money.h>

class CppShirt : public Item
{
 public:
   CppShirt( Color color, Money price )
      : color_{ color }
      , price_{ price }
   {}

   Color color() const {
      return color_;
   }

   Money price() const override {
      return price_;
   }

 private:
   Color color_{};
   Money price_{};
};


//---- <DecoratedItem.h> --------------------------------------------------------------------------

//#include <Item.h>
#include <memory>
#include <stdexcept>

class DecoratedItem : public Item
{
 public:
   explicit DecoratedItem( std::unique_ptr<Item>&& item )
      : item_( std::move(item) )
   {
      if( !item_ ) {
         throw std::invalid_argument( "Invalid item" );
      }
   }

 protected:
   Item&       item()       { return *item_; }
   Item const& item() const { return *item_; }

 private:
   std::unique_ptr<Item> item_;
};


//---- <Discount.h> -------------------------------------------------------------------------------

//#include <DecoratedItem.h>
#include <cmath>
#include <stdexcept>
#include <utility>

class Discount : public DecoratedItem
{
 public:
   Discount( double discount, std::unique_ptr<Item>&& item )
      : DecoratedItem( std::move(item) )
      , factor_( 1.0 - discount )
   {
      if( !std::isfinite(discount) || discount < 0.0 || discount > 1.0 ) {
         throw std::invalid_argument( "Invalid discount value" );
      }
   }

   Money price() const override {
      return item().price() * factor_;
   }

 private:
   double factor_;
};


//---- <Coupon.h> ---------------------------------------------------------------------------------

//#include <DecoratedItem.h>
#include <utility>

class Coupon : public DecoratedItem
{
 public:
   Coupon( Money value, std::unique_ptr<Item>&& item )
      : DecoratedItem( std::move(item) )
      , value_( value )
   {}

   Money price() const override {
      if( item().price() < value_ )
         return Money{};
      else
         return item().price() - value_;
   }

 private:
   Money value_;
};


//---- <Tax.h> ------------------------------------------------------------------------------------

//#include <DecoratedItem.h>
#include <cmath>
#include <stdexcept>
#include <utility>

class Tax : public DecoratedItem
{
 public:
   Tax( double tax, std::unique_ptr<Item>&& item )
      : DecoratedItem( std::move(item) )
      , factor_( 1.0 + tax )
   {
      if( !std::isfinite(tax) || tax < 0.0 ) {
         throw std::invalid_argument( "Invalid tax value" );
      }
   }

   Money price() const override {
      return item().price() * factor_;
   }

 private:
   double factor_;
};


//---- <QuantityDiscount.h> -----------------------------------------------------------------------

//#include <DecoratedItem.h>
#include <cstddef>
#include <utility>

class QuantityDiscount : public DecoratedItem
{
 public:
   QuantityDiscount( size_t count, std::unique_ptr<Item>&& item )
      : DecoratedItem{ std::move(item) }
      , count_{ count }
   {}

   Money price() const override {
      return item().price() * count_ * ( 1.0-discount() );
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

   size_t count_{};
};


//---- <ShoppingCart.h> ---------------------------------------------------------------------------

//#include <Item.h>
#include <numeric>
#include <utility>
#include <vector>

class ShoppingCart : public Item
{
 public:
   template< typename... Items >
   ShoppingCart( Items&&... items )
      : items_{}
   {
      items_.reserve( sizeof...(Items) );
      ( items_.push_back( std::forward<Items>(items) ), ... );
   }

   Money price() const override {
      Money const sum =
         std::accumulate( begin(items_), end(items_), Money{}
                        , []( Money accu, auto const& item ){ return accu + item->price(); } );
      return sum * ( 1.0-discount() );
   }

 private:
   double discount() const
   {
      if     ( items_.size() >  4U ) return 0.25;
      else if( items_.size() == 4U ) return 0.2;
      else if( items_.size() == 3U ) return 0.15;
      else if( items_.size() == 2U ) return 0.1;
      else                           return 0.0;
   }

   std::vector<std::unique_ptr<Item>> items_;
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <ConferenceTicket.h>
//#include <CppBook.h>
//#include <CppShirt.h>
//#include <CppStandard.h>
//#include <Coupon.h>
//#include <Discount.h>
//#include <QuantityDiscount.h>
//#include <ShoppingCart.h>
//#include <Tax.h>
#include <cstdlib>
#include <iostream>

int main()
{
   std::unique_ptr<Item> item1(
      std::make_unique<Tax>( 0.19,
         std::make_unique<Discount>( 0.2,
            std::make_unique<ConferenceTicket>( "CppCon", Money{999.0F} ) ) ) );

   std::unique_ptr<Item> item2(
      std::make_unique<Tax>( 0.07,
         std::make_unique<QuantityDiscount>( 3,
            std::make_unique<CppBook>( "Effective C++", Money{19.0F} ) ) ) );

   std::unique_ptr<Item> item3(
      std::make_unique<Tax>( 0.19,
         std::make_unique<CppStandard>( "ISO/IEC 14882:2020", Money{200.0F} ) ) );

   std::unique_ptr<Item> item4(
      std::make_unique<Tax>( 0.19,
         std::make_unique<Coupon>( Money{5.0F},
            std::make_unique<CppShirt>( Color::red, Money{15.0F} ) ) ) );

   std::unique_ptr<Item> item5(
      std::make_unique<ShoppingCart>( std::move(item1), std::move(item3), std::move(item4) ) );

   std::cout << "\n"
             //<< " Total price of item1 = " << item1->price() << "\n"
             << " Total price of item2 = " << item2->price() << "\n"
             //<< " Total price of item3 = " << item3->price() << "\n"
             //<< " Total price of item4 = " << item4->price() << "\n"
             << " Total price of item5 = " << item5->price() << "\n"
             << "\n";

   return EXIT_SUCCESS;
}

