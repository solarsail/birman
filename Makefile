ROOT := $(PWD)
OUTDIR := $(ROOT)/bin
OBJDIR := $(ROOT)/bin/obj
SRC_DIR := $(ROOT)/src
INCLUDE_DIR := $(SRC_DIR)/include

CC := colorgcc
LIBS := -lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS := -c -g -std=c++11 -I$(INCLUDE_DIR)

export ROOT OUTDIR OBJDIR CC LIBS CXXFLAGS

.PHONY: sybsystem clean

sybsystem:
	@$(MAKE) -C src
	@$(MAKE) -C test

clean:
	rm -rf $(OUTDIR)
