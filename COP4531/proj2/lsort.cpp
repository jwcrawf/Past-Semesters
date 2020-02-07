/*
    lsort.cpp
    08/03/18
    Chris Lacher

    sort from standard input to standard output

    Copyright 2018, R.C. Lacher
*/

#include <iostream>
#include <list.h>

// typedef unsigned long ElementType;
#include <xstring.cpp>
typedef fsu::String ElementType;

int main()
{
  fsu::List < ElementType > L;  // a list
  ElementType e;
  while (std::cin >> e)
  {
    L.PushBack(e);
  }
  L.Sort();
  for (typename fsu::List < ElementType > ::Iterator i = L.Begin(); i != L.End(); ++i)
  {
    std::cout << *i << '\n';
  }
  return 0;
}
