/*
  wgraph.h
 
  Jon Crawford
*/ 

#ifndef _WGRAPH_H
#define _WGRAPH_H

#include <graph.h>
#include <iostream>
#include <vector.h>
#include <list.h>
#include <edge.h>
#include <hashtbl.h>
#include <hashclasses.h>
#include <xstring.h>
#include <tostring.h>
#include <xstring.cpp>
#include <primes.h>
#include <primes.cpp>
#include <bitvect.h>
#include <bitvect.cpp>
#include <hashfunctions.cpp>
#include <wgraph_util.h>

namespace fsu
{
  template < typename N >                           
  class ALUWGraph : public ALUGraph <N>
  {
  public:
    typedef N                                      Vertex;
    typedef typename ALUGraph<N>::SetType          SetType;    
    typedef typename SetType::ConstIterator        AdjIterator;
    typedef fsu::Edge<Vertex> Edge;
    
    typedef fsu::HashTable<fsu::String, double , hashclass::KISS <fsu::String> > AA;

    void     SetVrtxSize  (N n);
    //size_t   VrtxSize     () const;
    void     Check        (std::ostream& os);
    void     AddEdge      (Vertex from, Vertex to, double weight = 1.0);
    bool     HasEdge      (Vertex from, Vertex to, double& wt) const; // sets wt variable if edge exists
    Edge     GetEdge      (Vertex from, Vertex to) const;             // returns [0,0,0.0] if edge does not exist
    void     SetWeight    (Vertex from, Vertex to, double weight);    // (re)sets weight
    double   GetWeight    (Vertex from, Vertex to) const;   
                  // returns weight if edge exists, 0.0 otherwise
    void     Dump         (std::ostream& os);
    void     Clear        ();
    size_t   MapSize      () const { return size_;}
    //size_t   EdgeSize     () const;
    //size_t   OutDegree    (Vertex v) const;    // same as Degree for undirected case
    //size_t   InDegree     (Vertex v) const;    // same is OutDegree for undirected case
    
    //AdjIterator Begin     (Vertex v) const;
    //AdjIterator End       (Vertex v) const;
    ALUWGraph();
    explicit ALUWGraph(N n);
    
  protected:
    AA        weight_;

  private:
    static fsu::String Key ( Vertex x , Vertex y )
    {
      // improved private function from the discussion board
      fsu::String key = x < y ? fsu::ToHex(x) + "." + fsu::ToHex(y) : fsu::ToHex(y) + "." + fsu::ToHex(x);
      //fsu::String key = fsu::ToHex(x) + "." + fsu::ToHex(y);
      return key;
    }   
     size_t size_;
  };


  template < typename N >                             
  class ALDWGraph : public ALDGraph <N>
  {
  public:
    typedef N                                      Vertex;
    typedef typename ALUGraph<N>::SetType          SetType;    
    typedef typename SetType::ConstIterator        AdjIterator;    
    typedef fsu::Edge<Vertex> Edge;
    typedef fsu::HashTable<fsu::String, double , hashclass::KISS <fsu::String> > AA;

    // need to decide which of these can be inherited from above
    void     SetVrtxSize  (N n);
    //size_t   VrtxSize     () const;
    void     Check        (std::ostream& os);
    void     AddEdge      (Vertex from, Vertex to, double weight = 1.0);
    bool     HasEdge      (Vertex from, Vertex to, double& wt) const; // sets wt variable if edge exists
    Edge     GetEdge      (Vertex from, Vertex to) const;             // returns [0,0,0.0] if edge does not exist
    void     SetWeight    (Vertex from, Vertex to, double weight);    // (re)sets weight
    double   GetWeight    (Vertex from, Vertex to) const;  
               // returns weight if edge exists, 0.0 otherwise
    void     Dump         (std::ostream& os);
    void     Clear        ();
    void     Reverse      (ALDWGraph& d) const;
    size_t   MapSize      () const { return size_;}
   // size_t   EdgeSize     () const;
    //size_t   OutDegree    (Vertex v) const;    // same as Degree for directed case
    //size_t   InDegree     (Vertex v) const;    // same is OutDegree for directed case
    
   // AdjIterator Begin     (Vertex v) const;
    //AdjIterator End       (Vertex v) const;

    ALDWGraph();
    explicit ALDWGraph(N n);

  protected:
    AA        weight_;
    
  private:
    static fsu::String Key ( Vertex x , Vertex y )
    {
      // improved private function from the discussion board
      fsu::String key = fsu::ToHex(x) + "." + fsu::ToHex(y);
      //fsu::String key = x < y ? fsu::ToHex(x) + "." + fsu::ToHex(y) : fsu::ToHex(y) + "." + fsu::ToHex(x);
      return key;
    }
    size_t size_;     
  };

  template < typename N >
  ALDWGraph<N>::ALDWGraph () : weight_(0, 1), size_(0){}

  template < typename N >
  ALDWGraph<N>::ALDWGraph ( N n ) : weight_(n, 1), size_(0){}

  template < typename N >
  ALUWGraph<N>::ALUWGraph () : weight_(0, 1), size_(0) {}

  template < typename N >
  ALUWGraph<N>::ALUWGraph ( N n ) : weight_(n, 1), size_(0){}

  template < typename N >
  void ALDWGraph<N>::SetVrtxSize (N n)
  {
    ALUGraph<N>::al_.SetSize((size_t)n);
    weight_.Rehash((size_t)n);    
    size_ = n;
  }

  template < typename N >
  void ALUWGraph<N>::SetVrtxSize (N n)
  {
    ALUGraph<N>::al_.SetSize((size_t)n);
    weight_.Rehash((size_t)n);
    size_ = n;
  }

  template < typename N >
  void ALDWGraph<N>::Check (std::ostream& os)
  {    
    weight_.Analysis(os);    
  }

  template < typename N >
  void ALUWGraph<N>::Check (std::ostream& os)
  {   
    weight_.Analysis(os);    
  }  

  template < typename N >
  void ALDWGraph<N>::AddEdge (Vertex from, Vertex to, double weight)
  {
    if (from == to) return;
    ALUGraph<N>::al_[(size_t)from].Insert(to);    
    weight_.Put(Key(from,to), weight);
    ++size_;
    if (size_ > 2 * weight_.NumBuckets())
      weight_.Rehash(size_);
  }

  template < typename N >
  void ALUWGraph<N>::AddEdge (Vertex from, Vertex to, double weight)
  {
    if (from == to) return; 
    AA::ConstIterator i = weight_.Includes(Key(from, to));     
    if(i == weight_.End())
    {
      ALUGraph<N>::al_[(size_t)from].Insert(to);
      ALUGraph<N>::al_[(size_t)to].Insert(from);
      weight_.Put(Key(from,to), weight);    
      ++size_;               
      if (size_ >  2 * weight_.NumBuckets())
        weight_.Rehash(size_);      
    }        
  }
  
  template < typename N >
  Edge<N> ALUWGraph<N>::GetEdge(Vertex from, Vertex to) const
  {  
    AA::ConstIterator i = weight_.Includes(Key(from, to));
    if (i != weight_.End())     
      return Edge(from, to, (*i).data_); 
    return Edge(0, 0, 0.0);
  }

  template < typename N >
  Edge<N> ALDWGraph<N>::GetEdge(Vertex from, Vertex to) const
  {    
    AA::ConstIterator i = weight_.Includes(Key(from, to));
    if (i != weight_.End())     
      return Edge(from, to, (*i).data_); 
    return Edge(0, 0, 0.0);
  }

  template < typename N >
  double ALUWGraph<N>::GetWeight (Vertex from, Vertex to) const
  {
    AA::ConstIterator i = weight_.Includes(Key(from, to));
    if (i != weight_.End())     
      return (*i).data_;    
    return 0.0;
  }

  template < typename N >
  double ALDWGraph<N>::GetWeight (Vertex from, Vertex to) const
  {
    AA::ConstIterator i = weight_.Includes(Key(from, to));
    if (i != weight_.End())     
      return (*i).data_;    
    return 0.0;
  }

  template < typename N >
  void ALUWGraph<N>::SetWeight (Vertex from, Vertex to, double weight)
  {
    if(!HasEdge(from, to , weight))
      std::cerr << "Cannot set weight, edge doesn't exist..\n";
    else
      weight_[Key(from, to)] = weight;
  }

  template < typename N >
  void ALDWGraph<N>::SetWeight (Vertex from, Vertex to, double weight)
  {
    if(!HasEdge(from, to , weight))
      std::cerr << "Cannot set weight, edge doesn't exist..\n";
    else
      weight_[Key(from, to)] = weight;
  }

  template < typename N >
  bool ALUWGraph<N>::HasEdge (Vertex from, Vertex to, double& wt) const
  {
    AA::ConstIterator i = weight_.Includes(Key(from, to));
    if (i != weight_.End())     
      wt = (*i).data_;
    return false; 
  }
  
  template < typename N >
  bool ALDWGraph<N>::HasEdge (Vertex from, Vertex to, double& wt) const
  {
    AA::ConstIterator i = weight_.Includes(Key(from, to));
    if (i != weight_.End())     
      wt = (*i).data_; 
    return false;         
  }

  template < typename N >
  void ALUWGraph<N>::Clear()
  {
    weight_.Clear();
    size_ = 0;
    for (Vertex v = 0; v < ALUGraph<N>::VrtxSize(); ++v) 
      ALUGraph<N>::al_[v].Clear();
    ALUGraph<N>::al_.SetSize(0);
  }

  template < typename N >
  void ALDWGraph<N>::Clear()
  {
    weight_.Clear(); 
    size_ = 0;  
    for (Vertex v = 0; v < ALUGraph<N>::VrtxSize(); ++v) 
      ALUGraph<N>::al_[v].Clear();
    ALUGraph<N>::al_.SetSize(0);
  }

  template < typename N >
  void ALDWGraph<N>::Reverse(ALDWGraph& d) const
  {        
    d.Clear();
    d.SetVrtxSize(this->VrtxSize());    
    for (Vertex v = 0; v < this->VrtxSize(); ++v)
    {
      for (AdjIterator i = this->Begin(v); i != this->End(v); ++i)      
        d.AddEdge(*i, v, GetWeight(v ,*i));   
    } 
    return;
  }

  template < typename N >
  void ALUWGraph<N>::Dump (std::ostream& os)
  {
    AdjIterator i;
    for (Vertex v = 0; v < ALUGraph<N>::VrtxSize(); ++v)
    {
      os << '[' << v << "]->";
      i = this->Begin(v);
      if (i != this->End(v))
      {
	      os << '(' << v << ',' << *i << ')'
           <<"w=" << GetWeight(v, *i);
	      ++i;
      }
      for ( ; i != this->End(v); ++i)
      {
	      os << ',' << '(' << v << ',' << *i << ')'
           <<"w=" << GetWeight(v, *i);
      }
      os << '\n';
    }
  }

  template < typename N >
  void ALDWGraph<N>::Dump (std::ostream& os)
  {
    AdjIterator i;
    for (Vertex v = 0; v < ALUGraph<N>::VrtxSize(); ++v)
    {
      os << '[' << v << "]->";
      i = this->Begin(v);
      if (i != this->End(v))
      {
	      os << '(' << v << ',' << *i << ')'
           <<"w=" << GetWeight(v, *i);
	      ++i;
      }
      for ( ; i != this->End(v); ++i)
      {
	      os << ',' << '(' << v << ',' << *i << ')'
           <<"w=" << GetWeight(v, *i);
      }
      os << '\n';
    }
  }
} // namespace fsu
#endif
