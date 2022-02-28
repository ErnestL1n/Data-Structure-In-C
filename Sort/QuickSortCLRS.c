#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void printarr(int[], int);
void swap(int*, int*);
void QuickSort(int[], int, int);

int main() {
  int arr[] = {12, 9, 2, 33, 1, 424, 333, -1, -111, -87};
  int n = sizeof(arr) / sizeof(int);
  printf("--------before sorting--------\n");
  printarr(arr, n);

  QuickSort(arr, 0, n - 1);

  printf("--------after sorting---------\n");
  printarr(arr, n);
  return 0;
}

int partition(int arr[], int st, int ed) {
  int pivot = arr[ed];
  int i = st - 1;
  for (int j = st; j < ed; ++j) {
    if (arr[j] < pivot) {
      ++i;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[ed]);
  return i + 1;
}

void QuickSort(int arr[], int st, int ed) {
  if (st < ed) {
    int p = partition(arr, st, ed);
    QuickSort(arr, st, p - 1);
    QuickSort(arr, p + 1, ed);
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