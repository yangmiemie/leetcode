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
#include <algorithm>
using std::vector;
using std::cout;
using std::endl;

struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

typedef struct TreeNode* Tree;

struct NTreeNode 
{
  TreeNode* node;
  int isFirstVisited;
  NTreeNode(TreeNode* x): node(x), isFirstVisited(0) {}
};

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<NTreeNode*> stack;
        NTreeNode* n; 
        vector<int> v;

        if (root == NULL)
          return v;

        stack.push_back(new NTreeNode(root));

        while (!stack.empty())
        {
          n = stack.back();

          if (n -> isFirstVisited)
          {
            v.push_back(n -> node -> val);
            stack.pop_back();
          }
          else
          {
            n -> isFirstVisited = 1;

            if (n -> node -> right)
              stack.push_back(new NTreeNode(n -> node -> right));

            if (n -> node -> left)
              stack.push_back(new NTreeNode(n -> node -> left));
          }
        }

        return v;
    }

    vector<int> postorderTraversal2(TreeNode* root) {
      vector<int> v;
      vector<TreeNode*> stack;
      TreeNode* node;
      TreeNode* lastVisitNode;

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

          if (node -> right == NULL || node -> right == lastVisitNode)
          {
            lastVisitNode = node;
            v.push_back(node -> val);
            stack.pop_back();
            node = NULL;
          }
          else
          {
            node = node -> right;
          }
        }
      }

      return v;
    }

    vector<int> postorderTraversal3(TreeNode* root) {
      vector<int> v;
      vector<TreeNode*> stack;
      TreeNode* node;

      if (root == NULL)
        return v;

      stack.push_back(root);

      while (!stack.empty())
      {
        node = stack.back();
        stack.pop_back();
        v.push_back(node -> val);

        if (node -> left)
          stack.push_back(node -> left);

        if (node -> right)
          stack.push_back(node -> right);
      }

      std::reverse(v.begin(), v.end());
      return v;
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

void PostOrderTraverse(Tree T)
{
  if (T == NULL)
    return;

  PostOrderTraverse(T -> left);
  PostOrderTraverse(T -> right);
  cout << T -> val << " ";
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
  PostOrderTraverse(T);
  cout << endl;

  v = s.postorderTraversal(T);
  for (vector<int>::iterator iter = v.begin(); iter != v.end(); ++iter)
    cout << *iter << " ";
  cout << endl;
  
  v = s.postorderTraversal2(T);
  for (int i = 0; i < v.size(); ++i)
    cout << v[i] << " ";
  cout << endl;

  v = s.postorderTraversal3(T);
  for (int i = 0; i < v.size(); ++i)
    cout << v[i] << " ";
  cout << endl;

  MakeEmpty(T);
  return 0;
}