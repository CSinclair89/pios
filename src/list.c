#include "rprintf.h" 
#include "list.h"
#include "serial.h"

#define ELEMENT_SIZE 128

char buf[4096];

// memory management variables
struct listElement *elementPool = (struct listElement *)buf;
struct listElement *listHead = NULL;
int elementInUse[ELEMENT_SIZE]; // keep track of element usage (max 128 elements)

// initialize memory pool and usage tracker
void init_list() {
	for (int i = 0; i < ELEMENT_SIZE; i++) elementInUse[i] = 0; // all elements are initially set to zero
}

// function to allocate unused element from buf
struct listElement *allocateElement() {
	for (int i = 0; i < ELEMENT_SIZE; i++) {
		if (!elementInUse[i]) {
			elementInUse[i] = 1; // mark element as used
			return &elementPool[i];
		}
	}
	return NULL;
}

// function to release an element back to the pool
void releaseElement(struct listElement *element) {
	for (int i = 0; i < ELEMENT_SIZE; i++) {
		if (&elementPool[i] == element) {
			elementInUse[i] = 0; // mark element as free
			return; 
		}
	}
}

// function to add a new element to the tail of the list
void listAdd(struct listElement **listHead, struct listElement *newElement) {
	if (newElement == NULL) return; // confirm that the new element is NOT null
	newElement->next = NULL; // set the new element's next pointer to null

	// if the list is empty, make the new element the head
	if (*listHead == NULL) *listHead = newElement;
	else { // traverse the list to find the last element
		struct listElement *curr = *listHead;
		while (curr->next != NULL) curr = curr->next;
		curr->next = newElement;
	}
}

void listRemove(struct listElement *element) {
	if (element == NULL || listHead == NULL) return; // if list is empty, return
	
	// removing head of the list
	if (listHead == element) {
		listHead = element->next;
		releaseElement(element);
		return;
	}

	// traversing the list to find element's predecessor
	struct listElement *curr = listHead;
	while (curr->next != NULL && curr->next != element) curr = curr->next;

	// if element is found, unlink it
	if (curr ->next == element) {
		curr->next = element->next;
		releaseElement(element);
	}
}

// function to print list to serial port
void printList() {
	struct listElement *curr = listHead;
	while (curr != NULL) {
		esp_printf(putc, "%d -> ", curr->data);
		curr = curr->next;
	}
	esp_printf(putc, "NULL\n");
}
