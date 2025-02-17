#==================================================================================================
#
#  CMakeLists for subchapter "Expression Templates" of chapter "C++ Design Patterns"
#
#  Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================

cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

add_executable(ExpressionTemplates
   ExpressionTemplates.cpp
   )

add_executable(Niebloid
   Niebloid.cpp
   )

add_executable(Ranges
   Ranges.cpp
   )

add_executable(Ranges_std
   Ranges_std.cpp
   )

set_target_properties(
   ExpressionTemplates
   Niebloid
   Ranges
   Ranges_std
   PROPERTIES
   FOLDER "2_Cpp_Design_Patterns/Expression_Templates"
   )
