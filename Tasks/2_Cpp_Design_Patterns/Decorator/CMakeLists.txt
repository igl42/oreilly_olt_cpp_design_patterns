#==================================================================================================
#
#  CMakeLists for subchapter "Decorator" of chapter "C++ Design Patterns"
#
#  Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================

cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

add_executable(Decorator_Allocator
   Decorator_Allocator.cpp
   )

add_executable(Decorator_CppFanShop
   Decorator_CppFanShop.cpp
   )

add_executable(Decorator_CppFanShop_2
   Decorator_CppFanShop_2.cpp
   )

add_executable(Decorator_Fantasy
   Decorator_Fantasy.cpp
   )

add_executable(Decorator_Static
   Decorator_Static.cpp
   )

add_executable(SynchronizedPool
   SynchronizedPool.cpp
   )

set_target_properties(
   Decorator_Allocator
   Decorator_CppFanShop
   Decorator_CppFanShop_2
   Decorator_Fantasy
   Decorator_Static
   SynchronizedPool
   PROPERTIES
   FOLDER "2_Cpp_Design_Patterns/Decorator"
   )
