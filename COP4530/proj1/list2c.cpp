/*
	list2c.cpp
	
	Jon Crawford
	
	1/25/2018
	
	COP4530 - Implementation file for the list2c project
	
	*Most Portions of this implementation attributed to Chris Lacher*
	
*/ 	

//global
template < typename T >
bool operator == (const List<T>& x1, const List<T>& x2)
{
  typename List<T>::ConstIterator i1, i2;
  for (i1 = x1.Begin(), i2 = x2.Begin();(i1 != x1.End()) && (i2 != x2.End());++i1, ++i2)
  {
  if (*(i1) != *(i2))
    return 0;
  }
  if (i1 != x1.End() || i2 != x2.End())
    return 0;
  return 1;
}

template < typename T >
bool operator != (const List<T>& x1, const List<T>& x2)
{
  return !(x1 == x2);
}

template < typename T >
std::ostream& operator << (std::ostream& os, const List<T>& x2)
{
  x2.Display(os);
  return os;
}	

//private
template < typename T >
alt2c::List<T>::Link::Link (const T& Tval) : Tval_(Tval), prev_(nullptr), next_(nullptr){}

template < typename T >
typename alt2c::List<T>::Link* List<T>::NewLink (const T& t)
{
  Link * newLink = new(std::nothrow) Link (t);
  if (nullptr == newLink)
  { 
    std::cerr << "** List error: memory allocation failure\n"; 
    return nullptr;
  }
  return newLink;
}

template < typename T >
void alt2c::List<T>::LinkIn(typename List<T>::Link * location, typename List<T>::Link * newLink)
{
  newLink->next_ = location;
  newLink->prev_ = location->prev_;
  newLink->next_->prev_ = newLink;
  newLink->prev_->next_ = newLink;
}

template < typename T >
typename alt2c::List<T>::Link * List<T>::LinkOut(typename List<T>::Link * oldLink)
{
  oldLink->prev_->next_ = oldLink->next_;
  oldLink->next_->prev_ = oldLink->prev_;
  oldLink->prev_ = nullptr;
  oldLink->next_ = nullptr;
  return oldLink;
}

template < typename T >
void alt2c::List<T>::Init()
{
  head_ = NewLink(T());
  tail_ = NewLink(T());
  head_->next_ = tail_;
  head_->prev_ = tail_;
  tail_->next_ = head_;
  tail_->prev_ = head_;
}

template <typename T>
void alt2c::List<T>::Init(T fill)
{
  head_ = NewLink(fill);
  tail_ = NewLink(fill);
  head_->next_ = tail_;
  head_->prev_ = tail_;
  tail_->next_ = head_;
  tail_->prev_ = head_;
}

template < typename T >
void alt2c::List<T>::Append(const List<T>& list)
// Appends deep copy of rhs - do not apply to self!
{
  for (ConstIterator i = list.Begin(); i != list.End(); ++i)
    PushBack(*i);
}



template < typename T >
alt2c::List<T>::List(): head_(nullptr), tail_(nullptr) { Init(); }

template < typename T >
alt2c::List<T>::List(T fill): head_(nullptr), tail_(nullptr)
{
  Init(fill);
}

template < typename T >
alt2c::List<T>::~List ()
{
  Release();
  delete head_;
  delete tail_;
}

template < typename T>
alt2c::List<T>::List(const List<T>& list): head_(nullptr), tail_(nullptr)
{
  Init();
  Append(list);
}

template < typename T>
alt2c::List<T>& alt2c::List<T>::operator = (const List<T>& list)
{
  if (this != &list)
  {
    Release();
    //Clear();
    Append(list);
  }
  return *this;
}

template < typename T>
alt2c::List<T> * alt2c::List<T>::Clone() const
{
  List * clone = new List;
  clone->Append(*this);
  return clone;
}

template < typename T >
alt2c::List<T>& List<T>::operator += (const List<T>& list)
{
  if (this != &list)
    Append(list);
  return *this;
}

template < typename T >
void alt2c::List<T>::PushFront (const T& t)
{
  if (Excess() == 0)
  {
    Link * newLink = NewLink(t);
    LinkIn(head_->next_, newLink); 
  }
  else 
  {
    head_->Tval_ = t;
    head_ = head_->prev_; 
  }
}

template < typename T >
void alt2c::List<T>::PushBack (const T& t)
{
  if (Excess() == 0)
  {
    Link * newLink = NewLink(t);
    LinkIn(tail_,newLink);
  }
  else 
  {
    tail_->Tval_ = t; 
    tail_ = tail_->next_;
  }
}

template < typename T >
ListIterator<T> alt2c::List<T>::Insert (ListIterator<T> i, const T& t)
{
  if (Empty()) 
  {
    i = End();
  }
  if (!i.Valid() || i == rEnd()) 
  {
    std::cerr << " ** cannot insert at position -1\n";
    return End();
  }
  if (Excess() == 0)
  {
    Link* newLink = NewLink(t);
    //if (newLink == nullptr) return End();
    LinkIn(i.curr_,newLink);
    i.curr_ = newLink;
    return i;
  }
  else
  {
    Link* newLink = LinkOut(tail_->next_);
    LinkIn(i.curr_,newLink);
    i.curr_ = newLink;
    return i;
  }
}

template < typename T >
ConstListIterator<T> alt2c::List<T>::Insert (ConstListIterator<T> i, const T& t)
{
  if (Empty()) 
  {
    i = End();
  }
  if (!i.Valid() || i == rEnd()) 
  {
    std::cerr << " ** cannot insert at position -1\n";
    return End();
  }
  if (Excess() == 0)
  {
    Link* newLink = NewLink(t);
    //if (newLink == nullptr) return End();
    LinkIn(i.curr_,newLink);
    i.curr_ = newLink;
    return i;
  }
  else
  {
    Link* newLink = LinkOut(tail_->next_);
    LinkIn(i.curr_,newLink);
    i.curr_ = newLink;
    return i;
  }
}

template < typename T >
ListIterator<T> alt2c::List<T>::Insert  (const T& t)
{
  return Insert(End(),t);
}

template < typename T >
void alt2c::List<T>::PopFront()
{
  if (Empty())
  {
    std::cerr << "** List error: PopFront() called on empty list\n"; 
  }
  Link * oldLink = LinkOut(head_->next_);
  delete oldLink;
} 

template < typename T >
void alt2c::List<T>::PopBack()
{
  if (Empty())
  {
    std::cerr << "** List error: PopBack() called on empty list\n"; 
  }
  Link* oldLink = LinkOut(tail_->prev_);
  delete oldLink;
} 

template < typename T >
ListIterator<T> alt2c::List<T>::Remove (Iterator i)
{
  if (i.curr_ == nullptr || i.curr_ == head_ || i.curr_ == tail_)
  {
    std::cerr << "** List error: Remove(i) called with vacuous iterator\n"; 
    return i;
  }
  i.curr_ = i.curr_->next_;                  
  Link * oldLink = LinkOut(i.curr_->prev_);  
  LinkIn(tail_->next_, oldLink);                          
  return i;                                  
} 

template < typename T >
ConstListIterator<T> alt2c::List<T>::Remove (ConstIterator i)
{
  if (i.curr_ == nullptr || i.curr_ == head_ || i.curr_ == tail_)
  {
    std::cerr << "** List error: Remove(i) called with vacuous iterator\n"; 
    return i;
  }
  i.curr_ = i.curr_->next_;                  
  Link * oldLink = LinkOut(i.curr_->prev_);  
  LinkIn(tail_->next_, oldLink);                            
  return i;                                  
} 

template < typename T >
size_t  alt2c::List<T>::Remove (const T& t)
{
  size_t count(0);
  Iterator i = Begin();
  while (i != End())
  {
    if (t == *i)
    {
      i = Remove(i);
      ++count;
    }
    else
    {
      ++i;
    }
  }
  return (count);
} 

template < typename T >
void alt2c::List<T>::Clear()
{
  tail_ = head_->next_;
}

template < typename T >
void alt2c::List<T>::Release()
{
  Clear();
  while (Excess() > 0 )
  {
    Link * killLink = LinkOut(tail_->next_);
    delete killLink;
  }  
} 

template < typename T >
size_t alt2c::List<T>::Size()  const
{
  size_t  size(0);
  Link * curr(head_->next_);
  while (curr != tail_)
  {
    curr = curr -> next_;
    ++size;
  }
  return size;
}

template < typename T >
size_t alt2c::List<T>::Excess()const
{
  size_t count = 0;
  Link * currentLink = tail_->next_;
  if(tail_->next_ == head_)
    return 0;
  else
  {
    while(currentLink != head_)
    {
      currentLink = currentLink->next_;
      ++count;
    }
  return count;
  }
}

template < typename T >
size_t alt2c::List<T>::Capacity () const { return (Size() + Excess()); }

template < typename T >
T& alt2c::List<T>::Front ()
{
  if (Empty())
  {
    std::cerr << "** List error: Front() called on empty list\n"; 
  }
  return *Begin();
}

template < typename T >
const T& alt2c::List<T>::Front () const
{
  if (Empty())
  {
    std::cerr << "** List error: Front() called on empty list\n"; 
  }
  return *Begin();
}

template < typename T >
T& alt2c::List<T>::Back  ()
{
  if (Empty())
  {
    std::cerr << "** List error: Back() called on empty list\n"; 
  }
  return *rBegin();
}

template < typename T >
const T& alt2c::List<T>::Back  () const
{
  if (Empty())
  {
    std::cerr << "** List error: Back() called on empty list\n"; 
  }
  return *rBegin();
}

template <typename T> 
ListIterator<T>  alt2c::List<T>::Includes (const T& t)
// sequential search
{
  Iterator i;
  for (i = Begin(); i != End(); ++i)
  {
    if (t == *i)
      return i;
  }
  return End();
} // Includes()

// output methods

template < typename T >
void alt2c::List<T>::Display (std::ostream& os, char ofc) const
{
  ConstIterator i;
  if (ofc == '\0')
    for (i = Begin(); i != End(); ++i)
      os << *i;
  else
    for (i = Begin(); i != End(); ++i)
      os << *i << ofc;
} // Display()

// debug/developer methods


// Iterator support

template < typename T >
ListIterator<T>  alt2c::List<T>::Begin()
{
  Iterator i(head_->next_);
  return i;
}

template < typename T >
ListIterator<T>  alt2c::List<T>::End()
{
  Iterator i(tail_);
  return i;
}

template < typename T >
ListIterator<T>  alt2c::List<T>::rBegin()
{
  Iterator i(tail_->prev_);
  return i;
}

template < typename T >
ListIterator<T>  alt2c::List<T>::rEnd ()
{
  Iterator i(head_);
  return i;
}

// ConstIterator support

template < typename T >
typename alt2c::List<T>::ConstIterator  List<T>::Begin() const
{
  ConstIterator i(head_->next_);
  return i;
}

template < typename T >
typename alt2c::List<T>::ConstIterator  List<T>::End() const
{
  ConstIterator i(tail_);
  return i;
}

template < typename T >
typename alt2c::List<T>::ConstIterator  List<T>::rBegin() const
{
  ConstIterator i(tail_->prev_);
  return i;
}

template < typename T >
typename alt2c::List<T>::ConstIterator  List<T>::rEnd () const
{
  ConstIterator i(head_);
  return i;
}

template <typename T> 
typename alt2c::List<T>::ConstIterator  List<T>::Includes (const T& t) const
{
  ConstIterator i;
  for (i = Begin(); i != End(); ++i)
  {
    if (t == *i)
      return i;
  }
  return End();
} // Includes()

//-------------------------------------------
//     ConstListIterator<T>:: Implementations
//-------------------------------------------

// default constructor
template < typename T >
ConstListIterator<T>::ConstListIterator ()  :  curr_(nullptr)
// construct a null ConstListIterator 
{}

// protected constructor
template < typename T >
ConstListIterator<T>::ConstListIterator (typename List<T>::Link* link) : curr_(link)
// construct an iterator around a link pointer (not available to client programs)
{}

// copy constructor
template < typename T >
ConstListIterator<T>::ConstListIterator (const ConstListIterator<T>& i)
   :  curr_(i.curr_)
{}

// assignment operator
template < typename T >
ConstListIterator<T>& ConstListIterator<T>::operator = (const ConstListIterator <T> & i)
{
   curr_ = i.curr_;
   return *this;
}

// protected method
template < typename T >
T&  ConstListIterator<T>::Retrieve() const
// Return reference to current t
// note conflicted signature - const method returns non-const reference
{
  if (curr_ == nullptr)
  {
    std::cerr << "** Error: ConstListIterator<T>::Retrieve() invalid dereference\n";
    exit (EXIT_FAILURE);
  }
  return curr_->Tval_;
}

template < typename T >
bool ConstListIterator<T>::Valid() const
// test cursor for legal dereference
{
  return curr_ != nullptr;
}

template < typename T >
bool ConstListIterator<T>::operator == (const ConstListIterator<T>& i2) const
{
  if (curr_ == i2.curr_)
    return 1;
  return 0;
}

template < typename T >
bool ConstListIterator<T>::operator != (const ConstListIterator<T>& i2) const
{
  return !(*this == i2);
}

template < typename T >
const T&  ConstListIterator<T>::operator * () const
{
  return Retrieve();
}

template < typename T >
ConstListIterator<T>& ConstListIterator<T>::operator ++ ()
// prefix increment
{
  if (curr_ != nullptr)
    curr_ = curr_->next_;
  return *this;
}

template < typename T >
ConstListIterator<T> ConstListIterator<T>::operator ++ (int)
// postfix increment
{
   ConstListIterator <T> clone = *this;
   this->operator++();
   return clone;
}

template < typename T >
ConstListIterator<T>& ConstListIterator<T>::operator -- ()
// prefix decrement
{
  if (curr_ != nullptr)
    curr_ = curr_->prev_;
  return *this;
}

template < typename T >
ConstListIterator<T> ConstListIterator<T>::operator -- (int)
// postfix decrement
{
   ConstListIterator <T> clone = *this;
   this->operator--();
   return clone;
}

//-------------------------------------------
//     ListIterator<T>:: Implementations
//-------------------------------------------

// default constructor
template < typename T >
ListIterator<T>::ListIterator ()  :  ConstListIterator<T>()
// construct a null ListIterator 
{}

// protected constructor
template < typename T >
ListIterator<T>::ListIterator (typename List<T>::Link* link) : ConstListIterator<T>(link)
// construct an iterator around a link pointer (not available to client programs)
{}

// copy constructor
template < typename T >
ListIterator<T>::ListIterator (const ListIterator<T>& i)
   :  ConstListIterator<T>(i)
{}

// assignment operator
template < typename T >
ListIterator<T>& ListIterator<T>::operator = (const ListIterator <T> & i)
{
  ConstListIterator<T>::operator=(i);
  return *this;
}

template < typename T >
const T&  ListIterator<T>::operator * () const
{
  return ConstListIterator<T>::Retrieve();
}

template < typename T >
T&  ListIterator<T>::operator * ()
{
  return ConstListIterator<T>::Retrieve();
}

template < typename T >
ListIterator<T>& ListIterator<T>::operator ++ ()
// prefix increment
{
  ConstListIterator<T>::operator++();
  return *this;
}

template < typename T >
ListIterator<T> ListIterator<T>::operator ++ (int)
// postfix increment
{
   ListIterator <T> clone = *this;
   this->operator++();
   return clone;
}

template < typename T >
ListIterator<T>& ListIterator<T>::operator -- ()
// prefix decrement
{
  ConstListIterator<T>::operator--();
  return *this;
}

template < typename T >
ListIterator<T> ListIterator<T>::operator -- (int)
// postfix decrement
{
   ListIterator <T> clone = *this;
   this->operator--();
   return clone;
}

template < typename T >
void alt2c::List<T>::Dump (std::ostream& os, char ofc) const
{
  Link * p = head_;
  if (ofc == '\0')
  {
    do
    {
      p = p->next_;
      os << p->Tval_;
    }
    while (p != head_);
  }
  else
  {
    do
    {
      p = p->next_;
      os << ofc << p->Tval_;
    }
    while (p != head_);
  }
  os << '\n';
} // Dump()

template < typename T >
void alt2c::List<T>::CheckLinks(std::ostream& os) const
{
  Link * q, * p = head_;
  size_t n = 0;
  do
  {
    q = p->next_->prev_;
    if (p != q)
    {
      os << " ** forward check failure at link " << n << '\n';
    }
    q = p->prev_->next_;
    if (p != q)
    {
      os << " ** reverse check failure at link " << n << '\n';
    }
    p = p->next_;
    ++n;
  }
  while (p != head_);
  if (n != 2 + Size() + Excess())
  {
    os << " ** link count mismatch: count = " << n << " , size = " << Size() << " , excess = " << Excess() << '\n';
  }
}

// check iterator integrity
template < typename T >
void alt2c::List<T>::CheckIters(std::ostream& os) const
{
  typename List<T>::ConstIterator i,j,k;
  // bool ok = 1;
  size_t n = 0;
  for (i = this->Begin(), n = 0; i != this->End(); ++i, ++n)
  {
    j = i; --j; ++j;
    k = i; ++k; --k;
    if (!i.Valid() || !j.Valid() || !k.Valid() || i != j || i != k)
    {
      os << " ** forward reciprocity failure at position " << n << '\n';
      // ok = 0;
      break;
    }
  }
  if (n != Size())
  {
    os << " ** Size() mismatch in forward check: count = " << n << " , size = " << Size() << '\n';
  }
  for (i = this->rBegin(), n = 0; i != this->rEnd(); --i, ++n)
  {
    j = i; --j; ++j;
    k = i; ++k; --k;
    if (!i.Valid() || !j.Valid() || !k.Valid() || i != j || i != k)
    {
      os << " ** reverse reciprocity failure at position " << n << '\n';
      // ok = 0;
      break;
    }
  }
  if (n != Size())
  {
     os << " ** Size() mismatch in reverse check: count = " << n << " , size = " << Size() << '\n';
  }
} // CheckIters() 





















