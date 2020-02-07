# Makefile
# cop4531 Summer 2019 - list merge sort project
# Jon Crawford

CPP = /home/courses/cop4531p/LIB/cpp
TCPP = /home/courses/cop4531p/LIB/tcpp
GPH = /home/courses/cop4531p/LIB/graph
TST = /home/courses/cop4531p/LIB/tests
CC = g++ -Wall -Wextra -std=c++11 -I. -I$(CPP) -I$(TCPP) -I$(TST) -I$(GPH)

all: lsort.x qsort.x sortspy.x ranstring.x ranuint.x
std: lsort.x qsort.x sortspy.x

lsort.x: lsort.cpp
	$(CC) -o lsort.x lsort.cpp

qsort.x: qsort.cpp
	$(CC) -o qsort.x qsort.cpp

sortspy.x: sortspy.cpp
	$(CC) -o sortspy.x sortspy.cpp

ranstring.x: ranstring.cpp
	$(CC) -o ranstring.x ranstring.cpp

ranuint.x: ranuint.cpp
	$(CC) -o ranuint.x ranuint.cpp
