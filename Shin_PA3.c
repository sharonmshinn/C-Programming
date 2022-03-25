#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


	FILE* file;
	int nums[100];
	int count = 0;
	int front = -1;
	int back = -1;
	
	/**
	This struct defines a node for a binary tree with an integer data,
	struct Node pointers left and right child and a Node pointer parent.
	**/
	typedef struct Node
	{
		int data;
		struct Node* left;
		struct Node* right;
		struct Node* parent;
	}Node;
	
	/**
	This method is used for the queue data structure, however we are passing
	an array of Node* instead while keeping track of the front of the queue 
	and back of the queue and the Node* we want to add to the queue.
	**/
	void enqueue(Node* q[], Node* node)
	{
		//if front indicates we have an empty queue, move the front to the first index
		if (front == -1){
			front = 0;
			//add first node to first index in array
			q[front] = node;
			//update back to one more than before
			back += 1;
		//if our queue is not empty, add one to back and add node to that index
		} else {
			back += 1;
			q[back] = node;
		}
	}
	
	/**
	This method takes in an array of Nodes that represents our queue,
	and moves the front of the queue to be one higher index than before,
	getting rid of our front Node.
	**/
	void dequeue(Node* q[])
	{
		front += 1;
	}
	
	/**
	This method returns a Node pointer and takes in an array of Nodes that
	represents our queue. It simply returns the Node object that is at the 
	front of the queue, but does not remove it.
	**/
	Node* getFront(Node* q[])
	{
		return q[front];
	}
	
	/**
	This method is used to reset the global variables of front and back of 
	both the queue and stack.
	**/
	void reset()
	{
		front = -1;
		back = -1;
	}
	
	/**
	Returns a boolean int value if the queue is empty by comparing if the
	front index is bigger than the back, meaning everything in the queue 
	has been dequeued.
	**/
	int isEmptyQueue()
	{
		if(back < front)
		{
			return true;
		}
		return false;
	}
	
 	/**
 	Returns a boolean int value for the stack data structure passed in by
 	comparing if the front index is back to -1, meaning there are no elements
 	in the stack.
 	**/
 	int isEmptyStack(Node* stack[]) {
 		return front == -1;
	 }
	 
	 int isFull(Node* stack[]) {
	 	return front == 99;
	 }
	 
	 /**
	 This method takes in the array of nodes that represents the stack and the 
	 Node to push onto the stack. This Node is now the top/front of the stack.
	 **/
	 void push(Node* stack[], Node* node) 
	 {
	 	//If our stack is full, print error message and don't push
	 	if(isFull(stack))
	 	{
	 		printf("Stack full, cannot push.");
	 		return;
		 }
		 /*
		 Otherwise, our back/bottom is at index zero and our top/front is 
		 one index more. Add node to front/top index.
		 */
		 back = 0;
		 front += 1;
		 stack[front] = node;
	 }
	 
	 /**
	 This method takes in the array of nodes that represents the stack and 
	 returns the top/front of the array, without removing it or popping it
	 from the stack. 
	 **/
	 Node* peek(Node* stack[])
	 {
	 	//If our stack is not empty, return the front/top of the stack, but don't pop
	 	if(!isEmptyStack(stack))
	 	{
	 		return stack[front];
		 }
		 //If our stack is empty, simply return.
		 return;
	 }
	 
	 /**
	 This method takes in the array of nodes that represents the stack 
	 and returns the top/front of the array. It then decrements the 
	 front by 1, indicating that the Node is no longer part of the stack.
	 **/
	 Node* pop(Node* stack[]) 
	 {
	 	//Local node variable to return
	 	Node* node;
	 	//If stack is empty, print error message to user
	 	if(isEmptyStack(stack))
	 	{
	 		printf("Stack is empty\n");
	 		return;
	 	//Otherwise assign local node var to top/front of stack
		 } else {
		 	node = stack[front];
		 	//Remove 1 from front index, indicating the node has been removed
		 	front -= 1;
		 }
		 return node;
	 }
	
	/**
	This method creates a new Node with the int value that is passed in through
	the parameter. It allocates enough space to create the Node struct, then
	default assigns the left and right child as NULL and the parent as NULL
	then returns the Node.
	**/
	Node* newNode(int value)
	{
		Node* result = malloc(sizeof(Node));
		result->left = NULL;
		result->right = NULL;
		result->data = value;
		result->parent = NULL;
		return result;	
	}
	
	Node* queue[100];
	
	/**
	This method takes in the a node that is the root of the tree,
	and the intendedvalue that of that Node. It then creates the 
	Node and assigns the left and right children using a node array
	queue and returns the root of the tree.
	Helper method for construct().
	**/
	Node* insertNode(Node* root, int value)
	{
		//Create new node with parameter int value
		Node* node = newNode(value);
		
		/*
		If root is null, or there is no root to the tree yet
		root is now the new node and the parent is null
		*/
		if(root == NULL){
			root = node;
			root->parent = NULL;
		/*
		Moving from left first to right, assigning children to root 
		node parameter by using queue.
		*/
		} else if (getFront(queue)->left == NULL){
			getFront(queue)->left = node;
			node->parent = getFront(queue);
		} else {
			getFront(queue)->right = node;
			node->parent = getFront(queue);
			//Dequeuing once both children are filled
			dequeue(queue);
		}
		//Adding new created node to queue to continue adding nodes to tree
		enqueue(queue, node);
		//Return reference to the root of the tree to not lose changes.
		return root;
	}
	
	/**
	This method takes in an array of integers and for each integer 
	in the array, it inserts the Node with that value in the array
	to the tree then returns the root once all values have been passed 
	to the helper method. It has a helper method, construct().
	**/
	Node* construct(int arr[])
	{
		int i;
		Node* root = NULL;
		for(i=0; i<count; i++)
		{
			root = insertNode(root, arr[i]);
		}
		return root;
	}
	
	
	/**
	This function takes in no parameters, but returns a pointer to the array we read in from the text file.
	**/
	void readFile(char fileName[]){
		//Opens file in read mode
		file = fopen(fileName, "r");
		
		///If the file is null, it is not valid and cannot be opened. Return 1.
		if(NULL == file){
			printf("file cannot be opened \n");
		//File is found
		}else{
			printf("file found\n");
		}
		//Reading in file int by int until we reach EOF, or end of file
		while(fscanf(file, "%d", &nums[count])!= EOF){
    		nums[count++];
 		}
 		
 		//Close the file
 		fclose(file);
	}
	
	/**
	This method is called to print the binary tree breadth-first search style, or
	level by level, left to right. It takes in the root of the tree, resets the 
	front and back global variables, then uses a node array queue structures to 
	print each node in order. Once the queue is empty, it stops.
	**/
	void printBFS(Node* root)
	{
		//Reset global front/back index values to indicate empty queue
		reset();
		//Local node array queue structure
		Node* q[100];
		//If passed in root is null, the tree is empty
	    if(root == NULL){
	    	return;
		}
		//Using queue to print BFS-style
		enqueue(q, root);
		printf("BFS: ");
		while(!isEmptyQueue()){
			int val = getFront(q)->data;
			printf("%d ", val);
			if(getFront(q)->left != NULL){
				enqueue(q, getFront(q)->left);
			}
			if(getFront(q)->right != NULL){
				enqueue(q, getFront(q)->right);
			}
			dequeue(q);
		}
		printf("\n\n");
	}
	
	/**
	This method is called to print the binary tree depth-first search style. 
	It takes in the root of the tree, resets the front and back global 
	variables, then uses a node array stack structures to 
	print each node in order. Once the stack is empty, it stops.
	**/
	void printDFS(Node* root) {
		//Resetting front/back global variables to indicate empty stack
		reset();
		printf("DFS: ");
		//Creating node array stack structure to be used
		Node* stack[100];
		//If root is null, the tree is empty. Return.
		if(root == NULL) {
			return;
		}
		//Using stack to print nodes DFS-style
		push(stack, root);
		while(!isEmptyStack(stack))
		{
			Node* current = pop(stack);
			printf("%d ", current->data);
			if(current->right != NULL)
			{
				push(stack, current->right);
			}
			if(current->left != NULL) 
			{
				push(stack, current->left);
			}
		}
		printf("\n\n");
	}
	
	/**
	This method takes in the root of the binary tree and the value
	that the user is searching for in the tree. It resets the front 
	and back global variables then uses a node array queue to search
	for the node with the value BFS-style. If the node is found, it
	will remove the children of the node and print the height the node
	was found at. If the node is not found, it will print 
	a message that the node is not in the tree. It then returns
	a reference to the root of the tree so the changes won't disappear.
	**/
	Node* findNode(Node* root, int compare)
	{
		//Resetting front/back global variables to indicate empty queue.
		reset();
		//Local int variable to print once we find our node level
		int height = 0;
		//Node array queue to be used to search for node with value compare
		Node* q[100];
		//Local node variable to be returned.
		Node* node;
		//If root is null, tree is empty. Return.
	    if(root == NULL){
	    	return;
		}
		//Using queue to search the tree BFS-style.
		enqueue(q, root);
		while(!isEmptyQueue()){
			//Grabbing value of front of queue's node for comparison.
			int val = getFront(q)->data;
			//If the value at the front of the queue is the value we are searching for
			if(val == compare) {
				//Print node with value found.
				printf("Node with value %d found.\n", compare);
				//Checking to see if the node has children or not.
				if(getFront(q)->left != NULL || getFront(q)->right != NULL) {
					//Children found and removing the children and setting their children to NULL.
					printf("Removing children.\n");
					free(getFront(q)->left);
					getFront(q)->left = NULL;
					free(getFront(q)->left);
					getFront(q)->right = NULL;
				} else {
					//Indicating the node has no children and nothing will be removed.
					printf("No children found.\n");
				}
				node = pop(q);
				//Finding the height by moving from parent to parent and incrementing height
				while(node->parent != NULL) {
					height += 1;
					node = node->parent;
				}
				//Now that our node is the root of the tree, assign root to node.
				root = node;
				//Break the loop
				break;
			} else {
				//Else keep searching for node with value compare
				if(getFront(q)->left != NULL){
				enqueue(q, getFront(q)->left);
				}
				if(getFront(q)->right != NULL){
					enqueue(q, getFront(q)->right);
				}
				dequeue(q);
			}
		}
		//If our queue is empty by the end of the loop and our height is 0, we didn't find the value.
		if(isEmptyQueue() && height == 0) {
			printf("Node with value %d not in tree.\n", compare);
		//Otherwise, we have found the value. Print the level.
		} else {
			printf("Node with value %d on level %d.\n\n", compare, height);
		}
		//Return a reference to the root so we don't lose our changes to the tree.
		return root;
	}
	
	/**
	Executed when compiled and ran. This method reads a file of int values and 
	creates a binary tree of the values. It then prints the menu for the user 
	to perform different actions on the tree.
	**/
	int main(int argc, char **argv)
	{
		//Reading file of first parameter in compiler
		readFile(argv[1]);
		
		//Local variable to indicate user's choice of action.
		int num;
		//Create the tree by passing in global array we read in from file, called nums.
		Node* tree = construct(nums);
		printf("Tree successfully created.\n");
		printf("1: Type an integer to find its level and remove all nodes below it\n");
		printf("2: BFS traversal of tree\n");
		printf("3: DFS traversal of tree\n");
		printf("4: Exit\n");
		printf("5: Help\n");
		
		//Loop to continue asking the user for number input for 
		do {
			printf("Enter the associated number to the task you would like to do or 5 for help: \n");
			scanf("%d", &num);
			//Finding node with inputted value and removing all children below it.
			if(num == 1) {
				int val;
				int level = 0;
				printf("Enter a value to search for and remove: \n");
				scanf("%d", &val);
				tree = findNode(tree, val);
			//BFS traversal and print of tree
			} else if (num == 2) {
				printBFS(tree);
			//DFS traversal and print of tree
			} else if (num == 3) {
				printDFS(tree);
			//Help menu
			} else if (num == 5) {
				printf("1: Type an integer to find its level and remove all nodes below it\n");
				printf("2: BFS traversal of tree\n");
				printf("3: DFS traversal of tree\n");
				printf("4: Exit\n");
				printf("5: Help\n");
			//Anything below 1 or above 5 is an invalid option. Error message.
			} else if (num < 1 || num > 5 ) {
				printf("Not a valid option. Try again.\n");
			}
		//Using a loop until user inputs 4, which indicates they want to exit. Quit.
		} while (num != 4);
	}
	

		
