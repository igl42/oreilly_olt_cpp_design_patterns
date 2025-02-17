#==================================================================================================
#
#  Makefile for subchapter "Expression Templates" of chapter "C++ Design Patterns"
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
default: ExpressionTemplates_2 ExpressionTemplates_3 Niebloid Ranges

ExpressionTemplates_2: ExpressionTemplates_2.cpp
	$(CXX) $(CXXFLAGS) -o ExpressionTemplates_2 ExpressionTemplates_2.cpp

ExpressionTemplates_3: ExpressionTemplates_3.cpp
	$(CXX) $(CXXFLAGS) -o ExpressionTemplates_3 ExpressionTemplates_3.cpp

Niebloid: Niebloid.cpp
	$(CXX) $(CXXFLAGS) -o Niebloid Niebloid.cpp

Ranges: Ranges.cpp
	$(CXX) $(CXXFLAGS) -o Ranges Ranges.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
