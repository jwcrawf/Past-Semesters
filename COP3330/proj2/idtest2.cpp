/**
   test2.cpp

   test2 harness for class ID
   specifically tests for ownership of data pointed to by name_
*/

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <id.h>

int main()
{
  char myName [15]     = "Chris Lacher";
  int  myAge = 99;

  char tonyName [15]   = "Tony Harris";
  int  tonyAge = 17;

  char daltonName [15] = "Dalton Bohning";
  int  daltonAge = 22;

  ID p1(myName, myAge), p2(tonyName,tonyAge), p3(daltonName, daltonAge);
  std::cout << " IDs after declaration:\n"; 
  std::cout << "  p1 = " << p1 << '\n';
  std::cout << "  p2 = " << p2 << '\n';
  std::cout << "  p3 = " << p3 << '\n';

  strcpy (myName,tonyName);      // copy tonyName to myName
  strcpy (tonyName,daltonName);  // copy daltonName to tonyName
  myAge = tonyAge;               // copy tonyAge to myAge
  tonyAge = daltonAge;           // copy daltonAge to tonyAge

  std::cout << " IDs after client program changes myName and myAge:\n"; 
  std::cout << "  p1 = " << p1 << '\n';
  std::cout << "  p2 = " << p2 << '\n';
  std::cout << "  p3 = " << p3 << '\n';
}
