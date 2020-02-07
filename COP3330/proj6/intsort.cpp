/* 
    xsort.cpp
    10/23/17
    cop3330p team

    Sort file of ElementType, where ElementType is one of several possible
    types, including:

      int, char, std::string, ID 

    File size is limited to maxSize.
    Calls template functions InsertionSort and Display presumed in tsort.h.

*/

#include <iostream>
#include <cstdlib>
#include <tsort.h>

const size_t maxSize = 1000;

// int data type
typedef int ElementType;
char ofc=' ';   
// */

/* // char data type
typedef char ElementType;
char ofc='\0';   
// */

/* // std::string data type
#include <string>
typedef std::string ElementType;
char ofc=' ';    
// */

/* // ID data type
#include <id.h> // defines type ID
typedef ID ElementType;
char ofc = '\n';
// */

int main()
{
  ElementType A [maxSize];
  ElementType t;
  size_t count = 0;
  while (count < maxSize && std::cin >> t)
  {
    A[count] = t;
    ++count;
  } 
  std::cout << " A as entered: ";
  Display(A, A + count,ofc); std::cout << '\n';
  InsertionSort(A, A + count);
  std::cout << " A after sort: ";
  Display(A, A + count,ofc); std::cout << '\n';
}
