#include "ds.h"
#include "serial.h"
#include "rprintf.h"
#include "string.h"
#include "algos.h"

void listTests() {
	
	esp_printf(putc, "--LINKED LISTED TEST--\n\n");

	// initialize list
	listInit();

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
        listPrint();

	esp_printf(putc, "\n");

        listRemove(b);
        esp_printf(putc, "Linked List after removing 20: \n");
        listPrint();

	esp_printf(putc, "\n");

        listRemove(a);
        listRemove(c);
        listRemove(d);
        esp_printf(putc, "Linked List after removing 10, 30, and 40: \n"); 
        listPrint();

	esp_printf(putc, "\n");
	esp_printf(putc, "Linked List test complete.\n");

}

void mapTests() {

	esp_printf(putc, "--HASHMAP TEST--\n\n");

	// initialize map
	HashMap map;
	hashmapInit(&map);

	// add entries to map
	hashmapPut(&map, "apples", 6);
	hashmapPut(&map, "beans", 52);
	hashmapPut(&map, "potatoes", 2);

	esp_printf(putc, "Initial HashMap: \n");
	hashmapPrint(&map);

	esp_printf(putc, "\n");

	// update an existing entry
	hashmapPut(&map, "apples", 13);
	esp_printf(putc, "HashMap after updating apples value: \n");
	hashmapPrint(&map);

	esp_printf(putc, "\n");

	// add a new entry to check chaining
	hashmapPut(&map, "bananas", 1);
	esp_printf(putc, "HashMap after adding a new entry (to test chaining): \n");
	hashmapPrint(&map);

	esp_printf(putc, "\n");

	// manually free a node
	unsigned int index = hash("beans");
	HashMapNode *nodeToFree = map.table[index];

	if (nodeToFree != NULL && strEqual(nodeToFree->key, "beans")) {

		// remove node from table
		map.table[index] = nodeToFree->next;
		hashmapFreeNode(&map, nodeToFree); // add removed node to free list
	}

	esp_printf(putc, "HashMap after freeing node w/ key 'beans':\n");
	hashmapPrint(&map);

	esp_printf(putc, "\n");

	// get the value of present key
	esp_printf(putc, "Get the value of key 'potatoes':\n");
	esp_printf(putc, "%d\n", hashmapGet(&map, "potatoes"));

	esp_printf(putc, "\n");

	// get value of non-present key
	esp_printf(putc, "Get the value of non-present key 'twix' (should return 0):\n");
	esp_printf(putc, "%d\n", hashmapGet(&map, "twix"));

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

void setTests() {

	esp_printf(putc, "--SET TEST--\n\n");

	HashSet set;
	setInit(&set);

	esp_printf(putc, "Set size without any elements: ");	

	esp_printf(putc, "%d\n", setSize(&set));	

	esp_printf(putc, "\n");	
	
	setAdd(&set, 17);
	setAdd(&set, 8);
	setAdd(&set, 91);
	esp_printf(putc, "Set with 3 elements added:\n");
	setPrint(&set);	

	esp_printf(putc, "\n");

	setAdd(&set, 22);
	esp_printf(putc, "Adding another element:\n");
	setPrint(&set);	

	esp_printf(putc, "\n");	

	esp_printf(putc, "Confirming that set contains 91 (should return 1):\n");
	esp_printf(putc, "%d\n", setContains(&set, 91));	

	esp_printf(putc, "\n");	

	esp_printf(putc, "Confirming that set does NOT contain 54 (should return 0):\n");
	esp_printf(putc, "%d\n", setContains(&set, 54));	

	esp_printf(putc, "\n");	

	esp_printf(putc, "Set size:\n");
	esp_printf(putc, "%d\n", setSize(&set));	

	esp_printf(putc, "\n");	

	setRemove(&set, 8);
	setRemove(&set, 91);
	esp_printf(putc, "Removing 2 elements and printing new set:\n");	
	setPrint(&set);

	esp_printf(putc, "\n");	

	esp_printf(putc, "Trying to add an element already in the set (22):\n");
	setAdd(&set, 22);

	esp_printf(putc, "\n");
	esp_printf(putc, "Set test complete.\n");
}

void heapTests() {
	esp_printf(putc, "--HEAP TEST--\n\n");

	Heap heap;
	heapInit(&heap);

	maxHeapInsert(&heap, 8);
	maxHeapInsert(&heap, 12);
	maxHeapInsert(&heap, 21);
	maxHeapInsert(&heap, 3);
	maxHeapInsert(&heap, 89);
	maxHeapInsert(&heap, 23);
	maxHeapInsert(&heap, 45);
	maxHeapInsert(&heap, 66);
	maxHeapInsert(&heap, 17);
	maxHeapInsert(&heap, 7);
	maxHeapInsert(&heap, 30);

	esp_printf(putc, "Testing Max Heap Functions:\n");
	heapPrint(&heap);

	esp_printf(putc, "\n");

	esp_printf(putc, "Removing root element of max heap: %d\n", maxHeapExtract(&heap));
	heapPrint(&heap);

	esp_printf(putc, "\n");

	esp_printf(putc, "Removing non-max element from max heap: %d\n", 45);
	maxHeapDelete(&heap, 45);
	heapPrint(&heap);

	esp_printf(putc, "\n");

	esp_printf(putc, "Adding one more element to max heap: %d\n", 19);
	maxHeapInsert(&heap, 19);
	heapPrint(&heap);

	esp_printf(putc, "\n");

	esp_printf(putc, "Turning max heap into min heap:\n");
	maxHeapToMinHeap(&heap);
	heapPrint(&heap);

	esp_printf(putc, "\n");

	esp_printf(putc, "Removing all elements from min heap:\n");
	minHeapDelete(&heap, 3);
	minHeapDelete(&heap, 7);
	minHeapDelete(&heap, 8);
	minHeapDelete(&heap, 12);
	minHeapDelete(&heap, 17);
	minHeapDelete(&heap, 19);
	minHeapDelete(&heap, 21);
	minHeapDelete(&heap, 23);
	minHeapDelete(&heap, 30);
	minHeapDelete(&heap, 66);

	heapPrint(&heap);

	esp_printf(putc, "\n");

	esp_printf(putc, "Testing Min Heap Functions:\n");
	minHeapInsert(&heap, 4);
	minHeapInsert(&heap, 11);
	minHeapInsert(&heap, 22);
	minHeapInsert(&heap, 40);
	minHeapInsert(&heap, 41);
	minHeapInsert(&heap, 57);
	minHeapInsert(&heap, 60);
	minHeapInsert(&heap, 78);
	minHeapInsert(&heap, 91);
	minHeapInsert(&heap, 13);
	heapPrint(&heap);	
	
	esp_printf(putc, "\n");
	
	esp_printf(putc, "Removing root element of min heap: %d\n", minHeapExtract(&heap));
	heapPrint(&heap);	

	esp_printf(putc, "\n");
	
	esp_printf(putc, "Removing non-min element from min heap: %d\n", 41);
	minHeapDelete(&heap, 41);
	heapPrint(&heap);
	
	esp_printf(putc, "\n");

	esp_printf(putc, "Adding one more element to the min heap: %d\n", 19);
	minHeapInsert(&heap, 19);
	heapPrint(&heap);

	esp_printf(putc, "\n");

	esp_printf(putc, "Turning min heap into max heap:\n");
	minHeapToMaxHeap(&heap);
	heapPrint(&heap);

	esp_printf(putc, "\n");

	esp_printf(putc, "Removing all elements from max heap:\n");

	maxHeapDelete(&heap, 11);
	maxHeapDelete(&heap, 22);
	maxHeapDelete(&heap, 40);
	maxHeapDelete(&heap, 57);
	maxHeapDelete(&heap, 60);
	maxHeapDelete(&heap, 78);
	maxHeapDelete(&heap, 91);
	maxHeapDelete(&heap, 19);
	maxHeapDelete(&heap, 13);
	heapPrint(&heap);

	esp_printf(putc, "\n");

	esp_printf(putc, "Heap test complete.\n");
}
