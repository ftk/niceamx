CC = g++
override CXXFLAGS += -Wall -std=c++0x -O3

all: navigation

navigation: $(wildcard *.cpp *.h *.hpp)
	$(CC) $(CXXFLAGS) -o $@ $(wildcard *.cpp)
