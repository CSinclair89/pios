#include "list.h"
#include "page.h"
#include "serial.h"
#include "rprintf.h"
#include "hashmap.h"
#include "string.h"
#include "algos.h"
#include "queue.h"
#include "stack.h"

void listTests() {
	
	esp_printf(putc, "--LINKED LISTED TEST--\n\n");

	// initialize list
	init_list();

	// add elements
	struct listElement *a = allocateElement();
        struct listElement *b = allocateElement();
        struct listElement *c = allocateElement();
        struct listElement *d = allocateElement();
        
        // define data for list elements
        a->data = 10;
        b->data = 20;
        c->data = 30;
        d->data = 40;

        // add list elements to list using listHead address as starting point
        listAdd(&listHead, a);
        listAdd(&listHead, b);
        listAdd(&listHead, c);
        listAdd(&listHead, d);

        esp_printf(putc, "Initial Linked List: \n");
        printList();

	esp_printf(putc, "\n");

        listRemove(b);
        esp_printf(putc, "Linked List after removing 20: \n");
        printList();

	esp_printf(putc, "\n");

        listRemove(a);
        listRemove(c);
        listRemove(d);
        esp_printf(putc, "Linked List after removing 10, 30, and 40: \n"); 
        printList();

	esp_printf(putc, "\n");
	esp_printf(putc, "Linked List test complete.\n");

}

void mapTests() {

	esp_printf(putc, "--HASHMAP TEST--\n\n");

	// initialize map
	HashMap map;
	init_hashmap(&map);

	// add entries to map
	addEntry(&map, "apples", 6);
	addEntry(&map, "beans", 52);
	addEntry(&map, "potatoes", 2);

	esp_printf(putc, "Initial HashMap: \n");
	printHashMap(&map);

	esp_printf(putc, "\n");

	// update an existing entry
	addEntry(&map, "apples", 13);
	esp_printf(putc, "HashMap after updating apples value: \n");
	printHashMap(&map);

	esp_printf(putc, "\n");

	// add a new entry to check chaining
	addEntry(&map, "bananas", 1);
	esp_printf(putc, "HashMap after adding a new entry (to test chaining): \n");
	printHashMap(&map);

	esp_printf(putc, "\n");

	// manually free a node
	unsigned int index = hash("beans");
	Node *nodeToFree = map.table[index];

	if (nodeToFree != NULL && strEqual(nodeToFree->key, "beans")) {

		// remove node from table
		map.table[index] = nodeToFree->next;
		freeNode(&map, nodeToFree); // add removed node to free list
	}

	esp_printf(putc, "HashMap after freeing node w/ key 'beans':\n");
	printHashMap(&map);

	esp_printf(putc, "\n");

	// get the value of present key
	esp_printf(putc, "Get the value of key 'potatoes':\n");
	esp_printf(putc, "%d\n", getValue(&map, "potatoes"));

	esp_printf(putc, "\n");

	// get value of non-present key
	esp_printf(putc, "Get the value of non-present key 'twix' (should return 0):\n");
	esp_printf(putc, "%d\n", getValue(&map, "twix"));

	esp_printf(putc, "\n");
	esp_printf(putc, "HashMap test complete.\n");

}

void queueTests() {

	esp_printf(putc, "--QUEUE TEST--\n\n");

	struct Queue queue;
	queueInit(&queue);

	enqueue(&queue, 10);
	enqueue(&queue, 20);
	enqueue(&queue, 30);

	esp_printf(putc, "Queue elements: ");
	queuePrint(&queue);

	esp_printf(putc, "\n");

	esp_printf(putc, "Dequeued: %d\n", dequeue(&queue));

	esp_printf(putc, "\n");

	esp_printf(putc, "Queue after dequeue: ");
	queuePrint(&queue);

	esp_printf(putc, "\n");

	esp_printf(putc, "Front element: %d\n", queuePeek(&queue));

	esp_printf(putc, "\n");
	esp_printf(putc, "Queue test complete.\n");

}

void twoSumTest() {

	esp_printf(putc, "--TWO SUM TEST--\n\n");

	int nums[4] = {7, 2, 11, 15};
	int target = 9;
	char key[32], diffStr[32];
	int numSize = sizeof(nums) / sizeof(nums[0]);

	esp_printf(putc, "Two Sum test w/ HashMap implementation:\n");
	esp_printf(putc, "Input array: [7, 2, 11, 15]\nTarget: 9\nExpected indices: {0, 1}\nReturned indices: ");

	twoSum(nums, numSize, target, key, diffStr);

	esp_printf(putc, "\n");
	esp_printf(putc, "Two Sum test complete.\n");	


}

void stackTests() {

	esp_printf(putc, "--STACK TEST--\n\n");	
	
	Stack stack;
	stackInit(&stack);
	stackPush(&stack, 6);
	stackPush(&stack, 81);
	stackPush(&stack, 4);
	stackPush(&stack, 14);

	esp_printf(putc, "Initial stack (bottom to top):\n");	
	stackPrint(&stack);

	esp_printf(putc, "\n");	

	esp_printf(putc, "Peeking at top element (should be 14):\n");
	esp_printf(putc, "%d\n", stackPeek(&stack));	

	esp_printf(putc, "\n");	

	esp_printf(putc, "Popping top two elements (should be 14, 4):\n");
	esp_printf(putc, "%d, %d\n", stackPop(&stack), stackPop(&stack));

	esp_printf(putc,"\n");	

	esp_printf(putc, "Printing stack after above elements are popped:\n");
	stackPrint(&stack);

	esp_printf(putc, "\n");	

	esp_printf(putc, "Adding one more element to top of stack:\n");
	stackPush(&stack, 7);
	stackPrint(&stack);

	esp_printf(putc, "\n");	

	esp_printf(putc, "Stack after popping remaining elements: \n");
	stackPop(&stack);
	stackPop(&stack);
	stackPop(&stack);

	stackPrint(&stack);	

	esp_printf(putc, "\n");	

	esp_printf(putc, "Stack test complete.\n");	
}
