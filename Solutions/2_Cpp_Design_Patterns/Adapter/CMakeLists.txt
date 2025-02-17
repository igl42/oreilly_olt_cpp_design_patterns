#==================================================================================================
#
#  CMakeLists for subchapter "Adapter" of chapter "C++ Design Patterns"
#
#  Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================

cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

add_executable(Adapter_2
   Adapter_2.cpp
   )

add_executable(LowerMatrix
   LowerMatrix.cpp
   )

add_executable(OptionalRefactoring_1
   OptionalRefactoring_1.cpp
   )

add_executable(OptionalRefactoring_2
   OptionalRefactoring_2.cpp
   )

add_executable(PyramidOfDoom
   PyramidOfDoom.cpp
   )

set_target_properties(
   Adapter_2
   LowerMatrix
   OptionalRefactoring_1
   OptionalRefactoring_2
   PyramidOfDoom
   PROPERTIES
   FOLDER "2_Cpp_Design_Patterns/Adapter"
   )
