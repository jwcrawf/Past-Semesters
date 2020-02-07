# makefile of Class ID project
#
# COP3330 
# Jon Crawford
# 9/20/17
#


idtest1.x : idtest1.o id.o
	g++11 -std=c++11 idtest1.x -o idtest1.o id.o

idtest2.x : idtest2.o id.o
	g++11 -std=c++11 idtest2.x -o idtest2.o id.o

id.o : id.h id.cpp
	g++11 -std=c++11 -Wall -Wextra -c -I. id.cpp

idtest1.o : id.h idtest1.cpp
	g++ -std=c++11 -Wall -Wextra -c -I. idtest1.cpp

idtest2.o : id.h idtest2.cpp
	g++ -std+c++11 -Wall -Wextra -c -I. idtest2.cpp


