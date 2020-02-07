/*
  prime.cpp
  9/22/17
  Jon Crawford

  Function implementations for Prime Project
*/

#include <cstdlib>
#include <iostream>
#include <prime.h>
#include <cmath>


Prime::Prime ( size_t ub ) : bv_(ub+1)
{
  Sieve();
}

Prime::~Prime () 
{}

Prime::Prime ( const Prime& p ) : bv_(p.bv_)
{}

size_t Prime::Largest ( size_t ub ) const
{
  if ( ub > UpperBound())
  {
    std::cerr << "**Prime::Largest: argument " << ub
              << " too large for object - changing argument to "
              << UpperBound() << std::endl;
    ub = UpperBound();
  }

  if (ub <= 1) return 0;
  if (ub == 2) return 2;  
  size_t largest = 2;

  for (size_t j = 2; j <= ub; ++j)
  {
    if (bv_.Test (j))
    { 
      largest = j;
    }
  }
  return largest;
}

void Prime::All ( size_t ub,std::ostream& os ) const
{
  if ( ub > UpperBound()) 
  {
    std::cerr << "**Prime::All: argument " << ub
              << " too large for object - changing argument to "
              << UpperBound() << std::endl;
    ub = UpperBound();
  }  
  os << " ";
  for (size_t i = 0; i <= ub; ++i)
  {
    if (bv_.Test(i))
    {
      os << i << " ";
    }  
  }
  os << std::endl;
}

void Prime::All ( std::ostream& os ) const
{
  size_t ub = UpperBound();
  os << " ";
  for (size_t i = 0; i <= ub; ++i)
  {
    if (bv_.Test(i))
    {
      os << i << " ";
    }    
  }
  os << std::endl;
}

size_t Prime::UpperBound () const
{
  return bv_.Size()-1;
}
 
void Prime::ResetUpperBound ( size_t ub )
{
  if ( ub > UpperBound())
    bv_.Expand(ub+1);
  Sieve();
}

void Prime::Dump ( std::ostream& os ) const
{
  bv_.Dump(os);
}

Prime& Prime::operator= ( const Prime& p )
{
  if ( this != &p )
    bv_ = p.bv_;
  return *this;
}

void Prime::Sieve()
{
  bv_.Set();  
  bv_.Unset(0);  
  bv_.Unset(1);  
  size_t max  = bv_.Size();
  
  for (size_t k = 2; k < std::sqrt(max); ++k)
  {
    if (bv_.Test(k)) 
    {
      for (size_t j = k + k; j < max; j += k)
      {
        bv_.Unset(j);
      }
    }
  }
}
 
