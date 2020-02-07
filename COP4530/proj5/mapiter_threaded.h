/*
    mapiter_threaded.h

    Jon Crawford

    3/5/2018

    header file with iterator class for Map proj5
*/

#include <cstddef>     // size_t
#include <cstdint>     // uint8_t
#include <ansicodes.h>
#include <iostream>
#include <iomanip>

#ifndef _MAPITER_THREADED_H
#define _MAPITER_THREADED_H

namespace fsu
{

  template < class C >
  class ConstThreadedMapIterator;   // patterns: ConstIterator, BidirectionalIterator

  template < class C >
  class ThreadedMapIterator;        // patterns: Iterator, BidirectionalIterator

  /*****************************************************/
  /*        class ConstThreadedMapIterator < C >       */
  /*****************************************************/

  template < class C >
  class ConstThreadedMapIterator // a ConstIterator pattern
  {
  protected:
    friend   C;
    typename C::Node* node_;

  public:
    // terminology support
    typedef typename C::ValueType        ValueType;
    typedef typename C::Node             Node;
    typedef ConstThreadedMapIterator<C>  ConstIterator;
    typedef ThreadedMapIterator<C>       Iterator;

    // constructors
             ConstThreadedMapIterator  ();
    virtual  ~ConstThreadedMapIterator ();
             ConstThreadedMapIterator  (Node* n);    // type converter
             ConstThreadedMapIterator  (const ConstThreadedMapIterator& i); // copy ctor

    // information/access
    bool  Valid   () const; // cursor is valid element

    // various operators
    bool                     operator == (const ConstThreadedMapIterator& i2) const;
    bool                     operator != (const ConstThreadedMapIterator& i2) const;
    const ValueType&         operator *  () const; // const version
    //ValueType&               operator *  ();       // non-const version
    ConstThreadedMapIterator<C>&  operator =  (const ConstThreadedMapIterator& i);
    ConstThreadedMapIterator<C>&  operator ++ ();    // prefix
    ConstThreadedMapIterator<C>   operator ++ (int); // postfix
    ConstThreadedMapIterator<C>&  operator -- ();    // prefix
    ConstThreadedMapIterator<C>   operator -- (int); // postfix

    // developers helper
    void Dump    ( std::ostream& os = std::cout , char = '\0' );

  private:
    void Init        (Node*);   
    void rInit       (Node*);
    void Increment   ();  // moves to next inorder node
    void Decrement   ();  // moves to previous inorder node

  };

  // protected increment/decrement
  template < class C >
  void ConstThreadedMapIterator<C>::Init(Node* n)
  {
    node_ = n;
    while (node_ != nullptr && node_->HasLeftChild())
      node_ = node_->lchild_;
    while (node_ != nullptr && node_->IsDead())
      Increment();
  }

  template < class C >
  void ConstThreadedMapIterator<C>::rInit(Node* n)
  {
    node_ = n;
    while (node_ != nullptr && node_->HasRightChild())
      node_ = node_->rchild_;
    while (node_ != nullptr && node_->IsDead())
      Decrement();
  }

  template < class C >
  void ConstThreadedMapIterator<C>::Increment ()
  {
    if (node_ == nullptr) return;
    if (node_->IsRightThreaded())
    {
      node_ = node_->rchild_;
      return;
    }
    node_ = node_->rchild_;
    while (node_ != nullptr && node_->HasLeftChild())
      node_ = node_->lchild_;
  }

  template < class C >
  void ConstThreadedMapIterator<C>::Decrement ()
  {
    if (node_ == nullptr) return;
    if (node_->IsLeftThreaded())
    {
      node_ = node_->lchild_;
      return;
    }
    node_ = node_->lchild_;
    while (node_ != nullptr && node_->HasRightChild())
      node_ = node_->rchild_;
  }

  template < class C >
  bool ConstThreadedMapIterator<C>::Valid() const
  {
    return node_ != nullptr;
  }

  // other operators

  template < class C >
  ConstThreadedMapIterator<C> & ConstThreadedMapIterator<C>::operator ++()
  {
    do Increment();
    while (node_ != nullptr && node_->IsDead());
    return *this;  
  }

  template < class C >
  ConstThreadedMapIterator<C>   ConstThreadedMapIterator<C>::operator ++(int)
  {
    Iterator i = *this;
    operator ++();
    return i;
  }

  template < class C >
  ConstThreadedMapIterator<C> & ConstThreadedMapIterator<C>::operator --()
  {
    do Decrement();
    while (node_ != nullptr && node_->IsDead());
    return *this;
  }

  template < class C >
  ConstThreadedMapIterator<C>   ConstThreadedMapIterator<C>::operator --(int)
  {
    Iterator i = *this;
    operator --();
    return i;
  }

  template < class C >
  const typename C::ValueType& ConstThreadedMapIterator<C>::operator *() const
  {
    return this->node_->value_;
  }

  template < class C >
  bool ConstThreadedMapIterator<C>::operator == (const ConstThreadedMapIterator<C>& i2) const
  {
    return (this->node_ == i2.mode_);
  }

  template < class C >
  bool ConstThreadedMapIterator<C>::operator != (const ConstThreadedMapIterator<C>& i2) const
  {
    return (this->node_ != i2.node_);
  }

  /*****************************************************/
  /*        class ThreadedMapIterator < C >             */
  /*****************************************************/

  template < class C >
  class ThreadedMapIterator : public ConstThreadedMapIterator <C>
  {
  private:
    friend   C;
    // typename C::Node* node_;

  public:
    // terminology support
    typedef typename C::ValueType    ValueType;
    typedef typename C::Node         Node;
    typedef ThreadedMapIterator<C>   ConstIterator;
    typedef ThreadedMapIterator<C>   Iterator;

    // constructors
             ThreadedMapIterator  ();
    virtual  ~ThreadedMapIterator ();
             ThreadedMapIterator  (Node* n);    // type converter
             ThreadedMapIterator  (const ThreadedMapIterator& i); // copy ctor

    // information/access
    // bool  Valid   () const; // cursor is valid element

    // various operators
    bool                     operator == (const ThreadedMapIterator& i2) const;
    bool                     operator != (const ThreadedMapIterator& i2) const;
    const ValueType&         operator *  () const; // const version
    ValueType&               operator *  ();       // non-const version
    ThreadedMapIterator<C>&  operator =  (const ThreadedMapIterator& i);
    ThreadedMapIterator<C>&  operator ++ ();    // prefix
    ThreadedMapIterator<C>   operator ++ (int); // postfix
    ThreadedMapIterator<C>&  operator -- ();    // prefix
    ThreadedMapIterator<C>   operator -- (int); // postfix

    // developers helper
    // void Dump    ( std::ostream& os = std::cout , char = '\0' );

  private:
    // void Init        (Node*);   
    // void rInit       (Node*);
    // void Increment   ();  // moves to next inorder node
    // void Decrement   ();  // moves to previous inorder node

  };

  template < class C >
  bool ThreadedMapIterator<C>::operator == (const ThreadedMapIterator<C>& i2) const
  {
    return (this->node_ == i2.node_);
  }

  template < class C >
  bool ThreadedMapIterator<C>::operator != (const ThreadedMapIterator<C>& i2) const
  {
    return (this->node_ != i2.node_);
  }

  /**************************************************/
  /* below here everything is implemented correctly */ 
  /**************************************************/

  // proper types

  template < class C >
  ConstThreadedMapIterator<C>::ConstThreadedMapIterator ()  :  node_()
  {}

  template < class C >
  ConstThreadedMapIterator<C>::~ConstThreadedMapIterator () 
  {}

  template < class C >
  ConstThreadedMapIterator<C>::ConstThreadedMapIterator (const ConstThreadedMapIterator<C>& i)
    :  node_(i.node_)
  {}

  template < class C >
  ConstThreadedMapIterator<C>::ConstThreadedMapIterator (Node * n)
    :  node_(n)
  {}

  template < class C >
  ConstThreadedMapIterator<C> & ConstThreadedMapIterator<C>::operator =  (const ConstThreadedMapIterator<C>& i)
  {
    this->node_ = i.node_;
    return *this;
  }

  template < class C >
  ThreadedMapIterator<C>::ThreadedMapIterator ()  :  ConstThreadedMapIterator<C>()
  {}

  template < class C >
  ThreadedMapIterator<C>::~ThreadedMapIterator () 
  {}

  template < class C >
  ThreadedMapIterator<C>::ThreadedMapIterator (const ThreadedMapIterator<C>& i)
    :  ConstThreadedMapIterator<C>(i)
  {}

  template < class C >
  ThreadedMapIterator<C>::ThreadedMapIterator (Node * n)
    :  ConstThreadedMapIterator<C>(n)
  {}

  // derived class operators implemented with calls to base class versions

  template < class C >
  ThreadedMapIterator<C> & ThreadedMapIterator<C>::operator =  (const ThreadedMapIterator<C>& i)
  {
    ConstThreadedMapIterator<C>::operator=(i);
    return *this;
  }

  template < class C >
  ThreadedMapIterator<C> & ThreadedMapIterator<C>::operator ++()
  {
    ConstThreadedMapIterator<C>::operator++();
    return *this;
  }

  template < class C >
  ThreadedMapIterator<C>   ThreadedMapIterator<C>::operator ++(int)
  {
    ThreadedMapIterator<C> i = *this;
    operator ++();
    return i;
  }

  template < class C >
  ThreadedMapIterator<C> & ThreadedMapIterator<C>::operator --()
  {
    ConstThreadedMapIterator<C>::operator--();
    return *this;
  }

  template < class C >
  ThreadedMapIterator<C>   ThreadedMapIterator<C>::operator --(int)
  {
    ThreadedMapIterator<C> i = *this;
    operator --();
    return i;
  }

  template < class C >
  const typename C::ValueType& ThreadedMapIterator<C>::operator *() const
  {
    return this->node_->value_;
  }

  template < class C >
  typename C::ValueType& ThreadedMapIterator<C>::operator *()
  {
    return this->node_->value_;
  }

  // the iterator dump method is completely implemented here:

  template < class C >
  void ConstThreadedMapIterator<C>::Dump(std::ostream& os , char)
  {
    os << "node: " << node_->value_ << " , ";
    if (node_->IsRightThreaded())
    {
      if (node_->rchild_ == nullptr)
        os << "++: null , ";
      else
        os << "++: " << node_->rchild_->value_ << " , ";
    }
    else
    {
      if (node_->rchild_ == nullptr)
        os << "rchild: null , ";
      else
        os << "rchild: " << node_->rchild_->value_ << " , ";
    }
    if (node_->IsLeftThreaded())
    {
      if (node_->lchild_ == nullptr)
        os << "--: null\n";
      else
        os << "--: " << node_->lchild_->value_ << '\n';
    }
    else
    {
      if (node_->lchild_ == nullptr)
        os << "lchild: null\n";
      else
        os << "lchild: " << node_->lchild_->value_ << '\n';
    }
  }
    
} // namespace fsu 

#endif

