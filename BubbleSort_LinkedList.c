/*
This program creates a singly linked list composed of nodes with random positive integer values,
and then implements the bubble sort algorithm with recursion to sort the list
from the smallest element to the largest.
~Ioannis Symeonidis
*/
#include <stdio.h>     
#include <stdlib.h> 
#include <time.h>
#define N 100
//N is the number of elements of the list and the range of the randomly 
//generated integers

typedef struct node{ //Our basic node
	int data;
	struct node* next;
}Node;

typedef Node* List;  //typedefs to improve readability
typedef Node* Node_ptr; //

List Generate_List(); //Used to generate the random list
void Create_Node(List*,int); //Used to create a node at the end of the list or the head if it is empty
void Sort_List(List*,int); //Implements the bubble sort on the list
void Print_List(List *); //Print the list from the head to the last node

int main(void)
{
	List mylist = Generate_List();
	puts("\nBefore Sorting");
	Print_List(&mylist);
	puts("\n\n\nAfter Sorting");
	Sort_List(&mylist,N); //Sort
	Print_List(&mylist);
	
}

List Generate_List()
{
	srand(time(0));
	int element;
	int i;
	List myList = NULL;
	for(i=0;i<N;i++) //Create as many nodes for as many elements are needed
	{
		element = rand()%N; //randomly generate an integer
		Create_Node(&myList,element);
	}
	return myList;
}
void Create_Node(List* head,int d)
{
	Node_ptr new_node= malloc(sizeof(Node));//initialise the new node on the heap
	new_node->data = d;
	new_node->next = NULL;
	if((*head)==NULL) //check if the list is empty
		(*head) = new_node;
	else //else append the new node at the end
	{
		Node_ptr temp = (*head);
		while(temp->next!=NULL)
		{
			temp= temp->next;
		}
		temp->next = new_node;
	}
}
void Sort_List(List* list,int size)
{
	Node_ptr temp = (*list);
	List temp_head = (*list);//save the head of the list
	int i=0;
	if(size==0) //if the function has ran for N times, stop the recursion
		return;
	for(i=0;i<size-1;i++) 
	{
		//If an element is bigger than its next, swap the values.
		//Then move to the next pair, up until i reaches size-1.
		//Every time the function runs, the biggest value bubbles
		//at the front of the current active part of the list.
		//This occurs up until the active part becomes as small as one element.
		if( ( temp->data ) > ( (temp->next)->data )  )
			{
				int k = temp->data;
				(temp->data) = ( (temp->next)->data );
				(temp->next)->data = k;
			}
		temp = temp->next;
	}
	Sort_List(&temp_head,size-1);
	
}
void Print_List(List * list)
{
	Node_ptr temp = (*list);
	int counter=0;
	//print all nodes up untl temp points to NULL
	while(temp!=NULL)
	{
		if(counter%5==0) //change lines every 5 nodes
			puts("\n");
		printf("(%2d)-->", temp->data);
		temp= temp->next;
		counter++;
	}
}
