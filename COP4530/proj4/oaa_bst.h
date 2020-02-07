/*
    oaa_bst.h
    
    Jon Crawford
    
    2/27/2018
		
    header file for class OAA 
*/

#ifndef _OAA_BST_H
#define _OAA_BST_H

#include <cstddef>    // size_t
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <compare.h>  // LessThan
#include <queue.h>    // used in Dump()
#include <ansicodes.h>
#include <genalg.h>

const size_t max_display_height = 6; // used by Dump methods

namespace fsu
{
  template < typename K , typename D , class P >
  class OAA;

  template < typename K , typename D , class P = LessThan<K> >
  class OAA
  {
  public:

    typedef K    KeyType;
    typedef D    DataType;
    typedef P    PredicateType;

             OAA  ();
    explicit OAA  (P p);
             OAA  (const OAA& a);
             ~OAA ();
    OAA& operator=(const OAA& a);

    DataType& operator [] (const KeyType& k)        { return Get(k); }

    void   Put        (const KeyType& k , const DataType& d) { Get(k) = d; }
    D&     Get        (const KeyType& k);
    bool   Retrieve   (const KeyType& k, DataType& d) const;

    void   Erase      (const KeyType& k);
    void   Clear      ();
    void   Rehash     ();

    bool   Empty      () const { return root_ == nullptr; }
    size_t Size       () const { return RSize(root_); }     // counts alive nodes
    size_t NumNodes   () const { return RNumNodes(root_); } // counts nodes
    int    Height     () const { return RHeight(root_); }

    template <class F>
    void   Inorder(F& f) const   { RInorder(root_,f); }

    template <class F>
    void   Preorder(F& f) const  { RPreorder(root_,f); }

    template <class F>
    void   Postorder(F& f) const { RPostorder(root_,f); }

    void   Display (std::ostream& os, int kw, int dw,     // key, data widths
                    std::ios_base::fmtflags kf = std::ios_base::right, // key flag
                    std::ios_base::fmtflags df = std::ios_base::right // data flag
                   ) const;

    void   DumpBW (std::ostream& os) const;
    void   Dump (std::ostream& os) const;
    void   Dump (std::ostream& os, int kw) const;
    void   Dump (std::ostream& os, int kw, char fill) const;

  private: // definitions and relationships

    enum Flags { ZERO = 0x00 , DEAD = 0x01, RED = 0x02 , LEFT_THREAD = 0x04 , RIGHT_THREAD = 0x08 ,
                 THREADS = LEFT_THREAD | RIGHT_THREAD };

    struct Node
    {
      const KeyType   key_;
            DataType  data_;
      Node * lchild_, * rchild_;
      uint8_t flags_; //  bit 1 = red/black, bit 2 = alive/dead

      Node (const KeyType& k, const DataType& d, uint8_t flags)
        : key_(k), data_(d), lchild_(nullptr), rchild_(nullptr), flags_(flags)
      {}

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
        flags &= 0x03; // last 2 bits only
        switch(flags)
        {
          case 0x00: return 'B'; // bits 00 = !RED |  ALIVE 
          case 0x01: return 'b'; // bits 01 = !RED | !ALIVE
          case 0x02: return 'R'; // bits 10 =  RED |  ALIVE
          case 0x03: return 'r'; // bits 11 =  RED | !ALIVE
          default: return 'X';   // unknown flags
        }
      }
    
      // support for color management
      bool IsRed    () const { return 0 != (RED & flags_); }
      bool IsBlack  () const { return !IsRed(); }
      bool IsDead   () const { return 0 != (DEAD & flags_); }
      bool IsAlive  () const { return !IsDead(); }
      void SetRed   ()       { flags_ |= RED; }
      void SetBlack ()       { flags_ &= ~RED; }
      void SetDead  ()       { flags_ |= DEAD; data_ = D(); }
      void SetAlive ()       { flags_ &= ~DEAD; }
      
      // support for search
      bool HasLeftChild       () const { return (lchild_ != nullptr) && !(IsLeftThreaded()); }
      bool HasRightChild      () const { return (rchild_ != nullptr) && !(IsRightThreaded()); }

      // support for threaded iterators    
      bool IsLeftThreaded     () const { return 0 != (LEFT_THREAD & flags_); }
      bool IsRightThreaded    () const { return 0 != (RIGHT_THREAD & flags_); }
      void SetLeftThread      (Node* n) { lchild_ = n; flags_ |= LEFT_THREAD; }
      void SetRightThread     (Node* n) { rchild_ = n; flags_ |= RIGHT_THREAD; }
      void SetLeftChild       (Node* n) { lchild_ = n; flags_ &= ~LEFT_THREAD; }
      void SetRightChild      (Node* n) { rchild_ = n; flags_ &= ~RIGHT_THREAD; }

      // node dump - may be used during development
      void Dump (std::ostream& os = std::cout) const
      {
        os << "  Node data:\n"
           << "    key:            " << key_  << '\n'
           << "    color:          " << (size_t)IsRed() << '\n'
           << "    alive:          " << (size_t)IsAlive() << '\n'
           << "    left_threaded:  " << (size_t)IsLeftThreaded() << '\n'
           << "    right_threaded: " << (size_t)IsRightThreaded() << '\n';
        os << "    lchild:         ";
        if (lchild_ != nullptr)
        {
          if (IsLeftThreaded())
            os << lchild_->key_  << " (predecessor)\n";
          else
            os << lchild_->key_  << " (left child)\n";
        }
        else
          os << "NULL\n";
        os << "    rchild:         ";
        if (rchild_ != nullptr)
        {
          if (IsRightThreaded())
            os << rchild_->key_  << " (succecessor)\n";
          else
            os << rchild_->key_  << " (right child)\n";
        }
        else
          os << "NULL\n";
        os << std::flush;
      }
    }; // struct Node
		
    // A PrintNode function object is passed to Inorder, facilitating Display.
    class PrintNode
    {
    public:
      PrintNode (std::ostream& os, int kw, int dw,
                 std::ios_base::fmtflags kf, std::ios_base::fmtflags df )
        : os_(os), kw_(kw), dw_(dw), kf_(kf), df_(df) {}
      void operator() (const Node * n) const
      {
        if (n->IsAlive())
        {
          os_.setf(kf_,std::ios_base::adjustfield);
          os_ << std::setw(kw_) << n->key_;
          os_.setf(df_,std::ios_base::adjustfield);
          os_ << std::setw(dw_) << n->data_;
          os_ << '\n';
        }
      }
    private:
      std::ostream& os_;
      int kw_, dw_;      // key and data column widths
      std::ios_base::fmtflags kf_, df_; // column adjustment flags for output stream
    };

  private: // data
    Node *         root_;
    PredicateType  pred_;

  private: // methods
    static Node * NewNode     (const K& k, const D& d, uint8_t flags = ZERO);
    static void   RRelease    (Node* n); // deletes all descendants of n     
    static Node * RClone      (const Node* n); // returns deep copy of n     
    static size_t RSize       (Node * n);                                    
    static size_t RNumNodes   (Node * n);               		     
    static int    RHeight     (Node * n);                                    

    template < class F >
    static void   RInorder (Node * n, F& f);

    template < class F >
    static void   RPreorder (Node * n, F& f);
   
    template < class F >
    static void   RPostorder (Node * n, F& f);
    
  }; // class OAA<>

  // proper type
  
  template < typename K , typename D , class P >
  OAA<K,D,P>::OAA  () : root_(nullptr), pred_()
  {}

  template < typename K , typename D , class P >
  OAA<K,D,P>::OAA  (P p) : root_(nullptr), pred_(p)
  {}

  template < typename K , typename D , class P >
  OAA<K,D,P>::~OAA ()
  {
    Clear();
  }

  template < typename K , typename D , class P >
  OAA<K,D,P>::OAA( const OAA& tree ) : root_(nullptr), pred_(tree.pred_)
  {
    root_ = RClone(tree.root_);
  }

  template < typename K , typename D , class P >
  OAA<K,D,P>& OAA<K,D,P>::operator=( const OAA& that )
  {
    if (this != &that)
    {
      Clear();
      this->root_ = RClone(that.root_);
    }
    return *this;
  }

  // API implementation
  template < typename K , typename D , class P >
  D& OAA<K,D,P>::Get(const KeyType& k)
  {
    if (root_ == nullptr)
    {
      root_ = NewNode(k,D());
      return root_->data_;
    }
    Node *  n = root_;    // travels down the tree
    Node *  p = nullptr;  // maintain as parent of n
    bool left = false;    // true iff n is left child of p
    while(n != nullptr)   // search loop
    {
      p = n;
      if (pred_(k,n->key_))       // k < n->key_ : go left
      {
        p = n;
        n = n->lchild_;
        left = true;
      }
      else if (pred_(n->key_,k))  // k > n->key_ : go right
      {
        p = n;
        n = n->rchild_;
        left = false;
      }
      else                        // key found
      {
        n->SetAlive();
        return n->data_;  //  return by reference - tree not modified
      }
    }
    n = NewNode(k,D());                        // create new node with key k
    (left ? p->lchild_ = n : p->rchild_ = n);  // attach n to left or right of
    return n->data_;                           // return by reference - see
  }
	
  template < typename K , typename D , class P >
  bool OAA<K,D,P>::Retrieve(const KeyType& k, DataType& d) const
  {
    Node * n = root_;
    while(n != nullptr)
    {
      if (pred_(k,n->key_))       // k < n->key_  : go left
        n = n->lchild_;
      else if (pred_(n->key_,k))  // k > n->key_  : go right
        n = n->rchild_;
      else if (n->IsAlive())      // k found alive
      {
        d = n->data_;
        return 1;
      }
      else
        return 0;
    }
    return 0;
  }
	
  template < typename K , typename D , class P >
  void OAA<K,D,P>::Erase(const KeyType& k)
  {
    Node * n = root_;
    while(n)
    {
      if (pred_(k,n->key_))       // k < n->value_ : go left
        n = n->lchild_;
      else if (pred_(n->key_,k))  // k > n->value_ : go right
        n = n->rchild_;
      else                          // k == n->value_ : found
      {
        n->SetDead();
        return;
      }
    }
  }
  
  template < typename K , typename D , class P >
  void OAA<K,D,P>::Clear()
  { 
    RRelease(root_);
    delete root_;
    root_ = nullptr;
  }
	
  template < typename K , typename D , class P >
  void OAA<K,D,P>::Rehash()
  // restructure with no tombstones
  {
    OAA<K,D,P> oaa;
    struct InsertNode
    {
      void operator()(Node * n)
      {
        if (n->IsAlive()) oaa_.Put(n->key_,n->data_);
      }
      InsertNode(OAA<K,D,P>& oaa) : oaa_(oaa)
      {}
      OAA<K,D,P>& oaa_;
    } in(oaa);
    Preorder(in);
    Clear();
    fsu::Swap(this->root_,oaa.root_);
  }

  template < typename K , typename D , class P >
  void  OAA<K,D,P>::Display (std::ostream& os, int kw, int dw, std::ios_base::fmtflags kf, std::ios_base::fmtflags df) const
  {
    PrintNode printnode(os,kw,dw,kf,df);
    Inorder (printnode);
  }

  template < typename K , typename D , class P >
  template < class F >
  void  OAA<K,D,P>::RInorder (Node * n, F& f)
  {
    if (n == nullptr) return;
    RInorder(n->lchild_, f);
    f(n);
    RInorder(n->rchild_, f);
  }

  template < typename K , typename D , class P >
  template < class F >
  void  OAA<K,D,P>:: RPreorder (Node * n, F& f)
  {
   if (n == nullptr) return;
   f(n);
   RPreorder(n->lchild_, f);
   RPreorder(n->rchild_, f);
  }

  template < typename K , typename D , class P >
  template < class F >
  void  OAA<K,D,P>:: RPostorder (Node * n, F& f)
  {
    if (n == nullptr) return;
    RPostorder(n->lchild_, f);
    RPostorder(n->rchild_, f);
    f(n);
  }

  // private static recursive methods
  template < typename K , typename D , class P >
  size_t OAA<K,D,P>::RSize(Node * n)
  {
    if (n == nullptr) return 0;
    return (size_t)(n->IsAlive()) + RSize(n->lchild_) + RSize(n->rchild_);
  }	
  
  template < typename K , typename D , class P >
  int OAA<K,D,P>::RHeight(Node * n)
  {
    if (n == nullptr) return -1;
    if (RHeight(n -> lchild_) < RHeight(n -> rchild_))
    {
      return 1 + RHeight(n -> rchild_);
    }  
    else
    {    
      return 1 + RHeight(n -> lchild_);
    }          
  }
	
  template < typename K , typename D , class P >
  size_t OAA<K,D,P>::RNumNodes(Node * n) 
  {
    if (n == nullptr) return 0;
    return 1 + RNumNodes(n->lchild_) + RNumNodes(n->rchild_);
  }	
  
  template < typename K , typename D , class P >
  void OAA<K,D,P>::RRelease(Node* n)
  {
    if (n != nullptr)
    {
      if (n->lchild_ != nullptr)
      {
        RRelease(n->lchild_);
        delete n->lchild_;
        n->lchild_ = nullptr;
      }
      if (n->rchild_ != nullptr)
      {
        RRelease(n->rchild_);
        delete n->rchild_;
        n->rchild_ = nullptr;
      }
    }
  }
		
  template < typename K , typename D , class P >
  typename OAA<K,D,P>::Node* OAA<K,D,P>::RClone(const OAA<K,D,P>::Node* n)
  // returns a pointer to a deep copy of n
  {
    if (n == nullptr)
      return nullptr;
    typename OAA<K,D,P>::Node* newN = NewNode (n->key_, n->data_, n->flags_);
    if (n->HasLeftChild())
      newN->lchild_ = OAA<K,D,P>::RClone(n->lchild_);
    else
      newN->lchild_ = nullptr;
    if (n->HasRightChild())
      newN->rchild_ = OAA<K,D,P>::RClone(n->rchild_);
    else
      newN->rchild_ = nullptr;
    return newN;
  } // end OAA<K,D,P>::RClone() */

  template < typename K , typename D , class P >
  typename OAA<K,D,P>::Node * OAA<K,D,P>::NewNode(const K& k, const D& d, uint8_t flags) 
  {
    Node * nPtr = new(std::nothrow) Node(k,d,flags);
    if (nPtr == nullptr)
    {
      std::cerr << "** OAA memory allocation failure\n";
      // handle exception in-class here
    }
    return nPtr;
  }

  // development assistants

  template < typename K , typename D , class P >
  void OAA<K,D,P>::DumpBW (std::ostream& os) const
  {
    if (root_ == nullptr)  return;

    // This is the same as "Dump(1)" except it uses a character map instead of a
    // color map for the display: B/b = black_alive/black_dead, R/r = red_alive/red_dead
    // we will use "root" as the placeholder node; test for dummy by address
    Queue < Node * , Deque < Node * > > Que;
    char nullFill = '-';
    Node * fillNode = root_;
    Node * current;
    size_t layerNumber, currLayerSize, nextLayerSize, j, k;
    layerNumber = 0;
    currLayerSize = 1;
    k = 1;  // 2^layerNumber
    Que.Push(root_);

    // execute body once for "real" root:
    os << ' '; // 1-space left margin for graphic
    nextLayerSize = 0;
    current = Que.Front();
    Que.Pop();
    os << Node::BWMap(current->flags_);
    if (current->lchild_ != nullptr)
    {
      Que.Push(current->lchild_);
      ++nextLayerSize;
    }
    else
    {
      Que.Push(fillNode);
    }
    if (current->rchild_ != nullptr)
    {
      Que.Push(current->rchild_);
      ++nextLayerSize;
    }
    else
    {
      Que.Push(fillNode);
    }
    os << '\n';

    // now finish off, using address to detect fillNode.
    while (currLayerSize > 0)
    {
      ++layerNumber;
      if (layerNumber > max_display_height)
      {
        os << " ===== DumpBW truncated at layer " << max_display_height << " =====\n";
        return;
      }
      currLayerSize = nextLayerSize;
      k *= 2;
      nextLayerSize = 0;
      os << ' '; // 1-space left margin for graphic
      for (j = 0; j < k; ++j)
      {
        current = Que.Front();
        Que.Pop();
        if (current == fillNode) // an empty position in the tree
          os << nullFill;
        else 
          os << Node::BWMap(current->flags_);
        if (current != fillNode && current->lchild_ != nullptr)
        {
          Que.Push(current->lchild_);
          ++nextLayerSize;
        }
        else
        {
          Que.Push(fillNode);
        }
        if (current != fillNode && current->rchild_ != nullptr)
        {
          Que.Push(current->rchild_);
          ++nextLayerSize;
        }
        else
        {
          Que.Push(fillNode);
        }
      } // end for
      os << '\n';
    } // end while
    Que.Clear();
  } // DumpBW(os)

  template < typename K , typename D , class P >
  void OAA<K,D,P>::Dump (std::ostream& os) const
  {
    if (root_ == nullptr) return;

    // This implementation is very like that for Dump(os, kw, fill), except that
    // there is no supplied fill object or output format character. The trick is
    // to use the root of a non-empty tree as the fill. To make that work, we have
    // to take care of the real root case before entering the main loop. 
    // we will use "root" as the placeholder node; test for dummy by address
    Queue < Node * , Deque < Node * > > Que;
    char nullFill = '-';
    char nodeFill = '*';
    Node * fillNode = root_;
    Node * current;
    size_t layerNumber, currLayerSize, nextLayerSize, j, k;
    layerNumber = 0;
    currLayerSize = 1;
    k = 1;  // 2^layerNumber
    Que.Push(root_);

    // execute body once for "real" root:
    os << ' '; // 1-space left margin for graphic
    nextLayerSize = 0;
    current = Que.Front();
    Que.Pop();
    os << Node::ColorMap(current->flags_) << nodeFill << ANSI_RESET_ALL;
    if (current->lchild_ != nullptr)
    {
      Que.Push(current->lchild_);
      ++nextLayerSize;
    }
    else
    {
      Que.Push(fillNode);
    }
    if (current->rchild_ != nullptr)
    {
      Que.Push(current->rchild_);
      ++nextLayerSize;
    }
    else
    {
      Que.Push(fillNode);
    }
    os << '\n';

    // now finish off, using address to detect fillNode.
    while (currLayerSize > 0)
    {
      ++layerNumber;
      if (layerNumber > max_display_height)
      {
        os << " ===== Dump(1) truncated at layer " << max_display_height << " =====\n";
        return;
      }
      currLayerSize = nextLayerSize;
      k *= 2;
      nextLayerSize = 0;
      os << ' '; // 1-space left margin for graphic
      for (j = 0; j < k; ++j)
      {
        current = Que.Front();
        Que.Pop();
        if (current == fillNode) // an empty position in the tree
          os << nullFill;
        else 
          os << Node::ColorMap(current->flags_) << nodeFill << ANSI_RESET_ALL;
        if (current != fillNode && current->lchild_ != nullptr)
        {
          Que.Push(current->lchild_);
          ++nextLayerSize;
        }
        else
        {
          Que.Push(fillNode);
        }
        if (current != fillNode && current->rchild_ != nullptr)
        {
          Que.Push(current->rchild_);
          ++nextLayerSize;
        }
        else
        {
          Que.Push(fillNode);
        }
      } // end for
      os << '\n';
    } // end while
    Que.Clear();
  } // Dump(os)

  template < typename K , typename D , class P >
  void OAA<K,D,P>::Dump (std::ostream& os, int kw) const
  {
    if (root_ == nullptr) return;
    Queue < Node * , Deque < Node * > > Que;
    Node * current;
    size_t currLayerSize, nextLayerSize, j;
    Que.Push(root_);
    currLayerSize = 1;
    while (!Que.Empty())
    {
      nextLayerSize = 0;
      if (kw == 1) os << ' '; // indent picture 1 space
      for (j = 0; j < currLayerSize; ++j)
      {
        current = Que.Front();
        Que.Pop();
        if (kw > 1) os << ' '; // indent each column 1 space
        os << Node::ColorMap(current->flags_) << std::setw(kw) << current->key_<< ANSI_RESET_ALL;
        if (current->lchild_ != nullptr)
        {
          Que.Push(current->lchild_);
          ++nextLayerSize;
        }
        if (current->rchild_ != nullptr)
        {
          Que.Push(current->rchild_);
          ++nextLayerSize;
        }
      }
      os << '\n';
      currLayerSize = nextLayerSize;
    } // end while
    if (currLayerSize > 0)
      std::cerr << "** OAA<K,D,P>::Dump() inconsistency\n";
  } // Dump(os, kw)

  template < typename K , typename D , class P >
  void OAA<K,D,P>::Dump (std::ostream& os, int kw, char fill) const
  {
    // fsu::debug ("Dump(3)");
    if (root_ == nullptr) return;
    Node* fillNode = NewNode(K(),D());
    Queue < Node * , Deque < Node * > > Que;
    Node * current;
    size_t layerNumber, currLayerSize, nextLayerSize, j, k;
    Que.Push(root_);
    layerNumber = 0;
    currLayerSize = 1;
    k = 1;  // 2^LayerNumber
    while (currLayerSize > 0)
    {
      ++layerNumber;
      if (layerNumber > max_display_height)
      {
        os << " ===== Dump(3) truncated at layer " << max_display_height << " =====\n";
        return;
      }
      k *= 2;
      currLayerSize = nextLayerSize;
      nextLayerSize = 0;
      if (kw == 1) os << ' '; // indent picture 1 space
      for (j = 0; j < k; ++j)
      {
        current = Que.Front();
        Que.Pop();
        if (kw > 1) os << ' '; // indent each column 1 space
        if (current == fillNode)
        {
          os <<std::setw(kw) << fill;
        }
        else
        {
          os << Node::ColorMap(current->flags_) << std::setw(kw) << current->key_<< ANSI_RESET_ALL;
        }

        if (current->lchild_ != nullptr)
        {
          Que.Push(current->lchild_);
          ++nextLayerSize;
        }
        else
        {
          Que.Push(fillNode);
        }
        if (current->rchild_ != nullptr)
        {
          Que.Push(current->rchild_);
          ++nextLayerSize;
        }
        else
        {
          Que.Push(fillNode);
        }
      }
      os << '\n';
    } // end while
    Que.Clear();
    delete fillNode;
  } // Dump(os, kw, fill) */

} // namespace fsu 

#endif

