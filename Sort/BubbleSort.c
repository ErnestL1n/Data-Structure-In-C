#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void printarr(int[], int);
void swap(int*, int*);
void BubbleSort(int[], int);

int main() {
  int arr[] = {12, 9, 2, 33, 1, 424, 333, -1, -111, -87};
  int n = sizeof(arr) / sizeof(int);
  printf("--------before sorting--------\n");
  printarr(arr, n);

  BubbleSort(arr, n);

  printf("--------after sorting---------\n");
  printarr(arr, n);
  return 0;
}

void BubbleSort(int arr[], int n) {
  // i=0~n-1
  // j=0~n-i-1
  for (int i = 0; i < n; ++i) {
    int flag = 0;
    for (int j = 0; j < n - i - 1; ++j) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
        flag = 1;
      }
    }
    // sorted
    if (flag == 0) {
      break;
    }
  }
}

void swap(int* a, int* b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void printarr(int arr[], int n) {
  for (int i = 0; i < n; ++i) {
    printf("[%d] ", arr[i]);
  }
  printf("\n");
}