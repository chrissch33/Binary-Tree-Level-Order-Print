// Created by: Christopher Schenkhuizen
// Most Recent Change: Updated comments to be more descriptive and added a full header
// Most Recent Change Date: 1/19/17

// This is completely original code and I do not mind if you use it, just please give me credit
// or I will be sad.


// Welcome to my C program that attempts to print a tree in "Level Order" or in
// more common terms, a Breadth-First search and then print.

// WARNING: The logic of this program is rather abstract using numbers converted
//			to binary as a map of the tree. Drawing the tree and the binary values
//			will help when trying to DEBUG or understand the code here.

// TODO: Add the following functions:
//			- returns the number of levels of the binary tree (recursive?)

// TODO: Modify the following functions that already have functionality:
//			- print function to add the appropriate number of spaces for larger
//					numbers to keep a pleasing visual
//			- Within the main method, add safeguards against NULL nodes when
//					navigating through the tree


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// defining a basic structure node
typedef struct node {
	struct node *left; // Binary tree left
	struct node *right;  // Binary tree right
	int data; // Symbolic use of an int to represent anything the node could hold
} t_node;

// Function to create a new Binary Tree
// Essentially just returns a node with no pointers to any other node
t_node* t_new(int data) {
  t_node* new = (t_node*) malloc(sizeof(t_node));
  new->data = data;
  new->left = NULL;
  new->right = NULL;
  return new;
}

// Using a head node, recursively adds a node in a binary fashion of greater than
// or less than, putting the node into the right or left respectively
t_node* t_insert(t_node* root, int data) {
  if (root) { // NULL check

	// This line here adds the node to the left of the root if the value is less
	// than the head node (uses recursive call)
    if (root->data >= data) root->left = t_insert(root->left, data);
    else root->right = t_insert(root->right, data);

	// returns the node to which the value was added below
    return root;
  }

  // if the root was NULL, just create a new node
  else {
    return t_new(data);
  }
}

// completely frees a tree of all nodes
// This is a recursive function
void t_clean(t_node* node) {
  if (node) {
    t_clean(node->left);
    t_clean(node->right);
  }

  free(node);
}

// A quick function to do powers for testing purposes
int power(int a, int b) {
  if (b == 0) return 1;
  if (b < 0) return 0;

  int temp, i;
  temp = a;
  for (i = 1; i < b; i++) {
    a *= temp;
  }

  return a;
}

// Main method for testing purposes
int main() {

// The size of the array here is just the number of nodes in the tree
  int* levelorder = (int*) malloc(sizeof(int) * 7);
  int count = 1;

// Code block adds nodes to a tree to test if the tree properly properly adds nodes
  t_node* root = t_new(5);
  t_insert(root, 3);
  t_insert(root, 7);
  t_insert(root, 4);
  t_insert(root, 1);
  t_insert(root, 6);
  t_insert(root, 11);

// A known value to me. Could be derrived through a recursive or looped function
  int levels = 3;

// In order the print the tree in level order, I use a binary number to model
//	the left vs right search
  int binary;

// A pointer to take the place of the root without modifying the root pointer
  t_node* place = root;

// Begin to record the data in level order and place it in an array
  levelorder[0] = root->data;


// l is for the upper for loop to go through the levels of the array
// i is for going through the binary tree to keep track of the Left-Right pointer
//		location of each node in the level
// c is to keep track of the maximum number of nodes allowed in a level (powers of 2)
//		and to allow the most inner for-loop to go through each node in a level
  int l, i, c;

  // Loop through the levels of the binary tree
  for (l = 2; l < levels + 1; l++) {

	// reset the binary number to the proper number of values (powers of 2) for the current level
    binary = power(2, l) - 1;

	// Loops through the maximum number of nodes in a level
    for (c = 0; c < power(2, l - 1); c++) {

	  // Reset the current placeholder called place to the root node
      place = root;

	  // Loop through the binary number from before in terms of bits
	  for (i = l - 2; i >= 0; i--) {

		// A switch statement to either move left or right down the binary tree
		//		given the binary map of the tree (using binary numbers)
        switch (1 & (binary >> i)) {

		  // A 1 represents moving left down the tree
		  case 1:
	    	place = place->left;
	    	break;

		  // A 0 represents moving right down the tree
	  	  case 0:
	    	place = place->right;
	    	break;

		  // A safeguard against disaster and syntactical nessessity
	  	  default:
	    	printf("ERROR! NOT BINARY!\n");
	    	return 0;
        }
      }

	  // Change the binary map of the node by moving right along the tree (subtract 1)
      binary--;

	  // A NULL node check
      if (place)

		// Inset the value of the node found after the binary navigation into the
		//		array of its values
        levelorder[count] = place->data;

	  // Increment the place within the array and the count of the current number
	  //	of nodes
      count++;
    }
  }

  // Begin the print function
  printf("\n");

  // The array holds the data values in level order, just print out the values now
  for (i = 0; i < 7; i++) {
    printf("%d\n", levelorder[i]);
  }

  // Release the memory held by the tree and free the memory of the nodes
  t_clean(root);

  // Return successful completion of the print function
  return 0;
}
