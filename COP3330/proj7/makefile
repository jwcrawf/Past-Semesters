#
# makefile for stack
# Jon Crawford
# 12/2/2017 
#

CC = g++ -std=c++11 -Wall -Wextra -I.

all: fstack.x constTest.x

fstack.x: tstack.h id.h fstack.cpp
	$(CC) -o fstack.x fstack.cpp

constTest.x: tstack.h constTest.cpp
	$(CC) -o constTest.x constTest.cpp

fstack.o: tstack.h id.h fstack.cpp
	$(CC) -c fstack.cpp

constTest.o: tstack.h constTest.cpp
	$(CC) -c constTest.cpp
