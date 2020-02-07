/*
    mapiter_adt.h
    Chris Lacher
    03/02/17

    binary tree iterator classes designed to operate on 2-way trees
    (no parent pointer) with associative array API

    Container class C is assumed to define the following Node methods:

      IsDead()
      HasLeftChild()
      HasRightChild()

    Iterator support required in C:

    Iterator Begin() const
    {
      Iterator i;
      i.Init(root_);
      return i;
    }

    Iterator End() const
    {
      Iterator i;
      return i;
    }

    Iterator rBegin() const
    {
      Iterator i;
      i.rInit(root_);
      return i;
    }

    Iterator rEnd() const
    {
      Iterator i;
      return i;
    }

*/

// #include <cstddef>     // size_t
// #include <cstdint>     // uint8_t
// #include <ansicodes.h>
// #include <iostream>
// #include <iomanip>
// #include <compare.h>   // LessThan

#include <queue.h>     // LevelorderIterator,  Dump()
#include <stack.h>     // InorderIterator deque-based stack
#include <vector.h>    // InorderIterator alternative
#include <list.h>      // InorderIterator alternative
#include <entry.h>
#include <debug.h>     // argh

#ifndef _MAPITER_ADT_H
#define _MAPITER_ADT_H

namespace fsu
{

  template < class C >
  class ConstInorderMapIterator; // patterns: ConstIterator, BidirectionalIterator

  template < class C >
  class InorderMapIterator;      // patterns: Iterator, BidirectionalIterator

  template < class C >
  class PreorderMapIterator;     // patterns: ConstIterator, BidirectionalIterator

  template < class C >
  class PostorderMapIterator;    // patterns: ConstIterator, BidirectionalIterator

  template < class C >
  class LevelorderMapIterator;   // patterns: ConstIterator, ForwardIterator

  /******************************************************************/
  /*    LevelorderMapIterator < C >                                  */
  /******************************************************************/

  template < class C >
  class LevelorderMapIterator // patterns: ConstIterator, ForwardIterator
  {
  public: // terminology support
    typedef typename C::ValueType       ValueType;
    typedef typename C::Node            Node;
    typedef LevelorderMapIterator<C>    ConstIterator;
    typedef LevelorderMapIterator<C>    Iterator;

  private: // inner sanctum
    friend C;
    fsu::Queue < Node* > que_; // default is deque-based

  public:
    // first class
    LevelorderMapIterator                 () : que_() {}
    virtual  ~LevelorderMapIterator       () { que_.Clear(); }
    LevelorderMapIterator                 (const LevelorderMapIterator& i) : que_(i.que_) {}
    LevelorderMapIterator<C>&  operator=  (const LevelorderMapIterator& i) { que_ = i.que_; return *this; }

    // information/access
    bool  Valid   () const { return !que_.Empty(); } // Iterator can be de-referenced

    // various operators
    bool                       operator== (const LevelorderMapIterator& i2) const { return que_ == i2.que_; }
    bool                       operator!= (const LevelorderMapIterator& i2) const { return !(*this == i2); }
    const ValueType&           operator*  () const { return que_.Front()->value_; }
    LevelorderMapIterator<C>&  operator++ ();    // prefix
    LevelorderMapIterator<C>   operator++ (int); // postfix

    // developers helper
    void Dump( std::ostream& os = std::cout , char ofc = '\0' ) const;

  private:
    void Init      (Node* n);
    void Increment ();
  };

  template < class C >
  void LevelorderMapIterator<C>::Dump(std::ostream& os, char ofc) const
  {
    fsu::Queue < Node* > que(que_);
    if (ofc == '\0')
    {
      while (!que.Empty())
      {
        os << que.Front()->value_;
        que.Pop();
      }
    }
    else
    {
      while (!que.Empty())
      {
        os << ofc << que.Front()->value_;
        que.Pop();
      }
    }
    os << '\n';
  }
  
  template < class C >
  void LevelorderMapIterator<C>::Init(Node* n)
  {
    que_.Clear();
    if (n == nullptr) return;
    que_.Push(n);
    while (!que_.Empty() && que_.Front()->IsDead())
      Increment();
  }

  template < class C >
  void LevelorderMapIterator<C>::Increment()
   {
    // fsu::Debug("Increment()");
    if ( que_.Empty() )
      return;
    Node * n = que_.Front();
    que_.Pop();
    if (n->HasLeftChild()) que_.Push(n->lchild_);
    if (n->HasRightChild()) que_.Push(n->rchild_);
  }

  template < class C >
  LevelorderMapIterator<C>&  LevelorderMapIterator<C>::operator++ ()
  {
    // fsu::Debug("operator++()");
    do Increment();
    while (!que_.Empty() && que_.Front()->IsDead());
    return *this;
  }

  template < class C >
  LevelorderMapIterator<C>   LevelorderMapIterator<C>::operator++ (int)
  {
    LevelorderMapIterator<C> i(*this);
    this->operator++();
    return i;
  }

  /******************************************************************/
  /*    ConstInorderMapIterator < C >                               */
  /******************************************************************/

  template < class C >
  class ConstInorderMapIterator // patterns: ConstIterator, BidirectionalIterator
  {
  public: // terminology support
    typedef typename C::ValueType         ValueType;
    typedef typename C::Node              Node;
    typedef ConstInorderMapIterator<C>    ConstIterator;
    typedef InorderMapIterator<C>         Iterator;

  protected: // inner sanctum; keep stack implementation choice compatible w ChechRBLLT
    friend C;
    // fsu::Stack < Node* > stk_; // default is deque-based - better safety & error detection
    fsu::Stack < Node* , fsu::Vector < Node* > > stk_; // faster

  public:
    // first class
    ConstInorderMapIterator                 () : stk_() {}
    virtual  ~ConstInorderMapIterator       () { stk_.Clear(); }
    ConstInorderMapIterator                 (const ConstInorderMapIterator& i) : stk_(i.stk_) {}
    ConstInorderMapIterator<C>&  operator=  (const ConstInorderMapIterator& i) { stk_ = i.stk_; return *this; }

    // information/access
    bool  Valid   () const { return !stk_.Empty(); } // Iterator can be de-references

    // various operators
    bool                         operator== (const ConstInorderMapIterator& i2) const { return stk_ == i2.stk_; }
    bool                         operator!= (const ConstInorderMapIterator& i2) const { return !(*this == i2); }
    const ValueType&             operator*  () const { return stk_.Top()->value_; }
    ConstInorderMapIterator<C>&  operator++ ();    // prefix
    ConstInorderMapIterator<C>   operator++ (int); // postfix
    ConstInorderMapIterator<C>&  operator-- ();    // prefix
    ConstInorderMapIterator<C>   operator-- (int); // postfix

    // developers helper
    void Dump( std::ostream& os = std::cout , char ofc = '\0' ) const;

  private:
    void Init      (Node* n); // live nodes only
    void sInit     (Node* n); // structural (all nodes) version - pair with Increment for structural traversal
    void rInit     (Node* n); // live nodes only
    void Increment (); // structural version of ++
    void Decrement (); // structural version of --
  };

  template < class C >
  void ConstInorderMapIterator<C>::Dump(std::ostream& os, char ofc) const
  {
    fsu::Stack < Node* , fsu::Vector < Node* > > s(stk_);
    fsu::Stack < Node* , fsu::Vector < Node* > > stk;
    while (!s.Empty())
    {
      stk.Push(s.Top());
      s.Pop();
    }
    if (ofc == '\0')
    {
      while (!stk.Empty())
      {
        os << stk.Top()->value_;
        stk.Pop();
      }
    }
    else
    {
      while (!stk.Empty())
      {
        os << ofc << stk.Top()->value_;
        stk.Pop();
      }
    }
    os << '\n';
  }
  
  template < class C >
  void ConstInorderMapIterator<C>::sInit(Node* n)
  {
    if (n == nullptr) return;
    stk_.Clear();
    stk_.Push(n);
    while (n != nullptr && n->HasLeftChild())
    {
      n = n->lchild_;
      stk_.Push(n);
    }
    // while (Valid() && stk_.Top()->IsDead())
    //   Increment();
  }

  template < class C >
  void ConstInorderMapIterator<C>::Init(Node* n)
  // only intended to be used with n = root_
  {
    if (n == nullptr) return;
    stk_.Clear();
    stk_.Push(n);
    while (n != nullptr && n->HasLeftChild())
    {
      n = n->lchild_;
      stk_.Push(n);
    }
    while (Valid() && stk_.Top()->IsDead())
      Increment();
  }

  template < class C >
  void ConstInorderMapIterator<C>::rInit(Node* n)
  // only intended to be used with n = root_
  {
    if (n == nullptr) return;
    stk_.Clear();
    stk_.Push(n);
    while (n != nullptr && n->HasRightChild())
    {
      n = n->rchild_;
      stk_.Push(n);
    }
    while (!stk_.Empty() && stk_.Top()->IsDead())
      Decrement();
  }

  template < class C >
  void ConstInorderMapIterator<C>::Increment()
  {
    // fsu::Debug("Increment()");
    if ( stk_.Empty() )
      return;
    Node * n;
    if ( stk_.Top()->HasRightChild() )
    {
      // fsu::Debug("Increment branch 1");
      n = stk_.Top()->rchild_;
      stk_.Push(n);
      while ( n != nullptr && n->HasLeftChild() )
      {
        n = n->lchild_;
        stk_.Push(n);
      }
    }
    else
    {
      // fsu::Debug("Increment branch 2");
      do
      {
        n = stk_.Top();
        stk_.Pop();
      }
      while( !stk_.Empty() && stk_.Top()->HasRightChild() && n == stk_.Top()->rchild_ );
    }
  }

  template < class C >
  void ConstInorderMapIterator<C>::Decrement()
  {
    // fsu::Debug("Decrement()");
    if ( stk_.Empty() )
      return;
    Node * n;
    if ( stk_.Top()->HasLeftChild() )
    {
      // fsu::Debug("Decrement branch 1");
      n = stk_.Top()->lchild_;
      stk_.Push(n);
      while ( n != nullptr && n->HasRightChild() )
      {
        n = n->rchild_;
        stk_.Push(n);
      }
    }
    else
    {
      // fsu::Debug("Decrement branch 2");
      do
      {
        n = stk_.Top();
        stk_.Pop();
      }
      while( !stk_.Empty() && stk_.Top()->HasLeftChild() && n == stk_.Top()->lchild_ );
    }
  }

  template < class C >
  ConstInorderMapIterator<C>&  ConstInorderMapIterator<C>::operator++ ()
  {
    // fsu::Debug("operator++()");
    do Increment();
    while (!stk_.Empty() && stk_.Top()->IsDead());
    return *this;
  }

  template < class C >
  ConstInorderMapIterator<C>   ConstInorderMapIterator<C>::operator++ (int)
  {
    ConstInorderMapIterator<C> i(*this);
    this->operator++();
    return i;
  }

  template < class C >
  ConstInorderMapIterator<C>&  ConstInorderMapIterator<C>::operator-- ()
  {
    // fsu::Debug("operator--()");
    do Decrement();
    while (!stk_.Empty() && stk_.Top()->IsDead());
    return *this;
  }

  template < class C >
  ConstInorderMapIterator<C>   ConstInorderMapIterator<C>::operator-- (int)
  {
    ConstInorderMapIterator<C> i(*this);
    this->operator--();
    return i;
  }

  /******************************************************************/
  /*    InorderMapIterator < C >                                    */
  /******************************************************************/

  template < class C >
  class InorderMapIterator : public ConstInorderMapIterator<C>
  {
  private: // inner sanctum; keep stack implementation choice compatible w ChechRBLLT
    friend C;

  public:
    typedef typename C::ValueType         ValueType;
    typedef typename C::Node              Node;
    typedef ConstInorderMapIterator<C>    ConstIterator;
    typedef InorderMapIterator<C>         Iterator;

    // first class
    InorderMapIterator                 () : ConstInorderMapIterator<C>() {}
    virtual  ~InorderMapIterator       () { }
    InorderMapIterator                 (const InorderMapIterator& i) : ConstInorderMapIterator<C> (i) {}
    InorderMapIterator<C>&  operator=  (const InorderMapIterator& i) { this->stk_ = i.stk_; return *this; }

    // various operators
    bool                       operator== (const InorderMapIterator& i2) const { return this->stk_ == i2.stk_; }
    bool                       operator!= (const InorderMapIterator& i2) const { return !(*this == i2); }

    const ValueType&           operator*  () const { return this->stk_.Top()->value_; }
    ValueType&                 operator*  ()       { return this->stk_.Top()->value_; }
    InorderMapIterator<C>&     operator++ ();    // prefix
    InorderMapIterator<C>      operator++ (int); // postfix
    InorderMapIterator<C>&     operator-- ();    // prefix
    InorderMapIterator<C>      operator-- (int); // postfix

  };

  template < class C >
  InorderMapIterator<C>&  InorderMapIterator<C>::operator++ ()
  {
    ConstInorderMapIterator<C>::operator++();
    return *this;
  }

  template < class C >
  InorderMapIterator<C>   InorderMapIterator<C>::operator++ (int)
  {
    InorderMapIterator<C> i(*this);
    this->operator++();
    return i;
  }

  template < class C >
  InorderMapIterator<C>&  InorderMapIterator<C>::operator-- ()
  {
    ConstInorderMapIterator<C>::operator--();
    return *this;
  }

  template < class C >
  InorderMapIterator<C>   InorderMapIterator<C>::operator-- (int)
  {
    InorderMapIterator<C> i(*this);
    this->operator--();
    return i;
  }

  /******************************************************************/
  /*    PreorderMapIterator < C >                                    */
  /******************************************************************/

  template < class C >
  class PreorderMapIterator // patterns: ConstIterator, BidirectionalIterator
  {
  public: // terminology support
    typedef typename C::ValueType      ValueType;
    typedef typename C::Node           Node;
    typedef PreorderMapIterator<C>     ConstIterator;
    typedef PreorderMapIterator<C>     Iterator;

  private: // inner sanctum; keep stack implementation choice compatible w ChechRBLLT
    friend C;
    // fsu::Stack < Node* > stk_; // default is deque-based - better safety & error detection
    fsu::Stack < Node* , fsu::Vector < Node* > > stk_; // faster

  public:
    // first class
    PreorderMapIterator                 () : stk_() {}
    virtual  ~PreorderMapIterator       () { stk_.Clear(); }
    PreorderMapIterator                 (const PreorderMapIterator& i) : stk_(i.stk_) {}
    PreorderMapIterator<C>&  operator=  (const PreorderMapIterator& i) { stk_ = i.stk_; return *this; }

    // information/access
    bool  Valid   () const { return !stk_.Empty(); } // Iterator can be de-references

    // various operators
    bool                     operator== (const PreorderMapIterator& i2) const { return stk_ == i2.stk_; }
    bool                     operator!= (const PreorderMapIterator& i2) const { return !(*this == i2); }
    const ValueType&         operator*  () const { return stk_.Top()->value_; }
    PreorderMapIterator<C>&  operator++ ();    // prefix
    PreorderMapIterator<C>   operator++ (int); // postfix
    PreorderMapIterator<C>&  operator-- ();    // prefix
    PreorderMapIterator<C>   operator-- (int); // postfix

    // developers helper
    void Dump( std::ostream& os = std::cout , char ofc = '\0' ) const;

  private:
    void Init      (Node* n); // live nodes only
    void rInit     (Node* n); // live nodes only
    void Increment (); // structural version of ++
    void Decrement (); // structural version of --
  };

  template < class C >
  void PreorderMapIterator<C>::Dump(std::ostream& os, char ofc) const
  {
    fsu::Stack < Node* , fsu::Vector < Node* > > s(stk_);
    fsu::Stack < Node* , fsu::Vector < Node* > > stk;
    while (!s.Empty())
    {
      stk.Push(s.Top());
      s.Pop();
    }
    if (ofc == '\0')
    {
      while (!stk.Empty())
      {
        os << stk.Top()->value_;
        stk.Pop();
      }
    }
    else
    {
      while (!stk.Empty())
      {
        os << ofc << stk.Top()->value_;
        stk.Pop();
      }
    }
    os << '\n';
  }
  
  template < class C >
  void PreorderMapIterator<C>::Init(Node* n)
  // only intended to be used with n = root_
  {
    // fsu::Debug("Preorder Init()");
    if (n == nullptr) return;
    stk_.Clear();
    stk_.Push(n);
    while (Valid() && stk_.Top()->IsDead())
      Increment();
  } // Init

  template < class C >
  void PreorderMapIterator<C>::Increment()
  {
    // fsu::Debug("Preorder Increment()");
    if ( stk_.Empty() )
      return;
    Node * top = stk_.Top();
    // push left child if possible
    if (top->HasLeftChild())
    {
      stk_.Push(top->lchild_);
      return;
    }
    // push right child if possible
    if (top->HasRightChild())
    {
      stk_.Push(top->rchild_);
      return;
    }
    // otherwise pop until a right child of a left child is found and push that child
    stk_.Pop();
    bool topWasLeftChild = !stk_.Empty() && stk_.Top()->lchild_ == top;
    while ((!stk_.Empty()))
    {
      top = stk_.Top();
      if (topWasLeftChild && top->HasRightChild())
      {
        stk_.Push(top->rchild_);
        return;
      }
      stk_.Pop();
      topWasLeftChild = !stk_.Empty() && stk_.Top()->lchild_ == top;
    } // possibly make this a do-while loop 
  } // Increment()

  template < class C >
  void PreorderMapIterator<C>::rInit(Node* n)
  // only intended to be used with n = root_
  {
    // fsu::Debug("Preorder rInit()");
    if (n == nullptr) return;
    stk_.Clear();
    stk_.Push(n);
    while (n != nullptr)
    {
      if (n->HasRightChild())
      {
        n = n->rchild_;
        stk_.Push(n);
      }
      else if (n->HasLeftChild())
      {
        n = n->lchild_;
        stk_.Push(n);
      }
      else
      {
        n = nullptr;
      }
    }
    while (Valid() && stk_.Top()->IsDead())
      Decrement();
    // std::cerr << "ivalue: " << this->operator*() << '\n';
  }

  template < class C >
  void PreorderMapIterator<C>::Decrement()
  {
    // fsu::Debug("Preorder Decrement()");
    if ( stk_.Empty() )
      return;
    Node * top = stk_.Top();
    stk_.Pop();
    bool topWasRightChild = (!stk_.Empty() && stk_.Top()->rchild_ == top);
    // if child was not the left child, go to the left child
    if (topWasRightChild && stk_.Top()->HasLeftChild())
    {
      stk_.Push(stk_.Top()->lchild_);
      // and descend to bottom with right priority
      while (!stk_.Empty())
      {
        if (stk_.Top()->HasRightChild())
          stk_.Push(stk_.Top()->rchild_);
        else if (stk_.Top()->HasLeftChild())
          stk_.Push(stk_.Top()->lchild_);
        else
          break;
      }
    }
  }

  template < class C >
  PreorderMapIterator<C>&  PreorderMapIterator<C>::operator++ ()
  {
    // fsu::Debug("operator++()");
    do Increment();
    while (!stk_.Empty() && stk_.Top()->IsDead());
    return *this;
  }

  template < class C >
  PreorderMapIterator<C>   PreorderMapIterator<C>::operator++ (int)
  {
    PreorderMapIterator<C> i(*this);
    this->operator++();
    return i;
  }

  template < class C >
  PreorderMapIterator<C>&  PreorderMapIterator<C>::operator-- ()
  {
    // fsu::Debug("operator--()");
    do Decrement();
    while (!stk_.Empty() && stk_.Top()->IsDead());
    return *this;
  }

  template < class C >
  PreorderMapIterator<C>   PreorderMapIterator<C>::operator-- (int)
  {
    PreorderMapIterator<C> i(*this);
    this->operator--();
    return i;
  }

  /******************************************************************/
  /*    PostorderMapIterator < C >                                   */
  /******************************************************************/

  template < class C >
  class PostorderMapIterator // patterns: ConstIterator, BidirectionalIterator
  {
  public: // terminology support
    typedef typename C::ValueType       ValueType;
    typedef typename C::Node            Node;
    typedef PostorderMapIterator<C>     ConstIterator;
    typedef PostorderMapIterator<C>     Iterator;

  private: // inner sanctum; keep stack implementation choice compatible w ChechRBLLT
    friend C;
    // fsu::Stack < Node* > stk_; // default is deque-based - better safety & error detection
    fsu::Stack < Node* , fsu::Vector < Node* > > stk_; // faster

  public:
    // first class
    PostorderMapIterator                 () : stk_() {}
    virtual  ~PostorderMapIterator       () { stk_.Clear(); }
    PostorderMapIterator                 (const PostorderMapIterator& i) : stk_(i.stk_) {}
    PostorderMapIterator<C>&  operator=  (const PostorderMapIterator& i) { stk_ = i.stk_; return *this; }

    // information/access
    bool  Valid   () const { return !stk_.Empty(); } // Iterator can be de-references

    // various operators
    bool                      operator== (const PostorderMapIterator& i2) const { return stk_ == i2.stk_; }
    bool                      operator!= (const PostorderMapIterator& i2) const { return !(*this == i2); }
    const ValueType&          operator*  () const { return stk_.Top()->value_; }
    PostorderMapIterator<C>&  operator++ ();    // prefix
    PostorderMapIterator<C>   operator++ (int); // postfix
    PostorderMapIterator<C>&  operator-- ();    // prefix
    PostorderMapIterator<C>   operator-- (int); // postfix

    // developers helper
    void Dump( std::ostream& os = std::cout , char ofc = '\0' ) const;

  private:
    void Init      (Node* n); // live nodes only
    void rInit     (Node* n); // live nodes only
    void Increment (); // structural version of ++
    void Decrement (); // structural version of --
  };

  template < class C >
  void PostorderMapIterator<C>::Dump(std::ostream& os, char ofc) const
  {
    fsu::Stack < Node* , fsu::Vector < Node* > > s(stk_);
    fsu::Stack < Node* , fsu::Vector < Node* > > stk;
    while (!s.Empty())
    {
      stk.Push(s.Top());
      s.Pop();
    }
    if (ofc == '\0')
    {
      while (!stk.Empty())
      {
        os << stk.Top()->value_;
        stk.Pop();
      }
    }
    else
    {
      while (!stk.Empty())
      {
        os << ofc << stk.Top()->value_;
        stk.Pop();
      }
    }
    os << '\n';
  }
  
  template < class C >
  void PostorderMapIterator<C>::Init(Node* n)
  // only intended to be used with n = root_
  {
    // fsu::Debug("Postorder Init()");
    if (n == nullptr) return;
    stk_.Clear();
    stk_.Push(n);
    while (n != nullptr)
    {
      if (n->HasLeftChild())
      {
        n = n->lchild_;
        stk_.Push(n);
      }
      else if (n->HasRightChild())
      {
        n = n->rchild_;
        stk_.Push(n);
      }
      else
      {
        n = nullptr;
      }
    }
    while (Valid() && stk_.Top()->IsDead())
      Increment();
  } // Init

  template < class C >
  void PostorderMapIterator<C>::Increment()
  {
    // fsu::Debug("Postorder Increment()");
    if ( stk_.Empty() )
      return;
    Node * top = stk_.Top();
    stk_.Pop();
    bool topWasLeftChild = (!stk_.Empty() && stk_.Top()->lchild_ == top);
    if (topWasLeftChild && stk_.Top()->HasRightChild())
    {
      stk_.Push(stk_.Top()->rchild_);
      while (!stk_.Empty())
      {
        if (stk_.Top()->HasLeftChild())
          stk_.Push(stk_.Top()->lchild_);
        else if (stk_.Top()->HasRightChild())
          stk_.Push(stk_.Top()->rchild_);
        else
          break;
      }
    }
  } // Increment()

  template < class C >
  void PostorderMapIterator<C>::rInit(Node* n)
  // only intended to be used with n = root_
  {
    // fsu::Debug("Postorder rInit()");
    if (n == nullptr) return;
    stk_.Clear();
    stk_.Push(n);
    while (Valid() && stk_.Top()->IsDead())
      Increment();
  }

  template < class C >
  void PostorderMapIterator<C>::Decrement()
  {
    // fsu::Debug("Postorder Decrement()");
    if ( stk_.Empty() )
      return;
    Node * top = stk_.Top();
    // push right child if possible
    if (top->HasRightChild())
    {
      stk_.Push(top->rchild_);
      return;
    }
    // push leftt child if possible
    if (top->HasLeftChild())
    {
      stk_.Push(top->lchild_);
      return;
    }
    // otherwise pop until a left child of a right child is found and push that child
    stk_.Pop();
    bool topWasRightChild = !stk_.Empty() && stk_.Top()->rchild_ == top;
    while ((!stk_.Empty()))
    {
      top = stk_.Top();
      if (topWasRightChild && top->HasLeftChild())
      {
        stk_.Push(top->lchild_);
        return;
      }
      stk_.Pop();
      topWasRightChild = !stk_.Empty() && stk_.Top()->rchild_ == top;
    } // possibly make this a do-while loop 
  } // Decrement

  template < class C >
  PostorderMapIterator<C>&  PostorderMapIterator<C>::operator++ ()
  {
    // fsu::Debug("operator++()");
    do Increment();
    while (!stk_.Empty() && stk_.Top()->IsDead());
    return *this;
  }

  template < class C >
  PostorderMapIterator<C>   PostorderMapIterator<C>::operator++ (int)
  {
    PostorderMapIterator<C> i(*this);
    this->operator++();
    return i;
  }

  template < class C >
  PostorderMapIterator<C>&  PostorderMapIterator<C>::operator-- ()
  {
    // fsu::Debug("operator--()");
    do Decrement();
    while (!stk_.Empty() && stk_.Top()->IsDead());
    return *this;
  }

  template < class C >
  PostorderMapIterator<C>   PostorderMapIterator<C>::operator-- (int)
  {
    PostorderMapIterator<C> i(*this);
    this->operator--();
    return i;
  }

} // namespace fsu 

#endif

