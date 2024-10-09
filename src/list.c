#include <stdio.h>
#include <stdlib.h>

// define structure for a node element
typedef struct Node {
	int data; // value of the node
	struct Node* next; // pointer to the next node
} Node;

Node* head = NULL; // initialize the head of the linked list

// add a new node to the beginning of the linked list
void listAdd(int value) {
	Node* newNode = (Node*)malloc(sizeof(Node)); // allocate memory for the new node
	newNode->data = value; // set the new node's value to the input value
	newNode->next = head; // point the new node to the current head
	head = newNode; // update head to point to the new node
}

// remove the first occurrence of a value from the linked list
void listRemove(int value) {
	Node* curr = head; // start from the head
	Node* prev = NULL; // previous node pointer
	
	// traverse the list to find the node to remove
	while (curr != NULL && curr->data != value) {
		prev = curr; // move previous to current
		curr = curr->next; // move to the next node
	}

	// if the value is found...
	if (curr != NULL) {
		if (prev == NULL) {
			// node to remove is the head
			head = curr->next; // update head to the next node
		} else {
			// bypass the current node
			prev->next = curr->next;
		}
		free(curr);
	}
}

// print the linked list
void printList() {

	Node* curr = head; // start from the head
	
	while (curr != NULL) {
		printf("%d -> ", curr->data); // print data
		curr = curr->next;
	}
	printf("NULL\n");
}

int main() {
	listAdd(20);
	listAdd(15);
	listAdd(8);

	printList();

	listRemove(15);

	printList();

	listRemove(20);
	listRemove(8);
	
	printList();

	return 0;
}














