struct ListNode {
  int val;
  struct ListNode *next;
};

#define Position struct ListNode* 
#define List struct ListNode* 

Position NewListNode(int Value);
void PrintList(List L);
List CreateList(int Size);
Position Find(List L, int Value);
void DestroyList(List L);

#undef Position
#undef List