/*
 Author: Koby Grah
 Date: 06/26/2023
 Class: CS 360
 Project: Balanced Parentheses
 Description: This program will read a file that contains some code, the file will parsed to store all
 curley brackets, paranthesis, and square brackets in a stack. the program will then check that stack to verify if
 there is an appropriate nubmer of parentheses/brackets and if they were used in the correct order.
 If the file is balanced the program will print "BALANCED" and will print "UNBALANCED" if not.
 */

#include <stdio.h>
#include <stdlib.h>

//define a node to be used in the stack
struct node {
    char bracket;
    struct node* next;
};

struct node *stackInit();

void push(char, struct node*);

void deleteStack(struct node *);

int length(struct node *);

struct node *getTop(struct node *);

void pop(struct node *);



void main(int argc, char **argv) {
    char fileName[50];
    int i = 0; //genreal counter
    char data[100]; //holds the current line from the file
    
    if (argc != 2) { //check if a valid number of arguments has been given
        //printf("Invalid argument! Please declare the file you want to use after calling the program\n");
        return;
    }
    
    struct node *myStack = stackInit(); //create the stack
    sscanf(argv[1], "%s", fileName); //parse second arg for the filename
    FILE *fp = fopen(fileName, "r"); //open file in read only
    
    if (fp == NULL) { //check to make sure the file is valid
        //printf("Whoops! I can't read that file!\n");
        return;
    }
    
    while (fgets(data, 100, fp) != NULL) { //loop through entire file
        //loop through the line
        for (i = 0; i < 100; i++) {
            //printf("Testing char %c\n", data[i]);
            //if a bracket/paren is found then add to stack
            if (data[i] == '\n') { //check if a newline is found as the array holds the data from the longest line forever
                break;
            } else if (data[i] == '{') {
                push(data[i], myStack);
            } else if (data[i] == '}') {
                push(data[i], myStack);
            } else if (data[i] == '[') {
                push(data[i], myStack);
            } else if (data[i] == ']') {
                push(data[i], myStack);
            } else if (data[i] == '(') {
                push(data[i], myStack);
            } else if (data[i] == ')') {
                push(data[i], myStack);
            }
        }
    }
    
    fclose(fp); //close file after parse is completed
    
    //place logic for determining if the stack is balanced or not
    struct node *overflow = stackInit(); //second stack to hold values to be compared
    int isEmpty = length(myStack);
    
    /*
    if (isEmpty == 0) { //indicates that there were no bracket/paren in the file
        printf("BALANCED");
    }
    */
    
    while (isEmpty == 1) { //loop while stack isn't empty
        struct node *myStackTemp = getTop(myStack); //get top of stack
        
        //run through cases that will add to overflow stack
        if (myStackTemp -> bracket == '}') {
            push(myStackTemp -> bracket, overflow);
            pop(myStack); //remove node from top of stack
        } else if (myStackTemp -> bracket == ')') {
            push(myStackTemp -> bracket, overflow);
            pop(myStack);
        } else if (myStackTemp -> bracket == ']') {
            push(myStackTemp -> bracket, overflow);
            pop(myStack);
        }
        
        //run through cases that will remove from overflow stack
        if (myStackTemp -> bracket == '{') { //overflow must have at least one node and match bracket
            if (overflow -> next != NULL) { //check to see if overflow isn't empty
                struct node *overflowTemp = getTop(overflow);
                
                if (overflowTemp -> bracket == '}') {
                    pop(overflow);
                    pop(myStack);
                } else { //the curly brace should always work when detected
                    deleteStack(overflow); //free all memory in the stacks
                    deleteStack(myStack);
                    printf("UNBALANCED");
                    return;
                }
                
            } else { //triggers iff you attempt to remove a parenthesis compliment that doesn't exist
                deleteStack(overflow); //free all memory in the stacks
                deleteStack(myStack);
                printf("UNBALANCED");
                return;
            }
            
        } else if (myStackTemp -> bracket == '(') {
            if (overflow -> next != NULL) {
                struct node *overflowTemp = getTop(overflow);
                
                if (overflowTemp -> bracket == ')') {
                    pop(overflow);
                    pop(myStack);
                } else if (overflowTemp -> bracket == '}') {
                    pop(overflow);
                    pop(myStack);
                } else {
                    deleteStack(overflow); //free all memory in the stacks
                    deleteStack(myStack);
                    printf("UNBALANCED");
                    return;
                }
                
            } else {
                deleteStack(overflow); //free all memory in the stacks
                deleteStack(myStack);
                printf("UNBALANCED");
                return;
            }
            
        } else if (myStackTemp -> bracket == '[') {
            if (overflow -> next != NULL) {
                struct node *overflowTemp = getTop(overflow);
                
                if (overflowTemp -> bracket == ']') {
                    pop(overflow);
                    pop(myStack);
                    
                } else if (overflowTemp -> bracket == '}') {
                    pop(overflow);
                    pop(myStack);
                } else {
                    deleteStack(overflow); //free all memory in the stacks
                    deleteStack(myStack);
                    printf("UNBALANCED");
                    return;
                }
                
            } else {
                deleteStack(overflow); //free all memory in the stacks
                deleteStack(myStack);
                printf("UNBALANCED");
                return;
            }
        }
        
        isEmpty = length(myStack); //refresh to see if the stack is empty
    }
    
    isEmpty = length(overflow); //check to see if there are no left over chars
    
    if (isEmpty == 0) {
        printf("BALANCED");
    } else {
        printf("UNBALANCED");
    }
    
    deleteStack(overflow); //free all memory in the stacks
    deleteStack(myStack);
    return;
}

//function to handle the initial creation of the stack, the sent node will serve as the bottom of the stack
struct node *stackInit() {
    struct node *sent = malloc(sizeof(struct node)); //create sentry node
    sent -> bracket = '.'; //dummy value to indicate we are at the sent node
    sent -> next = NULL;
        
    return sent;
}

/*
 Parameters: data is a char that holds the value to be added to the stack, sent is the sentrey node of the stack
 Return Value: Void
 Description: add a given data to the stack
 */
void push(char data, struct node *sent) {
    struct node *temp = sent; //temparary tracking node
    struct node *new = malloc(sizeof(struct node)); //create new node with the given data
    new -> bracket = data;
    new -> next = NULL;
    
    while (temp -> next != NULL) { //loop until the end of the stack is found. aka the top
        temp = temp -> next;
    }
    
    temp -> next = new; //point to new node
    //printf("Added %c to the stack\n", data);
    return;
}

void deleteStack(struct node *sent) {
    struct node *temp = sent;
    
    while (sent != NULL) {
        temp = sent;
        sent = sent -> next;
        free(temp);
    }
    
    return;
}

//returns an int declaring if the stack is empty or not. 0 for empty and 1 for not empty
int length(struct node *sent) {
    struct node *temp = sent -> next; //move off sent node
    
    if (temp != NULL) { //if this is triggered the stack isn't empty
        return 1; //indicates stack isn't empty
    }
    
    return 0; //indicates stack is empty
}

//returns the top of the stack
struct node *getTop(struct node *sent) {
    struct node *temp = sent -> next;
    
    while (temp -> next != NULL) { //loop until you get to the top of the list
        temp = temp -> next;
    }
    
    return temp;
}

//deletes the top node in the given stack
void pop(struct node *sent) {
    struct node *next = sent -> next;
    struct node *previous = sent;
    
    while (next -> next != NULL) {
        previous = next;
        next = next -> next;
    }
    
    previous -> next = NULL;
    //printf("Deleted %c\n", next -> bracket);
    free(next);
    return;
}

