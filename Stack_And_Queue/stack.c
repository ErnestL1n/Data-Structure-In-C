#include <stdio.h>
#include <stdlib.h>

struct Stack {
  struct Stack *next, *top;
  int val;
  int size;
};

struct Stack* newnode(int k) {
  struct Stack* node = (struct Stack*)malloc(sizeof(struct Stack));
  node->val = k;
  node->next = NULL;
  return node;
}

struct Stack* createstack() {
  struct Stack* stk = (struct Stack*)malloc(sizeof(struct Stack));
  stk->top = NULL;
  stk->size = 0;
  return stk;
}

int empty(struct Stack* stk) { return !stk->top; }

void push(struct Stack* stk, int val) {
  struct Stack* node = newnode(val);
  ++stk->size;
  if (stk->top == NULL) {
    stk->top = node;
    return;
  }
  node->next = stk->top;
  stk->top = node;
}

void pop(struct Stack* stk) {
  if (!stk->top) {
    printf("stk is empty!!\n");
    return;
  }
  --stk->size;
  struct Stack* tmp = stk->top;
  stk->top = stk->top->next;
  free(tmp);
}

int main() {
  int value;
  int i;
  struct Stack* stk = createstack();
  printf("請依序輸入10筆資料:\n");
  for (i = 0; i < 10; i++) {
    scanf("%d", &value);
    push(stk, value);
  }
  printf("====================\n");
  while (!empty(stk)) {
    printf("堆疊彈出的順序為:%d\n", stk->top->val);
    pop(stk);
  }
  pop(stk);
  return 0;
}
