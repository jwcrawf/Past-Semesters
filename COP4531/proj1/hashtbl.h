/*
    hashtbl.h
    Chris Lacher
    06/20/18

    Copyright 2018, R.C. Lacher
    
    Defining the classes HashTable <K, D, H>
                         HashTable <K, D, H> :: ConstIterator
                         HashTable <K, D, H> :: Iterator

    K                    = KeyType
    D                    = DataType
    Entry < K , D >      = EntryType = ValueType
    H                    = HashType
    List < ValueType >   = BucketType
    
    Note: a possible point of confusion is that
          HashTable  :: ValueType is Entry<K,D> and
          BucketType :: ValueType is Entry<K,D>, while 
          Entry<K,D> :: ValueType is D.

    The return type of HashTable<K, D, H>::Iterator::operator* is
    ValueType&, which means that (*I).data_ has type DataType&.

    The following are the C = BucketType operations used in the implementation,
    where E is BucketType::ValueType:

    C::Iterator Includes (const E& e);                 // returns location for e
    C::Iterator Insert   (const E& e);                 // inserts e and returns location
    void        Insert   (C::Iterator& i, const E& e); // places copy of e at i
    void        Remove   (C::Iterator i);              // removes item at i
    bool        Empty    ();                           // true iff Size() returns zero
    size_t      Size     ();                           // returns the number of elements
    C::Iterator Begin    ();                           // returns iterator to first element
    C::Iterator End      ();                           // returns iterator past the last element

*/

#ifndef _HASHTBL_H
#define _HASHTBL_H

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>    // used by Analysis in hashtbl.cpp

#include <entry.h>
#include <vector.h>
#include <list.h>
#include <primes.h>
#include <genalg.h> // Swap()

namespace fsu
{

  template <typename K, typename D, class H>
  class HashTable;

  template <typename K, typename D, class H>
  class ConstHashTableIterator;

  template <typename K, typename D, class H>
  class HashTableIterator;

  //--------------------------------------------
  //     HashTable <K,D,H>
  //--------------------------------------------

  template <typename K, typename D, class H>
  class HashTable
  {
    friend class ConstHashTableIterator <K,D,H>;
    friend class HashTableIterator <K,D,H>;
  public:
    typedef K                                KeyType;
    typedef D                                DataType;
    typedef fsu::Entry<K,D>                  ValueType;
    typedef fsu::Entry<K,D>                  EntryType;
    typedef fsu::List<ValueType>             BucketType;
    typedef H                                HashType;
    // typedef typename BucketType::ValueType   ValueType;
    typedef HashTableIterator<K,D,H>         Iterator;
    typedef ConstHashTableIterator<K,D,H>    ConstIterator;

    // ADT Table
    Iterator       Insert        (const K& k, const D& d);
    bool           Retrieve      (const K& k, D& d) const;
    Iterator       Includes      (const K& k);
    void           Insert        (Iterator i, const K& k , const D& d);

    // ADT Associative Array
    D&             Get           (const K& key);
    void           Put           (const K& key, const D& data);
    D&             operator[]    (const K& key);

    // needed for Table and AA
    bool           Remove        (const K& k);
    void           Rehash        (size_t numBuckets = 0);

    // const versions of Includes, Get & []
    ConstIterator  Includes      (const K& k) const;
    const D&       Get           (const K& key) const;
    const D&       operator[]    (const K& key) const;

    Iterator       Begin         ();
    Iterator       End           ();
    Iterator       rBegin        ();
    Iterator       rEnd          ();

    ConstIterator  Begin         () const;
    ConstIterator  End           () const;
    ConstIterator  rBegin        () const;
    ConstIterator  rEnd          () const;


    // proper type - first ctor uses default hash object, second uses supplied hash object
    explicit       HashTable     (size_t numBuckets = 100, bool prime = 1);
    HashTable                    (size_t numBuckets, HashType hashObject, bool prime = 1);
                   ~HashTable    ();
    HashTable                    (const HashTable<K,D,H>&);
    HashTable& operator =        (const HashTable&);

    // boiler plate
    void           Clear         ();
    size_t         Size          () const;
    bool           Empty         () const;

    // these are for debugging and analysis
    void           Dump          (std::ostream& os, int c1 = 0, int c2 = 0) const;
    size_t         NumBuckets    () const;
    size_t         MaxBucketSize () const;
    void           Analysis      (std::ostream& os) const;
    bool           Check         () const { return 1; }

  private:
    // data
    size_t                 numBuckets_;
    Vector < BucketType >  bucketVector_;
    HashType               hashObject_;
    bool                   prime_;     // flag for prime number of buckets

    // private method calculates bucket index
    size_t  Index          (const KeyType& k) const;
  } ;

  //--------------------------------------------
  //     ConstHashTableIterator <K,D,H>
  //--------------------------------------------

  // Note: This is a ConstIterator - cannot be used to modify table 

  template <typename K, typename D, class H>
  class ConstHashTableIterator
  {
    friend class HashTable <K,D,H>;
  public:
    typedef K                                KeyType;
    typedef D                                DataType;
    typedef fsu::Entry<K,D>                  ValueType;
    typedef fsu::Entry<K,D>                  EntryType;
    typedef fsu::List<ValueType>             BucketType;
    typedef H                                HashType;
    // typedef typename BucketType::ValueType   ValueType;
    typedef HashTableIterator<K,D,H>         Iterator;
    typedef ConstHashTableIterator<K,D,H>    ConstIterator;

    ConstHashTableIterator   ();
    ConstHashTableIterator   (const ConstIterator& i);
    ConstHashTableIterator   (const Iterator& i);  // type converter
    bool Valid          () const;
    ConstHashTableIterator <K,D,H>& operator =  (const ConstIterator& i);
    ConstHashTableIterator <K,D,H>& operator ++ ();
    ConstHashTableIterator <K,D,H>  operator ++ (int);
    ConstHashTableIterator <K,D,H>& operator -- ();
    ConstHashTableIterator <K,D,H>  operator -- (int);
    // ValueType&                      operator*  ();
    const ValueType&                operator*   () const;
    bool                            operator == (const ConstIterator& i2) const;
    bool                            operator != (const ConstIterator& i2) const;

  protected:
    const HashTable <K,D,H> *           tablePtr_;
    // HashTable <K,D,H> *                 tablePtr_;    // auto-coverts to   const HashTable <K,D,H>
    size_t                              bucketNum_;
    typename BucketType::ConstIterator  bucketItr_;
    // typename BucketType::Iterator       bucketItr_;   // auto-converts to  BucketType::ConstIterator
  } ;

  //--------------------------------------------
  //     HashTableIterator <K,D,H>
  //--------------------------------------------

  // Note: This is an Iterator - can be used to modify table data entries only
  /*
     Design notes: We have not followed the pattern of deriving Iterator from a
     base class ConstIterator. The approach is to define these as unrelated
     classes, and create a type-conversion constructor for ConstIterator. This
     is simpler and leads to more straighforward implementation code, taking full
     advantage of the fact that pointers and references auto-convert to their
     const counterparts.
  */

  template <typename K, typename D, class H>
  class HashTableIterator
  {
    friend class HashTable <K,D,H>;
    friend class ConstHashTableIterator <K,D,H>;
  public:
    typedef K                                KeyType;
    typedef D                                DataType;
    typedef fsu::Entry<K,D>                  ValueType;
    typedef fsu::Entry<K,D>                  EntryType;
    typedef fsu::List<ValueType>             BucketType;
    typedef H                                HashType;
    // typedef typename BucketType::ValueType   ValueType;
    typedef HashTableIterator<K,D,H>         Iterator;
    typedef ConstHashTableIterator<K,D,H>    ConstIterator;

    HashTableIterator   ();
    HashTableIterator   (const Iterator& i);
    bool Valid          () const;
    HashTableIterator <K,D,H>& operator=   (const Iterator& i);
    HashTableIterator <K,D,H>& operator++  ();
    HashTableIterator <K,D,H>  operator++  (int);
    HashTableIterator <K,D,H>& operator--  ();
    HashTableIterator <K,D,H>  operator--  (int);
    ValueType&                 operator*   ();
    const ValueType&           operator*   () const;
    bool                       operator==  (const Iterator& i2) const;
    bool                       operator!=  (const Iterator& i2) const;

  protected:
    HashTable <K,D,H> *             tablePtr_;    // auto-coverts to   const HashTable <K,D,H>
    size_t                          bucketNum_;   // no change in type from ConstIterator
    typename BucketType::Iterator   bucketItr_;   // auto-converts to  BucketType::ConstIterator
  } ;

  //--------------------------------------------
  //     HashTable <K,D,H> global operators
  //--------------------------------------------

  template <typename K, typename D, class H>
  bool operator== (const HashTable<K,D,H> t1, const HashTable<K,D,H> t2)
  {
    typename HashTable<K,D,H>::ConstIterator i1, i2;
    for ( i1 = t1.Begin(), i2 = t2.Begin(); i1 != t1.End() && i2 != t2.End(); ++i1, ++i2)
    {
      if (*i1 != *i2) return 0;
    }
    if (i1 != t1.End() || i2 != t2.End()) return 0;
    return 1;
  }

  template <typename K, typename D, class H>
  bool operator!= (const HashTable<K,D,H> t1, const HashTable<K,D,H> t2)
  {
    return !(t1 == t2);
  }


  //--------------------------------------------
  //     HashTable <K,D,H> implementations
  //--------------------------------------------

  // Table API

  template <typename K, typename D, class H>
  HashTableIterator<K,D,H> HashTable<K,D,H>::Insert (const K& k, const D& d)
  {
    EntryType e(k,d);
    Iterator i;
    i.tablePtr_  = this;
    i.bucketNum_ = Index(k);
    typename BucketType::Iterator j  = bucketVector_[i.bucketNum_].Includes(e);

    // new version works for all List ADTs
    if (j == bucketVector_[i.bucketNum_].End())
    {
      j = bucketVector_[i.bucketNum_].Insert(e);
    }
    else
    {
      *j = e;
    }
    i.bucketItr_ = j;
    return i;
  }

  template <typename K, typename D, class H>
  void HashTable<K,D,H>::Insert (Iterator i, const K& k, const D& d)
  {
    if (i.Valid() && i.tablePtr_ == this && (*i).key_ == k)
      // if ((*i).key_ == k)
      (*i).data_ = d;
    else
      Insert(k,d);
  }

  template <typename K, typename D, class H>
  bool HashTable<K,D,H>::Remove (const K& k)
  {
    EntryType e(k);
    size_t bucketNum_ = Index(k);
    typename BucketType::Iterator j = bucketVector_[bucketNum_].Includes(e); 
    if (j != bucketVector_[bucketNum_].End())
    {
      if (*j == e)
      {
        bucketVector_[bucketNum_].Remove(j);
        return 1;
      }
    }
    return 0;
  }

  template <typename K, typename D, class H>
  ConstHashTableIterator<K,D,H> HashTable<K,D,H>::Includes (const K& k) const
  {
    EntryType e(k);
    ConstIterator i;
    i.tablePtr_  = this;
    i.bucketNum_ = Index(e.key_);
    i.bucketItr_ = bucketVector_[i.bucketNum_].Includes(e); 
    if (i.bucketItr_ != bucketVector_[i.bucketNum_].End())
    {
      // if (*i == e) // check not needed
      // {
        return i;
      // }
    }
    return End();
  }

  template <typename K, typename D, class H>
  HashTableIterator<K,D,H> HashTable<K,D,H>::Includes (const K& k)
  {
    EntryType e(k);
    Iterator i;
    i.tablePtr_  = this;
    i.bucketNum_ = Index(e.key_);
    i.bucketItr_ = bucketVector_[i.bucketNum_].Includes(e); 
    if (i.bucketItr_ != bucketVector_[i.bucketNum_].End())
    {
      // if (*i == e) // check not needed
      // {
        return i;
      // }
    }
    return End();
  }

  // Associative Array API

  template <typename K, typename D, class H>
  D& HashTable<K,D,H>::Get (const K& key)
  {
    EntryType e(key);
    size_t bn = Index(key);
    typename BucketType::Iterator i = bucketVector_[bn].Includes(e); 
    if (i == bucketVector_[bn].End())
      i = bucketVector_[bn].Insert(e);
    return (*i).data_;
  }

  template <typename K, typename D, class H>
  const D& HashTable<K,D,H>::Get (const K& key) const
  {
    ConstIterator i = Includes(key);
    if (i == End())
    {
      std::cerr << "** HashTable Error: const bracket operator called on non-existent key\n";
      exit (EXIT_FAILURE);
    }
    return (*i).data_;
  }

  template <typename K, typename D, class H>
  void HashTable<K,D,H>::Put (const K& key, const D& data)
  {
    // any of these works:
    Insert(key,data);
    // Get(key) = data;
    // (*this)[key] = data;
  }

  template <typename K, typename D, class H>
  D& HashTable<K,D,H>::operator[] (const K& key)
  {
    return Get(key);
  }

  template <typename K, typename D, class H>
  const D& HashTable<K,D,H>::operator[] (const K& key) const
  {
    return Get(key);
  }

  template <typename K, typename D, class H>
  bool HashTable<K,D,H>::Retrieve (const K& k, D& d) const
  {
    ConstIterator i = Includes(k);
    if (i != End())
    {
      d = (*i).data_;
      return 1;
    }
    return 0;
  }

  // proper type

  template <typename K, typename D, class H>
  HashTable <K,D,H>::HashTable (size_t n, bool prime)
    :  numBuckets_(n), bucketVector_(0), hashObject_(), prime_(prime)
  {
    // ensure at least 2 buckets
    if (numBuckets_ < 3)
      numBuckets_ = 2;
    // optionally convert to prime number of buckets
    if (prime_)
      numBuckets_ = fsu::PrimeBelow(numBuckets_);
    // create buckets
    bucketVector_.SetSize(numBuckets_);
  }

  template <typename K, typename D, class H>
  HashTable <K,D,H>::HashTable (size_t n, H hashObject, bool prime)
    :  numBuckets_(n), bucketVector_(0), hashObject_(hashObject), prime_(prime)
  {
    // ensure at least 2 buckets
    if (numBuckets_ < 3)
      numBuckets_ = 2;
    // optionally convert to prime number of buckets
    if (prime_)
      numBuckets_ = fsu::PrimeBelow(numBuckets_);
    // create buckets
    bucketVector_.SetSize(numBuckets_);
  }

  template <typename K, typename D, class H>
  HashTable <K,D,H>::HashTable (const HashTable& ht)
    :  numBuckets_(ht.numBuckets_), bucketVector_(ht.bucketVector_), hashObject_(ht.hashObject_)
  {}

  template <typename K, typename D, class H>
  HashTable <K,D,H>::~HashTable ()
  {
    Clear();
  }

  template <typename K, typename D, class H>
  HashTable<K,D,H>& HashTable <K,D,H>::operator =  (const HashTable& ht)
  {
    if (this != &ht)
    {
      numBuckets_ = ht.numBuckets_;
      bucketVector_ = ht.bucketVector_;
      hashObject_ = ht.hashObject_;
      prime_ = ht.prime_;
    }
    return *this;
  }

  // other public methods

  template <typename K, typename D, class H>
  void HashTable<K,D,H>::Rehash (size_t nb)
  {
    if (nb == 0) nb = Size();
    HashTable<K,D,H> newTable(nb,hashObject_,prime_);
    for (size_t i = 0; i < numBuckets_; ++i)
    {
      while (!bucketVector_[i].Empty()) // pop as we go saves local space bloat
      {
        newTable.Insert(bucketVector_[i].Back().key_,bucketVector_[i].Back().data_);
        bucketVector_[i].PopBack();
      }
    }
    fsu::Swap(numBuckets_,newTable.numBuckets_);
    bucketVector_.Swap(newTable.bucketVector_);
  }

  template <typename K, typename D, class H>
  void HashTable<K,D,H>::Clear ()
  {
    for (size_t i = 0; i < numBuckets_; ++i)
      bucketVector_[i].Clear();
  }

  // Iterator support

  template <typename K, typename D, class H>
  ConstHashTableIterator<K,D,H> HashTable<K,D,H>::Begin () const
  {
    // fsu::debug("Begin()");
    ConstHashTableIterator<K,D,H> i;
    i.tablePtr_ = this;
    i.bucketNum_ = 0;
    while (i.bucketNum_ < numBuckets_ && bucketVector_[i.bucketNum_].Empty())
      ++i.bucketNum_;
    // now we either have the first non-empty bucket or we've exhausted the bucket numbers
    if (i.bucketNum_ < numBuckets_)
      i.bucketItr_ = bucketVector_[i.bucketNum_].Begin();
    else
      i = this->End();
    return i;
  }

  template <typename K, typename D, class H>
  ConstHashTableIterator<K,D,H> HashTable<K,D,H>::End () const
  {
    // fsu::debug("End()");
    ConstHashTableIterator<K,D,H> i;
    i.tablePtr_ = this;
    i.bucketNum_ = numBuckets_ - 1;
    i.bucketItr_ = bucketVector_[i.bucketNum_].End();
    return i;
  }

  template <typename K, typename D, class H>
  ConstHashTableIterator<K,D,H> HashTable<K,D,H>::rBegin () const
  {
    // fsu::debug("rBegin()");
    if (numBuckets_ == 0) return rEnd();

    ConstHashTableIterator<K,D,H> i;
    i.tablePtr_ = this;
    i.bucketNum_ = numBuckets_ - 1;
    while (i.bucketNum_ > 0 && bucketVector_[i.bucketNum_].Empty())
      --i.bucketNum_;
    // now either we are at bucket 0 or the bucket is not empty
    i.bucketItr_ = bucketVector_[i.bucketNum_].rBegin();
    return i;
  }

  template <typename K, typename D, class H>
  ConstHashTableIterator<K,D,H> HashTable<K,D,H>::rEnd () const
  {
    // fsu::debug("End()");
    ConstHashTableIterator<K,D,H> i;
    i.tablePtr_ = this;
    i.bucketNum_ = 0;
    i.bucketItr_ = bucketVector_[0].rEnd();
    return i;
  }

  template <typename K, typename D, class H>
  HashTableIterator<K,D,H> HashTable<K,D,H>::Begin ()
  {
    // fsu::debug("Begin()");
    HashTableIterator<K,D,H> i;
    i.tablePtr_ = this;
    i.bucketNum_ = 0;
    while (i.bucketNum_ < numBuckets_ && bucketVector_[i.bucketNum_].Empty())
      ++i.bucketNum_;
    // now we either have the first non-empty bucket or we've exhausted the bucket numbers
    if (i.bucketNum_ < numBuckets_)
      i.bucketItr_ = bucketVector_[i.bucketNum_].Begin();
    else
      i = this->End();
    return i;
  }

  template <typename K, typename D, class H>
  HashTableIterator<K,D,H> HashTable<K,D,H>::End ()
  {
    // fsu::debug("End()");
    HashTableIterator<K,D,H> i;
    i.tablePtr_ = this;
    i.bucketNum_ = numBuckets_ - 1;
    i.bucketItr_ = bucketVector_[i.bucketNum_].End();
    return i;
  }

  template <typename K, typename D, class H>
  HashTableIterator<K,D,H> HashTable<K,D,H>::rBegin ()
  {
    // fsu::debug("rBegin()");
    if (numBuckets_ == 0) return rEnd();

    HashTableIterator<K,D,H> i;
    i.tablePtr_ = this;
    i.bucketNum_ = numBuckets_ - 1;
    while (i.bucketNum_ > 0 && bucketVector_[i.bucketNum_].Empty())
      --i.bucketNum_;
    // now either we are at bucket 0 or the bucket is not empty
    i.bucketItr_ = bucketVector_[i.bucketNum_].rBegin();
    return i;
  }

  template <typename K, typename D, class H>
  HashTableIterator<K,D,H> HashTable<K,D,H>::rEnd ()
  {
    // fsu::debug("End()");
    HashTableIterator<K,D,H> i;
    i.tablePtr_ = this;
    i.bucketNum_ = 0;
    i.bucketItr_ = bucketVector_[0].rEnd();
    return i;
  }

  // other container class protocol

  template <typename K, typename D, class H>
  size_t HashTable<K,D,H>::Size () const
  {
    size_t size(0);
    for (size_t i = 0; i < numBuckets_; ++i)
      size += bucketVector_[i].Size();
    return size;
  }

  template <typename K, typename D, class H>
  bool HashTable<K,D,H>::Empty () const
  {
    for (size_t i = 0; i < numBuckets_; ++i)
      if (!bucketVector_[i].Empty())
        return 0;
    return 1;
  }

  template <typename K, typename D, class H>
  void HashTable<K,D,H>::Dump (std::ostream& os, int c1, int c2) const
  {
    typename BucketType::ConstIterator i;
    for (size_t b = 0; b < numBuckets_; ++b)
    {
      os << "b[" << b << "]:";
      for (i = bucketVector_[b].Begin(); i != bucketVector_[b].End(); ++i)
        os << '\t' << std::setw(c1) << (*i).key_ << ':' << std::setw(c2) << (*i).data_;
      os << '\n';
    }
  }

  // private helper

  template <typename K, typename D, class H>
  size_t HashTable <K,D,H>::Index (const K& k) const
  {
    return hashObject_ (k) % numBuckets_;
  }

  //---------------------------------------------------
  //     ConstHashTableIterator <K,D,H> Implementations
  //---------------------------------------------------

  // bidirectional iterator API

  template <typename K, typename D, class H>
  ConstHashTableIterator <K,D,H>& ConstHashTableIterator<K,D,H>::operator++ ()
  {
    if (!Valid())
      return *this;
    if (*this == tablePtr_->End())
      return *this;

    ++bucketItr_;
    // if bucketItr_ is at end of bucket, restart at beginning of next non-empty bucket
    if (bucketItr_ == tablePtr_->bucketVector_[bucketNum_].End())
    {
      // do version
      do
      {
        ++bucketNum_;
      }
      while (bucketNum_ < tablePtr_->numBuckets_ && tablePtr_->bucketVector_[bucketNum_].Empty()); // */
      if (bucketNum_ < tablePtr_->numBuckets_)
      {
        bucketItr_ = tablePtr_->bucketVector_[bucketNum_].Begin();
      }
      else
      {
        *this = tablePtr_->End();
      }
    }
    return *this;
  }

  template <typename K, typename D, class H>
  ConstHashTableIterator <K,D,H>& ConstHashTableIterator<K,D,H>::operator--()
  {
    if (!Valid())
      return *this;
    if (*this == tablePtr_->rEnd())
      return *this;

    --bucketItr_;
    if (bucketItr_ == tablePtr_->bucketVector_[bucketNum_].rEnd())
    {
      // if (bucketNum_ == 0) return *this;
      if (bucketNum_ == 0)
      {
        *this = tablePtr_->rEnd();
        return *this;
      }
      do
      {
        --bucketNum_;
      }
      while (bucketNum_ > 0 && tablePtr_->bucketVector_[bucketNum_].Empty());
      bucketItr_ = tablePtr_->bucketVector_[bucketNum_].rBegin();
    }
    /*
    if (bucketItr_ == tablePtr_->bucketVector_[bucketNum_].rEnd())
    {
      while (bucketNum_ > 0 && tablePtr_->bucketVector_[bucketNum_].Empty())
      {
        --bucketNum_;
      }
      if (bucketNum_ == 0 && tablePtr_->bucketVector_[0].Empty())
      {
        *this = tablePtr_->rEnd();
      }
      else
      {
        bucketItr_ = tablePtr_->bucketVector_[bucketNum_].rBegin();
      }
    }
    */
    return *this;
  }

  template <typename K, typename D, class H>
  ConstHashTableIterator <K,D,H> ConstHashTableIterator<K,D,H>::operator++ (int)
  {
    ConstHashTableIterator <K,D,H> i = *this;
    operator++();
    return i;
  }

  template <typename K, typename D, class H>
  ConstHashTableIterator <K,D,H> ConstHashTableIterator<K,D,H>::operator-- (int)
  {
    ConstHashTableIterator <K,D,H> i = *this;
    operator--();
    return i;
  }

  template <typename K, typename D, class H>
  const fsu::Entry<K,D>& ConstHashTableIterator<K,D,H>::operator*() const
  {
    if (!Valid())
    {
      std::cerr << "** ConstHashTableIterator error: invalid dereference\n";
      exit (EXIT_FAILURE);
    }
    return *bucketItr_;
  }

  template <typename K, typename D, class H>
  bool ConstHashTableIterator<K,D,H>::operator == (const ConstIterator& i2) const
  {
    if (!Valid() && !i2.Valid())
      return 1;
    if (Valid() && !i2.Valid())
      return 0;
    if (!Valid() && i2.Valid())
      return 0;

    // now both are valid
    if (tablePtr_ != i2.tablePtr_)
      return 0;
    if (bucketNum_ != i2.bucketNum_)
      return 0;
    if (bucketItr_ != i2.bucketItr_)
      return 0;
    return 1;
  }

  template <typename K, typename D, class H>
  bool ConstHashTableIterator<K,D,H>::operator != (const ConstIterator& i2) const
  {
    return !(*this == i2);
  }

  template <typename K, typename D, class H>
  bool ConstHashTableIterator<K,D,H>::Valid () const
  {
    if (tablePtr_ == 0)
      return 0;
    if (bucketNum_ >= tablePtr_->numBuckets_)
      return 0;
    return bucketItr_ != tablePtr_->bucketVector_[bucketNum_].End();
  }

  // proper type

  template <typename K, typename D, class H>
  ConstHashTableIterator<K,D,H>::ConstHashTableIterator () 
    :  tablePtr_(0), bucketNum_(0), bucketItr_()
  {}

  template <typename K, typename D, class H>
  ConstHashTableIterator<K,D,H>::ConstHashTableIterator (const ConstIterator& i)
    :  tablePtr_(i.tablePtr_), bucketNum_(i.bucketNum_), bucketItr_(i.bucketItr_)
  {}

  template <typename K, typename D, class H>
  ConstHashTableIterator <K,D,H>& ConstHashTableIterator<K,D,H>::operator = (const ConstIterator& i)
  {
    if (this != &i)
    {
      tablePtr_  = i.tablePtr_;
      bucketNum_ = i.bucketNum_;
      bucketItr_ = i.bucketItr_;
    }
    return *this;
  }

  // type converter Iterator -> ConstIterator

  template <typename K, typename D, class H>
  ConstHashTableIterator<K,D,H>::ConstHashTableIterator (const Iterator& i)
    :  tablePtr_(i.tablePtr_), bucketNum_(i.bucketNum_), bucketItr_(i.bucketItr_)
  {}

  //----------------------------------------------
  //     HashTableIterator <K,D,H> Implementations
  //----------------------------------------------

  // bidirectional iterator API (non-const)

  template <typename K, typename D, class H>
  HashTableIterator <K,D,H>& HashTableIterator<K,D,H>::operator++ ()
  {
    if (!Valid())
      return *this;
    if (*this == tablePtr_->End())
      return *this;

    ++bucketItr_;
    // if bucketItr_ is at end of bucket, restart at beginning of next non-empty bucket
    if (bucketItr_ == tablePtr_->bucketVector_[bucketNum_].End())
    {
      do
      {
        ++bucketNum_;
      }
      while (bucketNum_ < tablePtr_->numBuckets_ && tablePtr_->bucketVector_[bucketNum_].Empty()); // */
      if (bucketNum_ < tablePtr_->numBuckets_)
      {
        bucketItr_ = tablePtr_->bucketVector_[bucketNum_].Begin();
      }
      else
      {
        *this = tablePtr_->End();
      }
    }
    return *this;
  }

  template <typename K, typename D, class H>
  HashTableIterator <K,D,H>& HashTableIterator<K,D,H>::operator--()
  {
    if (!Valid())
      return *this;
    if (*this == tablePtr_->rEnd())
      return *this;

    --bucketItr_;
    if (bucketItr_ == tablePtr_->bucketVector_[bucketNum_].rEnd())
      {
      // if (bucketNum_ == 0) return *this;
      if (bucketNum_ == 0)
      {
        *this = tablePtr_->rEnd();
        return *this;
      }
      do
      {
        --bucketNum_;
      }
      while (bucketNum_ > 0 && tablePtr_->bucketVector_[bucketNum_].Empty());
      bucketItr_ = tablePtr_->bucketVector_[bucketNum_].rBegin();
    }
    /*
    if (bucketItr_ == tablePtr_->bucketVector_[bucketNum_].rEnd())
    {
      while (bucketNum_ > 0 && tablePtr_->bucketVector_[bucketNum_].Empty())
      {
        --bucketNum_;
      }
      if (bucketNum_ == 0 && tablePtr_->bucketVector_[0].Empty())
      {
        *this = tablePtr_->rEnd();
      }
      else
      {
        bucketItr_ = tablePtr_->bucketVector_[bucketNum_].rBegin();
      }
    }
    */
    return *this;
  }

  template <typename K, typename D, class H>
  HashTableIterator <K,D,H> HashTableIterator<K,D,H>::operator ++(int)
  {
    HashTableIterator <K,D,H> i = *this;
    operator ++();
    return i;
  }

  template <typename K, typename D, class H>
  HashTableIterator <K,D,H> HashTableIterator<K,D,H>::operator --(int)
  {
    HashTableIterator <K,D,H> i = *this;
    operator --();
    return i;
  }

  template <typename K, typename D, class H>
  fsu::Entry<K,D>& HashTableIterator<K,D,H>::operator*()
  {
    if (!Valid())
    {
      std::cerr << "** HashTableIterator error: invalid dereference\n";
      exit (EXIT_FAILURE);
    }
    return *bucketItr_;
  }

  template <typename K, typename D, class H>
  const fsu::Entry<K,D>& HashTableIterator<K,D,H>::operator*() const
  {
    if (!Valid())
    {
      std::cerr << "** HashTableIterator error: invalid dereference\n";
      exit (EXIT_FAILURE);
    }
    return *bucketItr_;
  }

  template <typename K, typename D, class H>
  bool HashTableIterator<K,D,H>::operator == (const Iterator& i2) const
  {
    if (!Valid() && !i2.Valid())
      return 1;
    if (Valid() && !i2.Valid())
      return 0;
    if (!Valid() && i2.Valid())
      return 0;

    // now both are valid
    if (tablePtr_ != i2.tablePtr_)
      return 0;
    if (bucketNum_ != i2.bucketNum_)
      return 0;
    if (bucketItr_ != i2.bucketItr_)
      return 0;
    return 1;
  }

  template <typename K, typename D, class H>
  bool HashTableIterator<K,D,H>::operator != (const Iterator& i2) const
  {
    return !(*this == i2);
  }

  template <typename K, typename D, class H>
  bool HashTableIterator<K,D,H>::Valid () const
  {
    if (tablePtr_ == 0)
      return 0;
    if (bucketNum_ >= tablePtr_->numBuckets_)
      return 0;
    return bucketItr_ != tablePtr_->bucketVector_[bucketNum_].End();
  }

  // proper type

  template <typename K, typename D, class H>
  HashTableIterator<K,D,H>::HashTableIterator () 
    :  tablePtr_(0), bucketNum_(0), bucketItr_()
  {}

  template <typename K, typename D, class H>
  HashTableIterator<K,D,H>::HashTableIterator (const Iterator& i)
    :  tablePtr_(i.tablePtr_), bucketNum_(i.bucketNum_), bucketItr_(i.bucketItr_)
  {}

  template <typename K, typename D, class H>
  HashTableIterator <K,D,H>& HashTableIterator<K,D,H>::operator = (const Iterator& i)
  {
    if (this != &i)
    {
      tablePtr_  = i.tablePtr_;
      bucketNum_ = i.bucketNum_;
      bucketItr_ = i.bucketItr_;
    }
    return *this;
  }

  // no type converter ConstIterator -> Iterator !

  template <typename K, typename D, class H>
  size_t HashTable<K,D,H>::NumBuckets () const
  {
    return numBuckets_; 
  }

  #include <hashtbl.cpp> // implements Analysis and MaxBucketSize methods

  /* // non-functional implementation of Analysis
  template <typename K, typename D, class H>
  size_t HashTable<K,D,H>::MaxBucketSize () const
  {
    std::cerr << " ** MaxBucketSize not implemented\n";
    return 0;
  }

  template <typename K, typename D, class H>
  void HashTable<K,D,H>::Analysis (std::ostream& os) const
  {
    os << " ** Analysis not implemented\n";
  }
  // end non-functional */

} // namespace fsu

#endif
