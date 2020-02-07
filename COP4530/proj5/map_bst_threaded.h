/*
    map_bst_threaded.h

    Jon Crawford

    3/5/2018

    header file with templates for map_bst proj5

*/

#ifndef _MAP_BST_THREADED_H
#define _MAP_BST_THREADED_H

#include <cstddef>     // size_t
#include <cstdint>     // uint8_t
#include <iostream>
#include <iomanip>
#include <compare.h>   // LessThan
#include <queue.h>     // used in Dump()
#include <mapiter_adt.h>
#include <mapiter_threaded.h>

namespace fsu
{
  template < typename K , typename D , class P >
  class Map_BST;

  template < typename K , typename D, class P = fsu::LessThan<K> >
  class Map_BST // : public Map_BST_ADT<K,D,P>
  {
  public:

    // family ties
    friend class ConstThreadedMapIterator < fsu::Map_BST<K,D,P> >;
    friend class ThreadedMapIterator      < fsu::Map_BST<K,D,P> >;
    friend class ConstInorderMapIterator  < fsu::Map_BST<K,D,P> >;
    friend class InorderMapIterator       < fsu::Map_BST<K,D,P> >;
    friend class PreorderMapIterator      < fsu::Map_BST<K,D,P> >;
    friend class PostorderMapIterator     < fsu::Map_BST<K,D,P> >;
    friend class LevelorderMapIterator    < fsu::Map_BST<K,D,P> >;

    // terminology support
    typedef K                                            KeyType;
    typedef D                                            DataType;
    typedef P                                            PredicateType;
    typedef typename fsu::Entry <K,D>                    ValueType; // type returned by iterator operator*
    typedef ThreadedMapIterator   < Map_BST <K,D,P> >    Iterator;  // native iterator
    typedef ConstThreadedMapIterator   < Map_BST <K,D,P> >    ConstIterator; // native constiterator
    typedef PreorderMapIterator   < Map_BST <K,D,P> >    PreorderIterator;   // stack-based
    typedef InorderMapIterator    < Map_BST <K,D,P> >    InorderIterator;    // stack-based
    typedef ConstInorderMapIterator    < Map_BST <K,D,P> >    ConstInorderIterator;     // stack-based
    typedef PostorderMapIterator  < Map_BST <K,D,P> >    PostorderIterator;  // stack-based
    typedef LevelorderMapIterator < Map_BST <K,D,P> >    LevelorderIterator; // queue-based

    // native iterator support (native = threaded)
    Iterator      Begin  ();
    Iterator      End    ();
    Iterator      rBegin ();
    Iterator      rEnd   ();
    ConstIterator Begin  () const;
    ConstIterator End    () const;
    ConstIterator rBegin () const;
    ConstIterator rEnd   () const;

    // external ADT iterators
    LevelorderIterator BeginLevelorder  () const;
    LevelorderIterator EndLevelorder    () const;

    InorderIterator BeginInorder        ();
    InorderIterator EndInorder          ();
    InorderIterator rBeginInorder       ();
    InorderIterator rEndInorder         ();

    ConstInorderIterator BeginInorder   () const;
    ConstInorderIterator EndInorder     () const;
    ConstInorderIterator rBeginInorder  () const;
    ConstInorderIterator rEndInorder    () const;

    PreorderIterator BeginPreorder      () const;
    PreorderIterator EndPreorder        () const;
    PreorderIterator rBeginPreorder     () const;
    PreorderIterator rEndPreorder       () const;

    PostorderIterator BeginPostorder    () const;
    PostorderIterator EndPostorder      () const;
    PostorderIterator rBeginPostorder   () const;
    PostorderIterator rEndPostorder     () const;

    // structural iterator support
    InorderIterator BeginStructuralInorder () const;

    // proper type
             Map_BST  ();
    explicit Map_BST  (P p);
             Map_BST  (const Map_BST& map);
             ~Map_BST ();
    Map_BST& operator=(const Map_BST& map);

    // associative array API
    D&        Get         (const KeyType& k);
    void      Put         (const KeyType& k , const DataType& d);
    bool      Retrieve    (const KeyType& k, DataType& d) const;

    DataType& operator [] (const KeyType& k) { return Get(k); }

    // table API
    Iterator       Includes (const KeyType& k);
    ConstIterator  Includes (const KeyType& k) const;
    void           Insert   (const KeyType& k , const DataType& d);
    void           Insert   (Iterator i, const K& k, const D& d);

    // ordered table 
    Iterator       LowerBound (const K& k);
    Iterator       UpperBound (const K& k);
    
    // common remove operations
    void   Erase    (const KeyType& k);
    void   Clear    ();
    void   Rehash   ();

    // size operations - implemented in-line with calls to private recursive methods
    bool   Empty    () const { return root_ == nullptr; } // doesn't cover case
                                                          // of "nothing but
                                                          // tombstones"
    size_t Size     () const { return RSize(root_); }     // counts alive nodes
    size_t NumNodes () const { return RNumNodes(root_); } // counts all nodes
    int    Height   () const { return RHeight(root_); }

    // development support
    void   DumpBW   (std::ostream& os) const;
    void   Dump     (std::ostream& os) const;
    void   Dump     (std::ostream& os, int kw) const;
    void   Dump     (std::ostream& os, int kw, char fill) const;
    void   DepthDistribution (std::ostream& os, size_t skip) const;

    // diagnoistics
    bool   CheckBST        (bool verboseFlag) const; // 0,1
    bool   CheckAllThreads (bool verboseFlag) const;
    bool   CheckStructure  (bool verboseFlag) const { return CheckBST (verboseFlag) && CheckAllThreads(verboseFlag); } // generic  name

  private: // types

    enum Flags { ZERO = 0x00, DEAD = 0x01, RED = 0x02, LEFT_THREAD = 0x04, RIGHT_THREAD = 0x08, THREADS = LEFT_THREAD | RIGHT_THREAD };

    struct Node
    {
      KeyType                             key_;
      DataType                            data_;
      fsu::Entry    <KeyType,DataType>    value_;
      Node *                              lchild_,
           *                              rchild_;
      uint8_t                             flags_;
      //Flags         flags_;

      Node (const KeyType& k, const DataType& d, Flags flags)
        : value_(k,d), lchild_(nullptr), rchild_(nullptr), flags_(flags)
      {}

      // support for color management
      bool IsRed    () const { return 0 != (RED & flags_); } // needs implementation
      bool IsBlack  () const { return !IsRed(); } // needs implementation
      void SetRed   ()       { flags_ |= RED; } // needs implementation
      void SetBlack ()       { flags_ &= ~RED; } // needs implementation

      // support for graveyard management
      bool IsDead   () const { return 0 != (DEAD & flags_); } // needs implementation
      bool IsAlive  () const { return !IsDead(); } // needs implementation
      void SetDead  ()       { flags_ |= DEAD; value_.data_ = D(); } // needs implementation
      void SetAlive ()       { flags_ &= ~DEAD; } // needs implementation

      // support for search
      bool HasLeftChild       () const { return (lchild_ != nullptr) && !(IsLeftThreaded()); }
      bool HasRightChild      () const { return (rchild_ != nullptr) && !(IsRightThreaded()); }

      // support for threaded management   
      bool IsLeftThreaded     () const  { return 0 != (LEFT_THREAD & flags_); }
      bool IsRightThreaded    () const  { return 0 != (RIGHT_THREAD & flags_); }
      void SetLeftThread      (Node* n) { lchild_ = n; flags_ |= LEFT_THREAD; }
      void SetRightThread     (Node* n) { rchild_ = n; flags_ |= RIGHT_THREAD; }
      void SetLeftChild       (Node* n) { lchild_ = n; flags_ &= ~LEFT_THREAD; }
      void SetRightChild      (Node* n) { rchild_ = n; flags_ &= ~RIGHT_THREAD; }

      static const char* ColorMap (uint8_t flags)
      {
        flags &= 0x03; // last 2 bits only
        switch(flags)
        {
          case 0x00: return ANSI_BOLD_BLUE;        // bits 00 = !RED |  ALIVE 
          case 0x01: return ANSI_BOLD_BLUE_SHADED; // bits 01 = !RED | !ALIVE
          case 0x02: return ANSI_BOLD_RED;         // bits 10 =  RED |  ALIVE
          case 0x03: return ANSI_BOLD_RED_SHADED;  // bits 11 =  RED | !ALIVE
          default: return "unknown color";   // unknown flags
        }
      }

      static char BWMap (uint8_t flags)
      {
        flags &= 0x03;
        switch(flags)
        {
          case 0x00: return 'B'; // bits 00 black alive
          case 0x01: return 'b'; // bits 01 black dead
          case 0x02: return 'R'; // bits 10 red alive
          case 0x03: return 'r'; // bits 11 red dead
          default:   return 'U'; // unknown flags
        }
      }

      // node dump - may be used during development
      void Dump (std::ostream& os = std::cout) const
      {
        os << "  Node data:\n"
           << "    value:          " << value_  << '\n'
           << "    color:          " << (size_t)IsRed() << '\n'
           << "    alive:          " << (size_t)IsAlive() << '\n'
           << "    left_threaded:  " << (size_t)IsLeftThreaded() << '\n'
           << "    right_threaded: " << (size_t)IsRightThreaded() << '\n';
        os << "    lchild:         ";
        if (lchild_ != nullptr)
        {
          if (IsLeftThreaded())
            os << lchild_->value_  << " (predecessor)\n";
          else
            os << lchild_->value_  << " (left child)\n";
        }
        else
          os << "NULL\n";
        os << "    rchild:         ";
        if (rchild_ != nullptr)
        {
          if (IsRightThreaded())
            os << rchild_->value_  << " (succecessor)\n";
          else
            os << rchild_->value_  << " (right child)\n";
        }
        else
          os << "NULL\n";
        os << std::flush;
      }
    }; // end struct Node

  private: // class data
    Node *         root_;
    PredicateType  pred_;

  private: // methods
    void SetAllThreads ();

    static Node * NewNode     (const K& k, const D& d, Flags flags = ZERO);
    static void   RRelease    (Node* n); // deletes all descendants of n
    static Node * RClone      (const Node* n); // returns deep copy of n
    static size_t RSize       (Node * n);
    static size_t RNumNodes   (Node * n);
    static int    RHeight     (Node * n);

  }; // end class Map_BST<>

  // define equality using class iterator type

  template < typename K , typename D , class P > 
  bool operator == (const Map_BST<K,D,P>& map1, const Map_BST<K,D,P>& map2)
  {
    typename Map_BST<K,D,P>::ConstIterator i1, i2;
    for (i1 = map1.Begin(), i2 = map2.Begin();
         (i1 != map1.End()) && (i2 != map2.End()); ++i1, ++i2)
    {
      if ((*i1).key_ != (*i2).key_ || (*i1).data_ != (*i2).data_)
        return 0;
    }
    if (i1 != map1.End() || i2 != map2.End())
      return 0;
    return 1;
  }

  template < typename K , typename D , class P > 
  bool operator != (const Map_BST<K,D,P>& b1, const Map_BST<K,D,P>& b2)
  {
    return !(b1 == b2);
  }

  // Iterator support methods
  
  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::Iterator Map_BST<K,D,P>::Begin()
  {
    Iterator i; 
    i.Init(root_);
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::Iterator Map_BST<K,D,P>::End()
  {
    Iterator i;
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::Iterator Map_BST<K,D,P>::rBegin()
  {
    Iterator i;
    i.rInit(root_);
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::Iterator Map_BST<K,D,P>::rEnd()
  {
    Iterator i;
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::ConstIterator Map_BST<K,D,P>::Begin() const
  {
    ConstIterator i;
    i.Init(root_);
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::ConstIterator Map_BST<K,D,P>::End() const
  {
    ConstIterator i;
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::ConstIterator Map_BST<K,D,P>::rBegin() const
  {
    ConstIterator i;
    i.rInit(root_);
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::ConstIterator Map_BST<K,D,P>::rEnd() const
  {
    ConstIterator i;
    return i;
  }

  // the Iterator locator methods 

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::Iterator Map_BST<K,D,P>::Includes ( const K& k )
  {  
    if (this->root_ == nullptr)
      return End();
    Iterator i = End();
    Node * n = this->root_;
    bool finished = 0;
    while (! finished)
    {
      i.node_ = n;
      if (this->pred_(k,n->value_.key_)) 
      {
        
        if (n->HasLeftChild())
          n = n->lchild_;
        else
          finished = 1;
      }
      else if (this->pred_(n->value_.key_,k)) 
      {
        
        if (n->HasRightChild())
          n = n->rchild_;
        else
          finished = 1;
      }
      else       
      {
        if (i.Valid() && k == (*i).key_)
          return i;
        else 
          return End();
      }
    }
    return End(); 
  }// end Includes(k)

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::ConstIterator Map_BST<K,D,P>::Includes ( const K& k ) const
  {
    if (this->root_ == nullptr)
      return End();
    ConstIterator i = End();
    Node * n = this->root_;
    bool finished = 0;
    while (! finished)
    {
      i.node_ = n;
      if (this->pred_(k,n->value_.key_))
      {

        if (n->HasLeftChild())
          n = n->lchild_;
        else
          finished = 1;
      }
      else if (this->pred_(n->value_.key_,k))
      {

        if (n->HasRightChild())
          n = n->rchild_;
        else
          finished = 1;
      }
      else
      {
        if (i.Valid() && k == (*i).key_)
          return i;
        else
          return End();
      }
    }
    return End();
  }// end Includes(k) const

  template < typename K , typename D , class P >
  void Map_BST<K,D,P>::Put (const K& k, const D& d)
  {
    Get(k) = d;
  }

  template < typename K , typename D , class P >
  void Map_BST<K,D,P>::Insert (const K& k, const D& d)
  {
    Put(k,d);
  }

  template < typename K , typename D , class P >
  D& Map_BST<K,D,P>::Get (const K& k)
  {
    if (root_ == nullptr)
    {  
      root_ = NewNode(k,D());
      return root_->value_.data_;
    }                  
    Node * p = nullptr;  
    Node * n = root_;
    bool finished = 0;
    do
    {
      p = n;
      if (pred_(k,n->value_.key_)) 
      {
        if (n->HasLeftChild())
          n = n->lchild_;        
        else                     
        {
          n = NewNode(k,D(),THREADS);
          n->SetLeftThread(p->lchild_);
          n->SetRightThread(p);
          p->SetLeftChild(n);
          finished = 1;            
        }
      }
      else if (pred_(n->value_.key_,k))
      {
        if (n->HasRightChild())      
          n = n->rchild_;        
        else
        {
          n = NewNode(k,D(),THREADS);
          n->SetRightThread(p->rchild_);
          n->SetLeftThread(p);
          p->SetRightChild(n);
          finished = 1;
        }
      }
      else 
      {
        n->SetAlive();     
        finished = 1;    
      }
    }
    while (!finished);
    return n->value_.data_;
  } // end Get(k)
       
  template < typename K , typename D , class P >
  bool Map_BST<K,D,P>::Retrieve (const K& k, D& d) const
  {
    Node * n = root_;
    while(n != nullptr)
    {
      if (pred_(k,n->value_.key_))     
        n = n->lchild_;
      else if (pred_(n->value_.key_,k))
        n = n->rchild_;
      else if (n->IsAlive()) 
      {
        d = n->value_.data_;
        return 1;
      }
      else
        return 0;
    }
    return 0;
  }

  template < typename K , typename D , class P >
  void Map_BST<K,D,P>::Erase ( const K& k )
  {
    Node * n = root_;
    while(n)
    {
      if (pred_(k,n->value_.key_)) 
        n = n->lchild_;
      else if (pred_(n->value_.key_,k)) 
        n = n->rchild_;
      else
      {
        n->SetDead();
        return;
      }
    }
  }

  template < typename K , typename D , class P >
  void Map_BST<K,D,P>::Clear()
  {
    RRelease(root_);
    delete root_;
    root_ = nullptr;
  }

  // recursive support methods
  template < typename K , typename D , class P >
  size_t Map_BST<K,D,P>::RSize(Node * n)
  {
    if (n == nullptr) return 0;
    size_t lh = 0, rh = 0;
    if(n->HasLeftChild())
      lh = RSize(n->lchild_);
    if(n->HasRightChild())
      rh = RSize(n->rchild_);
    return (size_t)(n->IsAlive()) + lh + rh;  
  }

  template < typename K , typename D , class P >
  size_t Map_BST<K,D,P>::RNumNodes(Node * n)
  {
    if (n == nullptr) return 0;
    size_t lh = 0, rh = 0;
    if(n->HasLeftChild())
      lh = RNumNodes(n->lchild_);
    if(n->HasRightChild())
      rh = RNumNodes(n->rchild_);
    return 1 + lh + rh;
  }

  template < typename K , typename D , class P >
  int Map_BST<K,D,P>::RHeight(Node * n)
  {
    if (n == nullptr) return -1;
    if (!n->HasLeftChild() && !n->HasRightChild()) return 0;
    int lh = 0, rh = 0;       
    if(n->HasLeftChild())
      lh = RHeight(n->lchild_);
    if(n->HasRightChild())
      rh = RHeight(n->rchild_);
    if (rh < lh) return 1 + lh;
    return 1 + rh;
  }

  template < typename K , typename D , class P >
  void Map_BST<K,D,P>::RRelease(Node* n)
  // post:  all descendants of n have been deleted
  {
    if (n != nullptr)
    {
      if (n->HasLeftChild())
      {
        RRelease(n->lchild_);
        delete n->lchild_;
        n->lchild_ = nullptr;
      }
      if (n->HasRightChild())
      {
        RRelease(n->rchild_);
        delete n->rchild_;
        n->rchild_ = nullptr;
      }
    }
  }

  /***********************************************/
  /* below here all implementations are provided */
  /***********************************************/

  template < typename K , typename D , class P >
  void Map_BST<K,D,P>::Insert (Iterator i, const K& k, const D& d)
  {
    if (i.Valid() && k == (*i).key_)
    {
      i.node_->value_.data_ = d;
      i.node_->SetAlive();
      return;
    }
    Map_BST<K,D,P>::Insert(k,d);
  }
  
  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::Iterator Map_BST<K,D,P>::LowerBound ( const K& k )
  {
    if (this->root_ == nullptr)
      return End();
    Iterator l = End();
    Node * n = this->root_;
    bool finished = 0;
    while (! finished)
    {
      if (!this->pred_(n->value_.key_,k)) // t <= n
      {
        l.node_ = n;
        if (n->HasLeftChild())
          n = n->lchild_;
        else
          finished = 1;
      }
      else // t > n
      {
        if (n->HasRightChild())
          n = n->rchild_;
        else
          finished = 1;
      }
    }
    // take care of dead node case
    if (l.Valid() && l.node_->IsDead())
      ++l;
    return l;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::Iterator Map_BST<K,D,P>::UpperBound ( const K& k )
  {
    if (this->root_ == nullptr)
      return End();
    Iterator u = End();
    Node * n = this->root_;
    bool finished = 0;
    while (! finished)
    {
      if (this->pred_(k,n->value_.key_)) // t < n
      {
        u.node_ = n;
        if (n->HasLeftChild())
          n = n->lchild_;
        else
          finished = 1;
      }
      else // t >= n
      {
        if (n->HasRightChild())
          n = n->rchild_;
        else
          finished = 1;
      }
    }
    // take care of dead node case
    if (u.Valid() && u.node_->IsDead())
      ++u;
    return u;
  }
  
  template < typename K , typename D , class P >
  void Map_BST<K,D,P>::Rehash()
  // restructure with no tombstones
  {
    Map_BST<K,D,P> newtree;
    for (PreorderIterator i = this->BeginPreorder(); i != this->EndPreorder(); ++i)
    // for (LevelorderIterator i = this->BeginLevelorder(); i != this->EndLevelorder(); ++i)
    {
      newtree.Insert((*i).key_, (*i).data_);
    }
    fsu::Swap(this->root_,newtree.root_);
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::Node* Map_BST<K,D,P>::RClone(const Map_BST<K,D,P>::Node* n)
  // returns a pointer to a deep copy of n
  // parentless version
  // does NOT set threads!
  {

    if (n == nullptr)
      return nullptr;
    Node* newN = NewNode (n->value_.key_, n->value_.data_, (Flags)n->flags_);
    if (n->HasLeftChild())
      newN->lchild_ = RClone(n->lchild_);
    else
      newN->lchild_ = nullptr;
    if (n->HasRightChild())
      newN->rchild_ = RClone(n->rchild_);
    else
      newN->rchild_ = nullptr;
    return newN;
  } // end RClone() */

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::Node * Map_BST<K,D,P>::NewNode(const K& k, const D& d, Flags flags) 
  {
    Node * nPtr = new(std::nothrow) Node(k,d,flags);
    if (nPtr == nullptr)
    {
      std::cerr << "** Map_BST memory allocation failure\n";
      // handle exception in-class here
    }
    return nPtr;
  }

  // proper type
  
  template < typename K , typename D , class P >
  Map_BST<K,D,P>::Map_BST  () : root_(nullptr), pred_()
  {}

  template < typename K , typename D , class P >
  Map_BST<K,D,P>::Map_BST  (P p) : root_(nullptr), pred_(p)
  {}

  template < typename K , typename D , class P >
  Map_BST<K,D,P>::~Map_BST ()
  {
    this->Clear();
  }

  template < typename K , typename D , class P >
  Map_BST<K,D,P>::Map_BST( const Map_BST<K,D,P>& tree )
  {
    root_ = RClone(tree.root_);
    this->SetAllThreads();
  }

  template < typename K , typename D , class P >
  Map_BST<K,D,P>& Map_BST<K,D,P>::operator=( const Map_BST<K,D,P>& that )
  {
    if (this != &that)
    {
      Clear();
      root_ = RClone(that.root_);
      this->SetAllThreads();
    }
    return *this;
  }

  // "Structural" iteration goes over the tree (not the represented set)
  // stopping at ALL nodes, dead or alive.
  // A structural traversal is used by the SetAllThreads method, a critical step
  // in copying a threaded BST.
  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::InorderIterator Map_BST<K,D,P>::BeginStructuralInorder () const
  {
    InorderIterator i;
    i.sInit(root_);
    return i;
  }

  // protected helper method prototyped in base class
  template < typename K , typename D , class P >
  void Map_BST<K,D,P>::SetAllThreads ()
  {
    // fsu::Debug("SetAllThreads");
    InorderIterator i = BeginStructuralInorder();
    if (i == EndInorder()) return;
    Node * n1, * n2;
    n1 = i.stk_.Top();
    n1->SetLeftThread(nullptr);
    i.Increment();
    while (i != EndInorder())
    {
      n2 = i.stk_.Top();
      if (!n1->HasRightChild())
      {
        n1->SetRightThread(n2);
      }
      if (!n2->HasLeftChild())
      {
        n2->SetLeftThread(n1);
      }
      n1 = n2;
      i.Increment();
    }
    n1->SetRightThread(nullptr);
  }

  // ADT-based iterator support

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::InorderIterator Map_BST<K,D,P>::BeginInorder()
  {
    InorderIterator i;
    i.Init(this->root_);
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::InorderIterator Map_BST<K,D,P>::EndInorder()
  {
    InorderIterator i;
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::InorderIterator Map_BST<K,D,P>::rBeginInorder()
  {
    InorderIterator i;
    i.rInit(this->root_);
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::InorderIterator Map_BST<K,D,P>::rEndInorder()
  {
    InorderIterator i;
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::ConstInorderIterator Map_BST<K,D,P>::BeginInorder() const
  {
    ConstInorderIterator i;
    i.Init(this->root_);
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::ConstInorderIterator Map_BST<K,D,P>::EndInorder() const
  {
    ConstInorderIterator i;
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::ConstInorderIterator Map_BST<K,D,P>::rBeginInorder() const
  {
    ConstInorderIterator i;
    i.rInit(this->root_);
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::ConstInorderIterator Map_BST<K,D,P>::rEndInorder() const
  {
    ConstInorderIterator i;
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::LevelorderIterator Map_BST<K,D,P>::BeginLevelorder() const
  {
    LevelorderIterator i;
    i.Init(this->root_);
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::LevelorderIterator Map_BST<K,D,P>::EndLevelorder() const
  {
    LevelorderIterator i;
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::PreorderIterator Map_BST<K,D,P>::BeginPreorder() const
  {
    PreorderIterator i;
    i.Init(this->root_);
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::PreorderIterator Map_BST<K,D,P>::EndPreorder() const
  {
    PreorderIterator i;
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::PreorderIterator Map_BST<K,D,P>::rBeginPreorder() const
  {
    PreorderIterator i;
    i.rInit(this->root_);
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::PreorderIterator Map_BST<K,D,P>::rEndPreorder() const
  {
    PreorderIterator i;
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::PostorderIterator Map_BST<K,D,P>::BeginPostorder() const
  {
    PostorderIterator i;
    i.Init(this->root_);
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::PostorderIterator Map_BST<K,D,P>::EndPostorder() const
  {
    PostorderIterator i;
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::PostorderIterator Map_BST<K,D,P>::rBeginPostorder() const
  {
    PostorderIterator i;
    i.rInit(this->root_);
    return i;
  }

  template < typename K , typename D , class P >
  typename Map_BST<K,D,P>::PostorderIterator Map_BST<K,D,P>::rEndPostorder() const
  {
    PostorderIterator i;
    return i;
  }

#include <map_bst_threaded_tools.cpp>

} // namespace fsu 

#endif

