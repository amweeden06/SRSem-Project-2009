# This sample Makefile allows you to make an OpenGL application
#   whose source is exactly one .c , .cpp or .cc file.
#
#
# To use this Makefile, you type:
#
#        make xxxx
#
# where
#       xxxx.c or xxxx.cpp is the name of the file you wish to compile 
#       
# A binary named xxxx will be produced
#
# Additional sources for the make can passed as the value of SRCS on 
#  the command line:
#      make SRCS="yyyy.o zzzz.o" xxxx
#
# Proper location of libraries depends on the ENV variable OSTYPE
# To insure this is picked up, you should export OSTYPE prior to running make
#                  

GLTYPES = gltypes.1

EXPENDABLES = main.o Display.o Wall.o Player.o MenuBar.o MenuButton.o
EXECUTABLES = Sewers
CFLAGS = -Wall -ggdb

CC = gcc 

CPP = g++

CPPFLAGS = $(CFLAGS)

# default
ifndef OSTYPE
OSTYPE = linux-gnu
endif
#


# OSX
ifeq ($(findstring darwin,$(OSTYPE)), darwin)
INCLUDES = -I/sw/include -I/usr/X11R6/include 
LDLIBS = -lglui -L/sw/lib -L/usr/X11R6/lib -lX11 -lGL -lGLU -lglut -lXmu -lm 
endif
#

# FreeBSD
ifeq ($(findstring freebsd,$(OSTYPE)), freebsd)
INCLUDES = -I/usr/X11R6/include 
LDLIBS = -lglui -L/usr/X11R6/lib -lX11 -lGL -lGLU -lglut -lXmu -lm 
endif
#

# linux
ifeq ($(findstring linux,$(OSTYPE)), linux)
INCLUDES =  
LDLIBS = -lglui -lX11 -lGL -lGLU -lglut -lXmu -lXi -lm 
endif
#

Sewers: main.o Display.o Player.o Wall.o MenuBar.o MenuButton.o $(GLTYPES).h $(GLTYPES).o
	g++ $(CPPFLAGS) $(LDLIBS) $(GLTYPES).o main.o Display.o Player.o Wall.o MenuBar.o MenuButton.o -o Sewers

main.o: main.cpp Display.hpp $(GLTYPES).h $(GLTYPES).o
	g++ $(CPPFLAGS) $(INCLUDES) -c main.cpp

Display.o: Display.cpp Display.hpp Player.hpp Wall.hpp MenuBar.hpp $(GLTYPES).h $(GLTYPES).o
	g++ $(CPPFLAGS) $(INCLUDES) -c Display.cpp

Player.o: Player.cpp Player.hpp component.h $(GLTYPES).h $(GLTYPES).o
	g++ $(CPPFLAGS) $(INCLUDES) -c Player.cpp

Wall.o: Wall.cpp component.h $(GLTYPES).h $(GLTYPES).o
	g++ $(CPPFLAGS) $(INCLUDES) -c Wall.cpp

MenuBar.o: MenuBar.cpp MenuBar.hpp MenuButton.hpp component.h $(GLTYPES).h $(GLTYPES).o
	g++ $(CPPFLAGS) $(INCLUDES) -c MenuBar.cpp

MenuButton.o: MenuButton.cpp MenuButton.hpp component.h $(GLTYPES).h $(GLTYPES).o
	g++ $(CPPFLAGS) $(INCLUDES) -c MenuButton.cpp

clean:
	rm -f $(EXPENDABLES)

distclean:
	rm -f $(EXPENDABLES) $(EXECUTABLES)

all:
	rm -f $(EXPENDABLES) $(EXECUTABLES)
	@make $(EXECUTABLES)
