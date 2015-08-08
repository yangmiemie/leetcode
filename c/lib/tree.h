// struct TreeNode
// {
// 	int val;
// 	struct TreeNode* left;
// 	struct TreeNode* right;
// };

struct TreeNode {
  int val;
  struct TreeNode* left, *right, *next;
};

#define Tree struct TreeNode*
#define Position struct TreeNode*
// typedef struct TreeNode* Tree;
// typedef struct TreeNode* Position;

Tree NewNode(int value);
Tree CreateTree();
Tree Insert(int value, Tree T);
void PreOrderTraverse(Tree T);
void InOrderTraverse(Tree T);
void PostOrderTraverse(Tree T);
Position Find(Tree T, int Value);
void MakeEmpty(Tree T);

#undef Tree
#undef Position





