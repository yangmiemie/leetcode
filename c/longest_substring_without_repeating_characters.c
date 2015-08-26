// Given a string, find the length of the longest substring without repeating characters. For example, the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.

#include <stdio.h>


// abcabcbb

int lengthOfLongestSubstring(char* s) {
  int Map[127] = {0};
  char *P1, *P2;
  int Length, Index;

  if (s == NULL || *s == '\0')
    return 0;

  P1 = s;
  P2 = s + 1;
  Length = 1;
  Map[*P1] = 1;

  while (*P2 != '\0')
  {
    Index = *P2;
    if (Map[Index] != 0)
    {
      while (*P1 != *P2)
      {
        Map[*P1] = 0;
        ++P1;       
      }

      ++P1;
    }
    else
    {
      Map[Index] = 1;
      
      if (P2 - P1 + 1 > Length)
        Length = P2 - P1 + 1;
    }

    ++P2;
  }

  if (P2 - P1 > Length)
    Length = P2 - P1;
  
  return Length;
}

int main(int argc, char const *argv[])
{
  char Str[] = "tmmzuxt";

  printf("%d\n", lengthOfLongestSubstring(Str));
  return 0;
}