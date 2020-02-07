


void SimpleSieve(fsu::BitVector& bv)
{
  size_t max = bv.Size();
  bv.Set();
  bv.Unset(0);
  bv.Unset(1);
  for(size_t i = 2; i < max; ++i) // 2 to n
    if(bv[i])
      for(size_t j = i + i; j < max; j += i)
        bv.Unset(j);
}


void Sieve(fsu::BitVector& bv)
// in: bv is a bit vector
// out: bv[k] is true iff k is prime
{
  size_t max = bv.Size(); 
  size_t sqrtmax = ceil(sqrt(max)); 
  // 1: initialize bv 
  bv.Set();
  bv.Unset(0); 
  bv.Unset(1);  // 0 and 1 is not prime 
  for (size_t i = 4; i < max; i += 2)   
    bv.Unset(i);
  
  for (size_t i = 3; i < sqrtmax; i += 2)	// we can skip over the even numbers, already unset
  {
    if (bv[i]) // i is prime    
      for (size_t j = i*i; j < max; j+= i) // clear all multiples of i      
        bv.Unset(j);   
  }
}

