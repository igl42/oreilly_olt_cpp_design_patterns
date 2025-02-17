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
default: Decorator_Allocator Decorator_CppFanShop_1 Decorator_CppFanShop_2 \
         Decorator_CppFanShop_3 Decorator_CppFanShop_CRTP Decorator_Fantasy_1 \
         Decorator_Fantasy_2 Decorator_PolicyBased

Decorator_Allocator: Decorator_Allocator.cpp
	$(CXX) $(CXXFLAGS) -o Decorator_Allocator Decorator_Allocator.cpp

Decorator_CppFanShop_1: Decorator_CppFanShop_1.cpp
	$(CXX) $(CXXFLAGS) -o Decorator_CppFanShop_1 Decorator_CppFanShop_1.cpp

Decorator_CppFanShop_2: Decorator_CppFanShop_2.cpp
	$(CXX) $(CXXFLAGS) -o Decorator_CppFanShop_2 Decorator_CppFanShop_2.cpp

Decorator_CppFanShop_3: Decorator_CppFanShop_3.cpp
	$(CXX) $(CXXFLAGS) -o Decorator_CppFanShop_3 Decorator_CppFanShop_3.cpp

Decorator_CppFanShop_CRTP: Decorator_CppFanShop_CRTP.cpp
	$(CXX) $(CXXFLAGS) -o Decorator_CppFanShop_CRTP Decorator_CppFanShop_CRTP.cpp

Decorator_Fantasy_1: Decorator_Fantasy_1.cpp
	$(CXX) $(CXXFLAGS) -o Decorator_Fantasy_1 Decorator_Fantasy_1.cpp

Decorator_Fantasy_2: Decorator_Fantasy_2.cpp
	$(CXX) $(CXXFLAGS) -o Decorator_Fantasy_2 Decorator_Fantasy_2.cpp

Decorator_PolicyBased: Decorator_PolicyBased.cpp
	$(CXX) $(CXXFLAGS) -o Decorator_PolicyBased Decorator_PolicyBased.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
