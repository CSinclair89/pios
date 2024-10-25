#include "rprintf.h"
#include "list.h"
#include "serial.h"
#include "timer.h"
#include "page.h"
#include "mmu.h"

char glbl[128];

void kernel_main() {
    
	// Initialize bss segment variables and respective pointers
  	extern char __bss_start, __bss_end;
	char *bssStart, *bssEnd;  
	
	// Define bssStart and bssEnd variables
	bssStart = &__bss_start;
	bssEnd = &__bss_end;
	char *i = bssStart;
	
	// Set bss segment to 0
	for (; i < bssEnd; i++) *i = 0;

	// System timer call	
//	waitFor(1000000);

	// Serial port test  message
	esp_printf(putc, "Test print. Hello! Number: %d\n", 42);

	///////////////////////////////
	// BEGIN LINKED LIST SECTION //
	///////////////////////////////
			
	// initialize the normal linked list
	init_list();

	// allocate memory for list elements
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

	// the fun part
	waitFor(1000000);
	esp_printf(putc, "\nLoading Initial Linked List");
//	waitFor(500000);
	esp_printf(putc, ".");
//	waitFor(500000);
	esp_printf(putc, ".");
//	waitFor(500000);
	esp_printf(putc, ".\n");
//	waitFor(2300000);
	printList();

	listRemove(b);
//	waitFor(500000);
	esp_printf(putc, "\nLoading linked list after removing 20");
//	waitFor(500000);
	esp_printf(putc, ".");
//	waitFor(500000);
	esp_printf(putc, ".");
//	waitFor(1000000);
	esp_printf(putc, ".\n");
//	waitFor(1500000);
	printList();

	listRemove(a);
	listRemove(c);
	listRemove(d);
//	waitFor(1000000);
	esp_printf(putc, "\nLoading linked list after removing all");
//	waitFor(200000);
	esp_printf(putc, ".");
//	waitFor(700000);
	esp_printf(putc, ".");
//	waitFor(1000000);
	esp_printf(putc, ".\n");
//	waitFor(500000);
	printList();

	// end fun part
	
	/////////////////////////////
	// END LINKED LIST SECTION //
	/////////////////////////////
	
	////////////////////////////////
	// BEGIN PAGE FRAME ALLOCATOR //
	////////////////////////////////

	// initialize page frame allocator	
	init_pfa_list();

	// test print of pfa list
//	waitFor(1000000);
	esp_printf(putc, "\nLoading Page Frame Allocation list");
//	waitFor(500000);
	esp_printf(putc, ".");
//	waitFor(200000);
	esp_printf(putc, ".");
//	waitFor(1500000);
	esp_printf(putc, ".\n");
//	waitFor(2400000);
	printPhysAddr();

	// define free list
	freeList = &physPageArray[0];

	// test print initial state
	printFreeList();

	// allocate 10 pages and print again
	struct ppage *allocatedPages = allocatePhysPages(10);
	esp_printf(putc, "\nAllocated 10 pages:\n");
	printFreeList();

	// free the pages and print one last time
	freePhysPages(allocatedPages);
	esp_printf(putc, "\nFreed the previous 10 pages:\n");
	printFreeList();
	
	//////////////////////////////
	// END PAGE FRAME ALLOCATOR //
	//////////////////////////////

	// Call MMU - PROBLEM: there is no mmu_on() function
//	mmu_on();

	// reminder to end program
//	waitFor(1000000);
	esp_printf(putc, "\nPress Ctrl + C to terminate the signal...\n");

	while(1){
    }
}
