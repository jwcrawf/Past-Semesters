/*
  bellford.h
 
  Jon Crawford
*/ 

#ifndef _BELLFORD_H
#define _BELLFORD_H

#include <wgraph.h>
#include <wgraph_util.h>
#include <vector.h>
#include <pq.h>
#include <compare.h>
#include <list.h>
#include <edge.h>
#include <queue.h>

//namespace fsu
//{
  template < class G>
  class BellmanFord
  {    

  public:

    typedef G                      Graph;
    typedef typename G::Vertex     Vertex;   
    typedef fsu::Edge<Vertex>      Edge;

    // constructor initializes all class variables in init list
    BellmanFord (const G& g): g_(g),d_(0),p_(0),onQ_(0,false),q_(),hasNegativeCycle_(false) {}

    // implementing the algorithm
    void Init(Vertex source); // preps variables for startup of algorithm
    void Exec();              // executes algorithm

    // extracting information
    const fsu::Vector<double>& Distance() const { return d_; }
    const fsu::Vector<size_t>& Parent() const { return p_; }
    void                       Path(Vertex x, fsu::List<Vertex>& path) const;
  

  private: // data
    const Graph& g_;
    fsu::Vector<double> d_;   // distance               (calculated by Exec())
    fsu::Vector<size_t> p_;   // predecessor in search  (calculated by Exec())
    fsu::Vector<bool> onQ_;
    fsu::Queue<size_t>  q_;
    
  private: // methods
    void Relax(Vertex v);    
    bool hasNegativeCycle_;
  };

  template < class G >
  void BellmanFord<G>::Init(Vertex Source)
  {    
    size_t gSize = g_.VrtxSize();    
    d_.SetSize(gSize, INFINITY);    
    p_.SetSize(gSize, gSize);      
    onQ_.SetSize(gSize, false);         
    size_t start_ = (size_t)Source;
    d_[start_] = 0.0;
    q_.Push(start_);
    onQ_[start_] = true;
    hasNegativeCycle_ = false;    
  }

  template < class G >
  void BellmanFord<G>::Exec()
  {
    Vertex v; 
    while (!q_.Empty() && !hasNegativeCycle_)
    {     
      v = q_.Front();
      q_.Pop();
      onQ_[v] = false;
      Relax(v);            
    }
  }

  template < class G >
  void BellmanFord<G>::Path(Vertex x, fsu::List<Vertex>& path) const
  {    
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
  void BellmanFord<G>::Relax(Vertex x)
  {     
    for (typename G::AdjIterator j = g_.Begin(x); j != g_.End(x); ++j)
    {
      Edge e = g_.GetEdge(x, *j);      
      if (d_[e.x_] + e.w_ < d_[e.y_])
      {
        d_[e.y_] = d_[e.x_] + e.w_;
        p_[e.y_] = e.x_;
        if (!onQ_[e.y_])     // prevents redundant inserts
        {
          q_.Push(e.y_);     // consider y for relaxation in next pass
          onQ_[e.y_] = true; // record y is on the queue
        }        
      }
    }    
  } //end relax
//} //end fsu

#endif