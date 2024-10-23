#include "page.h"
#include "rprintf.h"

//struct ppage *physPageArray[PAGE_COUNT];
//struct ppage *freeList = NULL;

void init_pfa_list(void) {
	for (int i = 0; i < PAGE_COUNT - 1; i++) {
		physPageArray[i]->next = physPageArray[i + 1]; // forward link
		physPageArray[i + 1]->prev = physPageArray[i]; // backward link
	}
	physPageArray[0]->prev = NULL; // first page has no previous
	physPageArray[PAGE_COUNT]->next = NULL; // last page has no next
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
	if (start->prev) start->prev->next = curr; // if we're at node 1, link 0 to 2
	else freeList = curr; // freeList (previously NULL) is now equal to curr
	
	// if curr is not null, curr's previous node is now start's previous node
	if (curr) curr->prev = start->prev;

	start->prev = NULL;
	return start;

}

void freePhysPages(struct ppage *ppageList) {
	if (ppageList == NULL) return;

	// find the last page of the block being freed
	struct ppage *last = ppageList; // initialize pointer to input
	while (last->next != NULL) last = last->next; // iterate to end of list
	
	// find tail of the current free list
	struct ppage *tail = freeList;

	// if free list is empty, freed block becomes the free list
	if (tail == NULL) freeList = ppageList;	
	else {
		// traverse to end of the free list
		while (tail->next != NULL) tail = tail->next;

		// attach freed block to end of free list
		tail->next = ppageList;
		ppageList->prev = tail;
	}
	last->next = NULL; // make sure last page in the list points to null
}

void printFreeList(void) {
	struct ppage *curr = freeList;
	int count = 0;
	
	esp_printf(putc, "Free List: ");
	while (curr != NULL) {
		esp_printf(putc, "[%d] Physical Address: %p, prev: %p, next: %p -> ", count++, curr->physAddr, curr->prev, curr->next);
		curr = curr->next;
	}
	esp_printf(putc, "NULL\n");
}
