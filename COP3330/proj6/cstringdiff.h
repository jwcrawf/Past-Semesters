/*
cstringsort.h
9/6/17
Jon Crawford

Header file for cstring sorting program
*/

#ifndef CSTRINGSORT_H
#define CSTRINGSORT_H
#include <tsort.h>

int  LexDiff(const char* s1, const char* s2);

int  DictionaryDiff(const char* s1, const char* s2);

bool LexComp(const char* s1, const char* s2);

bool DictionaryComp(const char* s1, const char* s2);

#endif 
