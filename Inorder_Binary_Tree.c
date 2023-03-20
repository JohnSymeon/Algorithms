/*
The purpose of this program is to create a binary tree and then implement 
the inorder traversal. First, it opens a file named "data.txt"
containing integers with the first one being the total number of 
integers the file contains, and the rest being the actual values.
Then, it places the values to a binary tree constructed by struct type 
nodes and then it implements the inorder traversal algorithm.
~Ioannis Symeonidis
*/
#include <stdio.h>     
#include <stdlib.h> 

typedef struct node{ //each node has a value and two branches
	int value;
	struct node* left;
	struct node* right;
}Node;

typedef Node* Root;// typedefs to improve readability
typedef Node* Node_ptr;//

int* scan_data(char*, int*); //use to scan the file, returns the integer array and takes the array size as reference
Root create_tree(int*, int); //creates the binary tree from the data array, takes as parameter the array size
Node_ptr find_pos(Root,int); //finds the next available node for the next node to be placed under in the tree, recursive
void print_inorder(Root root);// prints the inorder traversal of the tree, recursive

int main(void)
{
	int arr_size;
	int * data =  scan_data("data.txt", &arr_size);//get the data from the file
	printf("The scanned data is:\n\n");
	int i=0;
	for(i=0;i<arr_size;i++)
		printf("%d ", data[i]);
		
	Root root = create_tree(data, arr_size);
	printf("\n\nThe inorder traversal is:\n\n");
	print_inorder(root);
	
	free(data);//free the data array from memory
}

int* scan_data(char* filename, int* arr_size)
{
	FILE* fp = fopen(filename,"r"); //open the file as read mode 
	if(fp==NULL)//check if the file exists
	{
		puts("data.txt not found! Exitting programm...");
		exit(0);	
	}
	int size;
	fscanf(fp,"%d",&size); //get the size of the array
	int *data = malloc(sizeof(int)*size);//dynamically create the array
	int element;
	int i=0;
	for(;fscanf(fp,"%d",&element)!=EOF;i++)//initialise the array with the scanned data
		data[i] = element;
	*arr_size = size;//update the size of the array
	fclose(fp);
	return data;//close the file and return the array
}

Root create_tree(int* data, int size)
{
	Root root = malloc(sizeof(Node));//initialise the root of the tree
	root->value = data[0];
	root->left = NULL;
	root->right = NULL;
	int i=0;
	for(i=1;i<size;i++)
	{
		//For every other integer in the data array, create a node,
		//find the correct position with find_pos, and then determine
		//if it should be a left or a right child and place them there.
		Node_ptr new_node = malloc(sizeof(Node));//initialise new node
		new_node->value = data[i];
		new_node->left = NULL;
		new_node->right = NULL;
		
		Node_ptr node_pointer = find_pos(root, data[i]);//look for the node parent of the new node
		
		if((node_pointer->value )>(new_node->value))//place the new node to the left
			node_pointer->left = new_node;	
		else //else to the right
			node_pointer->right = new_node;	
	}
	return root;//return the newly created tree
}

Node_ptr find_pos(Root root, int val )
{
	//look left of the current node if the value of the new node is smaller
	if((root->value)>val)
	{
		if(root->left!=NULL) //if there is another child at the left 
			find_pos((root->left),val); //call the function again with that as the parent
		else		
			return root; //or else return this node
	}
	//Or else look at the right to check if it is larger
	else if(((root)->value)<val)
	{
		if((root)->right!=NULL)//if there is another child at the right
			find_pos((root->right),val);	
		else
			return root; //or else return this node		
	}
}

void print_inorder(Root root)
{	
	//As long as there is no subtree at the left, recall the function 
	//with that node as the parent first.
	//Then, print the parent.
	//And then, check the right subtree.
	if(root->left!=NULL) 
		print_inorder(root->left);
	
	printf("%d ",root->value);
		
	if(root->right!=NULL)
		print_inorder(root->right);
}
