#ifndef WAITLIST_H
#define WAITLIST_H

struct individual {
	char firstName[128];
	char lastName[128];
	char issue[256];
};

struct node {
	struct individual person;
	struct node *next;
};

struct node *queueInit();
void queueAdd(struct node *queue, char *firstName, char *lastName, char *issue);
struct individual queueDelete(struct node* queue);
struct individual queueHead(struct node* queue);
struct individual queueTail(struct node* queue);
void queueFree(struct node* queue);

#endif
