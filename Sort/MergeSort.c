#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void printarr(int[], int);
void swap(int*, int*);
void MergeSort(int[], int, int);

int main() {
  int arr[] = {12, 9, 2, 33, 1, 424, 333, -1, -111, -87};
  int n = sizeof(arr) / sizeof(int);
  printf("--------before sorting--------\n");
  printarr(arr, n);

  MergeSort(arr, 0, n - 1);

  printf("--------after sorting---------\n");
  printarr(arr, n);
  return 0;
}

void Merge(int arr[], int st, int mid, int ed) {
  // First subarray is arr[st..mid]
  // Second subarray is arr[mid+1..ed]
  int n1 = mid - st + 1, n2 = ed - mid;
  int L[n1], R[n2];
  int i, j, k;
  for (i = 0; i < n1; ++i) {
    L[i] = arr[st + i];
  }
  for (j = 0; j < n2; ++j) {
    R[j] = arr[mid + 1 + j];
  }
  i = 0;
  j = 0;
  k = st;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k++] = L[i++];
    } else {
      arr[k++] = R[j++];
    }
  }
  while (i < n1) {
    arr[k++] = L[i++];
  }
  while (j < n2) {
    arr[k++] = R[j++];
  }
}

void MergeSort(int arr[], int st, int ed) {
  if (st < ed) {
    int mid = st + (ed - st) / 2;
    MergeSort(arr, st, mid);
    MergeSort(arr, mid + 1, ed);
    Merge(arr, st, mid, ed);
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