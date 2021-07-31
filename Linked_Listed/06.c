/**************************************************************
EE2120 Data Structure
Programming Exercise #6 working template

Goals:
This program assignment is to have you practice the implementations
and operations of Stack, Queue, and Linear List using singly linked
lists.

In this program, we push each characters of your student ID into a
stack sequentially, then pop out the characters from the stack and
add into a queue. Afer that, we delete the characters from the queue
and push them into the 2nd stack. Finally, pop out the characters from
the 2nd stack and insert them into a list sequentially. At the end of
the program, the list is printed out and that would be your student ID.

Copyright (C) 2019

Wen-Yen Lin
wylin@mail.cgu.edu.tw
Department of Electrical Engineering
Chang Gung University
***************************************************************/

/*
The important part is at line 43~58
*/

// Here are the necessary header files
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// A better and safe way macro definition used in the text. Use this macro instead of 
// using "malloc" for your program.
#define MALLOC(p,s) \
if (!((p) = malloc(s))) {\
	fprintf(stderr, "Insufficient memory"); \
	exit(EXIT_FAILURE); \
}

// Declare the data structures used in this program.
// Data element
// typdef struct _ to name "element"
typedef struct {
	char c_data;
} element;

// Node structure
// Please fix the declaration sequence if there are errors during the compiling.
//self-referential structure
typedef struct node *nodePointer;
//define "struct node" data type
struct node {
	element data;
	nodePointer link;
};



// Declare a data type for the stack which contains the top pointer of the stack.
typedef struct  {
	nodePointer top;
} Stack;

// Declare a data type for the queue which contains the front and rear pointers of the stack.
typedef struct {
	nodePointer front, rear;
} Queue;

// Declare a data type for the list which contains the header pointer of the header node of the list.
typedef struct {
	nodePointer header;
} List;

// function declarations that you will implement for this program assignment
void pushS(Stack*, element); //Push an element into a Stack
element popS(Stack*); //Pop an element from a Stack
void addQ(Queue*, element); //Add and element into a Queue
element deleteQ(Queue*); //Delete and get an element from a Queue
void insertL(List, int, element); //Insert an element into i-th node of the list
void printL(List); //Print out the content of the list

void stackEmpty()
{
	printf("Stack is empty");
	return;
}
void queueEmpty() {
	printf("Queue is empty");
	return;
}


void main()
{
	//Initialize the student_ID character array as your own student ID
	//請將此student_ID字元陣列，起始成你的學生證號碼
	//for examples, char student_ID[] = "B9721200";
	char student_ID[] = "B0521229";

	//We will use one queue, two stacks and one list in this program.
	Queue queue1;
	Stack stack1, stack2;
	List list1;

	//Local variables will be used in this program. Free to add others if
	//you think you need more.
	element item;
	int id_length, i;

	//Initialized the queue1, stack1, and stack2 here.
	queue1.front = NULL;
	queue1.rear = NULL;
	stack1.top = NULL;
	stack2.top = NULL;
	//Initialized the list1 here. This list will be implemented as a linked list with header node.
	//list1.header = malloc(sizeof(struct node)); //Allocate the header node here.
	MALLOC(list1.header, sizeof(struct node));
	list1.header->link = NULL;

	id_length = strlen(student_ID); //determined the length of your student ID

	//push each character from your student ID as an element sequentially into stack1
	printf("There are %d characters in your student ID.\n", id_length);
	printf("(1) Pushing each characters from your student ID: %s into Stack - stack1....\n", student_ID);
	for (i = 0; i < id_length; i++) {
		item.c_data = student_ID[i];
		pushS(&stack1, item);
	}

	//pop out all elements from stack1 and add them into queue1 sequentially.
	printf("(2) Popping out all elements from stack1 and add them into queue1 sequentially....\n");
	printf("    The sequence of the characters in this phase are: ");
	while (stack1.top != NULL)
		addQ(&queue1, popS(&stack1));
	printf("\n");

	//delete all elements from queue1 and push them into stack2 sequentially.
	printf("(3) Deleting all elements from queue1 and push them into stack2 sequentially....\n");
	while (queue1.front != NULL)
		pushS(&stack2, deleteQ(&queue1));

	//pop out all elements from stack2 and insert them into list1 sequentially 
	//from the beginning of the list.
	printf("(4) Popping out all elements from stack2 and insert them into list1 sequentially....\n");
	i = 0;
	while (stack2.top != NULL) {
		insertL(list1, i, popS(&stack2));
		i++;
	}

	//Print out the contents of list1
	printf("(5) Print out the contents of list1....\n");
	printL(list1);
}

//Push an element, item, into a stack pointed by stackPtr
//Write your code for it here ......
void pushS(Stack* stackPtr, element item) {
	nodePointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = item;
	temp->link = stackPtr->top;
	stackPtr->top = temp;
}

//Pop and return element from a stack pointed by stackPtr
//Write your code for it here ......
element popS(Stack* stackPtr) {
	nodePointer temp = stackPtr->top;
	element item;
	if (!temp)
		stackEmpty();
	item = temp->data;
	stackPtr->top = temp->link;
	free(temp);
	return item;
}

//Add and element, item, into a queue pointed by queuePtr
//Write your code for it here ......
void addQ(Queue* queuePtr, element item) {
	nodePointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = item;
	temp->link = NULL;
	if (queuePtr->front)
		queuePtr->rear->link = temp;
	else
		queuePtr->front = temp;
	queuePtr->rear = temp;
	printf("%c", queuePtr->rear->data);
}

//Delete and return and element from a queue pointed by queuePtr
//Write your code for it here ......
element deleteQ(Queue* queuePtr) {
	nodePointer temp = queuePtr->front;
	element item;
	if (!temp)queueEmpty();
	item = temp->data;
	queuePtr->front = temp->link;
	free(temp);
	return item;
}

//Insert an element, item, into the index-th node of the list.
//Write your code for it here ......
void insertL(List list, int index, element item) {
	nodePointer temp;
	int j;
	nodePointer beforenode = list.header;
	MALLOC(temp, sizeof(*temp));
	temp->data = item;
	if (index < 0) {
		while (beforenode->link != NULL)beforenode = beforenode->link;
		temp->link = NULL;
		beforenode->link = temp;
	}
	else {
		for (j = 0; j < index; j++)beforenode = beforenode->link;
		temp->link = beforenode->link;
		beforenode->link = temp;
	}
}



//Print out all the contents in the list sequentially.
void printL(List list) {
	nodePointer currentNode;
	int nodeNumber;
	currentNode = list.header->link;
	nodeNumber = 0;
	printf("\nThe contents of the list are: ");
	while (currentNode != NULL) {
		printf("%c", currentNode->data.c_data);
		currentNode = currentNode->link;
		nodeNumber++;
	}
	printf("\n");

}