# 
#  makefile for DOT Common Carrier Project
#	
#  Jon Crawford
#  
#  10/16/17
#

all: stester.x vtester.x

vtester.x : vtester.o vehicles.o shapes.o
	g++ -std=c++11 -Wall -Wextra -o vtester.x vtester.o vehicles.o shapes.o

stester.x : stester.o shapes.o
	g++ -std=c++11 -Wall -Wextra -o stester.x stester.o shapes.o

stester.o : stester.cpp shapes.h
	g++ -std=c++11 -Wall -Wextra -c -I. stester.cpp

shapes.o : shapes.cpp shapes.h
	g++ -std=c++11 -Wall -Wextra -c -I. shapes.cpp

vehicles.o : vehicles.cpp vehicles.h shapes.h
	g++ -std=c++11 -Wall -Wextra -c -I. vehicles.cpp

vtester.o : vtester.cpp vehicles.h shapes.h
	g++ -std=c++11 -Wall -Wextra -c -I. vtester.cpp
