/*

 tsort.h
 
 Jon Crawford

 11/9/2017

 header file with definition and implementation of sort/display templates

*/

#ifndef _TSORT_H
#define _TSORT_H

#include <iostream>

template < typename T >
void Display (const T* beg, const T* end, char ofc = '\0');

template < typename T >
void InsertionSort (T* beg, T* end);


template < typename T >
void Display (const T* beg, const T* end, char ofc)
{
  size_t size = end - beg;
  for (size_t i = 0; i < size; ++i)
  {
    if (ofc == '\0')
      std::cout << beg[i];
    else
      std::cout << ofc << beg[i];
  }  
}

template < typename T >
void InsertionSort (T* beg, T* end)
{
  size_t size = end - beg;
  if (size < 2) return;                                                                                                          size_t i;                                 
  size_t j;                                                                                   
  T t = beg[0];                                                                                                 
  for (i = 1; i < size; ++i)
  {
    t = beg[i];
    j = 0;
    for (j = i; j > 0; j--)
                                                                     
      if (t < beg[j - 1])
        beg[j] = beg[j - 1];
      else break;
    beg[j] = t;                                                                          
  }
};

#endif 
