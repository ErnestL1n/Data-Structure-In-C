#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void printarr(int[], int);
void swap(int*, int*);
void InsertionSort(int[], int);

int main() {
  int arr[] = {12, 9, 2, 33, 1, 424, 333, -1, -111, -87};
  int n = sizeof(arr) / sizeof(int);
  printf("--------before sorting--------\n");
  printarr(arr, n);

  InsertionSort(arr, n);

  printf("--------after sorting---------\n");
  printarr(arr, n);
  return 0;
}

void InsertionSort(int arr[], int n) {
  // i=0~n-1
  // j=i-1~0
  int i, j;
  for (i = 0; i < n; ++i) {
    int tmp = arr[i];
    for (j = i - 1; j >= 0 && arr[j] > tmp; --j) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = tmp;
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