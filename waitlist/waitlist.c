/*
 Author: Koby Grah
 Date: 07/17/2023
 Class: CS 360
 Project: Waitlist
 Description: This program simulates a Helpdesk environment where a user can input their name and describe their issue,
 and then is added to a queue to be helped. This is implimented via a queue, ie FIFO, using a struct that contains the
 first and last names of an individual and a description of their issue, and an additional struct that holds that persons info
 and points to the person ahead of them in line. This program will be able to add, delete, and find the head or tail of the queue.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "waitlist.h"

/*
 The queueInit function has no parameters and returns a pointer to a queue.
 This function will initialize the queue and create a sentinel node.
 */
struct node *queueInit() {
    //No need to dynamically allocate memory of an individual as all fields already have specified memory sizes
    struct individual sentIndividual = malloc(sizeof(struct individual));
    struct node sentNode = malloc(sizeof(struct node));
    
    sentIndividual.firstName = "SENTINEL";
    sentIndividual.lastName = "SENTINEL";
    sentIndividual.issue = "SENTINEL";
    
    sentNode -> person = sentIndividual;
    sentNode -> next = NULL;
    
    return sentNode;
}

/*
 queueAdd uses a pointer to a given queue, and strings of a persons name and issue as parameters. There is no return value.
 This function will take the given data and create a new individual, then insert that individual into a new node and add it
 to the existing queue.
 */
void queueAdd(struct node *queue, char *firstName, char *lastName, char *issue) {
    struct individual newPerson = malloc(sizeof(struct individual));
    struct newNode = malloc(sizeof(struct node));
    struct node temp = queue; //tracking node
    
    strcpy(newPerson.firstName, firstName);
    strcpy(newPerson.lastName, lastName);
    strcpy(newPerson.issue, issue);
    
    newNode -> person = newPerson;
    newNode -> next = NULL;
    
    while (temp -> next != NULL) { //find the tail of the queue
        temp = temp -> next;
    }
    
    temp -> next = newNode; //insert into list
    return;
}


