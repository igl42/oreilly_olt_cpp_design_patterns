/**************************************************************************************************
*
* \file SynchronizedPool.cpp
* \brief C++ Training - Polymorphic Memory Resource (PMR) Programming Task
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Compare the allocation behavior of the following two options.
*
* Option 1: Use a 'std::map' equipped with a 'std::allocator'.
*
* Option 2: Use a 'std::pmr::map' equiped with a 'std::pmr::synchronized_pool' allocator.
*
**************************************************************************************************/

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <map>
#include <memory_resource>
#include <random>
#include <string>
#include <vector>


class MemoryTracker
   : public std::pmr::memory_resource
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

   bool do_is_equal( const std::pmr::memory_resource& other ) const noexcept override
   {
      if( this == &other ) return true;

      const auto* const tracker = dynamic_cast<const MemoryTracker*>( &other );
      return tracker != nullptr &&
             tracker->prefix_ == prefix_ &&
             upstream_->is_equal( *tracker->upstream_ );
   }

   std::pmr::memory_resource* upstream_{};
   std::string prefix_{};
};


int main()
{
   // Option 1: Using default memory allocation
   std::map<long,std::string> collection{};

   // Option 2: Using an 'synchronized_pool_resource'
   //MemoryTracker tracker{};
   //std::pmr::synchronized_pool_resource pool{ &tracker };
   //std::pmr::map<long,std::string> collection{ &pool };


   std::random_device rd{};
   std::mt19937 mt{ rd() };
   std::uniform_int_distribution<size_t> dist( 10UL, 1000UL );

   std::vector<std::string> vec{};  // Used to simulate in-between memory allocations

   // Setup of the map
   for( long i=0L; i<20L; ++i ) {
      std::string s{ "Customer" + std::to_string(i) };
      collection.emplace( i, s );
      vec.emplace_back( std::string( dist(mt), '.' ) );
   }

   // Printing the distance between the map elements
   for( const auto& elem : collection ) {
      static long long lastVal = 0LL;
      const long long val = reinterpret_cast<long long>( &elem );
      std::cout << "diff: " << ( val - lastVal ) << '\n';
      lastVal = val;
   }

   return EXIT_SUCCESS;
}
