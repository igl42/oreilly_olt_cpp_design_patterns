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


class MemoryTracker
{
   // Step 2: Track the dynamic memory allocations via a custom memory resource called 'MemoryTracker'.
};


class Mallocator
{
   // Step 3: Introduce an allocator called 'Mallocator', which builds on 'std::malloc'
   //         and 'std::free'.
};


class AlignedAllocator
{
   // Step 4: Introduce an allocator called 'AlignedAllocator', which builds on
   //         'std::aligned_alloc' and 'std::free'.
   // Note: 'std::aligned_alloc' is not available on MSVC (see the notes on
   //       https://en.cppreference.com/w/cpp/memory/c/aligned_alloc). You will
   //       have to use '_aligned_malloc()' and '_aligned_free()'.
};


class MemoryPool
{
   // Step 5: Introduce a memory pool, which uses stack memory for allocation sizes below a
   //         certain threshold and dynamic memory otherwise.
};


int main()
{
   std::array<std::byte,1000> raw;  // Note: not initialized!

   std::pmr::monotonic_buffer_resource buffer{ raw.data(), raw.size(), std::pmr::null_memory_resource() };

   std::pmr::vector<std::pmr::string> strings{ &buffer };

   strings.emplace_back( "String longer than what SSO can handle" );
   strings.emplace_back( "Another long string that goes beyond SSO" );
   strings.emplace_back( "A third long string that cannot be handled by SSO" );

   for( auto const& s : strings ) {
      std::cout << std::quoted(s) << '\n';
   }

   return EXIT_SUCCESS;
}
