/**************************************************************************************************
*
* \file Ranges_Benchmark.cpp
* \brief C++ Training - Ranges Performance Benchmark
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Copy-and-paste the following code into 'quick-bench.com'. Benchmark the time to filter
*       and transform a certain number of integers.
*
**************************************************************************************************/

#include <algorithm>
#include <iostream>
#include <random>
#include <ranges>
#include <stdexcept>
#include <vector>


//---- Benchmark configuration --------------------------------------------------------------------

constexpr size_t size( 200 );  // Size of the generated container (suggestions: 200 and 20000)
constexpr size_t iterations( 500 );  // Number of benchmark iterations (suggestions: 500 and 25)

#define BENCHMARK_FILTER_TRANSFORM 1
#define BENCHMARK_TRANSFORM_FILTER 0


//---- Benchmark setup ----------------------------------------------------------------------------

std::random_device rd{};
std::mt19937 mt{ rd() };

std::vector<int> generateNumbers()
{
   std::vector<int> v( size );

   std::uniform_int_distribution<int> dist( 0, size );

   for( int& i : v ) {
      i = dist(mt);
   }

   return v;
}

const auto numbers( generateNumbers() );


//---- Utility functions --------------------------------------------------------------------------

int compute( int i ) { return (i/3)*3; }
bool isEven( int i ) { return i%2==0; }
bool isOdd( int i ) { return i%2==1; }


//---- Benchmark for STL algorithms (filter/transform) --------------------------------------------

static void STL_Filter_Transform(benchmark::State& state)
{
   std::vector<int> resultNumbers{};

   resultNumbers.reserve( size );

   for( auto _ : state )
   {
      std::copy_if( begin(numbers), end(numbers)
                  , std::back_inserter(resultNumbers)
                  , [](int i){ return isOdd(i); } );
      std::transform( begin(resultNumbers), end(resultNumbers)
                    , begin(resultNumbers)
                    , [](int i){ return compute(i); } );

      if( resultNumbers.size() == 0UL ) std::cerr << " ERROR!!!\n";

      state.PauseTiming();
      resultNumbers.clear();
      state.ResumeTiming();
   }
}
#if BENCHMARK_FILTER_TRANSFORM
BENCHMARK(STL_Filter_Transform)->Iterations(iterations);
#endif


//---- Benchmark for ranges (filter/transform) ----------------------------------------------------

static void Ranges_Filter_Transform(benchmark::State& state)
{
   std::vector<int> resultNumbers{};
   resultNumbers.reserve( size );

   for( auto _ : state )
   {
      auto result = numbers
                  | std::ranges::views::filter( [](int i){ return isOdd(i); } )
                  | std::ranges::views::transform( [](int i){ return compute(i); } );

      resultNumbers.assign( begin(result), end(result) );

      if( resultNumbers.size() == 0UL ) std::cerr << " ERROR!!!\n";

      state.PauseTiming();
      resultNumbers.clear();
      state.ResumeTiming();
   }
}
#if BENCHMARK_FILTER_TRANSFORM
BENCHMARK(Ranges_Filter_Transform)->Iterations(iterations);
#endif


//---- Benchmark for manual for loop (filter/transform) -------------------------------------------

static void Manual_Filter_Transform(benchmark::State& state)
{
   std::vector<int> resultNumbers{};
   resultNumbers.reserve( size );

   for( auto _ : state )
   {
      for( int i : numbers ) {
         if( isOdd(i) ) {
            resultNumbers.push_back( compute(i) );
         }
      }

      if( resultNumbers.size() == 0UL ) std::cerr << " ERROR!!!\n";

      state.PauseTiming();
      resultNumbers.clear();
      state.ResumeTiming();
   }
}
#if BENCHMARK_FILTER_TRANSFORM
BENCHMARK(Manual_Filter_Transform)->Iterations(iterations);
#endif


//---- Benchmark for STL algorithms (transform/filter) --------------------------------------------

static void STL_Transform_Filter(benchmark::State& state)
{
   std::vector<int> transformedNumbers{};
   std::vector<int> resultNumbers{};

   transformedNumbers.reserve( size );
   resultNumbers.reserve( size );

   for( auto _ : state )
   {
      std::transform( begin(numbers), end(numbers)
                    , std::back_inserter(transformedNumbers)
                    , [](int i){ return compute(i); } );
      std::copy_if( begin(transformedNumbers), end(transformedNumbers)
                  , std::back_inserter(resultNumbers)
                  , [](int i){ return isOdd(i); } );

      if( resultNumbers.size() == 0UL ) std::cerr << " ERROR!!!\n";

      state.PauseTiming();
      transformedNumbers.clear();
      resultNumbers.clear();
      state.ResumeTiming();
   }
}
#if BENCHMARK_TRANSFORM_FILTER
BENCHMARK(STL_Transform_Filter)->Iterations(iterations);
#endif


//---- Benchmark for ranges (transform/filter) ----------------------------------------------------

static void Ranges_Transform_Filter(benchmark::State& state)
{
   std::vector<int> resultNumbers{};
   resultNumbers.reserve( size );

   for( auto _ : state )
   {
      auto result = numbers
                  | std::ranges::views::transform( [](int i){ return compute(i); } )
                  | std::ranges::views::filter( [](int i){ return isOdd(i); } );

      resultNumbers.assign( begin(result), end(result) );

      if( resultNumbers.size() == 0UL ) std::cerr << " ERROR!!!\n";

      state.PauseTiming();
      resultNumbers.clear();
      state.ResumeTiming();
   }
}
#if BENCHMARK_TRANSFORM_FILTER
BENCHMARK(Ranges_Transform_Filter)->Iterations(iterations);
#endif


//---- Benchmark for manual for loop (transform/filter) -------------------------------------------

static void Manual_Transform_Filter(benchmark::State& state)
{
   std::vector<int> resultNumbers{};
   resultNumbers.reserve( size );

   for( auto _ : state )
   {
      for( int i : numbers ) {
         const int tmp( compute(i) );
         if( isOdd(tmp) ) {
            resultNumbers.push_back( tmp );
         }
      }

      if( resultNumbers.size() == 0UL ) std::cerr << " ERROR!!!\n";

      state.PauseTiming();
      resultNumbers.clear();
      state.ResumeTiming();
   }
}
#if BENCHMARK_TRANSFORM_FILTER
BENCHMARK(Manual_Transform_Filter)->Iterations(iterations);
#endif

