# Makefile for asg6


CXX= g++ 

all: clean datacache.exe

.cpp.o:
	$(CXX) -g -O0 -c -o $@ $<  -std=c++11

datacache.exe: datacache.o
	$(CXX) -o datacache.exe datacache.o -std=c++11

.PHONY: clean

clean:
	rm -f *.o *~ \#*\#
