/*
    list_sort.cpp
    05/17/17
    Chris Lacher

    list_sort.cpp
    Jon Crawford
    COP4531 - Summer 2019 - proj2   

    Implementation of List<T>::Sort() using the bottom up merge sort
    Copyright 2017, R. C. Lacher


//----------------------------------
//     List<T>::Sort Implementations
//----------------------------------

**This is the combined pseudocode from the lecture and project doc**

void List::Sort()
{
  Link * currSeg, * nextSeg; // ptrs to sub-lists to be merged
  segSize = 1;
  do
  {
    numMerges = 0;
    // merge all adjacent pairs of sub-lists of length segSize
    currSeg = firstLink;
    while (currSeg != 0)
    {
      nextSeg = currSeg;
      advance nextSeg segSize steps in the list // Notes 1-3
      for (size_t i = 0; i < segSize; ++i)
        nextSeg = nextSeg -> nextLink_;
      merge the sublist at currSeg with the sublist at nextSeg // Note 4
      while (L1 and L2 are not empty)
      {
        if (nextSeg->t < currSeg->t)
        {
          q = nextSeg;
          nextSeg = nextSeg->next; // "advance" nextSeg
          unlink *q from L2 and append it to L
        }
        else
        {
          q = currSeg;
          currSeg = currSeg->next; // "advance" currSeg
          unlink *q from L1 and append it to L
        }
      }
      if (L1 is not empty) append L1 to L;
      if (L2 is not empty) append L2 to L;
      (leaving currSeg at the beginning of the next segment)
      ++numMerges;
    }
    // double the sub-list size to be merged
    segSize = 2 * segSize;
  }
  while (numMerges > 1); // stop when only 1 merge has occured - the last merge
  take care of remainders
  fix list at ends
}
*/
template<typename T>
template<class P>
void fsu::List<T>::Sort(P &comp)
{  
  // if (n < 2) return, code taken from list_macro.cpp
  if (head_->next_ == tail_ || head_->next_->next_ == tail_)
    return;
  Link * currSeg, * nextSeg, * temp;  
  size_t numMerges(0), segSize(1), currSegCount(0), nextSegCount(0);
  tail_->prev_->next_ = 0; //fix tail at end  
  
  do
  {     
    numMerges = 0; 
    currSeg = head_->next_; // currSeg = firstLink;   
    nextSeg = currSeg;
    temp = head_;
    
    while (currSeg != 0) 
    {      
      nextSeg = currSeg;
      for (size_t i = 0; i < segSize; ++i) // advance nextSeg segSize steps in the list
      {
        if (nextSeg == 0) break;
        nextSeg = nextSeg->next_;
      }       
      currSegCount = 0, nextSegCount = 0;   
      while (currSegCount < segSize && nextSegCount < segSize && nextSeg != 0) 
      {         
        if (comp(nextSeg->Tval_,currSeg->Tval_))
        {         
          temp->next_ = nextSeg;           
          nextSeg = nextSeg->next_;          
          ++nextSegCount;      
        }
        else 
        {
          temp->next_ = currSeg;
          currSeg = currSeg->next_;        
          ++currSegCount; 
        }
        temp->next_->prev_ = temp; 
        temp = temp->next_;               
      }
      // if (L1 is not empty) append L1 to L;
      while (currSegCount < segSize && currSeg != 0) 
      {        
        temp->next_ = currSeg;
        currSeg = currSeg->next_;
        temp->next_->prev_ = temp;
        temp = temp->next_;         
        ++currSegCount;
      }
      // if (L2 is not empty) append L2 to L;
      while (nextSegCount < segSize && nextSeg != 0) 
      {        
        temp->next_ = nextSeg;
        nextSeg = nextSeg->next_;
        temp->next_->prev_ = temp;
        temp = temp->next_;          
        ++nextSegCount;              
      }      
      // leaving currSeg at the beginning of the next segment
      temp->next_ = 0;
      currSeg = nextSeg;
      ++numMerges;
    }     
    segSize *= 2;
  } while(numMerges > 1);
  // fix list at end
  temp->next_ = tail_;
  temp->next_->prev_ = temp;
}


template<typename T>
void fsu::List<T>::Sort()
{
 fsu::LessThan<T> p;
 Sort(p);
}
