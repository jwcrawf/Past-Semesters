/*
	gssearch.h
	
	Jon Crawford
	
	1/30/2018
	
	header file with generic algorithms for proj2 spyware
*/	

#ifndef GSSEARCH_H
#define GSSEARCH_H

#include <compare_spy.h> 

namespace seq
{
  template < class I, typename T, class P >
  I g_lower_bound(I beg, I end, const T& val, P& LessThan)
  {
    while (beg != end)
    {
      if (!LessThan(*beg, val)) 
        return beg; 
      ++beg;
    }
    return beg; 
  }
	
  template < class I, typename T, class P>
  I g_upper_bound(I beg, I end, const T& val, P& LessThan)
  {
    while (beg != end)
    {
      if (LessThan(val, *beg)) 
        return beg; 
      ++beg;
    }
    return beg; 
  }
} // end seq

#endif