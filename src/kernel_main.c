#include "rprintf.h"
#include "serial.h"
#include "timer.h"
#include "page.h"
#include "mmu.h"
#include "test.h"
#include "hashmap.h"
#include "string.h"

char glbl[128];
// extern struct table_descriptor_stage1 L1table[512];

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

	////////////////////////////////
	// BEGIN PAGE FRAME ALLOCATOR //
	////////////////////////////////

	// initialize page frame allocator	
	init_pfa_list();

	// test print of pfa list
	esp_printf(putc, "\nInitial Page Frame Allocation list");

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

	///////////////
	// BEGIN MMU //
	///////////////
	
	// define virtual & physical addresses
//	void *vAddr = (void *)0xC0000000;
//	void *pAddr = (void *)0x3F200000;
		
	// call mapPages with virtual-physical mapping
//	mapPages(vAddr, pAddr);

	// called loadPageTable() with base address of L1
//	loadPageTable(L1table);

	// test print to terminal via physical addr after mmu is turned on
//	esp_printf(putc_phys, "Test w/ physical addr");

	// test print to terminal via virtual addr after mmu is turned on
//	esp_printf(putc, "Test w/ virtual addr");

	/////////////
	// END MMU //
	/////////////

	esp_printf(putc, "\n");
	listTests();
	esp_printf(putc, "\n");
	mapTests();
	esp_printf(putc, "\n");
	twoSumTest();
	esp_printf(putc, "\n");
	queueTests();
	esp_printf(putc, "\n");

	// test system timer and reminder to terminate program
	waitFor(1000000);
	esp_printf(putc, "\nPress Ctrl + C to terminate the signal...\n");

	while(1){
    }
}
