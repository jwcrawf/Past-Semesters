/*
    hashtbl.h
    
    Jon Crawford

    3/19/2018
    
    Header file with templates for proj6 HashTable
*/

#ifndef _HASHTBL_H
#define _HASHTBL_H

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>    

#include <entry.h>
#include <vector.h>
#include <list.h>
#include <primes.h>
#include <genalg.h> 

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
    typedef fsu::Entry<K,D>                  EntryType;
    typedef fsu::List<EntryType>             BucketType;
    typedef H                                HashType;
    typedef typename BucketType::ValueType   ValueType;
    typedef HashTableIterator<K,D,H>         Iterator;
    typedef ConstHashTableIterator<K,D,H>    ConstIterator;

    
    Iterator       Insert        (const K& k, const D& d);
    bool           Remove        (const K& k);
    bool           Retrieve      (const K& k, D& d) const;
    ConstIterator  Includes      (const K& k) const;
    Iterator       Includes      (const K& k);

    
    D&             Get           (const K& key);
    void           Put           (const K& key, const D& data);
    D&             operator[]    (const K& key);

    
    const D&       Get           (const K& key) const;
    const D&       operator[]    (const K& key) const;

    void           Clear         ();
    void           Rehash        (size_t numBuckets = 0);
    size_t         Size          () const;
    bool           Empty         () const;

    Iterator       Begin         ();
    Iterator       End           ();
    Iterator       rBegin        ();
    Iterator       rEnd          ();

    ConstIterator  Begin         () const;
    ConstIterator  End           () const;
    ConstIterator  rBegin        () const;
    ConstIterator  rEnd          () const;


    explicit       HashTable     (size_t numBuckets = 100, bool prime = 1);
    HashTable                    (size_t numBuckets, HashType hashObject, bool prime = 1);
                   ~HashTable    ();
    HashTable                    (const HashTable<K,D,H>&);
    HashTable& operator =        (const HashTable&);

    
    void           Dump          (std::ostream& os, int c1 = 0, int c2 = 0) const;
    size_t         MaxBucketSize () const;
    void           Analysis      (std::ostream& os) const;

  private:
    
    size_t                 numBuckets_;
    Vector < BucketType >  bucketVector_;
    HashType               hashObject_;
    bool                   prime_;     // flag for prime number of buckets

    
    size_t  Index          (const KeyType& k) const;
  } ;

  //--------------------------------------------
  //     ConstHashTableIterator <K,D,H>
  //--------------------------------------------

  template <typename K, typename D, class H>
  class ConstHashTableIterator
  {
    friend class HashTable <K,D,H>;
  public:
    typedef K                                KeyType;
    typedef D                                DataType;
    typedef fsu::Entry<K,D>                  EntryType;
    typedef fsu::List<EntryType>             BucketType;
    typedef H                                HashType;
    typedef typename BucketType::ValueType   ValueType;
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
    // Entry <K,D>&               operator * ();
    const Entry <K,D>&         operator *  () const;
    bool                       operator == (const ConstIterator& i2) const;
    bool                       operator != (const ConstIterator& i2) const;

  protected:
    const HashTable <K,D,H> *           tablePtr_;
    size_t                              bucketNum_;
    typename BucketType::ConstIterator  bucketItr_;
    // typename BucketType::Iterator  bucketItr_;
  } ;

  //--------------------------------------------
  //     HashTableIterator <K,D,H>
  //--------------------------------------------

  template <typename K, typename D, class H>
  class HashTableIterator
  {
    friend class HashTable <K,D,H>;
    friend class ConstHashTableIterator <K,D,H>;
  public:
    typedef K                                KeyType;
    typedef D                                DataType;
    typedef fsu::Entry<K,D>                  EntryType;
    typedef fsu::List<EntryType>             BucketType;
    typedef H                                HashType;
    typedef typename BucketType::ValueType   ValueType;
    typedef HashTableIterator<K,D,H>         Iterator;
    typedef ConstHashTableIterator<K,D,H>    ConstIterator;

    HashTableIterator   ();
    HashTableIterator   (const Iterator& i);
    bool Valid          () const;
    HashTableIterator <K,D,H>& operator =  (const Iterator& i);
    HashTableIterator <K,D,H>& operator ++ ();
    HashTableIterator <K,D,H>  operator ++ (int);
    HashTableIterator <K,D,H>& operator -- ();
    HashTableIterator <K,D,H>  operator -- (int);
    Entry <K,D>&               operator * ();
    const Entry <K,D>&         operator *  () const;
    bool                       operator == (const Iterator& i2) const;
    bool                       operator != (const Iterator& i2) const;

  protected:
    HashTable <K,D,H> *             tablePtr_;    // auto-coverts to   const HashTable <K,D,H>
    size_t                          bucketNum_;   // no change in type from ConstIterator
    typename BucketType::Iterator   bucketItr_;   // auto-converts to  BucketType::ConstIterator
  } ;

  //--------------------------------------------
  //     HashTable <K,D,H> implementations
  //--------------------------------------------

  template <typename K, typename D, class H>
  HashTableIterator<K,D,H> HashTable<K,D,H>::Insert (const K& k, const D& d)
  {
    EntryType e(k,d);
    Iterator i;
    size_t n = Index(k);
    typename BucketType::Iterator j = bucketVector_[n].Includes(e);
    if (j == bucketVector_[n].End())
      bucketVector_[n].Insert(e); 
    else 
      (*j).data_ = d;
    i.tablePtr_ = this;
    i.bucketNum_ = n;
    i.bucketItr_ = j;      
    return i;   
  }

  template <typename K, typename D, class H>
  bool HashTable<K,D,H>::Remove (const K& k)
  {
    EntryType e(k);
    size_t n = Index(k);
    typename BucketType::Iterator j = bucketVector_[n].Includes(e);
    if (j == bucketVector_[n].End()) return false;
    bucketVector_[n].Remove(j);
    return true;
  }

  template <typename K, typename D, class H>
  ConstHashTableIterator<K,D,H> HashTable<K,D,H>::Includes (const K& k) const
  {
    EntryType e(k);
    ConstIterator i;
    size_t n = Index(k);
    typename BucketType::ConstIterator j = bucketVector_[n].Includes(e);
    if (j == bucketVector_[n].End()) return End();
    i.tablePtr_ = this;
    i.bucketNum_ = n;
    i.bucketItr_ = j;
    return i;
  }

  template <typename K, typename D, class H>
  HashTableIterator<K,D,H> HashTable<K,D,H>::Includes (const K& k)
  {
    EntryType e(k);
    Iterator i;
    size_t n = Index(k);
    typename BucketType::Iterator j = bucketVector_[n].Includes(e);
    if (j == bucketVector_[n].End()) return End();
    i.tablePtr_ = this;
    i.bucketNum_ = n;
    i.bucketItr_ = j;
    return i;
  }

  template <typename K, typename D, class H>
  D& HashTable<K,D,H>::Get (const K& key)
  {
    EntryType e(key);
    size_t n = Index(key);
    typename BucketType::Iterator j = bucketVector_[n].Includes(e);
    if (j == bucketVector_[n].End()) 
      j = bucketVector_[n].Insert(e);
    return (*j).data_;
  }

  /* ===================================== */

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
    }
    return *this;
  }

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

  /* ===================================== */

  template <typename K, typename D, class H>
  ConstHashTableIterator<K,D,H> HashTable<K,D,H>::Begin () const
  {
    ConstHashTableIterator<K,D,H> i;
    i.tablePtr_ = this;
    i.bucketNum_ = 0;
    while (i.bucketNum_ < numBuckets_ && bucketVector_[i.bucketNum_].Empty())
      ++i.bucketNum_;
    if (!i.Valid())
    {
      i.bucketNum_ = 0;
      i.bucketItr_ = bucketVector_[i.bucketNum_].End();
    }
    else
      i.bucketItr_ = bucketVector_[i.bucketNum_].Begin();
    return i;
  }

  template <typename K, typename D, class H>
  ConstHashTableIterator<K,D,H> HashTable<K,D,H>::End () const
  {
    ConstHashTableIterator<K,D,H> i;
    i.tablePtr_ = this;
    i.bucketNum_ = numBuckets_ - 1;
    i.bucketItr_ = bucketVector_[i.bucketNum_].End();
    return i;
  }

  template <typename K, typename D, class H>
  ConstHashTableIterator<K,D,H> HashTable<K,D,H>::rBegin () const
  {
    ConstHashTableIterator<K,D,H> i;
    i.tablePtr_ = this;
    i.bucketNum_ = numBuckets_ - 1;
    while (i.bucketNum_ > 0 && bucketVector_[i.bucketNum_].Empty())
      --i.bucketNum_;
    if (i.Valid())
      i.bucketItr_ = bucketVector_[i.bucketNum_].rBegin();
    else
    {
      i.bucketNum_ = numBuckets_ - 1;
      i.bucketItr_ = bucketVector_[i.bucketNum_].rEnd();
    }
    return i;
  }

  template <typename K, typename D, class H>
  ConstHashTableIterator<K,D,H> HashTable<K,D,H>::rEnd () const
  {
    ConstHashTableIterator<K,D,H> i;
    i.tablePtr_ = this;
    i.bucketNum_ = 0;
    i.bucketItr_ = bucketVector_[i.bucketNum_].rEnd();
    return i;
  }

  template <typename K, typename D, class H>
  HashTableIterator<K,D,H> HashTable<K,D,H>::Begin ()
  {
    HashTableIterator<K,D,H> i;
    i.tablePtr_ = this;
    i.bucketNum_ = 0;
    while (i.bucketNum_ < numBuckets_ && bucketVector_[i.bucketNum_].Empty())
      ++i.bucketNum_;
    if (!i.Valid())
    {
      i.bucketNum_ = 0;
      i.bucketItr_ = bucketVector_[i.bucketNum_].End();
    }
    else
      i.bucketItr_ = bucketVector_[i.bucketNum_].Begin();
    return i;      
  }

  template <typename K, typename D, class H>
  HashTableIterator<K,D,H> HashTable<K,D,H>::End ()
  {
    HashTableIterator<K,D,H> i;
    i.tablePtr_ = this;
    i.bucketNum_ = numBuckets_ - 1;
    i.bucketItr_ = bucketVector_[i.bucketNum_].End();
    return i;
  }

  template <typename K, typename D, class H>
  HashTableIterator<K,D,H> HashTable<K,D,H>::rBegin ()
  {
    HashTableIterator<K,D,H> i;
    i.tablePtr_ = this;
    i.bucketNum_ = numBuckets_ - 1;
    while (i.bucketNum_ > 0 && bucketVector_[i.bucketNum_].Empty())
      --i.bucketNum_;
    if (i.Valid())
      i.bucketItr_ = bucketVector_[i.bucketNum_].rBegin();
    else
    {
      i.bucketNum_ = numBuckets_ - 1;
      i.bucketItr_ = bucketVector_[i.bucketNum_].rEnd();
    }
    return i;
  }

  template <typename K, typename D, class H>
  HashTableIterator<K,D,H> HashTable<K,D,H>::rEnd ()
  {
    HashTableIterator<K,D,H> i;
    i.tablePtr_ = this;
    i.bucketNum_ = 0;
    i.bucketItr_ = bucketVector_[i.bucketNum_].rEnd();
    return i;
  }

  /* ===================================== */

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

  template <typename K, typename D, class H>
  size_t HashTable <K,D,H>::Index (const K& k) const
  {
    return hashObject_ (k) % numBuckets_;
  }

  //---------------------------------------------------
  //     ConstHashTableIterator <K,D,H> Implementations
  //---------------------------------------------------

  template <typename K, typename D, class H>
  ConstHashTableIterator <K,D,H>& ConstHashTableIterator<K,D,H>::operator ++ ()
  {
    if (!Valid())
      return *this;
    ++bucketItr_;
    if (Valid())
      return *this;
    else
    {
      do
      {
        ++bucketNum_;      
        if (!Valid())
          return *this = tablePtr_->End();
      } while (tablePtr_->bucketVector_[bucketNum_].Empty());  
      bucketItr_ = tablePtr_->bucketVector_[bucketNum_].Begin();
      return *this;
    }
  }

  template <typename K, typename D, class H>
  ConstHashTableIterator <K,D,H>& ConstHashTableIterator<K,D,H>::operator -- ()
  {
    if (!Valid())
      return * this;
    --bucketItr_;
    if (bucketItr_ != tablePtr_->bucketVector_[bucketNum_].rEnd())
      return *this;
    else
    {
      do
      {
        --bucketNum_;
        if (bucketNum_ >= tablePtr_->numBuckets_)
          return *this = tablePtr_->rEnd();                                                                          
      } while (bucketNum_ > 0 && tablePtr_->bucketVector_[bucketNum_].Empty());
      bucketItr_ = tablePtr_->bucketVector_[bucketNum_].rBegin();
      return *this;
    }
   }

  template <typename K, typename D, class H>
  ConstHashTableIterator <K,D,H> ConstHashTableIterator<K,D,H>::operator ++ (int)
  {
    ConstHashTableIterator <K,D,H> i = *this;
    this->operator++();
    return i;
  }

  template <typename K, typename D, class H>
  ConstHashTableIterator <K,D,H> ConstHashTableIterator<K,D,H>::operator -- (int)
  {
    ConstHashTableIterator <K,D,H> i = *this;
    this->operator--();
    return i;
  }

  /* ===================================== */

  template <typename K, typename D, class H>
  const Entry<K,D>& ConstHashTableIterator<K,D,H>::operator * () const
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

  template <typename K, typename D, class H>
  ConstHashTableIterator<K,D,H>::ConstHashTableIterator (const Iterator& i)
    :  tablePtr_(i.tablePtr_), bucketNum_(i.bucketNum_), bucketItr_(i.bucketItr_)
  {}

  //----------------------------------------------
  //     HashTableIterator <K,D,H> Implementations
  //----------------------------------------------

  template <typename K, typename D, class H>
  HashTableIterator <K,D,H>& HashTableIterator<K,D,H>::operator ++ ()
  {
    if (!Valid())
      return *this;
    ++bucketItr_;
    if (Valid())
      return *this;
    else
    {
      do 
      {
        ++bucketNum_;
        if (!Valid())
          return *this = tablePtr_->End();
      } while (tablePtr_->bucketVector_[bucketNum_].Empty());
      bucketItr_ = tablePtr_->bucketVector_[bucketNum_].Begin();
      return *this;     
    }
  }

  template <typename K, typename D, class H>
  HashTableIterator <K,D,H>& HashTableIterator<K,D,H>::operator -- ()
  {
    if (!Valid())
      return *this;
    --bucketItr_;
    if(bucketItr_ != tablePtr_->bucketVector_[bucketNum_].rEnd())
      return *this;
    else
    {
      do 
      {
        --bucketNum_;
        if (bucketNum_ >= tablePtr_->numBuckets_)
          return *this = tablePtr_->rEnd();
      } while (bucketNum_ > 0 && tablePtr_->bucketVector_[bucketNum_].Empty()); 
      bucketItr_ = tablePtr_->bucketVector_[bucketNum_].rBegin();
      return *this;    
    }                                         
  }

  template <typename K, typename D, class H>
  HashTableIterator <K,D,H> HashTableIterator<K,D,H>::operator ++ (int)
  {
    HashTableIterator <K,D,H> i = *this;
    this->operator ++();
    return i;
  }

  template <typename K, typename D, class H>
  HashTableIterator <K,D,H> HashTableIterator<K,D,H>::operator -- (int)
  {
    HashTableIterator <K,D,H> i = *this;
    this->operator --();
    return i;
  }
  
  /* ===================================== */

  template <typename K, typename D, class H>
  Entry<K,D>& HashTableIterator<K,D,H>::operator * () 
  {
    if (!Valid())
    {
      std::cerr << "** HashTableIterator error: invalid dereference\n";
      exit (EXIT_FAILURE);
    }
    return *bucketItr_;
  }

  template <typename K, typename D, class H>
  const Entry<K,D>& HashTableIterator<K,D,H>::operator * () const
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
 
  template <typename K, typename D, class H>
  size_t HashTable<K,D,H>::MaxBucketSize () const
  {   
    std::cout << " ** MaxBucketSize not implemented\n";
    return 0;
  }

  template <typename K, typename D, class H>
  void HashTable<K,D,H>::Analysis (std::ostream& os) const
  {
    os << " ** Analysis not implemented\n";
  } // Analysis

} // namespace fsu
// #include <hashtbl.cpp> // implements Analysis and MaxBucketSize methods

#endif
