#==================================================================================================
#
#  Makefile for chapter "C++ Design Patterns"
#
#  Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================


# Build rules
default:
	@$(MAKE) --no-print-directory -C ./Adapter
	@$(MAKE) --no-print-directory -C ./CRTP
	@$(MAKE) --no-print-directory -C ./Decorator
	@$(MAKE) --no-print-directory -C ./Expression_Templates


# Cleanup
clean:
	@$(MAKE) --no-print-directory -C ./Adapter clean
	@$(MAKE) --no-print-directory -C ./CRTP clean
	@$(MAKE) --no-print-directory -C ./Decorator clean
	@$(MAKE) --no-print-directory -C ./Expression_Templates clean


# Setting the independent commands
.PHONY: default clean
