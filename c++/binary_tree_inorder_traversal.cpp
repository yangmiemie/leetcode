/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

typedef struct TreeNode* Tree;

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
      vector<TreeNode*> stack;
      vector<int> v;
      TreeNode* node;

      if (root == NULL)
        return v;

      node = root;

      while (!stack.empty() || node != NULL)
      {
        if (node != NULL)
        {
          stack.push_back(node);
          node = node -> left;
        }
        else
        {
          node = stack.back();
          stack.pop_back();
          v.push_back(node -> val);

          if (node -> right != NULL)
            node = node -> right;
          else
            node = NULL;
        }
      }
    }
};

Tree Insert(int value, Tree T)
{
  if (T == NULL)
    return new TreeNode(value);

  if (T -> val > value)
    T -> left = Insert(value, T -> left);
  else if (T -> val < value)
    T -> right = Insert(value, T -> right);

  return T;
}

void MakeEmpty(Tree T)
{
  if (T -> left)
    MakeEmpty(T -> left);

  if (T -> right)
    MakeEmpty(T -> right);

  delete(T);
}

void InOrderTraverse(Tree T)
{
  if (T == NULL)
    return;

  InOrderTraverse(T -> left);
  cout << T -> val << " ";
  InOrderTraverse(T -> right);
}

TreeNode* createTree()
{
  TreeNode* T;
  int i, Len;
  int array[] = {7, 3, 8};

  T = NULL;
  Len = sizeof(array) / sizeof(array[0]);
  for (i = 0; i < Len; ++i)
    T = Insert(array[i] % 32, T);

  return T;
}

int main(int argc, char const *argv[])
{
  TreeNode* T;
  Solution s;
  vector<int> v;

  T = createTree();
  InOrderTraverse(T);
  cout << endl;

  v = s.inorderTraversal(T);
  for (vector<int>::iterator iter = v.begin(); iter != v.end(); ++iter)
    cout << *iter << " ";
  cout << endl;

  MakeEmpty(T);
  return 0;
}