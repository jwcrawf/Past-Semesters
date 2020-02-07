# makefile of Class ID project
#
# COP3330 
# Jon Crawford
# 9/20/17
#


all:		idtest1.x idtest2.x

idtest1.x :	idtest1.o id.o
	g++ -std=c++11 -Wall -Wextra -o idtest1.x idtest1.o id.o

idtest2.x :	idtest2.o id.o
	g++ -std=c++11 -Wall -Wextra -o idtest2.x idtest2.o id.o

idtest1.o :	idtest1.cpp id.h
	g++ -std=c++11 -Wall -Wextra -c -I. idtest1.cpp

idtest2.o :	idtest2.cpp id.h
	g++ -std=c++11 -Wall -Wextra -c -I. idtest2.cpp

id.o :	id.cpp id.h
	g++ -std=c++11 -Wall -Wextra -c -I. id.cpp
