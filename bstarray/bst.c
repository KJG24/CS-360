/*
 Author: Koby Grah
 Class: CS 360
 Date: 07/10/2023
 Project: Binary Search Tree
 Description: This program allows the user to interface with a BST. The user will be
 able to create, add, delete, and add layers to the BST.
 The delete algo is implimented using the Hibbard Algorithm.
 */

#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

/*
 This function will handle the initial creation of the BST. Allowing the user to specify a
 given size of the new tree by passing an int.
 The function will create a tree of that size and autofill all nodes with the value zero.
 A pointer to the BST will be returned.
 Note: size will be the total size of the array the BST is stored in, not the height.
 */
BST* createEmptyTree(int size) {
    BST *newBST = malloc(sizeof(BST));
    newBST -> size = size;
    newBST -> tree = calloc(size, sizeof(int)); //calloc is used to autofill values as 0
    return newBST;
}

/*
 The growTree function will accept a given tree and grow it by one level.
 The new level will automatically be filled with all zero values.
 */
void growTree(BST* bst) {
    int i;
    int nextPower = 1; //holds the next power of two to compare against the size of the bst
    
    while (bst -> size > nextPower - 1) { //find current power of 2
        nextPower = nextPower * 2;
    }
    
    nextPower = nextPower * 2; //get the next power of 2
    
    // add 1 to the size of the tree to get a power of two, mul by two to get size of next
    // level, and then sub 1 as the array is always one less than a  power of 2
    int newSize = nextPower - 1;
    int *newTree = calloc(newSize, sizeof(int)); //create new tree of the correct size
    
    for (i = 0; i < bst -> size; i++) {
        newTree[i] = bst -> tree[i];
    }
    
    free(bst -> tree); //free old tree from memory
    bst -> size = newSize;
    bst -> tree = newTree;
    return;
}

/*
 The insertValue function takes a given tree and an integer value as an argument and will
 insert that int into the tree. Should the int be inserted correctly the function will
 return a 1, else it will return a -1. No duplicate numbers can be inserted and all
 numbers must be greater than 0.
 */
int insertValue(BST *bst, int value) {
    int i = 0;
    
    if (value <= 0) {
        return -1;
    }
    
    while (i < bst -> size) {
        if (bst -> tree[i] == 0) { //insert into empty node
            bst -> tree[i] = value;
            return 1; //return success
            
        } else if (bst -> tree[i] > value) {
            i = i * 2 + 1; //move to left child
            
        } else if (bst -> tree[i] < value) {
            i = i * 2 + 2; //move to right child
            
        } else if (bst -> tree[i] == value) {
            return -1; //indicate that a duplicate was found
            
        }
        //See if i > size, if so the tree needs to grow to insert. after reset i to move through new tree
        if (i >= bst -> size) {
            growTree(bst);
            i = 0;
        }
    }
    
    return -1; //indicates that size of tree is 0
}

int findValue(BST *bst, int value) {
    return 1;
}


int deleteValue(BST *bst, int value) {
    return 1;
}
