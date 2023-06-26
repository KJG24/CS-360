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

void add(char, struct node*);

void delete(struct node *);

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
            if (data[i] == '\n') {
                break;
            } else if (data[i] == '{') {
                add(data[i], myStack);
            } else if (data[i] == '}') {
                add(data[i], myStack);
            } else if (data[i] == '[') {
                add(data[i], myStack);
            } else if (data[i] == ']') {
                add(data[i], myStack);
            } else if (data[i] == '(') {
                add(data[i], myStack);
            } else if (data[i] == ')') {
                add(data[i], myStack);
            }
        }
    }
    
    fclose(fp); //close file after parse is completed
    
    //place logic for determining if the stack is balanced or not
    
    delete(myStack); //free all memory in the stack
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
void add(char data, struct node *sent) {
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

void delete(struct node *sent) {
    struct node *temp = sent;
    
    while (sent != NULL) {
        temp = sent;
        sent = sent -> next;
        free(temp);
    }
    
    return;
}
