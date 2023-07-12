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

/*
 The findValue function takes a given tree and an integer value as parameters.
 It will then search the tree for the specified value, returning the index of the list if found, or -1 if not
 */
int findValue(BST *bst, int value) {
    int i = 0;
    
    while (i <= bst -> size) {
        if (bst -> tree[i] == value) { //check if value has been found
            return i;
            
        } else if (bst -> tree[i] > value) { //check if value is less than current index, move left
            i = i * 2 + 1;
            
        } else if (bst -> tree[i] < value) { //check if value is greater than current index, move right
            i = i * 2 + 2;
            
        }
    }
    
    return -1; //triggers if value isn't in tree
}

/*
 The deleteValue function uses a given tree and integer value as parameters.
 The function will search the tree for the value, if found it will be deleted, if not it will return -1.
 If the value is found and has no child nodes, the value is deleted from the tree.
 If the value has one child node it will be replaced with its single child.
 If the value has two children then the value is deleted and replaced with
 the initial right childs' leftmost child.
 Once deletion is complete the index of the deleted node is returned.
 */
int deleteValue(BST *bst, int value) {
    int valueIndex = findValue(bst, value);
    int i;
    int newTree[bst -> size];
    int leftChild = valueIndex * 2 + 1;
    int rightChild = valueIndex * 2 + 2;
    
    if (valueIndex == -1) { //triggers if the value isn't in the tree
        return -1;
    }
    
    //Case 1: The value to be deleted either has no child nodes or they are set to zero
    if ((bst -> tree[leftChild] == 0) || (leftChild > bst -> size)) {
        if ((bst -> tree[rightChild] == 0) || (rightChild > bst -> size)){
            bst -> tree[valueIndex] = 0;
            return valueIndex;
        }
    }
    

    //Case 3: The value has two child nodes.
    if ((bst -> tree[leftChild] != 0) && (leftChild <= bst -> size)) { //check that both nodes exist and are not null
        if ((bst -> tree[rightChild] != 0) && (rightChild <= bst -> size)) {
            int successorNode = rightChild;
            int previousSuccessorNode = successorNode;
            
            while ((bst -> tree[successorNode] != 0) && (successorNode <= bst -> size)) { //move through tree until successor is found
                previousSuccessorNode = successorNode;
                successorNode = successorNode * 2 + 1; //move to the left child node
            }
            
            int replacementValue = bst -> tree[previousSuccessorNode]; //replacement value to be deleted with the smallest value in subtree
            deleteValue(bst, bst -> tree[previousSuccessorNode]); //recall function to remove the smallest value in the subtree and balance
            bst -> tree[valueIndex] = replacementValue;
            return valueIndex;
        }
    }
    
    //Case 2: The value has one child node
    if (bst -> tree[leftChild] != 0) {
        /*
         This algo works by doing the initial replacements and then once the null values of the empty
         child have been skipped, loop through the rest of the list and place them in the correct spot
         */
        bst -> tree[valueIndex] = bst -> tree[leftChild];
        bst -> tree[leftChild] = bst -> tree[leftChild * 2 + 1];
        bst -> tree[leftChild + 1] = bst -> tree[leftChild * 2 + 2];
        int nextValueIndexAfterRight = rightChild * 2 + 3;
        
        for (i = leftChild + 2; i < bst -> size - 1; i++) {
            bst -> tree[i] = bst -> tree[nextValueIndexAfterRight++];
        }
        
        bst -> tree[bst -> size - 1] = 0;
        return valueIndex;
        
    } else if (bst -> tree[rightChild] != 0) {
        bst -> tree[valueIndex] = bst -> tree[rightChild];
        bst -> tree[leftChild] = bst -> tree[rightChild * 2 + 1];
        bst -> tree[rightChild] = bst -> tree[rightChild * 2 + 2];
        int nextValueIndexAfterLeft = (((rightChild * 2) + 2) * 2) + 1;
        
        for (i = rightChild + 1; nextValueIndexAfterLeft < bst -> size - 1; i++) {
            bst -> tree[i] = bst -> tree[nextValueIndexAfterLeft++];
        }
        
        for (i; i < bst -> size - 1; i++) { //fill in the new bottom layer with all zeros
            bst -> tree[i] = 0;
        }
        return valueIndex;
    }
}
