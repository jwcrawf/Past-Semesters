#
# makefile for function template project
#

CC = g++ -std=c++11 -Wall -Wextra -I.

all: charsort.x intsort.x stringsort.x idsort.x

intsort.x: tsort.h intsort.cpp
	$(CC) -o intsort.x intsort.cpp

charsort.x: tsort.h charsort.cpp
	$(CC) -o charsort.x charsort.cpp

stringsort.x: tsort.h stringsort.cpp
	$(CC) -o stringsort.x stringsort.cpp

idsort.x: id.o idsort.o cstringdiff.o 
	$(CC) -o idsort.x idsort.o id.o cstringdiff.o

idsort.o: tsort.h id.h idsort.cpp
	$(CC) -c idsort.cpp

cstringdiff.o: cstringdiff.h cstringdiff.cpp
	$(CC) -c cstringdiff.cpp

id.o: id.h id.cpp
	$(CC) -c id.cpp

