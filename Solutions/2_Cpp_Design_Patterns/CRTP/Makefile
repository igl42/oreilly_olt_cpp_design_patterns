#==================================================================================================
#
#  Makefile for subchapter "CRTP" of chapter "C++ Design Patterns"
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
default: CRTP CRTP_Concept StrongType_CRTP

CRTP: CRTP.cpp
	$(CXX) $(CXXFLAGS) -o CRTP CRTP.cpp

CRTP_Concept: CRTP_Concept.cpp
	$(CXX) $(CXXFLAGS) -o CRTP_Concept CRTP_Concept.cpp

StrongType_CRTP: StrongType_CRTP.cpp
	$(CXX) $(CXXFLAGS) -o StrongType_CRTP StrongType_CRTP.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
