//Author:
//https://github.com/ErnestL1n/DataStructures
//Reference:
//https://www.amazon.com/Introduction-Algorithms-3rd-MIT-Press/dp/0262033844
//https://www.geeksforgeeks.org
//https://www.amazon.com/Fundamentals-Data-Structures-Ellis-Horowitz/dp/0929306406
//environment:
//https://visualstudio.microsoft.com/zh-hant/vs/?rr=https%3A%2F%2Fwww.google.com%2F

#include<stdio.h>
#include<stdlib.h> 
#include<limits.h>



//sort items in an ascending order by default.

void swap(int*, int*);
void BubbleSort(int[], int);
void InsertionSort(int[], int);
void SelectionSort(int[], int);
void QuickSortCLRS(int[], int, int);      int Partition(int[], int, int);       
void QuickSortHoare(int[], int, int);
void MergeSort(int[], int, int);  void Merge(int[], int, int, int);
void HeapSortCLRS(int[],int);    void MaxHeapBuild(int[],int);     void MaxHeapify(int[],int,int);
void mergesortIterative(int[], int);

//an utility function to find smaller one
int minimum(int, int);


int main() {
	int a[] = {10,2,3,4,5,6,7,8,9,1};
	int n = sizeof(a) / sizeof(a[0]);
	for (int i = 0;i < n;i++)
		printf("[%d]\t", a[i]);
	printf("\n");

	//Sorting Function right here: Mind the arguments when you call the function && The array index starts from 0
	mergesortIterative(a, n);

	for (int i = 0;i < n;i++)
		printf("[%d]\t", a[i]);
}



//an utility function to swap two item
void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}



//CLRS version Quicksort 
void QuickSortCLRS(int A[], int p, int r) {
	if (p < r) {                          //Exit Condition
		int q = Partition(A, p, r);       //new pivot index created by Partition function
		QuickSortCLRS(A, p, q - 1);       //left half array
		QuickSortCLRS(A, q + 1, r);       //right half array
	}
}
int Partition(int A[], int p, int r) {  //counter variables i,j
	//save pivot=A[r] -> temp     
	int temp = A[r];
	//index of smaller element 
	int i = p - 1;
	//Loop variable to find smaller element
	for (int j = p;j < r;j++) {                 
		//if finded
		if (A[j] <= temp) {        //find all items smaller than pivot a[r]
			i++;                   //prepare to swap the smaller to the index i+1
			swap(&A[i], &A[j]);
		}
	}//ends for
	//exchange pivot with the smaller index plus 1
	swap(&A[i + 1], &A[r]);
	return ++i;
}





////Hoare version Quicksort => I like CLRS version much more Haha
void QuickSortHoare(int A[], int p, int r) {    

	//set counter variables
	int i, j;
	int pivot;

	if (p < r) {
		//set counter
		i = p;j = r + 1;
		pivot = A[p];
		//save a[i] as pivot
		do {
			//move the counter to find smaller and swap
			do i++;while (A[i] < pivot);
			do j--;while (A[j] > pivot);
			if (j > i)
				swap(&A[i], &A[j]);
		} while (j > i);
		swap(&A[p], &A[j]);
		QuickSortHoare(A, p, j - 1);
		QuickSortHoare(A, j + 1, r);
	}
}



//Merge Sort
void MergeSort(int* a, int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;           //Divide
		MergeSort(a, p, q);            //Conquer
		MergeSort(a, q + 1, r);
		Merge(a, p, q, r);             // combine
	}
}
// Merge procedure for MergeSort
void Merge(int a[], int p, int q, int r) {

	int n1 = q - p + 1;
	int n2 = r - q;

	int* L = malloc(sizeof(int) * (n1 + 1));
	int* R = malloc(sizeof(int) * (n2 + 1));

	for (int i = 0;i < n1;i++)* (L + i) = a[p + i];              //copy a[p~q]   into   L[0~n1-1]

	for (int j = 0;j < n2;j++)* (R + j) = a[q + j + 1];          //copy a[q+1~r] into   R[0~n2-1]

	*(L + n1) = INT_MAX;
	*(R + n2) = INT_MAX;


	int i = 0;int j = 0;   //initialize index



	for (int k = p;k <= r;k++) {
		if (*(L + i) <= *(R + j))
		{
			a[k] = *(L + i);
			i++;
		}
		else {
			a[k] = *(R + j);
			j++;
		}
	}
}





//Heapsort
void HeapSortCLRS(int A[],int n)
{
	MaxHeapBuild(A,n);
	for (int i =n-1;i>=0;i--) {    //array 
		swap(&A[0], &A [i]);
		MaxHeapify(A, 0, i);
	}
}
void MaxHeapBuild(int A[],int n)       //function for building maxHeap
{
	int lastparentindex = n/2-1;
	for (int i = lastparentindex;i >= 0;i--)
		MaxHeapify(A, i, n);          //Adjust from the last parent to root
}    
void MaxHeapify(int A[],int root,int n)         //function Adjusting the Heap 
{
	int largest=root;
	int leftchild = root * 2 + 1;
	int rightchild = root * 2 + 2;
	if (leftchild  < n  && A[leftchild] >= A[root])largest = leftchild;                   // size -1  because index from 0
	if (rightchild < n  && A[rightchild] >= A[largest])largest = rightchild;              // size -1  because index from 0
	if (largest != root) {
		swap(&A[root], &A[largest]);
		MaxHeapify(A, largest ,n);                          //recursively on the subtree   T(n)<=T(2/3)+O(1)  Applies Master=O(lgn)
	}
}




//Selection Sort
void SelectionSort(int A[], int n)
{
	// i=0~n-2    j=i+1~n-1
	for (int i = 0;i < n - 1;i++)
	{
		int min_index = i;
		for (int j = i + 1;j < n;j++) {
			if (A[min_index] >= A[j])
			{
				min_index = j;
			}
		}
		swap(&A[i], &A[min_index]);
	}
}




//Bubble Sort
void BubbleSort(int A[], int n)
{
	//i=0~n-2     j=n-1 downtoi+1
	for (int i = 0;i < n - 1;i++) {
		int flag = 0;
		for (int j = n - 1;j > i;j--) {
			if (A[j] < A[j - 1])
			{
				swap(&A[j], &A[j - 1]);
				flag = 1;
			}
		}if (flag == 0)break;
	}
}




//Insertion Sort
void InsertionSort(int A[], int n) {
	// i=1~n-2    j=i-1~0
	for (int i = 1;i < n;i++)
	{
		int temp = A[i];
		int j = i - 1;
		while (j >= 0 && A[j] > temp) {
			A[j + 1] = A[j];
			j--;
		}
		A[j + 1] = temp;

	}
}



int minimum(int a, int b) { return (a < b) ? a : b; }

//reference:https://www.geeksforgeeks.org/iterative-merge-sort/



void mergesortIterative(int* list,int n) {

	int curr_size;  // For current size of subarrays to be merged curr_size varies from 1 to n/2 
	int left_start; // For picking starting index of left subarray to be merged 

	//Merge subarrays in bottom up manner.  
	//First merge subarrays of size 1 to create sorted subarrays of size 2
	//then merge subarrays of size 2 to create sorted subarrays of size 4, and so on. 

	for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size)
	{
		// Pick starting point of different subarrays of current size 
		for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size)
		{
			// Find ending point of left subarray. mid+1 is starting point of right 
			int mid = minimum(left_start + curr_size - 1, n - 1);


			//Find ending point of right subarray
			int right_end = minimum(left_start + 2 * curr_size - 1, n - 1);


			// Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end] 
			Merge(list, left_start, mid, right_end);
		}
	}
}
