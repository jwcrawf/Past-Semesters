#
# makefile for Queue
# Jon Crawford
# 12/9/2017 
#

CC = g++ -std=c++11 -Wall -Wextra -I.

all: fqueue.x constTest.x in2post.x

fqueue.x: tqueue.h id.h fqueue.cpp
	$(CC) -o fqueue.x fqueue.cpp

constTest.x: tqueue.h constTest.cpp
	$(CC) -o constTest.x constTest.cpp

in2post.x: tstack.h tqueue.h in2post.cpp
	$(CC) -o in2post.x in2post.cpp

fqueue.o: tqueue.h id.h fqueue.cpp
	$(CC) -c fqueue.cpp

constTest.o: tqueue.h constTest.cpp
	$(CC) -c constTest.cpp

in2post.o: tstack.h tqueue.h in2post.cpp
	$(CC) -c in2post.cpp
