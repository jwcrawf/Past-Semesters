/*
  prime_below.cpp
  01/30/17
  Chris Lacher

  calculates the largets prime <= n
*/

#include <prime.h>

int main (int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << " ** argument required: positive integer\n";
    exit(EXIT_FAILURE);
  }
  if (!isdigit(argv[1][0]))
  {
    std::cout << " ** invalid input: argument should be a positive integer\n";
    exit(EXIT_FAILURE);
  }
  size_t n = atol(argv[1]);
  Prime p(n);
  std::cout << " PrimeBelow(" << n << ") = " << p.Largest(n) << '\n';
}
