/**************************************************************************************************
*
* \file Decorator_Allocator.cpp
* \brief C++ Training - Polymorphic Memory Resource (PMR) Programming Task
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Extend the following example for C++17 polymorphic memory resources:
*
* Step 1: Instead of going out of memory via 'std::pmr::null_memory_resource', provide a
*         'std::pmr::new_delete_resource' as backend allocator.
*
* Step 2: Track the dynamic memory allocations via a custom memory resource called 'MemoryTracker'.
*
* Step 3: Introduce an allocator called 'Mallocator', which builds on 'std::malloc' and
*         'std::free'.
*
* Step 4: Introduce an allocator called 'AlignedAllocator', which builds on 'std::aligned_alloc'
*         and 'std::free'.
*
* Step 5: Introduce a memory pool, which uses stack memory for allocation sizes below a certain
*         threshold and dynamic memory otherwise.
*
**************************************************************************************************/

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>
#include <memory_resource>
#include <string>
#include <vector>


/*!\brief Rounds up an integral value to the next multiple of a given factor.
//
// \param value The integral value to be rounded up \f$[1..\infty)\f$.
// \param factor The factor of the multiple \f$[1..\infty)\f$.
// \return The next multiple of the given factor.
//
// This function rounds up the given integral value to the next multiple of the given integral
// factor. In case the integral value is already a multiple of the given factor, the value itself
// is returned.
*/
template< typename T1, typename T2 >
constexpr auto nextMultiple( T1 value, T2 factor ) noexcept
{
   return ( value + ( factor - ( value % factor ) ) % factor );
}

/*!\brief Determines if a given integral value is a power of two.
//
// \param value The given integral value \f$[0..\infty)\f$.
// \return \a true if the given number is a power of 2, otherwise \a false.
*/
template< typename T >
constexpr bool isPowerOfTwo( T value )
{
   return value and not ( value & (value-T(1)) );
}


class MemoryTracker : public std::pmr::memory_resource
{
 public:
   explicit MemoryTracker( std::pmr::memory_resource* upstream = std::pmr::get_default_resource() )
      : upstream_{ upstream }
   {}

   explicit MemoryTracker( std::string prefix
                         , std::pmr::memory_resource* upstream = std::pmr::get_default_resource() )
      : upstream_{ upstream }
      , prefix_  { std::move(prefix) }
   {}

 private:
   void* do_allocate( size_t bytes, size_t alignment ) override
   {
      std::cout << prefix_ << "allocate " << bytes << " bytes\n";
      void* const ret = upstream_->allocate( bytes, alignment );
      return ret;
   }

   void do_deallocate( void* ptr, size_t bytes, size_t alignment ) override
   {
      std::cout << prefix_ << "deallocate " << bytes << " bytes\n";
      upstream_->deallocate( ptr, bytes, alignment );
   }

   bool do_is_equal( std::pmr::memory_resource const& other ) const noexcept override
   {
      if( this == &other ) return true;

      auto const* const tracker = dynamic_cast<MemoryTracker const*>( &other );
      return tracker != nullptr and
             tracker->prefix_ == prefix_ and
             upstream_->is_equal( *tracker->upstream_ );
   }

   std::pmr::memory_resource* upstream_{};
   std::string prefix_{};
};


class Mallocator : public std::pmr::memory_resource
{
 private:
   void* do_allocate( size_t bytes, [[maybe_unused]] size_t alignment ) override
   {
      return malloc( bytes );
   }

   void do_deallocate( void* ptr, [[maybe_unused]] size_t bytes
                     , [[maybe_unused]] size_t alignment ) override
   {
      free( ptr );
   }

   bool do_is_equal( std::pmr::memory_resource const& other ) const noexcept override
   {
      return ( this == &other ) or ( dynamic_cast<Mallocator const*>( &other ) != nullptr );
   }
};


class AlignedAllocator : public std::pmr::memory_resource
{
 private:
   void* do_allocate( size_t bytes, size_t alignment ) override
   {
      if( !isPowerOfTwo(alignment) ) {
         throw std::bad_alloc();
      }

      size_t const fixed_alignment = std::max( alignment, sizeof(void*) );
      size_t const fixed_bytes = nextMultiple( bytes, fixed_alignment );

#if defined(_MSC_VER)
      return _aligned_malloc( fixed_bytes, fixed_alignment );
#else
      return std::aligned_alloc( fixed_alignment, fixed_bytes );
#endif
   }

   void do_deallocate( void* ptr, [[maybe_unused]] size_t bytes
                     , [[maybe_unused]] size_t alignment ) override
   {
#if defined(_MSC_VER)
      _aligned_free( ptr );
#else
      std::free( ptr );
#endif
   }

   bool do_is_equal( std::pmr::memory_resource const& other ) const noexcept override
   {
      return ( this == &other ) or ( dynamic_cast<AlignedAllocator const*>( &other ) != nullptr );
   }
};


class MemoryPool : public std::pmr::memory_resource
{
 public:
   MemoryPool( std::size_t threshold, std::pmr::memory_resource* small
             , std::pmr::memory_resource* large )
      : threshold_{ threshold }
      , small_{ small }
      , large_{ large }
   {}

 private:
   void* do_allocate( size_t bytes, size_t alignment ) override
   {
      if( bytes < threshold_ ) {
         return small_->allocate( bytes, alignment );
      }
      else {
         return large_->allocate( bytes, alignment );
      }
   }

   void do_deallocate( void* ptr, size_t bytes, size_t alignment ) override
   {
      if( bytes < threshold_ ) {
         return small_->deallocate( ptr, bytes, alignment );
      }
      else {
         return large_->deallocate( ptr, bytes, alignment );
      }
   }

   bool do_is_equal( std::pmr::memory_resource const& other ) const noexcept override
   {
      if( this == &other ) return true;

      auto const* const pool = dynamic_cast<MemoryPool const*>( &other );
      return pool != nullptr and
             threshold_ == pool->threshold_ and
             small_->is_equal( *pool->small_ ) and
             large_->is_equal( *pool->large_ );
   }

   std::size_t threshold_{};
   std::pmr::memory_resource* small_{};
   std::pmr::memory_resource* large_{};
};


int main()
{
   std::array<std::byte,1000> raw;  // Note: not initialized!

   std::pmr::monotonic_buffer_resource buffer{ raw.data(), raw.size(), std::pmr::null_memory_resource() };
   MemoryTracker stack_tracker{ "Stack: ", &buffer };

   AlignedAllocator aligned_allocator{};
   MemoryTracker dynamic_tracker{ "Dynamic: ", &aligned_allocator };  // ... or alternatively std::pmr::new_delete_resource()

   MemoryPool pool{ 40U, &stack_tracker, &dynamic_tracker };

   std::pmr::vector<std::pmr::string> strings{ &pool };

   strings.emplace_back( "String longer than what SSO can handle" );
   strings.emplace_back( "Another long string that goes beyond SSO" );
   //strings.emplace_back( "A third long string that cannot be handled by SSO" );

   for( auto const& s : strings ) {
      std::cout << std::quoted(s) << '\n';
   }

   return EXIT_SUCCESS;
}
