/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#include <stdio.h>
#include <stdlib.h>
#include "lib/tree.h"

typedef struct TreeNode* Tree;
typedef struct TreeNode* Position;

struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
  if (nums == NULL || numsSize == 0)
    return NULL;

  int Mid;
  Tree Root;

  Mid = numsSize / 2;
  Root = NewNode(nums[Mid]);

  Root -> left = sortedArrayToBST(nums, Mid);
  Root -> right = sortedArrayToBST(nums + Mid + 1, numsSize - Mid - 1);

  return Root;
}

int main(int argc, char const *argv[])
{
  int i, Len;
  int* Array;
  Tree T;

  Len = 16;
  Array = malloc(sizeof(int) * Len);

  for (i = 0; i < Len; ++i)
    Array[i] = i;

  T = sortedArrayToBST(Array, Len);

  PreOrderTraverse(T);
  printf("\n");

  InOrderTraverse(T);
  printf("\n");

  PostOrderTraverse(T);
  printf("\n");

  return 0;
}

