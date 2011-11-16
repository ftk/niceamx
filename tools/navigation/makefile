CC = g++
CXXFLAGS = -Wall -std=c++0x -O3 -march=native

all: navigation

navigation: $(wildcard *.cpp *.h *.hpp)
	$(CC) $(CXXFLAGS) -o $@ *.cpp
