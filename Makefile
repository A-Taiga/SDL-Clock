CXXFLAGS = `pkg-config --libs --cflags sdl2` `pkg-config --libs --cflags SDL2_ttf`
CC = clang++ -std=c++20 -g -Wall -Wextra -pedantic -Wshadow -I /opt/homebrew/include

OBJDIR = obj/
SRCDIR = src/
VPATH = src: obj:

objects = main.o text.o window.o
exeName = SDL-Clock

all: $(exeName)

$(exeName): $(objects)
	$(CC) $^ -o $@ $(CXXFLAGS)

$(OBJDIR)main.o: main.cpp text.hpp window.hpp utility.hpp texts.hpp
	$(CC) -c -o $@ $<

$(OBJDIR)window.o: window.cpp
	$(CC) -c -o $@ $<

$(OBJDIR)text.o: text.cpp utility.hpp
	$(CC) -c -o $@ $<


.PHONY: clean run
clean:
	-rm $(OBJDIR)*.o $(exeName)
run:
	./$(exeName)