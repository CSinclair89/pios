#include "rprintf.h"
#include "list.h"
#include "serial.h"
#include "timer.h"
#include "page.h"

char glbl[128];

void kernel_main() {
    
	// Initialize bss segment variables and respective pointers
  	extern char __bss_start, __bss_end;
	char *bssStart, *bssEnd;  
	
	// Define bssStart and bssEnd variables
	bssStart = &__bss_start;
	bssEnd = &__bss_end;
	char *i = bssStart;
	
	// System timer call	
	waitFor1ms();

	// Serial port test  message
	esp_printf(putc, "Hello! Number: %d\n", 42);

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

	esp_printf(putc, "Initial list: ");
	printList();

	listRemove(b);
	esp_printf(putc, "List after removing 20: ");
	printList();

	listRemove(a);
	listRemove(c);
	listRemove(d);
	esp_printf(putc, "List after removing all: ");
	printList();
	
	/////////////////////////////
	// END LINKED LIST SECTION //
	/////////////////////////////
	
	////////////////////////////////
	// BEGIN PAGE FRAME ALLOCATOR //
	////////////////////////////////

	// initialize page frame allocator	
	//init_pfa_list();
	
	// define free list
	//freeList = physPageArray[0];

	// test print initial state
	// printFreeList();
	
	//////////////////////////////
	// END PAGE FRAME ALLOCATOR //
	//////////////////////////////

	// Set bss segment to zero
	for (; i < bssEnd; i++) {
	       	*i = 0;
	}

	while(1){
    }
}
