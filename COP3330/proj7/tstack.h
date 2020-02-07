/*

  tstack.h

  Jon Crawford

  12/1/2017

  Header containing declarations and template implementation for stack

*/

#ifndef _TSTACK_H
#define _TSTACK_H

#include <iostream>
#include <cstdlib>

namespace fsu
{
 
  template < typename T , size_t N = 100>
  class Stack
  {
  public:
    void     Push     (const T& t); // push t onto stack; error if full
    T        Pop      ();           // pop stack and return removed element; error if stack is empty
    T&       Top      ();           // return top element of stack; error if stack is empty
    const T& Top      () const;     // const version
    size_t   Size     () const;     // return number of elements in stack
    size_t   Capacity () const;     // return storage capacity [maximum size] of stack
    bool     Empty    () const;     // return 1/true if stack is empty, 0/false if not empty
    void     Clear    ();           // make the stack empty

    Stack             ();             // default constructor
    Stack (T fill,char ofc, int dir);
    Stack             (char ofc, int dir); // sets ofc_ and dir_
    Stack             (const Stack&); // copy constructor
    ~Stack            (){};             // destructor
    Stack& operator = (const Stack&); // assignment operator
    //display
    void     Display    (std::ostream& os) const; // output stack contents through os - depends on
                                                  // ofc_ and dir_
    void     SetOFC     (char ofc);
    void     SetDIR     (int dir);
    void     Dump       (std::ostream& os) const; // output all private data(for development use only)

  private:
    const size_t capacity_;  // = N = size of array   - fixed during life of stack
    T            data_[N];   // statically declared array of T objects - where T objects are stored
    size_t       size_;      // current size of stack - dynamic during life of stack  
    
    char    ofc_;
    int     dir_;
  }; //end Stack
  
  template < typename T , size_t N >
  std::ostream& operator << (std::ostream& os, const Stack<T, N>& s)
  {
    s.Display (os);
    return os;
  }

  template <typename T, size_t N >
  Stack<T, N>::Stack()
    : capacity_(N), data_(), size_(0), ofc_('\0'), dir_(0)
  {}
  //from discussion board
  template < typename T , size_t N > 
  Stack<T,N>::Stack (T fill, char ofc, int dir) : capacity_(N), data_(), size_(0), ofc_(ofc), dir_(dir)
  {
    if (capacity_ < 1)
    {
      std::cerr << " ** Stack capacity must be at least 1\n"
                << "    terminating execution\n";
      exit (EXIT_FAILURE);
    }
    for (size_t i = 0; i < capacity_; ++i) data_[i] = fill;
  }

  template <typename T, size_t N >
  Stack<T, N>::Stack(char ofc, int dir) : capacity_(N), data_(), size_(0) 
  {
    ofc_ = ofc;
    dir_ = dir;
  }
  
  template <typename T, size_t N >
  Stack<T, N>::Stack(const Stack& copyStack)
    : capacity_(copyStack.capacity_), data_(), size_(copyStack.size_), 
      ofc_(copyStack.ofc_), dir_(copyStack.dir_)
  {    
    for (size_t i = 0; i < copyStack.size_; ++i)
      data_[i] = copyStack.data_[i];
  }
  
  template <typename T, size_t N >
  Stack<T,N>& Stack<T, N>::operator= (const Stack& aStack)
  {
    if (&aStack != this)
    {
      size_ = aStack.size_;
      for (size_t i = 0; i < N; ++i)
        data_[i] = aStack.data_[i];
    }
    dir_ = aStack.dir_;
    ofc_ = aStack.ofc_;
    return *this;
  }

  template <typename T, size_t N >
  void Stack<T, N>::Push(const T& t)
  {
    if (size_ < capacity_)
    {  
      data_[size_] = t;
      ++size_;
    }
    else
      std::cerr << " ** Stack error: Push(" << t << ") called on full stack" << std::endl;
  }

  template <typename T, size_t N >
  bool Stack<T, N>::Empty() const
  {
    if (size_ == 0)
      return true;
    else
      return false;
  }

  template <typename T, size_t N >
  T Stack<T, N>::Pop()
  {
    T returnVal;
    if (size_ != 0)
    {  
      returnVal = data_[size_];
      --size_;
      return returnVal;
    } 
    else
    {  
      std::cerr << "** Stack error: Pop() called on Empty Stack" << std::endl;
      exit(EXIT_FAILURE);
    }  
    //return returnVal;      
  }

  template <typename T, size_t N >
  T& Stack<T, N>::Top()
  {
    if (size_ > 0)
      return data_[size_ -1];
    else
      return data_[0];
  }

  template <typename T, size_t N >
  const T& Stack<T, N>::Top() const
  {
    return data_[size_ -1];
  }

  template <typename T, size_t N >
  size_t Stack<T, N>::Size() const
  {
    return size_;
  }

  template <typename T, size_t N >
  size_t Stack<T, N>::Capacity() const
  {
    return capacity_;
  }

  template <typename T, size_t N >
  void Stack<T, N>::Clear()
  {
    size_ = 0;
  }

  template <typename T, size_t N >
  void Stack<T, N>::Display(std::ostream& os) const
  {
    if (ofc_ == '\0')
    {
      if (dir_ >= 0)
        for (size_t i = 0; i < size_; ++i)
          os << data_[i];
      else
        for (size_t i = size_; i > 0; --i)
          os << data_[i-1];
    }
    else
    {
      if (dir_ >= 0)
      {
        os << ofc_;
        for (size_t i = 0; i < size_-1; ++i)      
          os << data_[i] << ofc_;
        os << data_[size_-1];
      }  
      else
      {
        os << ofc_;
        for (size_t i = size_; i > 1; --i)
          os << data_[i-1] << ofc_;
        os << data_[0];
      }  
    }  
  }

  template<typename T, size_t N>
  void Stack<T, N>::SetOFC(char ofc)
  {
    ofc_ = ofc;
  }

  template<typename T, size_t N>
  void Stack<T, N>::SetDIR(int dir)
  {
    dir_ = dir;
  }

  template<typename T, size_t N>
  void Stack<T, N>::Dump(std::ostream & os) const
  {
    std::cout << "Stack Dump(): " << '\n'
              << "Capacity: " << N << '\n'
              << "Size:     " << size_ << '\n'
              << "Array:    " << "[";
    for (size_t i = 0; i < capacity_-1; ++i)
    {
      os << data_[i] << ",";
    }
    os << data_[capacity_-1] << "]\n";
    
    std::cout << "Stack:    " << "[";
    if (size_ > 0)
    {
      for (size_t i = 0; i < size_-1; ++i) 
      {
        os << data_[i] << ",";
      }
      os << data_[size_-1];
    }  
    std::cout << "]\n";
  }
} //end fsu

#endif
