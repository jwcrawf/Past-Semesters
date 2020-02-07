/*
    constTest.cpp

    testing the const and non-const versions of Top
*/

#include <tstack.h>

char ShowTop(const fsu::Stack<char>& s)
{
  return s.Top();
}
// access top for reading is OK in a const environment */


// this version should work
void ChangeTop(fsu::Stack<char>& s, char newTop)
{
  s.Top() = newTop;
}
// modify top is OK in a non-const environment */

/* // this version should NOT work
void ChangeTop(const fsu::Stack<char>& s, char newTop)
{
  s.Top() = newTop;
}
// modify top is NOT OK in a const environment */


int main()
{
  fsu::Stack<char> s;
  s.Push('A');
  std::cout << ShowTop(s) << '\n';
  ChangeTop(s,'a');
  std::cout << ShowTop(s) << '\n';
  return 0;
}
