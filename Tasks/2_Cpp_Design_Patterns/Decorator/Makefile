#==================================================================================================
#
#  Makefile for subchapter "Decorator" of chapter "C++ Design Patterns"
#
#  Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================


# Compiler settings
CXX = g++
CXXFLAGS = -std=c++20 -Wall


# Setting the source and binary files
SRC = $(wildcard *.cpp)
BIN = $(SRC:.cpp=)


# Rules
default: Decorator_Allocator Decorator_CppFanShop Decorator_CppFanShop_2 \
         Decorator_Fantasy Decorator_Static SynchronizedPool

Decorator_Allocator: Decorator_Allocator.cpp
	$(CXX) $(CXXFLAGS) -o Decorator_Allocator Decorator_Allocator.cpp

Decorator_CppFanShop: Decorator_CppFanShop.cpp
	$(CXX) $(CXXFLAGS) -o Decorator_CppFanShop Decorator_CppFanShop.cpp

Decorator_CppFanShop_2: Decorator_CppFanShop_2.cpp
	$(CXX) $(CXXFLAGS) -o Decorator_CppFanShop_2 Decorator_CppFanShop_2.cpp

Decorator_Fantasy: Decorator_Fantasy.cpp
	$(CXX) $(CXXFLAGS) -o Decorator_Fantasy Decorator_Fantasy.cpp

Decorator_Static: Decorator_Static.cpp
	$(CXX) $(CXXFLAGS) -o Decorator_Static Decorator_Static.cpp

SynchronizedPool: SynchronizedPool.cpp
	$(CXX) $(CXXFLAGS) -o SynchronizedPool SynchronizedPool.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
