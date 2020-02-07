/*
  graph.h

  Jon Crawford

  4/3/2018

  Header file with templater implementations for proj7 Graph Search
*/

#ifndef _GRAPH_H
#define _GRAPH_H

#include <cstdlib>
#include <list.h>
#include <vector.h>

namespace fsu
{

  template < typename N >
  class ALUGraph 
  {

  public:
    typedef N                                      Vertex;
    typedef typename fsu::List<Vertex>             SetType;
    typedef typename SetType::ConstIterator        AdjIterator; 
    
    void SetVrtxSize   (N n);
    size_t VrtxSize    () const;
    void AddEdge       (Vertex from, Vertex to);
    bool HasEdge       (Vertex from, Vertex to) const;
    size_t EdgeSize    () const;
    size_t OutDegree   (Vertex v) const;
    size_t InDegree    (Vertex v) const;

    AdjIterator Begin  (Vertex v) const;
    AdjIterator End    (Vertex v) const;

    void Clear         ();
    void Dump          (std::ostream& os);

    ALUGraph           ();
    explicit ALUGraph  (N n);
  
  protected:
    fsu::Vector < SetType > al_;

  };

  template < typename N >
  class ALDGraph : public ALUGraph < N >
  {
    
  public:
    typedef N                                    Vertex;
    typedef typename ALUGraph<N>::SetType        SetType;
    typedef typename ALUGraph<N>::AdjIterator    AdjIterator;

    void AddEdge        (Vertex from, Vertex to);
    size_t EdgeSize     () const;         //Theta (|V| + |E|)
    size_t InDegree     (Vertex v) const; //Theta (|V| + |E|)
    void Reverse        (ALDGraph& d) const;

    ALDGraph            ();
    explicit ALDGraph   (N n);

  };

  //ALUGraph
  template < typename N >
  ALUGraph<N>::ALUGraph () : al_()
  {}

  template <typename N>
  ALUGraph<N>::ALUGraph (N n) : al_(n)
  {}

  template < typename N >
  void ALUGraph<N>::SetVrtxSize (N n)
  {
    al_.SetSize(n);
  }

  template < typename N >
  size_t ALUGraph<N>::VrtxSize () const
  {
    return al_.Size();
  }

  template < typename N >
  void ALUGraph<N>::AddEdge (Vertex from, Vertex to)
  {
    al_[from].Insert(to);
    al_[to].Insert(from);
  }

  template < typename N >
  bool ALUGraph<N>::HasEdge (Vertex from, Vertex to) const
  {
    AdjIterator i = al_[from].Includes(to);
    if ( i == End(from)) return 0;
    return 1;
  }

  template < typename N >
  size_t ALUGraph<N>::EdgeSize () const
  {
    size_t eSize(0);
    for (Vertex v = 0; v < al_.Size(); ++v)
      eSize += al_[v].Size();
    return eSize/2;
  }
  
  template < typename N >
  size_t ALUGraph<N>::OutDegree (Vertex v) const
  {
    return al_[v].Size();
  }
  template < typename N >  
  size_t ALUGraph<N>::InDegree (Vertex v) const
  {
    return al_[v].Size();
  }
  
  template < typename N >
  typename ALUGraph<N>::AdjIterator ALUGraph<N>::Begin (Vertex v) const 
  {
    return al_[v].Begin();
  }
  
  template <typename N >
  typename ALUGraph<N>::AdjIterator ALUGraph<N>::End (Vertex v) const 
  { 
    return al_[v].End(); 
  }


  template < typename N >
  void ALUGraph<N>::Clear ()
  {
    for(Vertex v = 0; v < al_.Size(); ++v)
      al_[v].Clear();
    al_.Clear();
  }

  template < typename N >
  void ALUGraph<N>::Dump (std::ostream& os)
  {
    AdjIterator i;
    for (Vertex v = 0; v < VrtxSize(); ++v)
    {
      os << '[' << v << "]->";
      i = this->Begin(v);
      if (i != this->End(v))
      {
        os << *i;
        ++i;
      }
      for ( ; i!= this->End(v); ++i)
        os << ',' << *i;
      os << '\n';
    }
  }

  //ALDGraph
  template < typename N >
  ALDGraph<N>::ALDGraph () : ALUGraph<N>::ALUGraph()
  {}

  template <typename N>
  ALDGraph<N>::ALDGraph (N n) : ALUGraph<N>::ALUGraph(n)
  {}

  template < typename N >
  void ALDGraph<N>::AddEdge (Vertex from, Vertex to)
  {
    this->al_[from].Insert(to);
  }

  template < typename N >
  size_t ALDGraph<N>::EdgeSize () const
  {
    size_t eSize(0);
    for (Vertex v = 0; v < ALUGraph<N>::al_.Size(); ++v)
      eSize += ALUGraph<N>::al_[v].Size();
    return eSize;
  }

  template < typename N >
  size_t ALDGraph<N>::InDegree (Vertex v) const
  {
    size_t inDegree(0);
    AdjIterator i;
    for (Vertex x = 0; x < ALUGraph<N>::VrtxSize(); ++x)
      for (i = this->Begin(x); i != this->End(x); ++i)
        if (v == *i) ++inDegree;
    return inDegree;
  }

  template < typename N >
  void ALDGraph<N>::Reverse (ALDGraph& d) const
  {
    AdjIterator i;
    d. Clear();
    d.SetVrtxSize(this->VrtxSize());
    for (Vertex v = 0; v < this->VrtxSize(); ++v)
      for (i = this->Begin(v); i != this->End(v); ++i)
        d.AddEdge(*i,v);
  }

} //end fsu

#endif
