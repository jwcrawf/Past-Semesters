/*
  hashtbl.cpp

  Jon Crawford

  date
  
  slave file with implementations for hashtable add-on functions
*/
#include <cstdlib>

template <typename K, typename D, class H>
size_t HashTable<K,D,H>::MaxBucketSize () const
{
  size_t max(0), size;
  for (size_t i = 0; i < numBuckets_; ++i)
  {
    size = bucketVector_[i].Size();
    if (max < size) max = size;
  }
  return max;
}

template <typename K, typename D, class H>
void HashTable<K,D,H>::Analysis (std::ostream& os) const
{
  int width0 = 10, width1 = 13, width2=15;

  // details header
  os << std::setw(width0) << "bucket size distributions" << '\n'
     << std::setw(width0) << "-------------------------" << '\n';
  os << std::setw(width0) << "size" 
     << std::setw(width1) << "actual"
     << std::setw(width2) << "theory" << " (uniform random distribution)" << '\n';
  os << std::setw(width0) << "----" 
     << std::setw(width1) << "------"
     << std::setw(width2) << "------" << '\n';


} // Analysis        

