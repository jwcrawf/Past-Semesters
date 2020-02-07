/*
  prim.h
 
  Jon Crawford
*/ 

#ifndef _PRIM_H
#define _PRIM_H

#include <wgraph.h>
#include <vector.h>
#include <pq.h>
#include <compare.h>
#include <list.h>
#include <edge.h>
#define DUMP_SIZE_THRESHOLD 64
//namespace fsu
//{
  template < class G>
  class Prim 
  {    
  public:
    
    typedef G                      Graph;
    typedef typename G::Vertex     Vertex;
    typedef fsu::Edge<Vertex>      Edge;
    typedef fsu::Vector<Edge>      Container;
    typedef fsu::GreaterThan<Edge> Predicate;
    typedef fsu::PriorityQueue<Edge,Container,Predicate> PQ;

    // constructor initializes all class variables in init list
    Prim (const G& g): g_(g),mst_(), mstw_(0.0),c_(0),pred_(),pq_(c_,pred_), gSize_(0) {}

    // implementing the algorithm
    void Init(bool verbose = 0); // preps class variables for execution of algorithm
    void Exec(bool verbose = 0); // runs algorithm

    // extracting information
    const fsu::List<Edge>& MST() const { return mst_; }
    double                 Weight() const { return mstw_; }
  
  private:
    const Graph& g_;
    fsu::List<Edge>   mst_;  // edges of MST  (calculated by Exec())
    double       mstw_; // weight of MST (calculated by Exec())
    Container    c_;    // <- "input" edge set
    Predicate    pred_; // edge prioritizer
    PQ           pq_;
    fsu::Vector<bool> inTree_; // tree vertices
    size_t gSize_;
  };

  template < class G >
  void Prim<G>::Init(bool verbose)
  {
    mst_.Clear();
    c_.Clear();
    mstw_ = 0;
    gSize_ = g_.VrtxSize();
    inTree_.SetSize(gSize_, false);   
    typename G::Vertex v = 0;
    for (typename G::AdjIterator j = g_.Begin(v); j != g_.End(v); ++j)
    {
      //if (v < *j)
        c_.PushBack(Edge(v, *j, g_.GetWeight(*j,v)));        
    }
    inTree_[0] = true;
    pq_.Init();
    if (verbose)
    {
      std::cout << "Init: Initial edges in PQ: " << pq_.Size() << '\n';
      if (pq_.Size() < DUMP_SIZE_THRESHOLD)
      {
        std::cout << "PQ.Dump():\n";
        pq_.Dump(std::cout, 2);
        std::cout << '\n';
      }
    }
  }

  template < class G >
  void Prim<G>::Exec(bool verbose)
  {    
    size_t mSize(0);
    while(mSize < gSize_ - 1)     
    { 
      //Pop edges from the priority queue until one has a vertex (say v) outside the tree
      Edge e = pq_.Front();     
      pq_.Pop();    
      if(!inTree_[e.y_])
      {
        //Add the edge to the tree, Update inTree_[v] to true        
        mst_.PushBack(e);
        ++mSize;
        mstw_ += e.w_;         
        inTree_[e.y_] = true;
        //For each edge e from v, push e onto the priority queue if the other end of e is not in the tree
        typename G::Vertex v = e.y_;
        for (typename G::AdjIterator j = g_.Begin(v); j != g_.End(v); ++j)
        {                                  
          //(these are the newly discovered edges)
          if(!inTree_[*j])
          {
            Edge e2 = g_.GetEdge(v, *j);
            pq_.Push(e2); 
          }
        }  
      }
    }
    
    if (verbose)
    {
      std::cout << "Exec: Remaining edges in PQ: " << pq_.Size() << '\n';
      if (pq_.Size() < DUMP_SIZE_THRESHOLD)
      {
        std::cout << "PQ.Dump():\n";
        pq_.Dump(std::cout, 2);
        std::cout << '\n';        
        std::cout << "PQ.PopOut():";
        pq_.PopOut(std::cout, ' ');
        std::cout << '\n';
      }
    }
  }

//} //end fsu
#endif
