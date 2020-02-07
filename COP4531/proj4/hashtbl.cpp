/*
    hashtbl.cpp
    Jon Crawford
    COP4531 Summer 2019
    Note: Most portions of this code attributed to RC Lacher, Hash Analysis 
    Implementing the MaxBucketSize and Analysis methods for HashTable<K,D,H>
*/
 
template <typename K, typename D, class H>
size_t HashTable<K,D,H>::MaxBucketSize () const
{
  size_t max = 0;
  for (size_t i = 0; i < numBuckets_; ++i) 
    if (max < bucketVector_[i].Size()) max = bucketVector_[i].Size();
  return max;
}

template <typename K, typename D, class H>
void HashTable<K,D,H>::Analysis (std::ostream& os) const
{
  // declare column widths
  int width0 = 10, width1 = 13, width2 = 15;
  int startheader = width0 - 4; // output ' ' at this width preceeding table
  int used = 0;
  size_t size = Size();
  double lambda = (double)size / (double)numBuckets_; 
  fsu::Vector<size_t> sizeCount(1 + MaxBucketSize(), 0);
  for (size_t i = 0; i < numBuckets_; ++i)
  {
    if(!bucketVector_[i].Empty()) ++used;
    ++sizeCount[bucketVector_[i].Size()];
  }  
  size = Size(); 
  double actual = 1 + ((double)size / (double)used);
  os << "\n" << std::setw(startheader) << ' ' << "table size:           "  << size << "\n"
     << std::setw(startheader) << ' ' << "number of buckets:    " << numBuckets_ << "\n"
     << std::setw(startheader) << ' ' << "nonempty buckets:     " << used << "\n"
     << std::setw(startheader) << ' ' << "max bucket size:      " << MaxBucketSize() << "\n"
     << std::setw(startheader) << ' ' << "load factor:          " << std::setprecision(2) 
     << std::fixed << lambda << "\n"
     << std::setw(startheader) << ' ' << "expected search time: " << std::setprecision(2) 
     << std::fixed << 1 + lambda << "\n"
     << std::setw(startheader) << ' ' << "actual search time:   " << std::setprecision(2) 
     << std::fixed << actual << "\n\n";
  // details header
  os << std::setw(startheader) << ' ' << "bucket size distributions" << '\n'
     << std::setw(startheader) << ' ' << "-------------------------" << '\n';
  os << std::setw(width0) << "size" 
     << std::setw(width1) << "actual"
     << std::setw(width2) << "theory" << " (uniform random distribution)\n";
  os << std::setw(width0) << "----" 
     << std::setw(width1) << "------"
     << std::setw(width2) << "------" << '\n';
  // theory formula calculations from PDF
  size_t bound = 1 + MaxBucketSize(), index = 0; // poisson bound
  double n = (double)size, b = (double)numBuckets_, expd; // double precision
  fsu::Vector<double> expdCount;
  expdCount.SetSize(1 + bound, 0.0); // set size of distribution
  expdCount[0] = (b - 1) / b;
  expdCount[0] = pow(expdCount[0], n - 1);
  expdCount[0] *= (b - 1);
  for(size_t k = 1; k < 1 + bound; ++k)
    expdCount[k] = ((n - k + 1) / ((b - 1) * k)) * expdCount[k - 1];  
  while(index < bound)
  {
    os << std::setw(width0) << index << std::setw(width1) << sizeCount[index]
       << std::setw(width2) << std::setprecision(1) << std::fixed << expdCount[index] << "\n";
    expd = expdCount[index]; //retain last value for next loop starting point
    ++index;
  }
  /* starting at the (1 + m)th value expdCount[m]) without storing them. */  
  while(bound < size)
  {    
    expd = ((n - bound + 1) / ((b - 1) * bound)) * expd;
    if(expd <= 0.05) break;
    os << std::setw(width0) << bound << std::setw(width1) << " "
       << std::setw(width2) << std::setprecision(1) << std::fixed << expd << "\n";    
    ++bound;
  }   
  os << "\n";
} // end Analysis

  