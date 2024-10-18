#ifndef LIST_H
#define LIST_H

#include "rprintf.h"
#include "serial.h"

#define BUFFER_SIZE 4096
#define ELEMENT_SIZE 128

struct listElement {
	int data;
	struct listElement *next;
};

extern struct listElement *listHead;
extern char buf[BUFFER_SIZE];
extern struct listElement *elementPool;
extern int elementInUse[ELEMENT_SIZE];

void init_list();
struct listElement *allocateElement(void);

void releaseElement(struct listElement *element);
void listAdd(struct listElement **listHead, struct listElement *newElement);
void listRemove(struct listElement *element);
void printList();

#endif












