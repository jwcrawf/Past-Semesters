/* 
	compare_spy.h
	
	Jon Crawford
	
	1/30/2018
	
	header with template for LessThanSpy
*/

#ifndef COMPARE_SPY_H
#define COMPARE_SPY_H

namespace fsu
{
  template <typename T>
  class LessThanSpy
  {
  public:
  LessThanSpy() : count_(0) {}
  bool operator()(const T &t1, const T &t2)
  {
    ++count_;
    return (t1 < t2);
  }
  void Reset() { count_ = 0; }
  
	size_t Count() const { return count_; }

  private:
  size_t count_;
  };
}

#endif