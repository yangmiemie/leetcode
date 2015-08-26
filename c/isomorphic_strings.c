// Given two strings s and t, determine if they are isomorphic.

// Two strings are isomorphic if the characters in s can be replaced to get t.

// All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.

// For example,
// Given "egg", "add", return true.

// Given "foo", "bar", return false.

// Given "paper", "title", return true.

// Note:
// You may assume both s and t have the same length.

#include <stdio.h>

int checkIsmorphic(char* s, char* t)
{
	char Map[127] = {0};
	int Index;
	
	while (*s != '\0' && *t != '\0')
	{
		Index = *s;
		if (Map[Index] == 0)
			Map[Index] = *t;
		else
		{
			if (Map[Index] != *t)
				return 0;
		}

		++s, ++t;
	}

	return 1;
}

int isIsomorphic(char* s, char* t) {
	return checkIsmorphic(s, t) && checkIsmorphic(t, s);
}

int main(int argc, char const *argv[])
{
	char *s = "qwertyuiop[]asdfghjkl;'\\zxcvbnm,./";
	char *t = "',.pyfgcrl/=aoeuidhtns-\\;qjkxbmwvz";

	printf("%d\n", isIsomorphic(t, s));
	return 0;
}