#include <stdio.h>
#include <stdlib.h>

struct Queue {
  int val;
  struct Queue* next;
  struct Queue *front, *rear;
  int size;
};
struct Queue* newnode(int k) {
  struct Queue* node = (struct Queue*)malloc(sizeof(struct Queue) * 1);
  node->val = k;
  node->next = NULL;
  return node;
}
struct Queue* createQueue() {
  struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
  q->front = q->rear = NULL;
  q->size = 0;
  return q;
}

void enqueue(struct Queue* q, int k) {
  struct Queue* node = newnode(k);
  ++q->size;
  if (q->rear == NULL) {
    q->front = q->rear = node;
    return;
  }
  q->rear->next = node;
  q->rear = q->rear->next;
}

void dequeue(struct Queue* q) {
  if (!q->front) {
    return;
  }
  --q->size;
  struct Queue* tmp = q->front;
  q->front = q->front->next;
  if (!q->front) {
    q->rear = NULL;
  }
  free(tmp);
}

int main() {
  struct Queue* q = createQueue();
  enqueue(q, 10);
  printf("%d\n", q->front);
  enqueue(q, 20);
  printf("%d\n", q->size);
  dequeue(q);
  printf("%d\n", q->size);
  dequeue(q);
  printf("%d\n", q->size);
  enqueue(q, 30);
  printf("%d\n", q->size);
  enqueue(q, 40);
  printf("%d\n", q->size);
  enqueue(q, 50);
  printf("%d\n", q->size);
  dequeue(q);
  printf("%d\n", q->size);
  printf("Queue Front : %d \n", q->front->val);
  printf("Queue Rear : %d", q->rear->val);
  return 0;
}