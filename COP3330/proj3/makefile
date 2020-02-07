#
# makefile for Prime project
# 9/22/2017
# Jon Crawford
#


LIB      = /home/courses/cop3330p/LIB
CC       = g++ -std=c++11 -I. -I$(LIB)/cpp -Wall -Wextra

all:      fbitvect.x fprime.x prime_below.x

fbitvect.x: prime.o bitvect.o fbitvect.o
	$(CC) -o fbitvect.x prime.o fbitvect.o bitvect.o

prime_below.x: prime.o bitvect.o prime_below.o
	$(CC) -o prime_below.x prime.o prime_below.o bitvect.o

fprime.x: prime.o bitvect.o fprime.o
	$(CC) -o fprime.x prime.o bitvect.o fprime.o

bitvect.o: bitvect.cpp # bitvect.h
	$(CC) -c bitvect.cpp

fbitvect.o: fbitvect.cpp prime.h # bitvect.h
	$(CC) -c fbitvect.cpp

fprime.o: fprime.cpp  prime.h # bitvect.h
	$(CC) -c fprime.cpp

prime.o: prime.cpp  prime.h  # bitvect.h
	$(CC) -c prime.cpp

prime_below.o: prime_below.cpp  prime.h
	$(CC) -c prime_below.cpp

