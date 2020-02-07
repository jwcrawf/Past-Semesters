#
# Jon Crawford
# makefile for DOT Fastlane project
# 10/23/2017
#

cflags = -I. -Wall -Wextra
#CC     = clang++ -std=c++11
CC     = g++ -std=c++11

AREA51  = /home/courses/cop3330p/LIB/area51

all:         clients benchmarks
clients:     stester.x vtester.x tracker.x
benchmarks:  stester_i.x vtester_i.x tracker_i.x 

# build executables

tracker.x: tracker.o shapes.o vehicles.o
	$(CC) -otracker.x tracker.o shapes.o vehicles.o

stester.x: stester.o shapes.o 
	$(CC) -ostester.x stester.o shapes.o

vtester.x: vtester.o shapes.o vehicles.o
	$(CC) -ovtester.x vtester.o shapes.o vehicles.o

# build object code files

tracker.o: shapes.h vehicles.h tracker.cpp
	$(CC) $(cflags) -c tracker.cpp

stester.o: shapes.h stester.cpp
	$(CC) $(cflags) -c stester.cpp

vtester.o: vehicles.h shapes.h vtester.cpp
	$(CC) $(cflags) -c vtester.cpp

shapes.o: shapes.h shapes.cpp
	$(CC) $(cflags) -c shapes.cpp

vehicles.o: shapes.h vehicles.h vehicles.cpp
	$(CC) $(cflags) -c vehicles.cpp

# build benchmarks

tracker_i.x: $(AREA51)/tracker_i.x
	cp   $(AREA51)/tracker_i.x .
	chmod 700 tracker_i.x

stester_i.x: $(AREA51)/stester_i.x
	cp   $(AREA51)/stester_i.x .
	chmod 700 stester_i.x

vtester_i.x: $(AREA51)/vtester_i.x
	cp   $(AREA51)/vtester_i.x .
	chmod 700 vtester_i.x
