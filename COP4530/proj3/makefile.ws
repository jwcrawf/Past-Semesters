# makefile.ws

# Jon Crawford

# 2/16/2018

# makefile for wordsmith proj3

CC = g++ -std=c++11 -Wall -Wextra -I. -I$(CPP) -I$(TCPP)
LIB = /home/courses/cop4530p/LIB/
CPP = $(LIB)cpp
TCPP = $(LIB)tcpp

ws.x: main_ws.cpp wordsmith.h wordsmith.cpp cleanup.cpp $(CPP)/xstring.h $(CPP)/xstring.cpp 
	$(CC) -o ws.x wordsmith.cpp $(CPP)/xstring.h $(CPP)/xstring.cpp	main_ws.cpp 


