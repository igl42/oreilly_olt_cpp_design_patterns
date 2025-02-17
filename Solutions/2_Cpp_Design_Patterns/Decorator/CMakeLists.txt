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

add_executable(Decorator_CppFanShop_1
   Decorator_CppFanShop_1.cpp
   )

add_executable(Decorator_CppFanShop_2
   Decorator_CppFanShop_2.cpp
   )

add_executable(Decorator_CppFanShop_3
   Decorator_CppFanShop_3.cpp
   )

add_executable(Decorator_CppFanShop_CRTP
   Decorator_CppFanShop_CRTP.cpp
   )

add_executable(Decorator_Fantasy_1
   Decorator_Fantasy_1.cpp
   )

add_executable(Decorator_Fantasy_2
   Decorator_Fantasy_2.cpp
   )

add_executable(Decorator_PolicyBased
   Decorator_PolicyBased.cpp
   )

add_executable(Decorator_Allocator
   Decorator_Allocator.cpp
   )

set_target_properties(
   Decorator_Allocator
   Decorator_CppFanShop_1
   Decorator_CppFanShop_2
   Decorator_CppFanShop_3
   Decorator_CppFanShop_CRTP
   Decorator_Fantasy_1
   Decorator_Fantasy_2
   Decorator_PolicyBased
   PROPERTIES
   FOLDER "2_Cpp_Design_Patterns/Decorator"
   )
