CC= gcc
CXX= g++

all: clean cscan.exe

.c.o:
	$(CC) -c -o $@ $<
.cpp.o:
	$(CXX) -c -o $@ $<  -std=c++11

cscan.exe: cscan.o
	$(CXX) -o cscan.exe cscan.o -std=c++11

clean:
	rm -f *.o *~ \#*\# cscan.exe yours.txt diff.txt core
