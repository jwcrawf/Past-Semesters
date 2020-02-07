CC= gcc
CXX= g++ 

all: datacache.exe

.c.o:
	$(CC) -g -O0 -c -o $@ $<
.cpp.o:
	$(CXX) -g -O0 -c -o $@ $<  -std=c++11

datacache.exe: datacache.o
	$(CXX) -o datacache.exe datacache.o -std=c++11

.PHONY: clean

clean:
	rm -f *.o *~ \#*\#
