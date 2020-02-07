/*
  dijkstra.h
 
  Jon Crawford
*/ 

#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

#include <wgraph.h>
#include <vector.h>
#include <pq.h>
#include <compare.h>
#include <list.h>
#include <edge.h>
#include <queue.h>

//namespace fsu
//{
  template < class G>
  class Dijkstra
  {
     
  public:

    typedef G                      Graph;
    typedef typename G::Vertex     Vertex;
    typedef fsu::Edge<Vertex>      Edge;
    typedef fsu::Pair<double,Vertex>                   DV;
    typedef fsu::Vector<DV>                            Container;
    typedef fsu::GreaterThan<DV>                       Predicate;
    typedef fsu::PriorityQueue<DV,Container,Predicate> PQ;
    
    // constructor initializes all class variables in init list
    Dijkstra (const G& g) : g_(g),start_(0),c_(0),pred_(),pq_(c_,pred_),d_(0), p_(0), hasNegativeWeight_(0) {}

    // implementing the algorithm
    void Init(Vertex source); // preps variables for startup of algorithm
    void Exec();              // executes algorithm

    // extracting information
    const fsu::Vector<double>& Distance() const { return d_; }
    const fsu::Vector<size_t>& Parent() const { return p_; }
    void                       Path(Vertex x, fsu::List<Vertex>& path) const;
    

  private: // data
    const Graph& g_;
    void Relax(Vertex x);
    Vertex              start_;
    Container           c_;    // <- "input" edge set
    Predicate           pred_; // edge prioritizer
    PQ                  pq_;   // priority queue package
    fsu::Vector<double> d_; // distance
    fsu::Vector<Vertex> p_; // predecessor in search
    bool                hasNegativeWeight_;
  };

  
  template < class G >
  void Dijkstra<G>::Init(Vertex Source)
  {    
    size_t gSize = g_.VrtxSize();
    d_.SetSize(gSize, INFINITY);    
    p_.SetSize(gSize, gSize);
    start_ = (size_t)Source;
    d_[start_] = 0.0;
    pq_.Push(DV(0.0,start_);
    hasNegativeWeight_ = false;      
  }

  template < class G >
  void Dijkstra<G>::Exec()
  {
    Vertex v;        
    while (!pq_.Empty() && !hasNegativeWeight_)
    {       
      v = pq_.Front().second_;      
      pq_.Pop(); 
      Relax(v);
    }
  }

  template < class G >
  void Dijkstra<G>::Path(Vertex x, fsu::List<Vertex>& path) const
  {  
    if (hasNegativeWeight_)
    {     
      std::cout << "  distances invalid - negative weight detected";
      return;
    }    
    path.Clear();
    size_t pSize = p_.Size();
    do
    {
      path.PushFront(x);
      x = Parent()[x];
    }
    while (x < pSize);
  }

  template < class G >
  void Dijkstra<G>::Relax(Vertex v)
  //void Dijkstra<G>::Relax(Vertex x, Vertex y, double w)
  {         
    for (typename G::AdjIterator j = g_.Begin(v); j != g_.End(v); ++j)
    {
      Edge e = g_.GetEdge(v,*j);
      Vertex x = e.x_, y = e.y_;
      double w = e.w_;
      if(w < 0)
      {        
        hasNegativeWeight_ = true;
        return;
      } 
      if(d_[y] == INFINITY)
      {
        d_[y] = d_[x] + w; // estimate path distance d[y]
        p_[y] = x; // define path from s through x to y
        pq_.Push(DV(w,y));
      }
      else if (d_[x] + w < d_[y])
      {
        d_[y] = d_[x] + w;
        p_[y] = x;         
        pq_.Push(DV(w,y));     // consider y for relaxation in next pass                   
      }
    }
  }

//} //end fsu

#endif