/**************************************************************************************************
*
* \file CRTP.cpp
* \brief C++ Training - Example for the CRTP Design Pattern
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Implement a common output operator and L2-norm for different kinds of 'DenseVector'
*         by means of the CRTP design pattern.
*
* Step 2: Implement an addition operation between different kinds of 'DenseVector'.
*
**************************************************************************************************/

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>


//---- <DenseVector.h> ----------------------------------------------------------------------------

// Step 1: Implement a common output operator and L2-norm for different kinds of 'DenseVector'
//         by means of the CRTP design pattern.


//---- <DynamicVector.h> --------------------------------------------------------------------------

template< typename T >
class DynamicVector
{
 public:
   using value_type     = T;
   using iterator       = typename std::vector<T>::iterator;
   using const_iterator = typename std::vector<T>::const_iterator;

   DynamicVector() = default;
   DynamicVector( std::initializer_list<T> init )
      : values_( std::begin(init), std::end(init) )
   {}

   size_t size() const { return values_.size(); }

   T&       operator[]( size_t index )       { return values_[index]; }
   T const& operator[]( size_t index ) const { return values_[index]; }

   iterator       begin()       { return values_.begin(); }
   const_iterator begin() const { return values_.begin(); }
   iterator       end()         { return values_.end(); }
   const_iterator end()   const { return values_.end(); }

   // ... Many numeric functions

 private:
   std::vector<T> values_;
};

template< typename T >
std::ostream& operator<<( std::ostream& os, DynamicVector<T> const& vector )
{
   size_t const size( vector.size() );

   os << "(";
   for( size_t i=0U; i<size; ++i ) {
      os << " " << vector[i];
   }
   os << " )";

   return os;
}

template< typename T >
constexpr auto l2norm( DynamicVector<T> const& vector )
{
   return std::sqrt( std::inner_product( std::begin(vector), std::end(vector)
                                       , std::begin(vector), T{} ) );
}


//---- <StaticVector.h> ---------------------------------------------------------------------------

template< typename T, size_t Size >
class StaticVector
{
 public:
   using value_type     = T;
   using iterator       = typename std::array<T,Size>::iterator;
   using const_iterator = typename std::array<T,Size>::const_iterator;

   constexpr StaticVector() = default;
   constexpr StaticVector( std::initializer_list<T> init )
   {
      assert( init.size() == Size );
      std::copy( std::begin(init), std::end(init), std::begin(values_) );
   }

   constexpr size_t size() const { return values_.size(); }

   constexpr T&       operator[]( size_t index )       { return values_[index]; }
   constexpr T const& operator[]( size_t index ) const { return values_[index]; }

   constexpr iterator       begin()       { return values_.begin(); }
   constexpr const_iterator begin() const { return values_.begin(); }
   constexpr iterator       end()         { return values_.end(); }
   constexpr const_iterator end()   const { return values_.end(); }

   // ... Many numeric functions

 private:
   std::array<T,Size> values_;
};

template< typename T, size_t Size >
std::ostream& operator<<( std::ostream& os, StaticVector<T,Size> const& vector )
{
   size_t const size( vector.size() );

   os << "(";
   for( size_t i=0U; i<size; ++i ) {
      os << " " << vector[i];
   }
   os << " )";

   return os;
}

template< typename T, size_t Size >
constexpr auto l2norm( StaticVector<T,Size> const& vector )
{
   return std::sqrt( std::inner_product( std::begin(vector), std::end(vector)
                                       , std::begin(vector), T{} ) );
}


//---- <Addition.h> -------------------------------------------------------------------------------

// Step 2: Implement an addition operation between different kinds of 'DenseVector'.
// ... operator+() ...


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   DynamicVector<int>    const a{ 1, 2, 3 };
   StaticVector<int,3UL> const b{ 4, 5, 6 };

   // Step 1
   std::cout << "\n"
             << " a = " << a << ", L2-norm = " << l2norm(a) << "\n"
             << " b = " << b << ", L2-norm = " << l2norm(b) << "\n"
             << "\n";

   // Step 2
   //std::cout << " a + b = " << ( a + b ) << "\n"
   //          << "\n";

   return EXIT_SUCCESS;
}
