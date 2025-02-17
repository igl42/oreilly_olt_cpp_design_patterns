#==================================================================================================
#
#  Makefile for subchapter "Adapter" of chapter "C++ Design Patterns"
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
default: Adapter_2 LowerMatrix OptionalRefactoring_1 OptionalRefactoring_2 PyramidOfDoom

Adapter_2: Adapter_2.cpp
	$(CXX) $(CXXFLAGS) -o Adapter_2 Adapter_2.cpp

LowerMatrix: LowerMatrix.cpp
	$(CXX) $(CXXFLAGS) -o LowerMatrix LowerMatrix.cpp

OptionalRefactoring_1: OptionalRefactoring_1.cpp
	$(CXX) $(CXXFLAGS) -o OptionalRefactoring_1 OptionalRefactoring_1.cpp

OptionalRefactoring_2: OptionalRefactoring_2.cpp
	$(CXX) $(CXXFLAGS) -o OptionalRefactoring_2 OptionalRefactoring_2.cpp

PyramidOfDoom: PyramidOfDoom.cpp
	$(CXX) $(CXXFLAGS) -o PyramidOfDoom PyramidOfDoom.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
