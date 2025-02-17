/**************************************************************************************************
*
* \file LowerMatrix.cpp
* \brief C++ Training - Adapter vs. Decorator Design Patterns
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement an adapter for the given 'DynamicMatrix' and 'StaticMatrix' class templates
*       that represents a lower triangular matrix (i.e. all elements above the diagonal are 0).
*
**************************************************************************************************/

#include <cstddef>
using std::size_t;


//---- <Memory.h> ---------------------------------------------------------------------------------

#include <new>
#include <type_traits>

template< typename Type >
Type* allocate( size_t size )
{
   static_assert( std::is_fundamental<Type>::value, "Invalid data type detected" );

   return new Type[size];
}


template< typename Type >
void deallocate( Type* address )
{
   static_assert( std::is_fundamental<Type>::value, "Invalid data type detected" );

   delete address;
}


//---- <Utility.h> --------------------------------------------------------------------------------

#include <algorithm>
#include <initializer_list>

template< typename Type >
constexpr size_t determineColumns( std::initializer_list< std::initializer_list<Type> > list )
{
   size_t cols( 0UL );

   for( auto const& rowList : list ) {
      cols = std::max( cols, rowList.size() );
   }

   return cols;
}


//---- <DenseMatrix.h> ----------------------------------------------------------------------------

#include <ostream>

template< typename Derived >
class DenseMatrix
{
 protected:
   ~DenseMatrix() = default;

 public:
   constexpr Derived&       derived()       { return static_cast<Derived&>(*this); }
   constexpr Derived const& derived() const { return static_cast<Derived const&>(*this); }

   constexpr size_t rows() const { return derived().rows(); }
   constexpr size_t cols() const { return derived().cols(); }

   constexpr decltype(auto) operator()( size_t i, size_t j )       { return derived()(i,j); }
   constexpr decltype(auto) operator()( size_t i, size_t j ) const { return derived()(i,j); }
};

template< typename Derived >
std::ostream& operator<<( std::ostream& os, DenseMatrix<Derived> const& matrix )
{
   size_t const rows( matrix.rows() );
   size_t const cols( matrix.cols() );

   for( size_t i=0U; i<rows; ++i ) {
      os << "(";
      for( size_t j=0U; j<cols; ++j ) {
         os << " " << matrix(i,j);
      }
      os << " )\n";
   };

   return os;
}


//---- <DynamicMatrix.h> --------------------------------------------------------------------------

//#include <Utility.h>
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <type_traits>

template< typename Type >
class DynamicMatrix
   : public DenseMatrix< DynamicMatrix<Type> >
{
 public:
   using value_type = Type;
   using reference = value_type&;
   using const_reference = value_type const&;

   DynamicMatrix() = default;

   DynamicMatrix( size_t rows, size_t cols )
      : rows_( rows )
      , cols_( cols )
      , vals_( allocate<Type>( rows*cols ) )
   {}

   DynamicMatrix( size_t rows, size_t cols, Type const& init )
      : rows_( rows )
      , cols_( cols )
      , vals_( allocate<Type>( rows*cols ) )
   {
      std::fill_n( vals_, rows*cols, init );
   }

   explicit DynamicMatrix( std::initializer_list< std::initializer_list<Type> > list )
      : rows_( list.size() )
      , cols_( determineColumns(list) )
      , vals_( allocate<Type>( rows_*cols_ ) )
   {
      size_t i( 0U );

      for( auto const& rowList : list ) {
         std::fill( std::copy( rowList.begin(), rowList.end(), data(i) ), data(i+1U), Type{} );
         ++i;
      }
   }

   DynamicMatrix( DynamicMatrix const& rhs )
      : rows_( rhs.rows_ )
      , cols_( rhs.cols_ )
      , vals_( allocate<Type>( allocate<Type>( rows_*cols_ ) ) )
   {
      assign( rhs );
   }

   DynamicMatrix( DynamicMatrix&& rhs ) noexcept
      : rows_( rhs.rows_ )
      , cols_( rhs.cols_ )
      , vals_( rhs.vals_ )
   {
      rhs.rows_ = 0U;
      rhs.cols_ = 0U;
      rhs.vals_ = nullptr;
   }

   ~DynamicMatrix()
   {
      deallocate( vals_ );
   }

   DynamicMatrix& operator=( std::initializer_list< std::initializer_list<Type> > list )
   {
      DynamicMatrix tmp( list );
      std::swap( rows_, tmp.rows_ );
      std::swap( cols_, tmp.cols_ );
      std::swap( vals_, tmp.vals_ );
      return *this;
   }

   DynamicMatrix& operator=( DynamicMatrix const& rhs )
   {
      if( rhs.rows_ != rows_ || rhs.cols_ != cols_ ) {
         throw std::invalid_argument( "Matrix sizes do not match" );
      }

      assign( rhs );

      return *this;
   }

   DynamicMatrix& operator=( DynamicMatrix&& rhs ) noexcept
   {
      deallocate( vals_ );

      rows_ = rhs.rows_;
      cols_ = rhs.cols_;
      vals_ = rhs.vals_;

      rhs.rows_ = 0U;
      rhs.cols_ = 0U;
      rhs.vals_ = nullptr;

      return *this;
   }

   size_t rows() const { return rows_; }
   size_t cols() const { return cols_; }

   Type*       data( size_t i )       { return vals_+i*cols_; }
   Type const* data( size_t i ) const { return vals_+i*cols_; }

   reference operator()( size_t row, size_t col )
   {
      assert( row < rows_ );
      assert( col < cols_ );
      return vals_[row*cols_+col];
   }

   const_reference operator()( size_t row, size_t col ) const
   {
      assert( row < rows_ );
      assert( col < cols_ );
      return vals_[row*cols_+col];
   }

 private:
   template< typename MT >
   void assign( MT const& m )
   {
      size_t const total( rows_*cols_ );
      std::copy_n( m.vals_, total, vals_ );
   }

   size_t rows_{ 0UL };
   size_t cols_{ 0UL };
   Type*  vals_{ nullptr };

   static_assert( std::is_fundamental<Type>::value, "Invalid data type detected" );
};


//---- <StaticMatrix.h> --------------------------------------------------------------------------

//#include <Utility.h>
#include <algorithm>
#include <cassert>
#include <type_traits>

template< typename Type, size_t Rows, size_t Cols >
class StaticMatrix
   : public DenseMatrix< StaticMatrix<Type,Rows,Cols> >
{
 public:
   using value_type = Type;
   using reference = value_type&;
   using const_reference = value_type const&;

   StaticMatrix()
      : StaticMatrix( Type{} )
   {}

   StaticMatrix( Type const& init )
   {
      for( size_t i=0U; i<Rows; ++i ) {
         std::fill_n( vals_[i], Cols, init );
      }
   }

   explicit StaticMatrix( std::initializer_list< std::initializer_list<Type> > list )
   {
      size_t i( 0U );

      for( auto const& rowList : list ) {
         std::fill( std::copy( rowList.begin(), rowList.end(), data(i) ), data(i+1U), Type{} );
         ++i;
      }
   }

   StaticMatrix& operator=( std::initializer_list< std::initializer_list<Type> > list )
   {
      size_t i( 0U );

      for( auto const& rowList : list ) {
         std::fill( std::copy( rowList.begin(), rowList.end(), data(i) ), data(i+1U), Type{} );
         ++i;
      }

      return *this;
   }

   size_t rows() const { return Rows; }
   size_t cols() const { return Cols; }

   Type*       data( size_t i )       { return vals_[i]; }
   Type const* data( size_t i ) const { return vals_[i]; }

   reference operator()( size_t row, size_t col )
   {
      assert( row < Rows );
      assert( col < Cols );
      return vals_[row][col];
   }

   const_reference operator()( size_t row, size_t col ) const
   {
      assert( row < Rows );
      assert( col < Cols );
      return vals_[row][col];
   }

 private:
   Type vals_[Rows][Cols]{};

   static_assert( std::is_fundamental<Type>::value, "Invalid data type detected" );
   static_assert( Rows > 0U, "Invalid number of rows detected" );
   static_assert( Cols > 0U, "Invalid number of columns detected" );
};


//---- <LowerMatrix.h> ----------------------------------------------------------------------------

template< typename MatrixType >
class LowerMatrix
{
   // TODO: Implement an adapter for the given 'DynamicMatrix' and 'StaticMatrix' class
   //       templates that represents a lower triangular matrix (i.e. all elements above
   //       the diagonal are 0).
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <DynamicMatrix.h>
#include <cstdlib>
#include <iostream>

int main()
{
   /*
   LowerMatrix<DynamicMatrix<int>> L( 3U );
   L(0,0) = 1;
   L(1,0) = 2;
   L(1,1) = 3;
   L(2,0) = 4;
   L(2,1) = 5;
   L(2,2) = 6;

   std::cout << '\n' << L << '\n';
   */

   return EXIT_SUCCESS;
}
