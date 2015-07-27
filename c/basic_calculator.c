// Implement a basic calculator to evaluate a simple expression string.

// The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .

// You may assume that the given expression is always valid.

// Some examples:
// "1 + 1" = 2
// " 2-1 + 2 " = 3
// "(1+(4+5+2)-3)+(6+8)" = 23

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ElementType int
#define SIZE 8
#define Parenthesis -1
#define Minus -2
#define Plus -3
#define IsDigit(x) ((x) >= '0' && (x) <= '9')
#define IsOp(x) ((x) == '+' || (x) == '-')
#define IsLeftParen(x) ((x) == '(')
#define IsRightParen(x) ((x) == ')')
#define IsSpace(x) ((x) == ' ')

struct Stack
{
  int Size;
  int Capacity;
  ElementType* Next;
};

typedef struct Stack* Stack;

Stack Initialize()
{
  Stack S;

  S = malloc(sizeof(struct Stack));
  S -> Next = malloc(sizeof(ElementType) * SIZE);
  S -> Size = 0;
  S -> Capacity = SIZE;

  return S; 
}

int IsEmpty(Stack S)
{
  return S -> Size == 0;
}

int IsFull(Stack S)
{
  return S -> Size == S -> Capacity;
}

void Destroy(Stack S)
{
  free(S -> Next);
  free(S);
}

void Push(Stack S, ElementType Value)
{
  if (IsFull(S))
  {
    S -> Next = realloc(S -> Next, sizeof(ElementType) * 2 * S -> Capacity);
    S -> Capacity *= 2;
  }

  S -> Next[S -> Size++] = Value;
}

ElementType Pop(Stack S)
{
  if (IsEmpty(S))
  {
    printf("Empty Stack\n");
    exit(1);
  }

  return S -> Next[--S -> Size];
}

ElementType Top(Stack S)
{
  if (IsEmpty(S))
  {
    printf("Empty Stack\n");
    exit(1);
  }

  return S -> Next[S -> Size - 1];
}

int Evaluate(int Op1, int Op2, char Op)
{
  if (Op == '+')
    return Op1 + Op2;
  else if (Op == '-')
    return Op1 - Op2;
}

void PushDigitToStack(Stack S, int Value)
{
  int X, Op1, Op2, Operator;

  while (1)
  {
    if (IsEmpty(S))
    {
      Push(S, Value);
      break;
    }
    else
    {
      X = Top(S);

      if (X == Plus || X == Minus)        
      {
        Op2 = Value;
        Operator = Pop(S) == Plus ? '+' : '-';
        Op1 = Pop(S);
        Value = Evaluate(Op1, Op2, Operator);
      }
      else
      {
        Push(S, Value);
        break;
      }
    }
  }
}

int SubStringToInt(char* pBegin, char* pEnd)
{
  int i = 0;

  while(pBegin != pEnd)
  {
    i = i * 10 + *pBegin - '0';
    ++pBegin;
  }

  return i;
}

int calculate(char* s) {
    char* Ptr, *Targets, *Parenthesises, *PtrParen, *PtrTarget, *Numbers; 
    char* PtrEnd;
    char Operator;
    int Op1, Op2, Value;
    Stack S;

    Ptr = s;
    Targets = "0123456789()";
    Numbers = "0123456789";
    S = Initialize();

    while(*Ptr != '\0')
    {
      if (IsDigit(*Ptr))
      {
        PtrEnd = Ptr + 1 + strspn(Ptr + 1, Numbers);
        Value = SubStringToInt(Ptr, PtrEnd);
        PushDigitToStack(S, Value);
        Ptr = PtrEnd;
        continue;
      }
      else if (IsOp(*Ptr))
      {
        PtrTarget = strpbrk(Ptr + 1, Targets);

        if (IsDigit(*PtrTarget))
        {
          Op1 = Pop(S);
          Operator = *Ptr;
  
          PtrEnd = PtrTarget + 1 + strspn(PtrTarget + 1, Numbers);
          Value = SubStringToInt(PtrTarget, PtrEnd);
          Ptr = PtrEnd;
          Op2 = Value;
          Push(S, Evaluate(Op1, Op2, Operator));
          continue;
        }
        else
        {
          if (*Ptr == '+')
            Push(S, Plus);
          else if (*Ptr == '-')
            Push(S, Minus);

          Ptr = PtrTarget;
          Push(S, Parenthesis);
        }
      }
      else if (IsSpace(*Ptr))
      {
      }
      else if (IsLeftParen(*Ptr))
      {
        Push(S, Parenthesis);
      }
      else if (IsRightParen(*Ptr))
      {
        // Get digit from stack
        Value = Pop(S);
        // Pop left parenthesis
        Pop(S);
        // Push digit back to stack
        PushDigitToStack(S, Value);
      }

      ++Ptr;
    }

    if (S -> Size != 1)
    {
      fprintf(stderr, "Error Expression\n");
      exit(1);
    }

    Value = Pop(S);
    Destroy(S);
    return Value;
}

int main(int argc, char const *argv[])
{
  // "1 + 1" = 2
  // " 2-1 + 2 " = 3
  // "(1+(4+5+2)-3)+(6+8)" = 23

  char *Expression1 = "1 + 1";
  char *Expression2 = " 2-1 + 2 ";
  char *Expression3 = "(1+(4+5+2)-3)+(6+8)";
  char *Expression4 = "2147483647";
  char *Expression5 = "1-11";

  int Result;

  Result = calculate(Expression1);
  printf("%d\n", Result);

  Result = calculate(Expression2);
  printf("%d\n", Result);

  Result = calculate(Expression3);
  printf("%d\n", Result);

  Result = calculate(Expression4);
  printf("%d\n", Result);

  Result = calculate(Expression5);
  printf("%d\n", Result);
  return 0;
}