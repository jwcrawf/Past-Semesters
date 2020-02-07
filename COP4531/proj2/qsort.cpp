/*
    sorts.cpp
    08/08/18
    Chris Lacher

    sort from standard input to standard output

    Copyright 2018, R.C. Lacher
*/

#include <iostream>
#include <vector.h>
#include <gheap_advanced.h>
#include <gsort.h>
#include <xstring.cpp>

// typedef unsigned long ElementType;
typedef fsu::String ElementType;

int main()
{
  fsu::Vector < ElementType > v;  // a vector
  ElementType e;
  while (std::cin >> e)
  {
    v.PushBack(e);
  }
  // fsu::g_insertion_sort(v.Begin(),v.End());
  // fsu::g_heap_sort(v.Begin(),v.End());
  //fsu::g_merge_sort_opt(v.Begin(),v.End());
   fsu::g_merge_sort_bu(v.Begin(),v.End());
  //fsu::g_quick_sort_opt(v.Begin(),v.End());
  // fsu::g_quick_sort_3w_opt(v.Begin(),v.End());
  for (typename fsu::Vector < ElementType > ::Iterator i = v.Begin(); i != v.End(); ++i)
  {
    std::cout << *i << '\n';
  }
  return 0;
}
