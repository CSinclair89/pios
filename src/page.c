#include "page.h"
#include "rprintf.h"

#define PAGE_SIZE 2048

struct ppage physPageArray[PAGE_COUNT];
struct ppage *freeList = NULL;

void init_pfa_list(void) {
	for (int i = 0; i < PAGE_COUNT; i++) {
		if (i < PAGE_COUNT - 1) {
			physPageArray[i].next = &physPageArray[i + 1]; // forward link
			physPageArray[i + 1].prev = &physPageArray[i]; // backward link
		}

		physPageArray[i].physAddr = (void *)(i * PAGE_SIZE); // test data value
	}
	physPageArray[0].prev = NULL; // first page has no previous
	physPageArray[PAGE_COUNT - 1].next = NULL; // last page has no next
	
	freeList = &physPageArray[0];
}

void printPhysAddr(void) {
	for (int i = 0; i < 10; i++) {
		esp_printf(putc, "Page %d, Physical Address: 0x%x\n", i, (unsigned int)physPageArray[i].physAddr);
	}
}

struct ppage *allocatePhysPages(unsigned int npages) {
	struct ppage *start = freeList;
	struct ppage *curr = freeList;

	if (npages == 0 || freeList == NULL) return NULL; // invalid allocation
	
	// traverse free list to find 'npages' consecutive pages
	for (unsigned int i = 0; i < npages; i++) {
		if (curr == NULL) return NULL; // not enough pages
		curr = curr->next;
	}

	// detach allocated pages from free list
	if (start == freeList) freeList = curr; // update head if we're allocating from head
	else if (start->prev) start->prev->next = curr; // link prev to next
	
	// if curr is not null, curr's previous node is now start's previous node
	if (curr) curr->prev = start->prev;

	start->prev = NULL;

	esp_printf(putc, "Allocated %d pages. New freeList head: 0x%x\n", npages, freeList->physAddr);
	return start;

}

void freePhysPages(struct ppage *ppageList) {
	if (ppageList == NULL) return;

	// find the last page of the block being freed
	struct ppage *last = ppageList; // initialize pointer to input
	while (last->next != NULL) last = last->next; // iterate to end of list

	// check if the block is already part of the free list
	if (last->next == freeList || ppageList == freeList || last == freeList || last == freeList->prev) {
		esp_printf(putc, "Error: trying to free pages already in free list.\n");
		return;
	}

	// attach the freed list to front of the free list
	last->next = freeList;
	if (freeList != NULL) freeList->prev = last;

	// update the free list head
	freeList = ppageList;

	// ensure previous pointer of head is null
	freeList->prev = NULL;

	esp_printf(putc, "Freed pages added. New freeList head: 0x%x\n", freeList->physAddr);
}

void printFreeList(void) {
	struct ppage *curr = freeList;
	int count = 0;
	if (curr == NULL) {
		esp_printf(putc, "Free List is empty.\n");
		return;
	}	
	esp_printf(putc, "Free List:\n");
	while (curr != NULL) {
		esp_printf(putc, "[%d] Physical Address: 0x%x, prev: 0x%x, next: 0x%x\n", count, curr->physAddr, curr->prev->physAddr, curr->next->physAddr);
		if (count > PAGE_COUNT - 1) {
			esp_printf(putc, "Error: Detected circular reference.\n");
			break;
		}
		curr = curr->next;
		count++;
	}
	esp_printf(putc, "End of Free List (NULL)\n");
}
