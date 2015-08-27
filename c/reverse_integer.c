// Reverse digits of an integer.

// Example1: x = 123, return 321
// Example2: x = -123, return -321

#include <stdio.h>
#include <limits.h>

int reverse(int x) {
  if (x == 0)
    return 0;

  int Positive;
  long Value;

  Positive = 1;
  Value = 0;

  if (x < 0)
  {
    Positive = -1;
    x = x * -1;
  }

  while (x > 0)
  {
    Value = Value * 10 + x % 10;
    x /= 10;

    if (Value > INT_MAX)
      return 0;
  }

  return (int)Positive * Value;
}

int main(int argc, char const *argv[])
{
  int N;

  N = 32;
  printf("%d\n", reverse(N));
  printf("%d\n", INT_MAX);
  return 0;
}