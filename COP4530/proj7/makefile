# makefile

# Jon Crawford

# 4/12/2018

# makefile for Graph Search proj7

LIB = /home/courses/cop4530p/LIB
CC = g++ -std=c++11 -Wall -Wextra -I. -I$(LIB)/cpp -I$(LIB)/tcpp -I$(LIB)/graph

all: fgraph.x fbfs_ug.x fbfs_dg.x fdfs_ug.x fdfs_dg.x agraph.x rangraph.x  

fgraph.x: fgraph.cpp graph.h 
	$(CC) -o fgraph.x fgraph.cpp

fbfs_ug.x: fbfsurvey_ug.cpp bfsurvey.h graph.h
	$(CC) -o fbfs_ug.x fbfsurvey_ug.cpp

fbfs_dg.x: fbfsurvey_dg.cpp bfsurvey.h graph.h 
	$(CC) -o fbfs_dg.x fbfsurvey_dg.cpp

fdfs_ug.x: fdfsurvey_ug.cpp dfsurvey.h graph.h
	$(CC) -o fdfs_ug.x fdfsurvey_ug.cpp

fdfs_dg.x: fdfsurvey_dg.cpp dfsurvey.h graph.h
	$(CC) -o fdfs_dg.x fdfsurvey_dg.cpp



agraph.x: $(LIB)/area51/agraph_i.x
	cp $(LIB)/area51/agraph_i.x agraph.x
	chmod 700 agraph.x

rangraph.x: $(LIB)/area51/rangraph_i.x
	cp $(LIB)/area51/rangraph_i.x rangraph.x
	chmod 700 rangraph.x
