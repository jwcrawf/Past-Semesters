/*
  tqueue.h

  12/8/2017

  Jon Crawford

  Header containing declarations and implementations of Queue class

*/

#ifndef _TQUEUE_H
#define _TQUEUE_H
#include<iostream>

namespace fsu
{
  template<typename T>
  class Queue
  {         
  
  public:
    Queue             ();              // default constructor
    Queue             (char ofc);      // sets output formatting character
    Queue             (const Queue&);  // copy constructor
    ~Queue            ();              // destructor
    Queue& operator = (const Queue&);  // assignment operator
    void     Push     (const T& t);
    T        Pop      ();
    T&       Front    ();
    const T& Front    () const;
    size_t   Size     () const;
    bool     Empty    () const;
    void     Clear    ();
    size_t   Capacity () const;
    void     Append   (const Queue& q);
    void     Release  ();
    
    void     Display    (std::ostream& os) const; // output queue contents through os - depends on ofc
    void     SetOFC     (char ofc);         // sets output formatting character
    void     Dump       (std::ostream& os) const; // output all private data (for development use only)
  
    private:
    //char    ofc_;
    //T badReturn_;
    class Link
    {
      Link ( const T& t ) : element_(t), nextLink_(nullptr) {}  // 1-parameter Link constructor
      T      element_;
      Link * nextLink_;
      friend class Queue<T>;
    };
    Link * firstLink_;
    Link * lastLink_;
    char ofc_;
    T badReturn_;
  };
  
  template < typename T >
  std::ostream& operator << (std::ostream& os, const Queue<T>& q)
  {
    q.Display (os);
    return os;
  }
  
  template < typename T >
  Queue<T>::Queue() : firstLink_(0), lastLink_(0)
  { 
    ofc_ = '\0';
    badReturn_ = T();
  }

  template < typename T >
  Queue<T>::Queue(char ofc)
    : firstLink_(0), lastLink_(0), ofc_(ofc), badReturn_(T()) {}

  template <typename T>
  Queue<T>::Queue(const Queue& q) : firstLink_(0), lastLink_(0)
  {
    if (!q.Empty())
    {
      Append(q);
      ofc_ = q.ofc_;
    }  
    else
      return;
  }

  template < typename T>
  Queue<T>::~Queue()
  {
    Release();
  }
  
  template < typename T>
  Queue<T>& Queue<T>::operator=( const Queue& rhs )
  {
    if (this != &rhs && !rhs.Empty())
    {
      this->Clear();
      this->Append(rhs);
      this->ofc_= rhs.ofc_; 
    }
    return *this;
  }

  template < typename T >
  void Queue<T>::Push (const T& t)
  {
    Queue<T>::Link * midLink = new Link(t);
    if(!Empty())
    {
      lastLink_->nextLink_ = midLink;
      lastLink_ = midLink;
    }
    else
    {
      lastLink_ = midLink;
      firstLink_ = midLink;
    }
  }

  template <typename T>
  T Queue<T>::Pop()
  {
    
    if (!Empty())
    {
      Queue::Link * tempLink = firstLink_;
      if (firstLink_ == lastLink_)
      {           
        firstLink_ = 0;
        lastLink_= 0;
      }  
      else
      {  
        firstLink_ = firstLink_->nextLink_;      
      } 
      T qVal = tempLink->element_;
      delete tempLink;
      return qVal;
    }
     
    else
    {
      std::cerr << "** Queue error: 'Pop()' called on Empty Queue\n";
      return badReturn_;
    }  
  }

  template < typename T >
  T& Queue<T>::Front()
  {
    if (!Empty())
    {
      return firstLink_->element_;
    }
    else
    {
      std::cerr << "** Queue error: 'Front()' called on Empty Queue\n";
      return badReturn_;
    }
  }

  template < typename T >
  const T& Queue<T>::Front() const
  {
    if (!Empty())
    {
      return firstLink_->element_;
    }
    else
    {
      std::cerr << "** Queue error: 'Front()' called on Empty Queue\n";
      return badReturn_;
    }
  }  
    
  template < typename T >
  size_t Queue<T>::Size() const
  {
    size_t size = 0;
    Queue<T>::Link* countLink = firstLink_;
    while (countLink != 0)
    {
      countLink = countLink->nextLink_;
      ++size;
    }
    return size;
  }

  template < typename T >
  bool Queue<T>::Empty() const
  {
    if (firstLink_ == 0)
      return true;
    else
      return false;
  }

  template < typename T >
  void Queue<T>::Clear() { Release(); }

  template < typename T >
  size_t Queue<T>::Capacity () const { return Size(); }

  template < typename T >
  void Queue<T>::Append (const Queue& appQ)
  {
    Queue<T>::Link* currentLink = appQ.firstLink_;
    T value = currentLink->element_;
    Queue<T>::Link* newLink = new Link(value);
    firstLink_ = lastLink_ = newLink;
    currentLink = currentLink->nextLink_;
    while (currentLink != 0)
    {
      T value = currentLink->element_;
      Queue<T>::Link* newLink = new Link(value);
      lastLink_->nextLink_ = newLink;
      lastLink_ = newLink;
      currentLink = currentLink->nextLink_;
    }
  }  

  template < typename T >
  void Queue<T>::Release ()
  {
    if (!Empty())
    {
      Queue<T>::Link* countLink = firstLink_;
      Queue<T>::Link* tempLink;
      
      while (countLink != 0)
      {
        tempLink = countLink;
        countLink = countLink->nextLink_;
        delete tempLink;
      }
    }
    lastLink_ = 0;
    firstLink_ = 0;
  }

  template < typename T >
  void Queue<T>::Display (std::ostream& os) const
  {
    if (!Empty())
      {
      Queue<T>::Link* countLink = firstLink_;
      if (ofc_ == '\0')
      {
        while (countLink != 0)
        {
          os << countLink->element_;
          countLink = countLink->nextLink_;
        }
      }
      else
      {
        while (countLink != 0)
        {
          os << ofc_ << countLink->element_;
          countLink = countLink->nextLink_;
        }
      }
    }
    else
    return;
  }// end Display

  template < typename T >
  void Queue<T>::SetOFC (char ofc) { ofc_ = ofc; }

  template < typename T >
  void Queue<T>::Dump (std::ostream& os) const { Display(os); }
  
}// end fsu
#endif
