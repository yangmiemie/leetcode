// Given two strings s and t, write a function to determine if t is an anagram of s.

// For example,
// s = "anagram", t = "nagaram", return true.
// s = "rat", t = "car", return false.

// Note:
// You may assume the string contains only lowercase alphabets.

#include <stdio.h>
#include <stdlib.h>

#define LEN 26

int isAnagram(char* s, char* t) {
  int i;
  int S1[26] = {0};
  int S2[26] = {0};

  if (s == NULL && t == NULL)
    return 1;

  if (s == NULL || t == NULL)
    return 0;

  while (*s != '\0' && *t != '\0')
  {
    S1[*s - 'a'] += 1;
    S2[*t - 'a'] += 1;
    ++s, ++t;
  }

  if (*s != '\0' || *t != '\0')
    return 0;

  for (i = 0; i < LEN; ++i)
  {
    if (S1[i] != S2[i])
      return 0;
  }

  return 1;
}

int main(int argc, char const *argv[])
{
  char *t = "abc";
  char *s = "bcda";

  printf("%d\n", isAnagram(s, t));
  return 0;
}