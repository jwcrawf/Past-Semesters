/*
    constTest.cpp

    testing the const and non-const versions of Top and Front 
*/

#include <tstack.h>
#include <tqueue.h>


// const environment, read access
char ShowTop(const fsu::Stack<char>& s)
{
  return s.Top();
}
char ShowFront(const fsu::Queue<char>& s)                                                      
{
  return s.Front();
}
// read-only accesses work in a const environment should work */

// non-const environment, write access
void ChangeTop(fsu::Stack<char>& s, char newTop)
{
  s.Top() = newTop;
}
void ChangeFront(fsu::Queue<char>& s, char newFront)
{
  s.Front() = newFront;
}
// write access in a non-const environment should work */

/* // const environment, write access
void ChangeTop(const fsu::Stack<char>& s, char newTop)
{
  s.Top() = newTop;
}
void ChangeFront(const fsu::Queue<char>& s, char newFront)
{
  s.Front() = newFront;
}
// write access in a const environment should not compile */


int main()
{
  fsu::Stack<char> s;
  fsu::Queue<char> q;
  s.Push('A');
  q.Push('B');
  std::cout << ShowTop(s)<< ' ' << ShowFront(q) << '\n';
  ChangeTop(s,'a');
  ChangeFront(q,'b');
  std::cout << ShowTop(s)<< ' ' << ShowFront(q) << '\n';
  return 0;
}
