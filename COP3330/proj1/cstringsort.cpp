/*cstringsort.cpp
9/6/17
Jon Crawford

Implementation file for cstring sorting program
*/

#include <iostream>
#include <cstringsort.h>


//////////////////////////////////////////////////////
// Function Name: LexDiff
//
// Input: char s1,s2
//
// Output:int difference of chars values
//
// Function Purpose:compare the values of each character of a string and return
//  a value of positive or negative depending on which string should come first
//
//////////////////////////////////////////////////////

int  LexDiff(const char* s1, const char* s2)
{
  //loop until end of string searching for difference
	while (*s1 && *s2 != '\0')
	{
		if (*s1 != *s2) {
			break;
		}
		s1++; //move to next 
		s2++; 
	}
        //return the difference of the char values
	return *s1 - *s2;
}

////////////////////////////////////////////////////// 
// Function Name: DictionaryDiff
//
// Input: char s1,s2
//
// Output: 1,-1,0 depending on difference of lowercase char values
//
// Function Purpose: to compare the lowercase char values of a string and return
//  a logical difference value to determine which one comes first
//
//////////////////////////////////////////////////////
 
int  DictionaryDiff(const char* s1, const char* s2)
{
  // loop until end of string searching for difference 
	while (*s1 && *s2 != '\0')
	{
		if (tolower(*s1) != tolower(*s2)) {
			break;
		}
		s1++; //move to next 
		s2++;
	}
        //return the difference of the lowercase char values
        if (tolower(*s1) - tolower(*s2) < 0)
          return -1;
        else if (tolower(*s1) - tolower(*s2) > 0)
          return 1;
        else
          return 0;
}

///////////////////////////////////////////////////////
// Function Name: LexComp
//
// Input: char s1,s2
//
// Output: bool
//
// Function Purpose:to call the LexDiff function
//  and determine string comes first
//
//////////////////////////////////////////////////////

bool LexComp(const char* s1, const char* s2)
{
  //call and determine based on pos or neg return
	if (LexDiff(s1, s2) < 0)
		return true;
	else
		return false;
}

//////////////////////////////////////////////////////
// Function Name: DictionaryComp
//
// Input: char s1,s2
//
// Output: bool
//
// Function Purpose: to call the DicDiff function
//  and determine which string comes first
//
/////////////////////////////////////////

bool DictionaryComp(const char* s1, const char* s2)
{
  //call and determine based on pos or neg return
	if (DictionaryDiff(s1, s2) < 0)
		return true;
	else
		return false;
}

//////////////////////////////////////////////////////
// Function Name: LexStringSort
//
// Input: char beg, char end
//
// Output: the function is void
//
// Function Purpose: To call LexComp function
//  and reorder the strings if it is
//  determined that one should come before the other
//
//////////////////////////////////////////////////////

void LexStringSort(char* *beg, char* *end)
{
	size_t size = end - beg;
	if (size < 2) return;
        //most of this taken from lacher example
	size_t i; // outer loop control
	size_t j; // inner loop control
	char* t; // value holder
	for (i = 1; i < size; ++i)
	{
		t = beg[i];
		j = 0;
		for (j = i; j>0; j--)
			// call LexComp to determine if switch
			if (LexComp(t, beg[j - 1]))
				beg[j] = beg[j - 1];
			else break;
		beg[j] = t; // copy t into vacated slot
	}
}

//////////////////////////////////////////////////////
// Function Name: DictionaryStringSort
//
// Input: char* beg, char* end
//
// Output: the function is void
//
// Function Purpose: To call DictionaryComp function
//  and reorder the strings if it is
//  determined that one should come before the other
//
//////////////////////////////////////////////////////

void DictionaryStringSort(char* *beg, char* *end)
{
	size_t size = end - beg;
	if (size < 2) return;
        //most of this taken from lacher example
	size_t i; // outer loop control
	size_t j; // inner loop control
	char* t; // value holder
	for (i = 1; i < size; ++i)
	{
		t = beg[i];
		j = 0;
		for (j = i; j>0; j--)
			// DictComp to determine if switch
			if (DictionaryComp(t, beg[j - 1]))
				beg[j] = beg[j - 1];
			else break;
		beg[j] = t; // copy t into vacated slot
	}
}
