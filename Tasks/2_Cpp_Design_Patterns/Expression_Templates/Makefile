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
default: ExpressionTemplates Niebloid Ranges Ranges_std

ExpressionTemplates: ExpressionTemplates.cpp
	$(CXX) $(CXXFLAGS) -o ExpressionTemplates ExpressionTemplates.cpp

Niebloid: Niebloid.cpp
	$(CXX) $(CXXFLAGS) -o Niebloid Niebloid.cpp

Ranges: Ranges.cpp
	$(CXX) $(CXXFLAGS) -o Ranges Ranges.cpp

Ranges_std: Ranges_std.cpp
	$(CXX) $(CXXFLAGS) -o Ranges_std Ranges_std.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
