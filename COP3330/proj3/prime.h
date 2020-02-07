/*
  prime.h
  9/22/17
  Jon Crawford

  Header file with definitions for Prime project
*/

#ifndef _PRIME_H
#define _PRIME_H

#include <cstdlib>
#include <iostream>
#include <bitvect.h>

class Prime
{
public:
  ~Prime ();
  Prime ( size_t ub );
  Prime ( const Prime& p );
  size_t Largest ( size_t ub ) const;
  void All ( size_t ub,std::ostream& os = std::cout ) const;
  void All ( std::ostream& os = std::cout ) const;
  size_t UpperBound () const;
  void ResetUpperBound ( size_t ub );
  void Dump ( std::ostream& os = std::cout ) const;
  Prime& operator= ( const Prime& p );
 
private:
  fsu::BitVector bv_;  // Bitvector
  void Sieve ();       // Sieve
};

#endif
